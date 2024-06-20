#pragma once
#include<vector>
#include<list>
#include<fstream>
#include<sstream>
#include<string>
#include<map>
#include<vector>
#include"../Common/Vector2.h"
#include"../Utility/Utility.h"
#include"../Scene/GameScene.h"
#include"../Manager/StageManager.h"
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

	//定数
	static constexpr int FRAME_INTERVAL = 15;
	static constexpr int STRING_TO_INT = 10;

	StageBase(std::vector<std::vector<int>>::iterator pzlIt, int pzlSizeX, int pzlSizeY,
		std::vector<std::vector<int>> map[], std::vector<std::vector<int>> obj[],
		int* roomImg,int* mapchip[]);	//コンストラクタ
	virtual ~StageBase(void);			//デストラクタ
		
	virtual bool Init(void);					//初期化
	virtual void Update(GameScene::MODE mode);	//更新
	virtual void Draw(GameScene::MODE mode);	//描画
	virtual bool Release(void);					//解放

	void CreateKey(int y, int x);	//連想配列のキー生成
	std::string GetKey(void)const;

	//パズルシーン
	Vector2 GetNowCursorPos(void);	//現在のカーソルの位置を取得
	void SetCursor(Vector2 move, Utility::DIR dir);	//カーソルのセット yとxはカーソルの移動量
	void SetPiece(Vector2 move, Utility::DIR dir);	//駒の位置入れ替え yとxはカーソルの移動量
	void SetFrameFlash(bool flag);					//枠点滅用
	void ResetPazzl(void);							//パズルのリセット

	//ステルスシーン
	bool InitStealth(void);				//ステルスシーン移行時の初期化
	void DrawObject(void);				//オブジェクト描画
	Position GetNowDrawMapSize(void);	//現在描画しているマップの最大サイズを取得
	bool IsMapObj(Vector2 pMapPos);		//座標にオブジェクトがあるかどうか
	bool IsMoveRoom(void);				//部屋の移動が可能だったかを返す
	int GetObjNum(Vector2 pMapPos);		//座標にあるオブジェクトが何かを返す
	int GetMapNum(Vector2 pMapPos);		//座標にあるマップチップがが何かを返す
	StageManager::MAPCHIP GetMapchipType(void);	//現在描画しているマップチップを返却
	RoomBase::ROOM_SHAPE GetNowShape(void);	//部屋の形を検索(鍵検索)
	bool CheckOneDownObject(Vector2 pMapPos);	//一つ下のマップチップがオブジェクトかを示す。
	void ChangeRoom(Vector2 pMapPos);			//部屋の切り替え

	StageManager::DOOR GetDoorPos(void)const;			//ドアの移動場所返却
	StageManager::DOOR_Y GetDoorPosSecond(void)const;	//同上
	bool IsSecondRoom(void)const;
	bool IsGoal(void)const;

private:
	std::map<std::string, RoomBase*> roomMng_;			//部屋の情報一括管理
	std::map<std::string, RoomBase::TYPE> resetRoom_;	//部屋のリセット用
	std::string roomKey_;								//連想配列のキー

	
	std::map<std::string, Position>pzlPos_;	//駒の描画位置管理

	CURSOR type_;		//カーソルが現在何を指しているかを保持
	int frame_[static_cast<int>(CURSOR::MAX)];	//カーソルフレームの画像を保持
	bool frameFlash_;							//カーソルを点滅させるかどうか
	int frameAnim_;								//カーソル点滅カウント用

	bool isMoveRoom_;		//部屋の移動が可能かを示す
	StageManager::DOOR door_;	//移動に使用するドアの位置
	bool isSecondRoom_;	//長方形の二マス目に出たか
	bool isGoal_;	//ゴールにたどり着いたか
	

	bool MovePiece(const Vector2 csr,
		const std::string bfr, const std::string aft);	//実際の移動処理　移動後のカーソル、移動前のKey、移動後のKey

	void MoveRoom(const Vector2 after, const std::string prvKey);


	//判定系
	bool CheckInstanceUp(int y, int x, RoomBase* r);	//長方形の２コマ目かを判断およびインスタンスの生成
	bool CheckInstanceLeft(int y, int x, RoomBase* r);
	RoomBase::ROOM_SHAPE GetRoomShape(std::string key);	//部屋の形を検索(鍵検索)
	RoomBase::ROOM_SHAPE GetRoomShape(RoomBase::TYPE type);	//部屋の形を検索(種類検索)
	bool IsDontMoveBlock(std::string key);	//移動不可なブロックかどうか

	Vector2 MoveLeftOrRight(const StageManager::DOOR_X door);	//左右の移動量を返却
	StageManager::DOOR SearchDoor(const Vector2 pMapPos);		//ドアの検索
	StageManager::DOOR SplitRoom(const Vector2 pMapPos,const Vector2 size,const Vector2 startPos);	//部屋の分割

	

	//Get&Set
	RoomBase* GetSecondRoomInstance(RoomBase* r);		//長方形２コマ目のインスタンスの生成
	void SetIsMoveRoom(bool flag);	//フラグのセット
	void SetIsSecondRoom(bool flag);	//フラグのセット
	void SetIsGoal(bool flag);

	//長方形２コマ目かを判断するために必要なインスタンスを生成する
	RoomBase* CreateInstance4Confirmation(RoomBase::TYPE type);

	void SetCursorType(CURSOR type);
	StageManager::DOOR_Y GetDoorSpare(void);			//縦長用の追加判定のドア検知を返却
	
	
	//更新
	void UpdateStealth(void);

	//描画
	void DrawPazzle(void);	//パズル
	void DrawCursor(void);	//カーソル
	void DrawStealth(void);	//ステルス

	void LoadImgs(void);	//画像読み込み

protected:
	////各ステージのファイル名
	//std::string file_Pzl;
	//std::string file_Map;

	std::vector<std::vector<int>>::iterator pzlCsv_;
	Vector2 size_;
	virtual void SetParam(void);	//部屋ごとのパラメータ設定

	std::vector<std::vector<int>>* mapCsv_;	//マップのCsvデータの先頭アドレス格納
	std::vector<std::vector<int>>* objCsv_;	//オブジェクトのCsvデータの先頭アドレス格納
	int* roomImg_;		//パズルシーンの駒画像受け取り
	int** mapchip_;		//ステルスシーンのマップチップ受け取り

	StageManager::DOOR_Y doorSpare_;	//ドア判定縦長用(正方形と横長はNONE)
};