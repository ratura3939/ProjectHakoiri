#include<DxLib.h>
#include"../Application.h"
#include"../Utility/Utility.h"
#include"../Manager/ResourceManager.h"
#include"../Manager/InputManager.h"
#include"../Manager/SceneManager.h"
#include"../Manager/Camera.h"
#include "CharacterBase.h"

CharacterBase::CharacterBase(void)
{
	img_ = nullptr;
	pos_ = { 0,0 };
	prevPos_ = { 0,0 };
	dir_ = DIR::BOTTOM;
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
	//アニメーションを向いてる方向に初期化
	animIdx_ = ANIM_NUM * static_cast<int>(dir_) + ANIM_CENTER;
	prvAnimIdx_ = ANIM_NUM * static_cast<int>(dir_);
	animCnt_ = 0;
}

void CharacterBase::Update(void)
{
	SetPrevPos(pos_);
	Move();
	Anim();
}

void CharacterBase::Draw(void)
{
	auto cameraPos = SceneManager::GetInstance().GetCamera().GetPos();

	//キャラクター
	DrawRotaGraph(pos_.x - cameraPos.x,
		pos_.y - cameraPos.y,
		1.0f,
		0.0 * Utility::DEG2RAD,
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

void CharacterBase::SetPrevPos(const Vector2F pos)
{
	prevPos_ = pos;
}

Vector2F CharacterBase::GetPrevPos() const
{
	return prevPos_;
}



Vector2F CharacterBase::GetCollisionPos(void) const
{
	//現在の方向に応じた当たり判定を返す。
	Vector2F colPos = pos_;

	switch (dir_)
	{
	case CharacterBase::DIR::BOTTOM:
		colPos.y += CHARACTER_HALF_Y;
		break;
	case CharacterBase::DIR::LEFT:
		colPos.x -= CHARACTER_HALF_X;
		break;
	case CharacterBase::DIR::RIGHT:
		colPos.x += CHARACTER_HALF_X;
		break;
	case CharacterBase::DIR::TOP:
		colPos.y -= CHARACTER_HALF_Y;
		break;
	case CharacterBase::DIR::BOTTOM_LEFT:
		colPos += Vector2F{ -CHARACTER_HALF_X, CHARACTER_HALF_Y };
		break;
	case CharacterBase::DIR::BOTTOM_RIGHT:
		colPos += Vector2F{ CHARACTER_HALF_X, CHARACTER_HALF_Y };
		break;
	case CharacterBase::DIR::TOP_LEFT:
		colPos += Vector2F{ -CHARACTER_HALF_X, -CHARACTER_HALF_Y };
		break;
	case CharacterBase::DIR::TOP_RIGHT:
		colPos += Vector2F{ CHARACTER_HALF_X, -CHARACTER_HALF_Y };
		break;
	}
	return colPos;
}

void CharacterBase::Anim(void)
{
	//アニメーションカウンタ増加
	animCnt_++;
	if (animCnt_ > ANIM_SWITCH_TIME)	//切り替えタイミング
	{
		animCnt_ = 0;	//カウンタの初期化
		//前の描画が中央だった時
		if (prvAnimIdx_ == ANIM_NUM * static_cast<int>(dir_) + ANIM_CENTER)
		{
			prvAnimIdx_ = animIdx_;
			animIdx_ = ANIM_NUM * static_cast<int>(dir_) + ANIM_CENTER;
		}
		//前の描画が左だった時
		else if (prvAnimIdx_ == ANIM_NUM * static_cast<int>(dir_))
		{
			prvAnimIdx_ = animIdx_;
			animIdx_ = ANIM_NUM * static_cast<int>(dir_) + ANIM_RIGHT;
		}
		//前の描画が右だった時
		else if (prvAnimIdx_ == ANIM_NUM * static_cast<int>(dir_) + ANIM_RIGHT)
		{
			prvAnimIdx_ = animIdx_;
			animIdx_ = ANIM_NUM * static_cast<int>(dir_);
		}
	}
}



void CharacterBase::ResetAnim(DIR dir)
{
	//方向変換時アニメーションも変更
	animIdx_ = ANIM_NUM * static_cast<int>(dir) + ANIM_CENTER;
	prvAnimIdx_ = ANIM_NUM * static_cast<int>(dir);
}

void CharacterBase::Move(void)
{
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
