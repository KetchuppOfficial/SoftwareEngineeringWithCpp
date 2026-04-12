// Thanks Herb Sutter for insight on the correct implementation :)

namespace {

class Wrapper;

using FuncPtr = Wrapper (*)();

class Wrapper {
  public:
    Wrapper(FuncPtr p) : p_{p} {}
    operator FuncPtr() { return p_; }

  private:
    FuncPtr p_;
};

Wrapper foo() { return foo; }

} // unnamed namespace

int main() {
    Wrapper wrapper = foo();
    (*wrapper)();
}
