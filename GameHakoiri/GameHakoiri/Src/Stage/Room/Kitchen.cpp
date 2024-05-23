#include<DxLib.h>
#include"../../Manager/ResourceManager.h"
#include"RoomBase.h"
#include "Kitchen.h"

Kitchen::Kitchen(int roomImg, int sizeX, int sizeY) :RoomBase(roomImg, sizeX, sizeY)
{

}
Kitchen::~Kitchen(void)
{

}
//ƒpƒ‰ƒ[ƒ^‚Ìİ’è
void Kitchen::SetParam(void)
{
	pazzleSize_ = { 1.0f,1.0f };
	type_ = RoomBase::TYPE::KITCHEN;


	mapCsv_ = ResourceManager::GetInstance().Load(ResourceManager::SRC::KITCHEN_MAP_CSV).csv_;
	objCsv_ = ResourceManager::GetInstance().Load(ResourceManager::SRC::KITCHEN_OBJ_CSV).csv_;
}