#include <eval.hpp>

int main(int argc, char *argv[])
{
	try
	{
		auto evaluator = eval::Evaluator();
		evaluator.evaluate_args(argc, argv);
	}
	catch(eval::Exception const & ex)
	{
		return eval::report_error(-2, ex.description());
	}
	return 0;
}