#include "Collider.h"
#include"../../DebugUI.h"
#include "Collider.h"
#include"../GameObject/GameObject.h"
#include"../newSceneManager.h"


Collider::Collider() : Collider({0,0,0})
{
}

Collider::Collider(const XMFLOAT3& centerPos)
	:attachObject_(nullptr),
	center_(centerPos),
	isKill_(false),
	colliderType_(ColliderType::BOX_COLLIDER),
	colliderEntity_(0),
	nowHit_(false),
	prevHit_(false),
	isShowHitArea_(true),
	collisionDistanceLimit_(100),
	fieldSize_({2000,2000,2000}),
	maxDivisionLevel_(2),
	prevAccessNumber_(-1)
{
#if _DEBUG
	isShowHitArea_ = true;
#else
	isShowHitArea_ = false;
#endif
}

Collider::~Collider()
{
}

void Collider::Draw()
{

}

void Collider::Release()
{
	//コライダータイプによって消す
	switch (colliderType_)
	{
	case ColliderType::BOX_COLLIDER:
		Coordinator::RemoveComponent<HitBox>(colliderEntity_);
		break;
	case ColliderType::SPHERE_COLLIDER:
		Coordinator::RemoveComponent<HitSphere>(colliderEntity_);
		break;
	case ColliderType::CAPSULE_COLLIDER:
		Coordinator::RemoveComponent<Hit_Capsule>(colliderEntity_);
		break;
	case ColliderType::OBB_COLLIDER:
		Coordinator::RemoveComponent<HitBox_OBB>(colliderEntity_);
	default:
		break;
	}
}


void Collider::SetCollisionType(const std::string& name)
{
	if (name == "struct HitBox")
		colliderType_ = ColliderType::BOX_COLLIDER;
	else if (name == "struct HitSphere")
		colliderType_ = ColliderType::SPHERE_COLLIDER;
	else if (name == "struct Hit_Capsule")
		colliderType_ = ColliderType::CAPSULE_COLLIDER;
	else if ("struct HitBox_OBB")
		colliderType_ = ColliderType::OBB_COLLIDER;
}

void Collider::SetCollisionPoint()
{
	switch (colliderType_)
	{
	case ColliderType::BOX_COLLIDER:
		{
			XMFLOAT3 colsize = GetCollisionShape<HitBox>().size_;
			leftUpBack_ = { -colsize.x,colsize.y,colsize.z };
			rightDownFront_ = { colsize.x,-colsize.y,-colsize.z };
		}
	break;
	case ColliderType::SPHERE_COLLIDER:
		{
			float colsize = GetCollisionShape<HitSphere>().radius_;
			leftUpBack_ = { -colsize,colsize,colsize };
			rightDownFront_ = { colsize,-colsize,-colsize };
		}
	break;

	}
}

void Collider::MortonOrderSolver()
{
	////最初のprevAccessNumberを取得
	//prevAccessNumber_ = GetAccessNumber();
	////アクセスする空間番号を取得
	//int accessNum = GetAccessNumber();
	////accessNumが以前と違ったら
	//if (accessNum != prevAccessNumber_)
	//{
	//	//以前まで所属していた空間から削除、
	//	//取得した番号の空間番号の空間に登録する
	//	
	//}
}

void Collider::CalcAccessNumber()
{
	int luNum = GetMortonOrderNumber(StoreFloat3(attachObject_->GetTransform()->position_ + (center_ + leftUpBack_)));
	int rdNum = GetMortonOrderNumber(StoreFloat3(attachObject_->GetTransform()->position_ + (center_ + rightDownFront_)));

	////////////////所属空間を算出/////////////////
	//排他的論理和をとる
	int XOR = luNum ^ rdNum;

	int aff		   = XOR << 3;
	int mask	   = 0x00000007;
	int shiftCount = 0;
	int shift	   = 0;

	int i = 0;
	//ルート空間まで3ずつビットシフト
	while (XOR!=0)
	{
		if ((XOR & 0x7) != 0)
		{

			shiftCount = i+1;
			shift	   = shiftCount * 3;

		}
		XOR >>= 3;
		i++;
	}
	int affiliationNum = (luNum >> shift);

	cellLevel_ = maxDivisionLevel_ - shiftCount;
	//アクセスする空間の配列番号を算出
	//シフトした数だけ分割レベルは下がる(0=ルート空間)
	currentAccessNumber_ = affiliationNum + ((int)(pow(8, cellLevel_) - 1) / 7);
	//Debug.Log("所属空間分割レベル" + (3 - shiftCount));
	//Debug.Log("所属空間" + (luNum >> shiftCount * 2));
	//Debug.Log("アクセス番号" + accessNum);
}

int Collider::GetMortonOrderNumber(XMFLOAT3 pos)
{
	//if (pos.y <= 0)
	//	pos.y = fabs(pos.y) + (fieldSize_.y * 0.5f);
	//else if (pos.y > 0)
	//	pos.y = (fieldSize_.y * 0.5f) - pos.y;
	//pos += new Vector3(fieldSize_.x * 0.5f, 0, -(fieldSize_.z * 0.5f));
	pos.x += fieldSize_.x * 0.5f;
	pos.y += fieldSize_.y * 0.5f;
	pos.z += fieldSize_.z * 0.5f;
	//pos.z *= -1;

	float cellSize = fieldSize_.x / pow(2, maxDivisionLevel_);

	//孫空間の座標
	int x = (int)(pos.x / cellSize);
	int y = (int)(pos.y / cellSize);
	int z = (int)(pos.z / cellSize);

	//Debug.Log(cellSize+"X:" + Convert.ToString(x,2) + "\n" + "Z:" + Convert.ToString(z, 2));
	//Debug.Log(cellSize + "X:" + x + "\n" + "Z:" + z);

	//Debug.Log(Convert.ToString(BitSeparate(x), 2)+"\n"+ Convert.ToString(BitSeparate(z), 2));

	//モートンオーダーの番号出す
	int mortonNum = BitSeparate(x) | (BitSeparate(y) << 1 | BitSeparate(z) << 2);
	return mortonNum;
}

int Collider::BitSeparate(int n)
{
	//各ビットを3ビットごとに広げる
	n = (n | (n << 8)) & 0x0000f00f;//0000|0000|0000|0000|1111|0000|0000|1111
	n = (n | (n << 4)) & 0x000c30c3;//0000|0000|0000|1100|0011|0000|1100|0011
	n = (n | (n << 2)) & 0x00249249;//0000|0000|0010|0100|1001|0010|0010|1001

	return n;
}
