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
#include <gp_Vec.hxx>
#include <Standard_Macro.hxx>

Mesh::Mesh(TopoDS_Shape input_wing)
{
  wing = input_wing;
  createProfiles(20, 15);
}

void Mesh::createProfiles(int input_spanwise_divisions, int input_chord_divisions)
{
  spanwise_divisions = input_spanwise_divisions;
  chord_divisions = input_chord_divisions;
  
  profiles.reshape(3, chord_divisions, spanwise_divisions + 1);
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
      
      double leading_edge = getCurveLeadingEdge(comp_curve);
      double trailing_edge = getCurveTrailingEdge(comp_curve);
      
      Handle(Adaptor3d_HCurve) curve1 = comp_curve.Trim(leading_edge, trailing_edge, 0.1);
      Adaptor3d_HCurve comp_curve = *curve1;
      //std::cout << comp_curve.FirstParameter() << " " << comp_curve.LastParameter() << "\n";
      // I need to try with a 4 patch wing section to see if I can still get LE and TE
      
      gp_Pnt point1;
      
      double delta_chord_parameter = (comp_curve.LastParameter() - comp_curve.FirstParameter()) / chord_divisions;
      double chord_location = comp_curve.FirstParameter();
      
      
      for (int chord_step = 0; chord_step < chord_divisions; chord_step++)
      {
	comp_curve.D0(chord_location, point1);
	// Theres probably a better way to do this!!!
	profiles(0, chord_step, span_step) = (double) point1.X();
	profiles(1, chord_step, span_step) = (double) point1.Y();
	profiles(2, chord_step, span_step) = (double) point1.Z();
	chord_location += delta_chord_parameter;
      }
    }
    y_location += delta_y;
  }
}

double Mesh::getCurveLeadingEdge(BRepAdaptor_CompCurve comp_curve)
{
  /**<
   * Gives the parameter of the point at maximum X along a 
   * curve using a modified bisection method. This point is 
   * essentially the leading edge of the airfoil.
   * 
   * By starting at an arbitary point, a second point is
   * created by moving along the curve by the step value.
   * With these two points, if the second point has a higher
   * X value, it becomes the new base point for the next 
   * iteration. If the tangent vector of the first point is
   * in positive X, and the tangent vector of the second 
   * point is in negative X (or vice-versa), then the X max 
   * point has been overshot, so the step is halved, 
   * bringing the second point closer to the first. If the
   * second point has a lower X value than the first, the
   * wrong direction is being searched, so the step value is
   * multiplied by -1.
   */
  
  double parameter_value = comp_curve.FirstParameter();
  gp_Pnt point1, point2;
  gp_Vec tangent1, tangent2;
   
  double tolerance = 0.0001;
  double step = 0.1;
  while ( step > tolerance )
  {
    comp_curve.D1(parameter_value, point1, tangent1);
    comp_curve.D1(parameter_value + step, point2, tangent2);
    if ( tangent1.X() * tangent2.X() < 0 )
      step /= 2;
    else if ( point2.X() < point1.X())
      step *= -1;
    else
      parameter_value += step;
  }
  return parameter_value;
}

double Mesh::getCurveTrailingEdge(BRepAdaptor_CompCurve comp_curve)
{
  /**<
   * Gives the parameter of the point at minimum X along a 
   * curve using a modified bisection method. This point is 
   * essentially the trailing edge of the airfoil.
   * 
   * By starting at an arbitary point, a second point is
   * created by moving along the curve by the step value.
   * With these two points, if the second point has a lower
   * X value, it becomes the new base point for the next 
   * iteration. If the tangent vector of the first point is
   * in positive X, and the tangent vector of the second 
   * point is in negative X (or vice-versa), then the X max 
   * point has been overshot, so the step is halved, 
   * bringing the second point closer to the first. If the
   * second point has a lower X value than the first, the
   * wrong direction is being searched, so the step value is
   * multiplied by -1.
   */
  
  double parameter_value = comp_curve.FirstParameter();
  gp_Pnt point1, point2;
  gp_Vec tangent1, tangent2;
   
  double tolerance = 0.0001;
  double step = 0.1;
  while ( step > tolerance )
  {
    comp_curve.D1(parameter_value, point1, tangent1);
    comp_curve.D1(parameter_value + step, point2, tangent2);
    if ( tangent1.X() * tangent2.X() < 0 )
      step /= 2;
    else if ( point2.X() > point1.X())
      step *= -1;
    else
      parameter_value += step;
  }
  return parameter_value;
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