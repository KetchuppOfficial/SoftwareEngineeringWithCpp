#include <cstddef>
#include <cstdio>
#include <new>
#include <print>

template <typename D>
class Entity {
  public:
    // use std::puts() because operators are non-throwing

    static void *operator new(std::size_t size, const std::nothrow_t &tag) {
        std::puts("Entity::operator new");
        return ::operator new(size, tag);
    }

    static void *operator new[](std::size_t size, const std::nothrow_t &tag) {
        std::puts("Entity::operator new[]");
        return ::operator new[](size, tag);
    }

    static void operator delete(void *x) {
        std::puts("Entity::operator delete");
        ::operator delete(x);
    }

    static void operator delete[](void *x) {
        std::puts("Entity::operator delete[]");
        ::operator delete[](x);
    }

  protected:
    Entity() = default;
};

class Client : private Entity<Client> {
  public:
    Client() { std::println("Client::Client"); }
    ~Client() { std::println("Client::~Client"); }

    using Entity<Client>::operator new;
    using Entity<Client>::operator new[];
    using Entity<Client>::operator delete;
    using Entity<Client>::operator delete[];
};

int main() {
    delete new (std::nothrow) Client;
    std::println("-----------------------");
    delete[] new (std::nothrow) Client[3];
}
