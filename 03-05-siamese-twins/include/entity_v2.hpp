#ifndef INCLUDE_ENTITY_V2_HPP
#define INCLUDE_ENTITY_V2_HPP

namespace dts {

class Entity_v2 {
  public:
    virtual ~Entity_v2() = default;

    virtual int test() const { return 1; }
};

} // namespace dts

#endif // INCLUDE_ENTITY_V2_HPP
