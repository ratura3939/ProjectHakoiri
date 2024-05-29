#include<DxLib.h>
#include"../../Manager/ResourceManager.h"
#include"../../Manager/StageManager.h"
#include"RoomBase.h"
#include "Wall.h"

Wall::Wall(int roomImg) 
	:RoomBase(roomImg)
{

}
Wall::~Wall(void)
{

}

//ƒpƒ‰ƒ[ƒ^‚Ìİ’è
void Wall::SetParam(void)
{
	pazzleSize_ = { StageManager::NOMAL_PAZZLE_X,StageManager::NOMAL_MAP_Y };
	type_ = RoomBase::TYPE::WALL;
	isDrawRoom_ = true;
}