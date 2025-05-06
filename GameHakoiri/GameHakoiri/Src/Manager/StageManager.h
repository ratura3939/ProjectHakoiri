#pragma once
#include<memory>
#include"../Utility/Utility.h"
#include"../Scene/GameScene.h"
#include"../Stage/Room/RoomBase.h"
#include"../Manager/SceneManager.h"

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
	//各ステージにおけるパズルのサイズXY
	static constexpr int TUTORIAL_PAZZLE_SIZE_X = 6;
	static constexpr int TUTORIAL_PAZZLE_SIZE_Y = 6;
	static constexpr int FIRST_PAZZLE_SIZE_X = 6;
	static constexpr int FIRST_PAZZLE_SIZE_Y = 6;
	static constexpr int SECOND_PAZZLE_SIZE_X = 6;
	static constexpr int SECOND_PAZZLE_SIZE_Y = 7;
	static constexpr int THIRD_PAZZLE_SIZE_X = 7;
	static constexpr int THIRD_PAZZLE_SIZE_Y = 7;
	//部屋の種類別のパズルにおける大きさXY
	static constexpr int NOMAL_PAZZLE_X = 1;
	static constexpr int NOMAL_PAZZLE_Y = 1;
	static constexpr int OBLONG_PAZZLE_X = 1;
	static constexpr int OBLONG_PAZZLE_Y = 2;
	static constexpr int OBLONG_2_PAZZLE_X = 2;
	static constexpr int OBLONG_2_PAZZLE_Y = 1;
	//部屋の種類別のマップにおける大きさXY
	static constexpr int NOMAL_MAP_X = 30;
	static constexpr int NOMAL_MAP_Y = 30;
	static constexpr int OBLONG_MAP_X = 30;
	static constexpr int OBLONG_MAP_Y = 60;
	static constexpr int OBLONG_2_MAP_X = 60;
	static constexpr int OBLONG_2_MAP_Y = 30;

	//各モードにおける基本サイズXY
	static constexpr int UNIT_PAZZLE_SIZE_X = 64;
	static constexpr int UNIT_PAZZLE_SIZE_Y = 64;
	static constexpr int UNIT_STEALTH_SIZE_X = 32;
	static constexpr int UNIT_STEALTH_SIZE_Y = 32;

	//扉の位置検索の際の部屋の分割数
	static constexpr int SPLIT_ROOM_X = 2;
	static constexpr int SPLIT_ROOM_Y = 3;

	//マニュアル
	static constexpr int MANUAL_SIZE = 256;
	static constexpr int MANUAL_FLASH = 40;
	static constexpr int MANUAL_FLASH_MAX = 3000;


	bool Init(STAGENUM);
	void Update(GameScene::MODE mode);
	void Draw(GameScene::MODE mode);
	void DrawObject(void);
	bool Release(void);	

#pragma region パズル関連
	//処理**********************************************************************************
	/// <summary>
	/// 移動(カーソル)
	/// </summary>
	/// <param name="dir">移動方向</param>
	void MoveCursor(Utility::DIR dir);

	/// <summary>
	/// 移動(駒)
	/// </summary>
	/// <param name="dir">移動方向</param>
	void MovePiece(Utility::DIR dir);

	/// <summary>
	/// 盤面リセット
	/// </summary>
	void PazzleReset(void);

	//設定************************************************************************************
	/// <summary>
	/// 点滅
	/// </summary>
	/// <param name="flag">true=点滅させる/fals=点滅させない</param>
	void SetFlash(bool flag);

	/// <summary>
	/// ゲーム説明フラグセット
	/// </summary>
	/// <param name="flag">true=描画する/false=描画しない</param>
	void SetIsDrawPazzleManual(bool flag);

	//判定**************************************************************************************
	/// <summary>
	/// ゴール可能かをｐ返す
	/// </summary>
	/// <returns>true=可能/false=不可能</returns>
	const bool IsCanGoal(void);
#pragma endregion

