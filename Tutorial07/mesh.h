#pragma once
#include <initializer_list>
class mesh
{
	
public:
	struct vertex {
		float posi[3];
		float uv[2];
	};
	vertex* points;
	short* indices;
	
	short* getindices();
	void setindices(std::initializer_list<short> i);
	vertex* getvertex();
	void setvertex(std::initializer_list<vertex> i);
	//void setindices(WORD[] i);*/
};

