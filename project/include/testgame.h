//
//  testgame.hpp
//  dcpp
//
//  Created by Jorge López on 21/4/16.
//  Copyright © 2016 Jorge López. All rights reserved.
//

#ifndef testgame_hpp
#define testgame_hpp

#include "app.h"

#include <subsystem/windowsubsystem.h>
#include <subsystem/inputsubsystem.h>
#include <subsystem/scenesubsystem.h>
#include <subsystem/rendersubsystem.h>

#include <component/gameobject.h>
#include <component/transform.h>
#include <component/modelcomponent.h>
#include <component/renderercomponent.h>
#include <component/camera.h>

#include <mesh/model.h>
#include <material/shader.h>

#include <signals/signal.h>
#include <help/callbacks.h>

namespace dc
{
	class CTestGameApp : public CApp
	{
		friend class CSingleton<CApp>;
	protected:
		CTestGameApp() {}
		~CTestGameApp() {}

	public:
		void Create()		override;
		void Configure()	override;

	private:
		void ExitApp();
		
		void ConfigureScene();
		
		CModel* CreateModel();
		
		CMaterial*	CreateMaterial();
		CShader LoadTestVS();
		CShader LoadTestFS();
		
		CShader LoadShader(const char* filePath, const EShaderType type);
		
		void PrintRenderLayerInfo(const CRenderLayerManager& layerManager);
		
	private:
		TAction pressAction;
		TAction releaseAction;
		TAction releaseToEraseAction;
		TAction closeAction;
	};
}

#endif /* testgame_hpp */
