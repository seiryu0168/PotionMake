#include "PhysicsSystem.h"
#include"../Coordinator.h"


PhysicsSystem::PhysicsSystem() : System(), time_(0)
{
	Coordinator::RegisterComponent<Gravity>();
	Coordinator::RegisterComponent<TransformData>();
	Coordinator::RegisterComponent<RigidBody>();
}

void PhysicsSystem::Update()
{
	++time_;
	PhysicsUpdate((float)time_ / 60.0f);
	
}

void PhysicsSystem::PhysicsUpdate(float deltaTime)
{
	//for (auto const& entity : entities_)
	//{
	//	auto& rigidBody = Coordinator::GetComponent<RigidBody>(entity);
	//	auto& transform = Coordinator::GetComponent<TransformData>(entity);
	//	auto& gravity = Coordinator::GetComponent<Gravity>(entity);
	//
	//	transform.position_ += rigidBody.vector_ * deltaTime;
	//	rigidBody.vector_ += gravity.force_ * deltaTime;
	//
	//}
}
