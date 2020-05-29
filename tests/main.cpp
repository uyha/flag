#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <cstdint>
#include <flag.hpp>

using namespace river;

constexpr bool cehck_compile_error = true;

TEST_CASE("Operations on enum with std::uint8_t") {
  enum class Easy : std::uint8_t { _0 = 0b000, _1 = 0b001, _2 = 0b010, _3 = 0b011, _4 = 0b100 };

  SECTION("Flip operators") {
    CHECK(std::is_same_v<std::uint8_t, decltype(~Easy::_0)>);
    CHECK(~Easy::_0 == 0b1111'1111);
    CHECK(~Easy::_1 == 0b1111'1110);
    CHECK(~Easy::_2 == 0b1111'1101);
  }

  SECTION("Binary operators") {
    CHECK(std::is_same_v<std::uint8_t, decltype(Easy::_0 | Easy::_1)>);
    CHECK((Easy::_0 | Easy::_1) == 0b001);
    CHECK((Easy::_0 & Easy::_1) == 0b000);
    CHECK((Easy::_3 ^ Easy::_4) == 0b111);
  }

  SECTION("Chainning operations") {
    CHECK(std::is_same_v<std::uint8_t, decltype(Easy::_0 & Easy::_1 & Easy::_2)>);
    CHECK((Easy::_1 & Easy::_2 & Easy::_3) == 0b000);
    CHECK((Easy::_1 | Easy::_2 | Easy::_4) == 0b111);
    CHECK((Easy::_1 ^ Easy::_2 ^ Easy::_4) == 0b111);
  }

  SECTION("Getting bits") {
    CHECK(std::is_same_v<std::uint8_t, decltype(bit<0>(Easy::_1))>);
    CHECK(bit<0>(Easy::_1));
    CHECK(bit<1>(Easy::_3));

    CHECK_FALSE(bit<1>(Easy::_1));
    CHECK_FALSE(bit<2>(Easy::_3));
  }
}

TEST_CASE("Operations on enum with std::uint32_t") {
  enum class Easy : std::uint32_t { _0 = 0b000, _1 = 0b001, _2 = 0b010, _3 = 0b011, _4 = 0b100 };

  SECTION("Flip operators") {
    CHECK(std::is_same_v<std::uint32_t, decltype(~Easy::_0)>);
    CHECK(~Easy::_0 == 0b1111'1111'1111'1111'1111'1111'1111'1111);
    CHECK(~Easy::_1 == 0b1111'1111'1111'1111'1111'1111'1111'1110);
    CHECK(~Easy::_2 == 0b1111'1111'1111'1111'1111'1111'1111'1101);
  }

  SECTION("Binary operators") {
    CHECK(std::is_same_v<std::uint32_t, decltype(Easy::_0 | Easy::_1)>);
    CHECK((Easy::_0 | Easy::_1) == 0b001);
    CHECK((Easy::_0 & Easy::_1) == 0b000);
    CHECK((Easy::_3 ^ Easy::_4) == 0b111);
  }

  SECTION("Chainning operations") {
    CHECK(std::is_same_v<std::uint32_t, decltype(Easy::_0 & Easy::_1 & Easy::_2)>);
    CHECK((Easy::_1 & Easy::_2 & Easy::_3) == 0b000);
    CHECK((Easy::_1 | Easy::_2 | Easy::_4) == 0b111);
    CHECK((Easy::_1 ^ Easy::_2 ^ Easy::_4) == 0b111);
  }

  SECTION("Getting bits") {
    CHECK(std::is_same_v<std::uint32_t, decltype(bit<0>(Easy::_1))>);
    CHECK(bit<0>(Easy::_1));
    CHECK(bit<1>(Easy::_3));
    CHECK((bit<0>(Easy::_3) && bit<1>(Easy::_3)));

    CHECK_FALSE(bit<1>(Easy::_1));
    CHECK_FALSE(bit<8>(Easy::_1));
    CHECK_FALSE(bit<2>(Easy::_3));
  }
}