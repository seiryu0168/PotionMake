#include "Particle.h"
#include"../GameObject/CameraManager.h"

Particle::Particle() : Particle(nullptr)
{
	layerNum_ = 0;
	blendMode_ = BLEND_MODE::BLEND_ADD;
}

Particle::Particle(GameObject* object,int layerNum)
	:attacheObject_(object),
	blendMode_(BLEND_MODE::BLEND_ADD),
	isStop_(false),
	layerNum_(layerNum)
{

}

//デストラクタ
Particle::~Particle()
{
	Release();
}

//初期化
void Particle::Initialize()
{
}

//更新
void Particle::Update()
{
	UpdateEmitter();
	UpdateParticle();
}

void Particle::UpdateParticle()
{
	for (auto particleCount = particleList_.begin(); particleCount != particleList_.end();)
	{
		//パーティクルの寿命がなくなったら
		if ((*particleCount)->life == 0)
		{
			(*particleCount)->pEmitter->particleCount--;
			//SAFE_DELETE(*particleCount);
			particleCount = particleList_.erase(particleCount);
		}

		//生きてる場合
		else
		{
			(*particleCount)->life--;

			//パーティクルの位置を更新
			(*particleCount)->nowData.position+= (*particleCount)->deltaData.position;
			//(*particleCount)->nowData.position.y += (*particleCount)->deltaData.position.y;
			//(*particleCount)->nowData.position.z += (*particleCount)->deltaData.position.z;

			//パーティクルの速度(移動量)を加速度で更新
			(*particleCount)->deltaData.position *= (*particleCount)->acceleration;
			//(*particleCount)->deltaData.position.y *= (*particleCount)->acceleration;
			//(*particleCount)->deltaData.position.z *= (*particleCount)->acceleration;
			
			//重力
			(*particleCount)->deltaData.position += XMVectorSet(0,-(*particleCount)->gravity,0,0);

			//拡大率を更新
			(*particleCount)->nowData.scale.x *= (*particleCount)->deltaData.scale.x;
			(*particleCount)->nowData.scale.y *= (*particleCount)->deltaData.scale.y;

			//色更新
			(*particleCount)->nowData.color.x += (*particleCount)->deltaData.color.x; //R
			(*particleCount)->nowData.color.y += (*particleCount)->deltaData.color.y; //G
			(*particleCount)->nowData.color.z += (*particleCount)->deltaData.color.z; //B
			(*particleCount)->nowData.color.w += (*particleCount)->deltaData.color.w; //A
			
			particleCount++;
		}

	}
}

void Particle::UpdateEmitter()
{
	if (isStop_)
		return;
	for (auto emitterCount = emitterList_.begin(); emitterCount != emitterList_.end();)
	{
		//死んでるエミッターの処理
		if ((*emitterCount)->isDead)
		{
			//パーティクル出てなければ削除
			if ((*emitterCount)->particleCount == 0)
			{
				(*emitterCount)->pBillBoard->Release();
				//SAFE_DELETE((*emitterCount)->pBillBoard);
				//SAFE_DELETE(*emitterCount);
				emitterCount = emitterList_.erase(emitterCount);
			}
			else
				emitterCount++;
		}
		else
		{
			//パーティクルを発生させる
			if ((*emitterCount)->data.delay == 0 || ((*emitterCount)->frameCount % (*emitterCount)->data.delay) == 0)
			{
				for (int particleNum = 0; particleNum < (*emitterCount)->data.number; particleNum++)
				{
					std::unique_ptr<ParticleData> pParticle = std::make_unique<ParticleData>();
					
					//初期位置
					pParticle->nowData.position = XMLoadFloat3(&(*emitterCount)->data.position);
					float deltaX = (float)((*emitterCount)->data.positionErr.x == 0 ? 0 : rand() % (int)((*emitterCount)->data.positionErr.x * 201) - ((*emitterCount)->data.positionErr.x * 100))/100.0f;
					float deltaY = (float)((*emitterCount)->data.positionErr.y == 0 ? 0 : rand() % (int)((*emitterCount)->data.positionErr.y * 201) - ((*emitterCount)->data.positionErr.y * 100))/100.0f;
					float deltaZ = (float)((*emitterCount)->data.positionErr.z == 0 ? 0 : rand() % (int)((*emitterCount)->data.positionErr.z * 201) - ((*emitterCount)->data.positionErr.z * 100))/100.0f;
					pParticle->nowData.position += XMVectorSet(deltaX,deltaY,deltaZ,0);
	

					//初期サイズ
					deltaX = (float)((*emitterCount)->data.sizeErr.x == 0 ? 0 : rand() % (int)((*emitterCount)->data.sizeErr.x * 201) - ((*emitterCount)->data.sizeErr.x * 100)) / 100.0f + 1.0f;
					deltaY = (float)((*emitterCount)->data.sizeErr.y == 0 ? 0 : rand() % (int)((*emitterCount)->data.sizeErr.y * 201) - ((*emitterCount)->data.sizeErr.y * 100)) / 100.0f + 1.0f;
					pParticle->nowData.scale.x = (*emitterCount)->data.size.x * deltaX;
					pParticle->nowData.scale.y = (*emitterCount)->data.size.y * deltaY;

					//初期色
					pParticle->nowData.color = (*emitterCount)->data.color;

					//パーティクル発射方向
					XMVECTOR vecDir = XMLoadFloat3(&(*emitterCount)->data.dir);
					deltaX = (float)((*emitterCount)->data.dirErr.x == 0 ? 0 : rand() % (int)((*emitterCount)->data.dirErr.x * 201) - ((*emitterCount)->data.dirErr.x * 100)) / 100.0f;
					deltaY = (float)((*emitterCount)->data.dirErr.y == 0 ? 0 : rand() % (int)((*emitterCount)->data.dirErr.y * 201) - ((*emitterCount)->data.dirErr.y * 100)) / 100.0f;
					deltaZ = (float)((*emitterCount)->data.dirErr.z == 0 ? 0 : rand() % (int)((*emitterCount)->data.dirErr.z * 201) - ((*emitterCount)->data.dirErr.z * 100)) / 100.0f;

					//ピッチ、ヨー、ロールをクォータニオンで表現
					XMVECTOR dirQuaternion = XMQuaternionRotationRollPitchYaw(XMConvertToRadians(deltaX),
																			  XMConvertToRadians(deltaY),
																			  XMConvertToRadians(deltaZ));
					//クォータニオンで誤差分回転
					vecDir = XMVector3Rotate(vecDir, dirQuaternion);
						//XMVector3TransformCoord(vecDir, matX * matY * matZ);

					float spd = (float)((*emitterCount)->data.speedErr == 0 ? 0 : (int)((*emitterCount)->data.speedErr * 201) - ((*emitterCount)->data.speedErr * 100)) / 100.0f+1.0f;
		
					vecDir = XMVector3Normalize(vecDir) * (*emitterCount)->data.firstSpeed * spd;
					pParticle->deltaData.position = vecDir;
					pParticle->deltaData.scale = (*emitterCount)->data.scale;		//パーティクルの拡大率
					pParticle->deltaData.color = (*emitterCount)->data.deltaColor;	//パーティクルの色
				

					pParticle->life = (*emitterCount)->data.lifeTime;				//パーティクルの寿命
					pParticle->gravity = (*emitterCount)->data.gravity;				//パーティクルのにかかる重力
					pParticle->acceleration = (*emitterCount)->data.acceleration;	//パーティクルの加速度
					
					pParticle->pEmitter = emitterCount->get();
					++pParticle->pEmitter->particleCount;

					//作成したパーティクルをリストに入れる
					particleList_.push_back(std::move(pParticle));

				}
			}

			//パーティクルの発射間隔が0フレームの場合、一発出して削除
			if ((*emitterCount)->data.delay == 0)
			{
				(*emitterCount)->isDead = true;
			}

			++emitterCount;
		}
	}
}

