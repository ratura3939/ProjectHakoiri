#include<DxLib.h>
#include"../../Manager/ResourceManager.h"
#include"RoomBase.h"
#include "Living.h"

Living::Living(int roomImg, int sizeX, int sizeY,
	std::vector<std::vector<int>> map, std::vector<std::vector<int>> obj,
	int* mapchip) 
	:RoomBase(roomImg, sizeX, sizeY, map, obj, mapchip)
{

}
Living::~Living(void)
{

}
//ƒpƒ‰ƒ[ƒ^‚Ìİ’è
void Living::SetParam(void)
{
	pazzleSize_ = { 1.0f,1.0f };
	type_ = RoomBase::TYPE::LIVING;

}