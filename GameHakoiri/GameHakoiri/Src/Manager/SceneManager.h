//#pragma once

//前方宣言
class Fader;
class SceneBase;

class SceneManager
{
public:
	//列挙型
	//シーン管理
	enum class SCENEID
	{
		NONE
		, TITLE
		, SELECT
		, GAME
		, RESULT
		, ENDING
		, MAX
	};
	
	
	//メンバ関数
	bool Init(void);	//初期化
	void Update(void);	//更新
	void Draw(void);	//描画
	bool Release(void);	//解放

	void ChangeScene(SCENEID,bool);		//シーン切り替え(フェード有り)

	void SetStageNum(int);		//ステージナンバーの保管
	int GetStageNum(void);		//ステージナンバーの譲渡

	//シングルトン化
	static bool CreateInstance(void);	//外部から静的インスタンスを生成
	static SceneManager& GetInstance(void);	//インスタンスの取得
	

private:
	SCENEID sceneID_;	//シーン切り替え
	SCENEID nextSceneID_;	//次のシーンを保持
	
	bool isChangeScene_;	//シーン切り替え用の論理型

	//インスタンスの動的確保
	SceneBase* scene_;	//シーン遷移
	Fader* fader_;	//フェード


	int stageNum_;	//選択したステージナンバー保存用

	//メンバ関数
	void DoChangeScene(void);		//シーン切り替え(フェードなし)
	void Fade(void);	//フェード実施用関数
	void ReleaseScene(SCENEID);	//シーンの解放

	//シングルトン化
	SceneManager(void);	//コンストラクタ
	SceneManager(const SceneManager&);	//コピーコンストラクタ
	void Destroy(void);	//デストラクタ

	static SceneManager* instance_;	//実態を確保
};