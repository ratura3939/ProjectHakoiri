#include<DxLib.h>
#include"RoomBase.h"
#include "Bath.h"

//�p�����[�^�̐ݒ�
void Bath::SetParam(void)
{
	PazzleSize_ = { 1.0f,1.0f };
	StealthSize_ = { 30.0f,30.0f };
	type_ = RoomBase::TYPE::BATH;

	

	//�e�X�g�p
	dbgColor_ = 0x4169e1;
}