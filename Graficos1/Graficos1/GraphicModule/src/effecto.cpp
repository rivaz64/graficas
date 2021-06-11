#include "effecto.h"

void GraphicsModule::effecto::render(std::vector<objeto*> v)
{
	pases[0]->render(v);
	for (int i = 1; i < pases.size(); i++){
		pases[i]->render(objts[i - 1]);
	}
}
