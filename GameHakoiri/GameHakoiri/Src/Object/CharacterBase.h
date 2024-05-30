#pragma once

#include"../Common/Vector2F.h"

class CharacterBase
{
public:

	enum class DIR
	{
		DOWN,
		LEFT,
		RIGHT,
		UP,
		MAX
	};

	//�萔
	static constexpr float ANIM_SPEED = 5.0f;
	static constexpr int ANIM_NUM = 3;
	static constexpr int ANIM_TYPE = 4;
	static constexpr int ANIM_CENTER = 1;
	static constexpr int ANIM_RIGHT = 2;
	static constexpr int ANIM_SWITCH_TIME = 15;

	CharacterBase(void);
	~CharacterBase(void);

	void Init(void);
	virtual void Update(void);
	virtual void Draw(void);
	void Release(void);

	void SetPos(Vector2F pos);
	Vector2F GetPos(void)const;

private:
	void Anim(void);


protected:

	//�摜
	int* img_;
	//�ʒu
	Vector2F pos_;
	//����
	DIR dir_;
	//�ړ���
	float move_;
	//�A�j���[�V�����֌W
	int animIdx_;
	int prvAnimIdx_;
	int animCnt_;

	void ResetAnim(DIR dir);
	virtual void Move(void);	//�����̏���
	void SetDir(DIR dir);		//�����̕ϊ�
	DIR GetDir(void)const;		//�����̎擾
	virtual void SetParam(void);//�e�p�����[�^�ݒ�
};

