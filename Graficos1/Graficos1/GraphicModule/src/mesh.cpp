#include "mesh.h"
namespace GraphicsModule {
    short* mesh::getindices()
    {
        return indices;
    }

    void mesh::setindices(std::initializer_list<short> i)
    {
        indices = (short*)i.begin();
    }

    mesh::vertex* mesh::getvertex()
    {
        return points;
    }

    void mesh::setvertex(std::initializer_list<vertex> i)
    {
        points = (vertex*)i.begin();
    }

}
