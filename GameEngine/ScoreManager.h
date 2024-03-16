#pragma once
#include<vector>
template<typename T>
class ScoreManager
{
protected:
	std::vector<T> playerScores_;
public:
	ScoreManager() {};
	ScoreManager(unsigned short playerCount,T initScore);
	~ScoreManager();

	virtual void ScoreUpdate(const unsigned short& playerNum, T Score) {};
};

template<typename T>
inline ScoreManager<T>::ScoreManager(unsigned short playerCount, T initScore)
{
	for (int i = 0; i < playerCount; i++)
	{
		playerScores_.push_back(initScore);
	}
}

template<typename T>
inline ScoreManager<T>::~ScoreManager()
{
}
