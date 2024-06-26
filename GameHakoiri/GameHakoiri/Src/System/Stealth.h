//#pragma once
#include<vector>
#include<map>
#include"../Object/EnemyBase.h"
#include"../Object/CharacterBase.h"
#include"../Common/Vector2F.h"

class CharacterBase;
class Player;
class EnemyBase;

class Stealth
{
public:

	//定数
	static constexpr int DOOR_DISTANCE = 32 * 15;	//ドアの位置は端からマップチップ15マス分の位置にある
	static constexpr int INIT_ROOM_POS = 32 * 4;	//部屋移動後の初期位置
	static constexpr int INIT_ROOM_POS_SIDE = 32 * 2;	//部屋移動後の初期位置
	static constexpr int OBLONG_ENEMY_NUM = 3;	//長方形の部屋の敵の数
	static constexpr int NOMAL_ENEMY_NUM = 2;	//正方形の部屋の敵の数

	//敵の初期位置

	static constexpr float NX1 = 672.0f + CharacterBase::CHARACTER_HALF_X;
	static constexpr float NY1 = 224.0f + CharacterBase::CHARACTER_HALF_Y;
	static constexpr float NX2 = 480.0f + CharacterBase::CHARACTER_HALF_X;
	static constexpr float NY2 = 608.0f + CharacterBase::CHARACTER_HALF_Y;

	static constexpr float OBX1= 480.0f + CharacterBase::CHARACTER_HALF_X;
	static constexpr float OBY1= 480.0f + CharacterBase::CHARACTER_HALF_Y;
	static constexpr float OBX2= 160.0f + CharacterBase::CHARACTER_HALF_X;
	static constexpr float OBY2= 1056.0f + CharacterBase::CHARACTER_HALF_Y;
	static constexpr float OBX3= 608.0f + CharacterBase::CHARACTER_HALF_X;
	static constexpr float OBY3= 1568.0f + CharacterBase::CHARACTER_HALF_Y;

	static constexpr float OB2X1 = 960.0f + CharacterBase::CHARACTER_HALF_X;
	static constexpr float OB2Y1 = 736.0f + CharacterBase::CHARACTER_HALF_Y;
	static constexpr float OB2X2 = 448.0f + CharacterBase::CHARACTER_HALF_X;
	static constexpr float OB2Y2 = 480.0f + CharacterBase::CHARACTER_HALF_Y;
	static constexpr float OB2X3 = 1376.0f + CharacterBase::CHARACTER_HALF_X;
	static constexpr float OB2Y3 = 384.0f + CharacterBase::CHARACTER_HALF_Y;

	/*static constexpr Vector2F NOMAL_POS_1=
	{672.0f + CharacterBase::CHARACTER_HALF_X,224.0f + CharacterBase::CHARACTER_HALF_Y };
	static constexpr Vector2F NOMAL_POS_2=
	{480.0f + CharacterBase::CHARACTER_HALF_X,608.0f + CharacterBase::CHARACTER_HALF_Y };

	static constexpr Vector2F OBLONG_POS_1=
	{480.0f + CharacterBase::CHARACTER_HALF_X,480.0f + CharacterBase::CHARACTER_HALF_Y };
	static constexpr Vector2F OBLONG_POS_2=
	{160.0f + CharacterBase::CHARACTER_HALF_X,1056.0f + CharacterBase::CHARACTER_HALF_Y };
	static constexpr Vector2F OBLONG_POS_3=
	{608.0f + CharacterBase::CHARACTER_HALF_X,1568.0f + CharacterBase::CHARACTER_HALF_Y };

	static constexpr Vector2F OBLONG_2_POS_1 =
	{ 960.0f + CharacterBase::CHARACTER_HALF_X,736.0f + CharacterBase::CHARACTER_HALF_Y };
	static constexpr Vector2F OBLONG_2_POS_2 =
	{ 448.0f + CharacterBase::CHARACTER_HALF_X,480.0f + CharacterBase::CHARACTER_HALF_Y };
	static constexpr Vector2F OBLONG_2_POS_3 =
	{ 1376.0f + CharacterBase::CHARACTER_HALF_X,384.0f + CharacterBase::CHARACTER_HALF_Y };*/

	Stealth(void);	//コンストラクタ
	~Stealth(void);	//デストラクタ

	bool Init(void);	//初期化
	void Update(void);	//更新
	void Draw(void);	//描画
	bool Release(void);	//解放

private:
	//インスタンス
	Player* player_;

	//判定
	bool isEnemyMove_;	//敵が衝突し移動できていないか

	EnemyBase* enemyMng_[OBLONG_ENEMY_NUM*static_cast<int>(EnemyBase::TYPE::MAX)];	//敵の最大数＊種類を保持
	std::vector<EnemyBase*> useEnemy_;		//使用する敵を保持する
	std::map<std::string, std::vector<EnemyBase::TYPE>> memorizeType_;	//部屋ごとにおける生成した敵を保持
	std::map<std::string, std::vector<Vector2F>> memorizePos_;			//部屋ごとにおける生成した敵を保持
	Vector2F initPos_[static_cast<int>(RoomBase::ROOM_SHAPE::MAX)][OBLONG_ENEMY_NUM];

	void Collision(void);		//当たり判定総括
	void CollisionMapchip(CharacterBase* character ,bool isPlayer);	//マップチップとの当たり判定
	void CollisionObstacle(CharacterBase* character);			//通り抜け不可なマップチップ
	void CollisionTrough(Vector2 pCol, CharacterBase* character);		//奥行きがあるマップチップ
	void CollisionEvent(Vector2 pCol);		//イベントがあるマップチップか
	void ChangeRoom(void);					//部屋の変更

	void DrawDebug(void);
	void EnemyInit(void);		//敵の初期化
	void CreateEnemy(void);		//敵の初期生成
	void InitEnemyPos(const RoomBase::ROOM_SHAPE type);	//敵の初期位置設定
	void SetEnemy(void);		//敵の配置
	void SearchSetEnemy(std::string key, int num);	//指定した部屋に敵の生成記録があるかを判定
	void MemorizeEnemy(std::string key);	//敵の記録を呼び出す

	void SetIsEnemyMove(bool flag);
	bool IsEnemyMove(void)const;
};