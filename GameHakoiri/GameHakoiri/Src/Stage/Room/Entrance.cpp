#include<DxLib.h>
#include"../../Manager/ResourceManager.h"
#include"../../Manager/StageManager.h"
#include"RoomBase.h"
#include "Entrance.h"

Entrance::Entrance(int roomImg, int sizeX, int sizeY,
	std::vector<std::vector<int>> map, std::vector<std::vector<int>> obj,
	int* mapchip) 
	:RoomBase(roomImg, sizeX, sizeY, map, obj, mapchip)
{

}
Entrance::Entrance(int roomImg)
	: RoomBase(roomImg)
{
}
Entrance::~Entrance(void)
{

}
//ƒpƒ‰ƒ[ƒ^‚Ìİ’è
void Entrance::SetParam(void)
{
	pazzleSize_ = { StageManager::OBLONG_2_PAZZLE_X,StageManager::OBLONG_2_PAZZLE_Y };
	type_ = RoomBase::TYPE::ENTRANCE;
	isDrawRoom_ = true;
}