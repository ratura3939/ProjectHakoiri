#include<DxLib.h>
#include"RoomBase.h"
#include "Storage.h"

//�p�����[�^�̐ݒ�
void Storage::SetParam(void)
{
	PazzleSize_ = { 1.0f,1.0f };
	StealthSize_ = { 30.0f,30.0f };
	type_ = RoomBase::TYPE::STORAGE;


	//�e�X�g�p
	dbgColor_ = 0x4b0082;
}