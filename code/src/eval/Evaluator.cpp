#include <eval/ds/Array.hpp>
#include <eval/exceptions.hpp>
#include <eval/Evaluator.hpp>
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cstring>
#include <cmath>

namespace eval {

static String
stripped(String const & string) noexcept(false)
{
	String stripped_string { string.size() };
	size_t length_ = string.length();
	size_t j = 0;
	for(size_t i = 0; i < length_; ++i)
	{
		char c = string[i];
		if(!(isspace(c) || c == '"' || c == '\''))
			stripped_string[j++] = c;
	}
	return { &stripped_string[0], &stripped_string[j] };
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
	  #ifdef _MSC_VER
		strncpy_s(&expression[k], size_ - k, argv[i], length);
	  #else
		strncpy(&expression[k], argv[i], length);
	  #endif
		k += length;
		expression[k++] = ' ';
	}
	expression[size_ - 1] = '\0';
	return static_cast<String &&>(expression);
}

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
		case '=': 
		case ';': 
			return true;
		default: 
			return false;
	}
}

static bool
precedes(char lhs_op, char rhs_op) noexcept
{
	switch(lhs_op)
	{
		case '(': 
		case ')': 
			switch(rhs_op)
			{
				case '*': 
				case '/': 
				case '%': 
				case '+': 
				case '-': 
				case '^': 
				case '(': 
				case ')': 
				case '=': 
				case ';': 
				default: 
					return true;
					// return false;
			}
		case '^': 
			switch(rhs_op)
			{
				case '*': 
				case '/': 
				case '%': 
				case '+': 
				case '-': 
				case ';': 
				case '=': 
					return true;
				case '^': 
				case '(': 
				case ')': 
				default: 
					return false;
			}
		case '%': 
			switch(rhs_op)
			{
				case '*': 
				case '/': 
				case '%': 
				case '+': 
				case '-': 
				case ';': 
				case '=': 
					return true;
				case '^': 
				case '(': 
				case ')': 
				default: 
					return false;
			}
		case '*': 
		case '/': 
			switch(rhs_op)
			{
				case '*': 
				case '/': 
				case '+': 
				case '-': 
				case ';': 
				case '=': 
					return true;
				case '%': 
				case '^': 
				case '(': 
				case ')': 
				default: 
					return false;
			}
		case '+': 
		case '-': 
			switch(rhs_op)
			{
				case '+': 
				case '-': 
				case ';': 
				case '=': 
					return true;
				case '*': 
				case '/': 
				case '%': 
				case '^': 
				case '(': 
				case ')': 
				default: 
					return false;
			}
		case '=': 
		case ';': 
			return true;
		default: 
			return false;
	}
}

static bool
is_value(String const & operand_) noexcept
{
	size_t length_ = operand_.length();
	bool value_ = false, nvalue_ = false;
	size_t start_ = 0;
	if(operand_[start_] == '+' || operand_[start_] == '-')
		start_++;
	for(size_t i = start_; i < length_; ++i)
	{
		char c = operand_[i];
		if((isdigit(c) || c == '.') && !value_)
			value_ = true;
		if(isalpha(c) && !nvalue_)
			nvalue_ = true;
	}
	return value_ && !nvalue_;
}

// (...)
static String 
get_sub_expression(String const & expression, size_t start_) noexcept(false)
{
	size_t length_ = expression.length();
	if(start_ >= length_ || expression[start_] != '(')
		throw exception::InvalidExpression(String::format(2048, "%s <-- expecting '('", String(&expression[0], expression.cstr()[start_+1]).cstr()));
	int count = 1;
	size_t i = start_ + 1;
	for(; i < length_; ++i)
	{
		if(expression[i] == '(')
			++count;
		else if(expression[i] == ')')
		{
			--count;
			if(count == 0)
				return { &expression[start_ + 1], &expression[i] };
		}
	}
	throw exception::InvalidExpression(String::format(2048, "%s <-- expecting ')'", String(&expression[0], expression.cstr()[i]).cstr()));
	return {};
}

