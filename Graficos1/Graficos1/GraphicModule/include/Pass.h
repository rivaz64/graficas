#pragma once
#include<map>
#include<manager.h>
#include<Buffer.h>
#include<chader.h>
#include<string>
#include <vector>
#include <renderer.h>
#include<objeto.h>
#include<Textura.h>
namespace GraphicsModule {
	class Pass
	{
	public:
		int chadernum=0;
		int outnum = 0;
		static int outn;
		std::vector<chader>chaders;
		std::map<int, Buffer*> vc;
		std::map<int, Buffer*> pc;
		std::map<int, Textura*> pt;
		std::map<int, Buffer*> vt;
		bool ulti;
		Renderer ren;
		int size;
		vector<int> outs;
		static bool first;
		bool setear;
		void compile(std::string file, std::vector<std::string> tecnicas,bool ultimo,vector<int> n, SRV_DIMENSION d,bool set);
		void render( std::vector<objeto*> objts);
		
	};
}


