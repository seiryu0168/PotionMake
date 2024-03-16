#pragma once
#include <d3d11.h>
#include <string>

class Texture
{

	ID3D11SamplerState* pSampler_;		//サンプラー
	ID3D11ShaderResourceView* pSRV_;	//シェーダーリソースビュー


	UINT imgWidth_;
	UINT imgHeight_;
public:
	Texture();
	~Texture();
	/// <summary>
	/// 画像ロード(ファイル名のみ)
	/// </summary>
	/// <param name="fileName">ファイル名</param>
	/// <returns></returns>
	HRESULT Load(const LPCWSTR& fileName);
	/// <summary>
	/// 画像ロード(パス込み)
	/// </summary>
	/// <param name="fileName">ファイル名</param>
	/// <returns></returns>
	HRESULT Load(const std::string& fileName);
	ID3D11SamplerState* GetSampler() const { return pSampler_; }
	ID3D11ShaderResourceView* GetSRV() const { return pSRV_; }


	UINT GetWidth() const;
	UINT GetHeight() const;
	void Release();
};