#pragma once
#include"Pass.h"
#include<map>
#include<objeto.h>
namespace GraphicsModule {
	class effecto
	{
	public:
		std::vector<Pass*>pases;
		std::vector<std::vector<objeto*>*>objts;
		void render();

		//render();
	};

}

