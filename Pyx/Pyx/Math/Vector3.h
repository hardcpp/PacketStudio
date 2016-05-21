#pragma once
#include <Pyx/Scripting/Script.h>

namespace  Pyx
{
	namespace Math
	{
		struct Vector3
		{

		private:
			static float LerpF(float from, float to, float amount)
			{
				return (1 - amount) * from + amount * to;
			}
			static Vector3 Lerp(Vector3 start, Vector3 end, int maxDistance)
			{
				double distance = start.GetDistance3D(end);
				if (distance < maxDistance)
					return end;

				double ratio = maxDistance / distance;

				float x = LerpF(start.X, end.X, (float)ratio);
				float y = LerpF(start.Y, end.Y, (float)ratio);
				float z = LerpF(start.Z, end.Z, (float)ratio);

				return Vector3(x, y, z);

			}

		public:
			float X, Y, Z;

		public:
			static void BindWithScript(Pyx::Scripting::Script* pScript);

		public:
			Vector3() { X = Y = Z = 0.0f; }
			Vector3(float x, float y, float z) : X(x), Y(y), Z(z) { }
			double GetDistance3D(Vector3& other) const;
			double GetDistance2D(Vector3& other) const;
			bool IsNan() const;
			bool IsInfinity() const;
			float Length() const;
			bool operator==(const Vector3& rhs) const;
			bool operator!=(const Vector3& rhs) const;
			Vector3& Vector3::operator+=(const Vector3& vector)
			{
				X += vector.X;
				Y += vector.Y;
				Z += vector.Z;
				return *this;
			}

			Vector3 Vector3::operator+(const Vector3& vector) const
			{
				return Vector3(X, Y, Z) += vector;
			}
			Vector3& Vector3::operator-=(const Vector3& vector)
			{
				X -= vector.X;
				Y -= vector.Y;
				Z -= vector.Z;
				return *this;
			}

			Vector3 Vector3::operator-(const Vector3& vector) const
			{
				return Vector3(X, Y, Z) -= vector;
			}
			Vector3& Vector3::operator*=(const Vector3& vector)
			{
				X *= vector.X;
				Y *= vector.Y;
				Z *= vector.Z;
				return *this;
			}

			Vector3 Vector3::operator*(const Vector3& vector) const
			{
				return Vector3(X, Y, Z) *= vector;
			}
			Vector3& Vector3::operator/=(const Vector3& vector)
			{
				X /= vector.X;
				Y /= vector.Y;
				Z /= vector.Z;
				return *this;
			}

			Vector3 Vector3::operator/(const Vector3& vector) const
			{
				return Vector3(X, Y, Z) /= vector;
			}
			void Normalize();

			std::string ToString() const;
		};

	}
}