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
#include <material/texturemanager.h>

#include <renderer/renderlayermanager.h>

#include <persist/md3/md3loader.h>
#include <persist/obj/objloader.h>
#include <persist/shader/shaderloader.h>
#include <persist/texture/textureloader.h>
#include <persist/assets/assetloader.h>

#include <containers/array.h>
#include <containers/forwardlist.h>

#include <signals/signal.h>

#include <dir/directory.h>

#include <math/vector.h>

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
		
		printf("Asset Loader\n");
		m_assetLoader.Load("./assets/asset_config.json", m_assetManager);
		
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
		modelGO->GetComponent<CTransform>()->Translate(math::Vector3f(0.f, 0.f, 0.f));
		
		// Camera GameObject creation
		CGameObject* cameraGO = new CGameObject("MainCamera", "GUI");
		
		// Component addition
		cameraGO->AddComponent<CTransform>();
		cameraGO->AddComponent<CCameraComponent>();
		
		// Component configuration
		//cameraGO->GetComponent<CTransform>()->Translate(math::Vector3f(0.f, 0.f, -1.0f));
		
		math::Vector3f eye = math::Vector3f(0.f, 0.f, -1.0f);
		math::Vector3f direction = math::Vector3f::Forward();
		math::Vector3f up = math::Vector3f::Up();
		
		CCameraComponent* camera = cameraGO->GetComponent<CCameraComponent>();
		camera->BackgroundColor(math::ColorRGBf::Blue());
		
		math::Matrix4x4f projectionMatrix = math::Matrix4x4f::Perspective(90.f, SCR_WIDTH/(float)SCR_HEIGHT, 0.01f, 100.f);
		printf("Projection Matrix\n");
		PrintMatrix(projectionMatrix);
		camera->ProjectionMatrix(projectionMatrix);
		camera->ViewMatrix(math::Matrix4x4f::LookAt(eye, eye+direction, up));
		//camera->Configure(90.f, SCR_WIDTH/SCR_HEIGHT, 0.01f, 100.f);
		
		// Scene creation
		CSceneSubsystem* sceneSubsystem = GetSubsystem<CSceneSubsystem>();
		sceneSubsystem->CreateScene("TestScene");
		sceneSubsystem->SetCurrentScene("TestScene");
		
		// Adding GO to scene
		CScene* scene = sceneSubsystem->SceneManager()->Scene("TestScene");
		scene->Add(modelGO);
		scene->Add(cameraGO);
		
		// Enable depth test
		glEnable(GL_DEPTH_TEST);
		
		// Accept fragment if it closer to the camera than the former one
		glDepthFunc(GL_LESS);
		
		// Cull triangles which normal is not towards the camera
		//glEnable(GL_CULL_FACE);
	}
	
	CModel* CTestGameApp::CreateModel()
	{
		printf("+ Started Obj loading\n");
		
		const char* cubePath = "./assets/mesh/plane2.obj";
		
		// Creation of model
		CObjLoader objLoader;
		CArray<CMesh*> meshArray = objLoader.Load(cubePath);

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
		printf("Loading shaders\n");
		
		CShaderLoader shaderLoader;
		CShader vertexShader = shaderLoader.Load("./assets/shader/mvp_tex.vert", EShaderType::VERTEX_SHADER);
		CShader fragmentShader = shaderLoader.Load("./assets/shader/textured.frag", EShaderType::FRAGMENT_SHADER);
		
		CShaderProgram shaderProg;
		shaderProg.Create();
		
		shaderProg.Add(vertexShader);
		shaderProg.Add(fragmentShader);
		
		shaderProg.Compile();
		
		shaderProg.AttachAll();
		
		shaderProg.Link(CRenderer::Instance().VertexProperties());
		
		shaderProg.CreateUniform("MVP");
		shaderProg.CreateUniform("TextureSampler");
		
		printf("Loading texture\n");
		
		CTextureLoader textureLoader;
		CTexture* texture = textureLoader.Load("./assets/texture/uvtemplate01.jpg");
		
		m_textureManager.Add("uvtemplate01", texture);
		
		printf("Creating a Material\n");
		CMaterial* material = new CMaterial("BasicMaterial");
		material->AddProperty<CShaderProgram>("ShaderProgram", shaderProg, Activate, Deactivate);
		material->AddProperty<CTexture>("Texture", *texture, Activate, Deactivate);
		
		printf("Material created!\n");
		return material;
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
