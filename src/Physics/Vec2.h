//
// Created by Ivan Riumkin on 2026-08-13.
//

#ifndef ANGRYSNAIL_VEC2_H
#define ANGRYSNAIL_VEC2_H

struct Vec2 {
    float x;
    float y;

    Vec2();
    ~Vec2() = default;

    Vec2(float x, float y);

    void Add(const Vec2 &v);

    void Subtract(const Vec2 &v);

    void Scale(float s);

    [[nodiscard]] Vec2 Rotate(float radians) const;

    [[nodiscard]] float Magnitude() const;

    [[nodiscard]] float SquaredMagnitude() const;

    [[nodiscard]] Vec2 &Normalize();

    [[nodiscard]] Vec2 UnitVector() const;

    [[nodiscard]] Vec2 Normal() const;

    [[nodiscard]] float Dot(const Vec2 &v) const;

    [[nodiscard]] float Cross(const Vec2 &v) const;


    Vec2 &operator =(const Vec2 &v); // v1 = v2
    bool operator ==(const Vec2 &v) const; // v1 == v2
    bool operator !=(const Vec2 &v) const; // v1 != v2

    Vec2 operator +(const Vec2 &v) const; // v1 + v2
    Vec2 operator -(const Vec2 &v) const; // v1 - v2
    Vec2 operator *(float n) const; // v1 * n
    Vec2 operator /(float n) const; // v1 / n
    Vec2 operator -() const; // -v1

    Vec2 &operator +=(const Vec2 &v); // v1 += v2
    Vec2 &operator -=(const Vec2 &v); // v1 -= v2
    Vec2 &operator *=(float n); // v1 *= n
    Vec2 &operator /=(float n); // v1 /= n
};

#endif //ANGRYSNAIL_VEC2_H
