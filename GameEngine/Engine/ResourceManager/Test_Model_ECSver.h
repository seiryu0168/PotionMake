#pragma once
#include"../DirectX_11/Material.h"
#include<vector>
#include"../Coordinator.h"
#include"../DirectX_11/Fbx.h"
#include"../GameObject/GameObject.h"

//メッシュクラスとマテリアルクラスをコンポーネントとして置く
//モデルクラスで描画
class Test_Model_ECSver// : public Draw3DComponent
{
private:
	int hModel_;
	SHADER_TYPE type_;
	int animationFrame_;
	std::shared_ptr<Fbx> fbx_;
	std::vector<Entity> materialList_;
	Entity meshEntity_;
	GameObject* attachObject_;
public:
	Test_Model_ECSver();
	Test_Model_ECSver(GameObject* object);

	bool Load(const std::string& fileName);
	void RayCast(RayCastData& rayData);
	void SetShaderType(SHADER_TYPE type) { type_ = type; }
	void Draw();

};

