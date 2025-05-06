#pragma once
#include<vector>
#include<list>
#include<fstream>
#include<sstream>
#include<string>
#include<map>
#include<memory>
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

	/// <summary>
	/// 配列をしていする指定数を取得
	/// </summary>
	/// <returns>配列指定数</returns>
	std::string GetKey(void)const;

#pragma region パズル関連

	/// <summary>
	/// カーソル位置取得
	/// </summary>
	/// <returns>カーソル位置(配列指定数)</returns>
	const Vector2 GetNowCursorPos(void);

	/// <summary>
	/// カーソル移動
	/// </summary>
	/// <param name="move">移動量</param>
	/// <param name="dir">方向</param>
	void SetCursor(const Vector2 move, const Utility::DIR dir);

	/// <summary>
	/// 駒の移動
	/// </summary>
	/// <param name="move">移動量</param>
	/// <param name="dir">方向</param>
	void SetPiece(const Vector2 move, const Utility::DIR dir);

	/// <summary>
	/// 点滅させるかどうか
	/// </summary>
	/// <param name="flag">true=させる/false=させない</param>
	void SetFrameFlash(const bool flag);

	/// <summary>
	/// リセット
	/// </summary>
	void ResetPazzl(void);

	/// <summary>
	/// 駒入れ替え(初期位置)
	/// </summary>
	/// <param name="nowKey">現在の配列位置(string)</param>
	void SwapPazzle(const std::string nowKey);

	/// <summary>
	/// 周囲①マスに駒があるか（ゴールできるかの判定のみに使用）
	/// </summary>
	/// <param name="nowPos">ゴール位置</param>
	/// <returns>true=ある/false=ない</returns>
	const bool CheckAroundRoomAnything(const Vector2 nowPos);

	/// <summary>
	/// ゴール可能か
	/// </summary>
	/// <returns>true=可能/fale=不可能</returns>
	const bool CanGoal(void);
#pragma endregion
	
#pragma region ステルス関連
	/// <summary>
	/// ステルス時の初期化
	/// </summary>
	/// <returns>true=成功/false=失敗</returns>
	bool InitStealth(void);

	/// <summary>
	/// オブジェクトの描画
	/// </summary>
	void DrawObject(void);

	/// <summary>
	/// 現在描画中のマップサイズ取得
	/// </summary>
	/// <returns>サイズ{float,float}</returns>
	Vector2F GetNowDrawMapSize(void);

	/// <summary>
	/// オブジェクトがあるか
	/// </summary>
	/// <param name="pMapPos">判定元の座標</param>
	/// <returns>true=ある/false=ない</returns>
	const bool IsMapObj(const Vector2 pMapPos);

	/// <summary>
	/// 部屋の移動が可能か
	/// </summary>
	/// <returns>true=可能/false=不可能</returns>
	const bool IsMoveRoom(void)const;

	/// <summary>
	/// オブジェクトの種類を取得
	/// </summary>
	/// <param name="pMapPos">判定元の座標</param>
	/// <returns>オブジェクトの種類(int)</returns>
	const int GetObjNum(const Vector2 pMapPos);

	/// <summary>
	/// 現在の床を得る
	/// </summary>
	/// <param name="pMapPos">判定元の座標</param>
	/// <returns>現在のマップ情報(通常or移動マス)</returns>
	const int GetMapNum(const Vector2 pMapPos);	

	/// <summary>
	/// 現在描画しているマップの種類
	/// </summary>
	/// <returns>マップの種類</returns>
	const StageManager::MAPCHIP GetMapchipType(void);

	/// <summary>
	/// 部屋の形を取得
	/// </summary>
	/// <returns>部屋の形(正方形or長方形)</returns>
	const RoomBase::ROOM_SHAPE GetNowShape(void);

	/// <summary>
	/// 下にオブジェクトがあるか(縦長の障害物用)
	/// </summary>
	/// <param name="pMapPos">判定元の座標</param>
	/// <returns>true=ある/false=ない</returns>
	const bool CheckOneDownObject(const Vector2 pMapPos);

	/// <summary>
	/// 部屋の変更
	/// </summary>
	/// <param name="pMapPos">プレイヤー位置</param>
	void ChangeRoom(const Vector2 pMapPos);

	/// <summary>
	/// ドアの位置取得
	/// </summary>
	/// <returns>ドアの位置取得(ドアがどの方向にあったか)</returns>
	const StageManager::DOOR GetDoorPos(void)const;			//ドアの移動場所返却

	/// <summary>
	/// GetDoorPos補足用
	/// </summary>
	/// <returns>ドアの位置取得(ドアがどの方向にあったか)</returns>
	const StageManager::DOOR_Y GetDoorPosSecond(void)const;

	/// <summary>
	/// 長方形のにマス目(非本体)かどうか
	/// </summary>
	/// <returns>true=非本体/false=本体</returns>
	const bool IsSecondRoom(void)const;

	/// <summary>
	/// ゴールしているか
	/// </summary>
	/// <returns>true=している/false=していない</returns>
	const bool IsGoal(void)const;
