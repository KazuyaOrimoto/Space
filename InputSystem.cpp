//=============================================================================
//	@file	InputSystem.cpp
//	@brief	キーボードやコントローラーの入力を管理する
//	@autor	居本 和哉
//	@date	2020/02/29
//=============================================================================

#include "InputSystem.h"
#include <SDL.h>
#include <cstring>
#include <stdio.h>
#include <limits.h>

bool InputSystem::controllerConnected = 0;

/*
@brief	現在のキーの入力状態のみを取得する
@param	SDL_Scancodeのキーコード
@return	true : 押されている , false : 押されていない
*/
bool KeyboardState::GetKeyValue(SDL_Scancode _keyCode) const
{
	return currState[_keyCode] == 1;
}

/*
@brief	現在と1フレーム前の状態からButtonStateを返す
@param	SDL_Scancodeのキーコード
@return	ButtonState型の現在の状態
*/
ButtonState KeyboardState::GetKeyState(SDL_Scancode _keyCode) const
{
	if (prevState[_keyCode] == 0)
	{
		if (currState[_keyCode] == 0)
		{
			return None;
		}
		else
		{
			return Pressed;
		}
	}
	else // Prev state must be 1
	{
		if (currState[_keyCode] == 0)
		{
			return Released;
		}
		else
		{
			return Held;
		}
	}
}

/*
@brief	現在の入力状態のみを取得する
@param	SDL_BUTTON定数
@return	true : 押されている , false : 押されていない
*/
bool MouseState::GetButtonValue(int _button) const
{
	return (SDL_BUTTON(_button) & currButtons) == 1;
}

/*
@brief	現在と1フレーム前の状態からButtonStateを返す
@param	SDL_BUTTON定数
@return	ButtonState型の現在の状態
*/
ButtonState MouseState::GetButtonState(int _button) const
{
	int mask = SDL_BUTTON(_button);
	if ((mask & prevButtons) == 0)
	{
		if ((mask & currButtons) == 0)
		{
			return None;
		}
		else
		{
			return Pressed;
		}
	}
	else
	{
		if ((mask & currButtons) == 0)
		{
			return Released;
		}
		else
		{
			return Held;
		}
	}
}

/*
@brief	現在の入力状態のみを取得する
@param	SDL_GameControllerButtonのボタンコード
@return	true : 押されている , false : 押されていない
*/
bool ControllerState::GetButtonValue(SDL_GameControllerButton _button) const
{
	return currButtons[_button] == 1;
}

/*
@brief	現在と1フレーム前の状態からButtonStateを返す
@param	SDL_GameControllerButtonのボタンコード
@return	ButtonState型の現在の状態
*/
ButtonState ControllerState::GetButtonState(SDL_GameControllerButton _button) const
{
	if (prevButtons[_button] == 0)
	{
		if (currButtons[_button] == 0)
		{
			return None;
		}
		else
		{
			return Pressed;
		}
	}
	else // Prev state must be 1
	{
		if (currButtons[_button] == 0)
		{
			return Released;
		}
		else
		{
			return Held;
		}
	}
}

float ControllerState::GetAxisValue(const SDL_GameControllerAxis iAxis) const
{
	return axisValues[iAxis];
}

/*
@brief  初期化処理
@return true : 成功 , false : 失敗
*/
bool InputSystem::Initialize()
{
	//キーボードの初期化処理
	//今のキーボードの状態を割り当てる
	state.Keyboard.currState = SDL_GetKeyboardState(NULL);
	//１フレーム前の入力状態を初期化する
	memset(state.Keyboard.prevState, 0,
		SDL_NUM_SCANCODES);

	memset(state.Controller.axisValues, 0,
		sizeof(float) * SDL_CONTROLLER_AXIS_MAX);


	//現在と１フレーム前のマウスの入力状態を初期化する
	state.Mouse.currButtons = 0;
	state.Mouse.prevButtons = 0;

	// パッドの設定ファイル gamecontrollerdb.txt の読み込みと問題が無いかのチェック
	int iNumOfControllers = SDL_GameControllerAddMappingsFromFile("Assets/Config/GameControllerdb.txt");
	if (iNumOfControllers == -1)
	{
		SDL_LogWarn(SDL_LOG_CATEGORY_INPUT, "Error loading database [%s]", SDL_GetError());
		return false;
	}

	//コントローラーを開く
	controller = nullptr;
	controller = SDL_GameControllerOpen(0);
	if (controller != nullptr)
	{
		controllerConnected = true;
	}
	if (SDL_IsGameController(0))
	{
		printf("Controller :: %s \n", SDL_GameControllerMapping(controller));
	}

	// コントローライベントの無視（こちらからフレーム毎に状態を取得するため）
	SDL_GameControllerEventState(SDL_IGNORE);

	return true;
}

/*
@brief  終了処理
*/
void InputSystem::Shutdown()
{
	if (!controller)
	{
		SDL_GameControllerClose(controller);
	}
	controller = nullptr;
}

/*
@brief  Updateの準備をする（SDL_PollEventsの直前に呼ぶ）
*/
void InputSystem::PrepareForUpdate()
{
	//現在の入力状態を１フレーム前の入力状態にコピーする
	//キーボード
	memcpy(state.Keyboard.prevState,
		state.Keyboard.currState,
		SDL_NUM_SCANCODES);

	//マウス
	state.Mouse.prevButtons = state.Mouse.currButtons;
	state.Mouse.isRelative = false;
	state.Mouse.scrollWheel = Vector2::Zero;

	//コントローラー
	memcpy(state.Controller.prevButtons,
		state.Controller.currButtons,
		SDL_CONTROLLER_BUTTON_MAX);
}

