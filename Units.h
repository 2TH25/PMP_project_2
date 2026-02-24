#ifndef UNITS_H
#define UNITS_H

#include <cstdint>
#include <ratio>

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
    Qty& operator+=(Qty<U, ROther> other);

    template<typename ROther>
    Qty& operator-=(Qty<U, ROther> other);

  };

  namespace details
  {
    template<class U, class R>
    double castTo1(Qty<U, R> q)
    {
      return q.value * (((double) R::num) / R::den);
    }
  } // namespace details

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

  using Mile                  = Qty<Metre, std::ratio<16093444, 10000>>;
  using Yard                  = Qty<Metre, std::ratio<91440000, 100000000>>;
  using Foot                  = Qty<Metre, std::ratio<32808400, 10000000>>;
  using Inch                  = Qty<Metre, std::ratio<39370094, 1000000>>;
  using Knot                  = Qty<Speed, std::ratio<19438400, 10000000>>;

  /*
   * Comparison operators
   */

  template<typename U, typename R1, typename R2>
  bool operator==(Qty<U, R1> q1, Qty<U, R2> q2)
  {
    return details::castTo1(q1) == details::castTo1(q2);
  };

  template<typename U, typename R1, typename R2>
  bool operator!=(Qty<U, R1> q1, Qty<U, R2> q2)
  {
    return details::castTo1(q1) != details::castTo1(q2);
  };

  template<typename U, typename R1, typename R2>
  bool operator<(Qty<U, R1> q1, Qty<U, R2> q2)
  {
    return details::castTo1(q1) < details::castTo1(q2);
  };

  template<typename U, typename R1, typename R2>
  bool operator<=(Qty<U, R1> q1, Qty<U, R2> q2)
  {
    return details::castTo1(q1) <= details::castTo1(q2);
  };

  template<typename U, typename R1, typename R2>
  bool operator>(Qty<U, R1> q1, Qty<U, R2> q2)
  {
    return details::castTo1(q1) > details::castTo1(q2);
  };

  template<typename U, typename R1, typename R2>
  bool operator>=(Qty<U, R1> q1, Qty<U, R2> q2)
  {
    return details::castTo1(q1) >= details::castTo1(q2);
  };

  #ifdef test

  /*
   * Arithmetic operators
   */

  template<typename U, typename R1, typename R2>
  /* implementation defined */ operator+(Qty<U, R1> q1, Qty<U, R2> q2);

  template<typename U, typename R1, typename R2>
  /* implementation defined */ operator-(Qty<U, R1> q1, Qty<U, R2> q2);

  template<typename U1, typename R1, typename U2, typename R2>
  /* implementation defined */ operator*(Qty<U1, R1> q1, Qty<U2, R2> q2);

  template<typename U1, typename R1, typename U2, typename R2>
  /* implementation defined */ operator/(Qty<U1, R1> q1, Qty<U2, R2> q2);

  #endif

  /*
   * Cast function between two quantities
   */
  template<typename ResQty, typename U, typename R>
  ResQty qtyCast(Qty<U, R> quantity);

  namespace literals {

    /*
     * Some user-defined literals
     */

    inline Length operator ""_metres(unsigned long long int val)
    {
      return val;
    };
    inline Mass operator ""_kilograms(unsigned long long int val)
    {
      return val;
    };
    inline Time operator ""_seconds(unsigned long long int val)
    {
      return val;
    };
    inline Current operator ""_amperes(unsigned long long int val)
    {
      return val;
    };
    inline Temperature operator ""_kelvins(unsigned long long int val)
    {
      return val;
    };
    inline Amount operator ""_moles(unsigned long long int val)
    {
      return val;
    };
    inline LuminousIntensity operator ""_candelas(unsigned long long int val)
    {
      return val;
    };
    inline Qty<Kelvin, std::ratio<1, 100>> operator ""_celsius(unsigned long long int val)
    {
      return ((val * 100) - 27315);
    };

  }

}

#endif // UNITS_H
