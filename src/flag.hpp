#pragma once

#include <type_traits>

namespace river {
template <typename T>
concept Flag = std::is_enum_v<T> &&std::is_unsigned_v<std::underlying_type_t<T>>;
template <Flag T> constexpr auto underlying_value(T enum_value) {
  return static_cast<std::underlying_type_t<T>>(enum_value);
}

template <Flag T> constexpr auto operator~(T value) {
  return static_cast<std::underlying_type_t<T>>(~underlying_value(value));
}

template <Flag T> constexpr auto operator|(T lhs, T rhs) {
  return static_cast<std::underlying_type_t<T>>(underlying_value(lhs) | underlying_value(rhs));
}
template <Flag T> constexpr auto operator|(std::underlying_type_t<T> lhs, T rhs) {
  return static_cast<std::underlying_type_t<T>>(lhs | underlying_value(rhs));
}
template <Flag T> constexpr auto operator|(T lhs, std::underlying_type_t<T> rhs) {
  return static_cast<std::underlying_type_t<T>>(underlying_value(lhs) | rhs);
}

template <Flag T> constexpr auto operator&(T lhs, T rhs) {
  return static_cast<std::underlying_type_t<T>>(underlying_value(lhs) & underlying_value(rhs));
}
template <Flag T> constexpr auto operator&(std::underlying_type_t<T> lhs, T rhs) {
  return static_cast<std::underlying_type_t<T>>(lhs & underlying_value(rhs));
}
template <Flag T> constexpr auto operator&(T lhs, std::underlying_type_t<T> rhs) {
  return static_cast<std::underlying_type_t<T>>(underlying_value(lhs) & rhs);
}

template <Flag T> constexpr auto operator^(T lhs, T rhs) {
  return static_cast<std::underlying_type_t<T>>(underlying_value(lhs) ^ underlying_value(rhs));
}
template <Flag T> constexpr auto operator^(std::underlying_type_t<T> lhs, T rhs) {
  return static_cast<std::underlying_type_t<T>>(lhs ^ underlying_value(rhs));
}
template <Flag T> constexpr auto operator^(T lhs, std::underlying_type_t<T> rhs) {
  return static_cast<std::underlying_type_t<T>>(underlying_value(lhs) ^ rhs);
}
} // namespace river