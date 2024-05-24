#include<DxLib.h>
#include"../../Manager/ResourceManager.h"
#include"RoomBase.h"
#include "Wall.h"

Wall::Wall(int roomImg, int sizeX, int sizeY,
	std::vector<std::vector<int>>::iterator map, std::vector<std::vector<int>>::iterator obj,
	int* mapchip) 
	:RoomBase(roomImg, sizeX, sizeY, map, obj, mapchip)
{

}
Wall::~Wall(void)
{

}

//ÉpÉâÉÅÅ[É^ÇÃê›íË
void Wall::SetParam(void)
{
	pazzleSize_ = { 1.0f,1.0f };
	type_ = RoomBase::TYPE::WALL;

}