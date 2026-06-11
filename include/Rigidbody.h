#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "Component.h"
#include "Vector2.h"

class Rigidbody : public Component {
public:
  Rigidbody();
  ~Rigidbody() override = default;

  // Integrates accumulated forces into velocity and applies drag.
  // Called by the Physics system once per frame, before position
  // integration — game code should not call this directly.
  void Integrate(float deltaTime);

  // Forces
  void AddForce(const Vector2 &force);
  void AddForce(float x, float y);
  void AddImpulse(const Vector2 &impulse);

  // Properties
  void SetVelocity(const Vector2 &v);
  void SetVelocity(float x, float y);
  Vector2 GetVelocity() const;

  void SetMass(float m);
  float GetMass() const;

  void SetDrag(float d);
  float GetDrag() const;

  void SetGravityScale(float scale);
  float GetGravityScale() const;

private:
  Vector2 velocity;
  Vector2 acceleration;

  float mass;
  float drag;
  float gravityScale;
};

#endif // RIGIDBODY_H
