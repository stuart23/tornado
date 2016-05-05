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
#include <gp_Vec.hxx>

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
      gp_Pnt point1, point2;
      gp_Vec tangent1, tangent2;
      
      // Bisection for leading edge
   
    std::cout << "Bisecting";   
      double parameter_value = comp_curve.FirstParameter();
      double tolerance = 0.01;
      double step = 0.1;
      while ( true )
      {
	comp_curve.D1(parameter_value, point1, tangent1);
	std::cout << "X " << point1.X() << " Y " << point1.Y() << " Z " << point1.Z() << " parameter " << parameter_value << " step " << step << "\n";
	comp_curve.D1(parameter_value + step, point2, tangent2);
	std::cout << tangent1.Y() << "\n";
	if ( abs(tangent1.Y()) < tolerance )
	  break;
	else if ( tangent1.X() * tangent2.X() < 0 )
	  step /= 2;
	else if ( point2.X() < point1.X())
	  step *= -1;
	else
	  parameter_value += step;
      }
	
      double delta_chord_parameter = (comp_curve.LastParameter() - comp_curve.FirstParameter()) / chord_divisions;
      double chord_location = comp_curve.FirstParameter();
      
      
      for (int chord_step = 0; chord_step < chord_divisions; chord_step++)
      {
	comp_curve.D0(chord_location, point1);
	// Theres probably a better way to do this!!!
	profiles(span_step, chord_step, 0) = (double) point1.X();
	profiles(span_step, chord_step, 1) = (double) point1.Y();
	profiles(span_step, chord_step, 2) = (double) point1.Z();
	chord_location += delta_chord_parameter;
      }
    }
    y_location += delta_y;
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