
/*!
@file Scene.cpp
@brief シーン実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{

	//--------------------------------------------------------------------------------------
	///	ゲームシーン
	//--------------------------------------------------------------------------------------
	void Scene::OnCreate(){
		try {
			//クリアする色を設定
			Col4 Col;
			Col.set(31.0f / 255.0f, 30.0f / 255.0f, 71.0f / 255.0f, 255.0f / 255.0f);
			SetClearColor(Col);
			//自分自身にイベントを送る
			//これにより各ステージやオブジェクトがCreate時にシーンにアクセスできる
			PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), L"ToTitleStage");
			CreateResourses();
			LoadStaticModelResources();
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
			{L"scarab.bmf",L"scarab"},
			{L"test.bmf",L"test"},
			{L"stage.bmf",L"stage"},
			{L"rock.bmf",L"rock"},
			{L"tree.bmf",L"tree"}
		

		};
		for (auto model : models) {
			wstring srtmodel = dataDir;
			auto staticModel = MeshResource::CreateStaticModelMesh(srtmodel, model.m_modelName);
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
		wstring strTexture = dataDir + L"trace.png";
		App::GetApp()->RegisterTexture(L"TRACE_TX", strTexture);
		strTexture = dataDir + L"sky.jpg";
		App::GetApp()->RegisterTexture(L"A_TX", strTexture);
		strTexture = dataDir + L"wall.jpg";
		App::GetApp()->RegisterTexture(L"WALL_TX", strTexture);
		strTexture = dataDir + L"Block_A.png";
		App::GetApp()->RegisterTexture(L"H_TX", strTexture);
		strTexture = dataDir + L"haikei.png";
		App::GetApp()->RegisterTexture(L"J_TX", strTexture);
		strTexture = dataDir + L"testClear.png";
		App::GetApp()->RegisterTexture(L"Cl_TX", strTexture);

	}


	Scene::~Scene() {
	}

	void Scene::OnEvent(const shared_ptr<Event>& event) {
		if (event->m_MsgStr == L"ToTitleStage") {
			//最初のアクティブステージの設定
			ResetActiveStage<TitleStage>();
		}
		else if (event->m_MsgStr == L"ToSerectStage") {
			ResetActiveStage<SerectStage>();
		}
		else if (event->m_MsgStr == L"ToGameStage") {
			ResetActiveStage<GameStage>();
		}
		else if (event->m_MsgStr == L"ToClearStage") {
			ResetActiveStage<ClearStage>();
		}

	}
	void Scene::SetScene(const shared_ptr<Event>&event,wstring name) {
			event->m_MsgStr = name;
			
	}



}
//end basecross
