#include "iostream"
#include "opencascade/STEPControl_Reader.hxx"
#include <vector>
#include <array>

class Mesh
{
public:
  Mesh(TopoDS_Shape wing_argument);
  void createProfiles(int spanwise_divisions);
  TopoDS_Shape wing;
  std::vector<std::vector<std::array<double,3>>> profiles;
};