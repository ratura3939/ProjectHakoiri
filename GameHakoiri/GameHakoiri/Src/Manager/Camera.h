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

	void SetTargetPos(const Vector2F pPos);
	void SetMapSize(const Vector2F mapsize);
	Vector2F GetPos(void)const;

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

