//#pragma once
#include"SceneBase.h"

class ResultScene :public SceneBase
{
public:
	ResultScene(void);	//�R���X�g���N�^
	~ResultScene(void);	//�f�X�g���N�^

	bool Init(void);	//������
	void Update(void);	//�X�V
	void Draw(void);	//�`��
	bool Release(void);	//���
private:

	void KeyboardContoroller(void);	// �L�[�{�[�h�̑���
	void GamePadController(void);	// �Q�[���p�b�h�̑���
};