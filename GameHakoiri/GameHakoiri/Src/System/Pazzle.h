//#pragma once

class StageManager;

class Pazzle
{
public:
	Pazzle(void);	//�R���X�g���N�^
	~Pazzle(void);	//�f�X�g���N�^

	void Update(void);	//�X�V

	void KeyboardContoroller(void);	// �L�[�{�[�h�̑���
	void GamePadController(void);	// �Q�[���p�b�h�̑���

private:
	bool isSelect_;		//�I�𒆂��ǂ���

	void ChangeIsSelect(bool);	//IsSelect�̕ύX
};

