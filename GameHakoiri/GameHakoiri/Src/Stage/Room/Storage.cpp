#include<DxLib.h>
#include"../../Manager/ResourceManager.h"
#include"RoomBase.h"
#include "Storage.h"

Storage::Storage(int roomImg, int sizeX, int sizeY) :RoomBase(roomImg, sizeX, sizeY)
{

}
Storage::~Storage(void)
{

}
//ÉpÉâÉÅÅ[É^ÇÃê›íË
void Storage::SetParam(void)
{
	pazzleSize_ = { 1.0f,1.0f };
	type_ = RoomBase::TYPE::STORAGE;

	mapCsv_ = ResourceManager::GetInstance().Load(ResourceManager::SRC::STRAGE_MAP_CSV).csv_;
	objCsv_ = ResourceManager::GetInstance().Load(ResourceManager::SRC::STRAGE_OBJ_CSV).csv_;
}