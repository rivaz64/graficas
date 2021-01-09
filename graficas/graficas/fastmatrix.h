#pragma once
template<class T>
class fastmatrix
{
public:

	char* pointer;
	int pich,size;
	fastmatrix() {
		size = sizeof(T);
	}
	void setsize(int x, int y) {
		pointer = new char[x * y * size];
		pich = x * size;
	}
	void setelement(int x, int y, T a) {
		*(T*)((int)pointer + x * size + y * pich) = a;
	}
	T* getelement(int x, int y) {
		return (T*)((int)pointer + x * size + y * pich);
	}
	
};

