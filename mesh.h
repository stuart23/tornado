#include "iostream"
#include "opencascade/STEPControl_Reader.hxx"
#include "boost/multi_array.hpp"

class Mesh
{
public:
  Mesh(TopoDS_Shape wing_argument);
  void createProfiles(int spanwise_divisions, int chord_divisions);
  TopoDS_Shape wing;
  boost::multi_array<double, 3> profiles;
  std::vector<std::array<std::array<double, 3>, 4>> quads;
};