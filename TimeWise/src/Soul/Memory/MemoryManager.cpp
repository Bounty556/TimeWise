#include "MemoryManager.h"

#include <stdlib.h>

#include <Utility/Macros.h>

namespace Soul
{
	unsigned char* MemoryManager::m_Memory;
	void* MemoryManager::m_StableMemoryStart;
	void* MemoryManager::m_StableMemoryEnd;

	void MemoryManager::Allocate(size_t bytes)
	{
		m_Memory = (unsigned char*)malloc(bytes);
		m_StableMemoryStart = m_Memory + Megabytes(2);
		m_StableMemoryEnd = m_Memory + bytes;

		// Create our 0th node at the 2MB mark
		MemoryNode* memoryNode = (MemoryNode*)m_StableMemoryStart;
		memoryNode->BlockSize = bytes - Megabytes(2);
		memoryNode->NextNode = nullptr;
	}

	void MemoryManager::Deallocate()
	{
		free((void*)m_Memory);
	}

	// TODO: We should be finding the smallest free block possible and partitioning there 
	//       first, saving the bigger blocks for larger partitions
	void* MemoryManager::PartitionMemory(unsigned int bytes, unsigned int count)
	{
		MemoryNode* currentNode = (MemoryNode*)m_StableMemoryStart;

		// Need more bytes to store the header for the partition we're making
		unsigned int actualBytes = (bytes * count) + sizeof(PartitionHeader); 

		while (currentNode)
		{
			// If we were to store memory here, can we keep our node?
			if (currentNode->BlockSize - sizeof(MemoryNode*) >= actualBytes)
			{
				void* location = ((unsigned char*)currentNode) + (currentNode->BlockSize - actualBytes);

				// Initialize newly partitioned memory to 0
				memset(location, 0, actualBytes);

				PartitionHeader* header = (PartitionHeader*)location;
				header->Bytes = actualBytes;
				header->Count = count;
				location = (unsigned char*)location + sizeof(PartitionHeader);

				currentNode->BlockSize -= actualBytes;

				return location;
			}
			// In this scenario, we can't keep our node - repair nodes afterwards
			else if (currentNode->BlockSize >= actualBytes)
			{
				// If we try to remove our 0th node everything will break...
				Assert(currentNode != m_StableMemoryStart);

				RemoveNode(currentNode);

				void* location = currentNode;

				// Initialize newly partitioned memory to 0
				memset(location, 0, currentNode->BlockSize);

				PartitionHeader* header = (PartitionHeader*)location;
				header->Bytes = currentNode->BlockSize;
				header->Count = count;
				location = (unsigned char*)location + sizeof(PartitionHeader);

				return location;
			}

			currentNode = currentNode->NextNode;
		}

		// We couldn't find a valid memory block
		SoulLogError("Failed to allocate %d bytes.", bytes);
		Assert(false);
		return (void*)nullptr;
	}

	unsigned int MemoryManager::GetByteSize(void* location)
	{
		Assert(location >= m_StableMemoryStart);
		Assert(location < m_StableMemoryEnd);

		// Back newLocation up to where we put the header
		PartitionHeader* header = (PartitionHeader*)((unsigned char*)location - sizeof(PartitionHeader));
		return header->Bytes - sizeof(PartitionHeader);
	}

	unsigned int MemoryManager::GetTotalPartitionedMemory()
	{
		unsigned int freeBytes = GetTotalFreeMemory();
		unsigned int partitionedBytes = (unsigned int)m_StableMemoryEnd - (unsigned int)m_StableMemoryStart - freeBytes;

		return partitionedBytes;
	}

	unsigned int MemoryManager::GetTotalFreeMemory()
	{
		MemoryNode* currentNode = (MemoryNode*)m_StableMemoryStart;
		unsigned int freeBytes = currentNode->BlockSize;

		while (currentNode->NextNode)
		{
			currentNode = currentNode->NextNode;
			freeBytes += currentNode->BlockSize;
		}

		return freeBytes;
	}

	void MemoryManager::DrawMemory()
	{
		SoulLogInfo("%d bytes available, %d bytes used. There are %d nodes in memory.", GetTotalFreeMemory(), GetTotalPartitionedMemory(), CountNodes());
	}

	void MemoryManager::RemoveNode(MemoryNode* removedNode)
	{
		MemoryNode* startNode = (MemoryNode*)m_StableMemoryStart;

		while (startNode->NextNode != nullptr)
		{
			if (startNode->NextNode == removedNode)
				startNode->NextNode = removedNode->NextNode;
		}
	}

	void MemoryManager::AddNode(void* location)
	{
		// Back newLocation up to where we put the header
		void* newLocation = (unsigned char*)location - sizeof(PartitionHeader);
		unsigned int size = ((PartitionHeader*)newLocation)->Bytes;

		// Create a new memory node at the given location
		MemoryNode* newNode = (MemoryNode*)newLocation;
		newNode->BlockSize = size;

		MemoryNode* previousNode = (MemoryNode*)m_StableMemoryStart;
		MemoryNode* currentNode = (MemoryNode*)m_StableMemoryStart;
		while (currentNode->NextNode)
		{
			currentNode = currentNode->NextNode;

			// We passed the new Node, reconstruct
			if (newNode < currentNode)
			{
				bool didCombine = false;
				// Check to see if newNode and currentNode can be combined
				if ((unsigned char*)newNode + newNode->BlockSize == (unsigned char*)currentNode)
				{
					newNode->BlockSize += currentNode->BlockSize;
					newNode->NextNode = currentNode->NextNode;
					previousNode->NextNode = newNode;
					didCombine = true;
				}

				// Check to see if previousNode and newNode can be combined
				if ((unsigned char*)previousNode + previousNode->BlockSize == (unsigned char*)newNode)
				{
					previousNode->BlockSize += newNode->BlockSize;
					if (didCombine)
					{
						previousNode->NextNode = newNode->NextNode;
					}
				}
				else
				{
					previousNode->NextNode = newNode;
					if (!didCombine)
					{
						newNode->NextNode = currentNode;
					}
				}
				return;
			}

			previousNode = currentNode;
		}

		// If we still haven't found this new node, it must be at the end
		if ((unsigned char*)currentNode + currentNode->BlockSize == (unsigned char*)newNode)
		{
			currentNode->BlockSize += newNode->BlockSize;
		}
		else
		{
			currentNode->NextNode = newNode;
			newNode->NextNode = nullptr;
		}
	}

	unsigned int MemoryManager::CountNodes()
	{
		MemoryNode* currentNode = (MemoryNode*)m_StableMemoryStart;
		unsigned int nodeCount = 0;

		while (currentNode)
		{
			nodeCount++;
			currentNode = currentNode->NextNode;
		}

		return nodeCount;
	}
}