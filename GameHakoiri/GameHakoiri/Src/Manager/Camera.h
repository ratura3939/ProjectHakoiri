#pragma once
class Camera
{
public:
	void CreateInstance(void);
	Camera& GetInstance(void);
	
	void Init(void);
	void Update(void);
	void Draw(void);
	void Relese(void);

private:
	Camera(void);	//コンストラクタ
	~Camera(void);	//デストラクタ
};

