#pragma once

#include <Memory/MemoryManager.h>
#include <Utility/Hashes.h>
#include <Utility/Macros.h>
#include <Utility/Math.h>
#include <Utility/Vector.h>

#include <memory>

#define MapType Map<K, V>
#define SetType Set<K, V>

namespace Soul
{
	/*
	A dictionary-like structure implemented using a hash map. All keys must be hashable via, an
	overloaded Hash function preferably (from Utility/Hashes.h)	hashes. The type stored in this
	Map should either be a primitive, or a type with a proper move constructor.
	*/
	template <class K, class V>
	class Map
	{
	public:
		template <class K, class V>
		struct Set
		{
			bool IsInitialized;
			K Key;
			V Value;
		};

	public:
		Map(unsigned int capacity = 7);

		Map(const MapType&) = delete; // No copy constructor
		Map(MapType&& otherMap); // Move constructor
		
		Map& operator=(const MapType&) = delete; // No copy assignment

		~Map();
		
		bool operator==(const MapType& otherMap);

		/*
		Adds a new hash-value pair to the map.
		*/
		bool AddPair(K& key, V& value);

		/*
		Adds a new hash-value pair to the map.
		*/
		bool AddPair(K&& key, V&& value);

		/*
		Adds a new hash-value pair to the map.
		*/
		bool AddPair(K& key, V&& value);
		/*
		Adds a new hash-value pair to the map.
		*/
		bool AddPair(K&& key, V& value);

		/*
		Clears this map of all of its data sets.
		*/
		void Clear();

		/*
		Gets the value stored at the provided hash.
		*/
		V* Get(const K& key) const;

		/*
		Gets the number of sets stored in this map.
		*/
		unsigned int GetCount() const;

		/*
		Prints a debug drawing of this map.
		*/
		void DebugPrintMap() const;

		/*
		Returns a vector of all of the keys stored in this map.
		*/
		Vector<K*> GetKeys() const;

		/*
		Returns a vector of all of the values stored in this map.
		*/
		Vector<V*> GetValues() const;

	private:
		/*
		Repartitions this map to have the desired capacity.
		*/
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
		Set<K, V>* m_Memory;
	};

	template <class K, class V>
	MapType::Map(unsigned int capacity) :
		m_Count(0),
		m_Capacity(Math::FindNextPrime(capacity)),
		m_Memory(PartitionArray(MapType::SetType, m_Capacity))
	{

	}

	template <class K, class V>
	MapType::Map(MapType&& otherMap)
	{
		m_Capacity = otherMap.m_Capacity;
		m_Count = otherMap.m_Count;
		m_Memory = otherMap.m_Memory;

		otherMap.m_Memory = nullptr;
	}

	template <class K, class V>
	MapType::~Map()
	{
		if (m_Memory)
		{
			MemoryManager::FreeMemory(m_Memory);
		}
	}

	template <class K, class V>
	bool MapType::operator==(const MapType& otherMap)
	{
		return (otherMap.m_Memory == m_Memory);
	}

	template <class K, class V>
	bool MapType::AddPair(K& key, V& value)
	{
		// Check to make sure adding this doesn't fill our capacity
		if (m_Count + 1 >= m_Capacity)
		{
			Resize(Math::FindNextPrime(m_Capacity * 2));
		}

		// Find the location to place this pair
		unsigned int hash = Hash(key);
		unsigned int location = hash % m_Capacity;

		unsigned int attempts = 0;
		unsigned int maxAttempts = m_Capacity / 2;
		// Check to see if there is an object at that location
		while (m_Memory[location].IsInitialized)
		{
			// We couldn't find a spot
			if (attempts++ >= maxAttempts)
			{
				SoulLogWarning("Error, could not find valid memory for new pair.\nCurrent capacity: %d\nCurrent pairs: %d", m_Capacity, m_Count);
				return false;
			}

			location = (location + (attempts * attempts)) % m_Capacity;
		}

		m_Memory[location].IsInitialized = true;
		new (&(m_Memory[location].Key)) K(std::move(key));
		new (&(m_Memory[location].Value)) V(std::move(value));
		
		m_Count++;

		return true;
	}

	template <class K, class V>
	bool MapType::AddPair(K&& key, V&& value)
	{
		// Check to make sure adding this doesn't fill our capacity
		if (m_Count + 1 >= m_Capacity)
		{
			Resize(Math::FindNextPrime(m_Capacity * 2));
		}

		// Find the location to place this pair
		unsigned long long hash = Hash(key);
		unsigned int location = hash % m_Capacity;

		unsigned int attempts = 0;
		unsigned int maxAttempts = m_Capacity / 2;
		// Check to see if there is an object at that location
		while (m_Memory[location].IsInitialized)
		{
			// We couldn't find a spot
			if (attempts++ >= maxAttempts)
			{
				SoulLogWarning("Error, could not find valid memory for new pair.\nCurrent capacity: %d\nCurrent pairs: %d", m_Capacity, m_Count);
				return false;
			}

			location = (location + (attempts * attempts)) % m_Capacity;
		}

		m_Memory[location].IsInitialized = true;
		new (&(m_Memory[location].Key)) K(std::move(key));
		new (&(m_Memory[location].Value)) V(std::move(value));

		m_Count++;

		return true;
	}

