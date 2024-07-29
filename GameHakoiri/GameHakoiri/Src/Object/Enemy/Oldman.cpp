#include"../../Manager/ResourceManager.h"
#include "Oldman.h"

void Oldman::SetParam(void)
{
	img_ = ResourceManager::GetInstance().Load(ResourceManager::SRC::OLDMAN_IMGS).handleIds_;
	dir_ = CharacterBase::DIR::TOP;
	speed_ = 2.0f;
	move_ = 2.0f;
	type_ = TYPE::HOUSEMADE;
	SetIsUse(false);
}
