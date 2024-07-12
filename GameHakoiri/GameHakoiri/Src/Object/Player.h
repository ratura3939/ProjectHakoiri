//#pragma once

#include"CharacterBase.h"

class Stealth;

class Player: public CharacterBase
{
public:

	//�萔
	static constexpr float UNIT_DIR_DEG = 45.0f;
	static constexpr float HP = 100.0f;
	static constexpr float HP_SIZE = 128.0f;

	Player(void);
	~Player(void)override;

	void SetParam(void)override;
	void Move(void)override;
	void Draw(void)override;

	bool IsDrawMap(void)const;
	float GetHp(void)const;
	void Damage(void);

private:
	void KeyboardContoroller(void);	// �L�[�{�[�h�̑���
	void GamePadController(void);	// �Q�[���p�b�h�̑���
	DIR CheckDir(float deg);					//��������

	void ChangeIsDrawMap(void);	//�}�b�v��`�悷�邩�̑I��

	float hp_;
	Vector2F hpPos_;
	int hpBaseImg_;
	int hpCircleImg_;
	int hpText_;

	bool isDrawMap_;
};