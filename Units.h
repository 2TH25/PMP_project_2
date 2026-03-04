#ifndef UNITS_H
#define UNITS_H

#include <cstdint>
#include <ratio>
#include <stdexcept>
#include <iostream>
#include <iomanip>

namespace phy {

  /*
   * A unit defined in terms of the base units
   */
  template<int Metre, int Kilogram, int Second, int Ampere, int Kelvin, int Mole, int Candela>
  struct Unit {
    static constexpr int metre = Metre;
    static constexpr int kilogram = Kilogram;
    static constexpr int second = Second;
    static constexpr int ampere = Ampere;
    static constexpr int kelvin = Kelvin;
    static constexpr int mole = Mole;
    static constexpr int candela = Candela;
  };

  /*
   * Various type aliases
   */

  using Metre               = Unit<1, 0, 0, 0, 0, 0, 0>;
  using Kilogram            = Unit<0, 1, 0, 0, 0, 0, 0>;
  using Second              = Unit<0, 0, 1, 0, 0, 0, 0>;
  using Ampere              = Unit<0, 0, 0, 1, 0, 0, 0>;
  using Kelvin              = Unit<0, 0, 0, 0, 1, 0, 0>;
  using Mole                = Unit<0, 0, 0, 0, 0, 1, 0>;
  using Candela             = Unit<0, 0, 0, 0, 0, 0, 1>;
  using Radian              = Unit<0, 0, 0, 0, 0, 0, 0>;

  using Volt                = Unit<2, 1, -3, -1, 0, 0, 0>;
  using Ohm                 = Unit<2, 1, -3, -2, 0, 0, 0>;
  using Watt                = Unit<2, 1, -3, 0, 0, 0, 0>;
  using Hertz               = Unit<0, 0, -1, 0, 0, 0, 0>;
  using Pascal              = Unit<-1, 1, -2, 0, 0, 0, 0>;
  using Speed               = Unit<1, 0, -1, 0, 0, 0, 0>;
  using Newton              = Unit<1, 1, -2, 0, 0, 0, 0>;

  namespace details
  {
    template<class U1, class U2>
    using multUnit = Unit<
      U1::metre + U2::metre,
      U1::kilogram + U2::kilogram,
      U1::second + U2::second,
      U1::ampere + U2::ampere,
      U1::kelvin + U2::kelvin,
      U1::mole + U2::mole,
      U1::candela + U2::candela
    >;

    template<class U1, class U2>
    using divUnit = Unit<
      U1::metre - U2::metre,
      U1::kilogram - U2::kilogram,
      U1::second - U2::second,
      U1::ampere - U2::ampere,
      U1::kelvin - U2::kelvin,
      U1::mole - U2::mole,
      U1::candela - U2::candela
    >;
  } // namespace details

  /*
   * A quantity is a value associated with a unit and a ratio
   */
  template<class U, class R = std::ratio<1>>
  struct Qty {
    using Unit = U;
    using Ratio = R;

    intmax_t value;

    Qty() { value = 0; };
    Qty(intmax_t v) { value = v; };

    template<typename ROther>
    Qty& operator+=(Qty<U, ROther> other) {
      value += (other.value * ROther::num * R::den) / (ROther::den * R::num);
      return *this;
    }

    template<typename ROther>
    Qty& operator-=(Qty<U, ROther> other)
    {
      value -= (other.value * ROther::num * R::den) / (ROther::den * R::num);
      return *this;
    }

  };

  /*
   * Various quantities
   */

  using Length                = Qty<Metre>;
  using Mass                  = Qty<Kilogram>;
  using Time                  = Qty<Second>;
  using Current               = Qty<Ampere>;
  using Temperature           = Qty<Kelvin>;
  using Amount                = Qty<Mole>;
  using LuminousIntensity     = Qty<Candela>;

  using Frequency             = Qty<Hertz>;
  using Force                 = Qty<Newton>;
  using MeterSecond           = Qty<Speed>;
  using ElectricPotential     = Qty<Volt>;
  using ElectricalResistance  = Qty<Ohm>;
  using Power                 = Qty<Watt>;
  using Pressure              = Qty<Pascal>;

  /*
   * Some weird quantities
   */

  using Mile                  = Qty<Metre, std::ratio<16093440, 10000>>;
  using Yard                  = Qty<Metre, std::ratio<91440000, 100000000>>;
  using Foot                  = Qty<Metre, std::ratio<30480000, 100000000>>;
  using Inch                  = Qty<Metre, std::ratio<25400000, 1000000000>>;
  using Knot                  = Qty<Speed, std::ratio<51444444, 100000000>>;

  /*
   * Cast function between two quantities
   */
  template<typename ResQty, typename U, typename R>
  ResQty qtyCast(Qty<U, R> quantity)
  {
    if (!std::is_same_v<typename ResQty::Unit, U>) throw std::runtime_error("Not same Units");
    return (quantity.value * R::num * ResQty::Ratio::den) / (R::den * ResQty::Ratio::num);
  };

  /*
   * Comparison operators
   */

