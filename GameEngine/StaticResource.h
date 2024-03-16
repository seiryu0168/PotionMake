#pragma once
#include"Engine/Components/Image.h"
#include"Engine/Components/Text.h"
#include<unordered_map>
#include<string>
//�V�[���J�ڂŏ����Ȃ��摜�ƃe�L�X�g��ۑ����鏊
namespace StaticResource
{	
	//�摜�̐����A�ǉ�
	void AddImage(std::string imageName, Image image);
	//�摜�̒ǉ�
	Image GetImage(std::string imageName);
	//�摜�̓ǂݍ���
	void StaticImageLoad(std::string imageName, std::string fileName,int cameraNum,int layerNum);
	//�e�L�X�g�̐����A�ǉ�
	void AddText(std::string textName,Text text);
	//�e�L�X�g�̎擾
	Text GetText(std::string textName);
	//�摜�ƃe�L�X�g�̏���
	void RemoveImage(std::string imageName);
	void RemoveText(std::string textName);

	void Draw();
	void Release();
};

