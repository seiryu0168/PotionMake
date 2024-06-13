#include "P_CP_ResourceItem.h"
#include "../Engine/Systems/ModelSystem.h"
#include "../Engine/Systems/ColliderSystem.h"

P_CP_ResourceItem::P_CP_ResourceItem(Object* parent)
	:ItemBase(parent,"P_CP_ResourceItem"),
	isLoaded_(false)
{
}

P_CP_ResourceItem::~P_CP_ResourceItem()
{
}

void P_CP_ResourceItem::Initialize()
{
	//ìñÇΩÇËîªíËÇÃê›íË
	HitBox box({ 1,1,1 });
	Collider coll({ 0,0,0 });
	coll.SetAttachObject(this);
	coll.SetCollider(box);
	AddComponent<Collider>(coll);
	SetTag("ResourceItem");

}

void P_CP_ResourceItem::Start()
{
}

void P_CP_ResourceItem::Update()
{
}

void P_CP_ResourceItem::SetModel(const std::string& modelName)
{
	//ä˘Ç…ÉçÅ[ÉhÇ≥ÇÍÇƒÇΩÇÁreturn
	if (isLoaded_) return;
	
	//ëfçﬁÇÃÉÇÉfÉã
	Test_Model_ECSver model(this);
	model.Load("Assets/Model/" + modelName);
	model.SetDrawDistance(300);
	AddComponent<Test_Model_ECSver>(model);
	isLoaded_ = true;
}

void P_CP_ResourceItem::Release()
{
}
