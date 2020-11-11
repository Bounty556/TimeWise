#pragma once

#include <Logging/Logger.h>
#include <Memory/MemoryManager.h>
#include <Nodes/RectangleNode.h>
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
			ObjectPool<RectangleNode> pool(16);

			RectangleNode* node;
			for (unsigned int i = 0; i < 1000; ++i)
			{
				node = pool.RequestObject();
				Assert(node != nullptr);
				pool.FreeObject(node);
			}
		}

		static void PoolClearCount()
		{
			ObjectPool<RectangleNode> pool(16);
			Assert(pool.Count() == 0);

			while (pool.RequestObject());

			Assert(pool.Count() == 16);

			pool.EmptyPool();
			Assert(pool.Count() == 0);
		}

		static void ArrayOperator()
		{
			ObjectPool<RectangleNode> pool(16);

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
			ObjectPool<RectangleNode> pool(32);

			RectangleNode* one = pool.RequestObject();
			RectangleNode* two = pool.RequestObject();
			RectangleNode* three = pool.RequestObject();

			/*pool.FreeObject(one);
			pool.FreeObject(two);
			pool.FreeObject(three);*/
			pool.EmptyPool();

			pool.RequestObject();
			pool.RequestObject();
			pool.RequestObject();
		}
	};
}