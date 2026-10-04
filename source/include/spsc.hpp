#pragma once

#include <memory>

template <typename T, typename Alloc = std::allocator<T>> class SPSC : private Alloc {
private:
  T *ring_;
  std::size_t capacity_;
  std::size_t pushCursor_{};
  std::size_t popCursor_{};

public:
  explicit SPSC(std::size_t capacity, Alloc const &alloc = Alloc{})
      : Alloc{alloc}, capacity_{capacity},
        ring_{std::allocator_traits<Alloc>::allocate(*this, capacity)} {};

  ~SPSC() {
    while (!empty()) {
      ring_[popCursor_ % capacity_].~T();
      ++popCursor_;
    }
    std::allocator_traits<Alloc>::deallocate(*this, ring_, capacity_);
  };

  auto capacity() { return capacity_; }
  auto size() { return pushCursor_ - popCursor_; }
  auto empty() { return size() == 0; }
  auto full() { return size() == capacity(); }

  bool push(T const &value) {
    if (full())
      return false;

    new (&ring_[pushCursor_ % capacity_]) T(value);
    ++pushCursor_;
    return true;
  };

  bool pop(T &value) {
    if (empty())
      return false;

    value = ring_[popCursor_ % capacity_];
    ++popCursor_;
    return true;
  };
};
