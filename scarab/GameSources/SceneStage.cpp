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
	void TitleStage::CreateTitleSprite() {
		float size = 0.4;
		auto titlecaharaLogo = AddGameObject<Sprite>(L"TITLELOGO_TX", true,
			Vec2(795.0f * size, 338.0f * size), Vec3(50.0f, 200.0f, 0.0f));
		//auto titlebackLogo = AddGameObject<Sprite>(L"TITLEBACK_TX", true,
		//	Vec2(640.0f, 720.0f), Vec3(0.0f, 0.0f, 0.1f));
		auto startLogo = AddGameObject<Sprite>(L"GAMESTART_TX", true,
			Vec2(150.0f, 30.0f), Vec3(0.0f, -150.0f, 0.1f));
		SetSharedGameObject(L"StartLogo", startLogo);

		auto endLogo = AddGameObject<Sprite>(L"GAMEEND_TX", true,
			Vec2(150.0f, 30.0f), Vec3(0.0f, -280.0f, 0.1f));
		SetSharedGameObject(L"EndLogo", endLogo);

		auto cursor = AddGameObject<Sprite>(L"ICON_TX", true,
			Vec2(27.0f, 27.0f), Vec3(150.0f, -150.0f, 0.1f));
		SetSharedGameObject(L"Cousor", cursor);
	}
	void TitleStage::GameSystemObj() {
		auto Clear = AddGameObject<StageClearObj>(Vec3(0.0f, 3.0f, 0.0f), Vec3(1.0f));
		//PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), L"ToGameStartScene");
	}
	void TitleStage::System() {
		auto Mauce = App::GetApp()->GetInputDevice().GetControlerVec();

	}
	void TitleStage::OnUpdate() {
		;
		m_InputHandler.PushHandle(GetThis<TitleStage>());
		auto cursor = GetSharedGameObject<Sprite>(L"Cousor");
		auto cursorComp = cursor->GetComponent<Transform>();
		auto cursorPos = cursorComp->GetPosition();
		if (m_cursornum == 0) {
			cursorPos.y = -150.f;
		}
		else if (m_cursornum == 1) {
			cursorPos.y = -280.0f;
		}
		cursorComp->SetPosition(cursorPos);
	}
	void TitleStage::OnPushA() {
		if (m_cursornum == 0) {
			auto ptrScene = App::GetApp()->GetScene<Scene>();
			PostEvent(0.0f, GetThis<ObjectInterface>(), ptrScene, L"ToSerectStage");
		}
		else if (m_cursornum == 1) {
			DestroyWindow(App::GetApp()->GetHWnd());
		}

	}
	void TitleStage::OnPushUP() {
		if (m_cursornum == 0) {
			m_cursornum = 1;
		}
		else if (m_cursornum == 1) {
			m_cursornum = 0;
		}
	}
	void TitleStage::OnPushDOWN() {
		if (m_cursornum == 0) {
			m_cursornum = 1;
		}
		else if (m_cursornum == 1) {
			m_cursornum = 0;
		}
	}

	void TitleStage::OnCreate() {
		try {
			CreateTitleSprite();
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

	void ClearStage::CreateClearSprite() {
		//auto titlebackLogo = AddGameObject<Sprite>(L"TITLEBACK_TX", true,
		//	Vec2(640.0f, 480.0f), Vec3(0.0f, 0.0f, 0.1f));
		//クリアの文字
		auto clear = AddGameObject<Sprite>(L"CLEAR_TX", true,
			Vec2(250.0f, 70.0f), Vec3(0.0f, 300.0f, 0.0f));

		auto gm = GameManager::GetInstance();

		for (int h = 0; h < 1; h++) {
			gm->UnkoNumUp();
		}

		int unkonum = gm->GetUnkoNum();
		Vec3 pos = Vec3(-120.f, 140.f, 0.f);

		int num = 4;

		for (int i = 0; i < unkonum; i++) {
			auto unkosp = AddGameObject<Sprite>(L"UNKOIKON_TX", true,
				Vec2(50, 50), Vec3(pos));
			 pos.x += 60.0f;
			 if ( i == num ) {
				 num += 5;
				 pos = Vec3( -120.0f, pos.y -=70.0f, 0.0f);
			 }
		}





		////スコア
		//auto ptrScore = AddGameObject<ScoreSprite>(3,
		//	L"NUMBER_TX",
		//	true,
		//	Vec2(400.0f, 120.0f), Vec3(0.0f, 200.0f, 0.1f));

		//ptrScore->SetScore(GameManager::GetInstance()->GetUnkoNum());

		//位置と文字の間隔の設定
		m_strSprite = m_sprite = -30.0f;
		m_spriteif = -90.0f;
		//次のステージ
		auto nextStageLogo = AddGameObject<Sprite>(L"NEXTSTAGE_TX", true,
			Vec2(150.0f, 30.0f), Vec3(0.0f, m_sprite, 0.1f));
		SetSharedGameObject(L"NextStageLogo", nextStageLogo);
		//リトライ
		auto oneMoreLogo = AddGameObject<Sprite>(L"RETRY_TX", true,
			Vec2(150.0f, 30.0f), Vec3(0.0f, m_sprite = m_sprite + m_spriteif, 0.1f));
		SetSharedGameObject(L"OneMoreLogo", oneMoreLogo);
		//ステージセレクト画面
		auto stageSelectLogoa = AddGameObject<Sprite>(L"STAGESELECT_TX", true,
			Vec2(150.0f, 30.0f), Vec3(0.0f, m_sprite = m_sprite + m_spriteif, 0.1f));
		SetSharedGameObject(L"StageSelectLogoa", stageSelectLogoa);
		//スタート画面
		auto startLogo = AddGameObject<Sprite>(L"TITLE_TX", true,
			Vec2(150.0f, 30.0f), Vec3(0.0f, m_sprite = m_sprite + m_spriteif, 0.1f));
		SetSharedGameObject(L"StartLogo", startLogo);

		//カーソルのアイコン
		auto cursor = AddGameObject<Sprite>(L"ICON_TX", true,
			Vec2(35.0f, 35.0f), Vec3(170.0f, -150.0f, 0.1f));
		SetSharedGameObject(L"Cousor", cursor);
	}

	void ClearStage::GameSystemObj() {
		auto Clear = AddGameObject<StageClearObj>(Vec3(0.0f, 3.0f, 0.0f), Vec3(0.5f));
		//PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), L"ToGameStartScene");
	}

	void ClearStage::System() {
		auto Mauce = App::GetApp()->GetInputDevice().GetControlerVec();

	}

	void ClearStage::OnUpdate() {
		//コントロ―ラーの取得
		m_InputHandler.PushHandle(GetThis<ClearStage>());
		//アイコンの移動
		auto cursor = GetSharedGameObject<Sprite>(L"Cousor");
		auto cursorComp = cursor->GetComponent<Transform>();
		auto cursorPos = cursorComp->GetPosition();
		cursorPos.y = m_strSprite + m_spriteif * m_cursornum;;
		cursorComp->SetPosition(cursorPos);


	}

	void ClearStage::OnPushA() {
		if (m_cursornum == 0) {
			auto ptrScene = App::GetApp()->GetScene<Scene>();
			PostEvent(0.0f, GetThis<ObjectInterface>(), ptrScene, L"ToTitleStage");
		}
		else if (m_cursornum == 1) {
			auto ptrScene = App::GetApp()->GetScene<Scene>();
			PostEvent(0.0f, GetThis<ObjectInterface>(), ptrScene, L"ToSerectStage");
		}
		else if (m_cursornum == 2) {
			auto ptrScene = App::GetApp()->GetScene<Scene>();
			PostEvent(0.0f, GetThis<ObjectInterface>(), ptrScene, L"ToGameStage");
		}
		else if (m_cursornum == 3) {
			auto ptrScene = App::GetApp()->GetScene<Scene>();
			PostEvent(0.0f, GetThis<ObjectInterface>(), ptrScene, L"ToTitleStage");
		}
	}

	void ClearStage::OnPushUP() {
		m_cursornum -= 1;
		if (m_cursornum == -1) {
			m_cursornum = 3;
		}
	}

	void ClearStage::OnPushDOWN() {
		m_cursornum += 1;
		if (m_cursornum == 4) {
			m_cursornum = 0;
		}
	}

	void ClearStage::OnCreate() {
		try {
			CreateClearSprite();
			//物理演算のオンオフ
			SetPhysicsActive(true);
			//ビューとライトの作成
			CreateViewLight();
			//クリアオブジェクト
			//GameSystemObj();
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
		auto ptrPlayer = AddGameObject<Player>(Vec3(0.0f, 1.0f, -5.0f));
		//シェア配列にプレイヤーを追加
		SetSharedGameObject(L"Player", ptrPlayer);
		ptrPlayer->AddTag(L"Player");
	}


	void SerectStage::CreateStage(){
		auto Grand = AddGameObject<FixedBox>(Vec3(0.0f, -0.5f, 0.0f), Vec3(30.0f, 1.0f, 30.0f));
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
		AddGameObject<StageSrectObj>(Vec3(-9.0f, 3.0f, -9.0f), Vec3(1.5f, 1.5f, 1.5f));
		AddGameObject<StageSrectObj>(Vec3(-1.0f, 3.0f, -1.0f), Vec3(1.5f, 1.5f, 1.5f));
		AddGameObject<StageSrectObj>(Vec3(6.5f, 3.0f, 9.0f), Vec3(1.5f, 1.5f, 1.5f));

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
		AddGameObject<Sprite>(L"GAMEOVER_SCARAB_TX", true,
			Vec2(640.0f, 480.0f), Vec3(0.0f, 0.0f, 0.1f));
		//位置と文字の間隔の設定
		m_strSprite = m_sprite = -30.0f;
		m_spriteif = -90.0f;
		//次のステージ
		auto nextStageLogo = AddGameObject<Sprite>(L"NEXTSTAGE_TX", true,
			Vec2(150.0f, 30.0f), Vec3(0.0f, m_sprite, 0.1f));
		SetSharedGameObject(L"NextStageLogo", nextStageLogo);
		//リトライ
		auto oneMoreLogo = AddGameObject<Sprite>(L"RETRY_TX", true,
			Vec2(150.0f, 30.0f), Vec3(0.0f, m_sprite = m_sprite + m_spriteif, 0.1f));
		SetSharedGameObject(L"OneMoreLogo", oneMoreLogo);
		//ステージセレクト画面
		auto stageSelectLogoa = AddGameObject<Sprite>(L"STAGESELECT_TX", true,
			Vec2(150.0f, 30.0f), Vec3(0.0f, m_sprite = m_sprite + m_spriteif, 0.1f));
		SetSharedGameObject(L"StageSelectLogoa", stageSelectLogoa);
		//スタート画面
		auto startLogo = AddGameObject<Sprite>(L"TITLE_TX", true,
			Vec2(150.0f, 30.0f), Vec3(0.0f, m_sprite = m_sprite + m_spriteif, 0.1f));
		SetSharedGameObject(L"StartLogo", startLogo);

		//カーソルのアイコン
		auto cursor = AddGameObject<Sprite>(L"ICON_TX", true,
			Vec2(35.0f, 35.0f), Vec3(170.0f, 0.0f, 0.1f));
		SetSharedGameObject(L"Cousor", cursor);
		//AddGameObject<FixedPsBox>(Vec3(30.0f, 1.0f, 30.0f), Quat(), Vec3(0.0f, -0.5f, 0.0f));
	}
	void GameOverStage::OnUpdate() {
		m_InputHandler.PushHandle(GetThis<GameOverStage>());
		//アイコンの移動
		auto cursor = GetSharedGameObject<Sprite>(L"Cousor");
		auto cursorComp = cursor->GetComponent<Transform>();
		auto cursorPos = cursorComp->GetPosition();
		cursorPos.y = m_strSprite + m_spriteif * m_cursornum;;
		cursorComp->SetPosition(cursorPos);
	}

	void GameOverStage::OnPushA() {
		//auto ptrScene = App::GetApp()->GetScene<Scene>();
		//PostEvent(0.0f, GetThis<ObjectInterface>(), ptrScene, L"ToOverStage");
		if (m_cursornum == 0) {
			auto ptrScene = App::GetApp()->GetScene<Scene>();
			PostEvent(0.0f, GetThis<ObjectInterface>(), ptrScene, L"ToTitleStage");
		}
		else if (m_cursornum == 1) {
			auto ptrScene = App::GetApp()->GetScene<Scene>();
			PostEvent(0.0f, GetThis<ObjectInterface>(), ptrScene, L"ToSerectStage");
		}
		else if (m_cursornum == 2) {
			auto ptrScene = App::GetApp()->GetScene<Scene>();
			PostEvent(0.0f, GetThis<ObjectInterface>(), ptrScene, L"ToGameStage");
		}
		else if (m_cursornum == 3) {
			auto ptrScene = App::GetApp()->GetScene<Scene>();
			PostEvent(0.0f, GetThis<ObjectInterface>(), ptrScene, L"ToTitleStage");
		}
	}
	void GameOverStage::OnPushB() {

	}
	void GameOverStage::OnPushUP() {
		m_cursornum -= 1;
		if (m_cursornum == -1) {
			m_cursornum = 3;
		}
	}

	void GameOverStage::OnPushDOWN() {
		m_cursornum += 1;
		if (m_cursornum == 4) {
			m_cursornum = 0;
		}
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








