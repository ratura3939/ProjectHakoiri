#include<Windows.h>
#include<DxLib.h>
#include<cmath>
#include"../Utility/Utility.h"
#include"../Application.h"
#include"../Manager/SceneManager.h"
#include"../Manager/Camera.h"
#include"../Manager/ResourceManager.h"
#include "EnemyBase.h"

EnemyBase::EnemyBase(void)
{
	moveDir_ = Utility::VECTOR_ZERO;
	isMove_ = false;
	moveStartPos_ = { 0.0f,0.0f };
	isUse_ = false;
	moveLimit_ = 0;
	speed_ = 0.0f;
	state_ = VISION_STATE::MISSING;
	type_ = TYPE::MAX;
	visionImg_[0] = 0;
	visionImg_[1] = 0;
	drawVisionRot_ = 0.0f;
	colObject_ = { 0,0 };
}

EnemyBase::~EnemyBase(void)
{
}

void EnemyBase::Init(void)
{
	CharacterBase::Init();
	moveLimit_ = move_ * MOVE_UNIT;
	visionImg_[static_cast<int>(VISION_STATE::FIND)] =
		ResourceManager::GetInstance().Load(ResourceManager::SRC::VISION_FIND_IMG).handleId_;

	visionImg_[static_cast<int>(VISION_STATE::MISSING)] =
		ResourceManager::GetInstance().Load(ResourceManager::SRC::VISION_MISSING_IMG).handleId_;

	state_ = VISION_STATE::MISSING;

	//DecideDir();
}

void EnemyBase::SetParam(void)
{
}

void EnemyBase::Draw(void)
{
	auto cameraPos = SceneManager::GetInstance().GetCamera().GetPos();
	
	//視界の描画
	//円弧書きたい
	DrawVision(cameraPos);

	//三角形（仮）


	DrawRotaGraph(pos_.x - cameraPos.x,
		pos_.y - cameraPos.y,
		1.0f,
		Application::SIE * 180.0,
		img_[animIdx_],
		true,
		false);
	
}

//移動処理
void EnemyBase::Move(void)
{
	//動いてないとき方向決め
	if (!isMove_) { DecideDir(); }
	//動いている状態に
	SetIsMove(true);

	pos_ += Vector2F{ moveDir_.x * speed_,moveDir_.y * speed_ };

	auto diff = Utility::Distance(pos_.ToVector2(), moveStartPos_.ToVector2());

	if (static_cast<int>(diff) > moveLimit_) { SetIsMove(false); }
}

//視野内にplayerがいるか
bool EnemyBase::FindPlayer(Vector2F pPos) const
{
	//プレイヤーと敵の距離ベクトル
	auto diff = pPos - pos_;

	auto distance = std::pow(diff.x, 2.0f) + std::pow(diff.y, 2.0f);

	if (distance <= (std::pow(VIEW_RANGE, 2.0f)))	//視界（円）判定
	{
		auto rot = atan2(moveDir_.x, -moveDir_.y);

		//自分から見たplayerの角度を求める
		float rad = atan2(diff.x, -diff.y);
		//自分の視野角分の差分を合わせる。visionRotが360度計なのでRADに合わせる
		float viewRad = rad - rot;

		//求めた角度を360度計に
		float viewDeg = static_cast<float>(Utility::DegIn360(Utility::Rad2DegF(viewRad)));

		//視野内なら
		if (viewDeg <= VIEW_ANGLE || viewDeg >= (360.0f - VIEW_ANGLE))
		{
			return true;
		}
		
	}
	//視野外なので
	return false;
}

//動く方向決め
void EnemyBase::DecideDir(void)
{
	//スタートポジション設定
	moveStartPos_ = pos_;

	//方向決め
	dir_ = static_cast<DIR>(rand() % static_cast<int>(DIR::MAX));
	ResetAnim(dir_);

	auto moveDir = Utility::VECTOR_ZERO;
	//動く方向に応じた単位ベクトルと回転の角度の指定
	int rot = ROT_UNIT;

	switch (dir_)
	{
	case DIR::BOTTOM:
		moveDir = { 0.0f,1.0f,0.0f };
		rot *= ROT_BTM;
		break;
	case DIR::LEFT:
		moveDir = { -1.0f,0.0f,0.0f };
		rot *= ROT_LFT;
		break;
	case DIR::RIGHT:
		moveDir = { 1.0f,0.0f,0.0f };
		rot *= ROT_RGH;
		break;
	case DIR::TOP:
		moveDir = { 0.0f,-1.0f,0.0f };
		rot *= ROT_TOP;
		break;
	case DIR::BOTTOM_LEFT:
		moveDir = { -1.0f,1.0f,0.0f };
		rot *= ROT_BTM_LFT;
		break;
	case DIR::BOTTOM_RIGHT:
		moveDir = { 1.0f,1.0f,0.0f };
		rot *= ROT_BTM_RGH;
		break;
	case DIR::TOP_LEFT:
		moveDir = { -1.0f,-1.0f,0.0f };
		rot *= ROT_TOP_LFT;
		break;
	case DIR::TOP_RIGHT:
		moveDir = { 1.0f,-1.0f,0.0f };
		rot *= ROT_TOP_RGH;
		break;
	}

	//単位行列
	MATRIX mat = MGetIdent();
	//移動方向の回転
	moveDir_ = VTransform(moveDir, mat);

	drawVisionRot_ = static_cast<double>(rot);
}

//視界の描画
void EnemyBase::DrawVision(Vector2F cameraPos)
{
	//視界
	auto pos = GetCollisionPos();

	DrawRotaGraph3(pos.x - cameraPos.x,
		pos.y - cameraPos.y,
		VISION_SIZE_X / 2,
		VISION_SIZE_Y,
		1.0f,
		1.0f,
		drawVisionRot_*Utility::DEG2RAD,
		visionImg_[static_cast<int>(state_)],
		true,
		false,
		false);
}


void EnemyBase::SetIsMove(bool flag)
{
	isMove_ = flag;
}

void EnemyBase::SetVisionState(VISION_STATE state)
{
	state_ = state;
}

void EnemyBase::SetColObject(const Vector2 obj)
{
	colObject_ = obj;
}

void EnemyBase::ResetColObject(void)
{
	colObject_ = { 0,0 };
}

Vector2 EnemyBase::GetColObject(void) const
{
	return colObject_;
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