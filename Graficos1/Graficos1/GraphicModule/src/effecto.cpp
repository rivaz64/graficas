#include "effecto.h"

void GraphicsModule::effecto::render()
{
	//pases[0]->render(&v);
	for (int i = 0; i < pases.size(); i++){
		if (i == 1) {
			int zx = 0;
		}
		pases[i]->render(objts[i],true);
	}
}
