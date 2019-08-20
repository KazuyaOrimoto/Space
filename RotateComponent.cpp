#include "RotateComponent.h"
#include "GameObject.h"
#include "InputSystem.h"
#include "Renderer.h"

RotateComponent::RotateComponent(GameObject* argOwner, int argUpdateOrder)
	: Component(argOwner)
	, right(true)
	, f(1)
	, canMove(true)
	, moveTorque(3)
{
}

/**
@brief	�t���[�����̏���
@param	�Ō�̃t���[������������̂ɗv��������
*/
void RotateComponent::Update(float argDeltaTime)
{
	ownerPos = owner->GetPosition();
	cameraQuat = owner->GetRotation();
    if (canMove)
    {
		//�E�̕ǂɂ����Ƃ�
        if (ownerPos.y > 850)
        {
			HitRightWall();
        }
        //���̕ǂɂ����Ƃ�
        else if (ownerPos.y < -850)
        {
			HitLeftWall();
        }
        //��̕ǂɂ����Ƃ�
        else if (ownerPos.z > 1850)
        {
			HitTopWall();
        }
        //���̕ǂɂ����Ƃ�
        else if (ownerPos.z < 150)
        {
			HitUnderWall();
        }
		//�ǂ̕ǂɂ����Ă��Ȃ��Ƃ�
		else
		{
			if (f < 1.0)
			{
				f += 0.2f;
				cameraQuat = Quaternion::Slerp(moveRot, target, f);

			}
			else if (f > 1.0)
			{
				f = 1.0f;
				cameraQuat = Quaternion::Slerp(moveRot, target, f);
			}
		}
    }
	//�ړ����ł��Ȃ����
	else
	{
		MoveWall();
	}

}

/**
@brief	���͏���
@param	InputState�\����
*/
void RotateComponent::ProcessInput(const InputState & state)
{
	if (!canMove)
	{
		return;
	}
	if (state.Keyboard.GetKeyState(SDL_SCANCODE_D))
	{
		if (state.Keyboard.GetKeyState(SDL_SCANCODE_D) == ButtonState::Pressed)
		{
			f = 0.0f;
		}
		float rad = Math::ToRadians(moveTorque);
		Quaternion inc(Vector3::UnitX, rad);
		target = Quaternion::Concatenate(rot, inc);
		moveRot = cameraQuat;
	}
	else if (state.Keyboard.GetKeyState(SDL_SCANCODE_A))
	{
		if (state.Keyboard.GetKeyState(SDL_SCANCODE_A) == ButtonState::Pressed)
		{
			f = 0.0f;
		}
		float rad = Math::ToRadians(-moveTorque);
		Quaternion inc(Vector3::UnitX, rad);
		target = Quaternion::Concatenate(rot, inc);
		moveRot = cameraQuat;
	}
	else
	{
		if (state.Keyboard.GetKeyState(SDL_SCANCODE_D) == ButtonState::Released || state.Keyboard.GetKeyState(SDL_SCANCODE_A) == ButtonState::Released)
		{
			f = 0.0f;
		}
		target = rot;
		moveRot = cameraQuat;
	}
}

//�ǈړ�
void RotateComponent::MoveWall()
{
	if (f < 1.0)
	{
		f += 0.2f;
		Quaternion temp = Quaternion::Slerp(rot, target, f);
		owner->SetRotation(temp);

	}
	else if (f > 1.0)
	{
		f = 1.0f;
		owner->SetRotation(target);
	}
	else
	{
		canMove = true;
		rot = target;
	}
}

void RotateComponent::HitRightWall()
{
	//���̃t���[���œ��͂��ꂽ�̂��E�Ȃ�E��]�A���Ȃ獶��]�p�̊p�x��������
	float rad = right ? Math::ToRadians(90.0f) : Math::ToRadians(-90.0f);
	rot = owner->GetRotation();
	Quaternion inc(Vector3::UnitX, rad);
	target = Quaternion::Concatenate(rot, inc);
	owner->SetPosition(Vector3(ownerPos.x, 850.0f, ownerPos.z));
	f = 0;
	canMove = false;

	DirectionalLight& dir = RENDERER->GetDirectionalLight();
	dir.direction = Vector3::Transform(dir.direction, inc);
}

void RotateComponent::HitLeftWall()
{
	//���̃t���[���œ��͂��ꂽ�̂��E�Ȃ�E��]�A���Ȃ獶��]�p�̊p�x��������
	float rad = right ? Math::ToRadians(90.0f) : Math::ToRadians(-90.0f);
	rot = owner->GetRotation();
	Quaternion inc(Vector3::UnitX, rad);
	target = Quaternion::Concatenate(rot, inc);
	owner->SetPosition(Vector3(ownerPos.x, -850.0f, ownerPos.z));
	f = 0;
	canMove = false;

	DirectionalLight& dir = RENDERER->GetDirectionalLight();
	dir.direction = Vector3::Transform(dir.direction, inc);
}

void RotateComponent::HitTopWall()
{
	//���̃t���[���œ��͂��ꂽ�̂��E�Ȃ�E��]�A���Ȃ獶��]�p�̊p�x��������
	float rad = right ? Math::ToRadians(90.0f) : Math::ToRadians(-90.0f);
	rot = owner->GetRotation();
	Quaternion inc(Vector3::UnitX, rad);
	target = Quaternion::Concatenate(rot, inc);
	owner->SetPosition(Vector3(ownerPos.x, ownerPos.y, 1850));
	f = 0;
	canMove = false;

	DirectionalLight& dir = RENDERER->GetDirectionalLight();
	dir.direction = Vector3::Transform(dir.direction, inc);
}

void RotateComponent::HitUnderWall()
{
	//���̃t���[���œ��͂��ꂽ�̂��E�Ȃ�E��]�A���Ȃ獶��]�p�̊p�x��������
	float rad = right ? Math::ToRadians(90.0f) : Math::ToRadians(-90.0f);
	rot = owner->GetRotation();
	Quaternion inc(Vector3::UnitX, rad);
	target = Quaternion::Concatenate(rot, inc);
	owner->SetPosition(Vector3(ownerPos.x, ownerPos.y, 150));
	f = 0;
	canMove = false;

	DirectionalLight& dir = RENDERER->GetDirectionalLight();
	dir.direction = Vector3::Transform(dir.direction, inc);
}