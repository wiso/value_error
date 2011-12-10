#ifndef VALUE_ERROR_H
#define VALUE_ERROR_H

#include <cmath>
#include <sstream>

// Forward declarations.
template<typename _Tp> class ValueErrorTemplate;


// Transcendentals:
/// Return cosine of @a z.
template<typename _Tp> ValueErrorTemplate<_Tp> cos(const ValueErrorTemplate<_Tp>&);
/// Return hyperbolic cosine of @a z.
template<typename _Tp> ValueErrorTemplate<_Tp> cosh(const ValueErrorTemplate<_Tp>&);
/// Return base e exponential of @a z.
template<typename _Tp> ValueErrorTemplate<_Tp> exp(const ValueErrorTemplate<_Tp>&);
/// Return natural logarithm of @a z.
template<typename _Tp> ValueErrorTemplate<_Tp> log(const ValueErrorTemplate<_Tp>&);
/// Return base 10 logarithm of @a z.
template<typename _Tp> ValueErrorTemplate<_Tp> log10(const ValueErrorTemplate<_Tp>&);
/// Return @a x to the @a y'th power.
template<typename _Tp> ValueErrorTemplate<_Tp> pow(const ValueErrorTemplate<_Tp>&, const _Tp&);
/// Return @a x to the @a y'th power.
template<typename _Tp> ValueErrorTemplate<_Tp> pow(const _Tp&, const ValueErrorTemplate<_Tp>&);
/// Return @a x to the @a y'th power.
template<typename _Tp> ValueErrorTemplate<_Tp> pow(const ValueErrorTemplate<_Tp>&, 
						   const ValueErrorTemplate<_Tp>&);
/// Return sine of @a z.
template<typename _Tp> ValueErrorTemplate<_Tp> sin(const ValueErrorTemplate<_Tp>&);
/// Return hyperbolic sine of @a z.
template<typename _Tp> ValueErrorTemplate<_Tp> sinh(const ValueErrorTemplate<_Tp>&);
/// Return square root of @a z.
template<typename _Tp> ValueErrorTemplate<_Tp> sqrt(const ValueErrorTemplate<_Tp>&);
/// Return tangent of @a z.
template<typename _Tp> ValueErrorTemplate<_Tp> tan(const ValueErrorTemplate<_Tp>&);
/// Return hyperbolic tangent of @a z.
template<typename _Tp> ValueErrorTemplate<_Tp> tanh(const ValueErrorTemplate<_Tp>&);



template<typename _Tp>
struct ValueErrorTemplate
{
  /// Value typedef.
  typedef _Tp value_type;

  /// Default constructor. First parameter is the central value,
  /// second parameter is the statistic error,
  /// third parameter is the systematic error.
  /// Unspecified parameters default to 0.
  ValueErrorTemplate(const _Tp& __value = _Tp(),
		     const _Tp& __stat_error = _Tp(),
		     const _Tp& __syst_error = _Tp())
  : _M_value(__value),
    _M_stat_error2(__stat_error * __stat_error),
    _M_syst_error2(__syst_error * __syst_error) { }

  template<typename _Up>
  ValueErrorTemplate(const ValueErrorTemplate<_Up>& __z)
    : _M_value(__z._M_value),
      _M_stat_error2(__z._M_stat_error2),
      _M_syst_error2(__z._M_syst_error2) { }

  _Tp& value()
  { return _M_value; }

  const _Tp& value() const
  { return _M_value; }

  _Tp value2() const
  { return _M_value * _M_value; }

  const _Tp stat_error() const
  { return sqrt(_M_stat_error2); }

  _Tp stat_error2() const
  { return _M_stat_error2; }

  _Tp syst_error2() const
  { return _M_syst_error2; }

  const _Tp syst_error() const
  { return sqrt(_M_syst_error2); }

  _Tp stat_error_rel2() const
  { return (stat_error2() == 0) ? 0 : stat_error2() / value2(); }

  _Tp syst_error_rel2() const
  { return (syst_error2() == 0) ? 0 : syst_error2() / value2(); }

  _Tp stat_error_rel() const
  { return sqrt(stat_error_rel2()); }

