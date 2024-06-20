#include<DxLib.h>
#include"../../Manager/ResourceManager.h"
#include"../../Manager/StageManager.h"
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
	pazzleSize_ = { StageManager::OBLONG_2_PAZZLE_X,StageManager::OBLONG_2_PAZZLE_Y };
	type_ = TYPE::OWN;
	isDrawRoom_ = true;
}