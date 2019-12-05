/*!
@file ProjectShader.cpp
@brief プロジェクトで使用するシェーダー実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
//--------------------------------------------------------------------------------------
/// タイトル用ステージ実体
//--------------------------------------------------------------------------------------
	void TitleStage::CreateViewLight() {
		auto ptrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto ptrMyCamera = ObjectFactory::Create<MyCamera>();
		ptrView->SetCamera(ptrMyCamera);
		ptrMyCamera->SetEye(Vec3(0.0f, 5.0f, -5.0f));
		ptrMyCamera->SetAt(Vec3(0.0f, 0.0f, 0.0f));
		//マルチライトの作成
		auto ptrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		ptrMultiLight->SetDefaultLighting();
	}
	void TitleStage::GameSystemObj() {
		auto Clear = AddGameObject<StageClearObj>(Vec3(0.0f, 3.0f, 0.0f), Vec3(1.0f));
		//PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), L"ToGameStartScene");
	}
	void TitleStage::System() {
		auto Mauce = App::GetApp()->GetInputDevice().GetControlerVec();

	}
	void TitleStage::OnUpdate(){
		m_InputHandler.PushHandle(GetThis<TitleStage>());
	}
	void TitleStage::OnPushA() {
		auto ptrScene = App::GetApp()->GetScene<Scene>();
		PostEvent(0.0f, GetThis<ObjectInterface>(), ptrScene, L"ToSerectStage");
	}
	void TitleStage::OnPushB() {

	}

	void TitleStage::OnCreate() {
		try {
			//物理演算のオンオフ
			SetPhysicsActive(true);
			//ビューとライトの作成
			CreateViewLight();
			//クリアオブジェクト
			GameSystemObj();
		}
		catch (...) {
			throw;
		}
	}

//--------------------------------------------------------------------------------------
///クリア用ステージ実体
//--------------------------------------------------------------------------------------

	void ClearStage::CreateViewLight() {
		auto ptrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto ptrMyCamera = ObjectFactory::Create<MyCamera>();
		ptrView->SetCamera(ptrMyCamera);
		ptrMyCamera->SetEye(Vec3(0.0f, 5.0f, -5.0f));
		ptrMyCamera->SetAt(Vec3(0.0f, 0.0f, 0.0f));
		//マルチライトの作成
		auto ptrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		ptrMultiLight->SetDefaultLighting();
	}
	void ClearStage::GameSystemObj() {
		auto Clear = AddGameObject<StageClearObj>(Vec3(0.0f, 3.0f, 0.0f), Vec3(0.5f));
		//PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), L"ToGameStartScene");
	}
	void ClearStage::System() {
		auto Mauce = App::GetApp()->GetInputDevice().GetControlerVec();

	}
	void ClearStage::OnUpdate() {
		m_InputHandler.PushHandle(GetThis<ClearStage>());
	}
	void ClearStage::OnPushA() {
		auto ptrScene = App::GetApp()->GetScene<Scene>();
		PostEvent(0.0f, GetThis<ObjectInterface>(), ptrScene, L"ToTitleStage");
	}
	void ClearStage::OnPushB() {

	}

	void ClearStage::OnCreate() {
		try {
			//物理演算のオンオフ
			SetPhysicsActive(true);
			//ビューとライトの作成
			CreateViewLight();
			//クリアオブジェクト
			GameSystemObj();
		}
		catch (...) {
			throw;
		}
	}

//--------------------------------------------------------------------------------------
///セレクト用ステージ実体
//--------------------------------------------------------------------------------------

	void SerectStage::CreateViewLight() {
		auto ptrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto ptrMyCamera = ObjectFactory::Create<MyCamera>();
		ptrView->SetCamera(ptrMyCamera);
		ptrMyCamera->SetEye(Vec3(0.0f, 5.0f, -5.0f));
		ptrMyCamera->SetAt(Vec3(0.0f, 0.0f, 0.0f));
		//マルチライトの作成
		auto ptrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		ptrMultiLight->SetDefaultLighting();
	}

	//プレイヤ―の生成
	void SerectStage::CreatePlayer() {
		//プレーヤーの作成
		auto ptrPlayer = AddGameObject<Player>(Vec3(0.0f,1.0f,-5.0f));
		//シェア配列にプレイヤーを追加
		SetSharedGameObject(L"Player", ptrPlayer);
		ptrPlayer->AddTag(L"Player");
	}

	void SerectStage::CreateStage(){
		auto Grand = AddGameObject<FixedPsBox>(Vec3(30.0f, 1.0f, 30.0f), Quat(), Vec3(0.0f, -0.5f, 0.0f));
		Grand->AddTag(L"Grand");
	}
	void SerectStage::OnUpdate() {
		m_InputHandler.PushHandle(GetThis<SerectStage>());
	}
	void SerectStage::OnPushA() {
		auto ptrScene = App::GetApp()->GetScene<Scene>();
		PostEvent(0.0f, GetThis<ObjectInterface>(), ptrScene, L"ToGameStage");
	}
	void SerectStage::OnPushB() {

	}
	void SerectStage::OnCreateSrectObj() {
		CreateSharedObjectGroup(L"SerectObj");
		AddGameObject<StageSrectObj>(Vec3(-10.0f, 3.0f, -10.0f), Vec3(2.5f, 1.5f, 2.5f));
		AddGameObject<StageSrectObj>(Vec3(-10.0f, 3.0f, 0.0f), Vec3(2.5f, 1.5f, 2.5f));
		AddGameObject<StageSrectObj>(Vec3(0.0f, 3.0f, 0.0f), Vec3(2.5f, 1.5f, 2.5f));
		AddGameObject<StageSrectObj>(Vec3(5.0f, 3.0f, 0.0f), Vec3(2.5f, 1.5f, 2.5f));
		AddGameObject<StageSrectObj>(Vec3(10.0f, 3.0f, 0.0f), Vec3(2.5f, 1.5f, 2.5f));
		AddGameObject<StageSrectObj>(Vec3(10.0f, 3.0f, 10.0f), Vec3(2.5f, 1.5f, 2.5f));
	}




	void SerectStage::OnCreate() {
		try {
			//物理演算のオンオフ
			SetPhysicsActive(true);
			//ビューとライトの作成
			CreateViewLight();
			//ステージの生成
			CreateStage();
			//プレイヤーの生成
			CreatePlayer();
			//ステージセレクトオブジェクトの生成
			OnCreateSrectObj();
		}
		catch (...) {
			throw;
		}
	}

//--------------------------------------------------------------------------------------
///ゲームオーバー用ステージ実体
//--------------------------------------------------------------------------------------

	void GameOverStage::CreateViewLight() {
		auto ptrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto ptrMyCamera = ObjectFactory::Create<MyCamera>();
		ptrView->SetCamera(ptrMyCamera);
		ptrMyCamera->SetEye(Vec3(0.0f, 5.0f, -5.0f));
		ptrMyCamera->SetAt(Vec3(0.0f, 0.0f, 0.0f));
		//マルチライトの作成
		auto ptrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		ptrMultiLight->SetDefaultLighting();
	}

	void GameOverStage::CreateStage() {
		AddGameObject<FixedPsBox>(Vec3(30.0f, 1.0f, 30.0f), Quat(), Vec3(0.0f, -0.5f, 0.0f));
	}
	void GameOverStage::OnUpdate() {
		m_InputHandler.PushHandle(GetThis<GameOverStage>());
	}
	void GameOverStage::OnPushA() {
		auto ptrScene = App::GetApp()->GetScene<Scene>();
		PostEvent(0.0f, GetThis<ObjectInterface>(), ptrScene, L"ToOverStage");
	}
	void GameOverStage::OnPushB() {

	}

	void GameOverStage::OnCreate() {
		try {
			//物理演算のオンオフ
			SetPhysicsActive(true);
			//ビューとライトの作成
			CreateViewLight();
			//ステージの生成
			CreateStage();
		}
		catch (...) {
			throw;
		}
	}

}



//end basecross
//11/22の俺へ
//お前はいまどんな気持ちでこれを読んでいるのかはわからないが
//きっとこれをお前が呼んでいる時俺はきっともうこの世にはいないだろう
//だが、今のお前に必要だと思いこの文章を残す。
//11/22にお前がやるべきことは
//・その他諸所必要なものの実装
//主にこの3つだ、余裕があれば
//・カメラのスタートからゴールへのカメラの移動
//・うんコインの自動生成
//・うんコインとった時の糞の大きさ調整と速度調整
//もやっておくときっと楽になるだろう
//チームメンバーはごみなので役に立たないだろうから敵の実装ももしかしたらやる羽目になるかもな・・・ﾊﾊｯ
//さぁこれを読んだ俺よ、誰の力を借りてもいいからこれらを11/22に実装しろ
//さすればお前は救われるかもしれない
//									過去の俺から






