#pragma once
#include"Direct3D.h"
#include"Texture.h"
#include"../Components/Transform.h"
#include"../SAFE_DELETE_RELEASE.h"

class Sprite
{
	struct VERTEX
	{
		XMVECTOR position;
		XMVECTOR uv;
	};
	//コンスタントバッファー
	struct CONSTANT_BUFFER
	{
		XMMATRIX matWorld;
		XMMATRIX matUVTrans;
		XMFLOAT4 color;
		XMFLOAT4 ChangeColor;
		XMFLOAT2 scroll;
	};
protected:
	ID3D11Buffer* pVertexBuffer_;	//頂点バッファ
	ID3D11Buffer* pIndexBuffer_;	//インデックスバッファ
	ID3D11Buffer* pConstantBuffer_;	//コンスタントバッファ

	DWORD vertexNum_;
	std::unique_ptr<VERTEX[]> vertices_;
	DWORD indexNum_;
	std::unique_ptr<int[]> index_;
	
	XMFLOAT3 size_;
	int hPict_;
	HRESULT CreateVertexBuffer();
	HRESULT CreateIndexBuffer();
	HRESULT CreateConstantBuffer();
	
	//void ToPipeLine(const Transform& transform);
	//void bufferSet();

public:
	Sprite();
	~Sprite();
	virtual HRESULT Initialize();
	virtual void InitVertex();
	virtual void InitIndex();
	HRESULT Load(const std::string& fileName);
	HRESULT StaticLoad(const std::string& fileName);
	void SetSize(float width, float height) { size_ = { width,height, 1.0f}; }
	XMFLOAT3 GetSize() const { return size_; }
	void Draw(Transform& transform, const RECT& rect, const XMFLOAT4& changeColor = {1,1,1,1}, float alpha = 1, XMFLOAT2 scroll = { 0,0 });
	void StaticDraw(Transform& transform, const RECT& rect, const XMFLOAT4& changeColor = {1,1,1,1}, float alpha = 1, XMFLOAT2 scroll = { 0,0 });
	void Release();
};

