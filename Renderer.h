#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <SDL.h>
#include "Math.h"

#define RENDERER Renderer::GetInstance()

//平行光源用の構造体
struct DirectionalLight
{
    // 光の方向
    Vector3 direction;
    // 拡散反射色
    Vector3 diffuseColor;
    // 鏡面反射色
    Vector3 specColor;
};

class SpriteComponent;
class Texture;
class Mesh;
class Game;
class MeshComponent;
class Shader;
class VertexArray;

class Renderer
{
public:
	/**
	@brief  インスタンスを取得する
	@return Rendererクラスのインスタンス
	*/
	static Renderer* GetInstance() { return renderer; }

	/**
	@brief  インスタンスを作成する
	*/
	static void CreateInstance();

	/**
	@brief  インスタンスを削除する
	*/
	static void DeleteInstance();

	/**
	@brief  初期化処理
	@return true : 成功 , false : 失敗
	*/
    bool Initialize(float argScreenWidth, float argScreenHeight);
	/**
	@brief  終了処理
	*/
    void Shutdown();

	/**
	@brief  ロードしたデータの解放
	*/
    void UnloadData();

	/**
	@brief  描画処理
	*/
    void Draw();

	/**
	@brief  スプライトの追加
	@param	追加するSpriteComponentクラスのポインタ
	*/
	void AddSprite(SpriteComponent* argSpriteComponent);

	/**
	@brief  スプライトの削除
	@param	削除するSpriteComponentクラスのポインタ
	*/
	void RemoveSprite(SpriteComponent* argSpriteComponent);

	/**
	@brief  テクスチャの取得
	@param	取得したいテクスチャのファイル名
	@return Textureクラスのポインタ
	*/
	Texture* GetTexture(const std::string& argFileName);

	/**
	@brief  メッシュコンポーネントの追加
	@param	追加するMeshComponentクラスのポインタ
	*/
    void AddMeshComponent(MeshComponent* argMeshComponent);

	/**
	@brief  メッシュコンポーネントの削除
	@param	削除するMeshComponentクラスのポインタ
	*/
    void RemoveMeshComponent(MeshComponent* argMeshComponent);

	/**
	@brief  メッシュの取得
	@param	取得したいメッシュのファイル名
	@return Meshクラスのポインタ
	*/
    Mesh* GetMesh(const std::string& argFileName);

	/**
	@brief	ビュー行列を設定する
	@param	ビュー行列
	*/
    void SetViewMatrix(const Matrix4& argView) { view = argView; }

	/**
	@brief	環境光を設定する
	@param	Vector3（環境光を表す）
	*/
    void SetAmbientLight(const Vector3& argAmbient) { ambientLight = argAmbient; }

	/**
	@brief	平行光源の構造体を取得する
	@return	DirectionalLight（平行光源の構造体）
	*/
    DirectionalLight& GetDirectionalLight() { return dirLight; }

	/**
	@brief	スクリーンの横幅を取得する
	@return	スクリーンの横幅
	*/
    float GetScreenWidth() const { return screenWidth; }
	
	/**
	@brief	スクリーンの縦幅を取得する
	@return	スクリーンの縦幅
	*/
	float GetScreenHeight() const { return screenHeight; }

private:
	//コンストラクタ、デストラクタの隠蔽
	Renderer();
	~Renderer();

	//自分のインスタンス
	static Renderer* renderer;

	/**
	@brief  シェーダーの読み込み
	@return true : 成功 , false : 失敗
	*/
    bool LoadShaders();
	/**
	@brief  Sprite用の頂点バッファとインデックスバッファの作成
	*/
    void CreateSpriteVerts();

	/**
	@brief  光源情報をシェーダーの変数にセットする
	@param  セットするShaderクラスのポインタ
	*/
    void SetLightUniforms(Shader* argShader);

    //ファイル名でメッシュを取得するための可変長コンテナ
    std::unordered_map<std::string, Mesh*> meshes;
    //メッシュコンポーネントのポインタの可変長コンテナ
    std::vector<MeshComponent*> meshComponents;
	//スプライトコンポーネントのポインタの可変長コンテナ
	std::vector<SpriteComponent*> sprites;
	//ファイル名でテクスチャを取得するための可変長コンテナ
	std::unordered_map<std::string, Texture*>textures;

	//クラスのポインタ

    Shader* spriteShader;
    VertexArray* spriteVerts;
    Shader* meshShader;

    //ビュー行列
    Matrix4 view;
	//射影行列
    Matrix4 projection;
    //スクリーンの横幅
    float screenWidth;
	//スクリーンの縦幅
    float screenHeight;
    //環境光
    Vector3 ambientLight;
	//平行光源
    DirectionalLight dirLight;
    //ウィンドウ
    SDL_Window* window;
    //コンテキスト
    SDL_GLContext context;
};