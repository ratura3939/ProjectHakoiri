#include<DxLib.h>
#include"../../Manager/ResourceManager.h"
#include"RoomBase.h"
#include "Wall.h"

Wall::Wall(int roomImg) 
	:RoomBase(roomImg)
{

}
Wall::~Wall(void)
{

}

//�p�����[�^�̐ݒ�
void Wall::SetParam(void)
{
	pazzleSize_ = { 1.0f,1.0f };
	type_ = RoomBase::TYPE::WALL;

}