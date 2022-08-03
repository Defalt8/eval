#include <eval/exceptions.hpp>

namespace eval {

static char const *
enum_string_exception_type(ExceptionType exception_type) noexcept
{
	switch(exception_type)
	{
		default:
		case ExceptionType::Unspecified:       return "Unspecified";
		case ExceptionType::NullPointer:       return "NullPointer";
		case ExceptionType::InvalidCast:       return "InvalidCast";
		case ExceptionType::AllocationFailure: return "AllocationFailure";
		case ExceptionType::IndexOutOfBounds:  return "IndexOutOfBounds";
		case ExceptionType::EntriesFull:       return "EntriesFull";
		case ExceptionType::EntryNotFound:     return "EntryNotFound";
		case ExceptionType::InvalidExpression: return "InvalidExpression";
		case ExceptionType::InvalidValue:      return "InvalidValue";
		case ExceptionType::NullReference:     return "NullReference";
		case ExceptionType::UnknownFunction:   return "UnknownFunction";
	}
}

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


ExceptionType 
InvalidExpression::type() const noexcept 
{
	return ExceptionType::InvalidExpression; 
}

char const * 
InvalidExpression::description() const noexcept 
{ 
	return "invalid expression"; 
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