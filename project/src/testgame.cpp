//
//  testgame.cpp
//  dcpp
//
//  Created by Jorge López on 21/4/16.
//  Copyright © 2016 Jorge López. All rights reserved.
//

#include "testgame.h"

#include "testhfsm.h"

#include <material/material.h>

#include <renderer/renderlayermanager.h>
#include <persist/md3/md3loader.h>
#include <persist/obj/objloader.h>

#include <containers/array.h>
#include <containers/forwardlist.h>

#include <signals/signal.h>

#include <dir/directory.h>

#include <cstdio>
#include <cstring>

#include <stdio.h>
#include <stdlib.h>

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
		
		ConfigureScene();
		
	}

	void CTestGameApp::ExitApp()
	{
		printf("+ Ask for termination\n");
		AskForTermination(true);
	}
	
	void CTestGameApp::ConfigureScene()
	{
		GetCurrentDir();
		/*
		 int* p=0;
		 CSignal<void(int*)> exampleSig;
		 exampleSig(p);
		 
		 CSignal<void(CShaderProgram)> shaderSignal;
		 shaderSignal(shaderProg);
		 */
		//shaderSignal(std::forward<CShaderProgram>(shaderProg));
		
		//

		// Layer creation
		CRenderLayerManager& layerManager = CRenderLayerManager::Instance();
		layerManager.Add("GUI");
		
		PrintRenderLayerInfo(layerManager);
		
		// Model creation
		CModel* model = CreateModel();
		
		// Drawable GameObject creation
		CGameObject* modelGO = new CGameObject("DrawGameObject", "GUI");
		
		// Component addition
		modelGO->AddComponent<CTransform>();
		modelGO->AddComponent<CModelComponent>();
		modelGO->AddComponent<CRendererComponent>();
		
		// Component configuration
		modelGO->GetComponent<CModelComponent>()->Model(model);
		
		// Camera GameObject creation
		CGameObject* cameraGO = new CGameObject("MainCamera", "GUI");
		
		// Component addition
		cameraGO->AddComponent<CTransform>();
		cameraGO->AddComponent<CCameraComponent>();
		
		// Component configuration
		cameraGO->GetComponent<CCameraComponent>()->BackgroundColor(math::ColorRGBf::Green());
		
		// Scene creation
		CSceneSubsystem* sceneSubsystem = GetSubsystem<CSceneSubsystem>();
		sceneSubsystem->CreateScene("TestScene");
		sceneSubsystem->SetCurrentScene("TestScene");
		
		// Adding GO to scene
		CScene* scene = sceneSubsystem->SceneManager()->Scene("TestScene");
		scene->Add(modelGO);
		scene->Add(cameraGO);
	}
	
	CModel* CTestGameApp::CreateModel()
	{
		printf("+ Started MD3 loading\n");
		
		// Model load
		std::string headModelPath = "./assets/model_head.md3";
		std::string torsoModelPath = "./assets/model_upper.md3";
		std::string legsModelPath = "./assets/model_lower.md3";
		
		const char* cubePath = "./assets/cube.obj";
		
		CObjLoader objLoader;
		objLoader.Load(cubePath);
		
		// Creation of model
		CMD3Loader md3Loader;
		CArray<CMesh*> meshArray = md3Loader.Load(headModelPath.c_str());
		
		// Material creation
		CMaterial* material = CreateMaterial();
		
		CModel* model = new CModel();
		for(CMesh* mesh : meshArray)
		{
			model->Add(material, mesh);
		}
		return model;
	}
	
	CMaterial* CTestGameApp::CreateMaterial()
	{
		printf("Creating a Material\n");
		CShader vertexShader = LoadTestVS();
		CShader fragmentShader = LoadTestFS();
		
		CShaderProgram shaderProg;
		shaderProg.Add(vertexShader);
		shaderProg.Add(fragmentShader);
		
		shaderProg.Compile();
		
		CMaterial* material = new CMaterial("BasicMaterial");
		material->AddProperty<CShaderProgram>("ShaderProgram", shaderProg);
		
		printf("Material created!\n");
		return material;
	}
	
	CShader CTestGameApp::LoadTestVS()
	{
		const char* filePath = "./assets/StandardShading.vertexshader";
		return LoadShader(filePath, EShaderType::VERTEX_SHADER);
	}
	
	CShader CTestGameApp::LoadTestFS()
	{
		const char* filePath = "./assets/StandardShading.fragmentshader";
		return LoadShader(filePath, EShaderType::FRAGMENT_SHADER);
	}
	
	CShader CTestGameApp::LoadShader(const char* filePath, const EShaderType type)
	{
		FILE* fp = fopen(filePath, "r");
		
		if(!fp)
		{
			printf("File not found: %s!\n", filePath);
			return 0;
		}
		long lSize;
		
		fseek( fp , 0L , SEEK_END);
		lSize = ftell( fp );
		rewind( fp );
		
		/* allocate memory for entire content */
		char* buffer = (char*) malloc(lSize * sizeof(char));
		if( !buffer )
		{
			fclose(fp);
			fputs("memory alloc fails", stderr);
			exit(1);
		}
		
		/* copy the file into the buffer */
		if(fread( buffer , lSize, 1 , fp) != 1)
		{
			fclose(fp);
			free(buffer);
			fputs("entire read fails", stderr);
			exit(1);
		}
		
		/* do your work here, buffer is a string contains the whole text */
		CShader shader(type);
		shader.Create(buffer);
		
		fclose(fp);
		free(buffer);
		
		return shader;
	}
	
	void CTestGameApp::PrintRenderLayerInfo(const CRenderLayerManager& layerManager)
	{
		printf("LM Count: %d \n", layerManager.Count());
		printf("LM Default Index: %d \n", layerManager.LayerIndex("Default"));
		printf("LM GUI Index: %d \n", layerManager.LayerIndex("GUI"));
		printf("LM OTHER Index: %d \n", layerManager.LayerIndex("OTHER"));
		printf("LM OTHER Exists: %s \n", layerManager.Exists("OTHER") ? "true" : "false");
	}
}
