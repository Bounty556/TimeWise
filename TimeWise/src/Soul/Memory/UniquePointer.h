#pragma once

#include <Memory/MemoryManager.h>

namespace Soul
{
	template <class T>
	class UniquePointer
	{
	public:
		UniquePointer(T* pointer);
		UniquePointer(const UniquePointer<T>&) = delete;
		UniquePointer(UniquePointer<T>&& otherPointer);
		~UniquePointer();

		UniquePointer<T> operator=(const UniquePointer<T>&) = delete;

		T& operator->() const;
		T& operator*() const;
		T& operator[](unsigned int index) const;

	private:
		T* m_Pointer;
	};

	template <class T>
	UniquePointer<T>::UniquePointer(T* pointer) :
		m_Pointer(pointer)
	{

	}

	template <class T>
	UniquePointer<T>::UniquePointer(UniquePointer<T>&& otherPointer) :
		m_Pointer(otherPointer.m_Pointer)
	{
		otherPointer.m_Pointer = nullptr;
	}

	template <class T>
	UniquePointer<T>::~UniquePointer()
	{
		if (m_Pointer)
		{
			MemoryManager::FreeMemory(m_Pointer);
		}
	}

	template <class T>
	T& UniquePointer<T>::operator->() const
	{
		return *m_Pointer;
	}

	template <class T>
	T& UniquePointer<T>::operator*() const
	{
		return *m_Pointer;
	}

	template <class T>
	T& UniquePointer<T>::operator[](unsigned int index) const
	{
		return m_Pointer[index];
	}
}