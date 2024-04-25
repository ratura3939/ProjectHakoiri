#include<DxLib.h>
#include"../../Common/Vector2.h"

#include"RoomBase.h"

//�R���X�g���N�^
//********************************************************
RoomBase::RoomBase(void)
{
	type_ = TYPE::NONE;
	pzlPos_ = { 0.0f,0.0f };
	mapPos_ = { 0.0f,0.0f };
	pieceSize_ = { 1.0f,1.0f };
	mapSize_ = { 1.0f,1.0f };
	isCursor_ = false;
}
//�f�X�g���N�^
//********************************************************
RoomBase::~RoomBase(void)
{

}

//������
//********************************************************
bool RoomBase::Init(void)
{
	pzlPos_ = { 0.0f,0.0f };
	mapPos_ = { 0.0f,0.0f };
	isCursor_ = false;

	//�e�����̐ݒ�
	SetParam();
	//��̑傫���̐ݒ�
	pieceSize_ = { PazzleSize_.x_ * static_cast<float>(UNIT_PAZZLE_SIZE_X),
		PazzleSize_.y_ * static_cast<float>(UNIT_PAZZLE_SIZE_Y) };

	//�}�b�v�̑傫���̐ݒ�
	mapSize_ = { StealthSize_.x_ * UNIT_STEALTH_SIZE_X,
		StealthSize_.y_ * UNIT_STEALTH_SIZE_Y };


	//�������������I�������̂�
	return true;
}
//�p�Y���V�[���ɂ����镔���̕`��
//********************************************************
void RoomBase::DrawPazzle(void)
{
	Vector2 pos = pzlPos_.ToVector2();
	DrawBox(pos.x_, pos.y_,
		pos.x_ + static_cast<int>(pieceSize_.x_),
		pos.y_ + static_cast<int>(pieceSize_.y_),
		dbgColor_, true);

	//�g�̕`��
	if (isCursor_)
	{
		DrawGraph(pos.x_, pos.y_, frameImg_, true);
	}
}
//�X�e���X�V�[���ɂ����镔���̕`��
//********************************************************
void RoomBase::DrawStealth(void)
{
	//�}�b�v�̕`��J�����Ƃ̊֌W���K�v
}
//���
//********************************************************
bool RoomBase::Release(void)
{
	//�摜�̊J��
	DeleteGraph(pieceImg_);

	//�������������I�������̂�
	return true;
}

//�p�Y�����W�̐ݒ�
//********************************************************
void RoomBase::SetPzlPos(Vector2F pos)
{
	pzlPos_ = pos;
}
//�}�b�v�̍��W�ݒ�
//********************************************************
void RoomBase::SetMapPos(Vector2F pos)
{
	mapPos_ = pos;
}

//�J�[�\���t���O�̐ݒ�
//********************************************************
void RoomBase::SetIsCursor(bool flag)
{
	isCursor_ = flag;
}

//�J�[�\���t���O�̕ԋp
bool RoomBase::GetIsCursor(void)
{
	return isCursor_;
}

//�������Ƃ̃p�����[�^�ݒ�
//********************************************************
void RoomBase::SetParam(void)
{
	//���̊֐��͔h���悲�Ƃ̂��̂Ȃ̂Ŋ֌W�Ȃ�
}