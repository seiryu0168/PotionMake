#pragma once
#include"../DirectX_11/Direct3D.h"
#include"../DirectX_11/Texture.h"
#include"DirectXMath.h"
#include"../GameObject/GameObject.h"
#include<list>

struct LineData
{
	float width;
	float endWidth;
	int   length;
	std::string textureName;
	LineData()
	{
		width = 0.5f;
		endWidth = 0.0f;
		length = 10;
		textureName = "Effect01.png";
	}

};
class LineParticle
{
	enum class LineMode
	{
		LINE_DEFAULT=0,
		LINE_CROSS,
	};

private:
	struct CONSTANT_BUFFER
	{
		XMMATRIX	matWVP;
		XMFLOAT4	color;
	};

	//頂点情報
	struct VERTEX
	{
		XMFLOAT3 position;
		XMFLOAT3 uv;
	};

	float WIDTH_;//ラインパーティクルの幅
	UINT LENGTH_;//ラインパーティクルのポジションを記憶する量
	float endWidth_;
	XMFLOAT4 color_;
	//int* index_;

	ID3D11Buffer* pVertexBuffer_;
	ID3D11Buffer* pIndexBuffer_;
	ID3D11Buffer* pConstantBuffer_;

	std::shared_ptr<Texture> pTexture_;
	std::vector<int> indexList;
	std::list<XMFLOAT3> positionList_;
	GameObject* attachObject_;
	BLEND_MODE blendMode_;
	int layerNum_;
public:
	LineParticle();
	LineParticle(GameObject* object,int lauerNum=0);
	/// <summary>
	/// ラインの位置保存
	/// 位置をポジションリストに追加
	/// </summary>
	/// <param name="pos">この関数が呼ばれた時の位置</param>
	void AddPosition(const XMFLOAT3& pos);
	/// <summary>
	/// パイプ状のラインパーティクル生成
	/// </summary>
	/// <param name="pList"></param>
	/// <returns></returns>
	HRESULT CreateMeshPype(const std::list<XMFLOAT3>* pList);
	HRESULT CreateMeshPlate(const std::list<XMFLOAT3>* pList);
	/// <summary>
	/// ラインパーティクルに使う画像のロード
	/// </summary>
	/// <param name="fileName"></param>
	/// <returns></returns>
	HRESULT Load(const std::string& fileName);
	/// <summary>
	/// ラインパーティクルの色設定
	/// </summary>
	/// <param name="col">色</param>
	void SetColor(const XMFLOAT4& col);
	/// <summary>
	/// インデックス生成
	/// </summary>
	void SetIndex();

	void Update();
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();
	void Draw(int layerNum);
	/// <summary>
	/// ラインパーティクルの各パラメータ設定
	/// </summary>
	/// <param name="width">横幅</param>
	/// <param name="length">ポジションの保存数</param>
	/// <param name="tipWidth">終端の幅</param>
	void SetLineParameter(const LineData& data);
	/// <summary>
	/// ブレンドモード設定
	/// </summary>
	/// <param name="mode">ブレンドモード</param>
	void SetBlendMode(BLEND_MODE mode) { blendMode_ = mode; }
	
	
	/// <summary>
	/// ラインパーティクルの幅設定
	/// </summary>
	/// <param name="width">幅</param>
	void SetWidth(float width) { WIDTH_ = max(0,width); }
	/// <summary>
	/// 末端の幅設定
	/// </summary>
	/// <param name="endWidth">幅</param>
	void SetEndWidth(float endWidth) { endWidth_ = max(0, endWidth); }
	/// <summary>
	/// 基準点の保存量
	/// </summary>
	/// <param name="length"></param>
	void SetLength(UINT length) { LENGTH_ = length; }
	/// <summary>
	/// アタッチされているオブジェクトを返す
	/// </summary>
	/// <returns>ゲームオブジェクト</returns>
	GameObject* GetAttachedObject() { return attachObject_; }
	void DeleteLine();
	void Release();



};

