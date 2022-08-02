#pragma once
#ifndef EVAL_DS_EXCEPTIONS_HPP
#define EVAL_DS_EXCEPTIONS_HPP

#include "../Exception.hpp"

namespace eval {

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

} // namespace exception
} // namespace eval


#endif // EVAL_DS_EXCEPTIONS_HPP