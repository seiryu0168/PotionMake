#include "Object.h"
#include"../Systems/PhysicsSystem.h"
#include"../SAFE_DELETE_RELEASE.h"
#include "../../Division.h"

int objectcount = 0;
Object::Object(Object* parent, const std::string& name)
	:pParent_(parent),
	objectName_(name),
	objectTag_(""),
	killFlag_(0),
	activeFlag_(true),
	isUpdate_(true),
	drawFlag_(true),
	startFlag_(false),
	objectID_(-1),
	time_(0),
	pScene_(nullptr),
	childList_()
{
	Transform transform;// = new Transform;
	if (parent != nullptr)
		transform.pParent_ = &parent->GetComponent<Transform>();

	AddComponent<Transform>(transform);
	transform_ = &GetComponent<Transform>();
	//Coordinator::RegisterComponent<Gravity>();
	//Coordinator::RegisterComponent<TransformData>();
	//Coordinator::RegisterComponent<RigidBody>();

	/*physicsSystem_ = Coordinator::RegisterSystem<PhysicsSystem>();
	

	Signature signature;
	signature.set(Coordinator::GetComponentType<Gravity>());
	signature.set(Coordinator::GetComponentType<RigidBody>());
	signature.set(Coordinator::GetComponentType<TransformData>());

	Coordinator::SetSystemSignature<PhysicsSystem>(signature);*/
}

Object::Object(Object* parent) : Object(parent, "")
{
	Transform transform;// = new Transform;
	if (parent != nullptr)
		transform.pParent_ = &parent->GetComponent<Transform>();

	AddComponent<Transform>(transform);
	transform_ = &GetComponent<Transform>();
}

Object::~Object()
{
}

void Object::NotifiedUpdateSub(bool updateFlag)
{
	if (updateFlag)
	{
		NotifiedUpdateT();
	}
	else
	{
		NotifiedUpdateF();
	}

	for (auto&& itr : childList_)
		itr->NotifiedUpdateSub(updateFlag);
}

void Object::UpdateSub()
{
	/////////アップデート/////////
	if (startFlag_ == false && activeFlag_)
	{
		//Object* p = GetRootObject();
		//Division::setLoad(true);
		//this->Initialize();
		this->startFlag_ = true;
		//Division::setLoad(false);
	}
	if (activeFlag_ && isUpdate_ && killFlag_ == false)
	{
		Update();
		transform_->Calclation();
	}

	if (isUpdate_)
	{

		for (auto&& itr : childList_)
		{
			itr->UpdateSub();
		}
	}

	//for (auto itr = childList_.begin(); itr != childList_.end();)
	//{
	//	if ((*itr)->killFlag_ == true)
	//	{
	//		(*itr)->ReleaseSub();
	//		 //SAFE_RELEASE(*itr->get());
	//		itr = childList_.erase(itr);
	//	}
	//	else
	//		itr++;
	//}
}

//void Object::ComponentUpdate()
//{
//	for (Component* comp : componentList_)
//	{
//		comp->Update();
//	}
//}

void Object::StaticUpdateSub()
{
	if (startFlag_ == false && activeFlag_)
	{
		//Object* p = GetRootObject();
		//this->Initialize();
		this->startFlag_ = true;
	}
	else if (startFlag_ && activeFlag_)
		StaticUpdate();

		for (auto&& itr : childList_)
		{
			itr->StaticUpdateSub();
		}
}
void Object::DrawSub()
{
	if (drawFlag_ && startFlag_)
	{
		Draw();
	}
	for (auto&& itr : childList_)
	{
		itr->DrawSub();
	}
}

void Object::SecondDrawSub()
{
	if (drawFlag_ && startFlag_)
	{
		SecondDraw();
	}

	for (auto&& itr : childList_)
	{
		itr->SecondDrawSub();
	}
}

void Object::ThirdDrawSub()
{
	if (drawFlag_&&startFlag_)
	{
		ThirdDraw();
	}

	for (auto&& itr : childList_)
	{
		itr->ThirdDrawSub();
	}
}
void Object::ReleaseSub()
{
	for (auto itr = childList_.begin();itr != childList_.end();)
	{
			(*itr)->ReleaseSub();
		if ((*itr)->IsDead())
		{
			(*itr)->Release();
			itr = childList_.erase(itr);
		}
		else
			itr++;


	
	}

	//Release();
}

void Object::KillMe()
{
	this->killFlag_ = true;
	for (auto&& itr = childList_.begin(); itr != childList_.end(); itr++)
	{
		(*itr)->KillMe();
	}
}

void Object::SetUpdate(bool updateFlag)
{
	if (isUpdate_ != updateFlag)
	{
		isUpdate_ = updateFlag;
		
		NotifiedUpdateSub(isUpdate_);
	}
}

Object* Object::GetParent() const
{
	return pParent_;
}

Object* Object::GetRootObject()
{
	if (this->GetParent() == nullptr)
		return this;
	else
		return GetParent()->GetRootObject();
}

Object* Object::FindObject(const std::string& name)
{
	return GetRootObject()->FindChild(name);
}

Object* Object::FindObjectAtTag(const std::string& tagName)
{
	return GetRootObject()->FindChildAtTag(tagName);
}

Object* Object::FindChild(const std::string& name) const
{
	if (childList_.empty())
		return nullptr;

	for (auto&& obj : childList_)
	{
		if (obj->objectName_ == name)
			return obj.get();

		Object* objChild = obj->FindChild(name);
		if (objChild != nullptr)
			return objChild;

	}
	return nullptr;
}

Object* Object::FindChildAtTag(const std::string& tagName) const
{
	if (childList_.empty())
		return nullptr;

	for (auto&& obj : childList_)
	{
		if (obj->objectTag_== tagName)
			return obj.get();

		Object* objChild = obj->FindChildAtTag(tagName);
		if (objChild != nullptr)
			return objChild;

	}
	return nullptr;
}

Object* Object::GetScene()
{
	auto itr = GetRootObject()->GetChildList()->begin();
	return (*itr)->GetChildList()->begin()->get();
}

Transform* Object::GetTransform() const
{
	return this->transform_;
}

void Object::KillAllChildren()
{
	//リストに何も無ければ終わり
	if (childList_.empty())
	{
		return;
	}
	//リストにある子どもを全員消す
	for (auto&& itr : childList_)
	{
		KillObjectSub(itr.get());
		//delete* itr;
		//itr = this->childList_.erase(itr);
	}
	childList_.clear();
}

void Object::KillObjectSub(Object* pTarget)
{
	if (!pTarget->childList_.empty())
	{
		for (auto&& itr : pTarget->childList_)
		{
			KillObjectSub(itr.get());
			//SAFE_DELETE(*itr);
			//itr = pTarget->childList_.erase(itr);
		}
		pTarget->childList_.clear();
	}
	pTarget->Release();
}
void Object::PushBackChild(const std::shared_ptr<Object>& pTarget)
{
	assert(pTarget != nullptr);
	pTarget->pParent_ = this;
	pTarget->objectID_ = objectcount++;
	childList_.push_back(pTarget);
}