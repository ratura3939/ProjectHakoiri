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
	static constexpr float DASH = 2.0f;
	static constexpr float USE_STAMINA = 2.0f;
	static constexpr float STAMINA_MAX = 128.0f;
	static constexpr float STAMINA_BOX = 16.0f;
	static constexpr float STAMINA_RECOVERY = 0.5f;
	static constexpr int RED = 0xff0000;
	static constexpr int ORENGE = 0xffa500;

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

	void RecoveryStamina(void);	//�X�^�~�i�̉�

	bool isDash_;	//�_�b�V�����\��
	float dash_;	//�_�b�V���̔{��
	float stamina_;//�_�b�V���Ɏg�p����X�^�~�i
	int staminaColor_;	//�X�^�~�i�Q�[�W�̃J���[

	//HP�o�[�\��
	float hp_;
	Vector2F hpPos_;
	int hpBaseImg_;
	int hpCircleImg_;
	int hpText_;

	bool isDrawMap_;
};