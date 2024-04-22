#pragma once
#include<vector>
#include<list>
#include<fstream>
#include<sstream>
#include<string>
#include<map>

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
	void LoadPazzle(void);			//盤面の読み込み
	void CreateKey(int y, int x);	//連想配列のキー生成

private:
	std::map<std::string, RoomBase*> roomMng_;	//部屋の情報一括管理
	std::string roomKey_;	//連想配列のキー


	std::vector<int>pzlX_;
	std::vector<std::vector<int>>pzlMap_;	//パズルの置き場情報を数字で管理

protected:

	//テスト用
	//std::string testName_;
};