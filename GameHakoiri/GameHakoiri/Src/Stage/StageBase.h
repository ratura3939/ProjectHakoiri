#pragma once
#include<vector>
#include<list>

//StageBaseは各ステージの情報置き場という認識

class RoomBase;

class StageBase
{
public:

	//列挙型
	enum class STAGENUM
	{
		TUTORIAL
		, FIRST
		, SECOND
		, THIRD
		, MAX
	};

	StageBase(void);	//コンストラクタ
	virtual ~StageBase(void);	//デストラクタ

	virtual bool Init(void);	//初期化
	virtual void Update(void);	//更新
	virtual void Draw(void);	//描画
	virtual bool Release(void);	//解放


	virtual void SetParam(void);	//部屋ごとのパラメータ設定

private:
	std::vector<RoomBase*> rooms_;	//部屋の動的管理

protected:

	//テスト用
	int test_[5];
};