//#pragma once
#include"SceneBase.h"

class TitleScene :public SceneBase
{
public:
	TitleScene(void);	//�R���X�g���N�^
	~TitleScene(void);	//�f�X�g���N�^

	bool Init(void);	//������
	void Update(void);	//�X�V
	void Draw(void);	//�`��
	bool Release(void);	//���
private:
	void KeyboardContoroller(void);	// �L�[�{�[�h�̑���
	void GamePadController(void);	// �Q�[���p�b�h�̑���
};