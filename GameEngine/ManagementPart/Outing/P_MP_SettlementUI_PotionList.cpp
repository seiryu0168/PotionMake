#include "P_MP_SettlementUI_PotionList.h"
#include "P_MP_SettiementUI_Potion.h"
#include "../../Engine/Systems/ImageSystem.h"
#include "../../Engine/Systems/TextSystem.h"
#include "../../Engine/DirectX_11/Input.h"

P_MP_SettlementUI_PotionList::P_MP_SettlementUI_PotionList(Object* parent)
	:GameObject(parent,"P_MP_SettlementUI_PotionList"),
	uiPos_({ -0.6f,0.0f,0 }),
	move_(0),
	scrollSpeed_(0.1f)
{
}

P_MP_SettlementUI_PotionList::~P_MP_SettlementUI_PotionList()
{
}

void P_MP_SettlementUI_PotionList::Initialize()
{
	//UIのベース画像を配置
	Image back(this);
	back.Load("Assets/Image/UIBaseImage4.png");
	back.SetSize({ 9*0.85f,15,0 });
	back.SetPosition({ -0.6f,-0.1f,0 });
	AddComponent<Image>(back);

	Image edge(this);
	edge.Load("Assets/Image/PotionLIstEdge07.png");
	edge.SetPosition({ -0.6f,-0.1f,0 });
	edge.SetSize({ 0.85f,0.85f,0 });
	edge.SetLayer(1);
	AddComponent<Image>(edge);

	CreateUITitle({ uiPos_.x,uiPos_.y + 0.746f }, { 10,10 }, "ポーション");

}

void P_MP_SettlementUI_PotionList::Start()
{
}

void P_MP_SettlementUI_PotionList::Update()
{
	//スクロールした分ポーションの位置を動かす
	float scroll = -XMVectorGetZ(XMVector3Normalize(Input::GetMouseMove()))* scrollSpeed_;
	if (GetComponent<Image>().IsHitCursor() && abs(scroll)>=0.1f)
	{
		move_ += scroll;
		move_ = Clamp(move_, 0.0f, 0.8f);
		for (auto itr = childList_.begin(); itr != childList_.end(); itr++)
		{
			((P_MP_SettiementUI_Potion*)itr->get())->AddPosition(move_);
		}
	}

}

void P_MP_SettlementUI_PotionList::CreateListUI(const std::vector<PlayerData::PotionData>& potionList)
{
	//ポーションリストUIを作る
	XMFLOAT3 potionPos = { 0,0.3f,0 };
	for (PlayerData::PotionData data : potionList)
	{
		if (data.isSale_)
		{
			P_MP_SettiementUI_Potion* potion = Instantiate<P_MP_SettiementUI_Potion>(this);
			potion->SetPotionData(data.tier_, data.potionName_, data.potionColor_, data.price_);
			potion->SetFirstPosition({ uiPos_.x + potionPos.x,uiPos_.y + potionPos.y,0 });
			potionPos.y -= 0.5f;
		}
	}
}

void P_MP_SettlementUI_PotionList::CreateUITitle(XMFLOAT2 pos, XMFLOAT2 diff, const std::string& str)
{
	XMINT3 color = { 102,100,82 };
	Text craftUIText(this);
	craftUIText.SetText(str);
	craftUIText.SetTextSize(55.0f);
	craftUIText.SetLayer(1);
	float rectSize = craftUIText.GetTextSize() * str.size() * 0.5f;
	TEXT_RECT rect = { 0,0,rectSize + diff.x,(float)craftUIText.GetTextSize() + diff.y };
	XMFLOAT2 ratio = { 0.5f + (pos.x * 0.5f), 0.5f - (pos.y * 0.5f) };
	ratio.x -= (rect.right / Direct3D::GetScreenWidth()) * 0.5f;
	craftUIText.SetRect(rect);
	craftUIText.SetAlignmentType(ALIGNMENT_TYPE::CENTER_CENTER);
	craftUIText.SetRatio(ratio.x, ratio.y);
	AddComponent<Text>(craftUIText);

	XMFLOAT2 imagePos = { pos.x ,pos.y - rect.bottom / Direct3D::GetScreenHeight() };
	Image base(this);
	base.Load("Assets/Image/UIBaseImage3.png");
	base.SetSize({ 0.015625f * rect.right,0.015625f * rect.bottom,0 });
	base.SetPosition({ imagePos.x,imagePos.y,0 });
	base.SetColorInt(color);
	base.SetLayer(1);
	XMFLOAT3 size = base.GetSizeAtPixel();
	//XMFLOAT2 distance = { size.x / Direct3D::GetScreenWidth(),size.y / Direct3D::GetScreenHeight() };

	float distance = rect.right / Direct3D::GetScreenWidth();
	Image start(this);
	start.Load("Assets/Image/UILong04_Start.png");
	start.SetSize({ size.y / 256,size.y / 256,0.0f });
	start.SetColorInt(color);
	start.SetLayer(1);
	//start.SetRotation({ 0,0,180 });
	start.SetPosition({ imagePos.x - distance - 0.03f,imagePos.y,0 });
	AddComponent<Image>(start);

	Image end(this);
	end.Load("Assets/Image/UILong04_End.png");
	end.SetSize({ size.y / 256,size.y / 256,0.0f });
	end.SetColorInt(color);
	end.SetLayer(1);
	end.SetPosition({ imagePos.x + distance + 0.03f,imagePos.y,0 });
	AddComponent<Image>(end);

	AddComponent<Image>(base);
}

void P_MP_SettlementUI_PotionList::Release()
{
}
