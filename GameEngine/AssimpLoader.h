#pragma once
#include<DirectXMath.h>
#define NOMINMAX
#include<d3d11.h>
#include<string>
#include<vector>

struct Mesh;
struct Vetex;
struct aiMesh;
struct aiMaterial;

struct ImportSetting
{
	std::string fileName;
	std::vector<Mesh>& meshes;
	bool isInverseU;
	bool isInverseV;

};

class AssimpLoader
{
private:
	void LoadMesh(Mesh& dst, const aiMesh* src, bool inverseU, bool inverseV);
	void LoadTexture(const wchar_t* fileName, Mesh& dst, const aiMaterial* src);
public:
	bool Load(ImportSetting setting);
};

