#include<DxLib.h>
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