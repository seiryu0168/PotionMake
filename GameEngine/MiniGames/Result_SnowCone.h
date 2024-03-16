#pragma once
#include"../Result_Single.h"
#include"../Engine/Time.h"
class Result_SnowCone : public Result_Single<int>
{
	enum class CountStatus
	{
		STAY = 0,
		SHOW,
		FINISH,
	};

	std::unique_ptr<Time::Watch> time_;
	CountStatus status_;
	int resultTextNum_;
	int count_;
	float interval_;
	bool isChange_;
public:
	Result_SnowCone(Object* parent);
	~Result_SnowCone();

	void Initialize() override;
	void Update() override;
	void Stay();
	void Show();
	void Finish();
	void ShowCommand();
	void Create(int num);
	void Release() override;
};

