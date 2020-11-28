#pragma once

#include <SFML/System/Vector2.hpp>

namespace Soul
{
	/*
	A spatial tree that can have a maximum of four children per node. Once a node has more than
	four children, it will add QuadTree nodes to place it's overflowing children into, such that
	it no longer has more than four children.
	*/
	template <class T>
	class QuadTree
	{
	public:
		struct Node
		{
			bool IsLive;
			sf::Vector2f Position;
			union
			{
				T Data;
				QuadTree* SubQuad;
			};
		};

	public:
		QuadTree();

	private:

	};
}