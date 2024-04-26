#include<DxLib.h>
#include"../../Common/Vector2.h"
#include"RoomBase.h"
#include "None.h"

//�p�����[�^�̐ݒ�
void None::SetParam(void)
{
	PazzleSize_ = { 1.0f,1.0f };
	StealthSize_ = { 0.0f,0.0f };
	type_ = RoomBase::TYPE::NONE;
	//�摜�̊i�[
	frameImg_ = LoadGraph("Data/Img/waku.png");
	if (frameImg_ == -1)
	{
		OutputDebugString("NONE�ɂĘg�ǂݍ��ݎ��s");
	}

	//�e�X�g�p
	//dbgColor_ = 0x8b4513;
	dbgColor_ = 0x000000;
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
	if (isCursor_
		&& type_==RoomBase::TYPE::NONE)
	{
		DrawGraph(pos.x_, pos.y_, frameImg_, true);
	}
}

//�����`�̋�̕⏕
void None::ChangeRole(RoomBase::TYPE type, int clr)
{
	type_ = type;
	dbgColor_ = clr;
}