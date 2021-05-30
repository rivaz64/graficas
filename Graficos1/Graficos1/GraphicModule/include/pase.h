#pragma once
#include "chader.h"
#include "objeto.h"
#include"Buffer.h"
#include<map>
namespace GraphicsModule {
	class pase
	{
	public:
		std::map<int,Buffer*> vc;
		std::map<int,Buffer*> pc;

		void render();
		//chader chad;
		//std::vector<objeto*> objts;
		//void draw();
	};
}


