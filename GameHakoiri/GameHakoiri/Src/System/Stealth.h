//#pragma once
#include<vector>
#include<map>
#include"../Object/EnemyBase.h"
#include"../Common/Vector2F.h"

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

	static constexpr Position NOMAL_POS_1={0.0f,0.0f};

	Stealth(void);	//コンストラクタ
	~Stealth(void);	//デストラクタ

	bool Init(void);	//初期化
	void Update(void);	//更新
	void Draw(void);	//描画
	bool Release(void);	//解放

private:
	Player* player_;
	Position prevPlayerPos_;

	EnemyBase* enemyMng_[OBLONG_ENEMY_NUM*static_cast<int>(EnemyBase::TYPE::MAX)];	//敵の最大数＊種類を保持
	std::vector<EnemyBase*> useEnemy_;		//使用する敵を保持する
	std::map<std::string, std::vector<EnemyBase::TYPE>> memorizeType_;	//部屋ごとにおける生成した敵を保持
	std::map<std::string, std::vector<Position>> memorizePos_;			//部屋ごとにおける生成した敵を保持
	Position initPos_[static_cast<int>(RoomBase::ROOM_SHAPE::MAX)][OBLONG_ENEMY_NUM];

	void Collision(void);
	void CollisionObstacle(void);
	void CollisionTrough(Vector2 pCol);
	void CollisionEvent(Vector2 pCol);
	void ChangeRoom(void);

	void DrawDebug(void);
	void EnemyInit(void);
	void CreateEnemy(void);
	void SetEnemyPos(void);
	void SetEnemy(void);
	void MemorizeEnemy(std::string key);
};