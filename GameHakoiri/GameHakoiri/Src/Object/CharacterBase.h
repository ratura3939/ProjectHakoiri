#pragma once

#include"../Common/Vector2F.h"

class CharacterBase
{
public:

	//8����
	enum class DIR
	{
		BOTTOM,
		LEFT,
		RIGHT,
		TOP,
		BOTTOM_LEFT,
		BOTTOM_RIGHT,
		TOP_LEFT,
		TOP_RIGHT,
		MAX
	};

	//�萔
	static constexpr float ANIM_SPEED = 5.0f;
	static constexpr int ANIM_NUM = 3;
	static constexpr int ANIM_TYPE = 4;
	static constexpr int ANIM_CENTER = 1;
	static constexpr int ANIM_RIGHT = 2;
	static constexpr int ANIM_SWITCH_TIME = 15;

	static constexpr int CHARACTER_SIZE_X = 32;
	static constexpr int CHARACTER_HALF_X = CHARACTER_SIZE_X / 2;
	static constexpr int CHARACTER_SIZE_Y = 32;
	static constexpr int CHARACTER_HALF_Y = CHARACTER_SIZE_Y / 2;

	static constexpr int VISION_SIZE_X = 454;
	static constexpr int VISION_SIZE_Y = 310;

	static constexpr int ROT_UNIT = 45;

	static constexpr int ROT_TOP=		0;
	static constexpr int ROT_TOP_RGH =	1;
	static constexpr int ROT_RGH =		2;
	static constexpr int ROT_BTM_RGH =	3;
	static constexpr int ROT_BTM =		4;
	static constexpr int ROT_BTM_LFT =	5;
	static constexpr int ROT_LFT =		6;
	static constexpr int ROT_TOP_LFT =	7;

	CharacterBase(void);
	virtual ~CharacterBase(void);

	void Init(void);
	virtual void Update(void);
	virtual void Draw(void);
	void Release(void);

	void SetPos(Position pos);
	Position GetPos(void)const;
	Position GetCollisionPos(void)const;

private:
	void Anim(void);
	

protected:

	//�摜
	int* img_;

	int visionImg_;
	double visionRot_;

	//�ʒu
	Position pos_;
	//����
	DIR dir_;
	//�ړ���
	float move_;
	//�A�j���[�V�����֌W
	int animIdx_;
	int prvAnimIdx_;
	int animCnt_;

	void ResetAnim(DIR dir);
	virtual void Move(void) = 0;	//�����̏���
	void SetDir(DIR dir);		//�����̕ϊ�

	DIR GetDir(void)const;
	virtual void SetParam(void) = 0;//�e�p�����[�^�ݒ�
};

