#include<DxLib.h>
#include"../../Manager/ResourceManager.h"
#include"RoomBase.h"
#include "Goal.h"

Goal::Goal(int roomImg) 
	:RoomBase(roomImg)
{

}
Goal::~Goal(void)
{

}
//�p�����[�^�̐ݒ�
void Goal::SetParam(void)
{
	pazzleSize_ = { 1.0f,1.0f };
	type_ = RoomBase::TYPE::GOAL;

	
}