#pragma once

#include <Components/Component.h>
#include <Memory/UniquePointer.h>

namespace Soul
{
	class Collider : public Component
	{
	public:
		Collider(Entity* entity, unsigned int vertexCount, ...);

		/*
		Gets the vertex at index.
		*/
		const sf::Vector2f& operator[](unsigned int index) const;

		void DrawCollider(Context& context) const;

		virtual const char* GetType() const override;

		unsigned int GetVertexCount() const;

	private:
		unsigned int m_VertexCount;
		UniquePointer<sf::Vector2f> m_Vertices;
	};
}