#include<DxLib.h>
#include"../../Manager/ResourceManager.h"
#include"RoomBase.h"
#include "Own.h"

Own::Own(int roomImg, int sizeX, int sizeY) :RoomBase(roomImg, sizeX, sizeY)
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


	mapCsv_ = ResourceManager::GetInstance().Load(ResourceManager::SRC::OWN_MAP_CSV).csv_;
	objCsv_ = ResourceManager::GetInstance().Load(ResourceManager::SRC::OWN_OBJ_CSV).csv_;
}