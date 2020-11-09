#pragma once

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/NonCopyable.hpp>

#include <Utility/Vector.h>

// TODO: Make children removable?

namespace Soul
{
	/*
	Nodes are the base form of an object within the soul engine. They generally have a
	transform, a renderable component to them, and are updated every frame. They can also have
	multiple children and one parent.

	Rotation is generally specified as radians, so conversion from degrees is necessary.
	*/
	class Node : public sf::Transformable, public sf::Drawable, public sf::NonCopyable
	{
	public:
		Node(Node* parent = nullptr);

		~Node();

		/*
		Returns the node that this node is a child of.
		*/
		const Node* GetParent() const;

		/*
		Adds a new child node to this node.
		*/
		void AddChild(Node* child);

		/*
		Updates this node as well as this node's children.
		*/
		void Update(float dt);

		/*
		Overridden from sf::Drawable. Draws this node as well is this node's children.
		*/
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const final override;

	private:
		/*
		Sends an update signal to all of this node's children.
		*/
		void UpdateChildren(float dt);

		/*
		Updates this node.
		*/
		virtual void UpdateSelf(float dt);

		/*
		Draws this node's children to the provided window. Children will be drawn at the location
		relative to their parent node.
		*/
		void DrawChildren(sf::RenderTarget& target, sf::RenderStates states) const;
		
		/*
		Draws this node to the provided window.
		*/
		virtual void DrawSelf(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		/*
		This node's parent. Can be nullptr.
		*/
		Node* m_Parent;

		/*
		A list of this node's children.
		*/
		Vector<Node*> m_Children;
	};
}