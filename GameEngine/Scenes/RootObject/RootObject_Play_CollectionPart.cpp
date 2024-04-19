#include "RootObject_Play_CollectionPart.h"
#include "../../CollectionPart_Ground.h"
#include"../../Player_CollectionPart.h"
#include"../../Play_CollectionPart_StageManager.h"
#include"../../Play_UIManager.h"
RootObject_Play_CollectionPart::RootObject_Play_CollectionPart()
{
}

RootObject_Play_CollectionPart::~RootObject_Play_CollectionPart()
{
}

void RootObject_Play_CollectionPart::Initialize()
{
	Instantiate<Player_CollectionPart>(this);
	Instantiate<Play_CollectionPart_StageManager>(this);
	Instantiate<CollectionPart_Ground>(this);
	Instantiate<Play_UIManager>(this);
}

void RootObject_Play_CollectionPart::Release()
{
}
