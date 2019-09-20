#pragma once
#include "Component.h"
#include "Collision.h"

class GameObject;

class ColliderComponent : public Component
{
public:
	ColliderComponent(GameObject* _owner, int _updateOrder = 100,int _collisionOrder = 100);
	virtual ~ColliderComponent();

	int GetCollisionOrder() const { return collisionOrder; }

	//オブジェクトが球に当たった時にめりこみからずらす処理
	virtual void ShiftObject(const Sphere& _hirSphere) {}
	//オブジェクトが平面に当たった時にめりこみからずらす処理
	virtual void ShiftObject(const Plane& _hitPlane) {}
	//オブジェクトがAABBに当たった時にめりこみからずらす処理
	virtual void ShiftObject(const AABB& _hitBox) {}
	//オブジェクトがカプセルに当たった時にめりこみからずらす処理
	virtual void ShiftObject(const Capsule& _hitCapsule) {}

private:
	bool isTrigger;
	//数値が大きい方を優先してめり込みから動かす処理をする（0以下は動かさない）
	int collisionOrder;
};

