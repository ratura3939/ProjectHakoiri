#include<DxLib.h>
#include"../../Manager/ResourceManager.h"
#include"../../Manager/StageManager.h"
#include"RoomBase.h"
#include"Wasitu.h"

Wasitu::Wasitu(int roomImg, int sizeX, int sizeY,
	std::vector<std::vector<int>> map, std::vector<std::vector<int>> obj,
	int* mapchip)
	:RoomBase(roomImg, sizeX, sizeY, map, obj, mapchip)
{

}
Wasitu::~Wasitu(void)
{

}

//ƒpƒ‰ƒ[ƒ^‚Ìİ’è
void Wasitu::SetParam(void)
{
	pazzleSize_ = { StageManager::NOMAL_PAZZLE_X,StageManager::NOMAL_MAP_Y };
	type_ = TYPE::WASITU;
	isDrawRoom_ = true;
}