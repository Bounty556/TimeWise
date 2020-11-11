#pragma once

namespace Soul
{
	/*
	The Object pool works via a queue that keeps a predetermined amount of pre-partitioned
	objects. Then, when needed, these predetermined objects can be accessed so that only up to
	the predetermined amount can exist. This means this object requires no form of repartitioning
	and can store objects sequentially for fast access.
	*/
	template <class T>
	class ObjectPool
	{
	public:
		ObjectPool(unsigned int objectCount);
		~ObjectPool();

		unsigned int Count();

		T* RequestObject();

		void FreeObject();

	private:
		unsigned int m_ObjectCount;
		T* m_ObjectPool;
		unsigned int* m_FreeList;
		unsigned int*
	};
}