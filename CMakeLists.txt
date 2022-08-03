cmake_minimum_required( VERSION 3.4 )

project( eval VERSION 1.0.0 DESCRIPTION "command line tool for evaluating mathematical operations" )

set( EVAL_HEADER_FILES
	code/include/eval.hpp
	code/include/eval/common.hpp
	code/include/eval/exceptions.hpp
	code/include/eval/Operand.hpp
	code/include/eval/Operator.hpp
	code/include/eval/Evaluator.hpp
)

set( EVAL_SOURCE_FILES
	code/src/main.cpp
	code/src/eval/common.cpp
	code/src/eval/exceptions.cpp
	code/src/eval/Operand.cpp
	code/src/eval/Operator.cpp
	code/src/eval/Evaluator.cpp
)

add_executable( eval ${EVAL_SOURCE_FILES} ${EVAL_HEADER_FILES} )

target_include_directories( eval PRIVATE "code/include" )

