#include <Pyx/Math/Vector3.h>

void Pyx::Math::Vector3::BindWithScript(Pyx::Scripting::Script* script)
{
	using namespace LuaIntf;
	LuaBinding(script->GetLuaState())
		.beginModule(XorStringA("Pyx"))
		.beginModule(XorStringA("Math"))
		.beginClass<Vector3>(XorStringA("Vector3"))
		.addStaticFunction(XorStringA("Lerp"), &Vector3::Lerp)
		.addConstructor(LUA_ARGS(_opt<float>, _opt<float>, _opt<float>))
		.addVariable(XorStringA("X"), &Vector3::X)
		.addVariable(XorStringA("Y"), &Vector3::Y)
		.addVariable(XorStringA("Z"), &Vector3::Z)
		.addFunction(XorStringA("GetDistance2D"), &Vector3::GetDistance2D)
		.addFunction(XorStringA("GetDistance3D"), &Vector3::GetDistance3D)
		.addPropertyReadOnly(XorStringA("IsNan"), &Vector3::IsNan)
		.addPropertyReadOnly(XorStringA("IsInfinity"), &Vector3::IsInfinity)
		.addFunction(XorStringA("__tostring"), &Vector3::ToString)
		.endClass();
}

double Pyx::Math::Vector3::GetDistance3D(Vector3& other) const
{
	float diffZ = Z - other.Z;
	float diffY = Y - other.Y;
	float diffX = X - other.X;
	return sqrt((diffZ * diffZ) + (diffY * diffY) + (diffX * diffX));
}

double Pyx::Math::Vector3::GetDistance2D(Vector3& other) const
{
	float diffZ = Z - other.Z;
	float diffX = X - other.X;
	return sqrt((diffZ * diffZ) + (diffX * diffX));
}

bool Pyx::Math::Vector3::IsNan() const
{
	return std::isnan(X) && std::isnan(Y) && std::isnan(Z);
}

bool Pyx::Math::Vector3::IsInfinity() const
{
	return std::isinf(X) && std::isinf(Y) && std::isinf(Z);
}

float Pyx::Math::Vector3::Length() const
{
	return sqrt(X * X + Y * Y + Z * Z);
}

bool Pyx::Math::Vector3::operator==(const Vector3& rhs) const
{
	return X == rhs.X && Y == rhs.Y && Z == rhs.Z;
}

bool Pyx::Math::Vector3::operator!=(const Vector3& rhs) const
{
	return !operator==(rhs);
}

void Pyx::Math::Vector3::Normalize()
{
	float length = this->Length();
	if (length != 0)
	{
		X = X / length;
		Y = Y / length;
		Z = Z / length;
	}
}

std::string Pyx::Math::Vector3::ToString() const
{
	std::stringstream ss;
	ss << X << ", " << Y << ", " << Z;
	return ss.str();
}
