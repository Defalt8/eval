#pragma once
#ifndef EVAL_OPERAND_HPP
#define EVAL_OPERAND_HPP

#include "common.hpp"
#include "ds/String.hpp"

namespace eval {

enum class OperandType
{
	  Unknown
	, Value
	, Reference
};

class Operand 
{
 public:
	virtual ~Operand() = default;
	Operand() noexcept = default;
	
	virtual OperandType type() const noexcept = 0;
	virtual String      id()   const noexcept = 0;

};

namespace operand {

class Value final : public Operand
{
	String    m_id {};
	value_t m_value {};

 public:
	Value() noexcept;
	Value(String id, value_t value) noexcept;

	OperandType type() const noexcept override;
	String      id()   const noexcept override;
	
	value_t & value() noexcept;
	value_t const & value() const noexcept;

};

class Reference final : public Operand
{
	String    m_id {};
	Operand * m_reference = nullptr;

 public:
	Reference() noexcept;
	Reference(String id, Operand & reference) noexcept;

	OperandType type() const noexcept override;
	String      id()   const noexcept override;
	
	Operand *       reference()       noexcept;
	Operand const * reference() const noexcept;
	
	value_t &       value()       noexcept(false);
	value_t const & value() const noexcept(false);

};

} // namespace operand

} // namespace eval

#endif // EVAL_OPERAND_HPP