#include<DxLib.h>
#include"RoomBase.h"
#include "Own.h"

Own::Own(int roomImg) :RoomBase(roomImg)
{

}
Own::~Own(void)
{

}
//�p�����[�^�̐ݒ�
void Own::SetParam(void)
{
	PazzleSize_ = { 2.0f,1.0f };
	StealthSize_ = { 60.0f,30.0f };
	type_ = RoomBase::TYPE::OWN;


	//�e�X�g�p
	dbgColor_ = 0xff69b4;
}