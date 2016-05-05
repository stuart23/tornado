#include "iostream"
#include "opencascade/STEPControl_Reader.hxx"
#include <BRepAlgoAPI_Section.hxx>
#include <BRepAdaptor_CompCurve.hxx>
#include <armadillo>

class Mesh
{
public:
  Mesh(TopoDS_Shape wing_argument);
  void createProfiles(int input_spanwise_divisions, int input_chord_divisions);
  void createQuads();
  
  TopoDS_Shape wing;
  arma::Cube<double> profiles();
  std::vector<std::array<std::array<double, 3>, 4>> quads;
  int spanwise_divisions;
  int chord_divisions;
  
private:
  bool getSectionEdges(BRepAlgoAPI_Section section, BRepAdaptor_CompCurve* comp_curve);
};