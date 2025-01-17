#pragma once

#include <SFML/Graphics/Transformable.hpp>

#include <Components/Component.h>
#include <Memory/UniquePointer.h>

namespace Soul
{
	class CollisionHandler;

	class Collider : public Component, public sf::Transformable
	{
	public:
		Collider(Entity* entity, unsigned int vertexCount, ...);

		void DrawCollider(Context& context) const;

		virtual bool CleanUp(Context& context) override;

		void AddCollision(float dt, const sf::Vector2f& contactPoint, const sf::Vector2f& correction, Collider& collider);

		void ResolveCollisions();

		void Update(float dt);

		void ApplyForce(sf::Vector2f force);

		sf::Vector2f FarthestVertex(const sf::Vector2f& direction) const;

		// Setters

		void SetHandler(CollisionHandler* handler);

		void SetMass(float mass);

		void SetBounciness(float bounciness);

		void SetFriction(float friction);

		void SetIsSolid(bool isSolid);

		// Getters

		UniquePointer<sf::Vector2f> GetVertices() const;

		sf::Vector2f GetCenter() const;

		unsigned int GetVertexCount() const;

		float GetMass() const;

		float GetBounciness() const;

		float GetFriction() const;

		bool IsSolid() const;

		const sf::Vector2f& GetVelocity() const;

		float GetRadius() const;

	private:
		unsigned int m_VertexCount;
		UniquePointer<sf::Vector2f> m_Vertices;
		sf::Vector2f m_Center;
		CollisionHandler* m_Handler;
		float m_Radius; // Distance from the center to furthest vertex
		float m_Mass;
		float m_Bounciness;
		float m_Friction;
		bool m_IsSolid;
	};
}