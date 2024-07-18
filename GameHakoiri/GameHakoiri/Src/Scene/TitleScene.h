//#pragma once
#include<string>
#include"SceneBase.h"
#include"../Common/Vector2F.h"

class TitleScene :public SceneBase
{
public:


	static constexpr float START_EX_S = 0.7f;
	static constexpr float START_EX_F = 1.0f;

	TitleScene(void);	//�R���X�g���N�^
	~TitleScene(void);	//�f�X�g���N�^

	bool Init(void);	//������
	void Update(void);	//�X�V
	void Draw(void);	//�`��
	bool Release(void);	//���
private:

	int titleImg_;
	int startImg_;
	float startEx_;
	bool isNext_;
	bool isCheck_;
	std::string str_;

	void KeyboardContoroller(void);	// �L�[�{�[�h�̑���
	void GamePadController(void);	// �Q�[���p�b�h�̑���
};