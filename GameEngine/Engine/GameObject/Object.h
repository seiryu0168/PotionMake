#pragma once
//#include"Engine\Collider\BoxCollider.h"
//#include"Engine\Collider/SphereCollider.h"
//#include"Engine\Collider/OBBCollider.h"
#include"../Coordinator.h"
#include"../Components/Transform.h"
#include<string>
#include<list>

//#ifdef _DEBUG
//#define _CRTDBG_MAP_ALLOC
//#include<memory>
//#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
//#include <crtdbg.h>
//#else
//#define DEBUG_NEW	
//#endif
//#ifdef _DEBUG
//#define new DEBUG_NEW
//#endif // _DEBUG

class PhysicsSystem;
class Object
{
	//friend class Collider;
	//friend class Component;

private:
	float time_;
protected:

	std::list<std::shared_ptr<Object>> childList_;
	std::unordered_map<std::string, std::vector<Entity>> entityList_;
	Object* pParent_;
	Object* pScene_;
	std::string	objectName_;			//名前
	int objectID_;						//オブジェクト固有の番号
	std::string objectTag_;				//オブジェクトに任意でつけられる識別用の名前
	bool killFlag_;						//キルするかどうか
	bool activeFlag_;					//オブジェクトがアクティブ(Update呼ばれる)かどうか
	bool isUpdate_;
	bool drawFlag_;						//描画するかどうか
	bool startFlag_;					//一回もアクティブになってない場合false
	Transform* transform_;
public:
	Object(Object* parent,const std::string& name);
	Object(Object* parent = nullptr);
	//Object();
	~Object();

	virtual void Initialize() = 0;
	virtual void Update() {};
	virtual void StaticUpdate() {};
	virtual void Draw() {};
	virtual void SecondDraw() {};
	virtual void ThirdDraw() {};
	virtual void BeforeDeath() {};
	virtual void Release() = 0;

	//isUpdate_がSetUpdate関数によってfalseに変更されたときに子オブジェクトのこの関数を呼びだす
	virtual void NotifiedUpdateF() {};
	//isUpdate_がSetUpdate関数によってtrueに変更されたときに子オブジェクトのこの関数を呼びだす
	virtual void NotifiedUpdateT() {};

	void NotifiedUpdateSub(bool updateFlag);

	void UpdateSub();
	void StaticUpdateSub();
	void DrawSub();
	void SecondDrawSub();
	void ThirdDrawSub();
	void ReleaseSub();

	virtual void OnCollision(Object* pTarget) {};

	void KillMe();
	bool IsDead() { return killFlag_; }
	void SetTag(const std::string& tagName) { objectTag_ = tagName; }
	void SetActive(bool status) { activeFlag_ = status; }
	bool IsActive() const { return activeFlag_; }
	bool IsStart() const { return startFlag_; }
	bool IsUpdate() const { return isUpdate_; }
	void SetUpdate(bool updateFlag);
	std::string GetObjectName() const { return objectName_; }
	std::string GetTag()const { return objectTag_; }
	Object* GetParent() const;
	Object* GetRootObject();
	Object* FindObject(const std::string& name);
	Object* FindObjectAtTag(const std::string& tagName);

	Object* FindChild(const std::string& name) const;
	Object* FindChildAtTag(const std::string& tagName) const;

	Object* GetScene();
	std::list<std::shared_ptr<Object>>* GetChildList() { return &childList_; }
	Transform* GetTransform() const;
	void KillAllChildren();
	void KillObjectSub(Object* pTarget);
	void PushBackChild(const std::shared_ptr<Object>& pTarget);

	template <typename T>
	size_t AddComponent(const T& component)
	{
		std::string typeName = typeid(T).name();
			Entity entity = Coordinator::CreateEntity();
			//今まで入れたことがないコンポーネントだったら
			//配列を作ってエンティティを格納
			if (entityList_.find(typeName) == entityList_.end())
			{
				std::vector<Entity> entities;
				entities.push_back(entity);
				entityList_.insert({ typeName,entities });
			}
			else
				entityList_.find(typeName)->second.push_back(entity);

			Coordinator::AddComponent<T>(entity,component);
			return entityList_.find(typeName)->second.size()-1;
	}

	template <typename T>
	void RemoveComponent(int componentNum=0)
	{
		std::string typeName = typeid(T).name();
		//コンポーネント番号が配列内にあるなら
		if (componentNum < entityList_.find(typeName)->second.size())
		{
			Coordinator::RemoveComponent<T>(entityList_.find(typeName)->second[componentNum]);
			entityList_.find(typeName)->second.erase(entityList_.find(typeName)->second.begin() + componentNum);
		}
		
	}

	template <typename T>
	T& GetComponent(int componentNum=0)
	{
		std::string typeName = typeid(T).name();
		assert(entityList_.find(typeName)->second.size());	//失敗したら強制終了
		return Coordinator::GetComponent<T>(entityList_.find(typeName)->second[componentNum]);
	}
	template <typename T>
	std::vector<Entity>& GetComponentList()
	{
		std::string typeName = typeid(T).name();
		assert(entityList_.find(typeName)!=entityList_.end());	//失敗したら強制終了
		return entityList_.find(typeName)->second;
	}

	template<class T>
	T* Instantiate(Object* parent)
	{
		std::shared_ptr<T> p = std::make_shared<T>(parent);
		if (parent != nullptr)
		{
			parent->PushBackChild(p);
			parent->transform_->PushBackChild(p->transform_);
		}
		p->Initialize();
		return p.get();
	}
};
