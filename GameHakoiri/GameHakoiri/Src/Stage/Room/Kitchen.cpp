#include<DxLib.h>
#include"RoomBase.h"
#include "Kitchen.h"

//�p�����[�^�̐ݒ�
void Kitchen::SetParam(void)
{
	PazzleSize_ = { 1.0f,2.0f };
	StealthSize_ = { 30.0f,60.0f };
	type_ = RoomBase::TYPE::KITCHEN;

	//�e�X�g�p
	dbgColor_ = 0xfaf0e6;
}