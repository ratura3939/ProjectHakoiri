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
	static constexpr int UNIT_STEALTH_SIZE_X = 32;

	//列挙型
	enum class TYPE
	{
		OWN
		, WASITU
		, LIVING
		, BATH
		, STORAGE
		, KITCHEN
		, ENTRANCE
		, MAX
	};

	RoomBase(void);	//コンストラクタ
	~RoomBase(void);	//デストラクタ

	bool Init(void);	//初期化
	bool Release(void);	//解放

	virtual void SetParam(void);	//部屋ごとのパラメータ設定

private:


protected:
	Vector2F PazzleSize_;
	int pieceImg_;

	Vector2F StealthSize_;
};