#pragma once

#include"../Scene/GameScene.h"

//前方宣言
class Fader;
class SceneBase;
class Camera;

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
	

	//コントローラー
	enum class CONTROLLER
	{
		KEYBOARD,
		PAD,
		MAX
	};
	
	//メンバ関数
	bool Init(void);	//初期化
	void Update(void);	//更新
	void Draw(void);	//描画
	bool Release(void);	//解放

	void ChangeScene(SCENEID,bool);		//シーン切り替え(フェード有り)

	void SetStageNum(int);		//ステージナンバーの保管
	int GetStageNum(void);		//ステージナンバーの譲渡

	void SetController(CONTROLLER cnt);
	void ChangeController(void);	//コントローラーの切り替え
	CONTROLLER GetController(void)const;

	// カメラの取得
	Camera& GetCamera(void) const;

	//シングルトン化
	static bool CreateInstance(void);	//外部から静的インスタンスを生成
	static SceneManager& GetInstance(void);	//インスタンスの取得
	
	void ClearStage(int stageNum);
	bool IsClearStage(int stageNum);

	void SetManual(GameScene::MODE mode);
	void Reset(void);

private:
	SCENEID sceneID_;	//シーン切り替え
	SCENEID nextSceneID_;	//次のシーンを保持
	CONTROLLER controller_;	//使用中のコントローラーを保持
	
	bool isChangeScene_;	//シーン切り替え用の論理型

	//インスタンスの動的確保
	SceneBase* scene_;	//シーン遷移
	Fader* fader_;	//フェード
	Camera& camera_;	//カメラ


	int stageNum_;	//選択したステージナンバー保存用
	bool clearStage_[3];	//クリアしたステージを保存


	//マニュアル関係
	bool isManual_;	//マニュアルを出すかどうか
	bool firstManual_[static_cast<int>(GameScene::MODE::MAX)];

	//メンバ関数
	void DoChangeScene(void);		//シーン切り替え(フェードなし)
	void Fade(void);	//フェード実施用関数
	void ReleaseScene(SCENEID);	//シーンの解放

	void SetChangeScene(const bool flag);

	//シングルトン化
	SceneManager(Camera& _camera);	//コンストラクタ
	SceneManager(const SceneManager&, Camera& _camera);	//コピーコンストラクタ
	void Destroy(void);	//デストラクタ

	static SceneManager* instance_;	//実態を確保
};