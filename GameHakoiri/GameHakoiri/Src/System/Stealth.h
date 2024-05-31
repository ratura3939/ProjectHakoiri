//#pragma once

class Player;

class Stealth
{
public:
	Stealth(void);	//コンストラクタ
	~Stealth(void);	//デストラクタ

	bool Init(void);	//初期化
	void Update(void);	//更新
	void Draw(void);	//描画
	bool Release(void);	//解放

private:
	Player* player_;

	void Collision(void);
	void ChangeRoom(void);

	void DrawDebug(void);
};