#include "iostream"
#include "opencascade/STEPControl_Reader.hxx"

class Mesh
{
public:
  Mesh(TopoDS_Shape wing, int spanwise_divisions);
};