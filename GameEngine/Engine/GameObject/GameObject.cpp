#include "GameObject.h"	
#include"../SAFE_DELETE_RELEASE.h"
GameObject::GameObject() : GameObject(nullptr,"")
{

}
GameObject::GameObject(Object* parent, const std::string& name)
	:Object(parent,name),
	drawFlag_(true)
{
	//Entity transformEntity = Coordinator::CreateEntity();
	//Transform transform;// = new Transform;
	//if (parent != nullptr)
	//	transform.pParent_ = &((GameObject*)parent)->GetComponent<Transform>();
	//
	//AddComponent<Transform>(transform);
	//transform_ = &GetComponent<Transform>();
}

//void GameObject::UpdateSub()
//{
//	/////////アップデート/////////
//	if (startFlag_ == false&&activeFlag_)
//	{
//		GameObject* p = GetRootJob();
//		this->Initialize();
//		this->startFlag_ = true;
//	}
//	else if(startFlag_&&
//			activeFlag_&&
//			isUpdate_)
//	Update();
//
//
//
//	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)
//	{
//		(*itr)->UpdateSub();
//	}
//	////////当たり判定///////////
//	for (auto itr = childList_.begin(); itr != childList_.end();)
//	{
//		if (activeFlag_)
//		{
//
//			if ((*itr)->killFlag_ == true)
//			{
//				(*itr)->BeforeDeath();
//				(*itr)->ReleaseSub();
//				delete* itr;
//				itr = childList_.erase(itr);
//			}
//			else
//			{
//				(*itr)->Collision(GetParent());
//				itr++;
//			}
//		}
//	}
//}

//void GameObject::FixedUpdateSub()
//{
//	FixedUpdate();
//	for(auto itr = childList_.begin();itr!=childList_.end();itr++)
//	{
//		(*itr)->FixedUpdateSub();
//	}
//
//	for (auto itr = childList_.begin(); itr != childList_.end();)
//	{
//		if ((*itr)->killFlag_ == true)
//		{
//			(*itr)->ReleaseSub();
//			delete* itr;
//			itr = childList_.erase(itr);
//		}
//		else
//		{
//			(*itr)->Collision(GetParent());
//			itr++;
//		}
//	}
//}

//void GameObject::DrawSub()
//{
//	if (drawFlag_ && startFlag_)
//	{
//		Draw();
//	}
//	for (auto itr=childList_.begin();itr!=childList_.end();itr++)
//	{
//		//if(typeid(itr)==typeid(GameObject*))
//		((GameObject*)(*itr))->DrawSub();
//	}
//}
//
//void GameObject::SecondDrawSub()
//{
//	if (drawFlag_ && startFlag_)
//	{
//		SecondDraw();
//	}
//
//	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)
//	{
//		if (typeid(itr) == typeid(GameObject*))
//			((GameObject*)(*itr))->SecondDrawSub();
//	}
//}
//
//void GameObject::ThirdDrawSub()
//{
//	if (drawFlag_&&startFlag_)
//	{
//		ThirdDraw();
//	}
//
//	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)
//	{
//		if (typeid(itr) == typeid(GameObject*))
//			((GameObject*)(*itr))->ThirdDrawSub();
//	}
//}

//void GameObject::ReleaseSub()
//{
//	for (auto i = colliderList_.begin(); i != colliderList_.end(); i++)
//	{
//		SAFE_DELETE(*i);
//	}
//	for (auto i = childList_.begin(); i != childList_.end(); i++)
//	{
//		(*i)->ReleaseSub();
//		SAFE_DELETE(*i);
//	}
//
//	Release();
//}

//void GameObject::AddComponent(Component* comp)
//{
//	componentList_.push_back(comp);
//}

//void GameObject::DeleteComponent(Component* comp)
//{
//	comp->Release();
//}

//Component* GameObject::GetComponent(int compNum)
//{
//	return componentList_[compNum];
//}

//////////////////////////当たり判定関係////////////////////

//衝突判定
void GameObject::Collision(GameObject* pTarget)
{
	//pTargetが自分かnullptrだったらなんもしない
	if (pTarget == nullptr||pTarget==this)
	{
		return;
	}
	////複数コライダー持ってるかもしれないから二重ループ
	//for (auto i = this->colliderList_.begin(); i != this->colliderList_.end(); i++)
	//{

	//	for (auto j = pTarget->colliderList_.begin(); j != pTarget->colliderList_.end();j++)
	//	{
	//		if ((*i)->IsHit(*j))
	//		{
	//			this->OnCollision(pTarget);
	//			if (this->colliderList_.empty())
	//				break;
	//		}
	//	}

	//	if (this->colliderList_.empty())
	//		break;
	//}

	if (pTarget->childList_.empty())
	{
		return;
	}

	for (auto itr = pTarget->childList_.begin(); itr != pTarget->childList_.end(); itr++)
	{
		if (typeid(itr) == typeid(GameObject*))
		{

		Collision((GameObject*)itr->get());
		}
	}
}

//コライダーを追加
//collider->pColObjectにセットする奴
//void GameObject::AddCollider(Collider* collider)
//{
//	//collider->SetGemaObject(this);
//	//colliderList_.push_back(collider);
//}

