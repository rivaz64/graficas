#include "effecto.h"

void GraphicsModule::effecto::render()
{
	//pases[0]->render(&v);
	for (int i = 0; i < pases.size(); i++){
		if(i== pases.size()-1)
		pases[i]->render(objts[i],false);
		else
		pases[i]->render(objts[i], pases[i+1]->clear);
	}
}
