#include "RootObject_Play_CollectionPart.h"
#include "../../CollectionPart_Ground.h"
#include"../../Player_CollectionPart.h"
RootObject_Play_CollectionPart::RootObject_Play_CollectionPart()
{
}

RootObject_Play_CollectionPart::~RootObject_Play_CollectionPart()
{
}

void RootObject_Play_CollectionPart::Initialize()
{
	Instantiate<Player_CollectionPart>(this);
	Instantiate<CollectionPart_Ground>(this);
}

void RootObject_Play_CollectionPart::Release()
{
}
