#include "Rigidbody.h"

#include "../Debugging/MemoryLeakDetector.h"
#include "../Time/Time.h"
#include "../Debugging/Debug.h"

#pragma region StaticHandlerMembers
float Rigidbody::Handler::globalGravity = -9.81f;
#pragma endregion StaticHandlerMembers

#pragma region StaticRigidbodyMembers
float Rigidbody::dragCoefficient = 0.5f;
#pragma endregion StaticRigidbodyMembers

namespace Physics
{
	static const float MAX_VELOCITY = 3.5f;
}

#pragma region RigidbodyMethods
Rigidbody::Rigidbody(GameObject* _gameObject) : Component(_gameObject), mass(1.0f), acceleration(Vector2::Zero), 
												velocity(Vector2::Zero), displacement(Vector2::Zero)
{
	// INFO: Set gravity to global gravity value
	gravity = Rigidbody::Handler::GetGlobalGravity();
}

void Rigidbody::Update(float deltaTime)
{
	// INFO: Don't update the rigidbody if it's inactive
	if (!IsActive())
		return;

	acceleration.X = (force.X / mass);
	acceleration.Y = (force.Y / mass) + gravity;

	velocity += acceleration * deltaTime;

	if (velocity.Magnitude() > Physics::MAX_VELOCITY)
	{
		Vector2::Normalize(velocity);
		velocity *= Physics::MAX_VELOCITY;
	}

	displacement = velocity * deltaTime;

	/*
	// INFO: Calculate gravitational force based on mass as well as the
	//       force applied to the rigidbody
	Vector2 gravitationalForce = gravityDirection * gravity * mass;

	// INFO: Calculate drag force based on the velocity of the rigidbody
	Vector2 unitVelocity = velocity.Normalized();
	Vector2 dragForce = unitVelocity * (-dragCoefficient * velocity.Magnitude());

	// INFO: Include drag force in the total force applied to the rigidbody
	Vector2 totalForce = gravitationalForce + force + dragForce;

	// INFO: Calculate acceleration based on the total force applied to the rigidbody
	acceleration = totalForce / mass;

	// INFO: Calculate velocity based on the acceleration of the rigidbody
	velocity += acceleration * deltaTime;

	// INFO: Calculate terminal velocity
	Vector2 terminalVelocity = gravitationalForce * mass / dragCoefficient;

	// INFO: Prevent the rigidbody from exceeding terminal velocity
	if (velocity.Magnitude() > terminalVelocity.Magnitude())
	{
		// INFO: Normalize the velocity
		Vector2::Normalize(velocity);

		// INFO: Scale the velocity to the terminal velocity
		velocity *= terminalVelocity.Magnitude();
	}

	// INFO: Calculate displacement based on the velocity of the rigidbody
	displacement = velocity * deltaTime;
	*/
}

void Rigidbody::AddForce(const Vector2& _force, ForceMode mode)
{
	float deltaTime = Time::DeltaTime();

	switch (mode)
	{
	case ForceMode::Force:
		force = _force * deltaTime / mass;
		break;
	case ForceMode::Acceleration:
		force = _force * deltaTime;
		break;
	case ForceMode::Impulse:
		force = _force / mass;
		break;
	case ForceMode::VelocityChange:
		force = _force;
		break;
	case ForceMode::None:
	default:
		break;
	}
}
#pragma endregion RigidbodyMethods
