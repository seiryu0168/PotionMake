#pragma once
#include"../ECS/System.h"
#include"../Coordinator.h"
#include"../Components/Collider.h"
class ColliderSystem : public System
{
private:
	ID3D11Buffer* pVertexBuffer_;	//頂点バッファ
	ID3D11Buffer* pIndexBuffer_;	//インデックスバッファ
	ID3D11Buffer* pConstantBuffer_;	//コンスタントバッファ

	struct CONSTANT_BUFFER
	{
		XMMATRIX matWorld;
		XMMATRIX matUVTrans;
		XMFLOAT4 color;
		XMFLOAT4 ChangeColor;
	};
public:
	ColliderSystem();
	~ColliderSystem() {};
	void Update() override;
	void Draw(int drawLayer = 0) override;
	void Release() override;
	void CheckRemove() override;
	/// <summary>
	/// どれとどれが当たってるかチェック
	/// </summary>
	/// <param name="firstTarget">チェックされるコライダー</param>
	/// <param name="secondTarget">チェックするコライダー</param>
	void CheckCollision(Collider* firstTarget, Collider* secondTarget) const;
	//ボックス同士の当たり判定
	bool IsHitBox_Box(Collider* firstTarget, Collider* secondTarget) const;
	//ボックスと球の当たり判定
	bool IsHitBox_Sphere(Collider* firstTarget, Collider* secondTarget) const;
	//球と球の当たり判定	
	bool IsHitSphere_Sphere(Collider* firstTarget, Collider* secondTarget) const;

};

