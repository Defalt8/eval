#pragma once
#ifndef EVAL_EVALUATOR_HPP
#define EVAL_EVALUATOR_HPP

#include "common.hpp"
#include "Operand.hpp"
#include "Operator.hpp"
#include "Operation.hpp"
#include "ds/Array.hpp"
#include "ds/String.hpp"
#include "ds/Unique.hpp"

namespace eval {

static constexpr size_t _Max_Operands  = 2048;
static constexpr size_t _Max_Operators = 2048;

class Evaluator
{
	Array<Unique<Operand>>  m_operands  { _Max_Operands };
	Array<Unique<Operator>> m_operators { _Max_Operators };

 public:
	~Evaluator() noexcept;
	Evaluator();
	Evaluator(Evaluator && evaluator) noexcept;
	
	void evaluate_args(int argc, char * argv[]) noexcept(false);
	void evaluate(String const & expression) noexcept(false);
};

} // namespace eval

#endif // EVAL_EVALUATOR_HPP