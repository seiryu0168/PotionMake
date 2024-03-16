#pragma once
#include"../Result_Single.h"
#include"../Engine/Time.h"
class Result_Shooting : public Result_Single<int>
{
	enum class CountStatus
	{
		STAY=0,
		SHOW,
		FINISH,
	};
	int resultTextNum_;
	int buttonImageNum_;	
	int perfectTextNum_;
	int returnText_;
	int count_;
	bool isChange_;
	float interval_;
	CountStatus status_;
	std::unique_ptr<Time::Watch> time_;
public:
	Result_Shooting(Object* parent);
	~Result_Shooting();

	void Initialize() override;
	void Update() override;
	void Stay();
	void ShowResult();
	void ShowCommand();
	void Finish();
	void Release() override;
};

