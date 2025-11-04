#ifndef INCLUDE_ENTITY_V1_HPP
#define INCLUDE_ENTITY_V1_HPP

namespace dts {

class Entity_v1 {
  public:
    virtual ~Entity_v1() = default;

    virtual int test() const { return 0; }
};

} // namespace dts

#endif // INCLUDE_ENTITY_V1_HPP
