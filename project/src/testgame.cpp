//
//  testgame.cpp
//  dcpp
//
//  Created by Jorge López on 21/4/16.
//  Copyright © 2016 Jorge López. All rights reserved.
//

#include "testgame.h"

#include "testhfsm.h"

#include <subsystem/windowsubsystem.h>
#include <subsystem/inputsubsystem.h>
#include <subsystem/scenesubsystem.h>
#include <subsystem/rendersubsystem.h>

#include <component/gameobject.h>
#include <component/transform.h>
#include <component/modelcomponent.h>
#include <component/renderercomponent.h>
#include <component/camera.h>

#include <renderer/renderlayermanager.h>
#include <persist/md3/loadmd3.h>

#include <containers/array.h>
#include <containers/forwardlist.h>

#include <signals/signal.h>

#include <dir/directory.h>

#include <cstdio>
#include <cstring>

namespace dc
{
	const char*			HELLO_SCREEN = "Hello Screen";
	const unsigned int	SCR_WIDTH = 640;
	const unsigned int 	SCR_HEIGHT = 480;
	const unsigned int	SCR_BPP = 16;
	const bool			SCR_FULLSCREEN = false;

	void CTestGameApp::Create()
	{
		printf("Adding HFSM subsystem\n");
		Add(new CTestHFSM());

		printf("Adding Window subsystem\n");
		CWindowSubsystem* windowSubsystem = new CWindowSubsystem();
		TDisplayInfo displayInfo(SCR_WIDTH, SCR_HEIGHT, SCR_BPP, HELLO_SCREEN, SCR_FULLSCREEN);
		windowSubsystem->DisplayInfo(displayInfo);
		Add(windowSubsystem);
		
		printf("Adding Input subsystem\n");
		Add(new CInputSubsystem());
		
		printf("Adding Scene subsystem\n");
		Add(new CSceneSubsystem());
		
		printf("Adding Render subsystem\n");
		Add(new CRenderSubsystem());
	}
	
	void CTestGameApp::Configure()
	{
		printf("Configuring app\n");
		
		printf("Adding input key event\n");
		CInputSubsystem* inputSubsystem = GetSubsystem<CInputSubsystem>();
		auto keyInputManager = inputSubsystem->CreateKeyInputManager();
		keyInputManager->GetSignal(EKeyState::RELEASE, SDLK_ESCAPE)->Connect(this, &CTestGameApp::ExitApp);
		
		Load();
		
		/*
		pressAction = [this, inputSubsystem]()
		{
			printf("+ Key pressed\n");
			auto keyInputManager = inputSubsystem->CreateKeyInputManager();
			keyInputManager->Deregister(EKeyState::RELEASE, releaseToEraseAction);
		};
		
		releaseToEraseAction = []()
		{
			printf("+ I'm going to be deleted\n");
		};
		
		releaseAction = []()
		{
			printf("+ Key M released\n");
		};
		*/
		
		//auto mouseInputManager = inputSubsystem->CreateMouseInputManager();
		
		/*
		mouseInputManager->GetSignal(EMouseEvent::MOTION).Connect([](const TMouseEvent& event)
		{
			if(event.buttonState == EKeyState::PRESS)
			{
				printf("PRESS\n");
			}
			else if(event.buttonState == EKeyState::HOLD)
			{
				printf("HOLD\n");
			}
			else if(event.buttonState == EKeyState::RELEASE)
			{
				printf("RELEASE\n");
			}
			printf("Mouse coordinates [%d, %d]\n", event.x, event.y);
		});
		*/
		
		/*
		mouseInputManager->GetSignal(EMouseEvent::BUTTON_DOWN).Connect([](const TMouseEvent& event)
		{
			printf("Button DOWN coordinates [%d, %d]\n", event.x, event.y);
		});
		
		mouseInputManager->GetSignal(EMouseEvent::BUTTON_UP).Connect([](const TMouseEvent& event)
		{
			printf("Button UP coordinates [%d, %d]\n", event.x, event.y);
		});
		
		auto connection = keyInputManager->GetSignal(EKeyState::RELEASE)->Connect([]() { printf("+ I'm a lambda\n");});
		
		keyInputManager->GetSignal(EKeyState::RELEASE, 'm')->Connect(releaseAction);
		
		CSceneSubsystem* sceneSubsystem = GetSubsystem<CSceneSubsystem>();
		CSceneManager* sceneManager = sceneSubsystem->SceneManager();
		
		GameObject* gameObject = new GameObject("EmptyGameObject");
		
		gameObject->CreateComponent<CTransform>();
		Transform* transform = gameObject->GetComponent<CTransform>();
		gameObject->RemoveComponent(transform);
		gameObject->AddComponent(transform);
		gameObject->DestroyComponent(transform);
		
		CScene* scene = new CScene("TestScene");
		scene->Add((gameObject));
		scene->Remove(gameObject);
		
		sceneManager->Add(scene);
		*/
	}

