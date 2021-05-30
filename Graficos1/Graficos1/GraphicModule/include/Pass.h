#pragma once
#include<map>
#include<manager.h>
#include<Buffer.h>
namespace GraphicsModule {
	class Pass
	{
	public:
		std::map<int, Buffer*> vc;
		std::map<int, Buffer*> pc;

		void render();
	};
}


