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
						evaluator.list_variables();
					else if(input == "~funcs")
						evaluator.list_functions();
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
			else if(arg1 == "-lv" || arg1 == "-vars" || arg1 == "-variables")
				eval::Evaluator().list_variables();
			else if(arg1 == "-lf" || arg1 == "-funcs" || arg1 == "-functions")
				eval::Evaluator().list_functions();
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
eval 1.3.8

Commandline Arguments
    -i|--interactive        start in interactive mode
    -h|--help               display this help
    -lv|--list-variables    lists the registered variables
    -lf|--list-functions    lists the registered functions

Interactive Mode Commands
    ~exit|~quit             exit
    ~vars                   list variables and their values
    ~funcs                  list functions
)";
