/*
File Name: Input.h
Project Name: The balloon
Author(s)
Main: Hyunjin Kim
Sub: Sehun Kim
All content 2021 DigiPen (USA) Corporation, all rights reserved.
 */
#pragma once
#include "Vec2.h"
#include "texture.h"
#include <vector>

namespace DOG 
{
	class Input
	{
	public:
		enum class Keyboard {
			None,
			Up, Down, Left, Right, Enter, Esc, Space, BSpace,
			Subt, Mult, Divd, Plus, Home, End, Tilde,
			A, B, C, D, E, F, G, H, I, J,
			K, L, M, N, O, P, Q, R, S, T,
			U, V, W, X, Y, Z,
			N0, N1, N2, N3, N4, N5, N6, N7, N8, N9,
			F1, F2, F3, F4, F5, F6, F7, F8, F9,
			_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, Count
		};

		//enum class Mouse {
		//	None, Left, Right, Middle, Count
		//};

		Input(Keyboard button);

		bool IsKeyDown() const;
		bool IsKeyReleased() const;
		bool IsKeyPressed() const;

	private:
		Keyboard button;
		//Mouse mouse_button;
	};

	class InputSystem
	{
	public:
		InputSystem();

		bool IsKeyDown(Input::Keyboard key) const;
		bool IsKeyReleased(Input::Keyboard key) const;
		bool IsKeyPressed(Input::Keyboard key) const;
		void setKeyDown(Input::Keyboard key, bool value);
		math::ivec2 GetMousePosition();
		math::ivec2 GetPMousePosition();
		math::ivec2 GetMouseDirection();
		int scroll_amount = 0;
		//bool IsMouseClicked(Input::Mouse mouse) const;
		//bool IsMouseReleased(Input::Mouse mouse) const;
		//void setMouseDown(Input::Mouse mouse, bool value);

		void Update();
	private:
		std::vector<bool> keyDown;
		std::vector<bool> wasKeyDown;
	};

	class Button 
	{
	public:
		Button(math::ivec2 pos_);
		Button(math::ivec2 pos_, std::string path);

		void Draw();
		bool IsPressed();
		math::ivec2 GetPosition();
		static constexpr int size = 70;
	private:
		Texture texture;
		bool IsMouseAbove();
		math::ivec2 pos;
		bool is_clicked;
	};
}