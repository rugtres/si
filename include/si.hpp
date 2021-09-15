#pragma once

#include <ratio>


namespace si {

  // a quantity with a the unit [ kg^M * m^L * s^T * angle^A ]
  template <typename M, typename L, typename T, typename A>
  class quantity_t {
  public:
    constexpr quantity_t() : value_(0.0) {}
    constexpr quantity_t(double val) : value_(val) {}

    constexpr double value() const { return value_; }

    // addition and subtraction doesn't change units
    constexpr const quantity_t& operator+=(const quantity_t& rhs) {
      value_ += rhs.value_;
    }

    constexpr const quantity_t& operator-=(const quantity_t& rhs) {
      value_ -= rhs.value_;
    }

  private:
    double value_;
  };


  // arithmetic operators
  
  // lhs[x] + rhs[x] = (lhs + rhs)[x]
  template <typename M, typename L, typename T, typename A>
  constexpr auto operator + (const quantity_t<M, L, T, A>& lhs, const quantity_t<M, L, T, A>& rhs) {
      return quantity_t<M, L, T, A>(lhs.value() + rhs.value());
  }

  // lhs[x] - rhs[x] = (lhs - rhs)[x]
  template <typename M, typename L, typename T, typename A>
  constexpr auto operator - (const quantity_t<M, L, T, A>& lhs, const quantity_t<M, L, T, A>& rhs) {
    return quantity_t<M, L, T, A>(lhs.value() - rhs.value());
  }

  // lhs[1] * rhs[x] = (lhs * rhs)[x]
  template <typename M, typename L, typename T, typename A>
  constexpr auto operator * (const double& lhs, const quantity_t<M, L, T, A>& rhs) {
    return quantity_t<M, L, T, A>(lhs * rhs.value());
  }

  // lhs[x] * rhs[1] = (lhs * rhs)[x]
  template <typename M, typename L, typename T, typename A>
  constexpr auto operator * (const quantity_t<M, L, T, A>& lhs, const double& rhs) {
    return quantity_t<M, L, T, A>(lhs.value() * rhs);
  }

  // lhs[x] / rhs[1] = (lhs / rhs)[x]
  template <typename M, typename L, typename T, typename A>
  constexpr auto operator / (quantity_t<M, L, T, A>& lhs, const double& rhs) {
    return quantity_t<M, L, T, A>(lhs.value() / rhs);
  }

  // lhs[1] / rhs[x] = (lhs / rhs)[-x]
  template <typename M, typename L, typename T, typename A>
  constexpr auto operator / (const double& lhs, const quantity_t<M, L, T, A>& rhs) {
    using std::ratio;
    using std::ratio_subtract;
    return quantity_t<ratio_subtract<ratio<0>,M>, ratio_subtract<ratio<0>, L>, ratio_subtract<ratio<0>, T>, ratio_subtract<ratio<0>, A>>(
      lhs / rhs.value()
    );
  }

  // lhs[x] * rhs[y] = (lhs * rhs)[x + y], e.g 3m * 2m = 6m^2
  template <typename ML, typename LL, typename TL, typename AL,
            typename MR, typename LR, typename TR, typename AR>
  constexpr auto operator * (const quantity_t<ML, LL, TL, AL>& lhs, const quantity_t<MR, LR, TR, AR>& rhs) {
    using std::ratio_add;
    return quantity_t<ratio_add<ML, MR>, ratio_add<LL, LR>, ratio_add<TL, TR>, ratio_add<AL, AR>>(
      lhs.value() * rhs.value()
    );
  }

  // lhs[x] / rhs[y] = (lhs / rhs)[x - y], e.g 3m / 1s = 3m * s^-1
  template <typename ML, typename LL, typename TL, typename AL,
            typename MR, typename LR, typename TR, typename AR>
  constexpr auto operator / (const quantity_t<ML, LL, TL, AL>& lhs, const quantity_t<MR, LR, TR, AR>& rhs) {
    using std::ratio_subtract;
    return quantity_t<ratio_subtract<ML, MR>, ratio_subtract<LL, LR>, ratio_subtract<TL, TR>, ratio_subtract<AL, AR>>(
      lhs.value() / rhs.value()
    );
  }

  // ...

  // comparison operators

  template <typename M, typename L, typename T, typename A>
  constexpr bool operator==(const quantity_t<M, L, T, A>& lhs, const quantity_t<M, L, T, A>& rhs)
  {
    return (lhs.value() == rhs.value());
  }

