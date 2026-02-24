#include "Units.h"

#include <iostream>

#include <gtest/gtest.h>

using namespace phy;

template<typename  U>
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

template<typename U_expected, typename R_expected = std::ratio<1>, typename U, typename R>
void test_qty(const Qty<U, R> &q, intmax_t value)
{
  EXPECT_EQ(q.value, value);

  EXPECT_TRUE((std::is_same_v<U, U_expected>));
  EXPECT_TRUE((std::is_same_v<R, R_expected>));
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

TEST(TP2_qty, basic_quantites) {
  Length q_metre;
  test_qty<Metre>(q_metre, 0);

  Length q_metre_value(42);
  test_qty<Metre>(q_metre_value, 42);

  Mass q_mass;
  test_qty<Kilogram>(q_mass, 0);

  Mass q_mass_value(42);
  test_qty<Kilogram>(q_mass_value, 42);

  Time q_time;
  test_qty<Second>(q_time, 0);

  Time q_time_value(42);
  test_qty<Second>(q_time_value, 42);

  Current q_current;
  test_qty<Ampere>(q_current, 0);

  Current q_current_value(42);
  test_qty<Ampere>(q_current_value, 42);

  Temperature q_temperature;
  test_qty<Kelvin>(q_temperature, 0);

  Temperature q_temperature_value(42);
  test_qty<Kelvin>(q_temperature_value, 42);

  Amount q_amount;
  test_qty<Mole>(q_amount, 0);

  Amount q_amount_value(42);
  test_qty<Mole>(q_amount_value, 42);

  LuminousIntensity q_intensity;
  test_qty<Candela>(q_intensity, 0);

  LuminousIntensity q_intensity_value(42);
  test_qty<Candela>(q_intensity_value, 42);
}

// TODO : enlever
TEST(test, test) {
  Qty<Metre, std::milli> test(999);
  auto test2 = qtyCast<Length>(test);

  std::cout << details::castTo1(test2) << " " << test2.value << "\n";
}

int main(int argc, char* argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
