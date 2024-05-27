#include<DxLib.h>
#include"../../Manager/ResourceManager.h"
#include"RoomBase.h"
#include "Entrance.h"

Entrance::Entrance(int roomImg, int sizeX, int sizeY,
	std::vector<std::vector<int>> map, std::vector<std::vector<int>> obj,
	int* mapchip) 
	:RoomBase(roomImg, sizeX, sizeY, map, obj, mapchip)
{

}
Entrance::~Entrance(void)
{

}
//ƒpƒ‰ƒ[ƒ^‚Ìİ’è
void Entrance::SetParam(void)
{
	pazzleSize_ = { 1.0f,1.0f };
	type_ = RoomBase::TYPE::ENTRANCE;

}