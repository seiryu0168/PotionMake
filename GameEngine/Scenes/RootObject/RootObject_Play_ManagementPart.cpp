#include "RootObject_Play_ManagementPart.h"
#include"../../ManagementPart_Floor.h"
//#include"../../Player.h"
#include"../../Player_ManagementPart.h"
#include"../../ManagementPart/PotionManagement/Play_ManagementPart_Shelf.h"
#include"../../ManagementPart/Craft/Play_ManagementPart_CraftTable.h"
#include"../../ManagementPart/Outing/Play_ManagementPart_Door.h"
#include"../../Play_UIManager.h"
RootObject_Play_ManagementPart::RootObject_Play_ManagementPart()
{
}

RootObject_Play_ManagementPart::~RootObject_Play_ManagementPart()
{
}

void RootObject_Play_ManagementPart::Initialize()
{
	Instantiate<Player_ManagementPart>(this);
	Instantiate<ManagementPart_Floor>(this);
	Instantiate<Play_ManagementPart_Shelf>(this);
	Instantiate<Play_ManagementPart_CraftTable>(this);
	Instantiate<Play_ManagementPart_Door>(this);
	Instantiate<Play_UIManager>(this);
}

void RootObject_Play_ManagementPart::Release()
{
}
