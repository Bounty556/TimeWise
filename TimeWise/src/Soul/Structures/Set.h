#pragma once

#include <Structures/Vector.h>

namespace Soul
{
	// TODO: Reimplement this as a binary tree
	template <class T>
	class Set
	{
	public:
		Set(unsigned int capacity = 8);

		Set(const Set<T>&) = delete; // No copy constructor
		Set(Set<T>&& otherSet); // Move constructor

		Set& operator=(const Set<T>&) = delete; // No copy assignment

		T& operator[](unsigned int index) const;

		/*
		Adds a new element to the end of this Set.
		*/
		void Add(T& element);

		/*
		Gets the current number of elements stored in this Set.
		*/
		unsigned int Length() const;

	private:
		Vector<T> m_Vector;
	};

	template <class T>
	Set<T>::Set(unsigned int capacity) :
		m_Vector(capacity)
	{

	}

	template <class T>
	Set<T>::Set(Set<T>&& otherSet) :
		m_Vector(std::move(otherSet.m_Vector))
	{

	}

	template <class T>
	T& Set<T>::operator[](unsigned int index) const
	{
		return m_Vector[index];
	}

	template <class T>
	void Set<T>::Add(T& element)
	{
		for (unsigned int i = 0; i < m_Vector.Length(); ++i)
		{
			if (m_Vector[i] == element)
			{
				return;
			}
		}

		m_Vector.Push(element);
	}

	template <class T>
	unsigned int Set<T>::Length() const
	{
		return m_Vector.Length();
	}
}