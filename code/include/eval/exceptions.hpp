#pragma once
#ifndef EVAL_EXCEPTIONS_HPP
#define EVAL_EXCEPTIONS_HPP

#include "Exception.hpp"
#include "ds/String.hpp"

namespace eval {
namespace exception {


class InvalidExpression final : public Exception
{
	String m_description = "invalid expression";

 public:
	InvalidExpression() noexcept = default;
	InvalidExpression(String description) noexcept;
	ExceptionType type() const noexcept override;
	char const * description() const noexcept override;
};

class InvalidValue final : public Exception
{
 public:
	ExceptionType type() const noexcept override;
	char const * description() const noexcept override;
};

class InvalidOperator final : public Exception
{
 public:
	ExceptionType type() const noexcept override;
	char const * description() const noexcept override;
};

class UnknownFunction final : public Exception
{
 public:
	ExceptionType type() const noexcept override;
	char const * description() const noexcept override;
};

class UnknownID final : public Exception
{
 public:
	ExceptionType type() const noexcept override;
	char const * description() const noexcept override;
};

class NullReference final : public Exception
{
 public:
	ExceptionType type() const noexcept override;
	char const * description() const noexcept override;
};


} // namespace exception
} // namespace eval

#endif // EVAL_EXCEPTIONS_HPP