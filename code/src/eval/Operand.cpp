#include <eval/Operand.hpp>
#include <eval/exceptions.hpp>

namespace eval {

namespace operand {

Value::Value() noexcept
{}

Value::Value(String id_, value_t value_) noexcept
	: m_id    { id_ }
	, m_value { value_ }
{}

OperandType 
Value::type() const noexcept 
{
	return OperandType::Value; 
}

String
Value::id() const noexcept 
{
	return m_id;
}

value_t & 
Value::value() noexcept(false)
{
	return m_value;
}

value_t const & 
Value::value() const noexcept(false)
{
	return m_value;
}


Reference::Reference() noexcept
{}

Reference::Reference(String id_, Operand & operand_) noexcept
	: m_id        { id_ }
{
	Operand * operand = &operand_;
	while(operand && operand->type() == OperandType::Reference)
		operand = static_cast<operand::Reference *>(operand)->reference();
	m_reference = operand;
}

Reference::Reference(String id_, Value & value_) noexcept
	: m_id        { id_ }
	, m_reference { &value_ }
{}

Reference::Reference(String id_, Reference & reference_) noexcept
	: m_id        { id_ }
{
	Operand * operand = &reference_;
	while(operand && operand->type() == OperandType::Reference)
		operand = static_cast<operand::Reference *>(operand)->reference();
	m_reference = operand;
}

OperandType 
Reference::type() const noexcept 
{ 
	return OperandType::Reference; 
}

String
Reference::id() const noexcept 
{
	return m_id;
}

Operand * 
Reference::reference() noexcept 
{
	return m_reference;
}

Operand const * 
Reference::reference() const noexcept 
{
	return m_reference;
}

value_t & 
Reference::value() noexcept(false)
{
	Operand * operand = m_reference;
	while(operand && operand->type() != OperandType::Value)
	{
		switch(operand->type())
		{
			default:
			case OperandType::Unknown: throw exception::NullReference(); break;
			case OperandType::Value: break;
			case OperandType::Reference: operand = static_cast<Reference *>(operand)->m_reference; break;
		}
	}
	if(!operand)
		throw exception::NullReference();
	return static_cast<Value *>(operand)->value();
}

value_t const & 
Reference::value() const noexcept(false)
{
	Operand * operand = m_reference;
	while(operand && operand->type() != OperandType::Value)
	{
		switch(operand->type())
		{
			default:
			case OperandType::Unknown: throw exception::NullReference(); break;
			case OperandType::Value: break;
			case OperandType::Reference: operand = static_cast<Reference *>(operand)->m_reference; break;
		}
	}
	if(!operand)
		throw exception::NullReference();
	return static_cast<Value *>(operand)->value();
}



} // namespace operand

} // namespace eval