//void GameObject::DelCollider(const GameObject& obj)
//{
//	//for (auto itr = colliderList_.begin(); itr != colliderList_.end();)
//	//{
//	//	if ((*itr)->GetpColObject() == &obj)
//	//	{
//	//		itr = colliderList_.erase(itr);
//	//	}
//	//	if (itr == colliderList_.end())
//	//	{
//	//		break;
//	//	}
//	//	itr ++;
//	//}
//}

//void GameObject::KillAllChildren()
//{
//	//リストに何も無ければ終わり
//	if (childList_.empty())
//	{
//		return;
//	}
//	//リストにある子どもを全員消す
//	for (auto itr = this->childList_.begin(); itr != this->childList_.end();)
//	{
//		KillObjectSub(*itr);
//		delete* itr;
//		itr = this->childList_.erase(itr);
//	}
//}

//void GameObject::KillObjectSub(GameObject* pTarget)
//{
//	if (!pTarget->childList_.empty())
//	{
//		for (auto itr = pTarget->childList_.begin(); itr != pTarget->childList_.end();)
//		{
//			KillObjectSub(*itr);
//			SAFE_DELETE(*itr);
//			itr = pTarget->childList_.erase(itr);
//		}
//		pTarget->childList_.clear();
//	}
//	pTarget->Release();
//}
//void GameObject::PushBackChild(GameObject* pTarget)
//{
//	assert(pTarget != nullptr);
//	pTarget->pParent_ = this;
//	//pTarget->objectID_ = objectcount++;
//	childList_.push_back(pTarget);
//}

//親を取得
//GameObject* GameObject::GetParent()
//{
//	return pParent_;
//}

//GameObject* GameObject::GetRootJob()
//{
//	if (this->GetParent() == nullptr)
//	{
//		return this;
//	}
//	else return GetParent()->GetRootJob();
//}

//GameObject* GameObject::FindObject(std::string name)
//{
//	GameObject* obj= GetRootJob()->FindChild(name);
//	return obj;
//}

//GameObject* GameObject::FindObjectAtTag(std::string tagName)
//{
//	GameObject* obj = GetRootJob()->FindChildAtTag(tagName);
//	return obj;
//}

//GameObject* GameObject::FindChild(std::string name)
//{
//	//子がいなかったらnullptr返す
//	if (this->childList_.empty())
//	{
//		return nullptr;
//	}
//
//	//子の中から探す
//	for (auto itr = this->childList_.begin(); itr != this->childList_.end(); itr++)
//	{
//		//名前が一致したら返す
//		if (name == (*itr)->objectName_)
//		{
//			return *itr;
//		}
//
//		//孫のオブジェクトも探す
//		GameObject* obj = (*itr)->FindChild(name);
//		if (obj != nullptr)
//		{
//			return obj;
//		}
//	}	
//	//見つからなかった時
//	return nullptr;
//}

//GameObject* GameObject::FindChildAtTag(std::string tagName)
//{
//	if (this->childList_.empty())
//	{
//		return nullptr;
//	}
//	//同じタグがあったら返す
//	for (auto i : this->childList_)
//	{
//		if (i->GetTag() == tagName)
//		{
//			return i;
//		}
//		//孫も調べる
//		GameObject* obj = i->FindChildAtTag(tagName);
//		if (obj != nullptr)
//			return obj;
//	}
//
//	//見つからなかった時
//	return nullptr;
//}

//GameObject* GameObject::GetScene()
//{
//	auto itr = GetRootJob()->GetChildList()->begin();
//	return (*(*itr)->GetChildList()->begin());
//}

//Transform* GameObject::GetTransform() const
//{
//	return this->transform_;
//}

XMMATRIX GameObject::LookAtMatrix(const XMFLOAT3& target, const XMVECTOR& frontVec, const XMVECTOR& upVector)
{
	//frontVec = XMVector3Normalize(frontVec);
	XMVECTOR front = XMVector3Normalize(frontVec);

	XMVECTOR Z = XMLoadFloat3(&target) - this->transform_->position_; //自分から目標へのベクトル　=　Z軸
	Z = XMVector3Normalize(Z);

	float angleX=0;
	XMVECTOR AAA = XMVector3Cross(Z, front);					//Z軸と向いてる方向のベクトルの外積計算(この外積が回転の軸になる)
	AAA = XMVector3Normalize(AAA);								//正規化

	angleX= XMVectorGetX(XMVector3Dot(front,Z));				//Z軸と向いてる方向のベクトルの外積計算
	angleX = -acosf(angleX);									//ラジアン角に変換

	XMVECTOR quo = XMQuaternionRotationNormal(AAA, angleX);    //AAAを軸に回転四元数を作成
															   //軸が正規化されてるベクトルの場合XMQuaternionRotationNormalの方が良い(早いらしい)
															   //XMQuaternionRotationAxisだとエラー吐いた

	XMMATRIX rotateMatrix = XMMatrixRotationQuaternion(quo);

	return rotateMatrix;
}

//ワールド行列取得
//親の影響込みの最終的な行列
XMMATRIX GameObject::GetWorldMatrix()
{
	return transform_->GetWorldMatrix();
}