#pragma once
//#include"Engine/GameObject/GameObject.h"
#include"Engine/ResourceManager/json.hpp"
#include"StandData.h"
#include"Engine/SAFE_DELETE_RELEASE.h"
#include<vector>
#include<variant>
using json = nlohmann::json;

//enum class GAME_ID : int
//{
//	SHOOTING = 0,
//	CHICKENRACE,
//	COMMANDMEMORY,
//	SNOWCONE,
//};
//
//struct SNOWCONE_DATA
//{
//	int size_;
//	int syrup;
//	int topping_;
//};

namespace InterSceneData
{
	//class StandData
	//{
	//public:
	//	std::string dataName_;
	//};
	//std::vector<std::string> typeArray_;
	///// <summary>
	///// �V�[���ԃf�[�^�Ƃ��Ĉ����f�[�^����ǉ�
	///// </summary>
	///// <typeparam name="T">�f�[�^�̌^</typeparam>
	///// <returns>�ǉ��o������true�A�ǉ��ł��Ȃ�������(���ɂ�������)false</returns>
	//template<class T>
	//bool AddDataType()
	//{
	//	for (std::string name : typeArray_)
	//	{
	//		if (name == typename(T))
	//		{
	//			return false
	//		}
	//	}
	//	typeArray_.push_back(typename(T));
	//
	//	return true;
	//}
	extern std::list<StandData*> datas_;

	void AddData_OverWrite(StandData* data);
		//{
		//	for (auto itr = datas_.begin(); itr != datas_.end(); itr++)
		//	{
		//		if (data->dataName_ == (*itr)->dataName_)
		//		{
		//			delete(*itr);
		//			itr = datas_.erase(itr);
		//			datas_.push_back(data);
		//			return;
		//		}
		//	}
		//	datas_.push_back(data);
		//}

		/// <summary>
		/// �V�[�����܂����ň����f�[�^�ǉ�
		/// </summary>
		/// <param name="data">�f�[�^�̃N���X</param>
		bool AddData_NonOverWrite(StandData* data);
	//{
	//	for (auto itr = datas_.begin(); itr != datas_.end(); itr++)
	//	{
	//		if (data->dataName_ == (*itr)->dataName_)
	//		{
	//			return false;
	//		}
	//	}
	//	datas_.push_back(data);
	//	return true;
	//}
	void DeleteData(std::string name);
	//{
	//	for (auto itr = datas_.begin(); itr != datas_.end(); itr++)
	//	{
	//		if ((*itr)->dataName_ == name)
	//		{
	//			delete(*itr);
	//			itr = datas_.erase(itr);
	//		}
	//	}
	//}
	template<class T>
	T* GetData(std::string name)
	{
		for (auto itr = datas_.begin(); itr != datas_.end(); itr++)
		{
			if ((*itr)->dataName_ == name)
			{
				return (T*)(*itr);
			}
		}
		return nullptr;
	}

	//struct Data
	//{
	//	std::variant<bool, std::string, short, int, float, std::vector<SNOWCONE_DATA>> value_;
	//	std::string dataName_;
	//};
	//extern std::vector<Data> interScenedatas_;
	//template<typename T>
	//void AddData(const std::string& dataName, T num)
	//{
	//	//�������O�̃f�[�^������
	//	for (Data& data : interScenedatas_)
	//	{
	//		//�������炻�̃f�[�^������������
	//		if (data.dataName_ == dataName)
	//		{
	//			data.value_ = num;
	//			return;
	//		}
	//	}
	//
	//	Data data;
	//	data.dataName_ = dataName;
	//	data.value_ = num;
	//	interScenedatas_.push_back(data);
	//}
	//template<typename T>
	//void DeleteData(const std::string& dataName)
	//{
	//	//�������O�̃f�[�^������
	//	for (auto itr=interScenedatas_.begin();itr!=interScenedatas_.end();)
	//	{
	//		//�������炻�̃f�[�^������������
	//		if (itr->dataName_ == dataName)
	//		{
	//			itr = interScenedatas_.erase(itr);
	//			break;
	//		}
	//		else
	//			itr++;
	//	}
	//}
	////void DataInput()
	//template<typename T>
	//T GetData(const std::string& dataName)
	//{
	//	//�������O�̃f�[�^������
	//	for (Data& data : interScenedatas_)
	//	{
	//		//�������炻�̃f�[�^������������
	//		if (data.dataName_ == dataName)
	//		{
	//			T a= std::get<T>(data.value_);
	//			return a;
	//			//return data.value_;
	//		}
	//	}
	//	T not_found{};
	//	return not_found;
	//	//return rtn;
	//}

};