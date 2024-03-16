#pragma once
#include"../Engine/GameObject/GameObject.h"
#include"../Engine/Time.h"
class SnowCone_ToppingMenu : public GameObject
{
protected:
	enum class SELECT_STATE
	{
		INPUT=0,
		MOVE,
		STAY,
	};
	std::unique_ptr<Time::Watch> time_;
	short moveDir_;
	int selectNum_;
	int hAudio_CursorMove_;
	int hAudio_PushButton_;
	SELECT_STATE state_;
public:
	SnowCone_ToppingMenu(Object* parent,const std::string& name);
	~SnowCone_ToppingMenu();
	void Initialize() override;
	void Reset();
	void Release() override;
};

