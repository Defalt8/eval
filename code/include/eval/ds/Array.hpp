#pragma once
#ifndef EVAL_DS_ARRAY_HPP
#define EVAL_DS_ARRAY_HPP

#include <cstddef>
#include <new>
#include "../common.hpp"
#include "exceptions.hpp"

namespace eval {

template <typename E>
class Array final
{
	E * m_begin = nullptr;
	E * m_end   = nullptr;

	E * 
	_allocate(size_t count_) noexcept(false)
	{
		if(count_ == 0) 
			return nullptr;
		void * block = ::operator new(count_ * sizeof(E), std::nothrow);
		if(!block) 
			throw eval::exception::AllocationFailure();
		return static_cast<E *>(block);
	}

	void
	_deallocate(void * block) noexcept
	{
		::operator delete(block);
	}

 public:
	~Array() noexcept 
	{
		this->destroy();
	}

	Array() = default;

	Array(Array && array) noexcept
		: m_begin { array.m_begin }
		, m_end   { array.m_end }
	{
	    array.m_begin = nullptr;
	    array.m_end = nullptr;
	}

	template <typename T = E, enable_if_t<IsConstructible<T, T const &>::value,int> = 0>
	Array(Array<T> const & array) noexcept(false)
		: m_begin { _allocate(array.size()) }
		, m_end   { m_begin ? (m_begin + array.size()) : nullptr }
	{
		if(m_begin)
		{
			size_t size_ = size_t(m_end - m_begin);
			for(size_t i = 0; i < size_; ++i)
				new ((void *)&m_begin[i]) E { static_cast<E>(array.m_begin[i]) };
		}
	}

	Array(size_t size_) noexcept(false)
		: m_begin { _allocate(size_) }
		, m_end   { m_begin ? (m_begin + size_) : nullptr }
	{
		if(m_begin)
		{
			for(size_t i = 0; i < size_; ++i)
				new ((void *)&m_begin[i]) E;
		}
	}

	template <typename... Args>
	Array(size_t size_, Args &&... args) noexcept(false)
		: m_begin { _allocate(size_) }
		, m_end   { m_begin ? (m_begin + size_) : nullptr }
	{
		if(m_begin)
		{
			for(size_t i = 0; i < size_; ++i)
				new ((void *)&m_begin[i]) E { static_cast<Args&&>(args)... };
		}
	}

	Array &
	operator=(Array && rhs) noexcept
	{
		if(&rhs != this)
		{
			this->~Array();
			new ((void *)this) Array(move(rhs));
		}
		return *this;
	}

	Array &
	operator=(Array const & rhs) noexcept(false)
	{
		if(&rhs != this)
		{
			this->~Array();
			new ((void *)this) Array(rhs);
		}
		return *this;
	}

	void 
	destroy() noexcept
	{
		if(m_begin)
		{
			for(E * it = m_begin; it < m_end; ++it)
				it->~E();
			_deallocate(m_begin);
			m_begin = nullptr;
			m_end   = nullptr;
		}
	}

	E &
	operator[](size_t index) noexcept(false)
	{
		if(!m_begin || index >= size())
			throw eval::exception::IndexOutOfBounds();
		return m_begin[index];
	}

	E const &
	operator[](size_t index) const noexcept(false)
	{
		if(!m_begin || index >= size())
			throw eval::exception::IndexOutOfBounds();
		return m_begin[index];
	}

	size_t size() const noexcept { return size_t(m_end - m_begin); }

	E * begin() noexcept { return m_begin; }
	E * end()   noexcept { return m_end; }
	E const * begin() const noexcept { return m_begin; }
	E const * end()   const noexcept { return m_end; }

	explicit operator bool() const noexcept { return !!m_begin; }
	bool operator!() const noexcept { return !m_begin; }

};

} // namespace eval

#endif // EVAL_DS_ARRAY_HPP