
/*!
@file Scene.cpp
@brief �V�[������
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{

	//--------------------------------------------------------------------------------------
	///	�Q�[���V�[��
	//--------------------------------------------------------------------------------------
	void Scene::OnCreate(){
		try {
			//�N���A����F��ݒ�
			Col4 Col;
			Col.set(1.0f / 255.0f, 30.0f / 255.0f, 71.0f / 255.0f, 255.0f / 255.0f);
			//Col.set(BACKGROUND_RED,BACKGROUND_GREEN,BACKGROUND_BLUE,BACKGROUND_INTENSITY);
			SetClearColor(Col);
			
			//�������g�ɃC�x���g�𑗂�
			//����ɂ��e�X�e�[�W��I�u�W�F�N�g��Create���ɃV�[���ɃA�N�Z�X�ł���
			PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), L"ToGameStage");
			
			CreateResourses();
			LoadStaticModelResources();
			LoadStaticBornModelResources();
			LoadMaltiModelResources();
		}
		catch (...) {
			throw;
		}
	}

/// ---------------------------------------------------------------------------<summary>
/// �X�^�e�B�b�N���f���̓ǂݍ���(�����Ȃ�)
/// </summary>----------------------------------------------------------------------------
	void Scene::LoadStaticModelResources() {
		wstring dataDir;
		App::GetApp()->GetDataDirectory(dataDir);
		struct InitializedParam {
			wstring m_modelName;
			wstring m_modelKey;
		};
		InitializedParam models[] = {
			//{L"�t�@�C����",L"�Ăяo�����̃L�["}
			{L"scarabtest.bmf",L"scarab"},
			{L"test.bmf",L"test"},
			{L"stage.bmf",L"stage"},
			{L"rock.bmf",L"rock"},
			{L"tree.bmf",L"tree"},
			{L"poop.bmf",L"unko"},
			{L"Base.bmf",L"Base"},
			{L"falltree.bmf",L"fallntree"},
			{L"lizard.bmf",L"liz"}
				
		

		};
		for (auto model : models) {
			wstring srtmodel = dataDir;
			auto staticModel = MeshResource::CreateStaticModelMesh(srtmodel, model.m_modelName);
			//auto malti = MeshResource::CreateMeshResource(strmodel, model._modelName);
			App::GetApp()->RegisterResource(model.m_modelKey, staticModel);
		}
	}

	/// ---------------------------------------------------------------------------<summary>
/// �X�^�e�B�b�N���f���̓ǂݍ���(�����Ȃ�)
/// </summary>----------------------------------------------------------------------------
	void Scene::LoadStaticBornModelResources() {
		wstring dataDir;
		App::GetApp()->GetDataDirectory(dataDir);
		struct InitializedParam {
			wstring m_modelName;
			wstring m_modelKey;
		};
		InitializedParam models[] = {
			//{L"�t�@�C����",L"�Ăяo�����̃L�["}
			{L"Scarab_Enemy_Walking.bmf",L"Enemy"},
			//{L"Scarab_Walking.bmf",L"scrab"}



		};
		for (auto model : models) {
			wstring srtmodel = dataDir;
			auto staticModel = MeshResource::CreateBoneModelMesh(srtmodel, model.m_modelName);

			App::GetApp()->RegisterResource(model.m_modelKey, staticModel);
		}
	}
	void Scene::LoadMaltiModelResources()
	{
		wstring dataDir;
		App::GetApp()->GetDataDirectory(dataDir);
		struct InitializedParam {
			wstring m_modelName;
			wstring m_modelKey;
		};
		InitializedParam models[] = {
			//{L"�t�@�C����",L"�Ăяo�����̃L�["}
			//{L"Scarab_Enemy_Walking.bmf",L"Enemy"},
			{L"ScarabOnPoop_Walking.bmf",L"scrab"}



		};
		for (auto model : models) {
			wstring srtmodel = dataDir;
			auto staticModel = MultiMeshResource::CreateBoneModelMultiMesh(srtmodel, model.m_modelName);
			App::GetApp()->RegisterResource(model.m_modelKey, staticModel);
		}
	}
	


	void Scene::CreateResourses() {
		wstring dataDir;
		auto play = shared_ptr<BaseResource>();
		//�T���v���̂��߃A�Z�b�g�f�B���N�g�����擾
		App::GetApp()->GetAssetsDirectory(dataDir);
		//�e�Q�[���͈ȉ��̂悤�Ƀf�[�^�f�B���N�g�����擾���ׂ�
		App::GetApp()->GetDataDirectory(dataDir);
		wstring strTexture = dataDir + L"trace.png";
		App::GetApp()->RegisterTexture(L"TRACE_TX", strTexture);
		strTexture = dataDir + L"sky.jpg";
		App::GetApp()->RegisterTexture(L"A_TX", strTexture);
		strTexture = dataDir + L"Grand.png";
		App::GetApp()->RegisterTexture(L"WALL_TX", strTexture);
		strTexture = dataDir + L"Block_A.png";
		App::GetApp()->RegisterTexture(L"H_TX", strTexture);
		strTexture = dataDir + L"haikei.png";
		App::GetApp()->RegisterTexture(L"J_TX", strTexture);
		strTexture = dataDir + L"Weed.png";
		App::GetApp()->RegisterTexture(L"Cl_TX", strTexture);
		strTexture = dataDir + L"UV_Scarab.tga";
		App::GetApp()->RegisterTexture(L"KUSA_TX", strTexture);
		strTexture = dataDir + L"poop_UV.png";
		App::GetApp()->RegisterTexture(L"UNKO_TX", strTexture);
		strTexture = dataDir + L"UV_Scarab_Enemy.png";
		App::GetApp()->RegisterTexture(L"ENEMY_TX", strTexture);
		strTexture = dataDir + L"number.png";
		App::GetApp()->RegisterTexture(L"NUMBER_TX", strTexture);

		strTexture = dataDir + L"clear.png";
		App::GetApp()->RegisterTexture(L"CLEAR_TX", strTexture);
		strTexture = dataDir + L"nextstage.png";
		App::GetApp()->RegisterTexture(L"NEXTSTAGE_TX", strTexture);
		strTexture = dataDir + L"gamestart.png";
		App::GetApp()->RegisterTexture(L"GAMESTART_TX", strTexture);
		strTexture = dataDir + L"gameend.png";
		App::GetApp()->RegisterTexture(L"GAMEEND_TX", strTexture);
		strTexture = dataDir + L"title.png";
		App::GetApp()->RegisterTexture(L"TITLE_TX", strTexture);
		strTexture = dataDir + L"stageselect.png";
		App::GetApp()->RegisterTexture(L"STAGESELECT_TX", strTexture);
		strTexture = dataDir + L"retry.png";
		App::GetApp()->RegisterTexture(L"RETRY_TX", strTexture);
		strTexture = dataDir + L"Title_01.png";
		App::GetApp()->RegisterTexture(L"TITLEBACK_TX", strTexture);
		strTexture = dataDir + L"Title02.png";
		App::GetApp()->RegisterTexture(L"TITLECHARA_TX", strTexture);
		strTexture = dataDir + L"poop_cursor.png";
		App::GetApp()->RegisterTexture(L"ICON_TX", strTexture);
		strTexture = dataDir + L"backsky.png";
		App::GetApp()->RegisterTexture(L"SKY_TX", strTexture);
	}


	Scene::~Scene() {
	}

	void Scene::OnEvent(const shared_ptr<Event>& event) {
		if (event->m_MsgStr == L"ToTitleStage") {
			//�ŏ��̃A�N�e�B�u�X�e�[�W�̐ݒ�
			ResetActiveStage<GameStage>();
		}
		else if (event->m_MsgStr == L"ToSerectStage") {
			ResetActiveStage<SerectStage>();
		}
		else if (event->m_MsgStr == L"ToGameStage") {
			ResetActiveStage<GameStage>();
		}
		else if (event->m_MsgStr == L"ToClearStage") {
			ResetActiveStage<ClearStage>();
		}

	}
	void Scene::SetScene(const shared_ptr<Event>&event,wstring name) {
			event->m_MsgStr = name;
			
	}



}
//end basecross
