#pragma once
#include"Engine/GameObject/GameObject.h"
#include"Engine/Coordinator.h"
#include"Engine/Systems/ParticleSystem.h"
#include"Engine/Systems/LineParticleSystem.h"
#include"Engine/Components/Test_Model_ECSver.h"
#include"Engine/Components/Collider.h"
#include"Engine/Components/Text.h"
#include"Engine/Components/Image.h"
#include"Engine/ResourceManager/json.hpp"
	using json = nlohmann::json;

class ObjectSetter
{
private:
	json jsonFile_;
	Object* sceneObject_;
public:
	ObjectSetter();
	ObjectSetter(Object* sceneObject);
	~ObjectSetter();
	/// <summary>
	/// jsonÉtÉ@ÉCÉãì«Ç›çûÇﬁ
	/// </summary>
	/// <param name="fileName"></param>
	/// <returns>ê¨å˜ÇµÇΩèÍçátrue,é∏îsÇµÇΩÇÁfalse</returns>
	bool DataLoad(const std::string& fileName);
	void AddCollider(GameObject* object, HitBox& box);
	void AddCollider(GameObject* object, HitSphere& sphere);
	void AddParticle(GameObject* object,EmitterData& data);
	void AddParticle(GameObject* object, std::string name, XMFLOAT3 pos = { 0,0,0 }, XMFLOAT3 posErr = { 0,0,0 }, XMFLOAT3 dir = { 0,0,0 }, XMFLOAT3 dirErr = { 0,0,0 }, float firstspd = 0, float spdErr = 0, float accele = 0, float gravity = 0, XMFLOAT4 color = { 0,0,0,1 }, XMFLOAT4 deltaCol = { 0,0,0,1 }, XMFLOAT2 size = { 1,1 }, XMFLOAT2 sizeErr = { 0,0 }, XMFLOAT2 scale = { 0,0 }, DWORD lifeTime = 10, int delay = 0, int number = 10, BLEND_MODE mode = BLEND_MODE::BLEND_ADD);
	//void AddLineParticle(GameObject* object, LineData& data);
	void AddLineParticle(GameObject* object, std::string name, float width = 0.5f, float endWidth = 0, int length = 10);
	void AddModel(GameObject* object,std::string fileName);
	void AddImage(GameObject* object, std::string fileName, XMFLOAT3 pos = { 0,0,0 }, XMFLOAT3 size = { 1,1,1 }, XMFLOAT3 rotate = {0,0,0}, float alpha=1.0f);
	void AddText(GameObject* object,FontData& data);
	void AddText(GameObject* object,std::string txt,std::string font,float fontSize,std::string locale, DWRITE_FONT_WEIGHT fontWeight, DWRITE_FONT_STYLE style, DWRITE_FONT_STRETCH stretch);
	void SetObject();
	void DeleteObject();





};

