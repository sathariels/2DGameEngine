#include "../include/Rigidbody.h"
#include "../include/GameObject.h"
#include "../include/Transform.h"

Rigidbody::Rigidbody()
    : velocity(0, 0), acceleration(0, 0), mass(1.0f), drag(0.5f),
      gravityScale(1.0f) {}

void Rigidbody::Update(float deltaTime) {
  if (!IsActive() || !owner)
    return;

  // Integrate acceleration to velocity
  velocity.x += acceleration.x * deltaTime;
  velocity.y += acceleration.y * deltaTime;

  // Apply drag
  velocity.x *= (1.0f - drag * deltaTime);
  velocity.y *= (1.0f - drag * deltaTime);

  // Reset acceleration
  acceleration = Vector2(0, 0);

  // Allow Physics system to handle actual position integration
  // so we can resolve collisions first
}

void Rigidbody::AddForce(const Vector2 &force) {
  if (mass > 0) {
    acceleration.x += force.x / mass;
    acceleration.y += force.y / mass;
  }
}

void Rigidbody::AddForce(float x, float y) { AddForce(Vector2(x, y)); }

void Rigidbody::AddImpulse(const Vector2 &impulse) {
  if (mass > 0) {
    velocity.x += impulse.x / mass;
    velocity.y += impulse.y / mass;
  }
}

void Rigidbody::SetVelocity(const Vector2 &v) { velocity = v; }

void Rigidbody::SetVelocity(float x, float y) { velocity = Vector2(x, y); }

Vector2 Rigidbody::GetVelocity() const { return velocity; }

void Rigidbody::SetMass(float m) { mass = m; }

float Rigidbody::GetMass() const { return mass; }

void Rigidbody::SetDrag(float d) { drag = d; }

float Rigidbody::GetDrag() const { return drag; }

void Rigidbody::SetGravityScale(float scale) { gravityScale = scale; }

float Rigidbody::GetGravityScale() const { return gravityScale; }
