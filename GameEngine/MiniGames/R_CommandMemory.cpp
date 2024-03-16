#include "R_CommandMemory.h"
#include "../Engine/Components/Image.h"

R_CommandMemory::R_CommandMemory(Object* parent)
	: Result_Multi(parent, "R_CommandMemory")
{
}

R_CommandMemory::~R_CommandMemory()
{
}

void R_CommandMemory::MoreInfo()
{
	Image image;
	image.Load("Assets\\Image\\CM_Res.png");
	image.SetSize({ 4, 3, 1 });
	AddComponent<Image>(image);
}
