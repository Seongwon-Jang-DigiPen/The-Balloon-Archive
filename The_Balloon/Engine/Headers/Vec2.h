/*
File Name: Vec2.h
Project Name: The balloon
Author(s)
Main: Hyunjin Kim
All content 2021 DigiPen (USA) Corporation, all rights reserved.
 */
#pragma once
#include <cmath>
#include <algorithm>
#include <limits>

namespace math
{
    [[nodiscard]] constexpr double abs(double d) noexcept { return (d < 0.0) ? -d : d; }

    [[nodiscard]] constexpr bool is_equal(double d1, double d2) noexcept
    {
        return abs(d1 - d2) <= std::numeric_limits<double>::epsilon() * abs(d1 + d2);
    }

    [[nodiscard]] constexpr bool is_equal(int i1, int i2) noexcept { return i1 == i2; }

    struct [[nodiscard]] vec2
    {
        // TODO
        constexpr vec2(double x1, double y1) noexcept : x(x1), y(y1) {};
        constexpr vec2(double amt) noexcept : vec2(amt, amt) {};
        constexpr vec2() noexcept : vec2(0, 0) {};
        constexpr vec2(const vec2& v) = default;

        constexpr vec2& operator+=(const vec2& v2) noexcept;
        constexpr vec2& operator-=(const vec2& v1) noexcept;
        constexpr vec2& operator*=(double amt) noexcept;
        constexpr vec2& operator/=(double amt) noexcept;

        constexpr vec2 operator*(double amt) noexcept;
        constexpr vec2 operator/(double amt) noexcept;

        constexpr double LengthSquared() noexcept;
        inline vec2 Normalize() noexcept;

        double x, y;
    };

    constexpr vec2 operator+(const vec2& v1, const vec2& v2) noexcept;
    constexpr vec2 operator-(const vec2& v1, const vec2& v2) noexcept;
    constexpr vec2 operator*(double amt, const vec2& v) noexcept;
    constexpr vec2 operator-(const vec2& v) noexcept;

    constexpr bool operator>(const vec2& v1, const vec2& v2) noexcept;
    constexpr bool operator<(const vec2& v1, const vec2& v2) noexcept;
    constexpr bool operator>=(const vec2& v1, const vec2& v2) noexcept;
    constexpr bool operator<=(const vec2& v1, const vec2& v2) noexcept;

    //[[nodiscard]] constexpr bool operator==(const vec2& v1, const vec2& v2) noexcept;
    //[[nodiscard]] constexpr bool operator!=(const vec2& v1, const vec2& v2) noexcept;

    struct [[nodiscard]] ivec2
    {
       // TODO

        constexpr ivec2(int x1, int y1) noexcept : x(x1), y(y1) {};
        constexpr ivec2(int amt) noexcept : ivec2(amt, amt) {};
        constexpr ivec2() noexcept : ivec2(0, 0) {};
        constexpr ivec2(const ivec2& v) = default;

        constexpr ivec2& operator+=(const ivec2& v2) noexcept;
        constexpr ivec2& operator-=(const ivec2& v1) noexcept;
        constexpr ivec2& operator*=(int amt) noexcept;
        constexpr ivec2& operator/=(int amt) noexcept;

        constexpr ivec2 operator*(int amt) noexcept;
        constexpr ivec2 operator/(int amt) noexcept;
        constexpr vec2 operator*(double amt) noexcept;
        constexpr vec2 operator/(double amt) noexcept;

        int x, y;

        constexpr operator vec2() noexcept {
            return vec2{ static_cast<double>(this->x), static_cast<double>(this->y) };
        }
    };

    constexpr ivec2 operator+(const ivec2& v1, const ivec2& v2) noexcept;
    constexpr ivec2 operator-(const ivec2& v1, const ivec2& v2) noexcept;

    constexpr ivec2 operator*(int amt, const ivec2& v) noexcept;
    constexpr vec2 operator*(double amt, const ivec2& v) noexcept;

    constexpr ivec2 operator-(const ivec2& v) noexcept;

    //[[nodiscard]] constexpr bool operator==(const ivec2& v1, const ivec2& v2) noexcept;
    //[[nodiscard]] constexpr bool operator!=(const ivec2& v1, const ivec2& v2) noexcept;
}

namespace math
{
    struct rect2
    {
        math::vec2 bottomLeft;
        math::vec2 topRight;

        constexpr vec2 Size() const noexcept { return { Right() - Left(), Top() - Bottom() }; }
        constexpr double Left() const noexcept { return std::min(bottomLeft.x, topRight.x); }     // if the rect was flipped, then bottomLeft.x > topRight.x
        constexpr double Right() const noexcept { return std::max(bottomLeft.x, topRight.x); }    // if the rect was flipped, then bottomLeft.x > topRight.x
        constexpr double Top() const noexcept { return std::max(bottomLeft.y, topRight.y); }   // if the rect uses top left as {0, 0} or was flipped in the y direction
        constexpr double Bottom() const noexcept { return std::min(bottomLeft.y, topRight.y); }   // if the rect uses top left as {0, 0} or was flipped in the y direction
    };

    struct irect2
    {
        math::ivec2 bottomLeft;
        math::ivec2 topRight;
    };
}

#include "Vec2.inl"
