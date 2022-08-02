#include <eval/ds/exceptions.hpp>
#include <eval/ds/String.hpp>
#include <eval/exceptions.hpp>

namespace eval {

ExceptionType 
Exception::type() const noexcept 
{ 
	return ExceptionType::Unspecified; 
}

namespace exception {

ExceptionType 
NullPointer::type() const noexcept 
{
	return ExceptionType::NullPointer; 
}

char const * 
NullPointer::description() const noexcept 
{ 
	return "dereferencing a null pointer"; 
}


ExceptionType 
InvalidCast::type() const noexcept 
{
	return ExceptionType::InvalidCast; 
}

char const * 
InvalidCast::description() const noexcept 
{ 
	return "invalid cast"; 
}


ExceptionType 
AllocationFailure::type() const noexcept 
{
	return ExceptionType::AllocationFailure; 
}

char const * 
AllocationFailure::description() const noexcept 
{ 
	return "allocation failure"; 
}


ExceptionType 
IndexOutOfBounds::type() const noexcept 
{
	return ExceptionType::IndexOutOfBounds; 
}

char const * 
IndexOutOfBounds::description() const noexcept 
{ 
	return "index out of bounds"; 
}



ExceptionType 
EntriesFull::type() const noexcept 
{
	return ExceptionType::EntriesFull; 
}

char const * 
EntriesFull::description() const noexcept 
{ 
	return "entries full"; 
}


ExceptionType 
EntryNotFound::type() const noexcept 
{
	return ExceptionType::EntryNotFound; 
}

char const * 
EntryNotFound::description() const noexcept 
{ 
	return "entry not found"; 
}

InvalidExpression::InvalidExpression(String description_) noexcept
	: m_description { move(description_) }
{}

ExceptionType 
InvalidExpression::type() const noexcept 
{
	return ExceptionType::InvalidExpression; 
}

char const * 
InvalidExpression::description() const noexcept 
{ 
	return m_description.cstr(); 
}


ExceptionType 
InvalidValue::type() const noexcept 
{
	return ExceptionType::InvalidValue; 
}

char const * 
InvalidValue::description() const noexcept 
{ 
	return "invalid value"; 
}


ExceptionType 
InvalidOperator::type() const noexcept 
{
	return ExceptionType::InvalidOperator; 
}

char const * 
InvalidOperator::description() const noexcept 
{ 
	return "invalid operator"; 
}


ExceptionType 
UnknownFunction::type() const noexcept 
{
	return ExceptionType::UnknownFunction; 
}

char const * 
UnknownFunction::description() const noexcept 
{ 
	return "function not registered"; 
}


ExceptionType 
UnknownID::type() const noexcept 
{
	return ExceptionType::UnknownID; 
}

char const * 
UnknownID::description() const noexcept 
{ 
	return "unknown id"; 
}


ExceptionType 
NullReference::type() const noexcept 
{
	return ExceptionType::NullReference; 
}

char const * 
NullReference::description() const noexcept 
{ 
	return "null reference"; 
}



} // namespace exception

} // namespace eval