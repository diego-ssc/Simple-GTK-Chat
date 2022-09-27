#ifndef ENUM_CLASS_HASH
#define ENUM_CLASS_HASH

struct EnumClassHash {
  template <typename T>
  std::size_t operator()(T t) const {
    return static_cast<std::size_t>(t);
  }
};

#endif
