#pragma once
#ifndef EVAL_EXCEPTIONS_HPP
#define EVAL_EXCEPTIONS_HPP

namespace eval {

enum class ExceptionType
{
	  Unspecified
	, NullPointer
	, InvalidCast
	, AllocationFailure
	, IndexOutOfBounds
	, EntriesFull
	, EntryNotFound
	, InvalidExpression
	, InvalidValue
	, NullReference
	, UnknownFunction
};

extern char const *
enum_string_exception_type(ExceptionType exception_type) noexcept;

class Exception 
{
 public:
	virtual ~Exception() noexcept = default;
	Exception() noexcept = default;
	
	virtual ExceptionType type() const noexcept;
	virtual char const * description() const noexcept = 0;

};

namespace exception {

class NullPointer final : public Exception
{
 public:
	ExceptionType type() const noexcept override;
	char const * description() const noexcept override;
};

class InvalidCast final : public Exception
{
 public:
	ExceptionType type() const noexcept override;
	char const * description() const noexcept override;
};

class AllocationFailure final : public Exception
{
 public:
	ExceptionType type() const noexcept override;
	char const * description() const noexcept override;
};

class IndexOutOfBounds final : public Exception
{
 public:
	ExceptionType type() const noexcept override;
	char const * description() const noexcept override;
};

class EntriesFull final : public Exception
{
 public:
	ExceptionType type() const noexcept override;
	char const * description() const noexcept override;
};

class EntryNotFound final : public Exception
{
 public:
	ExceptionType type() const noexcept override;
	char const * description() const noexcept override;
};

class InvalidExpression final : public Exception
{
 public:
	ExceptionType type() const noexcept override;
	char const * description() const noexcept override;
};

class InvalidValue final : public Exception
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

class NullReference final : public Exception
{
 public:
	ExceptionType type() const noexcept override;
	char const * description() const noexcept override;
};

} // namespace exception

} // namespace eval

#endif // EVAL_EXCEPTIONS_HPP