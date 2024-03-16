#include "Material.h"
#include"../SAFE_DELETE_RELEASE.h"
Material::Material()
	:pTexture_(nullptr),
	pNormalMap_(nullptr),
	diffuse_({0,0,0,0}),
	ambient_({0,0,0,0}),
	speculer_({0,0,0,0}),
	customColor_({1,1,1,1}),
	shininess_(0)
{
}

Material::~Material()
{
	//SAFE_RELEASE_DELETE(pTexture_);
	//SAFE_RELEASE_DELETE(pNormalMap_);
	SAFE_RELEASE(pTexture_);
	SAFE_RELEASE(pNormalMap_);
}

void Material::SetMaterialName(const std::string& name)
{
	materialName_ = name;
}

void Material::SetTexture(std::shared_ptr<Texture> tex)
{
	/*if (pTexture_ != nullptr)
		SAFE_RELEASE_DELETE(pTexture_);*/
	pTexture_ = tex;
}

void Material::SetNormalMap(std::shared_ptr<Texture> nmlMap)
{
	pNormalMap_ = nmlMap;
}

void Material::SetDiffuse(const XMFLOAT4& diff)
{
	diffuse_=diff;
}

void Material::SetAmbient(const XMFLOAT4& amb)
{
	ambient_ = amb;
}

void Material::SetSpeculer(const XMFLOAT4& spec)
{
	speculer_ = spec;
}

void Material::SetCustomColor(const XMFLOAT4& color)
{
	customColor_ = color;
}

void Material::SetShininess(float shin)
{
	shininess_ = shin;
}