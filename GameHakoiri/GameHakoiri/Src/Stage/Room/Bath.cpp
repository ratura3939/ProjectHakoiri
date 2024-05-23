#include<DxLib.h>
#include"../../Manager/ResourceManager.h"
#include"RoomBase.h"
#include "Bath.h"


Bath::Bath(int roomImg, int sizeX, int sizeY) :RoomBase(roomImg, sizeX, sizeY)
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


	mapCsv_ = ResourceManager::GetInstance().Load(ResourceManager::SRC::BATH_MAP_CSV).csv_;
	objCsv_ = ResourceManager::GetInstance().Load(ResourceManager::SRC::BATH_OBJ_CSV).csv_;
}