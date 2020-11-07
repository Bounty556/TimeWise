#pragma once

#include <Files/ControlsFile.h>
#include <Utility/Macros.h>
#include <Utility/Map.h>

namespace Soul
{
	namespace Tests
	{
		void MapTest()
		{
			MemoryManager::DrawMemory();

			{
				Map<String, int> stringIntMap;
				stringIntMap.AddPair(String("Test"), (int)5);
				Assert(*stringIntMap.Get(String("Test")) == 5);
			}

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

			MemoryManager::DrawMemory();
		}

		void ControlsFileTest()
		{
			MemoryManager::DrawMemory();
			{
				ControlsFile controlsFile("res/test2.controls");

				// TODO: Find out what is deteriorating the inner Map when GetInputValue is called

				Assert(controlsFile.GetInputValue("Shoot", 'c') == -1);
				Assert(controlsFile.GetInputValue("Shoot", 'a') == 3);
				Assert(controlsFile.GetInputValue("Shoot", 'k') == -1);
				Assert(controlsFile.GetInputValue("Shoot", 'm') == 1);
			}

			{
				ControlsFile controlsFile("res/test.controls");

				Assert(controlsFile.GetInputValue("Jump", 'k') == 12);
				Assert(controlsFile.GetInputValue("Jump", 'm') == -1);
				Assert(controlsFile.GetInputValue("Jump", 'a') == -1);
				Assert(controlsFile.GetInputValue("Jump", 'c') == 2);
				Assert(controlsFile.GetInputValue("Shoot", 'a') == 3);
				Assert(controlsFile.GetInputValue("Shoot", 'k') == -1);
				Assert(controlsFile.GetInputValue("Shoot", 'c') == -1);
				Assert(controlsFile.GetInputValue("Shoot", 'm') == 1);
			}
			MemoryManager::DrawMemory();
		}
	}
}