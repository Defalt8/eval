#pragma once
#ifndef EVAL_DS_UNIQUE_HPP
#define EVAL_DS_UNIQUE_HPP

#include <cstddef>
#include <new>
#include "../common.hpp"

namespace eval {

template <typename T>
class Unique final
{
	T * m_ptr = nullptr;

 public:
	~Unique() noexcept 
	{
		this->destroy();
	}

	Unique() = default;

	Unique(Unique && unique) noexcept
		: m_ptr { unique.m_ptr }
	{
	    unique.m_ptr = nullptr;
	}

	Unique &
	operator=(Unique && rhs) noexcept
	{
		if(&rhs != this)
		{
			swap(m_ptr, rhs.m_ptr);
			rhs.destroy();
		}
		return *this;
	}

	void 
	destroy() noexcept
	{
		delete m_ptr;
	}

	T       * ptr()       noexcept { return m_ptr; }
	T const * ptr() const noexcept { return m_ptr; }

	template <typename U>
	U       * ptr()       noexcept { return dynamic_cast<U *>(m_ptr); }
	template <typename U>
	U const * ptr() const noexcept { return dynamic_cast<U *>(m_ptr); }

	T &
	ref() noexcept(false)
	{
		if(!m_ptr)
			throw exception::NullPointer();
		return *m_ptr;
	}

	T const &
	ref() const noexcept(false)
	{
		if(!m_ptr)
			throw exception::NullPointer();
		return *m_ptr;
	}

	template <typename U>
	U &
	ref() noexcept(false)
	{
		if(!m_ptr)
			throw exception::NullPointer();
		U * uptr_ = dynamic_cast<U *>(m_ptr);
		if(!uptr_)
			throw exception::InvalidCast();
		return *uptr_;
	}

	template <typename U>
	U const &
	ref() const noexcept(false)
	{
		if(!m_ptr)
			throw exception::NullPointer();
		U * uptr_ = dynamic_cast<U *>(m_ptr);
		if(!uptr_)
			throw exception::InvalidCast();
		return *uptr_;
	}

	T *
	operator->() noexcept(false)
	{
		if(!m_ptr)
			throw exception::NullPointer();
		return m_ptr;
	}

	T const *
	operator->() const noexcept(false)
	{
		if(!m_ptr)
			throw exception::NullPointer();
		return m_ptr;
	}

	explicit operator bool() const noexcept { return !!m_ptr; }
	bool operator!() const noexcept { return !m_ptr; }

};

} // namespace eval

#endif // EVAL_DS_UNIQUE_HPP