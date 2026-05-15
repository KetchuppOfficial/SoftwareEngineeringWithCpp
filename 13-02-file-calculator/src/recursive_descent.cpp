#include <cctype>
#include <cmath>
#include <fstream>
#include <optional>
#include <print>
#include <sstream>
#include <string>
#include <unordered_map>
#include <variant>

class Stream final {
  public:
    using token_t = std::variant<char, double, std::string>;

    explicit Stream(const std::string &string) : m_stream(string + ';') {}

    bool empty() { return m_stream.peek() == ';'; }

    token_t get() {
        if (m_token.has_value()) {
            auto token = *std::move(m_token);
            m_token.reset();
            return token;
        }

        char c{};
        m_stream >> c;

        switch (c) {
        case '+':
        case '-':
        case '*':
        case '/':
        case '%':
        case '^':
        case '!':
        case '(':
        case ')':
        case '[':
        case ']':
        case '{':
        case '}':
        case ';':
            return token_t(c);

        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '.': {
            m_stream.unget();
            double y{};
            m_stream >> y;
            return token_t(y);
        }

        default: {
            std::string string(1, c);
            while (m_stream.get(c) && (std::isalpha(c) || std::isdigit(c))) {
                string.push_back(c);
            }
            if (!std::isspace(c)) {
                m_stream.unget();
            }
            return token_t(std::move(string));
        }
        }
    }

    void put(token_t token) { m_token.emplace(std::move(token)); }

  private:
    std::stringstream m_stream;
    std::optional<token_t> m_token;
};

template <typename... F>
struct Overloaded : public F... {
    using F::operator()...;
};

class Calculator final {
  public:
    void test() {
        std::string string;
        std::ifstream file{"input.txt"}; // I'm too tired to implement CLI parsing... Sorry...
        while (std::getline(file >> std::ws, string, '\n')) {
            if (string.empty()) {
                break;
            }

            Stream stream(string);
            if (!stream.empty()) {
                std::println("{} = {}", string, statement(stream));
            }
        }
    }

  private:
    double statement(Stream &stream) {
        auto token = stream.get();
        if (const auto *str = std::get_if<std::string>(&token)) {
            if (*str == "set") {
                return declaration(stream);
            }
        }
        stream.put(std::move(token));
        return expression(stream);
    }

    double declaration(Stream &stream) {
        const auto name = std::get<std::string>(stream.get());
        return m_variables[name] = expression(stream);
    }

    // expression ::= term { ('+'|'-') term }
    double expression(Stream &stream) const {
        double x = term(stream);
        auto token = stream.get();
        while (true) {
            switch (std::get<char>(token)) {
            case '+':
                x += term(stream);
                break;
            case '-':
                x -= term(stream);
                break;
            default:
                stream.put(std::move(token));
                return x;
            }
            token = stream.get();
        }
    }

    // term ::= power { ('*'|'/'|'%') power }
    double term(Stream &stream) const {
        double x = power(stream);
        auto token = stream.get();
        while (true) {
            switch (std::get<char>(token)) {
            case '*':
                x *= power(stream);
                break;
            case '/':
                x /= power(stream);
                break;
            case '%': {
                double y = power(stream);
                x = std::fmod(x, y);
                break;
            }
            default:
                stream.put(std::move(token));
                return x;
            }
            token = stream.get();
        }
    }

    // power ::= primary { '^' primary }
    double power(Stream &stream) const {
        double x = primary(stream);
        auto token = stream.get();
        for (char *c_ptr{}; (c_ptr = std::get_if<char>(&token)) != nullptr && *c_ptr == '^';) {
            double y = primary(stream);
            x = std::pow(x, y);
            token = stream.get();
        }
        stream.put(std::move(token));
        return x;
    }

    // primary ::= number | variable | '(' expression ')' | '[' expression ']' | '{' expression '}'
    //            | '+' primary | '-' primary
    //            | primary '!'
    double primary(Stream &stream) const {
        auto token = stream.get();

        if (auto *c_ptr = std::get_if<char>(&token)) {
            switch (*c_ptr) {
            case '(': {
                double x = expression(stream);
                stream.get(); // ')'
                return handle_factorial(stream, x);
            }
            case '[': {
                double x = expression(stream);
                stream.get(); // ']'
                return handle_factorial(stream, x);
            }
            case '{': {
                double x = expression(stream);
                stream.get(); // '}'
                return handle_factorial(stream, x);
            }
            case '+':
                return handle_factorial(stream, primary(stream));
            case '-':
                return handle_factorial(stream, -primary(stream));
            default:
                stream.put(token);
                break;
            }
        }

        double value =
            std::visit(Overloaded{[](double d) { return d; },
                                  [&variables = m_variables](const std::string &str) {
                                      return variables.at(str);
                                  },
                                  [](char) -> double { throw std::runtime_error("syntax error"); }},
                       token);

        return handle_factorial(stream, value);
    }

    double handle_factorial(Stream &stream, double value) const {
        auto token = stream.get();
        if (char *c_ptr{}; (c_ptr = std::get_if<char>(&token)) != nullptr && *c_ptr == '!') {
            auto n = static_cast<long long>(value);
            if (n < 0 || value != n) {
                throw std::runtime_error("factorial is defined for non-negative integers");
            }
            long long result = 1;
            for (long long i = 2; i <= n; ++i)
                result *= i;
            return static_cast<double>(result);
        }
        stream.put(token);
        return value;
    }

    std::unordered_map<std::string, double> m_variables;
};

int main() try {
    Calculator().test();
    return 0;
} catch (const std::exception &e) {
    std::println(stderr, "Caught an instance of {}.\nwhat(): {}", typeid(e).name(), e.what());
    return EXIT_FAILURE;
} catch (...) {
    std::println(stderr, "Caught an unknown exception.");
    return EXIT_FAILURE;
}
