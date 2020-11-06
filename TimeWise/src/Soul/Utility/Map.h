#pragma once

#include <Memory/MemoryManager.h>
#include <Utility/Math.h>

#include <memory>

namespace Soul
{
	/*
	A dictionary-like structure implemented using a hash map. All keys must be integers, preferably
	hashes.
	*/
	template <class T>
	class Map
	{
	public:
		template <class T>
		struct Set
		{
			unsigned long long Hash;
			T Value;
		};

	public:
		Map(unsigned int capacity = 7);
		~Map();

		/*
		Adds a new hash-value pair to the map.
		*/
		bool AddPair(unsigned long long hash, T& value);

		/*
		Adds a new hash-value pair to the map.
		*/
		bool AddPair(unsigned long long hash, T&& value);

		/*
		Gets the value stored at the provided hash.
		*/
		T* Get(unsigned long long hash) const;

		/*
		Gets the number of sets stored in this map.
		*/
		unsigned int GetCount() const;

	private:
		void Resize(unsigned int newCapacity);

	private:
		/*
		How many stored sets we currently have.
		*/
		unsigned int m_Count;

		/*
		How many sets this Map can have before needing to repartition and expand. This
		should be prime for use with quadratic probing.
		*/
		unsigned int m_Capacity;

		/*
		The minimum number of sets this Map can have. This should always be a prime.
		*/
		const unsigned int m_MinimumCapacity = 7;

		/*
		The start of the memory 
		*/
		Set<T>* m_Memory;
	};

	template <class T>
	Map<T>::Map(unsigned int capacity) :
		m_Count(0),
		m_Capacity(Math::FindNextPrime(capacity)),
		m_Memory(PartitionArray(Map<T>::Set<T>, m_Capacity))
	{

	}

	template <class T>
	Map<T>::~Map()
	{
		MemoryManager::FreeMemory(m_Memory);
	}

	template <class T>
	bool Map<T>::AddPair(unsigned long long hash, T& value)
	{
		// Check to make sure adding this doesn't fill our capacity
		if (m_Count + 1 >= m_Capacity)
		{
			Resize(Math::FindNextPrime(m_Capacity * 2));
		}

		// Find the location to place this pair
		unsigned int location = hash % m_Capacity;

		unsigned int attempts = 0;
		unsigned int maxAttempts = m_Capacity / 2;
		// Check to see if there is an object at that location
		while (m_Memory[location].Hash != 0)
		{
			// We couldn't find a spot
			if (attempts++ >= maxAttempts)
			{
				SoulLogWarning("Error, could not find valid memory for new pair.\nCurrent capacity: %d\nCurrent pairs: %d", m_Capacity, m_Count);
				return false;
			}

			location = (location + (attempts * attempts)) % m_Capacity;
		}

		m_Memory[location].Hash = hash;
		new (&(m_Memory[location].Value)) T(std::move(value));
		
		m_Count++;

		return true;
	}

	template <class T>
	bool Map<T>::AddPair(unsigned long long hash, T&& value)
	{
		// Check to make sure adding this doesn't fill our capacity
		if (m_Count + 1 >= m_Capacity)
		{
			Resize(Math::FindNextPrime(m_Capacity * 2));
		}

		// Find the location to place this pair
		unsigned int location = hash % m_Capacity;

		unsigned int attempts = 0;
		unsigned int maxAttempts = m_Capacity / 2;
		// Check to see if there is an object at that location
		while (m_Memory[location].Hash != 0)
		{
			// We couldn't find a spot
			if (attempts++ >= maxAttempts)
			{
				SoulLogWarning("Error, could not find valid memory for new pair.\nCurrent capacity: %d\nCurrent pairs: %d", m_Capacity, m_Count);
				return false;
			}

			location = (location + (attempts * attempts)) % m_Capacity;
		}

		m_Memory[location].Hash = hash;
		new (&(m_Memory[location].Value)) T(value);

		m_Count++;

		return true;
	}

	template <class T>
	T* Map<T>::Get(unsigned long long hash) const
	{
		// Find the location to place this pair
		unsigned int location = hash % m_Capacity;

		unsigned int attempts = 0;
		unsigned int maxAttempts = m_Capacity / 2;
		// Check to see if there is an object at that location
		while (m_Memory[location].Hash != hash)
		{
			// We couldn't find a spot
			if (attempts++ >= maxAttempts)
			{
				SoulLogWarning("Could not find value with hash: %lld", hash);
				return nullptr;
			}

			location += (attempts * attempts) % m_Capacity;
		}

		return &(m_Memory[location].Value);
	}

	template <class T>
	unsigned int Map<T>::GetCount() const
	{
		return m_Count;
	}

	template <class T>
	void Map<T>::Resize(unsigned int newCapacity)
	{
		// Create a new memory block with the necessary size, move all previous elements into it
		Set<T>* newMemory = PartitionArray(Set<T>, newCapacity);

		for (unsigned int i = 0; i < m_Capacity; ++i)
		{
			if (m_Memory[i].Hash == 0)
			{
				break;
			}

			// Find the location to place this pair
			unsigned int location = m_Memory[i].Hash % newCapacity;

			unsigned int attempts = 0;
			unsigned int maxAttempts = newCapacity / 2;
			// Check to see if there is an object at that location
			while (newMemory[location].Hash != 0)
			{
				// We couldn't find a spot
				if (attempts++ >= maxAttempts)
				{
					Assert(false);
				}

				location = (location + (attempts * attempts)) % newCapacity;
			}

			newMemory[location].Hash = m_Memory[i].Hash;
			new (&(newMemory[location].Value)) T(std::move(m_Memory[i].Value));
		}

		// Free the old memory and reassign
		MemoryManager::FreeMemory(m_Memory);
		m_Capacity = newCapacity;
		m_Memory = newMemory;

		SoulLogInfo("Resizing to %d", m_Capacity);
	}
}