#include "Collider.h"
#include"../../DebugUI.h"
#include "Collider.h"
#include"../GameObject/GameObject.h"


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
	fieldSize_({200,200,200}),
	maxDivisionCount_(3)
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
	//�R���C�_�[�^�C�v�ɂ���ď���
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
	//�ŏ���prevAccessNumber���擾
	prevAccessNumber_ = GetAccessNumber();
	//
}

int Collider::GetAccessNumber()
{
	int luNum = GetMortonOrderNumber(StoreFloat3(StoreFloat3(attachObject_->GetTransform()->position_) + leftUpBack_));
	int rdNum = GetMortonOrderNumber(StoreFloat3(StoreFloat3(attachObject_->GetTransform()->position_) + rightDownFront_));

	////////////////������Ԃ��Z�o/////////////////
	//�r���I�_���a���Ƃ�
	int affiliation = luNum ^ rdNum;

	int aff = affiliation << 3;
	int mask = 0x00000007;
	int shiftCount = 0;

	//���[�g��Ԃ܂�3���r�b�g�V�t�g
	for (int i = 0; i < 4; i++)
	{
		if ((affiliation & mask) >= 1)
			shiftCount = i;
		mask = mask << 3;
	}
	int affiliationNum = (luNum >> shiftCount * 3);

	//�A�N�Z�X�����Ԃ̔z��ԍ����Z�o
	//�V�t�g�����������������x���͉�����(0=���[�g���)
	int accessNum = affiliationNum + ((int)(pow(8, (3 - shiftCount)) - 1) / 7);
	//Debug.Log("������ԕ������x��" + (3 - shiftCount));
	//Debug.Log("�������" + (luNum >> shiftCount * 2));
	//Debug.Log("�A�N�Z�X�ԍ�" + accessNum);
	cellLevel_ = 3 - shiftCount;
	if (cellLevel_ == 0)
	{
		int a = 0;
	}
	return accessNum;
}

int Collider::GetMortonOrderNumber(XMFLOAT3 pos)
{
	if (pos.y <= 0)
		pos.y = fabs(pos.y) + (fieldSize_.y * 0.5f);
	else if (pos.y > 0)
		pos.y = (fieldSize_.y * 0.5f) - pos.y;
	//pos += new Vector3(fieldSize_.x * 0.5f, 0, -(fieldSize_.z * 0.5f));
	pos.x += fieldSize_.x * 0.5f;
	pos.z += fieldSize_.z * 0.5f;
	//pos.z *= -1;

	float cellSize = fieldSize_.x / pow(2, maxDivisionCount_);

	//����Ԃ̍��W
	int x = (int)(pos.x / cellSize);
	int y = (int)(pos.y / cellSize);
	int z = (int)(pos.z / cellSize);

	//Debug.Log(cellSize+"X:" + Convert.ToString(x,2) + "\n" + "Z:" + Convert.ToString(z, 2));
	//Debug.Log(cellSize + "X:" + x + "\n" + "Z:" + z);

	//Debug.Log(Convert.ToString(BitSeparate(x), 2)+"\n"+ Convert.ToString(BitSeparate(z), 2));

	//���[�g���I�[�_�[�̔ԍ��o��
	int mortonNum = BitSeparate(x) | (BitSeparate(y) << 1 | BitSeparate(z) << 2);
	return mortonNum;
}

int Collider::BitSeparate(int n)
{
	//�e�r�b�g��3�r�b�g���ƂɍL����
	n = (n | (n << 8)) & 0x0000f00f;//0000|0000|0000|0000|1111|0000|0000|1111
	n = (n | (n << 4)) & 0x000c30c3;//0000|0000|0000|1100|0011|0000|1100|0011
	n = (n | (n << 2)) & 0x00249249;//0000|0000|0010|0100|1001|0010|0010|1001

	return n;
}
