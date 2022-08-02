#pragma once
#ifndef EVAL_EXCEPTION_HPP
#define EVAL_EXCEPTION_HPP

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
	, InvalidOperator
	, NullReference
	, UnknownFunction
	, UnknownID
};

class Exception 
{
 public:
	virtual ~Exception() noexcept = default;
	Exception() noexcept = default;
	
	virtual ExceptionType type() const noexcept;
	virtual char const * description() const noexcept = 0;

};


} // namespace eval

#endif // EVAL_EXCEPTION_HPP