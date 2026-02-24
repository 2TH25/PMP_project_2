#include "Units.h"

#include <iostream>

#include <gtest/gtest.h>

using namespace phy;

template<typename U>
void test_unit(const int m, const int kg, const int s, const int A, const int K, const int mol, const int cd)
{
  EXPECT_EQ(U::metre, m);
  EXPECT_EQ(U::kilogram, kg);
  EXPECT_EQ(U::second, s);
  EXPECT_EQ(U::ampere, A);
  EXPECT_EQ(U::kelvin, K);
  EXPECT_EQ(U::mole, mol);
  EXPECT_EQ(U::candela, cd);
}

TEST(TP2_unit, basic_units) {
  test_unit<Metre>(1, 0, 0, 0, 0, 0, 0);
  test_unit<Kilogram>(0, 1, 0, 0, 0, 0, 0);
  test_unit<Second>(0, 0, 1, 0, 0, 0, 0);
  test_unit<Ampere>(0, 0, 0, 1, 0, 0, 0);
  test_unit<Kelvin>(0, 0, 0, 0, 1, 0, 0);
  test_unit<Mole>(0, 0, 0, 0, 0, 1, 0);
  test_unit<Candela>(0, 0, 0, 0, 0, 0, 1);
  test_unit<Radian>(0, 0, 0, 0, 0, 0, 0);
}

TEST(TP2_unit, derived_units) {
  test_unit<Volt>(2, 1, -3, -1, 0, 0, 0);
  test_unit<Ohm>(2, 1, -3, -2, 0, 0, 0);
  test_unit<Watt>(2, 1, -3, 0, 0, 0, 0);
  test_unit<Hertz>(0, 0, -1, 0, 0, 0, 0);
  test_unit<Pascal>(-1, 1, -2, 0, 0, 0, 0);
  test_unit<Speed>(1, 0, -1, 0, 0, 0, 0);
  test_unit<Newton>(1, 1, -2, 0, 0, 0, 0);
}

int main(int argc, char* argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
