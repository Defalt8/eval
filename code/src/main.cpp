#include <cstdio>
#include <eval.hpp>
#include <eval/ds/String.hpp>

extern char const * _Help_String;

int main(int argc, char *argv[])
{
	try
	{
		if(argc > 1)
		{
			eval::String arg1 = argv[1];
			if(arg1 == "-i" || arg1 == "--interactive")
			{
				auto evaluator = eval::Evaluator();
				eval::String input;
				while((input = eval::String::get_input()) && (input != "~exit" && input != "~quit"))
				{
					if(input == "~vars")
					{
						auto const & vars = evaluator.variables();
						for(auto const & var : vars)
							if(var.occupied)
								printf("  %10s -> %.15lf\n", var.key.cstr(), var.value.value());
							putc('\n', stdout);
					}
					else if(input == "~funcs")
					{
						auto const & funcs = evaluator.functions();
						for(auto const & func : funcs)
							if(func.occupied)
								printf("  %s\n", func.key.cstr());
							putc('\n', stdout);
					}
					else if(input == "~help")
					{
						printf("%s\n", _Help_String);
					}
					else
					{
						try 
						{
							auto result = evaluator.evaluate(eval::stripped(input));
							eval::report_value(result);
						}
						catch(eval::Exception const & ex)
						{
							eval::report_error(-2, ex.description());
						}
					}
				}
			}
			else if(arg1 == "-h" || arg1 == "--help")
			{
				printf("%s\n", _Help_String);
			}
			else
			{
				auto evaluator = eval::Evaluator();
				auto result = evaluator.evaluate_args(argc, argv);
				eval::report_value(result);
			}
		}
	}
	catch(eval::Exception const & ex)
	{
		return eval::report_error(-2, ex.description());
	}
	return 0;
}


char const * _Help_String = R"(
eval 1.1.6

COMMANDLINE-ARGUMENTS
    -i|--interactive    start in interactive mode
    -h|--help           display this help

INTERACTIVE-MODE-COMMANDS
    ~exit|~quit         exit
    ~vars               list variables and their values
    ~funcs              list functions
)";
