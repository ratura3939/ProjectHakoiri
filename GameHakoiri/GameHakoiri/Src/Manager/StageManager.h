#pragma once
#include<memory>
#include"../Utility/Utility.h"
#include"../Scene/GameScene.h"
#include"../Stage/Room/RoomBase.h"

class GameScene;
class StageBase;

class StageManager
{
public:

	//列挙型
	//生成するステージ
	enum class STAGENUM
	{
		TUTORIAL
		, FIRST
		, SECOND
		, THIRD
		, MAX
	};

	//マップに使用するマップチップの種類
	enum class MAPCHIP
	{
		BATH,
		EXTERIA,
		INTERIA,
		MAX
	};

	//オブジェクトの種類
	enum class OBJECT
	{
		OBSTACLE,
		THROUGH,
		EVENT,
		MAX
	};

	//扉の位置
	enum class DOOR_X
	{
		NONE,
		LEFT,
		RIGHT
	};

	enum class DOOR_Y
	{
		NONE,
		TOP,
		MIDDLE,
		BOTTOM
	};

	struct DOOR
	{
		DOOR_X x;
		DOOR_Y y;
	};

	//定数
	//各ステージにおけるパズルのサイズ
	static constexpr int TUTORIAL_PAZZLE_SIZE_X = 6;
	static constexpr int TUTORIAL_PAZZLE_SIZE_Y = 6;
	static constexpr int FIRST_PAZZLE_SIZE_X = 6;
	static constexpr int FIRST_PAZZLE_SIZE_Y = 6;
	static constexpr int SECOND_PAZZLE_SIZE_X = 6;
	static constexpr int SECOND_PAZZLE_SIZE_Y = 6;
	static constexpr int THIRD_PAZZLE_SIZE_X = 6;
	static constexpr int THIRD_PAZZLE_SIZE_Y = 6;
	//部屋の種類別のパズルにおける大きさ
	static constexpr int NOMAL_PAZZLE_X = 1;
	static constexpr int NOMAL_PAZZLE_Y = 1;
	static constexpr int OBLONG_PAZZLE_X = 1;
	static constexpr int OBLONG_PAZZLE_Y = 2;
	static constexpr int OBLONG_2_PAZZLE_X = 2;
	static constexpr int OBLONG_2_PAZZLE_Y = 1;
	//部屋の種類別のマップにおける大きさ
	static constexpr int NOMAL_MAP_X = 30;
	static constexpr int NOMAL_MAP_Y = 30;
	static constexpr int OBLONG_MAP_X = 30;
	static constexpr int OBLONG_MAP_Y = 60;
	static constexpr int OBLONG_2_MAP_X = 60;
	static constexpr int OBLONG_2_MAP_Y = 30;

	//各モードにおける基本サイズ
	static constexpr int UNIT_PAZZLE_SIZE_X = 64;
	static constexpr int UNIT_PAZZLE_SIZE_Y = 64;
	static constexpr int UNIT_STEALTH_SIZE_X = 32;
	static constexpr int UNIT_STEALTH_SIZE_Y = 32;

	//扉の位置検索の際の部屋の分割数
	static constexpr int SPLIT_ROOM_X = 2;
	static constexpr int SPLIT_ROOM_Y = 3;


	bool Init(STAGENUM);				//初期化
	void Update(GameScene::MODE mode);	//更新
	void Draw(GameScene::MODE mode);	//描画
	void DrawObject(void);				//描画
	bool Release(void);					//解放

	void MoveCursor(Utility::DIR dir);	//カーソルの移動
	void MovePiece(Utility::DIR dir);	//駒の移動
	void PazzleReset(void);		//盤面リセット
	void SetFlash(bool flag);	//枠点滅
	
	bool CanGoal(void);	//ゴール可能かを判断
	void ChangeModeInit(void);	//シーン切り替え時の初期化
	void ChangeMap(Vector2 pMapPos);	//部屋の切り替え
	Vector2F GetMapMaxSize(void)const;	//マップの最大サイズを取得

	bool IsCollisionObject(const Vector2 pMapPos)const;	//座標が何かのオブジェクトと衝突しているか
	bool IsCollisionWall(const Vector2 pMapPos)const;	//座標が壁と衝突しているか
	Vector2 GetVector2MapPos(const Vector2 pPos)const;	//座標をマップの配列に変換
	Vector2 GetMapPos2Vector(const Vector2 pPos)const;	//マップの配列を座標に変換
	OBJECT GetObjectType(const Vector2 pMapPos)const;	//オブジェクトのタイプを返却
	bool IsBottomObject(const Vector2 pMapPos)const;	//オブジェクトのタイプを返却
	bool IsMove(void);				//マップ移動をしたかどうかを返却
	RoomBase::ROOM_SHAPE GetShape(void);//部屋の形を取得（正方形か長方形か）
	std::string GetKey(void)const;	//roomKeyの取得
	DOOR GetDoor(void)const;		//移動に使用したドアの位置を返却
	DOOR_Y GetDoorSecond(void)const;//上記の部屋が縦長だった場合の補足分
	bool IsSecondEvidence(void)const;//長方形の本体じゃない方を通ったか
	bool IsClear(void)const;		//クリアしたか

	//シングルトン化
	static bool CreateInstance(STAGENUM);	//外部から静的インスタンスを生成
	static StageManager& GetInstance(void);	//インスタンスの取得
	
private:

	//インスタンス
	StageBase* stage_;

	STAGENUM num_;	//生成するステージ番号を保持

	Vector2 dir_[static_cast<int>(Utility::DIR::MAX)];

	//IMG
	int roomImg_[static_cast<int>(RoomBase::TYPE::MAX)];
	
	//Csv
	//パズルステージ保持
	std::vector<std::vector<int>> stageCsv_[static_cast<int>(STAGENUM::MAX)];

	//マップのCsvデータの先頭アドレス格納
	std::vector<std::vector<int>> mapCsv_[static_cast<int>(RoomBase::TYPE::MAX)];	
	//オブジェクトのCsvデータの先頭アドレス格納
	std::vector<std::vector<int>> objCsv_[static_cast<int>(RoomBase::TYPE::MAX)];	
	//マップ画像を取得
	int* mapTile_[static_cast<int>(MAPCHIP::MAX)];	
	//マップチップごとの当たり判定CSV格納用
	std::vector<std::vector<int>>mapchipObj_[static_cast<int>(MAPCHIP::MAX)][static_cast<int>(OBJECT::MAX)];	

	void LoadImg(void);
	void LoadCsv(void);



	//シングルトン化
	StageManager(void);	//コンストラクタ
	StageManager(const StageManager&);	//コピーコンストラクタ
	void Destroy(void);	//デストラクタ

	static  StageManager* instance_;	//実体を確保
};