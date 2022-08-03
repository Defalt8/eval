#pragma once
#ifndef EVAL_EVALUATOR_HPP
#define EVAL_EVALUATOR_HPP

#include "common.hpp"
#include "Operand.hpp"
#include "ds/Unique.hpp"
#include "ds/Array.hpp"
#include "ds/AssociativeArray.hpp"
#include "ds/String.hpp"

namespace eval {

static constexpr size_t _Max_Variables  = 1024;
static constexpr size_t _Max_Functions  = 1024;
static constexpr size_t _Max_Operands   = 2048;
static constexpr size_t _Max_Operators  = 2048;

struct Function 
{
	using callable_t = value_t(*)(value_t);

	callable_t function    = nullptr; 
	String     description {}; 
};

class Evaluator
{
 public:
	using func_t = Function;
	using variables_t  = AssociativeArray<String,operand::Value>;
	using functions_t  = AssociativeArray<String,func_t>;

 private:
	variables_t  m_variables  { _Max_Variables };
	functions_t  m_functions  { _Max_Functions };

 public:
	~Evaluator() noexcept;
	Evaluator();
	Evaluator(Evaluator && evaluator) noexcept;
	
	// will concat and strip whitespaces and quotes '" 
	value_t evaluate_args(int argc, char * argv[]) noexcept(false);
	// expression must be a stripped string. no whitespaces in between
	value_t evaluate(String const & expression) noexcept(false);
	bool is_variable(String const & operand) const noexcept;
	bool is_function(String const & operand) const noexcept;
	void list_variables() const noexcept;
	void list_functions() const noexcept;

	variables_t       & variables()       noexcept;
	variables_t const & variables() const noexcept;
	functions_t       & functions()       noexcept;
	functions_t const & functions() const noexcept;
};


extern String stripped(String const & string) noexcept(false);

} // namespace eval

#endif // EVAL_EVALUATOR_HPP