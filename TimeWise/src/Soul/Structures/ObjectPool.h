#pragma once

#include <Memory/MemoryManager.h>
#include <Memory/UniquePointer.h>

namespace Soul
{
	/*
	The Object pool works via a queue that keeps a predetermined amount of pre-partitioned
	objects. Then, when needed, these predetermined objects can be accessed so that only up to
	the predetermined amount can exist. This means this object requires no form of repartitioning
	and can store objects sequentially for fast access.

	All objects in the object pool need to have default constructors.
	*/
	template <class T>
	class ObjectPool
	{
	public:
		/*
		Contain the actual elements of the object pool, as well as metadata such as if the element
		is currently live, or what the next free object in the pool is.
		*/
		template <class T>
		struct Object
		{
			~Object()
			{
				if (IsLive)
				{
					Element.~T();
				}
			}

			bool IsLive;
			union
			{
				T Element;
				Object* NextFree;
			};
		};

	public:
		ObjectPool(unsigned int objectCount);
		ObjectPool(const ObjectPool&) = delete;
		ObjectPool(ObjectPool&& otherPool);

		ObjectPool& operator=(const ObjectPool&) = delete;

		/*
		Gets a reference to the nth object in the Object pool, regardless of if it's live or not.
		*/
		const ObjectPool<T>::Object<T>& operator[](unsigned int index) const;

		/*
		Gets the current number of live objects in the pool.
		*/
		unsigned int Count() const;

		/*
		Gets the maximum number of objects that can be in the pool.
		*/
		unsigned int Capacity() const;

		/*
		Returns a pointer to a new object in the pool if there is any room for one. Otherwise,
		returns nullptr.
		*/
		T* RequestObject();

		/*
		Frees the object in the pool at the given location, if there is a live object there.
		*/
		void FreeObject(T* element);

		/*
		Clears out all objects in the pool, resets live object count to 0.
		*/
		void EmptyPool();

	private:
		unsigned int m_ObjectCount;
		unsigned int m_ObjectCapacity;
		UniquePointer<Object<T>> m_ObjectPool;
		Object<T>* m_FreeList;
	};

	template <class T>
	ObjectPool<T>::ObjectPool(unsigned int capacity) :
		m_ObjectCount(0),
		m_ObjectCapacity(capacity),
		m_ObjectPool(PartitionArray(ObjectPool<T>::Object<T>, m_ObjectCapacity)),
		m_FreeList(m_ObjectPool.Raw())
	{
		for (unsigned int i = 0; i < m_ObjectCapacity; ++i)
		{
			m_ObjectPool[i].IsLive = false;
			if (i + 1 < m_ObjectCapacity)
			{
				m_ObjectPool[i].NextFree = &m_ObjectPool[i + 1];
			}
			else
			{
				m_ObjectPool[i].NextFree = nullptr;
			}
		}
	}

	template <class T>
	ObjectPool<T>::ObjectPool(ObjectPool&& otherPool) :
		m_ObjectCapacity(otherPool.m_ObjectCapacity),
		m_ObjectCount(otherPool.m_ObjectCount),
		m_ObjectPool(std::move(otherPool.m_ObjectPool)),
		m_FreeList(m_ObjectPool)
	{
		otherPool.m_FreeList = nullptr;
	}

	template <class T>
	const ObjectPool<T>::Object<T>& ObjectPool<T>::operator[](unsigned int index) const
	{
		if (index < 0 || index >= m_ObjectCapacity)
		{
			SoulLogError("Object pool index out of bounds.");
			Assert(false);
		}
		
		return m_ObjectPool[index];
	}

	template <class T>
	unsigned int ObjectPool<T>::Count() const
	{
		return m_ObjectCount;
	}

	template <class T>
	unsigned int ObjectPool<T>::Capacity() const
	{
		return m_ObjectCapacity;
	}

	template <class T>
	T* ObjectPool<T>::RequestObject()
	{
		if (m_FreeList)
		{
			// Instantiate new object at the free list head.
			Object<T>* head = m_FreeList;
			m_FreeList = head->NextFree;
			new (&(head->Element)) T();
			head->IsLive = true;
			m_ObjectCount++;

			return &(head->Element);
		}

		return nullptr;
	}

	template <class T>
	void ObjectPool<T>::FreeObject(T* element)
	{
		// Find the object with the given element
		for (unsigned int i = 0; i < m_ObjectCapacity; ++i)
		{
			if (&m_ObjectPool[i].Element == element && m_ObjectPool[i].IsLive)
			{
				m_ObjectPool[i].Element.~T();
				memset(&(m_ObjectPool[i].Element), 0, sizeof(T));
				m_ObjectPool[i].IsLive = false;
				m_ObjectPool[i].NextFree = m_FreeList;
				m_FreeList = &m_ObjectPool[i];
				--m_ObjectCount;
				return;
			}
		}
	}

	template <class T>
	void ObjectPool<T>::EmptyPool()
	{
		for (unsigned int i = 0; i < m_ObjectCapacity; ++i)
		{
			if (m_ObjectPool[i].IsLive)
			{
				m_ObjectPool[i].Element.~T();
				memset(&(m_ObjectPool[i].Element), 0, sizeof(T));
				m_ObjectPool[i].IsLive = false;
			}
			if (i < m_ObjectCapacity - 1)
			{
				m_ObjectPool[i].NextFree = &m_ObjectPool[i + 1];
			}
			else
			{
				m_ObjectPool[i].NextFree = nullptr;
			}
		}
		m_ObjectCount = 0;
		m_FreeList = m_ObjectPool.Raw();
	}
}