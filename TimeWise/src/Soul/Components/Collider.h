#pragma once

#include <Components/Component.h>
#include <Memory/UniquePointer.h>

namespace Soul
{
	class Collider : public Component
	{
	public:
		Collider(Entity* entity, unsigned int vertexCount, ...);

		void DrawCollider(Context& context) const;

		virtual bool CleanUp(Context& context) override;

		// Getters

		const UniquePointer<sf::Vector2f>& GetVertices() const;

		const UniquePointer<sf::Vector2f>& GetNormals() const;

		UniquePointer<sf::Vector2f> GetOffsetVertices() const;

		UniquePointer<sf::Vector2f> GetOffsetNormals() const;

		virtual const char* GetType() const override;

		unsigned int GetVertexCount() const;

	private:
		unsigned int m_VertexCount;
		UniquePointer<sf::Vector2f> m_Vertices;
		UniquePointer<sf::Vector2f> m_Normals;
	};
}