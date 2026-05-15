#include <cmath>
#include <cstddef>
#include <cstdio>
#include <iostream>
#include <istream>
#include <print>
#include <string>
#include <string_view>
#include <vector>

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>

class Operand : public boost::spirit::x3::variant<double,

                                                  boost::spirit::x3::forward_ast<struct Sign>,

                                                  boost::spirit::x3::forward_ast<struct Power>,

                                                  boost::spirit::x3::forward_ast<struct List>> {
  public:
    using base_type::base_type, base_type::operator=;
};

struct Sign {
    char operation = '\0';
    Operand operand;
};

struct Factorial {
    char operation = '\0';
};

struct Power {
    Operand head;
    std::vector<Factorial> factorials;
};

struct Step {
    char operation = '\0';
    Operand operand;
};

struct List {
    Operand head;
    std::vector<Step> steps;
};

BOOST_FUSION_ADAPT_STRUCT(Sign, operation, operand)
BOOST_FUSION_ADAPT_STRUCT(Factorial, operation)
BOOST_FUSION_ADAPT_STRUCT(Power, head, factorials)
BOOST_FUSION_ADAPT_STRUCT(Step, operation, operand)
BOOST_FUSION_ADAPT_STRUCT(List, head, steps)

namespace parser {

namespace x3 = boost::spirit::x3;

x3::rule<struct expression_tag, List> expression;
x3::rule<struct term_tag, List> term;
x3::rule<struct power_tag, List> power_rule;
x3::rule<struct factor_tag, Operand> factor;
x3::rule<struct postfix_tag, Power> postfix;

// expression : + -
auto const expression_def = term >> *(x3::char_('+') >> term |

                                      x3::char_('-') >> term);

// term : * / %
auto const term_def = power_rule >> *(x3::char_('*') >> power_rule |

                                      x3::char_('/') >> power_rule |

                                      x3::char_('%') >> power_rule);

// power : ^
auto const power_rule_def = postfix >> *(x3::char_('^') >> postfix);

// postfix : !
auto const postfix_def = factor >> *(x3::char_('!'));

// factor : unary + grouping
auto const factor_def = (x3::char_('+') >> factor |

                         x3::char_('-') >> factor |

                         x3::double_ |

                         '(' >> expression >> ')' |

                         '[' >> expression >> ']' |

                         '{' >> expression >> '}');

BOOST_SPIRIT_DEFINE(expression, term, power_rule, factor, postfix);

} // namespace parser

class Calculator final {
  public:
    double factorial(double x) const {
        if (x < 0) {
            return std::nan("");
        }

        auto n = static_cast<unsigned long long>(x);

        double result = 1.0;
        for (unsigned long long i = 2; i <= n; ++i) {
            result *= i;
        }
        return result;
    }

    double operator()(double x) const { return x; }

    double operator()(const Sign &sign) const {
        auto x = boost::apply_visitor(*this, sign.operand);
        switch (sign.operation) {
        case '+':
            return x;
        case '-':
            return -x;
        default:
            return x;
        }
    }

    double operator()(const Power &power) const {
        auto x = boost::apply_visitor(*this, power.head);

        for (const auto &step : power.factorials) {
            if (step.operation == '!') {
                x = factorial(x);
            }
        }

        return x;
    }

    double operator()(const Step &step, double x) const {
        auto y = boost::apply_visitor(*this, step.operand);
        switch (step.operation) {
        case '+':
            return x + y;
        case '-':
            return x - y;
        case '*':
            return x * y;
        case '/':
            return x / y;
        case '%':
            return std::fmod(x, y);
        case '^':
            return std::pow(x, y);
        default:
            return x;
        }
    }

    double operator()(List const &list) const {
        auto x = boost::apply_visitor(*this, list.head);
        for (const auto &step : list.steps) {
            x = (*this)(step, x);
        }
        return x;
    }
};

auto parse(std::string_view view) {
    List list;

    auto begin = view.begin();
    auto end = view.end();
    auto result = boost::spirit::x3::phrase_parse(begin, end, parser::expression,
                                                  boost::spirit::x3::ascii::space, list);
    if (!result || begin != end) {
        throw std::runtime_error("parse error");
    }

    static Calculator calculator;
    return calculator(list);
}

int main() try {
    std::println("Enter expression(s):");

    std::string string;
    while (std::getline(std::cin >> std::ws, string, '\n')) {
        if (string.empty() || string.front() == ';') {
            break;
        }
        std::println("{} = {}", string, parse(string));
    }
} catch (const std::exception &e) {
    std::println(stderr, "Caught an instance of {}.\nwhat(): {}", typeid(e).name(), e.what());
    return EXIT_FAILURE;
} catch (...) {
    std::println(stderr, "Caught an unknown exception.");
    return EXIT_FAILURE;
}
