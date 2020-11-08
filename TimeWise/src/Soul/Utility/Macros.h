#pragma once

#define Kilobytes(x) (x * 1024)
#define Megabytes(x) (Kilobytes(x) * 1024)
#define Gigabytes(x) (Megabytes(x) * 1024)

#define Assert(x) \
if (x) \
	{} \
else {*((int*)0) = 0;}

#define RunTest(x) SoulLogInfo("Running test " #x); \
MemoryManager::DrawMemory(); \
x(); \
MemoryManager::DrawMemory()