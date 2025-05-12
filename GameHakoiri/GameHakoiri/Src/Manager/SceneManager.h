#pragma once
#include<memory>
#include"../Scene/GameScene.h"

//前方宣言
class Fader;
class SceneBase;
class Camera;

class SceneManager
{
public:
	//列挙型
	/// <summary>
	/// シーン管理
	/// </summary>
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
	
	/// <summary>
	/// コントローラー
	/// </summary>
	enum class CONTROLLER
	{
		KEYBOARD,
		PAD,
		MAX
	};

	//定数
	static constexpr int STAGE_ALL = 3;
	

	//シングルトン化
	static bool CreateInstance(void);	//外部から静的インスタンスを生成
	static SceneManager& GetInstance(void);	//インスタンスの取得

private:
	SceneManager(Camera& _camera);	//コンストラクタ
	
public:
	void Destroy(void);	//デストラクタ
	bool Init(void);	//初期化
	void Update(void);	//更新
	void Draw(void);	//描画
	bool Release(void);	//解放


	// カメラの取得
	Camera& GetCamera(void) const;

#pragma region シーン管理
public:
	/// <summary>
	/// シーン切り換え受付
	/// </summary>
	/// <param name="next">切り替え後</param>
	/// <param name="isToFade">true=フェードする/false=フェードしない</param>
	void ChangeScene(const SCENEID next, const bool isToFade);

private:
	/// <summary>
	/// シーン切り換え
	/// </summary>
	void DoChangeScene(void);

	/// <summary>
	/// フェード
	/// </summary>
	/// <param name=""></param>
	void Fade(void);

	/// <summary>
	/// シーンの解放
	/// </summary>
	/// <param name="sceneID">解放するシーン</param>
	void ReleaseScene(const SCENEID sceneID);

	/// <summary>
	/// シーン変更フラグ設定
	/// </summary>
	/// <param name="flag">true=変更中/false=変更していない</param>
	void SetChangeScene(const bool flag);
#pragma endregion



#pragma region 他シーンに移行すべき情報類
public:
	//ステージ番号
	/// <summary>
	/// 設定
	/// </summary>
	/// <param name="">番号</param>
	void SetStageNum(const int);

	/// <summary>
	/// 取得
	/// </summary>
	/// <returns>ステージ番号</returns>
	const int GetStageNum(void)const;

	//コントローラー
	/// <summary>
	/// 設定
	/// </summary>
	/// <param name="cnt">コントローラー</param>
	void SetController(const CONTROLLER cnt);

	/// <summary>
	/// 現在とは違う片方に変更
	/// </summary>
	void ChangeController(void);

	/// <summary>
	/// 取得
	/// </summary>
	/// <returns>コントローラー</returns>
	const CONTROLLER GetController(void)const;

#pragma endregion

#pragma region クリア関係
public:
	void ClearStage(const int stageNum);
	const bool IsClearStage(const int stageNum)const;
	const bool IsClearStageNow(void)const;
	const bool CheckAllClear(void)const;

	void SetManual(const GameScene::MODE mode);
	void Reset(void);
	void CustomClearFlag(int num);
#pragma endregion


private:
	SCENEID sceneID_;		//シーン切り替え
	SCENEID nextSceneID_;	//次のシーンを保持
	CONTROLLER controller_;	//使用中のコントローラーを保持
	
	bool isChangeScene_;	//シーン切り替え用の論理型

	//インスタンスの動的確保
	SceneBase* scene_;				//シーン遷移
	std::unique_ptr<Fader> fader_;	//フェード
	Camera& camera_;				//カメラ

	int stageNum_;					//選択したステージナンバー保存用
	bool clearStage_[STAGE_ALL];	//クリアしたステージを保存

	//マニュアル関係
	bool isManual_;												//マニュアルを出すかどうか
	bool firstManual_[static_cast<int>(GameScene::MODE::MAX)];	//最初の操作説明

	static SceneManager* instance_;	//実態を確保
};