#include <eval.hpp>


int main(int argc, char *argv[])
{
	try
	{
		auto evaluator = eval::Evaluator();
		auto result = evaluator.evaluate_args(argc, argv);
		eval::report_value(result);
	}
	catch(eval::Exception const & ex)
	{
		return eval::report_error(-2, ex.description());
	}
	return 0;
}