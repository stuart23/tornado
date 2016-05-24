#include "iostream"
#include "opencascade/STEPControl_Reader.hxx"
#include <BRepAdaptor_CompCurve.hxx>
#include <gp_Pnt.hxx>
#include <armadillo>

class Mesh
{
public:
  Mesh(TopoDS_Shape wing_argument);
  void createProfiles(int input_spanwise_divisions, int input_chord_divisions);
  void createQuads();
  
  TopoDS_Shape wing;
  arma::Cube<double> profiles; // Slices = spanwise divisions. Cols = chordwise divisions. Rows = dimensions (3)
  std::vector<std::array<std::array<double, 3>, 4>> quads;
  int spanwise_divisions;
  int chord_divisions;
  
private:
  gp_Pnt getCurveLeadingEdge(BRepAdaptor_CompCurve comp_curve);
};