#pragma endregion

private:
	std::map<std::string, std::unique_ptr<RoomBase>> roomMng_;			//部屋の情報一括管理
	std::map<std::string, RoomBase::TYPE> resetRoom_;	//部屋のリセット用
	std::map<std::string, bool> resetRoomClone_;		//部屋のリセット用
	std::string roomKey_;								//連想配列のキー
	Vector2 goalPos_;		//ゴールの位置記録

	
	std::map<std::string, Vector2F>pzlPos_;	//駒の描画位置管理

	CURSOR type_;		//カーソルが現在何を指しているかを保持
	int frame_[static_cast<int>(CURSOR::MAX)];	//カーソルフレームの画像を保持
	bool frameFlash_;							//カーソルを点滅させるかどうか
	int frameAnim_;								//カーソル点滅カウント用

	bool isMoveRoom_;		//部屋の移動が可能かを示す
	StageManager::DOOR door_;	//移動に使用するドアの位置
	bool isSecondRoom_;	//長方形の二マス目に出たか
	bool isGoal_;	//ゴールにたどり着いたか
	

	void CreateKey(const int y, const int x);	//連想配列のキー生成

	const bool MovePiece(const Vector2 csr,
		const std::string bfr, const std::string aft);	//実際の移動処理　移動後のカーソル、移動前のKey、移動後のKeyぱずる

	void MoveRoom(const Vector2 after, const std::string prvKey);	//ステルス

	


	//判定系
	const bool CheckInstanceUp(int y, const int x, RoomBase& r);	//長方形の２コマ目かを判断およびインスタンスの生成(縦長）
	const bool CheckInstanceDown(int y, const int x, RoomBase& r);
	const bool CheckInstanceLeft(const int y, int x, RoomBase& r);	//長方形の２コマ目かを判断およびインスタンスの生成(横長）
	const bool CheckInstanceRight(const int y, int x, RoomBase& r);
	const RoomBase::ROOM_SHAPE GetRoomShape(const std::string key);	//部屋の形を検索(鍵検索)
	const RoomBase::ROOM_SHAPE GetRoomShape(const RoomBase::TYPE type)const;	//部屋の形を検索(種類検索)
	const bool IsDontMoveBlock(const std::string key);	//移動不可なブロックかどうか

	const Vector2 MoveLeftOrRight(const StageManager::DOOR_X door)const;	//左右の移動量を返却
	const StageManager::DOOR SearchDoor(const Vector2 pMapPos);		//ドアの検索
	const StageManager::DOOR SplitRoom(const Vector2 pMapPos,const Vector2 size,const Vector2 startPos)const;	//部屋の分割

	

	//Get&Set
	std::unique_ptr<RoomBase> GetSecondRoomInstance(const RoomBase& r);		//長方形２コマ目のインスタンスの生成
	void SetIsMoveRoom(const bool flag);	//フラグのセット
	void SetIsSecondRoom(const bool flag);	//フラグのセット
	void SetIsGoal(const bool flag);

	//長方形２コマ目かを判断するために必要なインスタンスを生成する
	RoomBase& CreateInstance4Confirmation(const RoomBase::TYPE type);

	void SetCursorType(const CURSOR type);
	const StageManager::DOOR_Y GetDoorSpare(void)const;			//縦長用の追加判定のドア検知を返却
	
	
	//更新

	//描画
	void DrawPazzle(void);	//パズル
	void DrawCursor(void);	//カーソル
	void DrawStealth(void);	//ステルス

	void LoadImgs(void);	//画像読み込み



protected:

	std::vector<std::vector<int>>::iterator pzlCsv_;
	Vector2 size_;
	virtual void SetParam(void);	//部屋ごとのパラメータ設定

	std::vector<std::vector<int>>* mapCsv_;	//マップのCsvデータの先頭アドレス格納
	std::vector<std::vector<int>>* objCsv_;	//オブジェクトのCsvデータの先頭アドレス格納
	int* roomImg_;		//パズルシーンの駒画像受け取り
	int** mapchip_;		//ステルスシーンのマップチップ受け取り

	StageManager::DOOR_Y doorSpare_;	//ドア判定縦長用(正方形と横長はNONE)
};