// ...;
static String 
get_semi_expression(String const & expression, size_t start_) noexcept(false)
{
	size_t length_ = expression.length();
	size_t i = start_;
	for(; i < length_; ++i)
		if(expression[i] == ';')
			break;
	return { &expression[start_], &expression[i] };
}

static String 
get_token(String const & expression, size_t start_, size_t & token_end_) noexcept(false)
{
	size_t length_ = expression.length();
	if(length_ <= 0)
		return {};
	String token { expression.size() };
	size_t start = start_;
	size_t j = 0;
	if(expression[start] == '-' || expression[start] == '+')
		token[j++] = expression[start++];
	if(expression[start] == '-' || expression[start] == '+')
		throw exception::InvalidExpression(String::format(2048, "%s <--", String(&expression[0], expression.cstr()[start+1]).cstr()));
	size_t i = start;
	for(; i < length_; ++i)
	{
		char c = expression[i];
		if(is_operator(c))
			break;
		else if(!(isalnum(c) || c == '.' || c == '_'))
			throw exception::InvalidExpression(String::format(2048, "%s <--", String(&expression[0], expression.cstr()[i+1]).cstr()));
		token[j++] = c;
	}
	token_end_ = i;
	return String { &token[0], &token[strlen(token.cstr())] };	
}

value_t
operate(value_t & lhs, char op_, value_t & rhs) noexcept(false)
{
	switch(op_)
	{
		case '*': return lhs * rhs;
		case '/': return lhs / rhs;
		case '%': return fmod(lhs, rhs);
		case '+': return lhs + rhs;
		case '-': return lhs - rhs;
		case '^': return pow(lhs, rhs);
		case '=': return lhs = rhs;
		default: throw exception::InvalidOperator();
	}
	return 0;
}

static void
register_default_variables(Evaluator::variables_t & variables) noexcept(false)
{
	variables["e"].value()      = 2.7182818284590452354L;
	variables["log2e"].value()  = 1.4426950408889634074L;
	variables["ln10"].value()   = 2.30258509299404568402L;
	variables["ln2"].value()    = 0.69314718055994530942L;
	variables["log10e"].value() = 0.43429448190325182765L;
	variables["pi"].value()     = 3.14159265358979323846L;
	variables["2pi"].value()    = 2*3.14159265358979323846L;
	variables["3pi"].value()    = 3*3.14159265358979323846L;
	variables["4pi"].value()    = 4*3.14159265358979323846L;
}

value_t deg2rad(value_t v) noexcept { return v * 3.14159265358979323846L / 180.L; }
value_t rad2deg(value_t v) noexcept { return v * 180.L / 3.14159265358979323846L; }
value_t norm2rad(value_t v) noexcept { return v * (2*3.14159265358979323846L); }
value_t rad2norm(value_t v) noexcept { return v / (2*3.14159265358979323846L); }
value_t sign(value_t v) noexcept { return v < 0 ? -1 : 1; }
value_t signz(value_t v) noexcept { return v == 0 ? 0 : (v < 0 ? -1 : 1); }

static void
register_default_functions(Evaluator::functions_t & functions) noexcept(false)
{
	functions["sqrt"] = sqrt;
	functions["sin"] = sin;
	functions["cos"] = cos;
	functions["tan"] = tan;
	functions["asin"] = asin;
	functions["acos"] = acos;
	functions["atan"] = atan;
	functions["sign"] = sign;
	functions["abs"] = fabs;
	functions["deg2rad"] = deg2rad;
	functions["rad2deg"] = rad2deg;
	functions["norm2rad"] = norm2rad;
	functions["rad2norm"] = rad2norm;
}

/**************************************************/

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
{}

value_t
Evaluator::evaluate_args(int argc, char * argv[]) noexcept(false)
{
	return evaluate(stripped(concat_args(argc, argv)));
}

