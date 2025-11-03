#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <utility>

namespace dts {

class Vector final {
  public:
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using value_type = int;
    using reference = value_type &;
    using const_reference = const value_type &;
    using pointer = value_type *;
    using const_pointer = const value_type *;
    using iterator = pointer;
    using const_iterator = const_pointer;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    Vector() noexcept : data_{nullptr}, size_{0}, capacity_{0} {}

    Vector(std::initializer_list<int> list)
        : data_{list.size() ? new int[list.size()]{} : nullptr}, size_{list.size()},
          capacity_{list.size()} {
        std::copy(list.begin(), list.end(), data_);
    }

    Vector(const Vector &other)
        : data_{other.capacity_ ? new int[other.capacity_] : nullptr}, size_{other.size_},
          capacity_{other.capacity_} {
        std::copy_n(other.data_, other.size_, data_);
    }

    Vector(Vector &&other) noexcept
        : data_{std::exchange(other.data_, nullptr)}, size_{std::exchange(other.size_, 0)},
          capacity_{std::exchange(other.capacity_, 0)} {}

    Vector &operator=(const Vector &rhs) {
        auto copy = rhs;
        swap(copy);
        return *this;
    }

    Vector &operator=(Vector &&rhs) noexcept {
        swap(rhs);
        return *this;
    }

    ~Vector() { delete[] data_; }

    bool empty() const noexcept { return size_ == 0; }
    size_type size() const noexcept { return size_; }
    size_type capacity() const noexcept { return capacity_; }

    iterator begin() { return data_; }
    const_iterator begin() const { return data_; }
    const_iterator cbegin() const { return begin(); }

    iterator end() { return data_ + size_; }
    const_iterator end() const { return data_ + size_; }
    const_iterator cend() const { return end(); }

    reverse_iterator rbegin() { return reverse_iterator{end()}; }
    const_reverse_iterator rbegin() const { return const_reverse_iterator{end()}; }
    const_reverse_iterator crbegin() const { return rbegin(); }

    reverse_iterator rend() { return reverse_iterator{begin()}; }
    const_reverse_iterator rend() const { return const_reverse_iterator{begin()}; }
    const_reverse_iterator crend() const { return rend(); }

    void swap(Vector &other) noexcept {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
    }

    friend void swap(Vector &lhs, Vector &rhs) noexcept(noexcept(lhs.swap(rhs))) { lhs.swap(rhs); }

    void push_back(int value) {
        if (size_ < capacity_) {
            data_[size_] = value;
        } else {
            constexpr size_type kDefaultInitCapacity = 10;
            const auto new_capacity = std::max(kDefaultInitCapacity, capacity_ * 2);
            auto *new_data = new int[new_capacity];
            std::copy_n(data_, size_, new_data);
            new_data[size_] = value;

            delete[] data_;
            data_ = new_data;
            capacity_ = new_capacity;
        }

        ++size_;
    }

    void clear() noexcept {
        delete[] data_;
        size_ = 0;
        capacity_ = 0;
    }

  private:
    int *data_;
    size_type size_;
    size_type capacity_;
};

} // namespace dts
