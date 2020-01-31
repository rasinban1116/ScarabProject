
/*!
@file Scene.cpp
@brief シーン実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	GameManager* GameManager::GM = nullptr;
	GameManager* GameManager::GetInstance() {
		if (GM == nullptr) {
			GM = new GameManager();
		}
		return GM;
	}

	//--------------------------------------------------------------------------------------
	///	ゲームシーン
	//--------------------------------------------------------------------------------------
	void Scene::OnCreate(){
		
		try {
			//クリアする色を設定
			Col4 Col;
			Col.set(1.0f / 255.0f, 30.0f / 255.0f, 71.0f / 255.0f, 255.0f / 255.0f);
			//Col.set(BACKGROUND_RED,BACKGROUND_GREEN,BACKGROUND_BLUE,BACKGROUND_INTENSITY);
			SetClearColor(Col);
			
			//自分自身にイベントを送る
			//これにより各ステージやオブジェクトがCreate時にシーンにアクセスできる
			PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), L"ToTitleStage");
			
			CreateResourses();
			LoadStaticModelResources();
			LoadStaticBornModelResources();
			LoadMaltiModelResources();
		}
		catch (...) {
			throw;
		}
	}

/// ---------------------------------------------------------------------------<summary>
/// スタティックモデルの読み込み(引数なし)
/// </summary>----------------------------------------------------------------------------
	void Scene::LoadStaticModelResources() {
		wstring dataDir;
		App::GetApp()->GetDataDirectory(dataDir);
		struct InitializedParam {
			wstring m_modelName;
			wstring m_modelKey;
		};
		InitializedParam models[] = {
			//{L"ファイル名",L"呼び出し時のキー"}
			{L"scarabtest.bmf",L"scarab"},
			{L"stage.bmf",L"stage"},
			{L"poop.bmf",L"unko"},
			{L"Base.bmf",L"Base"},
			{L"falltree.bmf",L"fallntree"},
			{L"lizard.bmf",L"liz"},
			{L"Goal_point.bmf",L"Goal"},
			{L"Stage_Tree.bmf",L"tree"},
			{L"StsgeRock.bmf",L"Rock"},

		

		};
		for (auto model : models) {
			wstring srtmodel = dataDir;
			auto staticModel = MeshResource::CreateStaticModelMesh(srtmodel, model.m_modelName);
			//auto malti = MeshResource::CreateMeshResource(strmodel, model._modelName);
			App::GetApp()->RegisterResource(model.m_modelKey, staticModel);
		}
	}

	/// ---------------------------------------------------------------------------<summary>
/// スタティックモデルの読み込み(引数なし)
/// </summary>----------------------------------------------------------------------------
	void Scene::LoadStaticBornModelResources() {
		wstring dataDir;
		App::GetApp()->GetDataDirectory(dataDir);
		struct InitializedParam {
			wstring m_modelName;
			wstring m_modelKey;
		};
		InitializedParam models[] = {
			//{L"ファイル名",L"呼び出し時のキー"}
			{L"Scarab_Enemy_Walking.bmf",L"Enemy"},
			{L"Lizard_Waik.bmf",L"Lizad"},
		};
		for (auto model : models) {
			wstring srtmodel = dataDir;
			auto staticModel = MeshResource::CreateBoneModelMesh(srtmodel, model.m_modelName);

			App::GetApp()->RegisterResource(model.m_modelKey, staticModel);
		}
	}
	void Scene::LoadMaltiModelResources()
	{
		wstring dataDir;
		App::GetApp()->GetDataDirectory(dataDir);
		struct InitializedParam {
			wstring m_modelName;
			wstring m_modelKey;
		};
		InitializedParam models[] = {
			//{L"ファイル名",L"呼び出し時のキー"}
			{L"ScarabOnPoop_Walking.bmf",L"scrab"},
			{L"Scarab_Walking.bmf",L"PlayWalk"}


		};
		for (auto model : models) {
			wstring srtmodel = dataDir;
			auto staticModel = MultiMeshResource::CreateBoneModelMultiMesh(srtmodel, model.m_modelName);
			App::GetApp()->RegisterResource(model.m_modelKey, staticModel);
		}
	}
	


	void Scene::CreateResourses() {
		wstring dataDir;
		auto play = shared_ptr<BaseResource>();
		//サンプルのためアセットディレクトリを取得
		App::GetApp()->GetAssetsDirectory(dataDir);
		//各ゲームは以下のようにデータディレクトリを取得すべき
		App::GetApp()->GetDataDirectory(dataDir);
		
		//ステージオブジェクト＆プレイヤー・エネミー用テクスチャ
		wstring strTexture = dataDir + L"trace.png";
		App::GetApp()->RegisterTexture(L"TRACE_TX", strTexture);
		strTexture = dataDir + L"sky.jpg";
		App::GetApp()->RegisterTexture(L"A_TX", strTexture);
		strTexture = dataDir + L"Grand.png";
		App::GetApp()->RegisterTexture(L"WALL_TX", strTexture);
		strTexture = dataDir + L"Block_A.png";
		App::GetApp()->RegisterTexture(L"H_TX", strTexture);
		strTexture = dataDir + L"haikei.png";
		App::GetApp()->RegisterTexture(L"J_TX", strTexture);
		strTexture = dataDir + L"Weed.png";
		App::GetApp()->RegisterTexture(L"Cl_TX", strTexture);
		strTexture = dataDir + L"UV_Scarab.tga";
		App::GetApp()->RegisterTexture(L"KUSA_TX", strTexture);
		strTexture = dataDir + L"Tx_Ball_poop.png";
		App::GetApp()->RegisterTexture(L"UNKO_TX", strTexture);
		strTexture = dataDir + L"UV_Scarab_Enemy.png";
		App::GetApp()->RegisterTexture(L"SCARAB_TX", strTexture);
		strTexture = dataDir + L"Stage_Select.png";
		App::GetApp()->RegisterTexture(L"SERECT_TX", strTexture);
		strTexture = dataDir + L"Tx_Stage_tree.png";
		App::GetApp()->RegisterTexture(L"Tree_TX", strTexture);
		strTexture = dataDir + L"Tx_Stage_Rock.png";
		App::GetApp()->RegisterTexture(L"Rock_TX", strTexture);

		strTexture = dataDir + L"Tx_Lizard.png";
		App::GetApp()->RegisterTexture(L"Lizad_TX", strTexture);
		//UIやスコア表示用のテクスチャ
		strTexture = dataDir + L"clear.png";
		App::GetApp()->RegisterTexture(L"CLEAR_TX", strTexture);
		strTexture = dataDir + L"nextstage.png";
		App::GetApp()->RegisterTexture(L"NEXTSTAGE_TX", strTexture);
		strTexture = dataDir + L"gamestart.png";
		App::GetApp()->RegisterTexture(L"GAMESTART_TX", strTexture);
		strTexture = dataDir + L"gameend.png";
		App::GetApp()->RegisterTexture(L"GAMEEND_TX", strTexture);
		strTexture = dataDir + L"title.png";
		App::GetApp()->RegisterTexture(L"TITLE_TX", strTexture);
		strTexture = dataDir + L"stageselect.png";
		App::GetApp()->RegisterTexture(L"STAGESELECT_TX", strTexture);
		strTexture = dataDir + L"retry.png";
		App::GetApp()->RegisterTexture(L"RETRY_TX", strTexture);
		strTexture = dataDir + L"titlelogo.png";
		App::GetApp()->RegisterTexture(L"TITLELOGO_TX", strTexture);
		strTexture = dataDir + L"poop_cursor.png";
		App::GetApp()->RegisterTexture(L"ICON_TX", strTexture);
		strTexture = dataDir + L"Cloud_1.png";
		App::GetApp()->RegisterTexture(L"SKY_TX", strTexture);
		strTexture = dataDir + L"Ball_poop_Tx.png";
		App::GetApp()->RegisterTexture(L"POOP_TX", strTexture);
		strTexture = dataDir + L"Game_over_enemy_Scarab.png";
		App::GetApp()->RegisterTexture(L"GAMEOVER_SCARAB_TX", strTexture);
		strTexture = dataDir + L"number.png";
		App::GetApp()->RegisterTexture(L"NUMBER_TX", strTexture);
		strTexture = dataDir + L"Poop_Icon.png";
		App::GetApp()->RegisterTexture(L"UNKOIKON_TX", strTexture);
		strTexture = dataDir + L"Game_Clear_Scarab.png";
		App::GetApp()->RegisterTexture(L"CLEARBACK_TX", strTexture);
		strTexture = dataDir + L"Title_01.png";
		App::GetApp()->RegisterTexture(L"TITLEBACK_TX", strTexture);
		strTexture = dataDir + L"SeeneTrans.jpg";
		App::GetApp()->RegisterTexture(L"SEENE_TX", strTexture);

		

		//BGM用
		strTexture = dataDir + L"12098.mp3";
		App::GetApp()->RegisterWav(L"GAMESTAGEBGM", strTexture);

	}


	Scene::~Scene() {
	}

	void Scene::OnEvent(const shared_ptr<Event>& event) {
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		if (event->m_MsgStr == L"ToTitleStage") {
			//最初のアクティブステージの設定
			ResetActiveStage<TitleStage>();
		}
		else if (event->m_MsgStr == L"ToSerectStage") {
			XAPtr->Start(L"GAMESTAGEBGM", XAUDIO2_LOOP_INFINITE, 0.08);
			ResetActiveStage<SerectStage>();
		}
		else if (event->m_MsgStr == L"ToGameStage") {
			ResetActiveStage<GameStage>();
		}
		else if (event->m_MsgStr == L"ToClearStage") {
			ResetActiveStage<ClearStage>();
		}
		else if (event->m_MsgStr == L"ToGameOverStage") {
			ResetActiveStage<GameOverStage>();
		}

	}
	void Scene::SetScene(const shared_ptr<Event>&event,wstring name) {
			event->m_MsgStr = name;
			
	}



}
//end basecross
