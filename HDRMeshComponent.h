#pragma once
#include "MeshComponent.h"

class GameObject;
class Shader;
class Mesh;

class HDRMeshComponent :
	public MeshComponent
{
public:
	HDRMeshComponent(GameObject* _owner, ShaderType _shaderType = DEFAULT);
	~HDRMeshComponent();

	/**
	@brief�@�`�揈��
	@param	�g�p����V�F�[�_�[�N���X�̃|�C���^
	*/
	virtual void Draw(Shader* _shader) override;

	void SetIntensity(float _intensity) { intensity = _intensity; }

	float GetIntensity()const { return intensity; }

private:
	float intensity;
};
