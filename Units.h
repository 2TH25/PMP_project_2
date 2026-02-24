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

  using Metre               = Unit</* implementation defined */>;
  using Kilogram            = Unit</* implementation defined */>;
  using Second              = Unit</* implementation defined */>;
  using Ampere              = Unit</* implementation defined */>;
  using Kelvin              = Unit</* implementation defined */>;
  using Mole                = Unit</* implementation defined */>;
  using Candela             = Unit</* implementation defined */>;
  using Radian              = Unit</* implementation defined */>;

  using Volt                = Unit</* implementation defined */>;
  using Ohm                 = Unit</* implementation defined */>;
  using Watt                = Unit</* implementation defined */>;
  using Hertz               = Unit</* implementation defined */>;
  using Pascal              = Unit</* implementation defined */>;
  using Speed               = Unit</* implementation defined */>;
  using Newton              = Unit</* implementation defined */>;

  /*
   * A quantity is a value associated with a unit and a ratio
   */
  template<class U, class R = std::ratio<1>>
  struct Qty {
    using Unit = U;
    using Ratio = R;

    intmax_t value;

    Qty();
    Qty(intmax_t v);

    template<typename ROther>
    Qty& operator+=(Qty<U, ROther> other);

    template<typename ROther>
    Qty& operator-=(Qty<U, ROther> other);

  };

  /*
   * Various quantities
   */

  using Length                = Qty</* implementation defined */>;
  using Mass                  = Qty</* implementation defined */>;
  using Time                  = Qty</* implementation defined */>;
  using Current               = Qty</* implementation defined */>;
  using Temperature           = Qty</* implementation defined */>;
  using Amount                = Qty</* implementation defined */>;
  using LuminousIntensity     = Qty</* implementation defined */>;

  using Frequency             = Qty</* implementation defined */>;
  using Force                 = Qty</* implementation defined */>;
  using MeterSecond           = Qty</* implementation defined */>;
  using ElectricPotential     = Qty</* implementation defined */>;
  using ElectricalResistance  = Qty</* implementation defined */>;
  using Power                 = Qty</* implementation defined */>;
  using Pressure              = Qty</* implementation defined */>;

  /*
   * Some weird quantities
   */

  using Mile                  = Qty</* implementation defined */>;
  using Yard                  = Qty</* implementation defined */>;
  using Foot                  = Qty</* implementation defined */>;
  using Inch                  = Qty</* implementation defined */>;
  using Knot                  = Qty</* implementation defined */>;

  /*
   * Comparison operators
   */

  template<typename U, typename R1, typename R2>
  bool operator==(Qty<U, R1> q1, Qty<U, R2> q2);

  template<typename U, typename R1, typename R2>
  bool operator!=(Qty<U, R1> q1, Qty<U, R2> q2);

  template<typename U, typename R1, typename R2>
  bool operator<(Qty<U, R1> q1, Qty<U, R2> q2);

  template<typename U, typename R1, typename R2>
  bool operator<=(Qty<U, R1> q1, Qty<U, R2> q2);

  template<typename U, typename R1, typename R2>
  bool operator>(Qty<U, R1> q1, Qty<U, R2> q2);

  template<typename U, typename R1, typename R2>
  bool operator>=(Qty<U, R1> q1, Qty<U, R2> q2);

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


  /*
   * Cast function between two quantities
   */
  template<typename ResQty, typename U, typename R>
  ResQty qtyCast(Qty<U,R>);

  namespace literals {

    /*
     * Some user-defined literals
     */

    inline Length operator ""_metres(unsigned long long int val);
    inline Mass operator ""_kilograms(unsigned long long int val);
    inline Time operator ""_seconds(unsigned long long int val);
    inline Current operator ""_amperes(unsigned long long int val);
    inline Temperature operator ""_kelvins(unsigned long long int val);
    inline Amount operator ""_moles(unsigned long long int val);
    inline LuminousIntensity operator ""_candelas(unsigned long long int val);
    inline /* implementation defined */ operator ""_celsius(unsigned long long int val);

  }

}

#endif // UNITS_H
