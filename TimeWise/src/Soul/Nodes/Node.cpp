#include "Node.h"

#include <Memory/MemoryManager.h>

namespace Soul
{
	Node::Node(Node* parent) :
		m_Parent(parent),
		m_Children()
	{
	}

	Node::~Node()
	{
		// Free the memory for each of children allocated within our vector. We have to do this
		// here because the vector will only go one level deep, and will "deallocate" the pointers
		// to the children rather than the children themselves.
		for (unsigned int i = 0; i < m_Children.Length(); ++i)
		{
			MemoryManager::FreeMemory(m_Children[i]);
		}
	}

	const Node* Node::GetParent() const
	{
		return m_Parent;
	}

	void Node::AddChild(Node* child)
	{
		child->m_Parent = this;
		m_Children.Push(child);
	}

	void Node::Update(float dt)
	{
		UpdateSelf(dt);
		UpdateChildren(dt);
	}

	void Node::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		DrawSelf(target, states);
		DrawChildren(target, states);
	}

	void Node::UpdateChildren(float dt)
	{
		for (unsigned int i = 0; i < m_Children.Length(); ++i)
		{
			m_Children[i]->Update(dt);
		}
	}

	void Node::UpdateSelf(float dt)
	{

	}

	void Node::DrawChildren(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();

		for (unsigned int i = 0; i < m_Children.Length(); ++i)
		{
			m_Children[i]->draw(target, states);
		}
	}

	void Node::DrawSelf(sf::RenderTarget& target, sf::RenderStates states) const
	{

	}
}