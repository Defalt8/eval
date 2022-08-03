#include <eval/Evaluator.hpp>
#include <eval/ds/Array.hpp>
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cstring>
#include <cmath>

namespace eval {

static bool
is_operator(char c) noexcept
{
	switch(c)
	{
		case '*': 
		case '/': 
		case '%': 
		case '+': 
		case '-': 
		case '^': 
		case '(': 
		case ')': 
			return true;
		default: 
			return false;
	}
}

static String
concat_args(int argc, char * argv[]) noexcept(false)
{
	size_t size_ = 1;
	for(int i = 1; i < argc; ++i)
		size_ += strlen(argv[i]) + (i == argc-1 ? 0 : 1);
	String expression { size_ };
	size_t k = 0;
	for(int i = 1; i < argc; ++i)
	{
		size_t length = strlen(argv[i]);
		strncpy_s(&expression[k], size_ - k, argv[i], length);
		k += length;
		expression[k++] = ' ';
	}
	expression[size_ - 1] = '\0';
	return static_cast<String &&>(expression);
}

static void
register_default_variables(AssociativeArray<String,operand::Value> & variables) noexcept(false)
{
	variables["E"].value()      = 2.7182818284590452354L;
	variables["LOG2E"].value()  = 1.4426950408889634074L;
	variables["LN10"].value()   = 2.30258509299404568402L;
	variables["LN2"].value()    = 0.69314718055994530942L;
	variables["LOG10E"].value() = 0.43429448190325182765L;
	variables["PI"].value()     = 3.14159265358979323846L;
}

static void
register_default_functions(AssociativeArray<String,op::Function> & functions) noexcept(false)
{
	functions["sqrt"].func() = sqrt;
}

Evaluator::~Evaluator() noexcept
{}

Evaluator::Evaluator()
{
	register_default_variables(m_variables);
	register_default_functions(m_functions);
}

Evaluator::Evaluator(Evaluator && evaluator) noexcept
	: m_variables  { move(evaluator.m_variables) }
	, m_functions  { move(evaluator.m_functions) }
	, m_operators  { move(evaluator.m_operators) }
	, m_operands   { move(evaluator.m_operands) }
{}

value_t
Evaluator::evaluate_args(int argc, char * argv[]) noexcept(false)
{
	return evaluate(concat_args(argc, argv));
}


enum class EvalMode
{
	  None
	, Operand
	, Operator
};

value_t 
Evaluator::evaluate(String const & expression) noexcept(false)
{
	// printf("{%s}\n", &expression[0]);
	if(!is_valid(expression))
		throw exception::InvalidExpression();
	// evaluate left to right
	// TO-DO: implement evaluation
	//  - identify operand types
	//  - identify operator types
	//  - push on stack
	//  - use recursion
	{
		EvalMode mode = EvalMode::None;
		size_t length_ = expression.length();
		for(size_t i = 0; i < length_; ++i)
		{
			char c = expression[i];
			switch(mode)
			{
				case EvalMode::None:
				case EvalMode::Operand:
				case EvalMode::Operator:
				default:
					continue;
			}
		}
	}
	value_t result = 0;
	return result;
}

bool 
Evaluator::is_valid(String const & expression) const noexcept
{
	size_t length_ = expression.length();
	for(size_t i = 0; i < length_; ++i)
	{
		char c = expression[i];
		if(!(isdigit(c) || c == '.' || c == '_' || isalpha(c) || is_operator(c)))
			return false;
		// TO-DO: implement validation
	}
	return true;
}

bool 
Evaluator::is_variable(String const & operand) const noexcept
{
	for(auto const & var : m_variables)
		if(var.key == operand)
			return true;
	return false;
}

bool 
Evaluator::is_function(String const & operand) const noexcept
{
	for(auto const & func : m_functions)
		if(func.key == operand)
			return true;
	return false;
}

Evaluator::variables_t & 
Evaluator::variables() noexcept 
{
	return m_variables;
}

Evaluator::variables_t const & 
Evaluator::variables() const noexcept 
{
	return m_variables;
}

Evaluator::functions_t const & 
Evaluator::functions() const noexcept 
{
	return m_functions;
}

Evaluator::functions_t & 
Evaluator::functions() noexcept 
{
	return m_functions;
}


} // namespace eval