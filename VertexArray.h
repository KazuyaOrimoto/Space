#pragma once
class VertexArray
{
public:
	/**
	@param	頂点バッファの配列のポインタ
	@param	頂点数
	@param	インデックスバッファの配列のポインタ
	@param	インデックスの数
	*/
	VertexArray(const float* argVerts, unsigned int argNumVerts,
		const unsigned int* argIndices, unsigned int argNumIndices);
	~VertexArray();

	/**
	@brief	頂点配列をアクティブにする（描画に使用できるようにする）
	*/
	void SetActive();

	unsigned int GetNumIndices() const { return numIndices; }
	unsigned int GetNumVerts() const { return numVerts; }

private:
	//頂点バッファにある頂点の数
	unsigned int numVerts;
	//インデクスバッファにあるインデックスの数
	unsigned int numIndices;
	//頂点バッファのOpenGL ID
	unsigned int vertexBuffer;
	//インデックスバッファのOpenGL ID
	unsigned int indexBuffer;
	//頂点配列オブジェクトのOpenGL ID
	unsigned int vertexArray;
};

