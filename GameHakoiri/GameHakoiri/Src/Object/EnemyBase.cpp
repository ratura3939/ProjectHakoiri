#include<Windows.h>
#include<DxLib.h>
#include"../Application.h"
#include"../Manager/SceneManager.h"
#include"../Manager/Camera.h"
#include "EnemyBase.h"

EnemyBase::EnemyBase(void)
{
}

EnemyBase::~EnemyBase(void)
{
}

void EnemyBase::SetParam(void)
{
}

void EnemyBase::Draw(void)
{
	auto cameraPos = SceneManager::GetInstance().GetCamera().GetPos();
	
	//éãäEÇÃï`âÊ
	//â~å èëÇ´ÇΩÇ¢
	DrawVision(cameraPos);

	//éOäpå`ÅiâºÅj


	DrawRotaGraph(pos_.x - cameraPos.x,
		pos_.y - cameraPos.y,
		1.0f,
		Application::SIE * 180.0,
		img_[animIdx_],
		true,
		false);
	
}

void EnemyBase::Move(void)
{

}

void EnemyBase::SetIsUse(bool flag)
{
	isUse_ = flag;
}

bool EnemyBase::IsUse(void)
{
	return isUse_;
}

EnemyBase::TYPE EnemyBase::GetType(void)
{
	return type_;
}

void EnemyBase::DrawVision(Vector2F cameraPos)
{
	//éãäE
	auto pos = GetCollisionPos();

	//íËêîâªÇµÇÊÇ§
	int rot = ROT_UNIT;
	switch (dir_)
	{
	case DIR::BOTTOM:
		rot *= ROT_BTM;
		break;
	case DIR::LEFT:
		rot *= ROT_LFT;
		break;
	case DIR::RIGHT:
		rot *= ROT_RGH;
		break;
	case DIR::TOP:
		rot *= ROT_TOP;
		break;
	case DIR::BOTTOM_LEFT:
		rot *= ROT_BTM_LFT;
		break;
	case DIR::BOTTOM_RIGHT:
		rot *= ROT_BTM_RGH;
		break;
	case DIR::TOP_LEFT:
		rot *= ROT_TOP_LFT;
		break;
	case DIR::TOP_RIGHT:
		rot *= ROT_TOP_RGH;
		break;
	}

	visionRot_ = static_cast<double>(rot);


	DrawRotaGraph3(pos.x - cameraPos.x,
		pos.y - cameraPos.y,
		VISION_SIZE_X / 2,
		VISION_SIZE_Y,
		1.0f,
		1.0f,
		visionRot_ * Application::SIE / 180.0,
		visionImg_,
		true,
		false,
		false);
}
