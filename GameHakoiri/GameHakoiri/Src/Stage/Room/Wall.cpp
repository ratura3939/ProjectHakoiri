#include<DxLib.h>
#include"RoomBase.h"
#include "Wall.h"

//�p�����[�^�̐ݒ�
void Wall::SetParam(void)
{
	PazzleSize_ = { 1.0f,1.0f };
	StealthSize_ = { 30.0f,30.0f };
	type_ = RoomBase::TYPE::WALL;


	//�e�X�g�p
	dbgColor_ = 0x8b4513;
}