  template <typename M, typename L, typename T, typename A>
  constexpr bool operator!=(const quantity_t<M, L, T, A>& lhs, const quantity_t<M, L, T, A>& rhs)
  {
    return (lhs.value() != rhs.value());
  }

  template <typename M, typename L, typename T, typename A>
  constexpr bool operator<=(const quantity_t<M, L, T, A>& lhs, const quantity_t<M, L, T, A>& rhs)
  {
    return (lhs.value() <= rhs.value());
  }

  template <typename M, typename L, typename T, typename A>
  constexpr bool operator>=(const quantity_t<M, L, T, A>& lhs, const quantity_t<M, L, T, A>& rhs)
  {
    return (lhs.value() >= rhs.value());
  }

  template <typename M, typename L, typename T, typename A>
  constexpr bool operator< (const quantity_t<M, L, T, A>& lhs, const quantity_t<M, L, T, A>& rhs)
  {
    return (lhs.value() < rhs.value());
  }

  template <typename M, typename L, typename T, typename A>
  constexpr bool operator> (const quantity_t<M, L, T, A>& lhs, const quantity_t<M, L, T, A>& rhs)
  {
    return (lhs.value() > rhs.value());
  }


  // declare some units
#define si_declare_quantity(M, L, T, A, name) \
using name = quantity_t<std::ratio<M>, std::ratio<L>, std::ratio<T>, std::ratio<A>>;

  si_declare_quantity(1, 0, 0, 0, Mass);
  si_declare_quantity(0, 1, 0, 0, Length);
  si_declare_quantity(0, 0, 1, 0, Time);
  si_declare_quantity(0, 0, 0, 1, Angle);

  si_declare_quantity(0, 2, 0, 0, Area);
  si_declare_quantity(0, 3, 0, 0, Volume);

  si_declare_quantity(0, 1, -1, 0, Speed);
  si_declare_quantity(0, 1, -2, 0, Acceleration);
  si_declare_quantity(0, 0, -1, 0, Frequency);
  si_declare_quantity(1, 1, -2, 0, Force);
  si_declare_quantity(1, -1, -2, 0, Pressure);
  // ...


  // some named units...
  constexpr Mass kg(1.0);
  constexpr Mass gram = 0.001 * kg;
  constexpr Mass milligram = 0.001 * gram;
  constexpr Mass ounce = 0.028349523125 * kg;    // or something
  // ... //
  constexpr Length meter(1.0);
  constexpr Length centimeter = 0.01 * meter;
  constexpr Length millimeter = 0.001 * meter;
  constexpr Length kilometer = 1000.0 * meter;
  constexpr Length inch = 2.54 * centimeter;
  constexpr Length foot = 12.0 * inch;          // or something
  // ... //
  constexpr Time second(1.0);
  constexpr Time minute = 60.0 * second;
  // ... //
  constexpr Angle rad(1.0);
  constexpr Angle deg = (1.0 / 57.29577951308232087) * rad;
  // ... //
  constexpr Area squaremeter = meter * meter;
  constexpr Volume qubicfoot = foot * foot * foot;
  // ... //
  constexpr Force newton(1.0);


  // ... and their literals
#define si_define_literal(quant, lit, name) \
constexpr quant operator"" lit(long double x) { return static_cast<double>(x) * name; }; \
constexpr quant operator"" lit(unsigned long long x) { return static_cast<double>(x) * name; };

  si_define_literal(Mass, _kg, kg);
  si_define_literal(Mass, _g, gram);
  si_define_literal(Mass, _mg, milligram);
  si_define_literal(Mass, _oz, ounce);
  // ... //
  si_define_literal(Length, _m, meter);
  si_define_literal(Length, _mm, millimeter);
  si_define_literal(Length, _km, kilometer);
  si_define_literal(Length, _inch, inch);
  si_define_literal(Length, _foot, foot);
  // ... //
  si_define_literal(Time, _s, second);
  si_define_literal(Time, _min, minute);
  // ... //
  si_define_literal(Angle, _rad, rad);
  si_define_literal(Angle, _deg, deg);

  si_define_literal(Area, _m2, squaremeter);
  si_define_literal(Volume, _foot3, qubicfoot);
  // .. //
  si_define_literal(Force, _N, newton);

}
