#pragma once

#include <type_traits>

#define IS_FLAG(enum_name)                                                                         \
  template <>                                                                                      \
  constexpr bool ::river::is_flag_v<enum_name> = true;

namespace river {
template <typename T>
concept unsigned_enum = std::is_enum_v<T> &&std::is_unsigned_v<std::underlying_type_t<T>>;

template <unsigned_enum T>
constexpr bool is_flag_v = false;

template <typename T>
concept Flag = unsigned_enum<T> &&is_flag_v<T>;

template <Flag T>
constexpr auto underlying_value(T enum_value) {
  return static_cast<std::underlying_type_t<T>>(enum_value);
}

template <Flag T>
constexpr auto operator~(T value) {
  return static_cast<std::underlying_type_t<T>>(~underlying_value(value));
}

template <Flag T>
constexpr auto operator|(T lhs, T rhs) {
  return static_cast<std::underlying_type_t<T>>(underlying_value(lhs) | underlying_value(rhs));
}
template <Flag T>
constexpr auto operator|(std::underlying_type_t<T> lhs, T rhs) {
  return static_cast<std::underlying_type_t<T>>(lhs | underlying_value(rhs));
}
template <Flag T>
constexpr auto operator|(T lhs, std::underlying_type_t<T> rhs) {
  return static_cast<std::underlying_type_t<T>>(underlying_value(lhs) | rhs);
}

template <Flag T>
constexpr auto operator&(T lhs, T rhs) {
  return static_cast<std::underlying_type_t<T>>(underlying_value(lhs) & underlying_value(rhs));
}
template <Flag T>
constexpr auto operator&(std::underlying_type_t<T> lhs, T rhs) {
  return static_cast<std::underlying_type_t<T>>(lhs & underlying_value(rhs));
}
template <Flag T>
constexpr auto operator&(T lhs, std::underlying_type_t<T> rhs) {
  return static_cast<std::underlying_type_t<T>>(underlying_value(lhs) & rhs);
}

template <Flag T>
constexpr auto operator^(T lhs, T rhs) {
  return static_cast<std::underlying_type_t<T>>(underlying_value(lhs) ^ underlying_value(rhs));
}
template <Flag T>
constexpr auto operator^(std::underlying_type_t<T> lhs, T rhs) {
  return static_cast<std::underlying_type_t<T>>(lhs ^ underlying_value(rhs));
}
template <Flag T>
constexpr auto operator^(T lhs, std::underlying_type_t<T> rhs) {
  return static_cast<std::underlying_type_t<T>>(underlying_value(lhs) ^ rhs);
}

template <auto mask>
constexpr bool has(std::underlying_type_t<decltype(mask)> value) {
  return value & mask;
}
} // namespace river