#pragma once

class StageBase
{
public:
	StageBase(void);	//コンストラクタ
	virtual ~StageBase(void);	//デストラクタ

	virtual bool Init(void);	//初期化
	virtual void Update(void);	//更新
	virtual void Draw(void);	//描画
	virtual bool Release(void);	//解放
};