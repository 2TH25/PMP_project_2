#include "Units.h"

#include <iostream>

#include <gtest/gtest.h>

using namespace phy;
using namespace phy::literals;

template<class U, class R>
double castTo1(Qty<U, R> q)
{
  return q.value * static_cast<double>(R::num) / R::den;
}

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

template<typename U_expected, typename R_expected = std::ratio<1>, typename U, typename R>
void test_qty(const Qty<U, R> &q, const intmax_t value)
{
  EXPECT_EQ(q.value, value);

  EXPECT_TRUE((std::is_same_v<U, U_expected>));
  EXPECT_TRUE((std::is_same_v<R, R_expected>));
}

template<typename U>
void test_comparison()
{
  Qty<U, std::deci> lower(10);
  Qty<U, std::milli> same(10000);
  Qty<U> normal(10);
  Qty<U, std::deca> greater(10);

  EXPECT_LT(lower, normal);
  EXPECT_LT(lower, same);
  EXPECT_LE(lower, normal);
  EXPECT_LE(lower, same);
  EXPECT_LE(lower, lower);
  EXPECT_EQ(lower, lower);
  EXPECT_LE(same, normal);
  EXPECT_EQ(same, normal);
  EXPECT_GE(same, normal);
  EXPECT_GT(greater, normal);
  EXPECT_GT(greater, same);
  EXPECT_GE(greater, normal);
  EXPECT_GE(greater, normal);
  EXPECT_GE(greater, greater);
  EXPECT_EQ(greater, greater);
}

TEST(TP2_unit, basic_units)
{
  test_unit<Metre>(1, 0, 0, 0, 0, 0, 0);
  test_unit<Kilogram>(0, 1, 0, 0, 0, 0, 0);
  test_unit<Second>(0, 0, 1, 0, 0, 0, 0);
  test_unit<Ampere>(0, 0, 0, 1, 0, 0, 0);
  test_unit<Kelvin>(0, 0, 0, 0, 1, 0, 0);
  test_unit<Mole>(0, 0, 0, 0, 0, 1, 0);
  test_unit<Candela>(0, 0, 0, 0, 0, 0, 1);
  test_unit<Radian>(0, 0, 0, 0, 0, 0, 0);
}

TEST(TP2_unit, derived_units)
{
  test_unit<Volt>(2, 1, -3, -1, 0, 0, 0);
  test_unit<Ohm>(2, 1, -3, -2, 0, 0, 0);
  test_unit<Watt>(2, 1, -3, 0, 0, 0, 0);
  test_unit<Hertz>(0, 0, -1, 0, 0, 0, 0);
  test_unit<Pascal>(-1, 1, -2, 0, 0, 0, 0);
  test_unit<Speed>(1, 0, -1, 0, 0, 0, 0);
  test_unit<Newton>(1, 1, -2, 0, 0, 0, 0);
}

