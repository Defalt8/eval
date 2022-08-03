#pragma once
#ifndef EVAL_OPERATOR_HPP
#define EVAL_OPERATOR_HPP

#include "common.hpp"
#include "ds/Unique.hpp"
#include "Operand.hpp"

namespace eval {

enum class OperatorType
{
	  Unspecified
	, BuiltIn
	, Function
};


class Operator
{
 public:
	virtual ~Operator() noexcept = default;
	Operator() = default;

	virtual OperatorType type() const noexcept = 0;
	virtual Unique<Operand> operate(Operand & lhs, Operand & rhs) const noexcept(false) = 0;

};

namespace op {

class BuiltIn final : public Operator
{
	char m_operator = '\0';

 public:
	BuiltIn() noexcept = default;
	BuiltIn(char operator_) noexcept;

	OperatorType type() const noexcept override;
	// lhs operator rhs
	Unique<Operand> operate(Operand & lhs, Operand & rhs) const noexcept(false) override;

	char &       operator_()       noexcept;
	char const & operator_() const noexcept;

};


class Function final : public Operator
{
	using func_t = value_t(*)(value_t);

	func_t m_func = nullptr;

 public:
	Function() noexcept = default;
	Function(func_t func) noexcept;

	OperatorType type() const noexcept override;
	// lhs * func(rhs)
	Unique<Operand> operate(Operand & lhs, Operand & rhs) const noexcept(false) override;

	func_t &       func()       noexcept;
	func_t const & func() const noexcept;

};

} // namespace op

} // namespace eval

#endif // EVAL_OPERATOR_HPP