  template<typename U, typename R1, typename R2>
  bool operator==(Qty<U, R1> q1, Qty<U, R2> q2)
  {
    if constexpr (std::ratio_less_v<R1, R2>)
      return q1.value == qtyCast<Qty<U, R1>>(q2).value;

    return qtyCast<Qty<U, R2>>(q1).value == q2.value;
  };

  template<typename U, typename R1, typename R2>
  bool operator!=(Qty<U, R1> q1, Qty<U, R2> q2)
  {
    if constexpr (std::ratio_less_v<R1, R2>)
      return q1.value != qtyCast<Qty<U, R1>>(q2).value;

    return qtyCast<Qty<U, R2>>(q1).value != q2.value;
  };

  template<typename U, typename R1, typename R2>
  bool operator<(Qty<U, R1> q1, Qty<U, R2> q2)
  {
    if constexpr (std::ratio_less_v<R1, R2>)
      return q1.value < qtyCast<Qty<U, R1>>(q2).value;

    return qtyCast<Qty<U, R2>>(q1).value < q2.value;
  };

  template<typename U, typename R1, typename R2>
  bool operator<=(Qty<U, R1> q1, Qty<U, R2> q2)
  {
    if constexpr (std::ratio_less_v<R1, R2>)
      return q1.value <= qtyCast<Qty<U, R1>>(q2).value;

    return qtyCast<Qty<U, R2>>(q1).value <= q2.value;
  };

  template<typename U, typename R1, typename R2>
  bool operator>(Qty<U, R1> q1, Qty<U, R2> q2)
  {
    if constexpr (std::ratio_less_v<R1, R2>)
      return q1.value > qtyCast<Qty<U, R1>>(q2).value;

    return qtyCast<Qty<U, R2>>(q1).value > q2.value;
  };

  template<typename U, typename R1, typename R2>
  bool operator>=(Qty<U, R1> q1, Qty<U, R2> q2)
  {
    if constexpr (std::ratio_less_v<R1, R2>)
      return q1.value >= qtyCast<Qty<U, R1>>(q2).value;
      
    return qtyCast<Qty<U, R2>>(q1).value >= q2.value;
  };

  /*
   * Arithmetic operators
   */

  template<typename U, typename R1, typename R2>
  std::conditional_t<std::ratio_less_v<R1, R2>, Qty<U, R1>, Qty<U, R2>> operator+(Qty<U, R1> q1, Qty<U, R2> q2)
  {
    if constexpr (std::ratio_less_v<R1, R2>)
    {
      Qty<U, R1> res(q1.value + qtyCast<Qty<U, R1>>(q2).value);
      return res;
    }
    Qty<U, R2> res(q2.value + qtyCast<Qty<U, R2>>(q1).value);
    return res;
  }

  template<typename U, typename R1, typename R2>
  std::conditional_t<std::ratio_less_v<R1, R2>, Qty<U, R1>, Qty<U, R2>> operator-(Qty<U, R1> q1, Qty<U, R2> q2)
  {
    if constexpr (std::ratio_less_v<R1, R2>)
      return {q1.value - qtyCast<Qty<U, R1>>(q2).value};

    return {qtyCast<Qty<U, R2>>(q1).value - q2.value};
  }

  template<typename U1, typename R1, typename U2, typename R2>
  Qty<details::multUnit<U1, U2>, std::conditional_t<std::ratio_less_v<R1, R2>, std::ratio_divide<R1, R2>, std::ratio_divide<R2, R1>>> operator*(Qty<U1, R1> q1, Qty<U2, R2> q2)
  {
    return {q1.value * q2.value};
  }

  template<typename U1, typename R1, typename U2, typename R2>
  Qty<details::divUnit<U1, U2>, std::ratio<1, R1::den * R2::num>> operator/(Qty<U1, R1> q1, Qty<U2, R2> q2)
  {
    // if constexpr (std::ratio_less_equal_v<R1, R2>)
    //   return {q1.value / q2.value};

    // return {q2.value / q1.value};

    return (q1.value * R1::num * R2::den) / q2.value;
  }

  namespace literals {

    /*
     * Some user-defined literals
     */

    inline Length operator ""_metres(unsigned long long int val)
    {
      return {static_cast<intmax_t>(val)};
    };
    inline Mass operator ""_kilograms(unsigned long long int val)
    {
      return {static_cast<intmax_t>(val)};
    };
    inline Time operator ""_seconds(unsigned long long int val)
    {
      return {static_cast<intmax_t>(val)};
    };
    inline Current operator ""_amperes(unsigned long long int val)
    {
      return {static_cast<intmax_t>(val)};
    };
    inline Temperature operator ""_kelvins(unsigned long long int val)
    {
      return {static_cast<intmax_t>(val)};
    };
    inline Amount operator ""_moles(unsigned long long int val)
    {
      return {static_cast<intmax_t>(val)};
    };
    inline LuminousIntensity operator ""_candelas(unsigned long long int val)
    {
      return {static_cast<intmax_t>(val)};
    };
    inline Qty<Kelvin, std::ratio<1, 100>> operator ""_celsius(unsigned long long int val)
    {
      return {static_cast<intmax_t>(val * 100 + 27315)};
    };

  }

}

#endif // UNITS_H
