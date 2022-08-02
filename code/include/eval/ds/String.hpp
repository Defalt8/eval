#pragma once
#ifndef EVAL_DS_STRING_HPP
#define EVAL_DS_STRING_HPP

#include <cstddef>
#include <cstring>
#include <cstdio>
#include <new>
#include "../common.hpp"
#include "exceptions.hpp"

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

	String(char const * begin_, char const * end_, size_t size_ = -1) noexcept(false)
		: m_begin { begin_ ? _allocate((size_ = size_t(end_ - begin_) + 1)) : nullptr }
		, m_end   { m_begin ? (m_begin + size_) : nullptr }
	{
		if(m_begin)
		{
			size_t length_ = size_ - 1;
			for(size_t i = 0; i < length_; ++i)
				m_begin[i] = begin_[i];
			m_begin[length_] = '\0';
		}
	}

	String(char const * pstring, size_t size_ = -1) noexcept(false)
		: m_begin { pstring ? _allocate((size_ = strlen(pstring) + 1)) : nullptr }
		, m_end   { m_begin ? (m_begin + size_) : nullptr }
	{
		if(m_begin)
		  #ifdef _MSC_VER
			strncpy_s(m_begin, size_, pstring, size_);
		  #else
			strncpy(m_begin, pstring, size_);
		  #endif
	}

	String &
	operator=(String && rhs) noexcept
	{
		if(&rhs != this)
		{
			this->~String();
			new ((void *)this) String(move(rhs));
		}
		return *this;
	}

	String &
	operator=(String const & rhs) noexcept(false)
	{
		if(&rhs != this)
		{
			this->~String();
			new ((void *)this) String(rhs);
		}
		return *this;
	}

	void 
	destroy() noexcept
	{
		if(m_begin)
		{
			_deallocate(m_begin);
			m_begin = nullptr;
			m_end   = nullptr;
		}
	}

	template <typename... Args>
	static String
	format(size_t size_, char const * format_, Args &&... args) noexcept
	{
		String string { size_ };
		int written = snprintf(&string[0], size_, format_, static_cast<Args&&>(args)...);
		return String(&string[0], &string[written > 0 ? written : 0]);
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
		if(!m_begin)
			return !rhs.m_begin;
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


static inline size_t 
hash(String const & string) noexcept
{
	static constexpr size_t _prime_squares[127] { 1, 9, 25, 49, 121, 169, 289, 361, 529, 841
		, 961, 1369, 1681, 1849, 2209, 2809, 3481, 3721, 4489, 5041, 5329, 6241, 6889, 7921
		, 9409, 10201, 10609, 11449, 11881, 12769, 16129, 17161, 18769, 19321, 22201, 22801
		, 24649, 26569, 27889, 29929, 32041, 32761, 36481, 37249, 38809, 39601, 44521, 49729
		, 51529, 52441, 54289, 57121, 58081, 63001, 66049, 69169, 72361, 73441, 76729, 78961
		, 80089, 85849, 94249, 96721, 97969, 100489, 109561, 113569, 120409, 121801, 124609
		, 128881, 134689, 139129, 143641, 146689, 151321, 157609, 160801, 167281, 175561
		, 177241, 185761, 187489, 192721, 196249, 201601, 208849, 212521, 214369, 218089
		, 229441, 237169, 241081, 249001, 253009, 259081, 271441, 273529, 292681, 299209
		, 310249, 316969, 323761, 326041, 332929, 344569, 351649, 358801, 361201, 368449
		, 375769, 380689, 383161, 398161, 410881, 413449, 418609, 426409, 434281, 436921
		, 452929, 458329, 466489, 477481, 491401, 502681 };
	size_t hash_ = 0;
	size_t length = string.length();
	char const * cstr = &string[0];
    for(size_t i = 0; i < length; ++i)
        hash_ += size_t(cstr[0]) * _prime_squares[i % 127];
	return hash_;
}

} // namespace eval

#endif // EVAL_DS_STRING_HPP