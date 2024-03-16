#pragma once
#include<unordered_map>
#include<memory>
#include<bitset>
#include"ECS.h"
#include"System.h"

class SystemManager
{
private:
	//システム型の文字列ポインタからシグネチャへのマップ
	std::unordered_map<const char*, Signature> signatures_{};
	//システム型の文字列ポインタからシステムポインタへのマップ
	std::unordered_map<const char*, std::shared_ptr<System>> systems_{};

public:
	void EntityDestroyed(Entity entity);
	void EntitySignatureChanged(Entity entity, const Signature entitySignature);
	void AllSystemUpdate();
	void Clear();

	/// <summary>
	/// システムクラスの登録
	/// システムクラスはエンジンの初期化時にすべて登録され、
	/// ゲームが終わる時にすべて消去される
	/// </summary>
	/// <typeparam name="T">システムのクラス</typeparam>
	/// <returns>システムクラスのスマートポインタ</returns>
	template <typename T>
	std::shared_ptr<T> RegisterSistem()
	{
		const char* typeName = typeid(T).name();
		//システムが今まで追加したのと同じものがある場合警告
		assert(systems_.find(typeName) == systems_.end() && "Registering system more than once");
		//システムのポインタを作成し、外部で使うために返す
		auto system = std::make_shared<T>();
		systems_.insert({ typeName,system });
		return system;
	}
	/// <summary>
	/// シグネチャをセット
	/// </summary>
	/// <typeparam name="T">紐づけるシステムクラス</typeparam>
	/// <param name="signature">シグネチャ</param>
	template <typename T>
	void SetSignature(const Signature& signature)
	{
		const char* typeName = typeid(T).name();
		assert(signatures_.find(typeName) == signatures_.end() && "System used before registered");
		//システムにシグネチャをセット
		signatures_.insert({ typeName,signature });
	}
	/// <summary>
	/// システムクラスの取得
	/// </summary>
	/// <typeparam name="T">欲しいシステムクラス</typeparam>
	/// <returns>システムクラス</returns>
	template <typename T>
	System* GetSystem() const
	{
		const char* typeName = typeid(T).name();
		if (signatures_.find(typeName) == signatures_.end())
			return nullptr;
		return systems_.find(typeName)->second.get();
	}
};

