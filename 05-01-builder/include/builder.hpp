#ifndef INCLUDE_BUILDER_HPP
#define INCLUDE_BUILDER_HPP

#include <memory>
#include <string>
#include <utility>

namespace dts {

struct Person {
    std::string name;
    unsigned age = 0;
    unsigned grade = 0;
};

class Builder final {
  public:
    Builder() : object_{std::make_unique<Person>()} {}

    Builder &name(const char *name) {
        object_->name = name;
        return *this;
    }

    Builder &name(std::string name) {
        object_->name = std::move(name);
        return *this;
    }

    Builder &age(unsigned age) {
        object_->age = age;
        return *this;
    }

    Builder &grade(unsigned grade) {
        object_->grade = grade;
        return *this;
    }

    const Person &get() const { return *object_; }

  private:
    std::unique_ptr<Person> object_;
};

} // namespace dts

#endif // INCLUDE_BUILDER_HPP
