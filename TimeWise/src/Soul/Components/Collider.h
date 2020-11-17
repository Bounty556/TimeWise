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

		virtual const char* GetType() const override;

		void DrawCollider(Context& context) const;

		// Getters
		
		unsigned int GetVertexCount() const;
		bool IsSolid() const;
		float GetBounciness() const;
		float GetFriction() const;

		// Setters

		void SetIsSolid(bool isSolid);
		void SetBounciness(float bounciness);
		void SetFriction(float friction);

	private:
		unsigned int m_VertexCount;
		UniquePointer<sf::Vector2f> m_Vertices;
		bool m_IsSolid;
		float m_Bounciness;
		float m_Friction;
	};
}