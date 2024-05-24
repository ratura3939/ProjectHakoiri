#include<DxLib.h>
#include"../../Manager/ResourceManager.h"
#include"RoomBase.h"
#include"Wasitu.h"

Wasitu::Wasitu(int roomImg, int sizeX, int sizeY,
	std::vector<std::vector<int>>::iterator map, std::vector<std::vector<int>>::iterator obj,
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
	pazzleSize_ = { 1.0f,1.0f };
	type_ = RoomBase::TYPE::WASITU;
}