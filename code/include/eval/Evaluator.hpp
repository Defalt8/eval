#pragma once
#ifndef EVAL_EVALUATOR_HPP
#define EVAL_EVALUATOR_HPP

#include "common.hpp"
#include "Operand.hpp"
#include "Operator.hpp"
#include "ds/Unique.hpp"
#include "ds/Array.hpp"
#include "ds/AssociativeArray.hpp"
#include "ds/String.hpp"

namespace eval {

static constexpr size_t _Max_Variables  = 1024;
static constexpr size_t _Max_Functions  = 1024;
static constexpr size_t _Max_Operands   = 2048;
static constexpr size_t _Max_Operators  = 2048;

class Evaluator
{
	using variables_t  = AssociativeArray<String,operand::Value>;
	using functions_t  = AssociativeArray<String,op::Function>;
	using operators_t  = Array<Unique<Operator>>;
	using operands_t   = Array<Unique<Operand>>;

	variables_t  m_variables  { _Max_Variables };
	functions_t  m_functions  { _Max_Functions };
	operators_t  m_operators  { _Max_Operators };
	operands_t   m_operands   { _Max_Operands  };

 public:
	~Evaluator() noexcept;
	Evaluator();
	Evaluator(Evaluator && evaluator) noexcept;
	
	value_t evaluate_args(int argc, char * argv[]) noexcept(false);
	value_t evaluate(String const & expression) noexcept(false);
	bool is_valid(String const & expression) const noexcept;
	bool is_variable(String const & operand) const noexcept;
	bool is_function(String const & operand) const noexcept;

	variables_t       & variables()       noexcept;
	variables_t const & variables() const noexcept;
	functions_t       & functions()       noexcept;
	functions_t const & functions() const noexcept;
};

} // namespace eval

#endif // EVAL_EVALUATOR_HPP