	template <class K, class V>
	bool MapType::AddPair(K& key, V&& value)
	{
		// Check to make sure adding this doesn't fill our capacity
		if (m_Count + 1 >= m_Capacity)
		{
			Resize(Math::FindNextPrime(m_Capacity * 2));
		}

		// Find the location to place this pair
		unsigned long long hash = Hash(key);
		unsigned int location = hash % m_Capacity;

		unsigned int attempts = 0;
		unsigned int maxAttempts = m_Capacity / 2;
		// Check to see if there is an object at that location
		while (m_Memory[location].IsInitialized)
		{
			// We couldn't find a spot
			if (attempts++ >= maxAttempts)
			{
				SoulLogWarning("Error, could not find valid memory for new pair.\nCurrent capacity: %d\nCurrent pairs: %d", m_Capacity, m_Count);
				return false;
			}

			location = (location + (attempts * attempts)) % m_Capacity;
		}

		m_Memory[location].IsInitialized = true;
		new (&(m_Memory[location].Key)) K(std::move(key));
		new (&(m_Memory[location].Value)) V(std::move(value));

		m_Count++;

		return true;
	}

	template <class K, class V>
	bool MapType::AddPair(K&& key, V& value)
	{
		// Check to make sure adding this doesn't fill our capacity
		if (m_Count + 1 >= m_Capacity)
		{
			Resize(Math::FindNextPrime(m_Capacity * 2));
		}

		// Find the location to place this pair
		unsigned long long hash = Hash(key);
		unsigned int location = hash % m_Capacity;

		unsigned int attempts = 0;
		unsigned int maxAttempts = m_Capacity / 2;
		// Check to see if there is an object at that location
		while (m_Memory[location].IsInitialized)
		{
			// We couldn't find a spot
			if (attempts++ >= maxAttempts)
			{
				SoulLogWarning("Error, could not find valid memory for new pair.\nCurrent capacity: %d\nCurrent pairs: %d", m_Capacity, m_Count);
				return false;
			}

			location = (location + (attempts * attempts)) % m_Capacity;
		}

		m_Memory[location].IsInitialized = true;
		new (&(m_Memory[location].Key)) K(std::move(key));
		new (&(m_Memory[location].Value)) V(std::move(value));

		m_Count++;

		return true;
	}

	template <class K, class V>
	void MapType::Clear()
	{
		// Call all destructors
		for (unsigned int i = 0; i < m_Capacity; ++i)
		{
			if (m_Memory[i].IsInitialized)
			{
				m_Memory[i].Key.~K();
				m_Memory[i].Value.~V();
			}
		}

		// Clear all data
		memset(m_Memory, 0, m_Capacity * sizeof(SetType));
		m_Count = 0;
	}

	template <class K, class V>
	V* MapType::Get(const K& key) const
	{
		// Find the location to place this pair
		unsigned long long hash = Hash(key);
		unsigned int location = hash % m_Capacity;

		unsigned int attempts = 0;
		unsigned int maxAttempts = m_Capacity / 2;

		// Check to see if there is an object at that location
		while ((m_Memory[location].IsInitialized && m_Memory[location].Key != key))
		{
			// We couldn't find a spot
			if (attempts++ >= maxAttempts)
			{
				SoulLogWarning("Could not find value with hash: %lld", hash);
				return nullptr;
			}

			location = (location + (attempts * attempts)) % m_Capacity;
		}

		return &(m_Memory[location].Value);
	}

	template <class K, class V>
	unsigned int MapType::GetCount() const
	{
		return m_Count;
	}

	template <class K, class V>
	void MapType::DebugPrintMap() const
	{
		for (unsigned int i = 0; i < m_Capacity; ++i)
		{
			if (m_Memory[i].IsInitialized)
			{
				SoulLogInfo("%s", m_Memory[i].Key.GetCString());
			}
			else
			{
				SoulLogInfo("0");
			}
		}
		SoulLogInfo("\n\n\n");
	}

	template <class K, class V>
	Vector<K*> MapType::GetKeys() const
	{
		Vector<K*> keys(m_Count);
		for (unsigned int i = 0; i < m_Capacity; ++i)
		{
			if (m_Memory[i].IsInitialized)
			{
				keys.Push(&(m_Memory[i].Key));
			}
		}

		return keys;
	}

	template <class K, class V>
	Vector<V*> MapType::GetValues() const
	{
		Vector<V*> values(m_Count);
		for (unsigned int i = 0; i < m_Capacity; ++i)
		{
			if (m_Memory[i].IsInitialized)
			{
				values.Push(&(m_Memory[i].Value));
			}
		}

		return values;
	}

	template <class K, class V>
	void MapType::Resize(unsigned int newCapacity)
	{
		// Create a new memory block with the necessary size, move all previous elements into it
		SetType* newMemory = PartitionArray(SetType, newCapacity);

		for (unsigned int i = 0; i < m_Capacity; ++i)
		{
			if (!m_Memory[i].IsInitialized)
			{
				continue;
			}

			// Find the location to place this pair
			unsigned long long hash = Hash(m_Memory[i].Key);
			unsigned int location = hash % newCapacity;

			unsigned int attempts = 0;
			unsigned int maxAttempts = newCapacity / 2;
			// Check to see if there is an object at that location
			while (newMemory[location].IsInitialized)
			{
				// We couldn't find a spot
				if (attempts++ >= maxAttempts)
				{
					Assert(false);
				}

				location = (location + (attempts * attempts)) % newCapacity;
			}

			newMemory[location].IsInitialized = true;
			new (&(newMemory[location].Key)) K(std::move(m_Memory[i].Key));
			new (&(newMemory[location].Value)) V(std::move(m_Memory[i].Value));
		}

		// Free the old memory and reassign
		MemoryManager::FreeMemory(m_Memory);
		m_Capacity = newCapacity;
		m_Memory = newMemory;
	}
}