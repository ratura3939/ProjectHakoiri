#include<DxLib.h>
#include"../../Manager/ResourceManager.h"
#include"../../Manager/StageManager.h"
#include"RoomBase.h"
#include "None.h"

None::None(int roomImg)
	:RoomBase(roomImg)
{

}
None::~None(void)
{

}
//ƒpƒ‰ƒ[ƒ^‚Ìİ’è
void None::SetParam(void)
{
	pazzleSize_ = { StageManager::NOMAL_PAZZLE_X,StageManager::NOMAL_MAP_Y };
	type_ = RoomBase::TYPE::NONE;
}