/*
@brief  フレーム毎の処理（SDL_PollEventsの直後に呼ぶ）
*/
void InputSystem::Update()
{
	//マウス
	int x = 0, y = 0;
	if (state.Mouse.isRelative)
	{
		state.Mouse.currButtons =
			SDL_GetRelativeMouseState(&x, &y);
	}
	else
	{
		state.Mouse.currButtons =
			SDL_GetMouseState(&x, &y);
	}

	state.Mouse.mousePos.x = static_cast<float>(x) - 1024.0f / 2;
	state.Mouse.mousePos.y = 768.0f / 2 - static_cast<float>(y);

	//コントローラー
	//・ボタン
	for (int i = 0; i < SDL_CONTROLLER_BUTTON_MAX; i++)
	{
		state.Controller.currButtons[i] =
			SDL_GameControllerGetButton(controller,
				SDL_GameControllerButton(i));
	}


	// コントローラが無い場合は early exitする
	if (controller != NULL)
	{
		// 前のフレームのコントローラの状態をコピーする
		memcpy(&state.Controller.prevButtons, &state.Controller.currButtons, sizeof(Uint8) * SDL_CONTROLLER_BUTTON_MAX);

		// コントローラの状態を更新する
		SDL_GameControllerUpdate();

		// 現在のコントローラのボタン状態を保存
		for (int b = 0; b < SDL_CONTROLLER_BUTTON_MAX; ++b)
		{
			state.Controller.currButtons[b] = SDL_GameControllerGetButton(controller, (SDL_GameControllerButton)b);
		}

		// 現在のコントローラの軸情報を保存
		for (int a = 0; a < SDL_CONTROLLER_AXIS_MAX; ++a)
		{
			state.Controller.axisValues[a] = SDL_GameControllerGetAxis(controller, (SDL_GameControllerAxis)a);
		}

		// LPAD入力をベクトル化する
		const float maxInput = 32767.0f;
		state.Controller.lAxis.x = (float)state.Controller.axisValues[SDL_CONTROLLER_AXIS_LEFTX];
		state.Controller.lAxis.y = (float)state.Controller.axisValues[SDL_CONTROLLER_AXIS_LEFTY];

		//printf("%f\n", (float)state.Controller.axisValues[SDL_CONTROLLER_AXIS_LEFTX]);
		//スティックの入力に最低値を設ける(定数以下はカット)
		state.Controller.lAxis.x = (fabs(state.Controller.lAxis.x) < (float)7849) ? 0.0f : state.Controller.lAxis.x / maxInput;
		state.Controller.lAxis.y = (fabs(state.Controller.lAxis.y) < (float)8689) ? 0.0f : state.Controller.lAxis.y / maxInput;

	}
}

/*
@brief  SDLイベントをInputSystemに渡す
*/
void InputSystem::ProcessEvent(SDL_Event& _event)
{
	switch (_event.type)
	{
	case SDL_MOUSEWHEEL:
		state.Mouse.scrollWheel = Vector2(
			static_cast<float>(_event.wheel.x),
			static_cast<float>(_event.wheel.y));
		break;
	default:
		break;
	}
}

/*
@brief  マウスのモードを設定する
@param	true : 相対モード , false : デフォルトモード
*/
void InputSystem::SetRelativeMouseMode(bool _value)
{
	SDL_bool set = _value ? SDL_TRUE : SDL_FALSE;
	SDL_SetRelativeMouseMode(set);

	state.Mouse.isRelative = _value;
}

/*
@brief  入力された値（int）をフィルタリングする（範囲内に収めて-1.0~1.0にまとめる）
@param	入力された値（int）
@return	フィルタリングされた値
*/
float InputSystem::Filter1D(int _input)
{
	//デッドゾーン（この値より小さいなら0.0にする）
	const int deadZone = 250;
	//最大値（この値より大きくても1.0にする）
	const int maxValue = 30000;

	float retVal = 0.0f;

	//入力値の絶対値を取る
	int absValue = _input > 0 ? _input : -_input;
	//入力値がデッドゾーンより小さいなら
	if (absValue > deadZone)
	{
		//デッドゾーンと最大値の間で1.0以下になるよう計算する
		retVal = static_cast<float>(absValue - deadZone) /
			(maxValue - deadZone);
		//符号を元の値と同じにする
		retVal = _input > 0 ? retVal : -1.0f * retVal;
		//-1.0~1.0の間に収める
		retVal = Math::Clamp(retVal, -1.0f, 1.0f);
	}

	return retVal;
}

/*
@brief  入力された値（int）をフィルタリングする（範囲内に収めて0.0~1.0にまとめる）
@param	入力された値のx（int）
@param	入力された値のy（int）
@return	フィルタリングされた値
*/
Vector2 InputSystem::Filter2D(int _inputX, int _inputY)
{
	//デッドゾーン（この値より小さいなら0.0にする）
	const float deadZone = 8000.0f;
	//最大値（この値より大きくても1.0にする）
	const float maxValue = 30000.0f;

	//2次元ベクトルにする
	Vector2 dir;
	dir.x = static_cast<float>(_inputX);
	dir.y = static_cast<float>(_inputY);

	float length = dir.Length();

	//入力値のベクトルの長さがデッドゾーンより小さいなら
	if (length < deadZone)
	{
		dir = Vector2::Zero;
	}
	else
	{
		//デッドゾーンと最大値の間で1.0以下になるよう計算する
		float f = (length - deadZone) / (maxValue - deadZone);
		//0.0と1.0の間に収める
		f = Math::Clamp(f, 0.0f, 1.0f);
		//ベクトルを正規化して、分数の値にスケーリングする
		dir *= f / length;
	}

	return dir;
}