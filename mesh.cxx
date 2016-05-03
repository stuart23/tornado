#include "mesh.h"
#include "step.h"
#include <BRepAlgoAPI_Section.hxx>
#include <gp_Pln.hxx>
#include <Bnd_Box.hxx>
#include <BRepBndLib.hxx>
#include "Standard_Macro.hxx"
#include <ShapeAnalysis_FreeBounds.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Wire.hxx>
#include <TopoDS_Edge.hxx>
#include <BRepAdaptor_CompCurve.hxx>
#include <gp_Pnt.hxx>

Mesh::Mesh(TopoDS_Shape input_wing)
{
  wing = input_wing;
  createProfiles(30);
}

void Mesh::createProfiles(int spanwise_divisions)
{
  std::array<float, 2> y_extents = Step::getYExtents(wing);
  std::vector<BRepAlgoAPI_Section> sections;
  
  float delta_y = (y_extents[1]-y_extents[0])/spanwise_divisions;
  for (float y_station = y_extents[0]; y_station <= y_extents[1]; y_station += delta_y)
  {
    gp_Pln section_plane = gp_Pln(gp_Pnt(0.0,y_station,0.0), gp_Dir(0,1,0));
    BRepAlgoAPI_Section section = BRepAlgoAPI_Section(wing, section_plane);

    Handle(TopTools_HSequenceOfShape) edges = new TopTools_HSequenceOfShape();
    Handle(TopTools_HSequenceOfShape) wires = new TopTools_HSequenceOfShape();
    TopExp_Explorer explorer;
    for (explorer.Init(section.Shape(), TopAbs_EDGE); explorer.More(); explorer.Next())
    {
      edges->Append(TopoDS::Edge(explorer.Current()));
    }
    ShapeAnalysis_FreeBounds::ConnectEdgesToWires(edges, Precision::Confusion(), Standard_False, wires);
    
    if ( wires->Length() > 0 )
    {
      TopoDS_Wire first_wire = TopoDS::Wire(wires->Value(1));
      BRepAdaptor_CompCurve comp_curve = BRepAdaptor_CompCurve(first_wire, Standard_False);
      gp_Pnt point;
      std::vector<std::array<double, 3>> profile;
      float chord_divisions = 50;
      for (float param = comp_curve.FirstParameter(); param <= comp_curve.LastParameter(); param += (comp_curve.LastParameter() - comp_curve.FirstParameter()) / chord_divisions)
      {
	comp_curve.D0(param, point);
	profile.push_back({point.X(), point.Y(), point.Z()});
      }
      profiles.push_back(profile);
    }
  }
}