TEST(TP2_qty, basic_quantites)
{
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

TEST(TP2_qty, derived_quantites)
{
  Frequency q_frequency;
  test_qty<Hertz>(q_frequency, 0);

  Frequency q_frequency_value(42);
  test_qty<Hertz>(q_frequency_value, 42);

  Force q_force;
  test_qty<Newton>(q_force, 0);

  Force q_force_value(42);
  test_qty<Newton>(q_force_value, 42);

  MeterSecond q_meter_second;
  test_qty<Speed>(q_meter_second, 0);

  MeterSecond q_meter_second_value(42);
  test_qty<Speed>(q_meter_second_value, 42);

  ElectricPotential q_potential;
  test_qty<Volt>(q_potential, 0);

  ElectricPotential q_potential_value(42);
  test_qty<Volt>(q_potential_value, 42);

  ElectricalResistance q_resistance;
  test_qty<Ohm>(q_resistance, 0);

  ElectricalResistance q_resistance_value(42);
  test_qty<Ohm>(q_resistance_value, 42);

  Power q_power;
  test_qty<Watt>(q_power, 0);

  Power q_power_value(42);
  test_qty<Watt>(q_power_value, 42);

  Pressure q_pressure;
  test_qty<Pascal>(q_pressure, 0);

  Pressure q_pressure_value(42);
  test_qty<Pascal>(q_pressure_value, 42);
}

TEST(TP2_qty, weird_quantites)
{
  Mile q_mile;
  test_qty<Metre, std::ratio<16093444, 10000>>(q_mile, 0);

  Mile q_mile_value(42);
  test_qty<Metre, std::ratio<16093444, 10000>>(q_mile_value, 42);

  Yard q_yard;
  test_qty<Metre, std::ratio<91440000, 100000000>>(q_yard, 0);

  Yard q_yard_value(42);
  test_qty<Metre, std::ratio<91440000, 100000000>>(q_yard_value, 42);

  Foot q_foot;
  test_qty<Metre, std::ratio<32808400, 10000000>>(q_foot, 0);

  Foot q_foot_value(42);
  test_qty<Metre, std::ratio<32808400, 10000000>>(q_foot_value, 42);

  Inch q_inch;
  test_qty<Metre, std::ratio<39370094, 1000000>>(q_inch, 0);

  Inch q_inch_value(42);
  test_qty<Metre, std::ratio<39370094, 1000000>>(q_inch_value, 42);

  Knot q_knot;
  test_qty<Speed, std::ratio<19438400, 10000000>>(q_knot, 0);

  Knot q_knot_value(42);
  test_qty<Speed, std::ratio<19438400, 10000000>>(q_knot_value, 42);
}

TEST(TP2_comparison, basic_comparison)
{
  test_comparison<Metre>();
  test_comparison<Kilogram>();
  test_comparison<Second>();
  test_comparison<Ampere>();
  test_comparison<Kelvin>();
  test_comparison<Mole>();
  test_comparison<Candela>();
}

TEST(TP2_literals, basic_literals)
{
  EXPECT_EQ(42_metres, Length(42));
  EXPECT_EQ(42_kilograms, Mass(42));
  EXPECT_EQ(42_seconds, Time(42));
  EXPECT_EQ(42_amperes, Current(42));
  EXPECT_EQ(42_kelvins, Temperature(42));
  EXPECT_EQ(42_moles, Amount(42));
  EXPECT_EQ(42_candelas, LuminousIntensity(42));
  Qty<Kelvin, std::ratio<1, 100>> kelvin(31515);
  EXPECT_EQ(42_celsius, kelvin);
}

TEST(TP2_qtyCast, notSameU)
{
  Qty<Second, std::deca> s(10);
  EXPECT_THROW(qtyCast<Length>(s);, std::runtime_error);
}

// TODO : enlever
TEST(test, test) {
  Qty<Metre> m(7);
  Qty<Metre, std::milli> mm(10);
  m += mm;
  std::cout << castTo1(m) << "\n";
  // using namespace phy::literals;
  // Qty<Metre, std::deci> test(25);
  // auto res_add = 10_metres + test;
  // std::cout << res_add.value << "\n";

  // auto res_sub = 10_metres - test;
  // std::cout << res_sub.value << "\n";

  // auto res_mult = 10_metres * test;
  // std::cout << res_mult.value << "\n";

  // auto res_div = 10_metres / test;
  // std::cout << res_div.value << "\n";

  // auto res_mult_test = 2000_metres * 3000_metres;
  // std::cout << res_mult_test.value << "\n";


  // auto test_mult_1 = Qty<Metre>(5);
  // auto test_mult_2 = Qty<Second>(3);
  // auto res_mult_test_ratio = test_mult_1 / test_mult_2;
  // std::cout << res_mult_test_ratio.value << "\n";
  // auto res_1 = details::castTo1(res_mult_test_ratio);
  // std::cout << res_1 << "\n";

  // Qty<Metre> test_add_operator_1(5);
  // test_add_operator_1 += test_add_operator_1;
  // std::cout << test_add_operator_1.value << "\n";
  // test_add_operator_1 -= test_add_operator_1;
  // std::cout << test_add_operator_1.value << "\n";
}

int main(int argc, char* argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
