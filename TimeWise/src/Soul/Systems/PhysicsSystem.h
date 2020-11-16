#pragma once

#include <Components/PhysicsComponent.h>
#include <Structures/Vector.h>

namespace Soul
{
	class PhysicsSystem
	{
	public:
		PhysicsSystem(unsigned int colliders);
		~PhysicsSystem();

		void Update(float dt, Context& context);

		template <class T>
		T* CreatePhysicsComponent(Entity* entity, sf::FloatRect bounds);

		template <class T>
		void RemovePhysicsComponent(T* component);

	private:
		Vector<PhysicsComponent*> m_Components;
	};

	template <class T>
	T* PhysicsSystem::CreatePhysicsComponent(Entity* entity, sf::FloatRect bounds)
	{
		T* component = Partition(T, entity, bounds, *this);

		m_Components.Push((PhysicsComponent*)component);

		return component;
	}

	template <class T>
	void PhysicsSystem::RemovePhysicsComponent(T* component)
	{
		m_Components.Remove(component);
	}
}