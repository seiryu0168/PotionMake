#pragma once
#include"Engine/GameObject/GameObject.h"
/// <summary>
/// �o�c�p�[�g�̊�{�I�ȓ����\������UI
/// �|�[�V��������A�Ǘ��A�O�o���̃A�N�V������\��
/// </summary>
class Play_ManagementPart_BaseUI : public GameObject
{
private:
	int UINum_;
	bool isAccessUI_;
public:
	Play_ManagementPart_BaseUI(Object* parent);
	~Play_ManagementPart_BaseUI();
	void Initialize() override;
	void Start() override;
	void Update() override;
	void AccessUI(int uiNum);
	void SetAccessUIFlag(bool flag) { isAccessUI_ = flag; }
	bool IsAccessUI() { return isAccessUI_; }
	void DisplayAction(std::string action, bool isDisplay);
	int GetUINum() { return UINum_; }
	void Release() override;
};

