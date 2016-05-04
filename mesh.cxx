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
#include <cstring>


Mesh::Mesh(TopoDS_Shape input_wing)
{
  wing = input_wing;
  createProfiles(30, 30);
}

void Mesh::createProfiles(int spanwise_divisions, int chord_divisions)
{
  profiles = boost::extents[spanwise_divisions][chord_divisions][3];
  std::array<float, 2> y_extents = Step::getYExtents(wing);
  std::vector<BRepAlgoAPI_Section> sections;
  
  float delta_y = (y_extents[1]-y_extents[0])/spanwise_divisions;
  float y_location = y_extents[0];
  for (int span_step = 0; span_step <= spanwise_divisions; span_step++)
  {
    gp_Pln section_plane = gp_Pln(gp_Pnt(0.0,y_location,0.0), gp_Dir(0,1,0));
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
      
      double delta_chord_parameter = (comp_curve.LastParameter() - comp_curve.FirstParameter()) / chord_divisions;
      double chord_location = comp_curve.FirstParameter();
      
      for (int chord_step = 0; chord_step < chord_divisions; chord_step++)
      {
	comp_curve.D0(chord_location, point);
	std::memcpy(profiles[span_step][chord_step], {(double) point.X(), (double) point.Y(), (double) point.Z()}, 3*sizeof(double));
	chord_location += delta_chord_parameter;
      }
      profiles.push_back(profile);
    }
    y_location += delta_y;
  }
}

void Mesh::createQuads()
{
  if ( profiles.size == 0 )
  {
    throw std::invalid_argument( "Quads cannot be generated until profiles have first been created." );
  }
  int spanwise_divisions = profiles.size();
  int chordwise_divisions = profiles[0].size();
  
  int number_of_quads = (spanwise_divisions - 1) * (chordwise_divisions - 1);
  quads.resize(number_of_quads);
  for (int index = 0; index < number_of_quads; index++)
  {
      
}