#pragma once
#include<d3d11.h>
#include <memory>
#include"Texture.h"
#include"Math.h"
class Material
{
private:
	std::string materialName_;
	std::shared_ptr<Texture> pTexture_;    //テクスチャ
	std::shared_ptr<Texture> pNormalMap_;  //ノーマルマップ
	XMFLOAT4 diffuse_;	  //ディフューズ(マテリアルの色)
	XMFLOAT4 ambient_;	  //アンビエント
	XMFLOAT4 speculer_;    //スペキュラー(ツルツルを表現する奴)
	XMFLOAT4 customColor_;//プログラム側で変える色
	float shininess_;	  //ハイライトの強さ

public:
	Material();
	~Material();
	//////////////////セッター/////////////////////
	void SetMaterialName(const std::string& name);
	void SetTexture(std::shared_ptr<Texture> tex);
	void SetNormalMap(std::shared_ptr<Texture> nmlMap);
	void SetDiffuse(const XMFLOAT4& diff);
	void SetAmbient(const XMFLOAT4& amb);
	void SetSpeculer(const XMFLOAT4& spec);
	void SetCustomColor(const XMFLOAT4& color);
	void SetShininess(float shin);

	//////////////////ゲッター/////////////////////
	const std::shared_ptr<Texture> GetTexture() const { return pTexture_; }
	const std::shared_ptr<Texture> GetNormalMap() const { return pNormalMap_; }
	const XMFLOAT4& GetDiffuse() const { return diffuse_; }
	const XMFLOAT4& GetAmbient() const { return ambient_; }
	const XMFLOAT4& GetSpeculer() const { return speculer_; }
	const XMFLOAT4& GetCustomColor() const { return customColor_; }
	const float& GetShininess() const { return shininess_; }
};

