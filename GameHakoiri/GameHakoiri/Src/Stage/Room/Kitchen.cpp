#include<DxLib.h>
#include"../../Manager/ResourceManager.h"
#include"../../Manager/StageManager.h"
#include"RoomBase.h"
#include "Kitchen.h"

Kitchen::Kitchen(int roomImg, int sizeX, int sizeY,
	std::vector<std::vector<int>> map, std::vector<std::vector<int>> obj,
	int* mapchip) 
	:RoomBase(roomImg, sizeX, sizeY, map, obj, mapchip)
{

}
Kitchen::Kitchen(int roomImg)
	: RoomBase(roomImg)
{
}
Kitchen::~Kitchen(void)
{

}
//パラメータの設定
void Kitchen::SetParam(void)
{
	pazzleSize_ = { StageManager::OBLONG_PAZZLE_X,StageManager::OBLONG_PAZZLE_Y };
	type_ = TYPE::KITCHEN;
	isDrawRoom_ = true;
}