  _Tp syst_error_rel() const
  { return sqrt(syst_error_rel2()); }
  
  void value(_Tp __val)
  { _M_value = __val; }

  void stat_error(_Tp __val)
  { _M_stat_error2 = __val * __val; }

  void sys_error(_Tp __val)
  { _M_syst_error2 = __val * __val; }

  ValueErrorTemplate<_Tp>& operator=(const _Tp&);

  ValueErrorTemplate<_Tp>&
  operator+=(const _Tp& __t)
  {
    _M_value += __t;
    return *this;
  }

  ValueErrorTemplate<_Tp>&
  operator-=(const _Tp& __t)
  {
    _M_value -= __t;
    return *this;
  }

  ValueErrorTemplate<_Tp>& operator*=(const _Tp&);
  ValueErrorTemplate<_Tp>& operator/=(const _Tp&);
  template<typename _Up>
  ValueErrorTemplate<_Tp>& operator=(const ValueErrorTemplate<_Up>&);
  template<typename _Up>
  ValueErrorTemplate<_Tp>& operator+=(const ValueErrorTemplate<_Up>&);
  template<typename _Up>
  ValueErrorTemplate<_Tp>& operator-=(const ValueErrorTemplate<_Up>&);
  template<typename _Up>
  ValueErrorTemplate<_Tp>& operator*=(const ValueErrorTemplate<_Up>&);
  template<typename _Up>
  ValueErrorTemplate<_Tp>& operator/=(const ValueErrorTemplate<_Up>&);

  const ValueErrorTemplate& __rep() const
  { return *this; }

private:
  _Tp _M_value;
  _Tp _M_stat_error2;
  _Tp _M_syst_error2;

};

template<typename _Tp>
ValueErrorTemplate<_Tp>&
ValueErrorTemplate<_Tp>::operator=(const _Tp& __t)
{
  _M_value = __t;
  _M_stat_error2 = _Tp();
  _M_syst_error2 = _Tp();
  return *this;
}

template<typename _Tp>
ValueErrorTemplate<_Tp>&
ValueErrorTemplate<_Tp>::operator*=(const _Tp& __t)
{
  _M_value *= __t;
  _M_stat_error2 *= __t * __t;
  _M_syst_error2 *= __t * __t;
  return *this;
}

template<typename _Tp>
ValueErrorTemplate<_Tp>&
ValueErrorTemplate<_Tp>::operator/=(const _Tp& __t)
{
  _M_value /= __t;
  _M_stat_error2 /= __t * __t;
  _M_syst_error2 /= __t * __t;
  return *this;
}

template<typename _Tp>
template<typename _Up>
ValueErrorTemplate<_Tp>&
ValueErrorTemplate<_Tp>::operator=(const ValueErrorTemplate<_Up>& __z)
{
  _M_value = __z.value();
  _M_stat_error2 = __z._M_stat_error2;
  _M_syst_error2 = __z._M_syst_error2;
  return *this;
}

template<typename _Tp>
template<typename _Up>
ValueErrorTemplate<_Tp>&
ValueErrorTemplate<_Tp>::operator+=(const ValueErrorTemplate<_Up>& __z)
{
  _M_value += __z.value();
  _M_stat_error2 += __z._M_stat_error2;
  _M_syst_error2 += __z._M_syst_error2;
  return *this;
}

template<typename _Tp>
template<typename _Up>
ValueErrorTemplate<_Tp>&
ValueErrorTemplate<_Tp>::operator-=(const ValueErrorTemplate<_Up>& __z)
{
  _M_value -= __z.value();
  _M_stat_error2 += __z._M_stat_error2;
  _M_syst_error2 += __z._M_syst_error2;
  return *this;
}

template<typename _Tp>
template<typename _Up>
ValueErrorTemplate<_Tp>&
ValueErrorTemplate<_Tp>::operator*=(const ValueErrorTemplate<_Up>& __z)
{
  const _Tp new_value = value() * __z.value();
  const _Tp new_value2 = new_value * new_value;
  _M_stat_error2 = value2() * __z.stat_error2() + stat_error2() * __z.value2();
  _M_syst_error2 = value2() * __z.syst_error2() + syst_error2() * __z.value2();
  _M_value = new_value;
  return *this;
}