	void CTestGameApp::ExitApp()
	{
		printf("+ Ask for termination\n");
		AskForTermination(true);
	}
	
	void CTestGameApp::Load()
	{
		printf("+ Started MD3 loading\n");
		
		GetCurrentDir();
		
		// Layer creation
		CRenderLayerManager& layerManager = CRenderLayerManager::Instance();
		layerManager.Add("GUI");
		
		printf("LM Count: %d \n", layerManager.Count());
		printf("LM Default Index: %d \n", layerManager.LayerIndex("Default"));
		printf("LM GUI Index: %d \n", layerManager.LayerIndex("GUI"));
		printf("LM OTHER Index: %d \n", layerManager.LayerIndex("OTHER"));
		printf("LM OTHER Exists: %d \n", layerManager.Exists("OTHER"));

		// Model load
		std::string headModelPath = "./assets/model_head.md3";
		std::string torsoModelPath = "./assets/model_upper.md3";
		std::string legsModelPath = "./assets/model_lower.md3";
		
		CLoadMD3 loadMd3;
		CArray<CMesh*> meshArray = loadMd3.Load(headModelPath.c_str());
		
		// Assign to model
		CModel* model = new CModel(meshArray);
		
		// GameObject creation
		CGameObject* gameObject = new CGameObject("DrawGameObject", "GUI");
		
		CGameObject* cameraGO = new CGameObject("MainCamera", "GUI");
		
		// Component addition
		gameObject->CreateComponent<CTransform>();
		gameObject->CreateComponent<CModelComponent>();
		gameObject->CreateComponent<CRendererComponent>();
		
		cameraGO->CreateComponent<CTransform>();
		cameraGO->CreateComponent<CCameraComponent>();
		
		// Component configuration
		gameObject->GetComponent<CModelComponent>()->Model(model);
		
		// Scene creation
		CSceneSubsystem* sceneSubsystem = GetSubsystem<CSceneSubsystem>();
		sceneSubsystem->CreateScene("TestScene");
		sceneSubsystem->SetCurrentScene("TestScene");
		
		// Adding GO to scene
		sceneSubsystem->SceneManager()->Scene("TestScene")->Add(gameObject);
		
		
		
		/*
		tModel* modelHead = new tModel();
		std::memset(modelHead,  0, sizeof(tModel));
		const bool headLoaded = loadMd3.ImportMD3(modelHead, headModelPath.c_str(), modelHead->scale);
		
		tModel* modelTorso = new tModel();
		std::memset(modelTorso,  0, sizeof(tModel));
		const bool torsoLoaded = loadMd3.ImportMD3(modelTorso, torsoModelPath.c_str(), modelTorso->scale);
		
		tModel* modelLegs = new tModel();
		std::memset(modelLegs,  0, sizeof(tModel));
		const bool legsLoaded = loadMd3.ImportMD3(modelLegs, legsModelPath.c_str(), modelLegs->scale);
		
		if(!headLoaded || !torsoLoaded || !legsLoaded)
		{
			printf("Problem loading MD3\n");
		}
		*/
	}
}
