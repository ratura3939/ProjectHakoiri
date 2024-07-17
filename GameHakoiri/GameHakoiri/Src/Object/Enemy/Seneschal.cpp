#include"../../Manager/ResourceManager.h"
#include "Seneschal.h"

void Seneschal::SetParam(void)
{
	img_ = ResourceManager::GetInstance().Load(ResourceManager::SRC::PLAYER_IMGS).handleIds_;
	dir_ = CharacterBase::DIR::TOP;
	speed_ = 1.0f;
	move_ = 10.0f;
	type_ = TYPE::SENESCHAL;
	SetIsUse(false);
}
