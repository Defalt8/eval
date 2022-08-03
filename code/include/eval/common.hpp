#pragma once
#ifndef EVAL_COMMON_HPP
#define EVAL_COMMON_HPP

#include "exceptions.hpp"

namespace eval {

using value_t = double;

template <typename T>
static constexpr T const &
max(T const & a, T const & b) noexcept
{
	return a > b ? a : b;
}

template <typename T>
static constexpr T const &
min(T const & a, T const & b) noexcept
{
	return a < b ? a : b;
}

template <typename T>
static constexpr void
swap(T & lhs, T & rhs) noexcept
{
	T tmp = move(lhs);
	lhs   = move(rhs);
	rhs   = move(tmp);
}

extern int report_error(int error_num, char const * error_str) noexcept;
extern void report_value(value_t const & value) noexcept;

template <typename T, typename... Args>
struct IsConstructible { static constexpr bool value = __is_constructible(T, Args...); };

template <bool c, class T = void> struct EnableIf {};
template <class T> struct EnableIf<true,T> { using type = T; };
template <bool c, class T = void> using enable_if_t = typename EnableIf<c,T>::type;

template <typename T>
static constexpr T decl();

template <typename T> 
static constexpr T && move(T && t) noexcept { return static_cast<T &&>(t); }
template <typename T> 
static constexpr T && move(T & t) noexcept { return static_cast<T &&>(t); }
template <typename T> 
static constexpr T && move(T const & t) noexcept = delete;

template <typename T, size_t size_>
static constexpr size_t size(T [size_]) noexcept { return size_; }

template <typename T>
static inline size_t 
hash(T const & value) noexcept
{
	return size_t(value);
}

} // namespace eval

#endif // EVAL_COMMON_HPP