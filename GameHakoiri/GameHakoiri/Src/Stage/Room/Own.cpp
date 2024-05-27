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
Own::Own(int roomImg)
	: RoomBase(roomImg)
{
}
Own::~Own(void)
{

}
//ÉpÉâÉÅÅ[É^ÇÃê›íË
void Own::SetParam(void)
{
	pazzleSize_ = { 1.0f,1.0f };
	type_ = RoomBase::TYPE::OWN;
	isDrawRoom_ = true;
}