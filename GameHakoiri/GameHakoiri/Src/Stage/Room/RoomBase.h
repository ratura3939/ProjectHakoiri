#pragma once
#include"../../Common/Vector2F.h"

class RoomBase
{
public:
	//定数
	static constexpr int ROOM_TYPES = 7;	//部屋の種類数
	static constexpr int UNIT_PAZZLE_SIZE_X = 64;
	static constexpr int UNIT_PAZZLE_SIZE_Y = 64;
	static constexpr int UNIT_STEALTH_SIZE_X = 32;
	static constexpr int UNIT_STEALTH_SIZE_Y = 32;

	//列挙型
	enum class TYPE
	{
		NONE
		, OWN
		, WASITU
		, LIVING
		, BATH
		, STORAGE
		, KITCHEN
		, ENTRANCE
		, WALL
		, GOAL
		, MAX
	};

	RoomBase(void);	//コンストラクタ
	~RoomBase(void);	//デストラクタ

	bool Init(void);	//初期化
	virtual void DrawPazzle(void);	//パズルシーンにおける部屋の描画
	void DrawStealth(void);	//ステルスシーンにおける部屋の描画
	bool Release(void);	//解放

	void SetRoomType(TYPE type);	//部屋の種類を設定
	TYPE GetRoomType(void);	//部屋の種類を返却

	void SetPzlPos(Vector2F pos);	//パズルの座標設定
	Vector2F GetPzlPos(void);	//パズルの座標返却

	void SetMapPos(Vector2F pos);	//マップの座標設定
	Vector2F GetMapPos(void);	//マップの座標返却

	void SetIsCursor(bool flag);	//カーソルフラグの設定
	bool GetIsCursor(void);	//カーソルフラグの返却


	//いずれ消すもの
	void SetColor(int col);
	int GetColor(void);
	

private:
	Vector2F mapPos_;		//ステルスシーンにおけるmapの座標（必要かはわからん）

	Vector2F pieceSize_;	//実際に描画する駒のサイズ
	Vector2F mapSize_;		//実際に描画するマップのサイズ

	bool isCursor_;			//カーソルに選択されているかどうか
	

protected:

	TYPE type_;	//部屋の種類の識別子


	Vector2F pzlPos_;		//パズルシーンにおける座標

	Vector2F PazzleSize_;	//パズルシーンにおけるサイズ(〇×〇か）
	int pieceImg_;		//駒の画像格納
	int frameImg_;		//枠の画像

	Vector2F StealthSize_;	//ステルスシーンにおけるマップのサイズ(〇×〇か）


	virtual void SetParam(void);	//部屋ごとのパラメータ設定

	//テスト用
	int dbgColor_;
};