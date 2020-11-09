#pragma once

#include <Strings/String.h>
#include <Utility/Macros.h>
#include <Utility/Map.h>

namespace Soul
{
	class MapTests
	{
	public:
		static void RunAllTests()
		{
			RunTest(BasicUse);
			RunTest(Repartition);
			RunTest(InternalMoveConstructors);
			RunTest(IntHashing);
			RunTest(GetKeys);
			RunTest(MapMoveConstructors);
			RunTest(MapElementDelete);
		}

	private:
	
		static void BasicUse()
		{
			Map<String, int> stringIntMap;
			stringIntMap.AddPair(String("Test"), (int)5);
		
			Assert(*stringIntMap.Get(String("Test")) == 5);
		}

		static void Repartition()
		{
			Map<String, int> stringIntMap;
			stringIntMap.AddPair(String("Test0"), (int)0);
			stringIntMap.AddPair(String("Test1"), (int)1);
			stringIntMap.AddPair(String("Test2"), (int)2);
			stringIntMap.AddPair(String("Test3"), (int)3);
			stringIntMap.AddPair(String("Test4"), (int)4);
			stringIntMap.AddPair(String("Test5"), (int)5);
			stringIntMap.AddPair(String("Test6"), (int)6);
			stringIntMap.AddPair(String("Test7"), (int)7);
			stringIntMap.AddPair(String("Test8"), (int)8);
			stringIntMap.AddPair(String("Test9"), (int)9);

			Assert(*stringIntMap.Get(String("Test0")) == 0);
			Assert(*stringIntMap.Get(String("Test1")) == 1);
			Assert(*stringIntMap.Get(String("Test2")) == 2);
			Assert(*stringIntMap.Get(String("Test3")) == 3);
			Assert(*stringIntMap.Get(String("Test4")) == 4);
			Assert(*stringIntMap.Get(String("Test5")) == 5);
			Assert(*stringIntMap.Get(String("Test6")) == 6);
			Assert(*stringIntMap.Get(String("Test7")) == 7);
			Assert(*stringIntMap.Get(String("Test8")) == 8);
			Assert(*stringIntMap.Get(String("Test9")) == 9);
		}

		static void InternalMoveConstructors()
		{
			Map<String, String> stringStringMap;
			stringStringMap.AddPair(String("Test0"), String("I am 0"));
			stringStringMap.AddPair(String("Test1"), String("I am 1"));
			stringStringMap.AddPair(String("Test2"), String("I am 2"));
			stringStringMap.AddPair(String("Test3"), String("I am 3"));
			stringStringMap.AddPair(String("Test4"), String("I am 4"));
			stringStringMap.AddPair(String("Test5"), String("I am 5"));
			stringStringMap.AddPair(String("Test6"), String("I am 6"));
			stringStringMap.AddPair(String("Test7"), String("I am 7"));
			stringStringMap.AddPair(String("Test8"), String("I am 8"));
			stringStringMap.AddPair(String("Test9"), String("I am 9"));

			Assert(*stringStringMap.Get(String("Test0")) == String("I am 0"));
			Assert(*stringStringMap.Get(String("Test1")) == String("I am 1"));
			Assert(*stringStringMap.Get(String("Test2")) == String("I am 2"));
			Assert(*stringStringMap.Get(String("Test3")) == String("I am 3"));
			Assert(*stringStringMap.Get(String("Test4")) == String("I am 4"));
			Assert(*stringStringMap.Get(String("Test5")) == String("I am 5"));
			Assert(*stringStringMap.Get(String("Test6")) == String("I am 6"));
			Assert(*stringStringMap.Get(String("Test7")) == String("I am 7"));
			Assert(*stringStringMap.Get(String("Test8")) == String("I am 8"));
			Assert(*stringStringMap.Get(String("Test9")) == String("I am 9"));
		}

		static void IntHashing()
		{
			Map<int, int> intIntMap;
			intIntMap.AddPair(0, 0);
			intIntMap.AddPair(1, 10);
			intIntMap.AddPair(2, 20);
			intIntMap.AddPair(3, 30);
			intIntMap.AddPair(4, 40);
			intIntMap.AddPair(5, 50);
			intIntMap.AddPair(6, 60);
			intIntMap.AddPair(7, 70);
			intIntMap.AddPair(8, 80);
			intIntMap.AddPair(9, 90);

			Assert(intIntMap.GetCount() == 10);

			intIntMap.Clear();

			Assert(intIntMap.GetCount() == 0);
		}

		static void GetKeys()
		{
			Map<String, int> stringIntMap;
			stringIntMap.AddPair(String("1"), 1);
			stringIntMap.AddPair(String("2"), 2);
			stringIntMap.AddPair(String("3"), 3);
			stringIntMap.AddPair(String("4"), 4);

			Vector<String*> keys = stringIntMap.GetKeys();
			Assert(*keys[0] == String("1"));
			Assert(*keys[1] == String("2"));
			Assert(*keys[2] == String("3"));
			Assert(*keys[3] == String("4"));
		}

		static void MapMoveConstructors()
		{
			Map<String, Map<String, int>> testMap;
			Map<String, int> innerMap1;
			innerMap1.AddPair("1", 1);
			innerMap1.AddPair("2", 2);
			innerMap1.AddPair("3", 3);
			innerMap1.AddPair("4", 4);
			Map<String, int> innerMap2;
			innerMap2.AddPair("1", 1);
			innerMap2.AddPair("2", 2);
			innerMap2.AddPair("3", 3);
			innerMap2.AddPair("4", 4);

			testMap.AddPair(String("FirstMap"), std::move(innerMap1));
			testMap.AddPair(String("SecondMap"), std::move(innerMap2));
			Map<String, Map<String, int>> testMap2(std::move(testMap));
		}

		static void MapElementDelete()
		{
			Map<String, int> map;
			map.AddPair("1", 1);
			map.AddPair("2", 2);
			map.AddPair("3", 3);
			map.AddPair("4", 4);

			map.RemovePair("1");
			Assert(map.Get("1") == nullptr);
			Assert(*(map.Get("2")) == 2);
			Assert(*(map.Get("3")) == 3);
			Assert(*(map.Get("4")) == 4);

			Map<String, int> resizedMap;
			resizedMap.AddPair("1", 1);
			resizedMap.AddPair("2", 2);
			resizedMap.AddPair("3", 3);
			resizedMap.AddPair("4", 4);
			resizedMap.AddPair("5", 5);
			resizedMap.AddPair("6", 6);
			resizedMap.AddPair("7", 7);
			resizedMap.AddPair("8", 8);
			resizedMap.AddPair("9", 9);
			resizedMap.AddPair("0", 0);

			resizedMap.RemovePair("6");
			resizedMap.RemovePair("9");

			Assert(*(resizedMap.Get("1")) == 1);
			Assert(*(resizedMap.Get("2")) == 2);
			Assert(*(resizedMap.Get("3")) == 3);
			Assert(*(resizedMap.Get("4")) == 4);
			Assert(*(resizedMap.Get("5")) == 5);
			Assert(resizedMap.Get("6") == nullptr);
			Assert(*(resizedMap.Get("7")) == 7);
			Assert(*(resizedMap.Get("8")) == 8);
			Assert(resizedMap.Get("9") == nullptr);
			Assert(*(resizedMap.Get("0")) == 0);
		}
	};
}