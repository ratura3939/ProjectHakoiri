//#pragma once
class Pazzle
{
public:
	Pazzle(void);	//コンストラクタ
	virtual ~Pazzle(void);	//デストラクタ

	virtual bool Init(void);	//初期化
	virtual void Update(void);	//更新
	virtual void Draw(void);	//描画
	virtual bool Release(void);	//解放
};

