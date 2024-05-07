#include "PotionStatusGauge.h"
#include "../../Engine/Systems/ImageSystem.h"
PotionStatusGauge::PotionStatusGauge(Object* parent)
	:GameObject(parent,"PotionStatusGauge")
{
}

PotionStatusGauge::~PotionStatusGauge()
{
}

void PotionStatusGauge::Initialize()
{
	Image gaugeImage(this);
	gaugeImage.Load("Assets/Image/GaugeImage01.png");
	gaugeImage.SetSize({ 0.3f,0.3f,0 });
	AddComponent<Image>(gaugeImage);
}

void PotionStatusGauge::Start()
{
}

void PotionStatusGauge::Update()
{
}

void PotionStatusGauge::Release()
{
}
