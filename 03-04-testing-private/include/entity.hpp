#ifndef INCLUDE_ENTITY_HPP
#define INCLUDE_ENTITY_HPP

namespace dts {

class Entity final {
    friend class Test_v1_Attorney;
    friend class Test_v2_Attorney;

    int test_v1() const { return 0; }
    int test_v2() const { return 42; }
};

class Test_v1_Attorney {
    friend class Tester_v1;

    static int test(const Entity &e) { return e.test_v1(); }
};

class Test_v2_Attorney {
    friend class Tester_v2;

    static int test(const Entity &e) { return e.test_v2(); }
};

class Tester_v1 final {
  public:
    static int test(const Entity &e) { return Test_v1_Attorney::test(e); }
};

class Tester_v2 final {
  public:
    static int test(const Entity &e) { return Test_v2_Attorney::test(e); }
};

} // namespace dts

#endif // INCLUDE_ENTITY_HPP
