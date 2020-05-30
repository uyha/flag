#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <cstdint>
#include <flag.hpp>

using namespace river;

constexpr bool cehck_compile_error = true;

TEST_CASE("Operations on an enum flag") {
  enum class Enum : std::uint8_t { _0 = 0b000, _1 = 0b001, _2 = 0b010, _3 = 0b011, _4 = 0b100 };

  SECTION("Flip operators") {
    CHECK(std::is_same_v<std::uint8_t, decltype(~Enum::_0)>);
    CHECK(~Enum::_0 == 0b1111'1111);
    CHECK(~Enum::_1 == 0b1111'1110);
    CHECK(~Enum::_2 == 0b1111'1101);
  }

  SECTION("Binary operators") {
    CHECK(std::is_same_v<std::uint8_t, decltype(Enum::_0 | Enum::_1)>);
    CHECK((Enum::_0 | Enum::_1) == 0b001);
    CHECK((Enum::_0 & Enum::_1) == 0b000);
    CHECK((Enum::_3 ^ Enum::_4) == 0b111);
  }

  SECTION("Chainning operations") {
    CHECK(std::is_same_v<std::uint8_t, decltype(Enum::_0 & Enum::_1 & Enum::_2)>);
    CHECK((Enum::_1 & Enum::_2 & Enum::_3) == 0b000);
    CHECK((Enum::_1 | Enum::_2 | Enum::_4) == 0b111);
    CHECK((Enum::_1 ^ Enum::_2 ^ Enum::_4) == 0b111);
  }

  SECTION("Getting bits") {
    CHECK(std::is_same_v<std::uint8_t, decltype(bit<0>(Enum::_1))>);
    CHECK(bit<0>(Enum::_1));
    CHECK(bit<1>(Enum::_3));

    CHECK_FALSE(bit<1>(Enum::_1));
    CHECK_FALSE(bit<2>(Enum::_3));
  }
}

TEST_CASE("Operations on enum and literals") {
  enum class Enum : std::uint8_t { _0 = 0b000, _1 = 0b001, _2 = 0b010, _3 = 0b011, _4 = 0b100 };

  CHECK((Enum::_1 & 0b1111'1111) == 0b1);
}