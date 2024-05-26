#include "Play_ManagementPart_CraftPotModel.h"
#include"../../Engine/Systems/ModelSystem.h"
#include"../../Engine/Systems/ParticleSystem.h"
Play_ManagementPart_CraftPotModel::Play_ManagementPart_CraftPotModel(Object* parent)
	:GameObject(parent,"Play_ManagementPart_CraftPotModel")
{
}

void Play_ManagementPart_CraftPotModel::Initialize()
{
	Test_Model_ECSver craftPot(this);
	craftPot.Load("Assets/Model/CraftPot.fbx");
	AddComponent<Test_Model_ECSver>(craftPot);

	Particle steam(this);
	EmitterData data;
	data.acceleration = 0;
	data.delay = 30;
	data.position = { 0,0,0 };
	data.positionErr = { 0.5f,1,0.5f };
	data.dir = { 1,0,0 };
	data.dirErr = { 0,0,0 };
	data.gravity = -0.05f;
	data.firstSpeed = 0;
	data.lifeTime = 100;
	data.number = 2;
	data.scale = { 1.0f,1.01f };
	data.size = { 1,1 };
	data.sizeErr = { 0,0 };
	data.deltaColor = { 0,0,0,-0.01f };
	data.textureFileName = "Assets/Image/SmokeImage00.png";
	data.blendMode = BLEND_MODE::BLEND_ADD;
	steam.SetData(data);
	AddComponent<Particle>(steam);
}

void Play_ManagementPart_CraftPotModel::Release()
{
}
