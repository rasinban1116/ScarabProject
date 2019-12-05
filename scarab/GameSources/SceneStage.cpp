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
		ptrMyCamera->SetEye(Vec3(0.0f, 5.0f, -5.0f));
		ptrMyCamera->SetAt(Vec3(0.0f, 0.0f, 0.0f));
		//�}���`���C�g�̍쐬
		auto ptrMultiLight = CreateLight<MultiLight>();
		//�f�t�H���g�̃��C�e�B���O���w��
		ptrMultiLight->SetDefaultLighting();
	}

	//�v���C���\�̐���
	void SerectStage::CreatePlayer() {
		//�v���[���[�̍쐬
		auto ptrPlayer = AddGameObject<Player>(Vec3(0.0f,1.0f,-5.0f));
		//�V�F�A�z��Ƀv���C���[��ǉ�
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
			//�������Z�̃I���I�t
			SetPhysicsActive(true);
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();
			//�X�e�[�W�̐���
			CreateStage();
			//�v���C���[�̐���
			CreatePlayer();
			//�X�e�[�W�Z���N�g�I�u�W�F�N�g�̐���
			OnCreateSrectObj();
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






