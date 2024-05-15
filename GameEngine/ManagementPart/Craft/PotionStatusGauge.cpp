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
	////ポーションの各ステータスの画像
	//Image gaugeImage(this);
	//gaugeImage.Load("Assets/Image/GaugeImage01.png");
	//gaugeImage.SetSize({ 0.3f,0.3f,0 });
	//AddComponent<Image>(gaugeImage);
}

void PotionStatusGauge::Start()
{
}

void PotionStatusGauge::Update()
{
}

void PotionStatusGauge::SetGauge(const std::string& iconName, const XMFLOAT3 pos,const XMFLOAT3& color)
{
	Image gaugeImage(this);
	gaugeImage.Load("Assets/Image/GaugeImage01.png");
	gaugeImage.SetPosition(pos);
	gaugeImage.SetSize({ 0.3f,0,0 });
	gaugeImage.SetColor(color);
	AddComponent<Image>(gaugeImage);
	Image icon(this);
	icon.Load(iconName);
	icon.SetPosition({ pos.x,pos.y - 0.08f,0 });
	icon.SetSize({ 0.3f,0.3f,0 });
	AddComponent<Image>(icon);

}

void PotionStatusGauge::Release()
{
}
