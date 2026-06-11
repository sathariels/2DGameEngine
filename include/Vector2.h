#ifndef VECTOR2_H
#define VECTOR2_H

#include <cmath>

struct Vector2 {
  float x, y;

  Vector2(float x = 0, float y = 0) : x(x), y(y) {}

  // --- Arithmetic ---
  Vector2 operator+(const Vector2 &other) const {
    return Vector2(x + other.x, y + other.y);
  }

  Vector2 operator-(const Vector2 &other) const {
    return Vector2(x - other.x, y - other.y);
  }

  Vector2 operator-() const { return Vector2(-x, -y); }

  Vector2 operator*(float scalar) const {
    return Vector2(x * scalar, y * scalar);
  }

  Vector2 operator/(float scalar) const {
    return Vector2(x / scalar, y / scalar);
  }

  Vector2 &operator+=(const Vector2 &other) {
    x += other.x;
    y += other.y;
    return *this;
  }

  Vector2 &operator-=(const Vector2 &other) {
    x -= other.x;
    y -= other.y;
    return *this;
  }

  Vector2 &operator*=(float scalar) {
    x *= scalar;
    y *= scalar;
    return *this;
  }

  // --- Measurement ---
  float Dot(const Vector2 &other) const { return x * other.x + y * other.y; }

  float LengthSquared() const { return x * x + y * y; }

  float Length() const { return std::sqrt(LengthSquared()); }

  float Distance(const Vector2 &other) const {
    return (*this - other).Length();
  }

  // --- Direction ---
  // Returns a unit-length copy; the zero vector stays zero.
  Vector2 Normalized() const {
    float len = Length();
    if (len <= 0.0f) return Vector2(0, 0);
    return *this / len;
  }

  // Mirrors this vector about a surface with unit normal n:
  //   v' = v - 2 (v . n) n
  Vector2 Reflect(const Vector2 &n) const {
    return *this - n * (2.0f * Dot(n));
  }

  // --- Interpolation ---
  static Vector2 Lerp(const Vector2 &a, const Vector2 &b, float t) {
    return a + (b - a) * t;
  }
};

inline Vector2 operator*(float scalar, const Vector2 &v) { return v * scalar; }

#endif // VECTOR2_H
