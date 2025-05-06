#pragma once

#include"../Common/Vector2F.h"

class Camera
{
public:
	static void CreateInstance(void);
	static Camera& GetInstance(void);
	
	bool Init(void);
	void Update(void);
	void Relese(void);

	/// <summary>
	/// 注視点の設定
	/// </summary>
	/// <param name="pPos"></param>
	void SetTargetPos(const Vector2F pPos);

	/// <summary>
	/// マップサイズセット
	/// </summary>
	/// <param name="mapsize"></param>
	void SetMapSize(const Vector2F mapsize);

	/// <summary>
	/// 位置取得
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	const Vector2F GetPos(void)const;

private:

	static Camera* instance_;

	Vector2F pos_;
	Vector2F localCenterPos_;
	Vector2F targetPos_;
	Vector2F mapSize_;

	void MoveCamera(void);

	Camera(void);	//コンストラクタ
	~Camera(void);	//デストラクタ
};

