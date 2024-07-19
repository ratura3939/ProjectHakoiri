//#pragma once
#include"SceneBase.h"

class ResultScene :public SceneBase
{
public:

	static constexpr int RESULT_SIZE_X = 256;
	static constexpr int RESULT_SIZE_Y = 128;
	static constexpr int RESULT_FLASH = 30;
	static constexpr int RESULT_FLASH_MAX = 3000;

	ResultScene(void);	//�R���X�g���N�^
	~ResultScene(void);	//�f�X�g���N�^

	bool Init(void);	//������
	void Update(void);	//�X�V
	void Draw(void);	//�`��
	bool Release(void);	//���
private:
	bool result_;
	int resultImg_[2];
	int backSelectImg_;
	int flash_;

	void KeyboardContoroller(void);	// �L�[�{�[�h�̑���
	void GamePadController(void);	// �Q�[���p�b�h�̑���
};