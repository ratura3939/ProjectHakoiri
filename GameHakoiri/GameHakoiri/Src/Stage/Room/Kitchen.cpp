#include<DxLib.h>
#include"../../Manager/ResourceManager.h"
#include"RoomBase.h"
#include "Kitchen.h"

Kitchen::Kitchen(int roomImg, int sizeX, int sizeY,
	std::vector<std::vector<int>>::iterator map, std::vector<std::vector<int>>::iterator obj,
	int* mapchip) 
	:RoomBase(roomImg, sizeX, sizeY, map, obj, mapchip)
{

}
Kitchen::~Kitchen(void)
{

}
//�p�����[�^�̐ݒ�
void Kitchen::SetParam(void)
{
	pazzleSize_ = { 1.0f,1.0f };
	type_ = RoomBase::TYPE::KITCHEN;

}