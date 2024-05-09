#pragma once
#include"../../Engine/GameObject/GameObject.h"
enum class ResourceMenuMode
{
	ResourceSelect=0,
	ProcessSelect,
};
/// <summary>
/// ポーションの素材を表示するUI
/// </summary>
class P_MP_CraftUI_ResourceStockUI : public GameObject
{
private:
	ResourceMenuMode mode_;
	std::vector<GameObject*> resourceObjects_;
	std::vector<GameObject*> processObjects_;
	int uiImageNumArray[3];
public:
	XMFLOAT3 uiPos_;
	P_MP_CraftUI_ResourceStockUI(Object* parent);
	~P_MP_CraftUI_ResourceStockUI();
	void Initialize() override;
	void Start() override;
	void Update() override;
	void CreateBase();
	void CreateUITitle(XMFLOAT2 pos,XMFLOAT2 diff,const std::string& str);
	void ChangeTitle(XMFLOAT2 pos, XMFLOAT2 diff,const std::string& str);
	void ModeChange(ResourceMenuMode mode);
	void Release() override;
};