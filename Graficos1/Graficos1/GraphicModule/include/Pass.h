#pragma once
#include<map>
#include<manager.h>
#include<Buffer.h>
namespace GraphicsModule {
	class Pass
	{
	public:
#ifdef directX
		std::map<int, Buffer*> vc;
		std::map<int, Buffer*> pc;
		std::map<int, Buffer*> pt;
		std::map<int, Buffer*> vt;
#endif
#ifdef openGL
		std::map<int, Buffer*> vc;
		std::map<int, Buffer*> pc;
#endif
		void render();
	};
}


