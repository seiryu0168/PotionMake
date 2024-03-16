#include "R_ChickenRace.h"
#include "../Engine/Components/Text.h"
#include "../InterSceneData.h"
#include <format>
#include "../Engine/Components/Image.h"

R_ChickenRace::R_ChickenRace(Object* parent)
	:Result_Multi(parent, "R_ChickenRace")
{
}

R_ChickenRace::~R_ChickenRace()
{
}

void R_ChickenRace::MoreInfo()
{
	{
		Image image;
		image.Load("Assets\\Image\\Ennichi_Image.png");
		AddComponent<Image>(image);
	}

	for (int i = 0; i < 2; i++)
	{
		float time = InterSceneData::GetData<float>(std::format("time_{:d}", i));
		int target = InterSceneData::GetData<int>("time_target");
		float error = time - target;
		Text text(std::format("ƒvƒŒƒCƒ„[{:d}\n{:g}•b\n(Œë· : {:g}•b)", i + 1, time, error), "‚è‚¢‚Ä‚ª‚«•M", { 0,0,700,50 });
		text.SetRatio(0.15f + (i * 0.45f), 0.35f);
		AddComponent<Text>(text);
	}
}
