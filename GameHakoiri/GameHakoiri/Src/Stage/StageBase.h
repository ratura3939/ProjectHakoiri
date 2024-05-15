#pragma once
#include<vector>
#include<list>
#include<fstream>
#include<sstream>
#include<string>
#include<map>
#include"../Common/Vector2.h"
#include"../Utility/Utility.h"
#include"../Scene/GameScene.h"
#include"Room/RoomBase.h"

//StageBaseは各ステージの情報置き場という認識

class RoomBase;

class StageBase
{
public:

	enum class CURSOR
	{
		NORMAL,
		OBLONG,
		OBLONG_2,
		MAX
	};

	static constexpr int FRAME_INTERVAL = 15;

	StageBase(void);	//コンストラクタ
	virtual ~StageBase(void);	//デストラクタ

	virtual bool Init(void);	//初期化
	virtual void Update(GameScene::MODE mode);	//更新
	virtual void Draw(GameScene::MODE mode);	//描画
	virtual bool Release(void);	//解放

	void LoadPazzle(void);			//盤面の読み込み
	void CreateKey(int y, int x);	//連想配列のキー生成
	Vector2 GetNowCursorPos(void);	//現在のカーソルの位置を取得
	void SetCursor(Vector2 move, Utility::DIR dir);	//カーソルのセット yとxはカーソルの移動量
	void SetPiece(Vector2 move, Utility::DIR dir);	//駒の位置入れ替え yとxはカーソルの移動量
	void SetFrameFlash(bool flag);	//枠点滅用

	void ResetPazzl(void);	//パズルのリセット

private:
	std::map<std::string, RoomBase*> roomMng_;	//部屋の情報一括管理
	std::map<std::string, RoomBase::TYPE> resetRoom_;//部屋のリセット用
	std::string roomKey_;	//連想配列のキー


	std::vector<std::vector<int>>pzlMap_;	//パズルの置き場情報を数字で管理
	std::vector<int>pzlX_;
	std::map<std::string, Vector2F>pzlPos_;	//駒の描画位置管理

	CURSOR type_;
	int frame_[static_cast<int>(CURSOR::MAX)];
	bool frameFlash_;
	int frameAnim_;
	
	bool MovePiece(const Vector2 csr,
		const std::string bfr, const std::string aft);	//実際の移動処理　移動後のカーソル、移動前のKey、移動後のKey

	//判定系
	bool CheckInstanceUp(int y, int x, RoomBase* r);	//長方形の２コマ目かを判断およびインスタンスの生成
	bool CheckInstanceLeft(int y, int x, RoomBase* r);
	bool IsOblong(std::string key);	//今いる場所が長方形か
	bool IsOblong(RoomBase::TYPE type);	//今いる場所が長方形か
	bool IsDontMoveBlock(std::string key);	//移動不可なブロックかどうか

	//Get&Set
	RoomBase* GetSecondRoomInstance(RoomBase* r);		//長方形２コマ目のインスタンスの生成
	void SetCursorType(CURSOR type);
	
	//更新
	void UpdateStealth(void);

	//描画
	void DrawPazzle(void);	//パズル
	void DrawCursor(void);	//カーソル
	void DrawStealth(void);	//ステルス

	void LoadImgs(void);

protected:
	//各ステージのファイル名
	std::string file_Pzl;
	std::string file_Map;


	virtual void SetParam(void);	//部屋ごとのパラメータ設定
};