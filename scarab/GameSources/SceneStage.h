/*!
@file SceneStage.h
@brief シーン用のゲームステージ群
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	///	タイトル用ステージ
	//--------------------------------------------------------------------------------------
	class TitleStage :public Stage {
		//ビューの作成
		void CreateViewLight();
		void GameSystemObj();
		void System();
		int m_cursornum;
		bool m_CntrolLock;
		bool m_txflg;
		InputHandler<TitleStage> m_InputHandler;	//入力ハンドラー

	public:
		//構築と破棄
		TitleStage() :Stage() {}
		virtual ~TitleStage() {}
		//初期化
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		void CreateTitleSprite();
		void ControlStick();
		void OnPushA();
		void OnPushB() {}
	};
	//--------------------------------------------------------------------------------------
	///　ステージクリア用ステージ
	//--------------------------------------------------------------------------------------
	class ClearStage :public Stage {
		bool m_CntrolLock;
		//ビューの作成
		void CreateViewLight();
		void GameSystemObj();
		void System();
		int m_cursornum;
		float m_strSprite;
		float m_sprite;
		float m_spriteif;
		float m_txpos;
		bool m_txflg;
		InputHandler<ClearStage> m_InputHandler;	//入力ハンドラー

	public:
		//構築と破棄
		ClearStage() :Stage() {}
		virtual ~ClearStage() {}
		//初期化
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		void CreateClearSprite();
		void ControlStick();
		void OnPushA();
		void OnPushB() {}
	};

	//--------------------------------------------------------------------------------------
	///　ステージセレクト用ステージ
	//--------------------------------------------------------------------------------------
	class SerectStage :public Stage {
		bool m_CntrolLock;
		//ビューの作成
		void CreateViewLight();
		void CreateStage();
		InputHandler<SerectStage> m_InputHandler;	//入力ハンドラー
	public:
		//構築と破棄
		SerectStage() :Stage() {}
		virtual ~SerectStage() {}
		//初期化
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		void CreatePlayer();
		void ControlStick();
		void OnPushA();
		void OnPushB();
		void OnCreateSrectObj();
	};

	//--------------------------------------------------------------------------------------
	///　ゲームオーバー用ステージ
	//--------------------------------------------------------------------------------------
	class GameOverStage :public Stage {
		//ビューの作成
		void CreateViewLight();
		void CreateStage();
		InputHandler<GameOverStage> m_InputHandler;	//入力ハンドラー
		int m_cursornum;
		float m_strSprite;
		float m_sprite;
		float m_spriteif;
		bool m_CntrolLock;
	public:
		//構築と破棄
		GameOverStage() :Stage() {}
		virtual ~GameOverStage() {}
		//初期化
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		void ControlStick();
		void OnPushA();
		void OnPushB();
	};
}
//end basecross

