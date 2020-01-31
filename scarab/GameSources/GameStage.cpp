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
		m_GameStageCsvB.GetSelect(LineVec, 0, L"SlopeFixedBox");
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
			auto Tiling = AddGameObject<SlopeFixedBox>(Scale, Rot, Pos, 1.0f, 1.0f, Tokens[10]);
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
		auto ptrPlayer = AddGameObject<Player>(Vec3(-89.0f, 0.5f, -35.0f));
		//�V�F�A�z��Ƀv���C���[��ǉ�
		SetSharedGameObject(L"Player", ptrPlayer);
		ptrPlayer->AddTag(L"Player");
	}

	//�v���C���[���p�������q�I�u�W�F�N�g�i�ӂ񂱂낪���ɂȂ�\��j�𐶐�
	void GameStage::CreatePlayerChild() {
		auto Unko = AddGameObject<UnkoBoll>(Vec3(-85.0f, 0.5f, -33.0f),Vec3(1.0f),Vec3(0.0f), Vec3(0.0f, 6.0f, 5.0f));
		SetSharedGameObject(L"UnkoBoll", Unko);
		Unko->AddTag(L"UnkoBoll");
	}

	void GameStage::CreateLowEnemy() {
		//�t���R���K�V�̐���
		auto group = CreateSharedObjectGroup(L"EnemyGroup");
		vector< vector<Vec3> > vecSca = {
			{ Vec3(-15.0f, 3.0f, -5.0f), Vec3(-23.0f,3.0f,-4.0f) },
			{ Vec3(5.0f, 0.5f, 1.0f), Vec3(-1.0f,5.0f, 7.0f) },
			{ Vec3(-73.0f, 0.5f, -40.0f), Vec3(-70.0f,0.5f, -35.0f) },
			{ Vec3(-75.0f, 0.5f,-2.0f), Vec3(-70.0f,2.0f, 1.0f) },
			{ Vec3(-30.0f, 0.5f,-34.0f), Vec3(30.0f,2.0f, -34.0f) },



		};
		for (auto v : vecSca) {
			auto ptreneobj = AddGameObject<Enemy>(v[0], v[1], 1, L"SCARAB_TX", L"Enemy");
		}

		//�g�J�Q�̐���
		vector< vector<Vec3> > vecLiz = {
			{ Vec3(10.0f ,0.5f, 0.0f), Vec3(0.0f, 0.0f, 5.0f) },
			{ Vec3(-70.0f, 0.5f,-40.0f), Vec3(69.0f,2.0f, -49.0f) },
			{ Vec3(-68.0f, 0.5f,-0.0f), Vec3(-68.0f,2.0f, -34.0f) },
			{ Vec3(-30.0f, 0.5f,-40.0f), Vec3(30.0f,2.0f, 34.0f) },

		};
		for (auto v : vecLiz) {
			auto ptreneobj = AddGameObject<Enemy>(v[0], v[1], 1, L"Lizad_TX", L"Lizad");

		}
	}

	void GameStage::CreateGimmickObj() {
		auto group = CreateSharedObjectGroup(L"CoinGrope");
		
		AddGameObject<GimmickObj>(Vec3(0.25f, 0.25f, 0.25f),  Quat(), Vec3(0.0f, 0.f, -3.0f));
		AddGameObject<GimmickObj>(Vec3(0.25f, 0.25f, 0.25f),  Quat(), Vec3(3.0f, 0.f, -3.0f));
		AddGameObject<GimmickObj>(Vec3(0.25f, 0.25f, 0.25f), Quat(), Vec3(-78.0f, 0.f, -35.0f));
		AddGameObject<GimmickObj>(Vec3(0.25f, 0.25f, 0.25f), Quat(), Vec3(-71.0f, 0.f, -30.0f));
		AddGameObject<GimmickObj>(Vec3(0.25f, 0.25f, 0.25f), Quat(), Vec3(-35.0f, 0.f, -4.0f));
		AddGameObject<GimmickObj>(Vec3(0.25f, 0.25f, 0.25f), Quat(), Vec3(-27.0f, 0.f, 1.0f));
		AddGameObject<GimmickObj>(Vec3(0.25f, 0.25f, 0.25f), Quat(), Vec3(-29.0f, 0.f, -32.0f));
		AddGameObject<GimmickObj>(Vec3(0.25f, 0.25f, 0.25f), Quat(), Vec3(-32.0f, 0.f, -38.0f));
		AddGameObject<GimmickObj>(Vec3(0.25f, 0.25f, 0.25f), Quat(), Vec3(-77.0f, 0.f, -4.2f));
	
	}
	void  GameStage::CreateWoods() {
		auto woods = CreateSharedObjectGroup(L"WoodsGrope");
		
		AddGameObject<StageObj>(Vec3(1), Vec3(1), 0);

	}
	

	void GameStage::CreateClearObj() {
		auto ClearObj = AddGameObject<StageClearObj>(Vec3(0,0.f,0), Vec3(0.5f));
		SetSharedGameObject(L"Clear",ClearObj);
	}

	void GameStage::CreateSky() {
		AddGameObject<SkyObj>(Vec3(200.f, 100.f, 0.5f), Quat(), Vec3(0.0f, 0.0f, 100.0f));
		AddGameObject<SkyObj>(Vec3(200.f, 100.f, 0.5f), Quat(), Vec3(0.0f, 0.0f, -100.0f));
		AddGameObject<SkyObj>(Vec3(0.5f, 100.f, 200.0f), Quat(), Vec3(100.0f, 0.0f, 0.0f));
		AddGameObject<SkyObj>(Vec3(0.5f, 100.f, 200.0f), Quat(), Vec3(-100.0f, 0.0f, 0.0f));
		AddGameObject<SkyObj>(Vec3(200.0f, 0.5f, 200.0f), Quat(), Vec3(0.0f, 50.0f, 0.0f));

	}




	void GameStage::OnCreate() {
		auto gm = GameManager::GetInstance();
		gm->UnkoNumReSet();
		try {
			wstring DataDir;
			App::GetApp()->GetDataDirectory(DataDir);
			//�������Z�̃I���I�t
			SetPhysicsActive(true);
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();
			////CSV�t�@�C������B�̓ǂݍ���
			m_GameStageCsvB.SetFileName(DataDir + L"Stage2.csv");
			m_GameStageCsvB.ReadCsv();
			//�������Z����{�b�N�X�̍쐬
			CreateFixedBox();
			//�������Z����R���W�������������v���C���[�̍쐬
			CreatePlayer();
			//�v���C���[���p�������q�I�u�W�F�N�g�̍쐬
			CreatePlayerChild();
			//�G�̒ǉ�
			CreateLowEnemy();
			//��̒ǉ�
			CreateSky();
			//�M�~�b�N�̐���
			CreateGimmickObj();
			CreateClearObj();
			//UI�̕\��
			CreateUI();
			//�ǂ̐���
			CreateBox();
			//�؁X�̐���
			CreateWoods();
		}
		catch (...) {
			throw;
		}
	}

}
//end basecross
