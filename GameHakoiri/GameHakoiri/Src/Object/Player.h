//#pragma once

#include"CharacterBase.h"

class Stealth;

class Player: public CharacterBase
{
public:

	//�萔
	static constexpr float UNIT_DIR_DEG = 45.0f;

	Player(void);
	~Player(void)override;

	void SetParam(void)override;
	void Move(void)override;

	bool IsDrawMap(void)const;

private:
	void KeyboardContoroller(void);	// �L�[�{�[�h�̑���
	void GamePadController(void);	// �Q�[���p�b�h�̑���
	DIR CheckDir(float deg);					//��������

	void ChangeIsDrawMap(void);	//�}�b�v��`�悷�邩�̑I��

	bool isDrawMap_;
};