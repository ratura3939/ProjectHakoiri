#include<DxLib.h>
#include"../../Manager/ResourceManager.h"
#include"RoomBase.h"
#include "Bath.h"


Bath::Bath(int roomImg, int sizeX, int sizeY,
	std::vector<std::vector<int>> map, std::vector<std::vector<int>> obj,
	int* mapchip)
	:RoomBase(roomImg, sizeX, sizeY, map, obj, mapchip)
{

}
Bath::~Bath(void)
{

}
//ƒpƒ‰ƒ[ƒ^‚Ìİ’è
void Bath::SetParam(void)
{
	pazzleSize_ = { 1.0f,1.0f };
	type_ = RoomBase::TYPE::BATH;
}