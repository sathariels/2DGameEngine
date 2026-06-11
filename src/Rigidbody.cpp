#include "../include/Rigidbody.h"
#include <algorithm>

Rigidbody::Rigidbody()
    : velocity(0, 0), acceleration(0, 0), mass(1.0f), drag(0.5f),
      gravityScale(1.0f) {}

void Rigidbody::Integrate(float deltaTime) {
  // Integrate acceleration to velocity (semi-implicit Euler — the
  // Physics system integrates the updated velocity into position)
  velocity.x += acceleration.x * deltaTime;
  velocity.y += acceleration.y * deltaTime;

  // Apply drag. Clamped at zero so a long frame can't flip the
  // velocity's direction.
  float dragFactor = std::max(0.0f, 1.0f - drag * deltaTime);
  velocity.x *= dragFactor;
  velocity.y *= dragFactor;

  // Reset acceleration — forces are accumulated fresh each frame
  acceleration = Vector2(0, 0);
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