#pragma region ステルス関連
	//処理**********************************************************************************
	/// <summary>
	/// ステルスモードへ変更及び初期化
	/// </summary>
	void ChangeModeInit(void);

	/// <summary>
	/// 部屋の切り替え
	/// </summary>
	/// <param name="pMapPos">扉に触れた時のプレイヤー位置</param>
	void ChangeMap(Vector2 pMapPos);

	//判定***********************************************************************************
	/// <summary>
	/// 長方形マスの本体じゃないほうを通ったか
	/// </summary>
	/// <returns> true=通った/false=通っていない </returns>
	const bool IsSecondEvidence(void)const;

	/// <summary>
	/// オブジェクトと衝突しているか
	/// </summary>
	/// <param name="pMapPos">判定対象の座標</param>
	/// <returns> true=している/false=していない </returns>
	const bool IsCollisionObject(const Vector2 pMapPos)const;

	/// <summary>
	/// 壁と衝突しているか
	/// </summary>
	/// <param name="pMapPos">判定対象の座標</param>
	/// <returns> true=している/false=していない </returns>
	const bool IsCollisionWall(const Vector2 pMapPos)const;

	/// <summary>
	/// マップ移動をしたか
	/// </summary>
	/// <returns> true=した/false=していない </returns>
	const bool IsMoveMap(void);

	/// <summary>
	/// クリアしたか
	/// </summary>
	/// <returns>true=した/false=していない</returns>
	const bool IsClear(void)const;

	/// <summary>
	/// 縦長のオブジェクトの最下部ブロックであるかどうか
	/// </summary>
	/// <param name="pMapPos">判定対象の座標</param>
	/// <returns>true=最下部である/false=最下部ではない</returns>
	const bool IsBottomObject(const Vector2 pMapPos)const;

	//情報取得*********************************************************************************
	/// <summary>
	/// 現在いる部屋のマップサイズを取得
	/// </summary>
	/// <returns>サイズ={float,float}</returns>
	Vector2F GetMapMaxSize(void)const;

	/// <summary>
	/// 座標をマップの要素数用に変換
	/// </summary>
	/// <param name="pPos">座標</param>
	/// <returns>要素数変換後の{X,Y}</returns>
	Vector2 GetVector2MapPos(const Vector2 pPos)const;

	/// <summary>
	/// 座標に衝突しているオブジェクトの種類変換
	/// </summary>
	/// <param name="pMapPos">座標</param>
	/// <returns>オブジェクトの種類(通り抜け可能かなど)</returns>
	const OBJECT GetObjectType(const Vector2 pMapPos)const;		//オブジェクトのタイプを返却

	/// <summary>
	/// 部屋の形を取得
	/// </summary>
	/// <returns>正方形OR長方形</returns>
	const RoomBase::ROOM_SHAPE GetShape(void);					//部屋の形正方形か長方形か）

	/// <summary>
	/// 鍵の取得
	/// </summary>
	/// <returns>現在の配列要素数</returns>
	const std::string GetKey(void)const;						//配列指定数

	/// <summary>
	/// ドアの位置を取得
	/// </summary>
	/// <returns></returns>
	const DOOR GetDoor(void)const;								//移動に使用したドアの位置

	/// <summary>
	/// 上記の部屋が縦長だった場合の補足分
	/// </summary>
	/// <returns>補足後の正確な場所</returns>
	const DOOR_Y GetDoorSecond(void)const;

private:
	/// <summary>
	/// 配列要素数を座標に変換
	/// </summary>
	/// <param name="pPos">マップ配列要素数</param>
	/// <returns>座標</returns>
	Vector2 GetMapPos2Vector(const Vector2 pPos)const;			//マップの配列を座標に変換
#pragma endregion
	
public:
	//シングルトン化
	static bool CreateInstance(STAGENUM);	//外部から静的インスタンスを生成
	static StageManager& GetInstance(void);	//インスタンスの取得
	
private:

	std::unique_ptr<StageBase> stage_;	//ステージ本体

	STAGENUM num_;						//生成するステージ番号

	Vector2 dir_[static_cast<int>(Utility::DIR::MAX)];	//移動方向

	bool isDrawPazzleManual_;			//パズルの操作説明を描画するかどうか
	int manualFlash_;												//点滅用カウンタ

	//IMG
	int roomImg_[static_cast<int>(RoomBase::TYPE::MAX)];			//部屋
	int* mapTile_[static_cast<int>(MAPCHIP::MAX)];					//マップ画像
	int manualImg_[static_cast<int>(SceneManager::CONTROLLER::MAX)];//説明
	
	//Csv
	std::vector<std::vector<int>> stageCsv_[static_cast<int>(STAGENUM::MAX)];		//パズル
	std::vector<std::vector<int>> mapCsv_[static_cast<int>(RoomBase::TYPE::MAX)];	//マップ
	std::vector<std::vector<int>> objCsv_[static_cast<int>(RoomBase::TYPE::MAX)];	//オブジェクト
	std::vector<std::vector<int>>mapchipObj_[static_cast<int>(MAPCHIP::MAX)][static_cast<int>(OBJECT::MAX)];	//マップチップ当たり判定C


	//データ読み込み
	void LoadImg(void);
	void LoadCsv(void);

	//シングルトン化
	StageManager(void);	//コンストラクタ
	StageManager(const StageManager&);	//コピーコンストラクタ
	void Destroy(void);	//デストラクタ

	static  StageManager* instance_;	//実体を確保
};