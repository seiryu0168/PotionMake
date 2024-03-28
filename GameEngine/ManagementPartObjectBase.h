#pragma once
#include"Engine/GameObject/GameObject.h"
/// <summary>
/// 経営パートでアクセス出来るオブジェクトの基底クラス
/// 開くUIの番号と何をするかのテキストを持つ
/// </summary>
class ManagementPartObjectBase : public GameObject
{
protected:
	int accessUINum_;
	std::string actionName_;
public:
	ManagementPartObjectBase(Object* parent, std::string name);
	~ManagementPartObjectBase();
	int GetAccessUINumber() { return accessUINum_; }
	std::string GetActionName() { return actionName_; }
};

