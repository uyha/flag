#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <cstdint>
#include <flag.hpp>

using namespace river;

enum class Easy : std::uint8_t { _0 = 0b000, _1 = 0b001, _2 = 0b010, _3 = 0b011, _4 = 0b100 };

TEST_CASE("Operations on enum with std::uint8_t") {
  SECTION("Flip operators") {
    REQUIRE(~Easy::_0 == 0b1111'1111);
    REQUIRE(~Easy::_1 == 0b1111'1110);
    REQUIRE(~Easy::_2 == 0b1111'1101);
  }
  SECTION("Binary operators") {
    REQUIRE((Easy::_0 | Easy::_1) == 0b001);
    REQUIRE((Easy::_0 & Easy::_1) == 0b000);
    REQUIRE((Easy::_0 ^ Easy::_1) == 0b001);
  }

  SECTION("Channing operations") {
    REQUIRE((Easy::_0 & Easy::_1 & Easy::_2) == 0b000);
    REQUIRE((~Easy::_0 & Easy::_1 & Easy::_3) == 0b001);
    REQUIRE((Easy::_0 | Easy::_1 & Easy::_3) == 0b001);
  }
}
