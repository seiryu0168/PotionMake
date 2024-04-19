#pragma once
#include"Engine/GameObject/GameObject.h"
class Play_CollectionPart_StageManager : public GameObject
{

public:
	Play_CollectionPart_StageManager(Object* parent);
	~Play_CollectionPart_StageManager();

	void Initialize() override;
	void Update() override;
	void Release() override;
};

