#pragma once

namespace Soul
{
	class PhysicsSystem
	{
	public:
		PhysicsSystem(unsigned int maxColliders);

		void Update(float dt);

	private:
		// TODO: Add colliders
	};
}