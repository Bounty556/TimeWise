#pragma once

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
		Vector(Vector<T>&&) = delete; // No move constructor

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
		Removes and returns the element at the end of this vector.
		*/
		T&& Pop();

		/*
		Returns the element at the end of this vector without removing it.
		*/
		const T& Peek() const;

		/*
		Gets the current number of elements stored in this vector.
		*/
		unsigned int Count() const;

	private:
		void Resize();

	private:
		/*
		The start of the memory block for this vector.
		*/
		T* m_Memory;

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
}