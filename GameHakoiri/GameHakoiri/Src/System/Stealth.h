//#pragma once
#include<vector>
#include<map>
#include"../Object/EnemyBase.h"
#include"../Object/CharacterBase.h"
#include"../Common/Vector2F.h"
#include"../Utility/Utility.h"
#include"../Stage/Room/RoomBase.h"

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
	static constexpr int OBLONG_ENEMY_NUM = 6;	//長方形の部屋の敵の数
	static constexpr int NOMAL_ENEMY_NUM = 2;	//正方形の部屋の敵の数
	static constexpr float DAMAGE = 0.3f;		//ダメージ

	//敵の初期位置

	static constexpr float NX1 = 32.0f * 21.0f + CharacterBase::CHARACTER_HALF_X;
	static constexpr float NY1 = 32.0f * 7.0f + CharacterBase::CHARACTER_HALF_Y;
	static constexpr float NX2 = 32.0f * 15.0f + CharacterBase::CHARACTER_HALF_X;
	static constexpr float NY2 = 32.0f * 19.0f + CharacterBase::CHARACTER_HALF_Y;

	static constexpr float OBX1= 32.0f * 8.0f + CharacterBase::CHARACTER_HALF_X;
	static constexpr float OBY1= 32.0f * 8.0f + CharacterBase::CHARACTER_HALF_Y;
	static constexpr float OBX2= 32.0f * 24.0f + CharacterBase::CHARACTER_HALF_X;
	static constexpr float OBY2= 32.0f * 15.0f + CharacterBase::CHARACTER_HALF_Y;
	static constexpr float OBX3= 32.0f * 8.0f + CharacterBase::CHARACTER_HALF_X;
	static constexpr float OBY3= 32.0f * 33.0f + CharacterBase::CHARACTER_HALF_Y;
	static constexpr float OBX4 = 32.0f * 24.0f + CharacterBase::CHARACTER_HALF_X;
	static constexpr float OBY4 = 32.0f * 33.0f + CharacterBase::CHARACTER_HALF_Y;
	static constexpr float OBX5 = 32.0f * 7.0f + CharacterBase::CHARACTER_HALF_X;
	static constexpr float OBY5 = 32.0f * 49.0f + CharacterBase::CHARACTER_HALF_Y;
	static constexpr float OBX6 = 32.0f * 24.0f + CharacterBase::CHARACTER_HALF_X;
	static constexpr float OBY6 = 32.0f * 49.0f + CharacterBase::CHARACTER_HALF_Y;

	static constexpr float OB2X1 = 32.0f * 11.0f + CharacterBase::CHARACTER_HALF_X;
	static constexpr float OB2Y1 = 32.0f * 8.0f + CharacterBase::CHARACTER_HALF_Y;
	static constexpr float OB2X2 = 32.0f * 24.0f + CharacterBase::CHARACTER_HALF_X;
	static constexpr float OB2Y2 = 32.0f * 12.0f + CharacterBase::CHARACTER_HALF_Y;

	static constexpr float OB2X3 = 32.0f * 15.0f + CharacterBase::CHARACTER_HALF_X;
	static constexpr float OB2Y3 = 32.0f * 23.0f + CharacterBase::CHARACTER_HALF_Y;
	static constexpr float OB2X4 = 32.0f * 48.0f + CharacterBase::CHARACTER_HALF_X;
	static constexpr float OB2Y4 = 32.0f * 9.0f + CharacterBase::CHARACTER_HALF_Y;

	static constexpr float OB2X5 = 32.0f * 38.0f + CharacterBase::CHARACTER_HALF_X;
	static constexpr float OB2Y5 = 32.0f * 15.0f + CharacterBase::CHARACTER_HALF_Y;
	static constexpr float OB2X6 = 32.0f * 52.0f + CharacterBase::CHARACTER_HALF_X;
	static constexpr float OB2Y6 = 32.0f * 25.0f + CharacterBase::CHARACTER_HALF_Y;


	//ブロックから見た位置の角度設定
	static constexpr float UNIT_DEG = 45.0f;
	static constexpr float NOMAL_DEG = 90.0f;


	Stealth(void);	//コンストラクタ
	~Stealth(void);	//デストラクタ

	bool Init(void);	//初期化
	void Update(void);	//更新
	void Draw(void);	//描画
	bool Release(void);	//解放

	bool IsFailde(void);

private:
	//インスタンス
	Player* player_;

	//判定
	bool isEnemyMove_;	//敵が衝突し移動できていないか
	bool isFailed_;
	bool isMoveRoom_;	//部屋移動を行ったか

	EnemyBase* enemyMng_[OBLONG_ENEMY_NUM*static_cast<int>(EnemyBase::TYPE::MAX)];	//敵の最大数＊種類を保持
	std::vector<EnemyBase*> useEnemy_;		//使用する敵を保持する
	std::map<std::string, std::vector<EnemyBase::TYPE>> memorizeType_;	//部屋ごとにおける生成した敵を保持
	std::map<std::string, std::vector<Vector2F>> memorizePos_;			//部屋ごとにおける生成した敵を保持
	Vector2F initPos_[static_cast<int>(RoomBase::ROOM_SHAPE::MAX)][OBLONG_ENEMY_NUM];	//敵の初期化位置

	//視界を遮られたときのオブジェクトとの位置関係を保存
	std::map<Vector2, Utility::DIR>objToPlayerDir_;
	std::map<Vector2, Utility::DIR>objToEnemyDir_;

	void Collision(void);		//当たり判定総括
	void CollisionMapchip(CharacterBase* character ,bool isPlayer);	//マップチップとの当たり判定
	void CollisionObstacle(CharacterBase* character);				//通り抜け不可なマップチップ
	void CollisionTrough(Vector2 pCol, CharacterBase* character);	//奥行きがあるマップチップ
	void CollisionEvent(Vector2 pCol);		//イベントがあるマップチップか
	
	bool CheckObjectPToE(Vector2F pPos, EnemyBase* enemy);	//playerと敵との間にオブジェクトがあるかを調べる
	std::vector<Vector2> GetWithinFieldOfViewObject(Vector2 pMapPos, Vector2 eMapPos);	//視野内のオブジェクトを取得
	Utility::DIR GetObjToCharacterDir(double rad);		//オブジェクトから見たキャラクターの位置の判定
	Vector2F GetJudgementPos(Vector2F pos, Utility::DIR dir);	//方向に応じた衝突判定に使用する位置を決める
	Utility::DIR CreateSpareLine(Vector2F charaPos, Vector2 obj, Utility::DIR dir);	//例外を防ぐための予備

	void ChangeRoom(void);					//部屋の変更
	bool IsSameSign(float v1, float v2)const;
	bool IsStraght(Vector2F v1, Vector2F v2)const;

	void DrawDebug(void);



	void EnemyInit(void);		//敵の初期化
	void CreateEnemy(void);		//敵の初期生成
	void InitEnemyPos(const RoomBase::ROOM_SHAPE type);	//敵の初期位置設定
	void SetEnemy(void);		//敵の配置
	void SearchSetEnemy(std::string key, int num);	//指定した部屋に敵の生成記録があるかを判定
	void MemorizeEnemy(std::string key);			//敵の記録

	void SetIsEnemyMove(bool flag);	//敵が動きを停止したかをセット
	bool IsEnemyMove(void)const;	//上記を返却
};