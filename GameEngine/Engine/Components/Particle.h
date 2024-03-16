#pragma once
#include"../GameObject/GameObject.h"
#include"../DirectX_11/BillBoard.h"
#include<list>
//�G�~�b�^�[�쐬���̃f�[�^
struct EmitterData
{
    std::string textureFileName;    //�\��e�N�X�`���̃t�@�C����
    XMFLOAT3 position;              //�G�~�b�^�[�̈ʒu
    XMFLOAT3 positionErr;           //�G�~�b�^�[�̌덷
    XMFLOAT3 dir;                   //�p�[�e�B�N���̔��˕���
    XMFLOAT3 dirErr;                //�p�[�e�B�N���̔��˕����̌덷
    float firstSpeed;               //1�t���[��������̈ړ���
    float speedErr;                 //�ړ��ʂ̌덷
    float acceleration;             //�����x
    float gravity;                  //�d��
    XMFLOAT4 color;                 //�F : RGBA 0�`�P
    XMFLOAT4 deltaColor;            //�F�̕ω���
    XMFLOAT2 size;                  //�T�C�Y
    XMFLOAT2 sizeErr;               //�T�C�Y�̌덷
    XMFLOAT2 scale;                 //1�t���[��������̊g�嗦
    DWORD lifeTime;                  //�p�[�e�B�N���̎���
    BLEND_MODE blendMode;
    
    int delay;                      //�p�[�e�B�N�����o���Ԋu�̃t���[����
    int number;                     //1��ɏo���p�[�e�B�N���̐�

//Emitter������
        EmitterData()
        {
            textureFileName = "";
            position = positionErr = dir = dirErr = { 0,0,0 };
            size = scale = { 0,0 };
            sizeErr = { 1,1 };
            firstSpeed = speedErr = 0.0f;
            acceleration = 1.0f;
            gravity = 0.0f;
            color = { 1,1,1,1 };
            deltaColor = { 0,0,0,0 };
            size = scale = { 1.0f,1.0f };
            lifeTime = 10;
            blendMode = BLEND_MODE::BLEND_ADD;
        }

};
class Particle// : public GameObject
{
private:
    //�G�~�b�^�[�̃f�[�^
    struct Emitter
    {
        EmitterData data;                   //�G�~�b�^�[�̃f�[�^
        int hParticle = -1;                 //�n���h��
        DWORD frameCount = 0;               //�o�߃t���[����
        std::unique_ptr<BillBoard> pBillBoard = nullptr;    //�p�[�e�B�N���Ɏg���|���S��
        bool isDead = false;                //�������ǂ���
        bool isStop = false;                //�p�[�e�B�N�����~�߂邩�ǂ���
        int particleCount = 0;              //���̃G�~�b�^�[����o�č��c���Ă�p�[�e�B�N���̐�
    };

    //�p�[�e�B�N���̕ω�����f�[�^
    struct Data
    {
        XMVECTOR position;  //�ʒu
        XMFLOAT2 scale;     //�T�C�Y
        XMFLOAT3 rotate;
        XMFLOAT4 color;     //�F
    };

    //�p�[�e�B�N���ꗱ�̃f�[�^
    struct ParticleData
    {
        Data     nowData;           //���̃p�[�e�B�N���f�[�^
        Data     deltaData;         //1�t���[���̕ω���
        DWORD    life;             //�c�����
        float    acceleration;     //�����x
        float    gravity;          //�d��
        Emitter* pEmitter;      //�G�~�b�^�[
    };

    std::vector<std::shared_ptr<Emitter>>      emitterList_;
    std::vector<std::shared_ptr<ParticleData>> particleList_;
    GameObject* attacheObject_;
    BLEND_MODE blendMode_;
    bool isStop_;
    int layerNum_;

    //�p�[�e�B�N���̃A�b�v�f�[�g
    void UpdateParticle();
    
    //�G�~�b�^�[�̃A�b�v�f�[�g
    void UpdateEmitter();
public:
    Particle();
    Particle(GameObject* object,int layerNum = 0);

    //�f�X�g���N�^
    ~Particle();

    //������
    void Initialize();

    //�X�V
    void Update();


    //�p�[�e�B�N������
    int ParticleStart(const EmitterData& data);
    
    //�G�~�b�^�[����
    void KillEmitter(int hEmitter);
    int SetData(const EmitterData& data);

    //�A�^�b�`����Ă�I�u�W�F�N�g��Ԃ�
    GameObject* GetAttachedObject() { return attacheObject_; }
    std::shared_ptr<Emitter> GetEmitter(int handle);

    //�p�[�e�B�N���̐������~�߂�
    void Stop() { isStop_ = true; }
    //�p�[�e�B�N���̐������ĊJ����
    void Restart() { isStop_ = false; }

    //�`��
    void Draw();
    //�`�惌�C���[����̕`��
    void Draw(int layerNum);

    //�J��
    void Release();
};

