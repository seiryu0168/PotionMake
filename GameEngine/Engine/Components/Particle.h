#pragma once
#include"../GameObject/GameObject.h"
#include"../DirectX_11/BillBoard.h"
#include<list>
//エミッター作成時のデータ
struct EmitterData
{
    std::string textureFileName;    //貼るテクスチャのファイル名
    XMFLOAT3 position;              //エミッターの位置
    XMFLOAT3 positionErr;           //エミッターの誤差
    XMFLOAT3 dir;                   //パーティクルの発射方向
    XMFLOAT3 dirErr;                //パーティクルの発射方向の誤差
    float firstSpeed;               //1フレームあたりの移動量
    float speedErr;                 //移動量の誤差
    float acceleration;             //加速度
    float gravity;                  //重力
    XMFLOAT4 color;                 //色 : RGBA 0～１
    XMFLOAT4 deltaColor;            //色の変化量
    XMFLOAT2 size;                  //サイズ
    XMFLOAT2 sizeErr;               //サイズの誤差
    XMFLOAT2 scale;                 //1フレームあたりの拡大率
    DWORD lifeTime;                  //パーティクルの寿命
    BLEND_MODE blendMode;
    
    int delay;                      //パーティクルを出す間隔のフレーム数
    int number;                     //1回に出すパーティクルの数

//Emitter初期化
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
    //エミッターのデータ
    struct Emitter
    {
        EmitterData data;                   //エミッターのデータ
        int hParticle = -1;                 //ハンドル
        DWORD frameCount = 0;               //経過フレーム数
        std::unique_ptr<BillBoard> pBillBoard = nullptr;    //パーティクルに使うポリゴン
        bool isDead = false;                //消すかどうか
        bool isStop = false;                //パーティクルを止めるかどうか
        int particleCount = 0;              //このエミッターから出て今残ってるパーティクルの数
    };

    //パーティクルの変化するデータ
    struct Data
    {
        XMVECTOR position;  //位置
        XMFLOAT2 scale;     //サイズ
        XMFLOAT3 rotate;
        XMFLOAT4 color;     //色
    };

    //パーティクル一粒のデータ
    struct ParticleData
    {
        Data     nowData;           //今のパーティクルデータ
        Data     deltaData;         //1フレームの変化量
        DWORD    life;             //残り寿命
        float    acceleration;     //加速度
        float    gravity;          //重力
        Emitter* pEmitter;      //エミッター
    };

    std::vector<std::shared_ptr<Emitter>>      emitterList_;
    std::vector<std::shared_ptr<ParticleData>> particleList_;
    GameObject* attacheObject_;
    BLEND_MODE blendMode_;
    bool isStop_;
    int layerNum_;

    //パーティクルのアップデート
    void UpdateParticle();
    
    //エミッターのアップデート
    void UpdateEmitter();
public:
    Particle();
    Particle(GameObject* object,int layerNum = 0);

    //デストラクタ
    ~Particle();

    //初期化
    void Initialize();

    //更新
    void Update();


    //パーティクル発生
    int ParticleStart(const EmitterData& data);
    
    //エミッター消去
    void KillEmitter(int hEmitter);
    int SetData(const EmitterData& data);

    //アタッチされてるオブジェクトを返す
    GameObject* GetAttachedObject() { return attacheObject_; }
    std::shared_ptr<Emitter> GetEmitter(int handle);

    //パーティクルの生成を止める
    void Stop() { isStop_ = true; }
    //パーティクルの生成を再開する
    void Restart() { isStop_ = false; }

    //描画
    void Draw();
    //描画レイヤーありの描画
    void Draw(int layerNum);

    //開放
    void Release();
};

