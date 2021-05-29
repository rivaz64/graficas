#pragma once
#include "chader.h"
#include "objeto.h"
namespace GraphicsModule {
	class pase
	{
	public:
		chader chad;
		std::vector<objeto*> objts;
		void draw();
	};
}


