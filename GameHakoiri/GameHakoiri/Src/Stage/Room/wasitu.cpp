#include<DxLib.h>
#include"RoomBase.h"
#include"Wasitu.h"

//�p�����[�^�̐ݒ�
void Wasitu::SetParam(void)
{
	PazzleSize_ = { 1.0f,1.0f };
	StealthSize_ = { 30.0f,30.0f };
	type_ = RoomBase::TYPE::WASITU;

	//�摜�̊i�[
	frameImg_ = LoadGraph("Data/Img/waku.png");
	if (frameImg_ == -1)
	{
		OutputDebugString("NONE�ɂĘg�ǂݍ��ݎ��s");
	}

	//�e�X�g�p
	dbgColor_ = 0x00ff00;
}