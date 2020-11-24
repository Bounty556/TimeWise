#pragma once

#include <Memory/MemoryManager.h>
#include <Memory/UniquePointer.h>
#include <Utility/Macros.h>

#include <memory>

namespace Soul
{
	/*
	This is to be used in place of the C Standard Template Library vectors. They should behave
	almost identically, but instead use our built-in memory arena. Thus for these to work, the
	MemoryManager class must have been initialized with Allocate().
	*/
	template <class T>
	class Vector
	{
	public:
		Vector(unsigned int capacity = 8);

		Vector(const Vector<T>&) = delete; // No copy constructor
		Vector(Vector<T>&& otherVector); // Move constructor

		Vector& operator=(const Vector<T>&) = delete; // No copy assignment

		T& operator[](unsigned int index) const;

		/*
		Adds a new element to the end of this vector.
		*/
		void Push(T& element);

		/*
		Adds a new element to the end of this vector.
		*/
		void Push(T&& element);
		
		/*
		Removes the element at the end of this vector.
		*/
		void Pop();

		/*
		Inserts an element at the given index.
		*/
		void Insert(unsigned int index, T& element);

		/*
		Inserts an element at the given index.
		*/
		void Insert(unsigned int index, T&& element);

		/*
		Returns the element at the end of this vector without removing it.
		*/
		const T& Peek() const;

		/*
		Removes the element that matches the given value and removes it from
		the vector, replacing it with the last element.
		*/
		void Remove(T& element);

		/*
		Gets the current number of elements stored in this vector.
		*/
		unsigned int Length() const;

		/*
		Removes all elements from this Vector.
		*/
		void Clear();

	private:
		void Resize(unsigned int newCapacity);

	private:
		/*
		The start of the memory block for this vector.
		*/
		UniquePointer<T> m_Memory;

		/*
		The number of elements currently stored in this vector.
		*/
		unsigned int m_Count;

		/*
		The number of elements we can store in this vector before needing to expand.
		*/
		unsigned int m_Capacity;

		/*
		The minimum number of elements we must partition space for for this vector.
		*/
		const unsigned int m_MinimumCapacity = 8;
	};

	template <class T>
	Vector<T>::Vector(unsigned int capacity) :
		m_Count(0),
		m_Memory(nullptr)
	{
		if (capacity < m_MinimumCapacity)
		{
			capacity = m_MinimumCapacity;
		}
		m_Capacity = capacity;

		m_Memory = PartitionArray(T, m_Capacity);
	}

	template <class T>
	Vector<T>::Vector(Vector<T>&& otherVector) :
		m_Capacity(otherVector.m_Capacity),
		m_Count(otherVector.m_Count),
		m_Memory(std::move(otherVector.m_Memory))
	{

	}

	template <class T>
	T& Vector<T>::operator[](unsigned int index) const
	{
		Assert(index >= 0 && index < m_Count);
		return m_Memory[index];
	}

	template <class T>
	void Vector<T>::Push(T& element)
	{
		// Check to see if increasing our count hits our capacity limit.
		if (m_Count == m_Capacity)
		{
			Resize(m_Capacity * 2);
		}

		// Put our new element at m_Count, then increase
		new (&m_Memory[m_Count]) T(std::move(element));
		m_Count++;
	}

	template <class T>
	void Vector<T>::Push(T&& element)
	{
		// Check to see if increasing our count hits our capacity limit.
		if (m_Count == m_Capacity)
		{
			Resize(m_Capacity * 2);
		}

		// Put our new element at m_Count, then increase
		new (&m_Memory[m_Count]) T(std::move(element));
		m_Count++;
	}

	template <class T>
	void Vector<T>::Pop()
	{
		Assert(m_Count > 0);
	
		m_Count--;
		m_Memory[m_Count].~T();
		memset(&(m_Memory[m_Count]), 0, sizeof(T));
	}

	template <class T>
	void Vector<T>::Insert(unsigned int index, T& element)
	{
		if (index > m_Count)
		{
			SoulLogWarning("Index out of bounds during vector insertion");
			return;
		}

		// Check to see if increasing our count hits our capacity limit.
		if (m_Count == m_Capacity)
		{
			Resize(m_Capacity * 2);
		}

		for (unsigned int i = m_Count; i > index; --i)
		{
			memset(&m_Memory[i], 0, sizeof(T));
			new (&m_Memory[i]) T(std::move(m_Memory[i - 1]));
		}


		memset(&m_Memory[index], 0, sizeof(T));
		new (&m_Memory[index]) T(std::move(element));
		++m_Count;
	}

	template <class T>
	void Vector<T>::Insert(unsigned int index, T&& element)
	{
		if (index > m_Count)
		{
			SoulLogWarning("Index out of bounds during vector insertion");
			return;
		}

		// Check to see if increasing our count hits our capacity limit.
		if (m_Count == m_Capacity)
		{
			Resize(m_Capacity * 2);
		}

		for (unsigned int i = m_Count; i > index; --i)
		{
			memset(&m_Memory[i], 0, sizeof(T));
			new (&m_Memory[i]) T(std::move(m_Memory[i - 1]));
		}


		memset(&m_Memory[index], 0, sizeof(T));
		new (&m_Memory[index]) T(std::move(element));
		++m_Count;
	}

	template <class T>
	const T& Vector<T>::Peek() const
	{
		Assert(m_Count > 0);
		return m_Memory[m_Count - 1];
	}

	template <class T>
	void Vector<T>::Remove(T& element)
	{
		// Search linearly for the element
		for (unsigned int i = 0; i < m_Count; ++i)
		{
			if (m_Memory[i] == element)
			{
				if (i == m_Count - 1)
				{
					--m_Count;
				}
				else
				{
					m_Memory[i] = std::move(m_Memory[m_Count - 1]);
					--m_Count;
				}
			}
		}
	}

	template <class T>
	unsigned int Vector<T>::Length() const
	{
		return m_Count;
	}

	template <class T>
	void Vector<T>::Clear()
	{
		m_Memory = PartitionArray(T, m_Capacity);
		m_Count = 0;
	}

	template <class T>
	void Vector<T>::Resize(unsigned int newCapacity)
	{
		// Acquire new memory
		T* newMemory = PartitionArray(T, newCapacity);

		for (unsigned int i = 0; i < m_Capacity; ++i)
		{
			new (&newMemory[i]) T(std::move(m_Memory[i]));
		}

		m_Memory = newMemory;
		m_Capacity = newCapacity;
	}
}