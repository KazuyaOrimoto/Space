﻿//=============================================================================
//	@file	Shader.h
//	@brief	シェーダーの管理
//	@autor	居本 和哉
//	@date	2020/02/29
//=============================================================================

#pragma once

#include <glew.h>
#include <string>
#include "Math.h"

class Shader
{
public:
	Shader();
	~Shader();
	/**
	@brief	頂点シェーダーとフラグメントシェーダーのロード
	@param	頂点シェーダーのファイル名
	@param	頂点シェーダーのファイル名
	@return	true : 成功 , false : 失敗
	*/
	bool Load(const std::string& _vertName, const std::string& _fragName);
	/**
	@brief	ロードしたシェーダーの解放
	*/
	void Unload();

	/**
	@brief	シェーダープログラムをアクティブにする
	*/
	void SetActive();

	/**
	@brief	行列のUniform変数を設定する
	@param	設定するUniform変数名
	@param	設定する行列
	*/
	void SetMatrixUniform(const char* _name, const Matrix4& _matrix);

	/**
	@brief	Vector3のUniform変数を設定する
	@param	設定するUniform変数名
	@param	設定するVector3
	*/
	void SetVectorUniform(const char* _name, const Vector3& _vector);

	/**
	@brief	floatのUniform変数を設定する
	@param	設定するUniform変数名
	@param	設定するfloat
	*/
	void SetFloatUniform(const char* _name, const float& _value);

	/**
	@brief	boolのUniform変数を設定する
	@param	設定するUniform変数名
	@param	設定するbool
	*/
	void SetBoolUniform(const char* _name, const bool& _value);

	/**
	@brief	floatのUniform配列を設定する
	@param	設定するUniform変数名
	@param	設定するfloat
	*/
	void SetFloatArrayUniform(const char* _name, const int _size, const float* const & _value);	

	/**
	@brief	floatのUniform配列を設定する
	@param	設定するUniform変数名
	@param	設定するfloat
	*/
	void SetFloatArrayUniform(const char* _name, const int _size, double* const & _value);

	/**
	@brief	intのUniform変数を設定する
	@param	設定するUniform変数名
	@param	設定するint
	*/
	void SetIntUniform(const char* _name, const int & _value);

private:
	/**
	@brief	シェーダーをコンパイルする
	@param	コンパイルするシェーダーのファイル名
	@param	シェーダーの種類
	@param	シェーダーのID用の参照変数
	@return	true : 成功 , false : 失敗
	*/
	bool CompileShader(const std::string& _fileName, GLenum _shaderType, GLuint& _outShader);

	/**
	@brief	シェーダーがコンパイル出来ているか確認
	@param	シェーダーのID
	@return	true : 成功 , false : 失敗
	*/
	bool IsCompiled(GLuint _shader);
	/**
	@brief	シェーダーがリンク出来ているか確認
	@param	シェーダーのID
	@return	true : 成功 , false : 失敗
	*/
	bool IsVaildProgram();

	GLuint vertexShader;
	GLuint fragShader;
	GLuint shaderProgram;
};

