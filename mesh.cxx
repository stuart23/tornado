#include "mesh.h"
#include "step.h"
#include <gp_Pln.hxx>
#include <Bnd_Box.hxx>
#include <BRepBndLib.hxx>
#include "Standard_Macro.hxx"
#include <ShapeAnalysis_FreeBounds.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Wire.hxx>
#include <TopoDS_Edge.hxx>
#include <gp_Pnt.hxx>

Mesh::Mesh(TopoDS_Shape input_wing)
{
  wing = input_wing;
  createProfiles(4, 4);
}

void Mesh::createProfiles(int input_spanwise_divisions, int input_chord_divisions)
{
  spanwise_divisions = input_spanwise_divisions;
  chord_divisions = input_chord_divisions;
  
  arma::Cube<double> profiles(spanwise_divisions + 1, chord_divisions, 3);
  std::array<float, 2> y_extents = Step::getYExtents(wing);
  std::vector<BRepAlgoAPI_Section> sections;
  
  float delta_y = (y_extents[1]-y_extents[0])/spanwise_divisions;
  float y_location = y_extents[0];
  for (int span_step = 0; span_step <= spanwise_divisions + 1; span_step++)
  {
    gp_Pln section_plane = gp_Pln(gp_Pnt(0.0,y_location,0.0), gp_Dir(0,1,0));
    gp_Pnt point;
    BRepAlgoAPI_Section section = BRepAlgoAPI_Section(wing, section_plane);
    BRepAdaptor_CompCurve comp_curve;
    std::cout << "hERE"  ;
    if ( getSectionEdges(section, &comp_curve) )
    {
      int k;
      double delta_chord_parameter = (comp_curve.LastParameter() - comp_curve.FirstParameter()) / chord_divisions;
      double chord_location = comp_curve.FirstParameter();
    
      for (int chord_step = 0; chord_step < chord_divisions; chord_step++)
      {
        comp_curve.D0(chord_location, point);
        // Theres probably a better way to do this!!!
        profiles(span_step, chord_step, 0) = (double) point.X();
        profiles(span_step, chord_step, 1) = (double) point.Y();
        profiles(span_step, chord_step, 2) = (double) point.Z();
        chord_location += delta_chord_parameter;
      }
    }
    y_location += delta_y;
  }
  profiles.print();
}

bool Mesh::getSectionEdges(BRepAlgoAPI_Section section, BRepAdaptor_CompCurve* comp_curve)
{
  Handle(TopTools_HSequenceOfShape) edges = new TopTools_HSequenceOfShape();
  Handle(TopTools_HSequenceOfShape) wires = new TopTools_HSequenceOfShape();
  TopExp_Explorer explorer;
  for (explorer.Init(section.Shape(), TopAbs_EDGE); explorer.More(); explorer.Next())
  {
    edges->Append(TopoDS::Edge(explorer.Current()));
  }
    
  ShapeAnalysis_FreeBounds::ConnectEdgesToWires(edges, Precision::Confusion(), Standard_False, wires);
  int j = wires->Length();
  if ( wires->Length() == 0 )
  {
    return false;
  }
  else
  {
    TopoDS_Wire first_wire = TopoDS::Wire(wires->Value(1));
    //comp_curve->Initialize(first_wire, Standard_False);
    return false;
  }
}

void Mesh::createQuads()
{
  /*Need to check if profiles created first...
  if ( profiles.size == 0 )
  {
    throw std::invalid_argument( "Quads cannot be generated until profiles have first been created." );
  }*/
  
  int number_of_quads = (spanwise_divisions - 1) * (chord_divisions - 1);
  quads.resize(number_of_quads);
  for (int index = 0; index < number_of_quads; index++)
  {
    
  }
}