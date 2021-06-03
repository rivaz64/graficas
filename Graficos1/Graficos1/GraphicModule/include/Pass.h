#pragma once
#include<map>
#include<manager.h>
#include<Buffer.h>
#include<chader.h>
#include<string>
#include <vector>
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
		void compile(std::string file, std::vector<std::string> tecnicas);
		void render();
	};
}


