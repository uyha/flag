#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <cstdint>
#include <river/flag.hpp>

enum class Enum : std::uint8_t { _0 = 0b000, _1 = 0b001, _2 = 0b010, _3 = 0b011, _4 = 0b100 };
IS_FLAG_ENUM(Enum);

TEST_CASE("Operations on an enum flag") {
  SECTION("Flip operators") {
    using river::flags::operator~;
    CHECK(std::is_same_v<std::uint8_t, decltype(~Enum::_0)>);
    CHECK(~Enum::_0 == 0b1111'1111);
    CHECK(~Enum::_1 == 0b1111'1110);
    CHECK(~Enum::_2 == 0b1111'1101);
  }

  SECTION("Binary operators") {
    using river::flags::operator|, river::flags::operator&, river::flags::operator^;
    CHECK(std::is_same_v<std::uint8_t, decltype(Enum::_0 | Enum::_1)>);
    CHECK((Enum::_0 | Enum::_1) == 0b001);
    CHECK((Enum::_0 & Enum::_1) == 0b000);
    CHECK((Enum::_3 ^ Enum::_4) == 0b111);
  }

  SECTION("Chaining operations") {
    using river::flags::operator|, river::flags::operator&, river::flags::operator^;
    CHECK(std::is_same_v<std::uint8_t, decltype(Enum::_0 & Enum::_1 & Enum::_2)>);
    CHECK((Enum::_1 & Enum::_2 & Enum::_3) == 0b000);
    CHECK((Enum::_1 | Enum::_2 | Enum::_4) == 0b111);
    CHECK((Enum::_1 ^ Enum::_2 ^ Enum::_4) == 0b111);
  }

  SECTION("Getting bits") {
    using river::flags::has;
    CHECK(has<Enum::_1>(0b1111));
    CHECK(has<Enum::_4>(0b0100));
    CHECK_FALSE(has<Enum::_1>(0b0));
    CHECK_FALSE(has<Enum::_4>(0b1000));
  }
}

TEST_CASE("Operations on enum and literals") {
  using river::flags::operator&;
  CHECK((Enum::_1 & 0b1111'1111) == 0b1);
}

TEST_CASE("Check has function") {
  using river::flags::has;
  std::uint8_t value = 0b1u;
  CHECK(has<Enum::_1>(value));
  CHECK_FALSE(has<Enum::_3>(value));
}

TEST_CASE("Update value") {
  using namespace river::flags;
  std::uint8_t value = 0u;
  value |= Enum::_1;
  CHECK(has<Enum::_1>(value));
  CHECK_FALSE(has<Enum::_3>(value));

  value |= Enum::_3;
  CHECK(has<Enum::_1>(value));
  CHECK(has<Enum::_3>(value));

  value &= Enum::_1;
  CHECK(has<Enum::_1>(value));
  CHECK_FALSE(has<Enum::_3>(value));

  value ^= Enum::_3;
  CHECK_FALSE(has<Enum::_1>(value));
  CHECK(has<Enum::_2>(value));
  CHECK_FALSE(has<Enum::_3>(value));
}