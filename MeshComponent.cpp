﻿//=============================================================================
//	@file	MeshComponent.cpp
//	@brief	メッシュの描画をするコンポーネント
//	@autor	居本 和哉
//	@date	2020/02/29
//=============================================================================

#include "MeshComponent.h"
#include "GameObject.h"
#include "Game.h"
#include "Shader.h"
#include "Mesh.h"
#include "Renderer.h"
#include "VertexArray.h"
#include "Texture.h"

/**
@param	アタッチするゲームオブジェクトのポインタ
*/
MeshComponent::MeshComponent(GameObject* _owner)
    :Component(_owner)
    , mMesh(nullptr)
    , mTextureIndex(0)
	, visible(true)
{
}

MeshComponent::~MeshComponent()
{
	RENDERER->RemoveMeshComponent(this);
}

/**
@brief　描画処理
@param	使用するシェーダークラスのポインタ
*/
void MeshComponent::Draw(Shader* _shader)
{
	if (!visible)
	{
		return;
	}
    if (mMesh)
    {
        // Set the world transform
        _shader->SetMatrixUniform("uWorldTransform",
            owner->GetWorldTransform());
        // Set specular power
        _shader->SetFloatUniform("uSpecPower", mMesh->GetSpecPower());
        // Set the active texture
        Texture* t = mMesh->GetTexture(mTextureIndex);
        if (t)
        {
            t->SetActive();
        }
        // Set the argMesh's vertex array as active
        VertexArray* va = mMesh->GetVertexArray();
        va->SetActive();
        // Draw
        glDrawElements(GL_TRIANGLES, va->GetNumIndices(), GL_UNSIGNED_INT, nullptr);
    }
}
