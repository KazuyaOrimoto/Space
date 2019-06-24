#pragma once

#include <SDL_scancode.h>
#include <SDL_gamecontroller.h>
#include <SDL_mouse.h>
#include "Math.h"

//�{�^���̏�Ԃ�\��
enum ButtonState
{
	None,		//������Ă��Ȃ�
	Pressed,	//�������t���[��
	Released,	//�������t���[��
	Held		//������Ă����
};

//�L�[�{�[�h�̓��͊Ǘ��N���X
class KeyboardState
{
public:
	// InputSystem����e�ՂɍX�V�ł���悤�ɂ���
	friend class InputSystem;

	/**
	@brief	���݂̃L�[�̓��͏�Ԃ݂̂��擾����
	@param	SDL_Scancode�̃L�[�R�[�h
	@return	true : ������Ă��� , false : ������Ă��Ȃ�
	*/
	bool GetKeyValue(SDL_Scancode keyCode) const;

	/**
	@brief	���݂�1�t���[���O�̏�Ԃ���ButtonState��Ԃ�
	@param	SDL_Scancode�̃L�[�R�[�h
	@return	ButtonState�^�̌��݂̏��
	*/
	ButtonState GetKeyState(SDL_Scancode keyCode) const;
private:
	//���݂̃L�[�{�[�h�̓��͏��
	const Uint8* currState;
	//�P�t���[���O�̃L�[�{�[�h�̓��͏��
	Uint8 prevState[SDL_NUM_SCANCODES];
};

//�}�E�X�̓��͊Ǘ��N���X
class MouseState
{
public:
	// InputSystem����e�ՂɍX�V�ł���悤�ɂ���
	friend class InputSystem;

	/**
	@brief	���݂̃}�E�X�̃|�W�V�������擾����
	@return	Position
	*/
	const Vector2& GetPosition() const { return mousePos; }

	/**
	@brief	���݂̃}�E�X�̃X�N���[���z�C�[���̏�Ԃ��擾����
	@return	�X�N���[���ʁiVector2�j
	*/
	const Vector2& GetScrollWheel() const { return scrollWheel; }

	/**
	@brief	���΃}�E�X���[�h���ǂ������擾����
	@return	true : ���΃��[�h , false , �ʏ탂�[�h
	*/
	bool IsRelative() const { return isRelative; }

	/**
	@brief	���݂̓��͏�Ԃ݂̂��擾����
	@param	SDL_BUTTON�萔
	@return	true : ������Ă��� , false : ������Ă��Ȃ�
	*/
	bool GetButtonValue(int button) const;

	/**
	@brief	���݂�1�t���[���O�̏�Ԃ���ButtonState��Ԃ�
	@param	SDL_BUTTON�萔
	@return	ButtonState�^�̌��݂̏��
	*/
	ButtonState GetButtonState(int button) const;
private:
	//�}�E�X�̃|�W�V����
	Vector2 mousePos;
	//�X�N���[���z�C�[���̃X�N���[����
	Vector2 scrollWheel;
	// ���݂̃}�E�X�̓��͏��
	Uint32 currButtons;
	//�P�t���[���O�̃}�E�X�̓��͏��
	Uint32 prevButtons;
	// ���΃}�E�X���[�h���ǂ���
	bool isRelative;
};

// �R���g���[���[�̓��͊Ǘ��N���X
class ControllerState
{
public:
	// InputSystem����e�ՂɍX�V�ł���悤�ɂ���
	friend class InputSystem;

	/**
	@brief	���݂̓��͏�Ԃ݂̂��擾����
	@param	SDL_GameControllerButton�̃{�^���R�[�h
	@return	true : ������Ă��� , false : ������Ă��Ȃ�
	*/
	bool GetButtonValue(SDL_GameControllerButton button) const;

	/**
	@brief	���݂�1�t���[���O�̏�Ԃ���ButtonState��Ԃ�
	@param	SDL_GameControllerButton�̃{�^���R�[�h
	@return	ButtonState�^�̌��݂̏��
	*/
	ButtonState GetButtonState(SDL_GameControllerButton button) const;

