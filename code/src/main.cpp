#include <eval.hpp>
#include <cstdio>

int main(int argc, char *argv[])
{
	try
	{
		auto evaluator = eval::Evaluator();
		auto result = evaluator.evaluate_args(argc, argv);
		// eval::report_value(result);
		// testing...
		auto & vars = evaluator.variables();
		{
			vars["my_var"] = eval::operand::Value("my_var", 0);
			eval::Unique<eval::Operand> lhs = new eval::operand::Value(nullptr, 2);
			eval::Unique<eval::Operand> rhs = new eval::operand::Reference(nullptr, vars["PI"]);
			{
				eval::op::BuiltIn mul ('*');
				auto result = mul.operate(*lhs, *rhs);
				eval::op::BuiltIn assign ('=');
				assign.operate(vars["my_var"], *result);
				eval::report_value(result->value());
			}
			for(auto const & e : vars)
				if(e.occupied)
					printf("%10s -> %lf\n", e.key.cstr(), e.value.value());
		}
	}
	catch(eval::Exception const & ex)
	{
		return eval::report_error(-2, ex.description());
	}
	return 0;
}