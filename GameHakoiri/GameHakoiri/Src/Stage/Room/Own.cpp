#include<DxLib.h>
#include"../../Manager/ResourceManager.h"
#include"RoomBase.h"
#include "Own.h"

Own::Own(int roomImg, int sizeX, int sizeY,
	std::vector<std::vector<int>> map, std::vector<std::vector<int>> obj,
	int* mapchip)
	:RoomBase(roomImg, sizeX, sizeY, map, obj, mapchip)
{

}
Own::~Own(void)
{

}
//ƒpƒ‰ƒ[ƒ^‚Ìİ’è
void Own::SetParam(void)
{
	pazzleSize_ = { 1.0f,1.0f };
	type_ = RoomBase::TYPE::OWN;

}