	/**
	@brief	���̃X�e�B�b�N�̓��͒l���擾����
	@return	���͒l�i-1.0~1.0�j
	*/
	const Vector2& GetLeftStick() const { return leftStick; }

	/**
	@brief	�E�̃X�e�B�b�N�̓��͒l���擾����
	@return	���͒l�i-1.0~1.0�j
	*/
	const Vector2& GetRightStick() const { return rightStick; }

	/**
	@brief	���̃g���K�[�̓��͒l���擾����
	@return	���͒l�i0.0~1.0�j
	*/
	float GetLeftTrigger() const { return leftTrigger; }

	/**
	@brief	�E�̃g���K�[�̓��͒l���擾����
	@return	���͒l�i0.0~1.0�j
	*/
	float GetRightTrigger() const { return rightTrigger; }

	/**
	@brief	�R���g���[���[���ڑ�����Ă��邩
	@return	true : �ڑ�����Ă��� , false : �ڑ�����Ă��Ȃ�
	*/
	bool GetIsConnected() const { return isConnected; }
private:
	//���݂̃{�^���̓��͏��
	Uint8 currButtons[SDL_CONTROLLER_BUTTON_MAX];
	//�P�t���[���O�̃{�^���̓��͏��
	Uint8 prevButtons[SDL_CONTROLLER_BUTTON_MAX];
	//���̃X�e�B�b�N�̓��͒l
	Vector2 leftStick;
	//�E�̃X�e�B�b�N�̓��͒l
	Vector2 rightStick;
	//���̃g���K�[�̓��͒l
	float leftTrigger;
	//�E�̃g���K�[�̓��͒l
	float rightTrigger;
	//�R���g���[���[���ڑ�����Ă��邩
	bool isConnected;
};

//�e���͋@��̓��͏�Ԃ��܂Ƃ߂����b�p�[�\����
struct InputState
{
	KeyboardState Keyboard;
	MouseState Mouse;
	ControllerState Controller;
};

class InputSystem
{
public:
	/**
	@brief  ����������
	@return true : ���� , false : ���s
	*/
	bool Initialize();

	/**
	@brief  �I������
	*/
	void Shutdown();

	/**
	@brief  Update�̏���������iSDL_PollEvents�̒��O�ɌĂԁj
	*/
	void PrepareForUpdate();

	/**
	@brief  �t���[�����̏����iSDL_PollEvents�̒���ɌĂԁj
	*/
	void Update();

	/**
	@brief  SDL�C�x���g��InputSystem�ɓn��
	*/
	void ProcessEvent(union SDL_Event& event);

	/**
	@brief  ���݂̓��͏�Ԃ��擾����
	@return �iInputState�j�e���͏����܂Ƃ߂��\����
	*/
	const InputState& GetState() const { return state; }

	/**
	@brief  �}�E�X�̃��[�h��ݒ肷��
	@param	true : ���΃��[�h , false : �f�t�H���g���[�h
	*/
	void SetRelativeMouseMode(bool value);
private:
	/**
	@brief  ���͂��ꂽ�l�iint�j���t�B���^�����O����i�͈͓��Ɏ��߂�-1.0~1.0�ɂ܂Ƃ߂�j
	@param	���͂��ꂽ�l�iint�j
	@return	�t�B���^�����O���ꂽ�l
	*/
	float Filter1D(int input);

	/**
	@brief  ���͂��ꂽ�l�iint�j���t�B���^�����O����i�͈͓��Ɏ��߂�0.0~1.0�ɂ܂Ƃ߂�j
	@param	���͂��ꂽ�l��x�iint�j
	@param	���͂��ꂽ�l��y�iint�j
	@return	�t�B���^�����O���ꂽ�l
	*/
	Vector2 Filter2D(int inputX, int inputY);

	//�e���͋@��̓��͏�Ԃ��܂Ƃ߂����b�p�[�\����
	InputState state;
	//SDL�ŃR���g���[���[��F�����邽�߂̃N���X�|�C���^
	SDL_GameController* controller;
};