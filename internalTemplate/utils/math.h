#pragma once
#include "includes.h"
#include "../renderes/RendererOptions.h"

constexpr float PI = 3.14159265358979323846f;

struct Vector2
{
	float x, y;
	Vector2(float x = 0, float y = 0) : x(x), y(y) {}

	Vector2 operator-(const Vector2& other) const
	{
		return Vector2(x - other.x, y - other.y);
	}

	Vector2 operator+(const Vector2& other) const
	{
		return Vector2(x + other.x, y + other.y);
	}

	Vector2 operator*(float scalar) const
	{
		return Vector2(x * scalar, y * scalar);
	}

	Vector2 operator/(float scalar) const
	{
		return Vector2(x / scalar, y / scalar);
	}
};

struct Vector3
{
	float x, y, z;

	Vector3(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {}

	// Subtraction
	Vector3 operator-(const Vector3& other) const
	{
		return Vector3(x - other.x, y - other.y, z - other.z);
	}

	// Addition
	Vector3 operator+(const Vector3& other) const
	{
		return Vector3(x + other.x, y + other.y, z + other.z);
	}

	// Scalar multiplication
	Vector3 operator*(float scalar) const
	{
		return Vector3(x * scalar, y * scalar, z * scalar);
	}

	// Scalar division
	Vector3 operator/(float scalar) const
	{
		return Vector3(x / scalar, y / scalar, z / scalar);
	}
};

struct Vector4
{
	float x, y, z, w;
	Vector4(float x = 0, float y = 0, float z = 0, float w = 0) : x(x), y(y), z(z), w(w) {}

	Vector4 operator-(const Vector4& other) const
	{
		return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
	}

	Vector4 operator+(const Vector4& other) const
	{
		return Vector4(x + other.x, y + other.y, z + other.z, w - other.w);
	}

	Vector4 operator*(float scalar) const
	{
		return Vector4(x * scalar, y * scalar, z * scalar, w * scalar);
	}

	Vector4 operator/(float scalar) const
	{
		return Vector4(x / scalar, y / scalar, z / scalar, w / scalar);
	}
};

using Vec2 = Vector2;
using vec2 = Vector2;
using VEC2 = Vector2;

using Vec3 = Vector3;
using vec3 = Vector3;
using VEC3 = Vector3;

using Vec4 = Vector4;
using vec4 = Vector4;
using VEC4 = Vector4;


namespace math
{
	float calculateDistance(const Vector3& a, const Vector3& b);

	Vector2 CalculateAngles(Vector3 from, Vector3 to);

	bool WorldToScreenDX(Vec3 pos, Vec2& screen, float matrix[16], int windowWidth, int windowHeight);

	bool WorldToScreenGL(Vec3 pos, Vec2& screen, float matrix[16], int windowWidth, int windowHeight);

	bool WorldToScreen(Vec3 pos, Vec2& screen, float matrix[16], int windowWidth, int windowHeight);
}
