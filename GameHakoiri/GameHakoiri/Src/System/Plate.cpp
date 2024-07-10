#include<DxLib.h>
#include"../Manager/ResourceManager.h"
#include"../Manager/SceneManager.h"
#include"../Manager/InputManager.h"
#include"../Utility/Utility.h"
#include "Plate.h"

Plate::Plate(void)
{
	isFinishAnim_ = false;
	plateImg_[0] = 0;
	plateImg_[1] = 0;
	frameImg_ = 0;
}

Plate::~Plate(void)
{
}

void Plate::Init(void)
{
	plateImg_[static_cast<int>(TYPE::SELECT)] = 
		ResourceManager::GetInstance().Load(ResourceManager::SRC::PLATE_SELECT_IMG).handleId_;
	plateImg_[static_cast<int>(TYPE::CHECK)] = 
		ResourceManager::GetInstance().Load(ResourceManager::SRC::PLATE_CHECK_IMG).handleId_;
	frameImg_ = ResourceManager::GetInstance().Load(ResourceManager::SRC::FRAME_OBLONG_2_IMG).handleId_;


	speed_ = 8.0f;
}

bool Plate::Update(TYPE type)
{
	switch (state_)
	{
	case Plate::STATE::GO:
		UpdateGo();
		break;
	case Plate::STATE::STOP:
		if (UpdateStop(type))
		{
			return true;
		}
		break;
	case Plate::STATE::BACK:
		UpdateBack();
		break;
	}
    return false;
}

void Plate::UpdateGo(void)
{
}

bool Plate::UpdateStop(TYPE type)
{

	return false;
}

void Plate::UpdateBack(void)
{
}

void Plate::Draw(TYPE type)
{
	DrawRotaGraph(platePos_.x, platePos_.y,
		1.0f,
		0.0f * Utility::DEG2RAD,
		plateImg_[static_cast<int>(type)],
		true,
		false);
}

void Plate::Release(void)
{
	
}

Plate::INPUT Plate::KeyboardContoroller(void)
{
	INPUT ret = INPUT::NONE;

	return ret;
}

Plate::INPUT Plate::GamePadController(void)
{
	INPUT ret = INPUT::NONE;

	return ret;
}
