#include <eval/Evaluator.hpp>
#include <eval/ds/Array.hpp>
#include <cstdio>
#include <cstring>

namespace eval {

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


Evaluator::~Evaluator() noexcept
{}

Evaluator::Evaluator()
{}

Evaluator::Evaluator(Evaluator && evaluator) noexcept
	: m_operands   { move(evaluator.m_operands) }
	, m_operators  { move(evaluator.m_operators) }
{}

void
Evaluator::evaluate_args(int argc, char * argv[]) noexcept(false)
{
	evaluate(concat_args(argc, argv));
}

void 
Evaluator::evaluate(String const & expression) noexcept(false)
{
	value_t result = 0;
	printf("{%s}\n", &expression[0]);
	report_value(result);
}


} // namespace eval