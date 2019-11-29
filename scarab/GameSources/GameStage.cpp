/*!
@file GameStage.cpp
@brief �Q�[���X�e�[�W����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

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
			rot.x = (float)_wtof(Tokens[4].c_str());
			rot.y = (float)_wtof(Tokens[5].c_str());
			rot.z = (float)_wtof(Tokens[6].c_str());
			Vec3 Pos(
				(float)_wtof(Tokens[7].c_str()),
				(float)_wtof(Tokens[8].c_str()),
				(float)_wtof(Tokens[9].c_str())
			);

			//�e�l����������̂ŃI�u�W�F�N�g�쐬
			auto tiling = AddGameObject<TilingFixedBox>(Scale, Rot, Pos, 1.0f, 1.0f, Tokens[10]);
			auto tilingquat = tiling->GetComponent<Transform>();
			//tilingquat->SetQuaternion(rot);
		}
	}


	//�Œ�̃{�b�N�X�̍쐬
	//void GameStage::CreateFixedBox() {
	//	//���̑�
	//	AddGameObject<FixedPsBox>(Vec3(30.0f, 1.0f, 30.0f), Quat(), Vec3(0.0f, -0.5f, 0.0f));
	//
	//	//�����Ȃ���
	//	AddGameObject<FixedPsBox>(Vec3(3.0f, 3.0f, 3.0f), Quat(), Vec3(0.0f, 0.0f, 3.0f));
	//	AddGameObject<FixedPsBox>(Vec3(2.0f, 3.0f, 2.0f), Quat(), Vec3(4.0f, 0.0f, 5.0f));

	//	//�ォ��~���Ă��鋅��
	//	AddGameObject<ActivePsSphere>(1.0f, Quat(), Vec3(0.0f, 6.0f, 5.0f));

	//}

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
			{ TargetPos.x,TargetPos.y,TargetPos.z -0.5f },
		};

		//�z�u�I�u�W�F�N�g�̍쐬
		for (size_t count = 0; count < vec.size(); count++) {
			AddGameObject<PlayerChild>(vec[count]);
		}

	}

	void GameStage::CreateLowEnemy() {
		auto group = CreateSharedObjectGroup(L"Enemy_LowGroup");
		vector< vector<Vec3> > vecSeek = {
			{ Vec3(5.0, 0.5f, 0.0f), Vec3(0.0f, 0.0f, 5.0f) },
		};
		//�ǂ�������I�u�W�F�N�g�̍쐬
		for (auto v : vecSeek) {
			auto ptrPathobj = AddGameObject<FollowPathObject>(v[0], v[1]);
			SetSharedGameObject(L"Pathobj", ptrPathobj);
			ptrPathobj->AddTag(L"Pathobj");
			
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
			m_GameStageCsvB.SetFileName(DataDir + L"test0.csv");
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
			//UI�̕\��
			CreateUI();
			//�N���A�I�u�W�F�N�g
			//GameSystemObj();
		}
		catch (...) {
			throw;
		}
	}

}
//end basecross
