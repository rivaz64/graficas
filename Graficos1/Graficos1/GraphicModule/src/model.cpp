#include "model.h"
GraphicsModule::model::~model()
{
	for (mesh* m : modelo) {
		delete m;
	}
}