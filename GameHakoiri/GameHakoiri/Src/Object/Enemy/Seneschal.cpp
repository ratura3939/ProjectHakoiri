#include"../../Manager/ResourceManager.h"
#include "Seneschal.h"

void Seneschal::SetParam(void)
{
	img_ = ResourceManager::GetInstance().Load(ResourceManager::SRC::PLAYER_IMGS).handleIds_;
	dir_ = CharacterBase::DIR::BOTTOM;
	move_ = 4.0f;
	type_ = TYPE::SENESCHAL;
	SetIsUse(false);
}
