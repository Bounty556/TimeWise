#pragma once

namespace Soul
{
	/*
	A fixed-size queue that utilizes a rolling buffer array as it's underlying structure. This is
	a FIFO structure.
	*/
	template <class T>
	class Queue
	{
	public:
		explicit Queue(unsigned int capacity);
		Queue(const Queue& otherQueue) = delete;
		Queue(Queue&& otherQueue) = delete;
		Queue operator=(const Queue& otherQueue) = delete;

		~Queue();

		/*
		Removes and returns the first element in the queue.
		*/
		T Dequeue();

		/*
		Adds a new element to the end of the queue.
		*/
		void Enqueue(T element);

	private:
		unsigned int m_Capacity;
		unsigned int m_EndIndex;
		unsigned int m_StartIndex;
		T* m_Queue;
	};

	template <class T>
	Queue<T>::Queue(unsigned int capacity) :
		m_Capacity(capacity + 1),
		m_EndIndex(0),
		m_StartIndex(0),
		m_Queue(PartitionArray(T, capacity))
	{
	}

	template <class T>
	Queue<T>::~Queue()
	{
		MemoryManager::FreeMemory(m_Queue);
	}

	template <class T>
	T Queue<T>::Dequeue()
	{
		if (m_StartIndex != m_EndIndex)
		{
			T toReturn(std::move(m_Queue[m_StartIndex]));
			m_StartIndex = (m_StartIndex + 1) % m_Capacity;

			return toReturn;
		}
		else
		{
			SoulLogError("Dequeueing past queue capacity.");
			Assert(false);
		}
	}

	template <class T>
	void Queue<T>::Enqueue(T element)
	{
		if ((m_EndIndex + 1) % m_Capacity != m_StartIndex)
		{
			new (&(m_Queue[m_EndIndex])) T(std::move(element));
			m_EndIndex = (m_EndIndex + 1) % m_Capacity;
		}
		else
		{
			SoulLogWarning("Enqueueing past queue capacity.");
		}
	}
}