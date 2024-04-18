#include<DxLib.h>
#include"../Application.h"
#include"Room/RoomBase.h"
#include"Room/Wasitu.h"
#include"Room/None.h"
#include"StageBase.h"

//コンストラクタ
//********************************************************
StageBase::StageBase(void)
{

}
//デストラクタ
//********************************************************
StageBase::~StageBase(void)
{

}

//初期化
//********************************************************
bool StageBase::Init(void)
{
	SetParam();

	//テスト用

	
	
	for (int i = 0; i < 5; i++)
	{
		RoomBase* r = nullptr;

		switch (static_cast<RoomBase::TYPE>(test_[i]))
		{
		case RoomBase::TYPE::NONE: //空きスペース
			r = new None();
			OutputDebugString("NONEのインスタンス生成\n");
			break;
		//case RoomBase::TYPE::OWN: //自室
		//	r = new Own();
		//	break;
		case RoomBase::TYPE::WASITU: //和室
			r = new Wasitu();
			OutputDebugString("和室のインスタンス生成\n");
			break;
		//case RoomBase::TYPE::LIVING: //居間
		//	r = new Living();
		//	break;
		//case RoomBase::TYPE::BATH: //風呂
		//	r = new Bath();
		//	break;
		//case RoomBase::TYPE::STORAGE: //物置
		//	r = new Storage();
		//	break;
		//case RoomBase::TYPE::KITCHEN: //台所
		//	r = new Kitchen();
		//	break;
		//case RoomBase::TYPE::ENTRANCE: //玄関
		//	r = new Entrance();
		//	break;
		}
		if (r->Init() == false)
		{
			OutputDebugString("部屋の初期化失敗\n");
		}

		rooms_.push_back(r);	//配列内に格納
	}
	//正しく処理が終了したので
	return true;
}
//更新
//********************************************************
void StageBase::Update(void)
{

}
//描画
//********************************************************
void StageBase::Draw(void)
{
	Vector2F pos{ static_cast<float>(Application::SCREEN_SIZE_X / 2),
	static_cast<float>(Application::SCREEN_SIZE_Y / 2) };
	int x = 0;
	int y = 0;

	size_t piece = rooms_.size();
	for (int i = 0; i < piece; i++)
	{
		pos.x_ += static_cast<float>(RoomBase::UNIT_PAZZLE_SIZE_X);
		rooms_[i]->SetPzlPos(pos);
		rooms_[i]->DrawPazzle();
		DrawFormatString(x, y, 0xffffff, "配列%dを描画", i, true);
		y += 100;
	}
}
//解放
//********************************************************
bool StageBase::Release(void)
{
	//駒
	size_t size = rooms_.size();
	for (int i = 0; i < size; i++)
	{
		rooms_[i]->Release();
		delete rooms_[i];
		rooms_[i] = nullptr;
	}
	//正しく処理が終了したので
	return true;
}

//ステージごとのパラメータ設定
//********************************************************
void StageBase::SetParam(void)
{
	//この関数は派生先ごとのものなので関係なし
}