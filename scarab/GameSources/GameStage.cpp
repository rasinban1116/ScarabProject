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

	//�Œ�̃{�b�N�X�̍쐬
	void GameStage::CreateFixedBox() {
		//���̑�
		AddGameObject<FixedPsBox>(Vec3(30.0f, 1.0f, 30.0f), Quat(), Vec3(0.0f, -0.5f, 0.0f));

		//�����Ȃ���
		AddGameObject<FixedPsBox>(Vec3(3.0f, 1.0f, 3.0f), Quat(), Vec3(0.0f, 0.5f, 3.0f));
		//AddGameObject<FixedPsBox>(Vec3(3.0f, 1.0f, 3.0f), Quat(0.5f), Vec3(4.0f, 0.5f, 5.0f));

	}
	void GameStage::CreateCollisionBox2() {
		vector <vector<Vec3>> vec = { {

				Vec3(10.0f, 0.5f, 10.0f),
				Vec3(-0.5f, 0.0f, -0.5f),
				Vec3(-10.0f, 0.25f, 10.0f)
		},
		{
				Vec3(10.0f, 0.5f, 10.0f),
				Vec3(-0.0f, 0.0f, -0.0f),
				Vec3(-10.0f,4.0f, 18.0f)
		},

		};
		//�I�u�W�F�N�g�̍쐬
		for (auto v : vec) {
		auto SlopeObj = AddGameObject<FixedBox>(v[0], v[1], v[2]);
		//�V�F�A�z��ɍ⓹�I�u�W�F�N�g��ǉ�
		//auto SlopeGroup = CreateSharedObjectGroup(L"SlopeGroup");
		}

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
		//�z��̏�����
		vector<Vec3> vec = {
			{ 0, 0.125f, 10.0f },
			{ 10.0f, 0.125f, 0.0f },
			{ -10.0f, 0.125f, 0.0f },
			{ 0, 0.125f, -10.0f },
		};

		//�z�u�I�u�W�F�N�g�̍쐬
		for (size_t count = 0; count < vec.size(); count++) {
			AddGameObject<PlayerChild>(vec[count]);
		}

	}

	void GameStage::activeboll() {
		AddGameObject<ActivePsSphere>(1.0f, Quat(), Vec3(0.0f, 6.0f, 5.0f));
	}


	void GameStage::OnCreate() {
		try {
			//�������Z�̃I���I�t
			SetPhysicsActive(true);
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();
			//�������Z����{�b�N�X�̍쐬
			CreateFixedBox();
			//�������Z����R���W�������������v���C���[�̍쐬
			CreatePlayer();
			//�v���C���[���p�������q�I�u�W�F�N�g�̍쐬
			CreatePlayerChild();
			//�R���W�������������{�b�N�X�̍쐬
			CreateCollisionBox2();
			//�������Z���鋅�̂̍쐬
			activeboll();
		}
		catch (...) {
			throw;
		}
	}

}
//end basecross
