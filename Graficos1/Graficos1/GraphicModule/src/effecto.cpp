#include "effecto.h"

void GraphicsModule::effecto::render()
{
	loopnum = initloop;
	for (int i = 0; i < pases.size(); i++){
		pases[i]->render(objts[i], loopnum);
		if (i == 8&&loopnum>0) {
			i = 6;
			loopnum--;
		}
	}
}
