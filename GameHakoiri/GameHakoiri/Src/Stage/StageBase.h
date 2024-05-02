#pragma once
#include<vector>
#include<list>
#include<fstream>
#include<sstream>
#include<string>
#include<map>
#include"../Common/Vector2.h"
#include"../Utility/Utility.h"

//StageBaseは各ステージの情報置き場という認識

class RoomBase;

class StageBase
{
public:

	StageBase(void);	//コンストラクタ
	virtual ~StageBase(void);	//デストラクタ

	virtual bool Init(void);	//初期化
	virtual void Update(void);	//更新
	virtual void PazzleDraw(void);	//描画
	virtual bool Release(void);	//解放

	void LoadPazzle(void);			//盤面の読み込み
	void CreateKey(int y, int x);	//連想配列のキー生成
	Vector2 GetNowCursorPos(void);	//現在のカーソルの位置を取得
	void SetCursor(Vector2 move, Utility::DIR dir);	//カーソルのセット yとxはカーソルの移動量
	void SetPiece(Vector2 move, Utility::DIR dir);	//駒の位置入れ替え yとxはカーソルの移動量

private:
	std::map<std::string, RoomBase*> roomMng_;	//部屋の情報一括管理
	std::string roomKey_;	//連想配列のキー


	std::vector<std::vector<int>>pzlMap_;	//パズルの置き場情報を数字で管理
	std::vector<int>pzlX_;
	std::map<std::string, Vector2F>pzlPos_;	//駒の描画位置管理

	int frame_;
	int frameImg_;
	int frameObImg_;
	int frameOb2Img_;
	

	bool CheckInstanceUp(int y, int x, RoomBase* r);	//長方形の２コマ目かを判断およびインスタンスの生成
	bool CheckInstanceLeft(int y, int x, RoomBase* r);

	RoomBase* GetSecondRoomInstance(RoomBase* r);		//長方形２コマ目のインスタンスの生成

	void DrawCursor(void);	//カーソルの描画

protected:

	virtual void SetParam(void);	//部屋ごとのパラメータ設定

	//テスト用
	//std::string testName_;
};