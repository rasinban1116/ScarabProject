/*!
@file GameStage.cpp
@brief �Q�[���X�e�[�W����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//�X�e�[�W�����I���������͈͓��ȊO���X���[�v�����鏈��������


	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X����
	//--------------------------------------------------------------------------------------
	void GameStage::CreateViewLight() {
		//OpeningCameraView�p�̃r���[
		m_OpeningCameraView = ObjectFactory::Create<SingleView>(GetThis<Stage>());
		auto ptrOpeningCamera = ObjectFactory::Create<OpeningCamera>();
		m_OpeningCameraView->SetCamera(ptrOpeningCamera);
		//ObjCamera�p�̃r���[
		m_ObjCameraView = ObjectFactory::Create<SingleView>(GetThis<Stage>());
		auto ptrObjCamera = ObjectFactory::Create<ObjCamera>();
		m_ObjCameraView->SetCamera(ptrObjCamera);
		//MyCamera�p�̃r���[
		m_MyCameraView = ObjectFactory::Create<SingleView>(GetThis<Stage>());
		auto ptrMyCamera = ObjectFactory::Create<MyCamera>();
		ptrMyCamera->SetEye(Vec3(0.0f, 10.0f, -5.0f));
		ptrMyCamera->SetAt(Vec3(0.0f, 0.0f, 0.0f));
		m_MyCameraView->SetCamera(ptrMyCamera);
		//������Ԃł�m_OpeningCameraView���g��
		SetView(m_OpeningCameraView);
		m_CameraSelect = CameraSelect::openingCamera;
		//�}���`���C�g�̍쐬
		auto PtrMultiLight = CreateLight<MultiLight>();
		//�f�t�H���g�̃��C�e�B���O���w��
		PtrMultiLight->SetDefaultLighting();

	}

	void GameStage::CreateBox(){
		auto treeGrope = CreateSharedObjectGroup(L"Tree");
		//AddGameObject<WallPsBox>(Vec3(1), Quat(0),Vec3(-60.0f, 8.5f, -25.0f),int(1));
		//AddGameObject<WallPsBox>(Vec3(1), Quat(0), Vec3(-50.0f, 10.5f, -20.0f), int(1));
		//AddGameObject<WallPsBox>(Vec3(1), Quat(0), Vec3(-30.0f, 10.5f, -35.0f), int(3));


	}
	//�{�b�N�X�̍쐬
	void GameStage::CreateFixedBox() {
		CreateSharedObjectGroup(L"TilingBox");
		Vec3 Rot;
		//CSV�̍s�P�ʂ̔z��
		vector<wstring> LineVec;
		//0�Ԗڂ̃J������L"TilingFixedBox"�ł���s�𔲂��o��
		m_GameStageCsvB.GetSelect(LineVec, 0, L"TilingFixedBox");
		for (auto& v : LineVec) {
			//�g�[�N���i�J�����j�̔z��
			vector<wstring> Tokens;
			//�g�[�N���i�J�����j�P�ʂŕ�����𒊏o(L','���f���~�^�Ƃ��ċ敪��)
			Util::WStrToTokenVector(Tokens, v, L',');
			//�e�g�[�N���i�J�����j���X�P�[���A��]�A�ʒu�ɓǂݍ���
			Vec3 Scale(
				(float)_wtof(Tokens[1].c_str()),
				(float)_wtof(Tokens[2].c_str()),
				(float)_wtof(Tokens[3].c_str())
			);
			
			

			//��]�́uXM_PIDIV2�v�̕�����ɂȂ��Ă���ꍇ������
			Rot.x = (Tokens[4] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[4].c_str());
			Rot.y = (Tokens[5] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[5].c_str());
			Rot.z = (Tokens[6] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[6].c_str());
			Quat rot;
			float x, y, z;
			x = (float)_wtof(Tokens[4].c_str());
			y = (float)_wtof(Tokens[5].c_str());
			z = (float)_wtof(Tokens[6].c_str());
			rot.setX(x);
			rot.setY(y);
			rot.setZ(z);
			//Rot = rot;
			Vec3 Pos(
				(float)_wtof(Tokens[7].c_str()),
				(float)_wtof(Tokens[8].c_str()),
				(float)_wtof(Tokens[9].c_str())
			);

			//�e�l����������̂ŃI�u�W�F�N�g�쐬
			auto Tiling = AddGameObject<TilingFixedBox>(Scale, Rot, Pos, 1.0f, 1.0f, Tokens[10]);
		}
		//0�Ԗڂ̃J������L"TilingFixedBox"�ł���s�𔲂��o��
		m_GameStageCsvB.GetSelect(LineVec, 0, L"TilingFixedBox");
		for (auto& v : LineVec) {
			//�g�[�N���i�J�����j�̔z��
			vector<wstring> Tokens;
			//�g�[�N���i�J�����j�P�ʂŕ�����𒊏o(L','���f���~�^�Ƃ��ċ敪��)
			Util::WStrToTokenVector(Tokens, v, L',');
			//�e�g�[�N���i�J�����j���X�P�[���A��]�A�ʒu�ɓǂݍ���
			Vec3 Scale(
				(float)_wtof(Tokens[1].c_str()),
				(float)_wtof(Tokens[2].c_str()),
				(float)_wtof(Tokens[3].c_str())
			);



			//��]�́uXM_PIDIV2�v�̕�����ɂȂ��Ă���ꍇ������
			Rot.x = (Tokens[4] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[4].c_str());
			Rot.y = (Tokens[5] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[5].c_str());
			Rot.z = (Tokens[6] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[6].c_str());
			Quat rot;
			float x, y, z;
			x = (float)_wtof(Tokens[4].c_str());
			y = (float)_wtof(Tokens[5].c_str());
			z = (float)_wtof(Tokens[6].c_str());
			rot.setX(x);
			rot.setY(y);
			rot.setZ(z);
			//Rot = rot;
			Vec3 Pos(
				(float)_wtof(Tokens[7].c_str()),
				(float)_wtof(Tokens[8].c_str()),
				(float)_wtof(Tokens[9].c_str())
			);

			//�e�l����������̂ŃI�u�W�F�N�g�쐬
			auto Tiling = AddGameObject<TilingFixedBox>(Scale, Rot, Pos, 1.0f, 1.0f, Tokens[10]);
		}


	}

	void GameStage::CreateUI() {
		auto UI = AddGameObject<UIDraw>();
		SetSharedGameObject(L"UI", UI);
	}
	void GameStage::GameSystemObj() {
		auto Clear = AddGameObject<StageClearObj>(Vec3(0.0f,3.0f,0.0f),Vec3(0.5f));
	}


	//�v���C���\�̐���
	void GameStage::CreatePlayer() {
		//�v���[���[�̍쐬
		auto ptrPlayer = AddGameObject<Player>(Vec3(-89.0f, 19.0f, -35.0f));
		//�V�F�A�z��Ƀv���C���[��ǉ�
		SetSharedGameObject(L"Player", ptrPlayer);
		ptrPlayer->AddTag(L"Player");
		
	}

	//�v���C���[���p�������q�I�u�W�F�N�g�i�ӂ񂱂낪���ɂȂ�\��j�𐶐�
	void GameStage::CreatePlayerChild() {
		auto Unko = AddGameObject<UnkoBoll>(Vec3(-85.0f, 21.0f, -33.0f),Vec3(1.0f),Vec3(0.0f), Vec3(0.0f, 6.0f, 5.0f));
		SetSharedGameObject(L"UnkoBoll", Unko);
		Unko->AddTag(L"UnkoBoll");
	}

	void GameStage::CreateLowEnemy() {
		auto group = CreateSharedObjectGroup(L"EnemyGroup");
		vector< vector<Vec3> > vecSeek = {
			{ Vec3(5.0, 0.5f, 0.0f), Vec3(0.0f, 0.0f, 5.0f) },
			{ Vec3(-15.0f, 3.0f, -5.0f), Vec3(-23.0f,3.0f,-4.0f) },
			{ Vec3(5.0, 0.5f, 1.0f), Vec3(-1.0f,5.0f, 7.0f) },


			
		};
		//�ǂ�������I�u�W�F�N�g�̍쐬
		for (auto v : vecSeek) {
			auto ptreneobj = AddGameObject<Enemy>(v[0], v[1],1);
			//AddGameObject<Enemy>(v[0], v[1], 1);
			ptreneobj->AddTag(L"Enemy");
			
		}
	}

	void GameStage::CreateGimmickObj() {
		auto group = CreateSharedObjectGroup(L"CoinGrope");
		
		AddGameObject<GimmickObj>(Vec3(0.25f, 0.25f, 0.25f),  Quat(), Vec3(0.0f, 0.6f, -3.0f));
		AddGameObject<GimmickObj>(Vec3(0.25f, 0.25f, 0.25f),  Quat(), Vec3(3.0f, 0.6f, -3.0f));
		AddGameObject<GimmickObj>(Vec3(0.25f, 0.25f, 0.25f), Quat(), Vec3(-83.0f, 18.2f, -35.0f));
		AddGameObject<GimmickObj>(Vec3(0.25f, 0.25f, 0.25f), Quat(), Vec3(-80.0f, 18.2f, -40.0f));
		AddGameObject<GimmickObj>(Vec3(0.25f, 0.25f, 0.25f), Quat(), Vec3(-43.0f, 4.2f, -2.0f));
		AddGameObject<GimmickObj>(Vec3(0.25f, 0.25f, 0.25f), Quat(), Vec3(-37.0f, 4.2f, -8.0f));	
		AddGameObject<GimmickObj>(Vec3(0.25f, 0.25f, 0.25f), Quat(), Vec3(-43.0f, 13.0f, -46.0f));	
		AddGameObject<GimmickObj>(Vec3(0.25f, 0.25f, 0.25f), Quat(), Vec3(-50.0f, 13.0f, -40.0f));		
		AddGameObject<GimmickObj>(Vec3(0.25f, 0.25f, 0.25f), Quat(), Vec3(-77.0f, 9.2f, -4.2f));
	
	}

	void GameStage::CreateClearObj() {
		auto ClearObj = AddGameObject<StageClearObj>(Vec3(0), Vec3(1));
		SetSharedGameObject(L"Clear",ClearObj);
	}

	//�J�����}���̍쐬
	void GameStage::CreateCameraman() {
		//auto ptrCameraman = AddGameObject<Cameraman>(2.0f);
		////�V�F�A�z���Cameraman��ǉ�
		//SetSharedGameObject(L"Cameraman", ptrCameraman);
		
		auto ptrOpeningCameraman = AddGameObject<OpeningCameraman>();
		//�V�F�A�z���OpeningCameraman��ǉ�
		SetSharedGameObject(L"OpeningCameraman", ptrOpeningCameraman);

		auto ptrOpeningCamera = dynamic_pointer_cast<OpeningCamera>(m_OpeningCameraView->GetCamera());
		if (ptrOpeningCamera) {
			ptrOpeningCamera->SetCameraObject(ptrOpeningCameraman);
			SetView(m_OpeningCameraView);
			m_CameraSelect = CameraSelect::openingCamera;
		}

	}



	void GameStage::OnCreate() {
		try {
			wstring DataDir;
			App::GetApp()->GetDataDirectory(DataDir);
			//�������Z�̃I���I�t
			SetPhysicsActive(true);
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();
			////CSV�t�@�C������B�̓ǂݍ���
			m_GameStageCsvB.SetFileName(DataDir + L"test2.csv");
			m_GameStageCsvB.ReadCsv();
			//�������Z����{�b�N�X�̍쐬
			CreateFixedBox();
			//�������Z����R���W�������������v���C���[�̍쐬
			CreatePlayer();
			//�v���C���[���p�������q�I�u�W�F�N�g�̍쐬
			CreatePlayerChild();
			CreateLowEnemy();
			//�M�~�b�N�̐���
			CreateGimmickObj();
			CreateClearObj();
			//UI�̕\��
			CreateUI();
			//�J�����}���̍쐬
			CreateCameraman();
			//�ǂ̐���
			CreateBox();
		}
		catch (...) {
			throw;
		}
	}
	void GameStage::ToMyCamera() {
		auto ptrPlayer = GetSharedGameObject<Player>(L"Player");
		//MyCamera�ɕύX
		auto ptrMyCamera = dynamic_pointer_cast<MyCamera>(m_MyCameraView->GetCamera());
		if (ptrMyCamera) {
			ptrMyCamera->SetTargetObject(ptrPlayer);
			//m_MyCameraView���g��
			SetView(m_MyCameraView);
			m_CameraSelect = CameraSelect::myCamera;
		}
	}
	void GameStage::ToObjCamera() {
		auto ptrPlayer = GetSharedGameObject<Player>(L"Player");
		//ObjCamera�ɕύX
		auto ptrCameraman = GetSharedGameObject<Cameraman>(L"Cameraman");
		auto ptrObjCamera = dynamic_pointer_cast<ObjCamera>(m_ObjCameraView->GetCamera());
		if (ptrObjCamera) {
			ptrObjCamera->SetCameraObject(ptrCameraman);
			ptrObjCamera->SetTargetObject(ptrPlayer);
			//m_ObjCameraView���g��
			SetView(m_ObjCameraView);
			m_CameraSelect = CameraSelect::objCamera;
		}
	}

}
//end basecross
