//#pragma once

class Player;

class Stealth
{
public:

	//定数
	static constexpr int DOOR_DISTANCE = 32 * 15;	//ドアの位置は端からマップチップ15マス分の位置にある
	static constexpr int INIT_ROOM_POS = 32 * 4;	//部屋移動後の初期位置
	static constexpr int INIT_ROOM_POS_SIDE = 32 * 2;	//部屋移動後の初期位置

	Stealth(void);	//コンストラクタ
	~Stealth(void);	//デストラクタ

	bool Init(void);	//初期化
	void Update(void);	//更新
	void Draw(void);	//描画
	bool Release(void);	//解放

private:
	Player* player_;
	Vector2F prevPlayerPos_;

	void Collision(void);
	void CollisionObstacle(void);
	void CollisionTrough(Vector2 pCol);
	void CollisionEvent(Vector2 pCol);
	void ChangeRoom(void);

	void DrawDebug(void);
};