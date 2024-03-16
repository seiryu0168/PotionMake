#include "AssimpLoader.h"
#include <assimp/Importer.hpp>
#include<assimp/postprocess.h>
#include<assimp/scene.h>
#include"Mesh.h"
#include<filesystem>
//#pragma comment(lib,"assimp-vc143-mt.lib")
namespace fs = std::filesystem;

//std::wstring GetDirectoryPath(const std::wstring& originalPath)
//{
//	//fs::path path = originalPath.c_str();
//	//return path.remove_filename().c_str();
//}


void AssimpLoader::LoadMesh(Mesh& dst, const aiMesh* src, bool inverseU, bool inverseV)
{
	//aiVector3D aro3D(0.0f, 0.0f, 0.0f);
	//aiColor4D  zeroColor(0.0f, 0.0f, 0.0f, 0.0f);
	//dst.vertices.resize(src->mNumVertices);

}

void AssimpLoader::LoadTexture(const wchar_t* fileName, Mesh& dst, const aiMaterial* src)
{

}

bool AssimpLoader::Load(ImportSetting setting)
{
	if (setting.fileName.size()<=0)
	{
		return false;
	}
	auto& meshes = setting.meshes;
	auto inverseU = setting.isInverseU;
	auto inverseV = setting.isInverseV;
	
	auto path = setting.fileName;
	
	//原因は分からないが、引数無しのコンストラクタを明示しておかないとダメらしい
	Assimp::Importer importer;
	//int flag=0;
	//flag |= aiProcess_Triangulate;
	//flag |= aiProcess_PreTransformVertices;
	//flag |= aiProcess_CalcTangentSpace;
	//flag |= aiProcess_GenSmoothNormals;
	//flag |= aiProcess_GenUVCoords;
	//flag |= aiProcess_RemoveRedundantMaterials;
	//flag |= aiProcess_OptimizeMeshes;
	//
	//auto scene = importer.ReadFile(setting.fileName,flag);
	//
	//if (scene == nullptr)
	//	return false;
	//
	//meshes.clear();
	//meshes.resize(scene->mNumMeshes);
	//for (size_t i = 0; i < meshes.size(); ++i)
	//{
	//	const auto pMesh = scene->mMeshes[i];
	//	LoadMesh(meshes[i], pMesh, inverseU, inverseV);
	//	const auto pMaterial = scene->mMaterials[i];
	//	LoadTexture(setting.fileName, meshes[i], pMaterial);
	//}
}