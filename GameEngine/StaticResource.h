#pragma once
#include"Engine/Components/Image.h"
#include"Engine/Components/Text.h"
#include<unordered_map>
#include<string>
//シーン遷移で消えない画像とテキストを保存する所
namespace StaticResource
{	
	//画像の生成、追加
	void AddImage(std::string imageName, Image image);
	//画像の追加
	Image GetImage(std::string imageName);
	//画像の読み込み
	void StaticImageLoad(std::string imageName, std::string fileName,int cameraNum,int layerNum);
	//テキストの生成、追加
	void AddText(std::string textName,Text text);
	//テキストの取得
	Text GetText(std::string textName);
	//画像とテキストの消去
	void RemoveImage(std::string imageName);
	void RemoveText(std::string textName);

	void Draw();
	void Release();
};

