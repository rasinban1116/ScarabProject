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
	//�{�b�N�X�̍쐬
	void GameStage::CreateFixedBox() {
		CreateSharedObjectGroup(L"TilingBox");
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
			
			
			Vec3 Rot;
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
			AddGameObject<TilingFixedBox>(Scale, Rot, Pos, 1.0f, 1.0f, Tokens[10]);
			//auto tilingquat = tiling->GetComponent<Transform>();
			//tilingquat->SetQuaternion(rot);
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
		auto ptrPlayer = AddGameObject<Player>();
		//�V�F�A�z��Ƀv���C���[��ǉ�
		SetSharedGameObject(L"Player", ptrPlayer);
		ptrPlayer->AddTag(L"Player");
	}

	//�v���C���[���p�������q�I�u�W�F�N�g�i�ӂ񂱂낪���ɂȂ�\��j�𐶐�
	void GameStage::CreatePlayerChild() {
		//�I�u�W�F�N�g�̃O���[�v���쐬����
		auto group = CreateSharedObjectGroup(L"SeekGroup");
		auto Target = GetSharedObject(L"Player", true);
		auto Targetrans = Target->GetComponent<Transform>();
		auto TargetPos = Targetrans->GetPosition();
		//�z��̏�����
		vector<Vec3> vec = {
			{ TargetPos.x,TargetPos.y-0.5f,TargetPos.z -1.0f },
		};

		//�z�u�I�u�W�F�N�g�̍쐬
		for (size_t count = 0; count < vec.size(); count++) {
			AddGameObject<PlayerChild>(vec[count]);
		}

	}

	void GameStage::activeboll() {
		AddGameObject<ActivePsSphere>(1.0f, Quat(), Vec3(0.0f, 6.0f, 5.0f));
	}

	void GameStage::CreateGimmickObj() {
		auto group = CreateSharedObjectGroup(L"CoinGroup");
		AddGameObject<GimmickObj>(Vec3(0.1f, 0.5f, 0.5f),  Quat(), Vec3(0.0f, 0.6f, -3.0f));
		AddGameObject<GimmickObj>(Vec3(0.1f, 0.5f, 0.5f),  Quat(), Vec3(3.0f, 0.6f, -3.0f));
		AddGameObject<GimmickObj>(Vec3(0.1f, 0.5f, 0.5f),  Quat(), Vec3(-3.0f, 0.6f, -3.0f));
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
			//�M�~�b�N�̐���
			CreateGimmickObj();
			//UI�̕\��
			CreateUI();
		}
		catch (...) {
			throw;
		}
	}

}
//end basecross
