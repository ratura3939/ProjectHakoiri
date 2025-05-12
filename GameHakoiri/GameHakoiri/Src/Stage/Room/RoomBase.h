#pragma once
#include<vector>
#include"../../Common/Vector2F.h"


class RoomBase
{
public:
	//定数
	static constexpr int ROOM_TYPES = 7;	//部屋の種類数

	//列挙型
	
	/// <summary>
	/// 部屋の種類
	/// </summary>
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

	/// <summary>
	/// 部屋の形
	/// </summary>
	enum class ROOM_SHAPE
	{
		NOMAL,
		OBLONG,
		OBLONG_SIDE,
		MAX
	};

	RoomBase(int roomImg, int sizeX, int sizeY,
		std::vector<std::vector<int>> map, std::vector<std::vector<int>> obj,
		int* mapchip);			//コンストラクタ
	RoomBase(int roomImg);		//コピーコンストラクタ
	virtual ~RoomBase(void);	//デストラクタ

	bool Init(void);	//初期化
	//部屋の描画
	virtual void DrawPazzle(void);	//パズル
	void DrawStealth(void);			//ステルス
	void DrawStealthObject(void);	//障害物

	bool Release(void);				//解放


	//セッター・ゲッター

	/// <summary>
	/// 種類設定
	/// </summary>
	/// <param name="type">種類</param>
	void SetRoomType(const TYPE type);

	/// <summary>
	/// 種類取得
	/// </summary>
	/// <returns>種類</returns>
	const TYPE GetRoomType(void)const;	//部屋の種類を返却

	/// <summary>
	/// 座標設定(パズル時)
	/// </summary>
	/// <param name="pos">座標</param>
	void SetPzlPos(const Vector2F pos);

	/// <summary>
	/// 座標取得
	/// </summary>
	/// <returns>種類</returns>
	const Vector2F GetPzlPos(void)const;

	/// <summary>
	/// カーソルフラグ設定
	/// </summary>
	/// <param name="flag">true=カーソル状態/false=非カーソル状態</param>
	void SetIsCursor(const bool flag);

	/// <summary>
	/// カーソルフラグ取得
	/// </summary>
	/// <returns>true=カーソル状態/false=非カーソル状態</returns>
	const bool GetIsCursor(void)const;

	/// <summary>
	/// 変更が既にされたかの設定
	/// </summary>
	/// <param name="flag">true=した/false=していない</param>
	void SetIsChange(const bool flag);

	/// <summary>
	/// 変更が既にされたかの取得
	/// </summary>
	/// <returns>true=されている/false=されていない</returns>
	const bool IsChange(void)const;
	
	/// <summary>
	/// 部屋を描画するかのフラグ
	/// </summary>
	/// <param name="flag">true=する/false=しない</param>
	void SetIsDrawRoom(const bool flag);

	/// <summary>
	/// 現在の部屋のサイズ取得
	/// </summary>
	/// <returns>サイズ</returns>
	Vector2F GetRoomSize(void)const;

	/// <summary>
	/// 指定場所のオブジェクトを返す
	/// </summary>
	/// <param name="pos">指定場所</param>
	/// <returns>指定のオブジェクトCSV値</returns>
	const int GetObj(const Vector2 pos)const;

	/// <summary>
	/// 指定場所のマップチップを返す
	/// </summary>
	/// <param name="pos">指定場所</param>
	/// <returns>指定のマップCSV値</returns>
	const int GetMapchip(const Vector2 pos)const;

	/// <summary>
	/// 指定場所の一つ下のオブジェクトを返す
	/// </summary>
	/// <param name="pos">指定場所</param>
	/// <returns>指定の一つ下のオブジェクトCSV値</returns>
	const bool IsOneDownObj(const Vector2 pos)const;	//指定された場所のオブジェクトCSVの値を返す

	/// <summary>
	/// ダミーフラグ取得
	/// </summary>
	/// <returns>true=ダミーではない/false=ダミーである</returns>
	const bool IsClone(void)const;

	/// <summary>
	/// ダミーフラグ設定
	/// </summary>
	/// <param name="flag">true=ダミー/false=非ダミー</param>
	void SetIsClone(const bool flag);


private:
	Vector2F mapMaxSize_;	//実際に描画するマップのサイズ

	bool isChange_;			//パズルリセット時にすでに確定している場所であるかの判定
	bool isDrawStealth_;	//ステルスシーンにおいて描画するかを決める

	std::vector<std::vector<int>> map_;		//マップデータ
	std::vector<std::vector<int>> obj_;		//オブジェクトデータ
	int* mapchip_;	//マップイラスト
	

protected:

	TYPE type_;				//部屋の種類の識別子


	Vector2F pzlPos_;		//パズルシーンにおける座標
	Vector2F pieceSize_;	//実際に描画する駒のサイズ
	Vector2F pazzleSize_;	//パズルシーンにおけるサイズ(〇×〇か）
	

	Vector2F mapSize_;		//ステルスシーンにおけるマップのサイズ(〇×〇か）

	bool isCursor_;			//カーソルに選択されているかどうか

	int roomImg_;			//部屋の画像
	bool isDrawRoom_;		//描画するか決める（長方形の二マス目用）
	bool isClone_;			//本体じゃないかどうかを判断

	virtual void SetParam(void);	//部屋ごとのパラメータ設定
};