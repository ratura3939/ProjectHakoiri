#include<DxLib.h>
#include"../../Manager/ResourceManager.h"
#include"../../Common/Vector2.h"
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
	pazzleSize_ = { 1.0f,1.0f };
	type_ = RoomBase::TYPE::NONE;

}