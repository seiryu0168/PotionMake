#include "ObjectSetter.h"
//#include"RootObject.h"
#include"TestObject.h"
#include"TestObjectChild.h"
ObjectSetter::ObjectSetter() : ObjectSetter(nullptr)
{

}

ObjectSetter::ObjectSetter(Object* sceneObject)
{
	sceneObject_ = sceneObject;
}

ObjectSetter::~ObjectSetter()
{
}

bool ObjectSetter::DataLoad(const std::string& fileName)
{
	
	return false;
}

void ObjectSetter::AddCollider(GameObject* object,HitBox& box)
{
	Collider collider;
	collider.SetAttachObject(object);
	collider.SetCollider(box);
		
	object->AddComponent<Collider>(collider);
}

void ObjectSetter::AddCollider(GameObject* object, HitSphere& sphere)
{
	Collider collider;
	collider.SetAttachObject(object);
	collider.SetCollider(sphere);

	object->AddComponent<Collider>(collider);
}

void ObjectSetter::AddParticle(GameObject* object, EmitterData& data)
{
	Particle particle(object);
	particle.SetData(data);
	object->AddComponent<Particle>(particle);
}

void ObjectSetter::AddParticle(GameObject* object, std::string name, XMFLOAT3 pos, XMFLOAT3 posErr, XMFLOAT3 dir, XMFLOAT3 dirErr, float firstspd, float spdErr, float accele, float gravity, XMFLOAT4 color, XMFLOAT4 deltaCol, XMFLOAT2 size, XMFLOAT2 sizeErr, XMFLOAT2 scale, DWORD lifeTime, int delay, int number, BLEND_MODE mode)
{
	EmitterData data;
	data.textureFileName = name;
	data.position = pos; data.positionErr = posErr;
	data.dir = dir; data.dirErr = dirErr;
	data.firstSpeed = firstspd;	data.speedErr = spdErr;
	data.acceleration = accele;
	data.gravity = gravity;
	data.color = color;	data.deltaColor = deltaCol;
	data.size = size; data.sizeErr = sizeErr;
	data.scale = scale;
	data.lifeTime = lifeTime;
	data.delay = delay;
	data.number = number;
	data.blendMode = mode;
	Particle particle(object);
	particle.SetData(data);
	object->AddComponent<Particle>(particle);
}

void ObjectSetter::AddLineParticle(GameObject* object, std::string name, float width, float endWidth, int length)
{
	LineData data;
	data.textureName = name;
	data.width = width;
	data.endWidth = endWidth;
	data.length = length;
}

void ObjectSetter::AddModel(GameObject* object, std::string fileName)
{
	Test_Model_ECSver model;
	model.Load(fileName);
	object->AddComponent<Test_Model_ECSver>(model);
}

void ObjectSetter::AddImage(GameObject* object, std::string fileName, XMFLOAT3 pos, XMFLOAT3 size, XMFLOAT3 rotate, float alpha)
{
	 Image image;
	 image.Load(fileName);
	 image.SetPosition(pos);
	 image.SetSize(size);
	 image.SetRotation(rotate);
	 image.SetAlpha(alpha);
	 object->AddComponent<Image>(image);

}

void ObjectSetter::AddText(GameObject* object, std::string txt, std::string font, float fontSize, std::string locale, DWRITE_FONT_WEIGHT fontWeight, DWRITE_FONT_STYLE style, DWRITE_FONT_STRETCH stretch)
{
	Text text;
	text.SetText(txt);
	//text.SetTextSize()
}

void ObjectSetter::SetObject()
{
	sceneObject_->Instantiate<TestObject>(sceneObject_);
	sceneObject_->Instantiate<TestObjectChild>(sceneObject_);
}

void ObjectSetter::DeleteObject()
{
	//SAFE_DELETE(sceneObject_);
}
