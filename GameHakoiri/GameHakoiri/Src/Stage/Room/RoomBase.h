#pragma once
#include<vector>
#include"../../Common/Vector2F.h"


class RoomBase
{
public:
	//定数
	static constexpr int ROOM_TYPES = 7;	//部屋の種類数

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

	enum class ROOM_SHAPE
	{
		NOMAL,
		OBLONG,
		OBLONG_SIDE,
		MAX
	};

	RoomBase(int roomImg, int sizeX, int sizeY,
		std::vector<std::vector<int>> map, std::vector<std::vector<int>> obj,
		int* mapchip);	//コンストラクタ
	RoomBase(int roomImg);	//コピーコンストラクタ
	virtual ~RoomBase(void);	//デストラクタ

	bool Init(void);	//初期化
	virtual void DrawPazzle(void);	//パズルシーンにおける部屋の描画
	void DrawStealth(void);	//ステルスシーンにおける部屋の描画
	void DrawStealthObject(void);	//ステルスシーンにおける部屋の描画(これはプレイヤーとの描画順の関係でステルスで呼ぶ）
	bool Release(void);	//解放


	//セッター・ゲッター
	void SetRoomType(TYPE type);	//部屋の種類を設定
	TYPE GetRoomType(void)const;			//部屋の種類を返却

	void SetPzlPos(Vector2F pos);	//パズルの座標設定
	Vector2F GetPzlPos(void)const;		//パズルの座標返却

	void SetMapPos(Vector2F pos);	//マップの座標設定
	Vector2F GetMapPos(void)const;		//マップの座標返却

	void SetIsCursor(bool flag);	//カーソルフラグの設定
	bool GetIsCursor(void)const;			//カーソルフラグの返却

	bool IsChange(void);			//IsChangeのゲッター
	void SetIsChange(bool flag);	//IsChangeのセッター

	void SetIsDrawRoom(bool flag);	//部屋を描画するかのフラグをセット

	Vector2F GetRoomSize(void)const;//現在の部屋のサイズを取得

	int GetObj(Vector2 pos)const;	//指定された場所のオブジェクトCSVの値を返す
	int GetMapchip(Vector2 pos)const;	//指定された場所のオブジェクトCSVの値を返す
	bool IsOneDownObj(Vector2 pos)const;	//指定された場所のオブジェクトCSVの値を返す

	bool IsClone(void)const;	//複製たいかどうか
	void SetIsClone(bool flag);	//上記のセット


private:
	Vector2F mapPos_;		//ステルスシーンにおけるmapの座標（必要かはわからん）
	Vector2F mapMaxSize_;		//実際に描画するマップのサイズ

	bool isChange_;	//パズルリセット時にすでに確定している場所であるかの判定
	bool isDrawStealth_;	//ステルスシーンにおいて描画するかを決める

	std::vector<std::vector<int>> map_;
	std::vector<std::vector<int>> obj_;
	int* mapchip_;
	

protected:

	TYPE type_;	//部屋の種類の識別子


	Vector2F pzlPos_;		//パズルシーンにおける座標
	Vector2F pieceSize_;	//実際に描画する駒のサイズ
	Vector2F pazzleSize_;	//パズルシーンにおけるサイズ(〇×〇か）
	

	Vector2F mapSize_;	//ステルスシーンにおけるマップのサイズ(〇×〇か）

	bool isCursor_;			//カーソルに選択されているかどうか

	int roomImg_;	//部屋の画像
	bool isDrawRoom_;	//描画するか決める（長方形の二マス目用）
	bool isClone_;	//本体じゃないかどうかを判断

	virtual void SetParam(void);	//部屋ごとのパラメータ設定
};