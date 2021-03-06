
#include "Vector4.h"
#include "math.h"

const Vector4 Vector4::Zero {0, 0, 0, 0};
const Vector4 Vector4::One {1, 1, 1, 1};

Vector4::Vector4(float x, float y, float z, float w)
    : x{x}
    , y{y}
    , z{z}
    , w{w}
{
}

Vector4::Vector4(List<float> list)
    : x{list[0]}
    , y{list[1]}
    , z{list[2]}
    , w{list[3]}
{
}

List<float> Vector4::toList()
{
    return {x, y, z, w};
}

float Vector4::length()
{
    return sqrt(x * x + y * y + z * z + w * w);
}

float Vector4::squaredLength()
{
    return x * x + y * y + z * z + w * w;
}

Vector4 operator-(const Vector4& vector)
{
    return
    {
        -vector.x,
        -vector.y,
        -vector.z,
        -vector.w
    };
}

Vector4 operator+(const Vector4& lhs, const Vector4& rhs)
{
    return
    {
        lhs.x + rhs.x,
        lhs.y + rhs.y,
        lhs.z + rhs.z,
        lhs.w + rhs.w
    };
}

Vector4 operator-(const Vector4& lhs, const Vector4& rhs)
{
    return
    {
        lhs.x - rhs.x,
        lhs.y - rhs.y,
        lhs.z - rhs.z,
        lhs.w - rhs.w
    };
}

Vector4 operator*(const Vector4& vector, const float& value)
{
    return
    {
        vector.x * value,
        vector.y * value,
        vector.z * value,
        vector.w * value
    };
}
