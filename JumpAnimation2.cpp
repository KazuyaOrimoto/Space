#include "JumpAnimation2.h"
#include "GameObject.h"
#include "MainCamera.h"


JumpAnimation2::JumpAnimation2(GameObject* _gameObject, MainCamera* _camera)
	:AnimationClip(_gameObject,20)
{
	rad = Math::ToRadians(-40);
	right = owner->GetRight();
	camera = _camera;

}

JumpAnimation2::~JumpAnimation2()
{
}

void JumpAnimation2::Update(float deltaTime)
{
	//�|�W�V�����̃A�j���[�V����
	Vector3 playerPos = owner->GetParent()->GetPosition();
	Vector3 nextPos = playerPos + owner->GetUp() * 20.0f * (20 - animationCount);
	owner->SetPosition(nextPos);

	//��]�̃A�j���[�V����
	float r = Math::Lerp(rad, -(rad/2), ((float)animationCount / (float)animationChangeCount));
	Quaternion rot = owner->GetParent()->GetRotation();
	Quaternion inc(right, r);
	Quaternion NextRot = Quaternion::Concatenate(rot, inc);
	owner->SetRotation(NextRot);

	//�J�����̃A�j���[�V����
	float vert = camera->GetVertDist();
	float horz = camera->GetHorzDist();

	camera->SetVertDist(vert + 25.0f);
	camera->SetHorzDist(horz + 25.0f);

}