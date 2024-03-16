#pragma once
#include "../DirectX_11/Direct3D.h"
#include <DirectXMath.h>
class Camera
{
	XMVECTOR position_;			//カメラの位置（視点）
	XMVECTOR target_;			//見る位置（焦点）
	XMVECTOR upVector_;			//上ベクトル
	XMMATRIX viewMatrix_;		//ビュー行列
	XMMATRIX projMatrix_;		//プロジェクション行列
	XMMATRIX billBoardMatrix_;	//ビルボード行列
	float	 angleOfView_;		//視野角
	float	 aspectRadio_;		//アスペクト比
	float	 nearClipping_;		//ニアクリッピング
	float	 farClipping_;		//ファークリッピング
	D3D11_VIEWPORT viewPort_;	//ビューポート
public:
	Camera();
	void Initialize(float width, float height, float nearClipping, float farClipping);
	void Update();
	//視点（カメラの位置）を設定
	void SetPosition(XMVECTOR position);

	//焦点（見る位置）を設定
	void SetTarget(XMVECTOR target);

	//カメラの上方向ベクトルを設定
	void SetUpVector(XMVECTOR upVector);

	/// <summary>
	/// プロジェクション行列を設定
	/// </summary>
	/// <param name="aov">画角</param>
	/// <param name="aspectRadio">アスペクト比</param>
	/// <param name="nearZ">ニアクリッピング</param>
	/// <param name="farZ">ファークリッピング</param>
	void SetProjection(float aov, float aspectRadio, float nearZ, float farZ);

	/// <summary>
	/// 画角設定
	/// </summary>
	/// <param name="aov">画角</param>
	void SetAOV(float aov);

	/// <summary>
	/// アスペクト比設定
	/// </summary>
	/// <param name="aspect">アスペクト比</param>
	void SetAspectRadio(float aspect);

	/// <summary>
	/// クリッピング範囲設定
	/// </summary>
	/// <param name="nearZ">ニアクリッピング</param>
	/// <param name="farZ">ファークリッピング</param>
	void SetClipping(float nearZ, float farZ);

	void SetViewPort(float width, float height, float minDepth, float maxDepth, float topLeftX, float topLeftY);

	//視点(見える位置)を取得
	XMFLOAT3 GetPosition();

	//焦点取得
	XMVECTOR GetTarget() { return target_; }

	//ビュー行列を取得
	XMMATRIX GetViewMatrix() { return viewMatrix_; }

	//ビルボード用回転行列
	XMMATRIX GetBillBoardMatrix() { return billBoardMatrix_; }

	//プロジェクション行列を取得
	XMMATRIX GetProjectionMatrix() { return projMatrix_; }

	D3D11_VIEWPORT GetViewPort() { return viewPort_; }

};

