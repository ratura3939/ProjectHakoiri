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

	void MoveCamera(void);
	void SetTargetPos(Vector2F pPos);

private:

	static Camera* instance_;

	Vector2F pos_;
	Vector2F targetPos_;

	Camera(void);	//コンストラクタ
	~Camera(void);	//デストラクタ
};

