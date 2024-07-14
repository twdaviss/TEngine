#pragma once

namespace TEngine::Math
{
    struct Matrix4;

    //------------------------------------------------------------------------------
    // Quaternion
    struct Quaternion
    {
        float x, y, z, w;
        Quaternion() = default;
        constexpr Quaternion(float ix, float iy, float iz, float iw) noexcept : x(ix), y(iy), z(iz), w(iw) {}

        Quaternion(const Quaternion&) = default;
        Quaternion& operator=(const Quaternion&) = default;

        Quaternion(Quaternion&&) = default;
        Quaternion& operator=(Quaternion&&) = default;

        // Comparison operators
        bool operator == (const Quaternion& q) const { return x == q.x && y == q.y && z == q.z && w == q.w; }
        bool operator != (const Quaternion& q) const { return x != q.x || y != q.y || z != q.z || w != q.w; }

        // Unary operators		
        Quaternion operator*(const Quaternion& rhs) const 
        { 
            Quaternion q2;
            q2.x = w * rhs.x + x * rhs.w + y * rhs.z - z * rhs.y;
            q2.y = w * rhs.y + y * rhs.w + z * rhs.x - x * rhs.z;
            q2.z = w * rhs.z + z * rhs.w + x * rhs.y - y * rhs.x;
            q2.w = w * rhs.w - x * rhs.x - y * rhs.y - z * rhs.z;
            return (q2);
        }
        Quaternion operator+(const Quaternion& rhs) const { return Quaternion(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w); }
        Quaternion operator*(float s) const { return Quaternion(x * s, y * s, z * s, w * s); }
        Quaternion operator/(float s) const { return Quaternion(x / s, y / s, z / s, w / s); }

        // Constants
        static const Quaternion Identity;
        static const Quaternion Zero;

        void Conjugate() noexcept;
        void Inverse() noexcept;
        float Magnitude() const noexcept;
        float MagnitudeSqr() const noexcept;
        void Normalize() noexcept;
        float Dot(const Quaternion& q) const noexcept;

        //statc functions
        static Quaternion Conjugate(const Quaternion& q);
        static float Magnitude(const Quaternion& q);
        static Quaternion Normalize(const Quaternion& q);

        static Quaternion CreateFromAxisAngle(const Vector3& axis, float angle) noexcept;
        static Quaternion CreateFromYawPitchRoll(float yaw, float pitch, float roll) noexcept;
        static Quaternion CreateFromRotationMatrix(const Matrix4& m) noexcept;

        static Quaternion Lerp(const Quaternion& q0, const Quaternion& q1, float t);
        static Quaternion Slerp(const Quaternion& q0, const Quaternion& q1, float t);




    };
}