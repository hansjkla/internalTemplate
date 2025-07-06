#include "math.h"

float math::calculateDistance(const Vector3& a, const Vector3& b) {
	float dx = b.x - a.x;
	float dy = b.y - a.y;
	float dz = b.z - a.z;

	// Euklidische Distanzformel
	float value = std::sqrt(dx * dx + dy * dy + dz * dz);
	if (value < 0)
	{
		value = value * -1;
	}
	return value;
}

Vector2 math::CalculateAngles(Vector3 from, Vector3 to)
{
	Vector2 angles;

	float deltaX = to.x - from.x;
	float deltaY = to.y - from.y;
	float deltaZ = to.z - from.z;

	float hypotenuse = std::sqrt(deltaX * deltaX + deltaY * deltaY);

	angles.x = std::atan2(deltaY, deltaX) * 180.0f / PI;         // Yaw
	angles.y = std::atan2(-deltaZ, hypotenuse) * 180.0f / PI;    // Pitch (negative Z = up)

	// Clamp pitch to [-89, 89]
	if (angles.y > 89.0f) angles.y = 89.0f;
	if (angles.y < -89.0f) angles.y = -89.0f;

	// Normalize yaw to [-180, 180]
	if (angles.x > 180.0f) angles.x -= 360.0f;
	if (angles.x < -180.0f) angles.x += 360.0f;

	return angles;
}

bool math::WorldToScreenDX(Vec3 pos, Vec2& screen, float matrix[16], int windowWidth, int windowHeight)
{
	// For Direct3D
	//Matrix-vector Product, multiplying world(eye) coordinates by projection matrix = clipCoords
	vec4 clipCoords;
	clipCoords.x = pos.x * matrix[0] + pos.y * matrix[1] + pos.z * matrix[2] + matrix[3];
	clipCoords.y = pos.x * matrix[4] + pos.y * matrix[5] + pos.z * matrix[6] + matrix[7];
	clipCoords.z = pos.x * matrix[8] + pos.y * matrix[9] + pos.z * matrix[10] + matrix[11];
	clipCoords.w = pos.x * matrix[12] + pos.y * matrix[13] + pos.z * matrix[14] + matrix[15];

	if (clipCoords.w < 0.1f)
		return false;

	//perspective division, dividing by clip.W = Normalized Device Coordinates
	Vec3 NDC;
	NDC.x = clipCoords.x / clipCoords.w;
	NDC.y = clipCoords.y / clipCoords.w;
	NDC.z = clipCoords.z / clipCoords.w;

	screen.x = (windowWidth / 2 * NDC.x) + (NDC.x + windowWidth / 2);
	screen.y = -(windowHeight / 2 * NDC.y) + (NDC.y + windowHeight / 2);
	return true;
}

bool math::WorldToScreenGL(Vec3 pos, Vec2& screen, float matrix[16], int windowWidth, int windowHeight)
{
	//Matrix-vector Product, multiplying world(eye) coordinates by projection matrix = clipCoords
	Vec4 clipCoords;
	clipCoords.x = pos.x * matrix[0] + pos.y * matrix[4] + pos.z * matrix[8] + matrix[12];
	clipCoords.y = pos.x * matrix[1] + pos.y * matrix[5] + pos.z * matrix[9] + matrix[13];
	clipCoords.z = pos.x * matrix[2] + pos.y * matrix[6] + pos.z * matrix[10] + matrix[14];
	clipCoords.w = pos.x * matrix[3] + pos.y * matrix[7] + pos.z * matrix[11] + matrix[15];

	if (clipCoords.w < 0.1f)
		return false;

	//perspective division, dividing by clip.W = Normalized Device Coordinates
	Vec3 NDC;
	NDC.x = clipCoords.x / clipCoords.w;
	NDC.y = clipCoords.y / clipCoords.w;
	NDC.z = clipCoords.z / clipCoords.w;

	//Transform to window coordinates
	screen.x = (windowWidth / 2 * NDC.x) + (NDC.x + windowWidth / 2);
	screen.y = -(windowHeight / 2 * NDC.y) + (NDC.y + windowHeight / 2);
	return true;
}

bool math::WorldToScreen(Vec3 pos, Vec2& screen, float matrix[16], int windowWidth, int windowHeight)
{
	if (Renderer == RendererOptions::NONE)
	{
		return false;
	}

	else if (Renderer == RendererOptions::DX9 ||
		Renderer == RendererOptions::DX10 ||
		Renderer == RendererOptions::DX11 ||
		Renderer == RendererOptions::DX12)
	{
		return math::WorldToScreenDX(pos, screen, matrix, windowWidth, windowHeight);
	}

	else if (Renderer == RendererOptions::OPENGL)
	{
		return math::WorldToScreenGL(pos, screen, matrix, windowWidth, windowHeight);
	}

	else if (Renderer == RendererOptions::VULKAN)
	{
		return false;
	}

	return false;
}