int Particle::ParticleStart(const EmitterData& data)
{
	int handle = 0;
	/*for (auto&& emitterCount : emitterList_)
	{
		handle++;
	}*/

	std::unique_ptr<Emitter> pEmitter = std::make_unique<Emitter>();

	pEmitter->data = data;
	pEmitter->frameCount = 0;

	pEmitter->pBillBoard = std::make_unique<BillBoard>();
	pEmitter->pBillBoard->Load(data.textureFileName);
	handle = (int)emitterList_.size() - 1;
	pEmitter->hParticle = handle;
	emitterList_.push_back(std::move(pEmitter));
	return handle;
	//return handle;
}

void Particle::KillEmitter(int hEmitter)
{
	for (auto&& itr : emitterList_)
	{
		if (itr->hParticle == hEmitter)
		{
			itr->isDead = true;
			return;
		}
	}
}

int Particle::SetData(const EmitterData& data)
{
	//パーティクルのデータをエミッターにセット
	int handle = 0;

	std::shared_ptr<Emitter> pEmitter = std::make_shared<Emitter>();

	pEmitter->data = data;
	pEmitter->frameCount = 0;

	pEmitter->pBillBoard = std::make_unique<BillBoard>();
	pEmitter->pBillBoard->Load(data.textureFileName);
	blendMode_ = data.blendMode;
	emitterList_.push_back(pEmitter);
	handle = (int)emitterList_.size() - 1;
	pEmitter->hParticle = handle;
	return handle;
}

std::shared_ptr<Particle::Emitter> Particle::GetEmitter(int handle)
{
	return emitterList_[handle];
}

//描画
void Particle::Draw()
{
	Direct3D::SetShader(SHADER_TYPE::SHADER_EFF);
	Direct3D::SetBlendMode(blendMode_);

	for (auto&& itr : particleList_)
	{
		XMMATRIX matW;

		//移動行列
		XMFLOAT3 pos = StoreFloat3(itr->nowData.position);
		XMMATRIX matTrans = attacheObject_->GetTransform()->GetWorldMatrix()*XMMatrixTranslation(pos.x, pos.y, pos.z);
		
		//拡大行列
		XMMATRIX matScale = XMMatrixScaling(itr->nowData.scale.x, itr->nowData.scale.y, 1.0f);

		matW = matScale * CameraManager::GetCurrentCamera().GetBillBoardMatrix() * matTrans;
		itr->pEmitter->pBillBoard->Draw(matW, itr->nowData.color);
	}
}

void Particle::Draw(int layerNum)
{
	//レイヤー番号に応じて描画

	if (layerNum != layerNum_)
		return;

	Direct3D::SetShader(SHADER_TYPE::SHADER_EFF);
	Direct3D::SetBlendMode(blendMode_);

	for (auto&& itr : particleList_)
	{
		XMMATRIX matW;

		//移動行列
		XMFLOAT3 pos = StoreFloat3(itr->nowData.position);
		XMMATRIX matTrans = attacheObject_->GetTransform()->GetWorldMatrix() * XMMatrixTranslation(pos.x, pos.y, pos.z);

		//拡大行列
		XMMATRIX matScale = XMMatrixScaling(itr->nowData.scale.x, itr->nowData.scale.y, 1.0f);

		matW = matScale * CameraManager::GetCurrentCamera().GetBillBoardMatrix() * matTrans;
		itr->pEmitter->pBillBoard->Draw(matW, itr->nowData.color);
	}
}

//開放
void Particle::Release()
{

}