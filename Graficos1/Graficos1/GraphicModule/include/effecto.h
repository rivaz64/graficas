#pragma once
#include"Pass.h"
#include<map>
#include<objeto.h>
namespace GraphicsModule {
	class effecto
	{
		int loopnum = 2;
		
	public:
		int initloop = 2;
		std::vector<Pass*>pases;
		std::vector<std::vector<objeto*>*>objts;
		void render();

		//render();
	};

}

