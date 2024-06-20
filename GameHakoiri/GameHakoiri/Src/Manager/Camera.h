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

	void SetTargetPos(const Position pPos);
	void SetMapSize(const Position mapsize);
	Position GetPos(void)const;

private:

	static Camera* instance_;

	Position pos_;
	Position localCenterPos_;
	Position targetPos_;
	Position mapSize_;

	void MoveCamera(void);

	Camera(void);	//コンストラクタ
	~Camera(void);	//デストラクタ
};

