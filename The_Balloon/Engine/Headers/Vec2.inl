/*
File Name: Vec2.inl
Project Name: The balloon
Author(s)
Main: Hyunjin Kim
All content 2021 DigiPen (USA) Corporation, all rights reserved.
 */

namespace math
{
	// vec2

	constexpr vec2& vec2::operator+=(const vec2& v) noexcept { *this = *this + v; return *this; };
	constexpr vec2& vec2::operator-=(const vec2& v) noexcept { *this = *this - v; return *this; };
	constexpr vec2& vec2::operator*=(double amt) noexcept { *this = *this * amt; return *this; };
	constexpr vec2& vec2::operator/=(double amt) noexcept { *this = *this / amt; return *this; };

	constexpr vec2 vec2::operator*(double amt) noexcept { return vec2(x * amt, y * amt); };
	constexpr vec2 vec2::operator/(double amt) noexcept { return vec2(x / amt, y / amt); };

	constexpr vec2 operator+(const vec2& v1, const vec2& v2) noexcept { return vec2(v1.x + v2.x, v1.y + v2.y); };
	constexpr vec2 operator-(const vec2& v1, const vec2& v2) noexcept { return vec2(v1.x - v2.x, v1.y - v2.y); };
	constexpr vec2 operator*(double amt, const vec2& v) noexcept { return vec2(v.x * amt, v.y * amt); };
	constexpr vec2 operator-(const vec2& v) noexcept { return vec2(-v.x, -v.y); };

	constexpr bool operator>(const vec2& v1, const vec2& v2) noexcept {
		if (v1.x * v1.x + v1.y * v1.y > v2.x * v2.x + v2.y * v2.y) {
			return true;
		}
		return false;
	};
	constexpr bool operator<(const vec2& v1, const vec2& v2) noexcept {
		if (v1.x * v1.x + v1.y * v1.y < v2.x * v2.x + v2.y * v2.y) {
			return true;
		}
		return false;
	}
	constexpr bool operator>=(const vec2& v1, const vec2& v2) noexcept {
		if (v1.x * v1.x + v1.y * v1.y >= v2.x * v2.x + v2.y * v2.y) {
			return true;
		}
		return false;
	};
	constexpr bool operator<=(const vec2& v1, const vec2& v2) noexcept {
		if (v1.x * v1.x + v1.y * v1.y <= v2.x * v2.x + v2.y * v2.y) {
			return true;
		}
		return false;
	}

	[[nodiscard]] constexpr bool operator==(const vec2& v1, const vec2& v2) { return (math::is_equal(v1.x, v2.x) && math::is_equal(v1.y, v2.y)); }
	[[nodiscard]] constexpr bool operator!=(const vec2& v1, const vec2& v2) { return !(math::is_equal(v1.x, v2.x) && math::is_equal(v1.y, v2.y)); }

	inline vec2 vec2::Normalize() noexcept { return *this /= std::sqrt(this->LengthSquared()); };

	constexpr double vec2::LengthSquared() noexcept { return x * x + y * y; };

	// ivec2

	constexpr ivec2& ivec2::operator+=(const ivec2& v) noexcept { *this = *this + v; return *this; };
	constexpr ivec2& ivec2::operator-=(const ivec2& v) noexcept { *this = *this - v; return *this; };
	constexpr ivec2& ivec2::operator*=(int amt) noexcept { *this = *this * amt; return *this; };
	constexpr ivec2& ivec2::operator/=(int amt) noexcept { *this = *this / amt; return *this; };

	constexpr ivec2 ivec2::operator*(int amt) noexcept { return ivec2(x * amt, y * amt); };
	constexpr ivec2 ivec2::operator/(int amt) noexcept { return ivec2(x / amt, y / amt); };
	constexpr vec2 ivec2::operator*(double amt) noexcept { return vec2(x * amt, y * amt); };
	constexpr vec2 ivec2::operator/(double amt) noexcept { return vec2(x / amt, y / amt); };

	constexpr ivec2 operator+(const ivec2& v1, const ivec2& v2) noexcept { return ivec2(v1.x + v2.x, v1.y + v2.y); };
	constexpr ivec2 operator-(const ivec2& v1, const ivec2& v2) noexcept { return ivec2(v1.x - v2.x, v1.y - v2.y); };

	constexpr ivec2 operator*(int amt, const ivec2& v) noexcept { return ivec2(v.x * amt, v.y * amt); };
	constexpr vec2 operator*(double amt, const ivec2& v) noexcept { return vec2(v.x * amt, v.y * amt); };

	constexpr ivec2 operator-(const ivec2& v) noexcept { return ivec2(-v.x, -v.y); };

	[[nodiscard]] constexpr bool operator==(const ivec2& v1, const ivec2& v2) { return (math::is_equal(v1.x, v2.x) && math::is_equal(v1.y, v2.y)); }
	[[nodiscard]] constexpr bool operator!=(const ivec2& v1, const ivec2& v2) { return !(math::is_equal(v1.x, v2.x) && math::is_equal(v1.y, v2.y)); }
};

