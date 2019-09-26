#pragma once
#include "GameObject.h"

class PlayerObject;
class MeshComponent;
class SphereCollider;
class ObstacleBox;

class BikeObject : public GameObject
{
public:
	BikeObject(Game* _game, PlayerObject* _ownerObject);
    ~BikeObject();

    /**
    @brief	�t���[�����̏���
    @param	�Ō�̃t���[������������̂ɗv��������
    */
    virtual void UpdateGameObject(float _deltaTime) override;

    virtual void OnCollision(GameObject& _hitObject) override;

    void HitObstacle(const ObstacleBox & _hitObstacle);

    /**
    @brief	���͏���
    @param	InputState�\����
    */
    virtual void GameObjectInput(const InputState& _state)override;

private:

	void Animation();

    MeshComponent* meshComp;
    PlayerObject* ownerObject;
    SphereCollider* sphereCollider;

	bool animation;
	int animNum;
};
