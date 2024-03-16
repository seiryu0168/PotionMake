#pragma once

//ストップウォッチのような機能を持つ名前空間
namespace Time
{
	//Timeと同じように個別で使用可能なクラス
	class Watch
	{
		bool Lock_;		//現在の状態で固定するか
		bool CountDown_;	//カウントダウンかカウントアップか
		int MilliSeconds_;	//経過時間

	public:
		Watch();
		Watch(int sec);
		~Watch();

		//時間を初期化
		void Reset();

		//時間の更新を一時停止
		void Lock();

		//時間の更新を再開
		void UnLock();

		//呼び出し時点の時間を取得
		int GetMilliSeconds() const;

		template<typename T = int>
		T GetSeconds() const
		{
			return (T)GetMilliSeconds() / 1'000;
		}

		int GetMinutes() const;
		int GetHours() const;

		void AddMilliSeconds(int mil);

		//カウントダウンまたはカウントアップに変更
		//true = カウントダウン, false = カウントアップ
		void SetCountdown(bool c) { CountDown_ = c; }

		//カウントダウン状態かどうか
		bool IsCountDown() const;
		bool IsLock() const { return Lock_; }
		template<typename T = int>
		void SetSecond(T second)
		{
			MilliSeconds_ = (int)(second * 1'000);
		}
	};	//class Watch

	//初期化
	void Initialize();

	//更新(Mainで呼び出し)
	void Update();

	//時間を初期化
	void Reset();

	//時間の更新を一時停止
	void Lock();

	//時間の更新を再開
	void UnLock();

	//呼び出し時点の時間を取得
	int GetMilliSeconds();

	template<typename T = int>
	T GetSeconds()
	{
		return (T)GetMilliSeconds() / 1'000;
	}
	
	int GetMinutes();
	int GetHours();

	void Release();
};

