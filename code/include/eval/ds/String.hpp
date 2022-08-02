#pragma once
#ifndef EVAL_DS_STRING_HPP
#define EVAL_DS_STRING_HPP

#include <cstddef>
#include <cstring>
#include <new>
#include "../common.hpp"

namespace eval {

class String final
{
	char * m_begin = nullptr;
	char * m_end   = nullptr;

	char * 
	_allocate(size_t count_) noexcept(false)
	{
		if(count_ == 0) 
			return nullptr;
		void * block = ::operator new(count_ * sizeof(char), std::nothrow);
		if(!block) 
			throw eval::exception::AllocationFailure();
		return static_cast<char *>(block);
	}

	void
	_deallocate(void * block) noexcept
	{
		::operator delete(block);
	}

 public:
	~String() noexcept 
	{
		this->destroy();
	}

	String() = default;

	String(String && string) noexcept
		: m_begin { string.m_begin }
		, m_end   { string.m_end }
	{
	    string.m_begin = nullptr;
	    string.m_end = nullptr;
	}

	String(String const & string) noexcept(false)
		: m_begin { _allocate(string.size()) }
		, m_end   { m_begin ? (m_begin + string.size()) : nullptr }
	{
		if(m_begin)
		{
			size_t size_ = size_t(m_end - m_begin);
			for(size_t i = 0; i < size_; ++i)
				m_begin[i] = string.m_begin[i];
		}
	}

	String(size_t size_) noexcept(false)
		: m_begin { _allocate(size_) }
		, m_end   { m_begin ? (m_begin + size_) : nullptr }
	{
		if(m_begin)
		{
			for(size_t i = 0; i < size_; ++i)
				m_begin[i] = '\0';
		}
	}

	String(char const * pstring, size_t size_ = -1) noexcept(false)
		: m_begin { _allocate((size_ = strlen(pstring) + 1)) }
		, m_end   { m_begin ? (m_begin + size_) : nullptr }
	{
		if(m_begin)
			strncpy_s(m_begin, size_, pstring, size_);
	}

	String &
	operator=(String && rhs) noexcept
	{
		if(&rhs != this)
		{
			this->~String();
			new (this) String(move(rhs));
		}
		return *this;
	}

	String &
	operator=(String const & rhs) noexcept(false)
	{
		if(&rhs != this)
		{
			this->~String();
			new (this) String(rhs);
		}
		return *this;
	}

	void 
	destroy() noexcept
	{
		if(m_begin)
			_deallocate(m_begin);
	}

	char &
	operator[](size_t index) noexcept(false)
	{
		if(!m_begin || index >= size())
			throw eval::exception::IndexOutOfBounds();
		return m_begin[index];
	}

	char const &
	operator[](size_t index) const noexcept(false)
	{
		if(!m_begin || index >= size())
			throw eval::exception::IndexOutOfBounds();
		return m_begin[index];
	}

	bool
	operator==(String const & rhs) const noexcept
	{
		return 0 == strncmp(m_begin, rhs.m_begin, min(size(), rhs.size()));
	}

	bool
	operator!=(String const & rhs) const noexcept
	{
		return !operator==(rhs);
	}

	size_t size() const noexcept { return size_t(m_end - m_begin); }
	size_t length() const noexcept { return m_begin ? (size() - 1) : 0; }
	
	char * str() noexcept { return m_begin; }
	char const * cstr() const noexcept { return m_begin; }

	char * begin() noexcept { return m_begin; }
	char * end()   noexcept { return m_end; }
	char const * begin() const noexcept { return m_begin; }
	char const * end()   const noexcept { return m_end; }

	explicit operator bool() const noexcept { return !!m_begin; }
	bool operator!() const noexcept { return !m_begin; }
	
};

} // namespace eval

#endif // EVAL_DS_STRING_HPP