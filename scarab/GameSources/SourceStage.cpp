/*!
@file ProjectShader.cpp
@brief �v���W�F�N�g�Ŏg�p����V�F�[�_�[����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
//--------------------------------------------------------------------------------------
/// �^�C�g���p�X�e�[�W����
//--------------------------------------------------------------------------------------
	void TitleStage::CreateViewLight() {
		auto ptrView = CreateView<SingleView>();
		//�r���[�̃J�����̐ݒ�
		auto ptrMyCamera = ObjectFactory::Create<MyCamera>();
		ptrView->SetCamera(ptrMyCamera);
		ptrMyCamera->SetEye(Vec3(0.0f, 5.0f, -5.0f));
		ptrMyCamera->SetAt(Vec3(0.0f, 0.0f, 0.0f));
		//�}���`���C�g�̍쐬
		auto ptrMultiLight = CreateLight<MultiLight>();
		//�f�t�H���g�̃��C�e�B���O���w��
		ptrMultiLight->SetDefaultLighting();
	}
	void TitleStage::CreateTitleSprite() {
		auto titleLogo = AddGameObject<Sprite>(L"A_TX", true,
			Vec2(400.0f, 120.0f), Vec3(0.0f, 200.0f, 0.1f));
		SetSharedGameObject(L"TitleLogo", titleLogo);
		auto startLogo = AddGameObject<Sprite>(L"GAMESTART_TX", true,
			Vec2(150.0f, 30.0f), Vec3(0.0f, -150.0f, 0.1f));
		SetSharedGameObject(L"StartLogo", startLogo);
		auto endLogo = AddGameObject<Sprite>(L"STAGESELECT_TX", true,
			Vec2(150.0f, 30.0f), Vec3(0.0f, -280.0f, 0.1f));
		SetSharedGameObject(L"EndLogo", endLogo);
		auto cursor = AddGameObject<Sprite>(L"A_TX", true,
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
	void TitleStage::OnUpdate(){;
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
			//�������Z�̃I���I�t
			SetPhysicsActive(true);
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();
			//�N���A�I�u�W�F�N�g
			GameSystemObj();
		}
		catch (...) {
			throw;
		}
	}

//--------------------------------------------------------------------------------------
///�N���A�p�X�e�[�W����
//--------------------------------------------------------------------------------------

	void ClearStage::CreateViewLight() {
		auto ptrView = CreateView<SingleView>();
		//�r���[�̃J�����̐ݒ�
		auto ptrMyCamera = ObjectFactory::Create<MyCamera>();
		ptrView->SetCamera(ptrMyCamera);
		ptrMyCamera->SetEye(Vec3(0.0f, 5.0f, -5.0f));
		ptrMyCamera->SetAt(Vec3(0.0f, 0.0f, 0.0f));
		//�}���`���C�g�̍쐬
		auto ptrMultiLight = CreateLight<MultiLight>();
		//�f�t�H���g�̃��C�e�B���O���w��
		ptrMultiLight->SetDefaultLighting();
	}

	void ClearStage::CreateClearSprite() {
		//�N���A�̕���
		auto clear = AddGameObject<Sprite>(L"CLEAR_TX", true,
			Vec2(250.0f, 70.0f), Vec3(0.0f, 300.0f, 0.0f));
		//�X�R�A
		auto scoreLogo = AddGameObject<Sprite>(L"A_TX", true,
			Vec2(400.0f, 120.0f), Vec3(0.0f, 200.0f, 0.1f));
		SetSharedGameObject(L"Scoreogo", scoreLogo);

		//�ʒu�ƕ����̊Ԋu�̐ݒ�
		m_strSprite = m_sprite = -30.0f;
		m_spriteif = -90.0f;
		//���̃X�e�[�W
		auto nextStageLogo = AddGameObject<Sprite>(L"A_TX", true,
			Vec2(150.0f, 30.0f), Vec3(0.0f, m_sprite, 0.1f));
		SetSharedGameObject(L"NextStageLogo", nextStageLogo);
		//���g���C
		auto oneMoreLogo = AddGameObject<Sprite>(L"A_TX", true,
			Vec2(150.0f, 30.0f), Vec3(0.0f, m_sprite = m_sprite + m_spriteif, 0.1f));
		SetSharedGameObject(L"OneMoreLogo", oneMoreLogo);
		//�X�e�[�W�Z���N�g���
		auto stageSelectLogoa = AddGameObject<Sprite>(L"STAGESELECT_TX", true,
			Vec2(150.0f, 30.0f), Vec3(0.0f, m_sprite = m_sprite + m_spriteif, 0.1f));
		SetSharedGameObject(L"StageSelectLogoa", stageSelectLogoa);
		//�X�^�[�g���
		auto startLogo = AddGameObject<Sprite>(L"A_TX", true,
			Vec2(150.0f, 30.0f), Vec3(0.0f, m_sprite = m_sprite + m_spriteif, 0.1f));
		SetSharedGameObject(L"StartLogo", startLogo);
		
		//�J�[�\���̃A�C�R��
		auto cursor = AddGameObject<Sprite>(L"A_TX", true,
			Vec2(27.0f, 27.0f), Vec3(150.0f, -150.0f, 0.1f));
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
		//�R���g���\���[�̎擾
		m_InputHandler.PushHandle(GetThis<ClearStage>());
		//�A�C�R���̈ړ�
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
		}
		else if (m_cursornum == 2) {
		}
		else if (m_cursornum == 3) {
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
			//�������Z�̃I���I�t
			SetPhysicsActive(true);
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();
			//�N���A�I�u�W�F�N�g
			GameSystemObj();
		}
		catch (...) {
			throw;
		}
	}

//--------------------------------------------------------------------------------------
///�Z���N�g�p�X�e�[�W����
//--------------------------------------------------------------------------------------

	void SerectStage::CreateViewLight() {
		auto ptrView = CreateView<SingleView>();
		//�r���[�̃J�����̐ݒ�
		auto ptrMyCamera = ObjectFactory::Create<MyCamera>();
		ptrView->SetCamera(ptrMyCamera);
		ptrMyCamera->SetEye(Vec3(0.0f, 100.0f, .0f));
		ptrMyCamera->SetAt(Vec3(0.0f, 0.0f, 0.0f));
		//�}���`���C�g�̍쐬
		auto ptrMultiLight = CreateLight<MultiLight>();
		//�f�t�H���g�̃��C�e�B���O���w��
		ptrMultiLight->SetDefaultLighting();
	}

	//�v���C���\�̐���
	void SerectStage::CreatePlayer() {
		//�v���[���[�̍쐬
		auto ptrPlayer = AddGameObject<Player>();
		//�V�F�A�z��Ƀv���C���[��ǉ�
		SetSharedGameObject(L"Player", ptrPlayer);
		ptrPlayer->AddTag(L"Player");
	}

	void SerectStage::CreateStage(){
			AddGameObject<FixedPsBox>(Vec3(30.0f, 1.0f, 30.0f), Quat(), Vec3(0.0f, -0.5f, 0.0f));
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

	void SerectStage::OnCreate() {
		try {
			//�������Z�̃I���I�t
			SetPhysicsActive(true);
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();
			//�X�e�[�W�̐���
			CreateStage();
			//�v���C���[�̐���
			CreatePlayer();
		}
		catch (...) {
			throw;
		}
	}

//--------------------------------------------------------------------------------------
///�Q�[���I�[�o�[�p�X�e�[�W����
//--------------------------------------------------------------------------------------

	void GameOverStage::CreateViewLight() {
		auto ptrView = CreateView<SingleView>();
		//�r���[�̃J�����̐ݒ�
		auto ptrMyCamera = ObjectFactory::Create<MyCamera>();
		ptrView->SetCamera(ptrMyCamera);
		ptrMyCamera->SetEye(Vec3(0.0f, 5.0f, -5.0f));
		ptrMyCamera->SetAt(Vec3(0.0f, 0.0f, 0.0f));
		//�}���`���C�g�̍쐬
		auto ptrMultiLight = CreateLight<MultiLight>();
		//�f�t�H���g�̃��C�e�B���O���w��
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
			//�������Z�̃I���I�t
			SetPhysicsActive(true);
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();
			//�X�e�[�W�̐���
			CreateStage();
		}
		catch (...) {
			throw;
		}
	}

}



//end basecross
//11/22�̉���
//���O�͂��܂ǂ�ȋC�����ł����ǂ�ł���̂��͂킩��Ȃ���
//�����Ƃ�������O���Ă�ł��鎞���͂����Ƃ������̐��ɂ͂��Ȃ����낤
//�����A���̂��O�ɕK�v���Ǝv�����̕��͂��c���B
//11/22�ɂ��O�����ׂ����Ƃ�
//�E���̑������K�v�Ȃ��̂̎���
//��ɂ���3���A�]�T�������
//�E�J�����̃X�^�[�g����S�[���ւ̃J�����̈ړ�
//�E����R�C���̎�������
//�E����R�C���Ƃ������̕��̑傫�������Ƒ��x����
//������Ă����Ƃ����Ɗy�ɂȂ邾�낤
//�`�[�������o�[�͂��݂Ȃ̂Ŗ��ɗ����Ȃ����낤����G�̎�������������������H�ڂɂȂ邩���ȁE�E�E�ʯ
//���������ǂ񂾉���A�N�̗͂��؂�Ă��������炱����11/22�Ɏ�������
//������΂��O�͋~���邩������Ȃ�
//									�ߋ��̉�����






