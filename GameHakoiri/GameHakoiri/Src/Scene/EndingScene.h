//#pragma once
#include"SceneBase.h"

class EndingScene :public SceneBase
{
public:


	static constexpr float EX_S = 1.0f;
	static constexpr float EX_F = 1.3f;

	static constexpr int BACK_TITLE_X = 512;
	static constexpr int BACK_TITLE_Y = 256;
	static constexpr int THANK_SIZE = 512;

	EndingScene(void);	//�R���X�g���N�^
	~EndingScene(void);	//�f�X�g���N�^

	bool Init(void);	//������
	void Update(void);	//�X�V
	void Draw(void);	//�`��
	bool Release(void);	//���
private:

	int endImg_;
	int backTitleImg_;
	float endEx_;

	void KeyboardContoroller(void);	// �L�[�{�[�h�̑���
	void GamePadController(void);	// �Q�[���p�b�h�̑���
};