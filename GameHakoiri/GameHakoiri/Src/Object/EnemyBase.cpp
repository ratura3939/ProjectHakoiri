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
	
	//‹ŠE‚Ì•`‰æ
	//‰~ŒÊ‘‚«‚½‚¢
	Pie(nullptr, 1, 2, 3, 1, 2, 3, 3, 3);

	//OŠpŒ`i‰¼j



	DrawRotaGraph(pos_.x_ - cameraPos.x_,
		pos_.y_ - cameraPos.y_,
		1.0f,
		Application::SIE * 180.0,
		img_[animIdx_],
		true,
		false);
	
}

void EnemyBase::Move(void)
{
}