template<typename _Tp>
template<typename _Up>
ValueErrorTemplate<_Tp>&
ValueErrorTemplate<_Tp>::operator/=(const ValueErrorTemplate<_Up>& __z)
{
    const _Tp new_value = value() / __z.value();
    const _Tp new_value2 = new_value * new_value;
    _M_stat_error2 = new_value2 * (__z.stat_error_rel2() + stat_error_rel2());
    _M_syst_error2 = new_value2 * (__z.syst_error_rel2() + syst_error_rel2());
   _M_value = new_value;
    return *this;
}


//@{
/// Return new ValueErrorTemplate value @a x plus @a y
template<typename _Tp>
inline ValueErrorTemplate<_Tp>
operator+(const ValueErrorTemplate<_Tp>& __x,
	  const ValueErrorTemplate<_Tp>& __y)
{
  ValueErrorTemplate<_Tp> __r = __x;
  __r += __y;
  return __r;
}

template<typename _Tp>
inline ValueErrorTemplate<_Tp>
operator+(const ValueErrorTemplate<_Tp>& __x,
	  const _Tp& __y)
{
  ValueErrorTemplate<_Tp> __r = __x;
  __r += __y;
  return __r;
}

template<typename _Tp>
inline ValueErrorTemplate<_Tp>
operator+(const _Tp& __x,
	  const ValueErrorTemplate<_Tp>& __y)
{
  ValueErrorTemplate<_Tp> __r = __y;
  __r += __x;
  return __r;
}
//@}


//@{
/// Return new ValueErrorTemplate value @a x minus @a y
template<typename _Tp>
inline ValueErrorTemplate<_Tp>
operator-(const ValueErrorTemplate<_Tp>& __x,
	  const ValueErrorTemplate<_Tp>& __y)
{
  ValueErrorTemplate<_Tp> __r = __x;
  __r -= __y;
  return __r;
}

template<typename _Tp>
inline ValueErrorTemplate<_Tp>
operator-(const ValueErrorTemplate<_Tp>& __x,
	  const _Tp& __y)
{
  ValueErrorTemplate<_Tp> __r = __x;
  __r -= __y;
  return __r;
}

template<typename _Tp>
inline ValueErrorTemplate<_Tp>
operator-(const _Tp& __x,
	  const ValueErrorTemplate<_Tp>& __y)
{
  ValueErrorTemplate<_Tp> __r = __y;
  __r -= __x;
  return __r;
}
//@}



//@{
/// Return new ValueErrorTemplate value @a x times @a y
template<typename _Tp>
inline ValueErrorTemplate<_Tp>
operator*(const ValueErrorTemplate<_Tp>& __x,
	  const ValueErrorTemplate<_Tp>& __y)
{
  ValueErrorTemplate<_Tp> __r = __x;
  __r *= __y;
  return __r;
}

template<typename _Tp>
inline ValueErrorTemplate<_Tp>
operator*(const ValueErrorTemplate<_Tp>& __x,
	  const _Tp& __y)
{
  ValueErrorTemplate<_Tp> __r = __x;
  __r *= __y;
  return __r;
}

template<typename _Tp>
inline ValueErrorTemplate<_Tp>
operator*(const _Tp& __x,
	  const ValueErrorTemplate<_Tp>& __y)
{
  ValueErrorTemplate<_Tp> __r = __y;
  __r *= __x;
  return __r;
}
//@}

//@{
/// Return new ValueErrorTemplate value @a x divided by @a y
template<typename _Tp>
inline ValueErrorTemplate<_Tp>
operator/(const ValueErrorTemplate<_Tp>& __x,
	  const ValueErrorTemplate<_Tp>& __y)
{
  ValueErrorTemplate<_Tp> __r = __x;
  __r /= __y;
  return __r;
}

template<typename _Tp>
inline ValueErrorTemplate<_Tp>
operator/(const ValueErrorTemplate<_Tp>& __x,
	  const _Tp& __y)
{
  ValueErrorTemplate<_Tp> __r = __x;
  __r /= __y;
  return __r;
}

