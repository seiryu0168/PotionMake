#include "Play_ManagementPart_Manaita.h"
#include"../../Engine/Systems/ModelSystem.h"
Play_ManagementPart_Manaita::Play_ManagementPart_Manaita(Object* parent)
	:GameObject(parent,"Play_ManagementPart_Manaita")
{
}

void Play_ManagementPart_Manaita::Initialize()
{
	Test_Model_ECSver manaita(this);
	manaita.Load("Assets/Model/Manaita.fbx");
	AddComponent<Test_Model_ECSver>(manaita);
}

void Play_ManagementPart_Manaita::Release()
{
}
