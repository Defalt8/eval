#pragma once
#ifndef EVAL_DS_MAP_ARRAY_HPP
#define EVAL_DS_MAP_ARRAY_HPP

#include <cstddef>
#include <new>
#include "../common.hpp"
#include "Array.hpp"

namespace eval {

template <typename Key, typename Value>
struct Entry
{
	Key   key   {};
	Value value {};
	bool occupied = false;
};

template <typename Key, typename Value>
class AssociativeArray final
{
	Array<Entry<Key,Value>> m_entries {};

 public:
	~AssociativeArray() noexcept 
	{
		this->destroy();
	}

	AssociativeArray() = default;

	AssociativeArray(AssociativeArray && associative_rray) noexcept
		: m_entries { move(associative_rray.m_entries) }
	{}

	AssociativeArray(size_t entries_size_) noexcept(false)
		: m_entries { entries_size_ }
	{}

	AssociativeArray &
	operator=(AssociativeArray && rhs) noexcept
	{
		if(&rhs != this)
		{
			this->~AssociativeArray();
			new (this) AssociativeArray(move(rhs));
		}
		return *this;
	}

	void 
	destroy() noexcept
	{
		m_entries.destroy();
	}

	Value &
	operator[](Key const & key) noexcept(false)
	{
		if(!m_entries)
			throw eval::exception::NullPointer();
		size_t hash_ = hash(key);
		size_t size_ = m_entries.size();
		size_t i = hash_ % size_;
		for(; i < size_; ++i)
		{
			if(!m_entries[i].occupied)
			{
				m_entries[i].key = key;
				m_entries[i].occupied = true;
				break;
			}
			else if(m_entries[i].key == key)
				break;
		}
		if(i == size_ && (hash_ % size_) > 0)
		{
			i = (hash_ % size_) - 1;
			for(;; --i)
			{
				if(!m_entries[i].occupied)
				{
					m_entries[i].key = key;
					m_entries[i].occupied = true;
					break;
				}
				else if(m_entries[i].key == key)
					break;
				if(i == 0)
				{
					i = size_;
					break;
				}
			}
		}
		if(i >= size_)
			throw exception::EntriesFull();
		return m_entries[i].value;
	}

	Value const &
	operator[](Key const & key) const noexcept(false)
	{
		if(!m_entries)
			throw eval::exception::NullPointer();
		size_t hash_ = hash(key);
		size_t size_ = m_entries.size();
		size_t i = hash_ % size_;
		for(; i < size_; ++i)
		{
			if(!m_entries[i].occupied)
			{
				throw exception::EntryNotFound();
				break;
			}
			else if(m_entries[i].key == key)
				break;
		}
		if(i == size_ && (hash_ % size_) > 0)
		{
			i = (hash_ % size_) - 1;
			for(;; --i)
			{
				if(!m_entries[i].occupied)
				{
					throw exception::EntryNotFound();
					break;
				}
				else if(m_entries[i].key == key)
					break;
				if(i == 0)
				{
					i = size_;
					break;
				}
			}
		}
		if(i >= size_)
			throw exception::EntryNotFound();
		return m_entries[i].value;
	}

	size_t size() const noexcept { return size_t(m_entries.size()); }

	Entry<Key,Value> * begin() noexcept { return m_entries.begin(); }
	Entry<Key,Value> * end()   noexcept { return m_entries.end(); }
	Entry<Key,Value> const * begin() const noexcept { return m_entries.begin(); }
	Entry<Key,Value> const * end()   const noexcept { return m_entries.end(); }

	explicit operator bool() const noexcept { return bool(m_entries); }
	bool operator!() const noexcept { return !m_entries; }

};

} // namespace eval

#endif // EVAL_DS_MAP_ARRAY_HPP