template<typename _Tp>
inline ValueErrorTemplate<_Tp>
operator/(const _Tp& __x,
	  const ValueErrorTemplate<_Tp>& __y)
{
  ValueErrorTemplate<_Tp> __r = __y;
  __r /= __x;
  return __r;
}
//@}

/// Return @a x
template<typename _Tp>
inline ValueErrorTemplate<_Tp>
operator+(const ValueErrorTemplate<_Tp>& __x)
{ return __x; }

/// Return negation of @a x
template<typename _Tp>
inline ValueErrorTemplate<_Tp>
operator-(const ValueErrorTemplate<_Tp>& __x)
{
  ValueErrorTemplate<_Tp> __r = __x;
  __r.value(-__r.value());
  return __r;
}

template<typename _Tp>
inline bool
operator==(const ValueErrorTemplate<_Tp>& __x,
	   const ValueErrorTemplate<_Tp>& __y)
{
  return __x.value() == __y.value &&
    __x._M_stat_error2 == __y._M_stat_error2 &&
    __x._M_syst_error2 == __y._M_syst_error2;
}

template<typename _Tp>
inline bool
operator!=(const ValueErrorTemplate<_Tp>& __x,
	   const ValueErrorTemplate<_Tp>& __y)
{
  return __x.value() != __y.value &&
    __x._M_stat_error2 != __y._M_stat_error2 &&
    __x._M_syst_error2 != __y._M_syst_error2;
}

/// Insertion operator for ValueErrorTemplate
template<typename _Tp, typename _CharT, class _Traits>
std::basic_ostream<_CharT, _Traits>&
operator<<(std::basic_ostream<_CharT, _Traits>& __os,
	   const ValueErrorTemplate<_Tp>& __x)
{
  std::basic_ostringstream<_CharT, _Traits> __s;
  __s.flags(__os.flags());
  __s.imbue(__os.getloc());
  __s.precision(__os.precision());
  __s << '[' << __x.value()
      << "+/-" << __x.stat_error()
      << "+/-" << __x.syst_error()
      << ']';
  return __os << __s.str();
}


template<typename _Tp>
inline ValueErrorTemplate<_Tp>
cos(const ValueErrorTemplate<_Tp>& __z)
{
    const _Tp value = __z.value();
    const _Tp der = fabs(sin(value));
    const _Tp stat = __z.stat_error();
    const _Tp syst = __z.syst_error();
    return ValueErrorTemplate<_Tp>(cos(value),
				   der * stat, 
				   der * syst);
}

template<typename _Tp>
inline ValueErrorTemplate<_Tp>
cosh(const ValueErrorTemplate<_Tp>& __z)
{
    const _Tp value = __z.value();
    const _Tp asinh_value = fabs(sinh(value));
    const _Tp stat = __z.stat_error();
    const _Tp syst = __z.syst_error();
    return ValueErrorTemplate<_Tp>(cosh(value),
				   asinh_value * stat, 
				   asinh_value * syst);
}

template<typename _Tp>
inline ValueErrorTemplate<_Tp>
exp(const ValueErrorTemplate<_Tp>& __z)
{
    const _Tp exp_value = exp(__z.value());
    const _Tp stat = __z.stat_error();
    const _Tp syst = __z.syst_error();
    return ValueErrorTemplate<_Tp>(exp_value,
				   exp_value * stat, 
				   exp_value * syst);
}

template<typename _Tp>
inline ValueErrorTemplate<_Tp>
log(const ValueErrorTemplate<_Tp>& __z)
{
    const _Tp value = __z.value();
    const _Tp der = fabs(1. / value);
    const _Tp stat = __z.stat_error();
    const _Tp syst = __z.syst_error();
    return ValueErrorTemplate<_Tp>(log(value),
				   der * stat, 
				   der * syst);
}


template<typename _Tp>
inline ValueErrorTemplate<_Tp>
log10(const ValueErrorTemplate<_Tp>& __z)
{
    const _Tp value = __z.value();
    const _Tp der = fabs(1. / (value * log(10)));
    const _Tp stat = __z.stat_error();
    const _Tp syst = __z.syst_error();
    return ValueErrorTemplate<_Tp>(log10(value),
				   der * stat, 
				   der * syst);
}

