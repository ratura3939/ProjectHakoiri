#include<DxLib.h>
#include"../Application.h"
#include"../Manager/ResourceManager.h"
#include"../Manager/InputManager.h"
#include"../Manager/SceneManager.h"
#include"../Manager/Camera.h"
#include "CharacterBase.h"

CharacterBase::CharacterBase(void)
{
	img_ = nullptr;
	pos_ = { 0,0 };
	dir_ = DIR::DOWN;
	move_ = 1.0f;
	animIdx_ = 0;
	prvAnimIdx_ = 0;
	animCnt_ = 0;
}

CharacterBase::~CharacterBase(void)
{
}

void CharacterBase::Init(void)
{
	SetParam();
	//�A�j���[�V�����������Ă�����ɏ�����
	animIdx_ = ANIM_NUM * static_cast<int>(dir_) + ANIM_CENTER;
	prvAnimIdx_ = ANIM_NUM * static_cast<int>(dir_);
	animCnt_ = 0;
}

void CharacterBase::Update(void)
{
	Move();
	Anim();
}

void CharacterBase::Draw(void)
{
	auto cameraPos = SceneManager::GetInstance().GetCamera().GetPos();

	DrawRotaGraph(pos_.x_ - cameraPos.x_,
		pos_.y_ - cameraPos.y_,
		1.0f,
		Application::SIE * 180.0 ,
		img_[animIdx_],
		true,
		false);
}

void CharacterBase::Release(void)
{
}

void CharacterBase::SetPos(Vector2F pos)
{
	pos_ = pos;
}

Vector2F CharacterBase::GetPos(void)const
{
	return pos_;
}

void CharacterBase::Move(void)
{
}

void CharacterBase::Anim(void)
{
	//�A�j���[�V�����J�E���^����
	animCnt_++;
	if (animCnt_ > ANIM_SWITCH_TIME)	//�؂�ւ��^�C�~���O
	{
		animCnt_ = 0;	//�J�E���^�̏�����
		//�O�̕`�悪������������
		if (prvAnimIdx_ == ANIM_NUM * static_cast<int>(dir_) + ANIM_CENTER)
		{
			prvAnimIdx_ = animIdx_;
			animIdx_ = ANIM_NUM * static_cast<int>(dir_) + ANIM_CENTER;
		}
		//�O�̕`�悪����������
		else if (prvAnimIdx_ == ANIM_NUM * static_cast<int>(dir_))
		{
			prvAnimIdx_ = animIdx_;
			animIdx_ = ANIM_NUM * static_cast<int>(dir_) + ANIM_RIGHT;
		}
		//�O�̕`�悪�E��������
		else if (prvAnimIdx_ == ANIM_NUM * static_cast<int>(dir_) + ANIM_RIGHT)
		{
			prvAnimIdx_ = animIdx_;
			animIdx_ = ANIM_NUM * static_cast<int>(dir_);
		}
	}
}

void CharacterBase::ResetAnim(DIR dir)
{
	//�����ϊ����A�j���[�V�������ύX
	animIdx_ = ANIM_NUM * static_cast<int>(dir) + ANIM_CENTER;
	prvAnimIdx_ = ANIM_NUM * static_cast<int>(dir);
}

void CharacterBase::SetDir(DIR dir)
{
	dir_ = dir;
}

CharacterBase::DIR CharacterBase::GetDir(void) const
{
	return dir_;
}

void CharacterBase::SetParam(void)
{
}
