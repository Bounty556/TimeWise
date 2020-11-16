#pragma once

#include <Other/Logger.h>
#include <Memory/MemoryManager.h>
#include <Structures/ObjectPool.h>
#include <Utility/Macros.h>

namespace Soul
{
	class ObjectPoolTests
	{
	public:
		static void RunAllTests()
		{
			RunTest(RectangleNodePool);
			RunTest(PoolClearCount);
			RunTest(ArrayOperator);
			RunTest(HalfFullPool);
		}

	private:
		static void RectangleNodePool()
		{
			ObjectPool<String> pool(16);

			String* node;
			for (unsigned int i = 0; i < 1000; ++i)
			{
				node = pool.RequestObject();
				Assert(node != nullptr);
				pool.FreeObject(node);
			}
		}

		static void PoolClearCount()
		{
			ObjectPool<String> pool(16);
			Assert(pool.Count() == 0);

			while (pool.RequestObject());

			Assert(pool.Count() == 16);

			pool.EmptyPool();
			Assert(pool.Count() == 0);
		}

		static void ArrayOperator()
		{
			ObjectPool<String> pool(16);

			for (unsigned int i = 0; i < 16; ++i)
			{
				Assert(!pool[i].IsLive);
			}

			while (pool.RequestObject());

			for (unsigned int i = 0; i < 16; ++i)
			{
				Assert(pool[i].IsLive);
			}
		}

		static void HalfFullPool()
		{
			ObjectPool<String> pool(32);

			String* one = pool.RequestObject();
			String* two = pool.RequestObject();
			String* three = pool.RequestObject();

			pool.EmptyPool();

			Assert(one == pool.RequestObject());
			Assert(two == pool.RequestObject());
			Assert(three == pool.RequestObject());
		}
	};
}