template<typename _Tp>
inline ValueErrorTemplate<_Tp>
pow(const ValueErrorTemplate<_Tp>& __x, const _Tp __y)
{
    
    const _Tp value = __x.value();
    const _Tp der = fabs(__y * pow(value, __y - 1));
    const _Tp stat = __x.stat_error();
    const _Tp syst = __x.syst_error();
    return ValueErrorTemplate<_Tp>(pow(value, __y),
				   der * stat, 
				   der * syst);
}

template<typename _Tp>
inline ValueErrorTemplate<_Tp>
pow(const _Tp __x, const ValueErrorTemplate<_Tp>& __y)
{
    
    const _Tp value = __y.value();
    const _Tp der = pow(__x, value) * log(__x);
    const _Tp stat = __x.stat_error();
    const _Tp syst = __x.syst_error();
    return ValueErrorTemplate<_Tp>(pow(__x, value),
				   der * stat, 
				   der * syst);
}


template<typename _Tp> ValueErrorTemplate<_Tp> pow(const ValueErrorTemplate<_Tp>& __x, 
						   const ValueErrorTemplate<_Tp>& __y)
{
    const _Tp value_x = __x.value();
    const _Tp value_y = __y.value();
    const _Tp new_value = pow(value_x, value_y);
    const _Tp der1 = value_y * pow(value_x, value_y - 1);
    const _Tp der2 = new_value * log(value_x);
    return ValueErrorTemplate<_Tp>(pow(value_x, value_y),
				   sqrt(pow(der1 * __x.stat_error(), 2) + pow(der2 * __y.stat_error(), 2)),
				   sqrt(pow(der1 * __x.syst_error(), 2) + pow(der2 * __y.syst_error(), 2)));
}

template<typename _Tp>
inline ValueErrorTemplate<_Tp>
sin(const ValueErrorTemplate<_Tp>& __z)
{
    const _Tp value = __z.value();
    const _Tp der = fabs(cos(value));
    const _Tp stat = __z.stat_error();
    const _Tp syst = __z.syst_error();
    return ValueErrorTemplate<_Tp>(sin(value),
				   der * stat, 
				   der * syst);
}

template<typename _Tp>
inline ValueErrorTemplate<_Tp>
sinh(const ValueErrorTemplate<_Tp>& __z)
{
    const _Tp value = __z.value();
    const _Tp der = fabs(cosh(value));
    const _Tp stat = __z.stat_error();
    const _Tp syst = __z.syst_error();
    return ValueErrorTemplate<_Tp>(sinh(value),
				   der * stat, 
				   der * syst);
}

template<typename _Tp>
inline ValueErrorTemplate<_Tp>
sqrt(const ValueErrorTemplate<_Tp>& __z)
{
    const _Tp value = __z.value();
    const _Tp new_value = sqrt(value);
    const _Tp der = 1. / (2 * new_value);
    const _Tp stat = __z.stat_error();
    const _Tp syst = __z.syst_error();
    return ValueErrorTemplate<_Tp>(new_value,
				   der * stat, 
				   der * syst);
}

template<typename _Tp>
inline ValueErrorTemplate<_Tp>
tan(const ValueErrorTemplate<_Tp>& __z)
{
    const _Tp value = __z.value();
    const _Tp new_value = tan(value);
    const _Tp der = 1 + pow(new_value, 2);
    const _Tp stat = __z.stat_error();
    const _Tp syst = __z.syst_error();
    return ValueErrorTemplate<_Tp>(new_value,
				   der * stat, 
				   der * syst);
}

template<typename _Tp>
inline ValueErrorTemplate<_Tp>
tanh(const ValueErrorTemplate<_Tp>& __z)
{
    const _Tp value = __z.value();
    const _Tp new_value = tanh(value);
    const _Tp der = fabs(1. - pow(new_value, 2));
    const _Tp stat = __z.stat_error();
    const _Tp syst = __z.syst_error();
    return ValueErrorTemplate<_Tp>(new_value,
				   der * stat, 
				   der * syst);
}


typedef ValueErrorTemplate<double> ValueError;

#endif
