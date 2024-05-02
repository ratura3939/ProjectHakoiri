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

#pragma region �`��

void RoomBase::Draw(void)
{
	DrawPazzle();
}
#pragma endregion


//�p�Y���V�[���ɂ����镔���̕`��
//********************************************************
void RoomBase::DrawPazzle(void)
{
	Vector2 pos = pzlPos_.ToVector2();
	DrawBox(pos.x_, pos.y_,
		pos.x_ + static_cast<int>(pieceSize_.x_),
		pos.y_ + static_cast<int>(pieceSize_.y_),
		dbgColor_, true);
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

#pragma region �����̎�ނ�SetGet

void RoomBase::SetRoomType(TYPE type)
{
	type_ = type;
}

RoomBase::TYPE RoomBase::GetRoomType(void)
{
	return type_;
}
#pragma endregion



#pragma region �p�Y����SetGet

void RoomBase::SetPzlPos(Vector2F pos)
{
	pzlPos_ = pos;
}
Vector2F RoomBase::GetPzlPos(void)
{
	return pzlPos_;
}
#pragma endregion

#pragma region �}�b�v��SetGet

void RoomBase::SetMapPos(Vector2F pos)
{
	mapPos_ = pos;
}

Vector2F RoomBase::GetMapPos(void)
{
	return mapPos_;
}
#pragma endregion

#pragma region �J�[�\����SetGet

void RoomBase::SetIsCursor(bool flag)
{
	isCursor_ = flag;
}

bool RoomBase::GetIsCursor(void)
{
	return isCursor_;
}
#pragma endregion





#pragma region �������������

void RoomBase::SetColor(int col)
{
	dbgColor_ = col;
}
int RoomBase::GetColor(void)
{
	return dbgColor_;
}
#pragma endregion


//�������Ƃ̃p�����[�^�ݒ�
//********************************************************
void RoomBase::SetParam(void)
{
	//���̊֐��͔h���悲�Ƃ̂��̂Ȃ̂Ŋ֌W�Ȃ�
}