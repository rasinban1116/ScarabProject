/*!
@file GameStage.h
@brief ゲームステージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス
	//--------------------------------------------------------------------------------------
	class GameStage : public Stage {
		//ビューの作成
		void CreateViewLight();
		//MyCamera用のビュー
		shared_ptr<SingleView> m_MyCameraView;
		//CSVファイルそのA
		CsvFile m_GameStageCsvA;
		//CSVファイルそのB
		CsvFile m_GameStageCsvB;
		//固定のボックスの作成
		void CreateFixedBox();
		//固定の傾いたボックスの作成
		void CreateBox();
		//プレイヤーの作成
		void CreatePlayer();
		//敵の作成
		void CreateLowEnemy();;
		//プレイヤーを継承した子オブジェクトの継承
		void CreatePlayerChild();
		//ゲームクリア用のオブジェクト作成
		void CreateClearObj();
		//空の作成
		void CreateSky();
		//UIの表示
		void CreateUI();
		void GameSystemObj();

	public:
		//構築と破棄
		GameStage() :Stage() {}
		virtual ~GameStage() {}
		//初期化
		virtual void OnCreate()override;
	};


}
//end basecross

