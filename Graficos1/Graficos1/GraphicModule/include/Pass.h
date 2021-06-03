#pragma once
#include<map>
#include<manager.h>
#include<Buffer.h>
#include<chader.h>
#include<string>
#include <vector>
#include <renderer.h>
#include<objeto.h>
namespace GraphicsModule {
	class Pass
	{
	public:
		int chadernum=0;
		std::vector<chader>chaders;
		std::map<int, Buffer*> vc;
		std::map<int, Buffer*> pc;
		std::map<int, Buffer*> pt;
		std::map<int, Buffer*> vt;
		Renderer ren;
		static bool first;
		void compile(std::string file, std::vector<std::string> tecnicas);
		void render();// std::vector<objeto*>);
	};
}


