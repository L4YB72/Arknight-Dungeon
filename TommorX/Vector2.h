#pragma once
#include <cmath>

struct Vector2 {
    double x, y;

    // 构造函数
    Vector2() = default;
    constexpr Vector2(double x_, double y_) : x(x_), y(y_) {}

    // 算术运算符
    Vector2 operator+(const Vector2& r) const { return { x + r.x, y + r.y }; }
    Vector2 operator-(const Vector2& r) const { return { x - r.x, y - r.y }; }
    Vector2 operator-() const { return { -x, -y }; }

    // 标量运算符
    Vector2 operator*(double s) const { return { x * s, y * s }; }
    Vector2 operator/(double s) const { return { x / s, y / s }; }

    // 点积运算符
    double operator*(const Vector2& r) const { return x * r.x + y * r.y; }

    // 复合赋值运算符
    Vector2& operator+=(const Vector2& r) { x += r.x; y += r.y; return *this; }
    Vector2& operator-=(const Vector2& r) { x -= r.x; y -= r.y; return *this; }
    Vector2& operator*=(double s) { x *= s; y *= s; return *this; }
    Vector2& operator/=(double s) { x /= s; y /= s; return *this; }

    // 比较运算符
    bool operator==(const Vector2& r) const { return x == r.x && y == r.y; }
    bool operator!=(const Vector2& r) const { return !(*this == r); }

    // 函数
    double length() const { return std::sqrt(x * x + y * y); }
    double length_squared() const { return x * x + y * y; }
    Vector2 normalized() const {
        double len = length();
        return len > 0 ? *this / len : Vector2(0, 0);
    }
    static double dot(const Vector2& a, const Vector2& b) { return a.x * b.x + a.y * b.y; }
    static double cross(const Vector2& a, const Vector2& b) { return a.x * b.y - a.y * b.x; }
};

// 非成员运算符：标量 * 向量
inline Vector2 operator*(double s, const Vector2& v) { return v * s; }