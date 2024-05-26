#include "Play_ManagementPart_Mortar.h"
#include"../../Engine/Systems/ModelSystem.h"
Play_ManagementPart_Mortar::Play_ManagementPart_Mortar(Object* parent)
	:GameObject(parent,"Play_ManagementPart_Mortar")
{
}

void Play_ManagementPart_Mortar::Initialize()
{
	Test_Model_ECSver mortar(this);
	mortar.Load("Assets/Model/Mortar.fbx");
	AddComponent<Test_Model_ECSver>(mortar);
}

void Play_ManagementPart_Mortar::Update()
{
}

void Play_ManagementPart_Mortar::Release()
{
}
