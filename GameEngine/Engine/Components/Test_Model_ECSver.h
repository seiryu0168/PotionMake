#pragma once
#include"../DirectX_11/Material.h"
#include<vector>
//#include"../Coordinator.h"
#include"../DirectX_11/Fbx.h"
#include"../GameObject/GameObject.h"

//メッシュクラスとマテリアルクラスをコンポーネントとして置く
//モデルクラスで描画
class Test_Model_ECSver// : public Draw3DComponent
{
private:
	bool isDraw_;
	SHADER_TYPE type_;
	int animationFrame_;
	std::shared_ptr<Fbx> fbx_;
	std::vector<Entity> materialList_;
	Entity meshEntity_;
	GameObject* attachObject_;

	int layerNum_;
public:
	Test_Model_ECSver();
	Test_Model_ECSver(GameObject* object, int layerNum = 0);

	//モデルのロード
	bool Load(const std::string& fileName);

	//レイキャスト(未検証)
	void RayCast(RayCastData& rayData);

	//シェーダータイプ設定
	void SetShaderType(SHADER_TYPE type) { type_ = type; }

	/// <summary>
	/// ボーンの位置取得
	/// </summary>
	/// <param name="boneName">ボーン名</param>
	/// <returns>ボーン位置</returns>
	const XMVECTOR GetBone(const std::string& boneName);
	/// <summary>
	/// ボーンの位置取得
	/// </summary>
	/// <param name="partsNum">パーツ番号</param>
	/// <param name="num">ボーンの番号</param>
	/// <returns>ボーン位置</returns>
	const XMVECTOR GetBone(const UINT& partsNum,const UINT& num);
	/// <summary>
	/// ボーン名取得
	/// </summary>
	/// <param name="partsNum">パーツ番号</param>
	/// <param name="num">ボーンの番号</param>
	/// <returns>ボーン名</returns>
	const std::string GetBoneName(const UINT& partsNum, const UINT& num);
	/// <summary>
	/// ボーン番号取得
	/// </summary>
	/// <returns>ボーン番号</returns>
	const UINT GetBoneCount();
	//描画するかどうか
	const bool IsDraw() { return isDraw_; }
	//描画フラグの設定
	void SetDraw(bool isDraw) { isDraw_ = isDraw; }
	/// <summary>
	/// モデルの色を変える
	/// </summary>
	/// <param name="partsNum">パーツ番号</param>
	/// <param name="materialNum">マテリアル番号</param>
	/// <param name="color">色</param>
	void SetCustomColor(int partsNum,int materialNum,const XMFLOAT4& color);
	//アタッチされているオブジェクトを返す
	GameObject* GetAttachedObject() { return attachObject_; }
	//描画
	void Draw();
	//描画レイヤーありの描画
	void Draw(int layerNum);
	//Transform指定の描画
	void Draw(Transform transform, SHADER_TYPE type, int frame);

};

