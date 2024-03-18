#include "RootObject_Play_ManagementPart.h"
#include"../../ManagementPart_Floor.h"
#include"../../Player.h"
RootObject_Play_ManagementPart::RootObject_Play_ManagementPart()
{
}

RootObject_Play_ManagementPart::~RootObject_Play_ManagementPart()
{
}

void RootObject_Play_ManagementPart::Initialize()
{
	Instantiate<Player>(this);
	Instantiate<ManagementPart_Floor>(this);
}

void RootObject_Play_ManagementPart::Release()
{
}