value_t
Evaluator::evaluate(String const & expression) noexcept(false)
{
	Array<char> op_stack { _Max_Operators };
	Array<value_t> operand_stack { _Max_Operands };
	int op_top = 0;
	int operand_top = 0;
	value_t result = 0;
	size_t length_ = expression.length();
	size_t i = 0;
	for(; i < length_; ++i)
	{
		if(expression[i] == ';')
		{
			result = 0;
			m_variables["result"].value() = result;
			continue;
		}
		else if(expression[i] == '(')
		{
			String sub_expression = get_sub_expression(expression, i);
			value_t sub_value = evaluate(sub_expression);
			result = sub_value;
			i += sub_expression.length() + 2;
		}
		else
		{
			size_t token_end_ = i, sub_expression_end_ = i;
			String token = get_token(expression, i, token_end_);
			// sub_expression_end_ to check if a function is being assigned
			if(token_end_ < length_ && expression[token_end_] == '(')
				sub_expression_end_ = token_end_ + get_sub_expression(expression, token_end_).length() + 2;
			else 
				sub_expression_end_ = token_end_;
			// -------------------
			if(is_value(token))
			{
				result = atof(token.cstr());
				i = token_end_;
			}
			else if(token_end_ >= length_ || expression[sub_expression_end_] != '=')
			{
				// token is not a value and not being assigned to 
				if(is_variable(token))
				{
					result = m_variables[token].value();
					i = token_end_;
				}
				else if(is_function(token))
				{
					String sub_expression = get_sub_expression(expression, token_end_);
					value_t sub_value = evaluate(sub_expression);
					result = m_functions[token](sub_value);
					i = token_end_ + sub_expression.length() + 2;
				}
				else
					throw exception::InvalidExpression(String::format(2048, "%s <-- unknown ID", String(&expression[0], expression.cstr()[token_end_]).cstr()));
			}
			else if(is_function(token)) // assigning to a function
				throw exception::InvalidExpression(String::format(2048, "%s <-- function to the left of =", String(&expression[0], expression.cstr()[token_end_]).cstr()));
			else if(expression[sub_expression_end_] == '=')
			{
				// do assignment 
				String semi_expression = get_semi_expression(expression, token_end_ + 1);
				result = evaluate(semi_expression);
				m_variables[token].value() = result;
				i = token_end_ + 1 + semi_expression.length();
				continue;
			}
			else if(i < length_)
				throw exception::InvalidExpression(String::format(2048, "%s <--", String(&expression[0], expression.cstr()[token_end_]).cstr()));
		}
		operand_stack[operand_top++] = result;
		if(i < length_)
		{
			if(expression[i] == ';')
				m_variables["result"].value() = result;
			else
			{
				char operator_char_ = expression[i];
				// as long as the operators on the stack precede, evaluate the down stack
				if(op_top > 0 && precedes(op_stack[op_top-1], operator_char_))
				{
					result = operand_stack[--operand_top];
					while(op_top > 0 && precedes(op_stack[op_top-1], operator_char_))
						result = operate(operand_stack[--operand_top], op_stack[--op_top], result);
					operand_stack[operand_top++] = result;
					// m_variables["result"].value() = result;
				}
				op_stack[op_top++] = operator_char_;
			}
		}
	}
	if(op_top > 0)
	{
		// check for operator-operand balance
		if(operand_top <= op_top)
			throw exception::InvalidExpression(String::format(2048, "%s <-- expecting operand", String(&expression[0], expression.cstr()[i+1]).cstr()));
		else
		{
			// evaluate the down stack
			result = operand_stack[--operand_top];
			while(op_top > 0)
				result = operate(operand_stack[--operand_top], op_stack[--op_top], result);
			// m_variables["result"].value() = result;
		}
	}
	m_variables["result"].value() = result;
	return result;
}

bool 
Evaluator::is_variable(String const & operand_) const noexcept
{
	try 
	{
		auto const & variables_ = m_variables;
		auto const & var = variables_[operand_];
	}
	catch(exception::EntryNotFound const & ex)
	{
		return false;
	}
	return true;
}

bool 
Evaluator::is_function(String const & operand_) const noexcept
{
	try 
	{
		auto const & functions_ = m_functions;
		auto const & func = functions_[operand_];
	}
	catch(exception::EntryNotFound const & ex)
	{
		return false;
	}
	return true;
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