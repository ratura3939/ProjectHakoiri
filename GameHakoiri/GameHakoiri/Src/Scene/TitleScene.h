//#pragma once
#include"SceneBase.h"
#include"../Common/Vector2F.h"

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

	bool isNext_;

	void KeyboardContoroller(void);	// �L�[�{�[�h�̑���
	void GamePadController(void);	// �Q�[���p�b�h�̑���
};