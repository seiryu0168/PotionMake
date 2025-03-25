#pragma once
#include"../ECS/System.h"
#include"../Coordinator.h"
#include"../Components/Collider.h"
class ColliderSystem : public System
{
private:
	ID3D11Buffer* pBoxVertexBuffer_;	//頂点バッファ
	ID3D11Buffer* pBoxIndexBuffer_;	//インデックスバッファ
	ID3D11Buffer* pBoxConstantBuffer_;	//コンスタントバッファ

	ID3D11Buffer* pSphereVertexBuffer_;	//頂点バッファ
	ID3D11Buffer* pSphereIndexBuffer_;	//インデックスバッファ
	ID3D11Buffer* pSphereConstantBuffer_;	//コンスタントバッファ

	//分割した空間の配列
	std::vector<std::list<Entity>> cellAllay_;
	//衝突対応リスト
	std::vector<Entity> collisionList_;
	//最大分割数
	USHORT maxDivision_;

	struct CONSTANT_BUFFER
	{
		XMMATRIX matWVP;			//ワールド、ビュー、プロジェクション行列の合成(頂点変換に使う)
		XMMATRIX matW;				//ワールド行列
		XMMATRIX matNormal;			//回転行列と拡大行列の合成(法線の変形に使う)
	};

	const struct VERTEX
	{
		XMVECTOR position;
		//XMVECTOR uv
	};

	VERTEX boxVertices_[8] = 
	  { {XMVectorSet(-1,1,-1,0)},
		{XMVectorSet(1,1,-1,0)},
		{XMVectorSet(1,-1,-1,0)},
		{XMVectorSet(-1,-1,-1,0)},
		{XMVectorSet(-1,1,1,0)},
		{XMVectorSet(1,1,1,0)},
		{XMVectorSet(1,-1,1,0)},
		{XMVectorSet(-1,-1,1,0)}
	  };

	VERTEX sphereVertices_[36];
	//CONSTANT_BUFFER boxCb;
	//CONSTANT_BUFFER sphereCb;

	int boxIndex[36] = { 0,1,3, 0,1,2, 1,6,2, 1,5,6, 5,7,6, 5,4,7, 4,3,7, 4,0,3, 0,4,5, 0,5,1, 2,7,3, 2,6,7 };

	void CreateVB();
	void CreateIB();
	void CreateCB();
public:
	ColliderSystem();
	~ColliderSystem() {};
	void Update() override;
	void Draw(int drawLayer = 0) override;
	std::vector<std::list<Entity>>& GetCellList() { return cellAllay_; }
	void Release() override;
	void CheckRemove() override;
	//8分木空間分割を利用した当たり判定チェック
	void CheckCollision_Octree();
	//衝突対応リスト作成
	void CreateCollisionList(UINT accessNum);

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
	//カプセルとボックスの当たり判定
	bool IsHitCapsule_Box(Collider* firstTarget, Collider* secondTarget) const;
	//カプセル同士の当たり判定
	bool IsHitCapsule_Capsule(Collider* firstTarget, Collider* secondTarget) const;
	//OBBコライダー同士の当たり判定
	bool IsHitOBB_OBB(Collider* firstTarget, Collider* secondTarget) const;

};

