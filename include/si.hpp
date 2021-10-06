#pragma once

namespace si {

  // a quantity with unit [Mass^M * Length^L * time^T]
  template <int M, int L, int T>
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


  // base quantities
  using Mass = quantity_t<1, 0, 0>;
  using Length = quantity_t<0, 1, 0>;
  using Time = quantity_t<0, 0, 1>;


  // addition of homogeneous quantities
  // units are unchanged

  template <int M, int L, int T>
  constexpr auto operator + (const quantity_t<M, L, T>& lhs, const quantity_t<M, L, T>& rhs) {
    return quantity_t<M, L, T>(lhs.value() + rhs.value());
  }

  // subtraction of homogeneous quantities
  // units are unchanged 

  template <int M, int L, int T>
  constexpr auto operator - (const quantity_t<M, L, T>& lhs, const quantity_t<M, L, T>& rhs) {
    return quantity_t<M, L, T>(lhs.value() - rhs.value());
  }

  // scaling operators
  // units are unchanged

  template <int M, int L, int T>
  constexpr auto operator * (const double& lhs, const quantity_t<M, L, T>& rhs) {
    return quantity_t<M, L, T>(lhs * rhs.value());
  }

  template <int M, int L, int T>
  constexpr auto operator * (const quantity_t<M, L, T>& lhs, const double& rhs) {
    return quantity_t<M, L, T>(lhs.value() * rhs);
  }

  template <int M, int L, int T>
  constexpr auto operator / (quantity_t<M, L, T>& lhs, const double& rhs) {
    return quantity_t<M, L, T>(lhs.value() / rhs);
  }


  // division number / quantity
  // units flip sign!
  template <int M, int L, int T>
  constexpr auto operator / (const double& lhs, const quantity_t<M, L, T>& rhs) {
    return quantity_t<-M, -L, -T>(
      lhs / rhs.value()
    );
  }

  // mixed quantity multiplication
  // units are added together!
  template <int ML, int LL, int TL,
            int MR, int LR, int TR>
  constexpr auto operator * (const quantity_t<ML, LL, TL>& lhs, const quantity_t<MR, LR, TR>& rhs) {
    return quantity_t<ML + MR, LL + LL, TL + TR>(
      lhs.value() * rhs.value()
    );
  }

  // mixed quantity multiplication
  // units are subtracted!
  template <int ML, int LL, int TL,
            int MR, int LR, int TR>
  constexpr auto operator / (const quantity_t<ML, LL, TL>& lhs, const quantity_t<MR, LR, TR>& rhs) {
    return quantity_t<ML - MR, LL - LR, TL - TR>(
      lhs.value() / rhs.value()
    );
  }

  // ...

  // comparison operators

  template <int M, int L, int T>
  constexpr bool operator==(const quantity_t<M, L, T>& lhs, const quantity_t<M, L, T>& rhs) {
    return (lhs.value() == rhs.value());
  }

  template <int M, int L, int T>
  constexpr bool operator!=(const quantity_t<M, L, T>& lhs, const quantity_t<M, L, T>& rhs) {
    return (lhs.value() != rhs.value());
  }

  template <int M, int L, int T>
  constexpr bool operator<=(const quantity_t<M, L, T>& lhs, const quantity_t<M, L, T>& rhs) {
    return (lhs.value() <= rhs.value());
  }

  template <int M, int L, int T>
  constexpr bool operator>=(const quantity_t<M, L, T>& lhs, const quantity_t<M, L, T>& rhs) {
    return (lhs.value() >= rhs.value());
  }

  template <int M, int L, int T>
  constexpr bool operator<(const quantity_t<M, L, T>& lhs, const quantity_t<M, L, T>& rhs) {
    return (lhs.value() < rhs.value());
  }

  template <int M, int L, int T>
  constexpr bool operator>(const quantity_t<M, L, T>& lhs, const quantity_t<M, L, T>& rhs) {
    return (lhs.value() > rhs.value());
  }


  // si base units
  constexpr auto Kilogram  = Mass(1.0);
  constexpr auto Meter = Length(1.0);
  constexpr auto Second = Time(1.0);

  // scaled ones
  constexpr auto Gram = Mass(0.001);
  constexpr auto Kilometer = Length(1000.0);
  constexpr auto Hour = Time(60.0*60.0);

  // a derived quantity and its unit
  using Force = quantity_t<1, 1, -2>;
  constexpr auto Newton = Force(1.0);

 // ... and their literals
#define si_define_literal(quant, lit, name) \
constexpr quant operator"" lit(long double x) { return static_cast<double>(x) * name; }; \
constexpr quant operator"" lit(unsigned long long x) { return static_cast<double>(x) * name; };

si_define_literal(Mass, _kg, Kilogram);
si_define_literal(Length, _m, Meter);
si_define_literal(Time, _s, Second);
si_define_literal(Mass, _g, Gram);
si_define_literal(Length, _km, Kilometer);
si_define_literal(Time, _h, Hour);
si_define_literal(Force, _N, Newton);

}
