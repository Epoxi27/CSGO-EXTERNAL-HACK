
#include <iostream>
#include <numbers>


#define TORAD(x) (x*0.0174532925)

struct Vec4 {
	float x, y, z, w;
};


class Vector3
{
public:

	auto Init(float ix = 0.f, float iy = 0.f, float iz = 0.f) {
		x = ix;
		y = iy;
		z = iz;
	}



	constexpr Vector3 operator+(const Vector3& other) const noexcept
	{
		return { x + other.x, y + other.y, z + other.z };
	}

	constexpr Vector3 operator-(const Vector3& other) const noexcept
	{
		return { x - other.x, y - other.y, z - other.z };
	}

	constexpr Vector3 operator*(const Vector3& other) const noexcept
	{
		return { x * other.x, y * other.y, z * other.z };
	}

	constexpr Vector3 operator*(const float factor) const noexcept
	{
		return { x * factor, y * factor, z * factor };
	}

	constexpr bool operator==(const Vector3& other) const noexcept
	{
		return (x == other.x && y == other.y && z == other.z);
	}

	constexpr Vector3 operator/(const Vector3& other) const noexcept
	{
		return { x / other.x, y / other.y, z / other.z };
	}

	constexpr Vector3 Scale(float factor) const noexcept
	{
		return { x * factor, y * factor, z * factor };
	}


	constexpr float Dot(const Vector3& other) {
		float tx = (x * other.x + y * other.y + z * other.z);
		return tx;
	}

	Vector3 Forward(float distance) {

		float magnitude = sqrt(x * x + y * y + z * z);
		float angle_xy = atan2(y, x);
		float angle_xz = atan2(z, x);

		double dx = distance * cos(angle_xy) * cos(angle_xz);
		double dy = distance * sin(angle_xy) * cos(angle_xz);
		double dz = distance * sin(angle_xz);
		x += dx;
		y += dy;
		z += dz;

		return { x,y,z };
	}



	float Lenght2D() const noexcept
	{
		return sqrt(pow(x, 2) + pow(y, 2));
	}


	float Lenght3D() const noexcept
	{
		return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
	}

	inline Vector3 ToAngle() const noexcept
	{
		return {
			std::atan2(-z, std::hypot(x, y)) * (180.0f / std::numbers::pi_v<float>),
			std::atan2(y, x) * (180.0f / std::numbers::pi_v<float>),
			0.0f
		};
	}
	inline Vector3 Normalized() const
	{
		Vector3 res = *this;
		float l = res.Lenght3D();
		if (l != 0.0f) {
			res = res * (1 / l);
		}
		else {
			res.x = res.y = res.z = 0.0f;
		}
		return res;
	}

	float x{ }, y{ }, z{ };
};

class Vector2
{
public:

	auto Init(float ix = 0.f, float iy = 0.f) {
		x = ix;
		y = iy;

	}



	constexpr Vector2 operator+(const Vector2& other) const noexcept
	{
		return { x + other.x, y + other.y };
	}

	constexpr Vector2 operator-(const Vector2& other) const noexcept
	{
		return { x - other.x, y - other.y };
	}

	constexpr Vector2 operator*(const Vector2& other) const noexcept
	{
		return { x * other.x, y * other.y };
	}

	constexpr Vector2 operator*(const float factor) const noexcept
	{
		return { x * factor, y * factor };
	}

	constexpr bool operator==(const Vector2& other) const noexcept
	{
		return (x == other.x && y == other.y);
	}

	constexpr Vector2 operator/(const Vector2& other) const noexcept
	{
		return { x / other.x, y / other.y };
	}

	constexpr Vector2 Scale(float factor) const noexcept
	{
		return { x * factor, y * factor };
	}


	constexpr float Dot(const Vector2& other) {
		float tx = (x * other.x + y * other.y);
		return tx;
	}




	float Lenght() const noexcept
	{
		return sqrt(pow(x, 2) + pow(y, 2));
	}




	inline Vector2 Normalized() const
	{
		Vector2 res = *this;
		float l = res.Lenght();



		typedef  unsigned int uintptr_t;


		if (l != 0.0f) {
			res = res * (1 / l);
		}
		else {
			res.x = res.y = 0.0f;
		}
		return res;
	}

	float x{ }, y{ };
};

