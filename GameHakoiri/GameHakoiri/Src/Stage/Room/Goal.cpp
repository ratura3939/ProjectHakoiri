#include<DxLib.h>
#include"RoomBase.h"
#include "Goal.h"

Goal::Goal(int roomImg) :RoomBase(roomImg)
{

}
Goal::~Goal(void)
{

}
//�p�����[�^�̐ݒ�
void Goal::SetParam(void)
{
	PazzleSize_ = { 1.0f,1.0f };
	StealthSize_ = { 30.0f,30.0f };
	type_ = RoomBase::TYPE::GOAL;

	

	//�e�X�g�p
	dbgColor_ = 0x00ffff;
}