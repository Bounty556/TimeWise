#pragma once

#define Kilobytes(x) (x * 1024)
#define Megabytes(x) (Kilobytes(x) * 1024)
#define Gigabytes(x) (Megabytes(x) * 1024)

#define ByteDistance(x, y) ((unsigned int)y - (unsigned int)x)

#define Assert(x) \
if (x) \
	{} \
else {*((int*)0) = 0;}

#define RunTest(x, ...) SoulLogInfo("Running test " #x); \
MemoryManager::DrawMemory(); \
x(__VA_ARGS__); \
MemoryManager::DrawMemory()