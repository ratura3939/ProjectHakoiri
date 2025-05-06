#include"../../Manager/ResourceManager.h"
#include "Seneschal.h"

void Seneschal::SetParam(void)
{
	img_ = ResourceManager::GetInstance().Load(ResourceManager::SRC::SENESCHAI_IMGS).handleIds_;
	dir_ = CharacterBase::DIR::TOP;
	speed_ = SPEED;
	move_ = MOVE_POW;
	type_ = TYPE::SENESCHAL;
	SetIsUse(false);
}
