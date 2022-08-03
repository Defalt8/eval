#include <eval/Operator.hpp>
#include <cmath>

namespace eval {

namespace op {

BuiltIn::BuiltIn(char operator_) noexcept
	: m_operator { operator_ }
{}

OperatorType 
BuiltIn::type() const noexcept
{
	return OperatorType::BuiltIn;
}

// lhs operator rhs
Unique<Operand>
BuiltIn::operate(Operand & lhs, Operand & rhs) const noexcept(false)
{
	value_t & lhs_val = lhs.value();
	value_t & rhs_val = rhs.value();
	switch(m_operator)
	{
		case '*': return new operand::Value(nullptr, lhs_val * rhs_val);
		case '/': return new operand::Value(nullptr, lhs_val / rhs_val);
		case '%': return new operand::Value(nullptr, fmod(lhs_val, rhs_val));
		case '+': return new operand::Value(nullptr, lhs_val + rhs_val);
		case '-': return new operand::Value(nullptr, lhs_val - rhs_val);
		case '^': return new operand::Value(nullptr, pow(lhs_val, rhs_val));
		case '=':
		{
			lhs_val = rhs_val;
			Operand * operand = &lhs;
			while(operand && operand->type() == OperandType::Reference)
				operand = static_cast<operand::Reference *>(operand)->reference();
			return new operand::Reference(lhs.id(), *static_cast<operand::Value *>(operand));
		}
		default: throw exception::InvalidOperator();
	}
	return {};
}

char & 
BuiltIn::operator_() noexcept
{
	return m_operator;
}

char const & 
BuiltIn::operator_() const noexcept
{
	return m_operator;
}



Function::Function(func_t func) noexcept
	: m_func { func }
{}

OperatorType 
Function::type() const noexcept
{
	return OperatorType::Function;
}

Unique<Operand> 
Function::operate(Operand & lhs, Operand & rhs) const noexcept(false)
{
	if(!m_func)
		throw exception::NullPointer();
	return new operand::Value(nullptr, lhs.value() * m_func(rhs.value()));
}

Function::func_t &       
Function::func()       noexcept
{
	return m_func;
}

Function::func_t const & 
Function::func() const noexcept
{
	return m_func;
}



} // namespace op

} // namespace eval