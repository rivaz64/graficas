#include "effecto.h"

void GraphicsModule::effecto::render()
{
	//pases[0]->render(&v);
	for (int i = 0; i < pases.size(); i++){
		pases[i]->render(objts[i],i);
	}
}
