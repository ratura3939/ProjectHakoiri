#include<DxLib.h>
#include"../../Manager/ResourceManager.h"
#include"RoomBase.h"
#include "Wall.h"

Wall::Wall(int roomImg, int sizeX, int sizeY) :RoomBase(roomImg, sizeX, sizeY)
{

}
Wall::~Wall(void)
{

}

//ƒpƒ‰ƒ[ƒ^‚Ìİ’è
void Wall::SetParam(void)
{
	pazzleSize_ = { 1.0f,1.0f };
	type_ = RoomBase::TYPE::WALL;

}