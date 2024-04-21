#include<DxLib.h>
#include<fstream>
#include<sstream>

#include"../Application.h"
#include"../Utility/Utility.h"
#include"Room/RoomBase.h"
#include"Room/Wasitu.h"
#include"Room/None.h"
#include"StageBase.h"

//コンストラクタ
//********************************************************
StageBase::StageBase(void)
{
	roomKey_ = "00";
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
	//
	SetParam();

	LoadPazzle();

	//テスト用

	size_t pzlY = pzlMap_.size();
	size_t pzlX = pzlX_.size();

	for (int y = 0; y < pzlY; y++)
	{
		for (int x = 0; x < pzlX; x++)
		{
			RoomBase* r = nullptr;

			switch (static_cast<RoomBase::TYPE>(pzlMap_[y][x]))
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

			//rooms_.push_back(r);	//配列内に格納
			CreateKey(y, x);
			roomMng_[roomKey_] = r;
		}
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

	size_t pzlY = pzlMap_.size();
	size_t pzlX = pzlX_.size();
	for (int y = 0; y < pzlY; y++)
	{
		for (int x = 0; x < pzlX; x++)
		{
			pos.x_ += static_cast<float>(RoomBase::UNIT_PAZZLE_SIZE_X);
			CreateKey(y, x);
			roomMng_[roomKey_]->SetPzlPos(pos);
			roomMng_[roomKey_]->DrawPazzle();;
		}
	}

	/*size_t piece = rooms_.size();
	for (int i = 0; i < piece; i++)
	{
		pos.x_ += static_cast<float>(RoomBase::UNIT_PAZZLE_SIZE_X);
		rooms_[i]->SetPzlPos(pos);
		rooms_[i]->DrawPazzle();
		DrawFormatString(x, y, 0xffffff, "配列%dを描画", i, true);
		y += 100;
	}*/

}
//解放
//********************************************************
bool StageBase::Release(void)
{
	//駒
	size_t pzlY = pzlMap_.size();
	size_t pzlX = pzlX_.size();
	for (int y = 0; y < pzlY; y++)
	{
		for (int x = 0; x < pzlX; x++)
		{
			CreateKey(y, x);
			roomMng_[roomKey_]->Release();
			delete roomMng_[roomKey_];
			roomMng_[roomKey_] = nullptr;
		}
	}

	//正しく処理が終了したので
	return true;
}
//盤面の読み込み
//********************************************************
void StageBase::LoadPazzle(void)
{
	std::string loadName;
	//loadName = Application::PATH_PAZZLE + testName_;

	//std::ifstream ifs = std::ifstream(loadName);
	std::ifstream ifs = std::ifstream("Data/Csv/Pazzle/test.csv");
	if (!ifs)
	{
		OutputDebugString("地上ステージのifstreamの準備失敗");
		return;
	}

	int chipNo = 0;
	//列の先頭から保存する
	int x = 0;
	int y = 0;
	int num = 0;

	//行格納用領域
	std::string line;
	while (getline(ifs, line))	//行がある間
	{
		//Split関数戻り値受け取り用
		std::vector<std::string> strSplit;

		strSplit = Utility::Split(line, ',');	//関数の呼び出し

		//一文字の情報
		std::string chipData;
		//分割したマップデータを格納する
		for (int x = 0; x < strSplit.size(); x++)
		{
			chipNo = stoi(strSplit[x]);
			num = chipNo;
			pzlX_.push_back(num);	//配列内に格納
		}
		pzlMap_.push_back(pzlX_);	//配列内に格納
	}

}

//ステージごとのパラメータ設定
//********************************************************
void StageBase::SetParam(void)
{
	//この関数は派生先ごとのものなので関係なし
}
//連想配列のキー生成
//********************************************************
void StageBase::CreateKey(int y, int x)
{
	roomKey_ = std::to_string(y) + std::to_string(x);
}