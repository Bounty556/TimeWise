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
		// TODO: Set memory to 0's ?

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

	// TODO: Maybe we should be finding the smallest free block
	//       possible and partitioning there first, saving the bigger
	//       blocks for larger partitions
	void* MemoryManager::PartitionMemory(unsigned int bytes)
	{
		MemoryNode* memoryNode = (MemoryNode*)m_StableMemoryStart;
		// Need 4 bytes to store the size of the variable we're
		// allocating
		unsigned int actualBytes = bytes + sizeof(unsigned int); 

		// TODO: Align to byte boundaries?
		
		while (true)
		{
			// If we were to store memory here, can we keep our node?
			if (memoryNode->BlockSize - sizeof(MemoryNode*) >= actualBytes)
			{
				void* location = ((unsigned char*)memoryNode) + (memoryNode->BlockSize - actualBytes);
				unsigned int* header = (unsigned int*)location;
				(*header) = actualBytes;
				location = ((unsigned char*)location) + sizeof(unsigned int);

				memoryNode->BlockSize -= actualBytes;

				return location;
			}
			// In this scenario, we can't keep our node - repair nodes
			// afterwards
			else if (memoryNode->BlockSize >= actualBytes)
			{
				RemovedNode(memoryNode);

				void* location = ((void*)memoryNode);
				unsigned int* header = (unsigned int*)location;
				(*header) = memoryNode->BlockSize;
				
				location = ((unsigned char*)location) + sizeof(unsigned int);

				return location;
			}
			else // Go on to the next node
			{
				if (memoryNode->NextNode)
				{
					memoryNode = memoryNode->NextNode;
				}
				else
				{
					break;
				}
			}
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
		void* newLocation = (unsigned char*)location - sizeof(unsigned int);
		unsigned int size = *((unsigned int*)newLocation);
		size -= sizeof(unsigned int); // Don't include header
		return size;
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

	void MemoryManager::RemovedNode(MemoryNode* removedNode)
	{
		MemoryNode* startNode = (MemoryNode*)m_StableMemoryStart;

		while (startNode->NextNode != nullptr)
		{
			if (startNode->NextNode == removedNode)
				startNode->NextNode = removedNode->NextNode;
		}
	}

	void MemoryManager::AddedNode(void* location)
	{
		// Back newLocation up to where we put the header
		void* newLocation = (unsigned char*)location - sizeof(unsigned int);
		unsigned int size = *((unsigned int*)newLocation);

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
				// First, make sure this node can't be combined with
				// the previous node
				if ((unsigned char*)previousNode + previousNode->BlockSize == (unsigned char*)newNode)
				{
					previousNode->BlockSize += newNode->BlockSize;
				}
				else
				{
					previousNode->NextNode = newNode;
					newNode->NextNode = currentNode;
				}
				return;
			}

			previousNode = currentNode;
		}

		// If we still haven't found this new node, it must be at the
		// end
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