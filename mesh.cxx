#include "mesh.h"
#include "step.h"
#include <BRepAlgoAPI_Section.hxx>
#include <gp_Pln.hxx>

Mesh::Mesh(TopoDS_Shape wing, int spanwise_divisions)
{
  std::array<float, 2> y_extents = Step::getYExtents(wing);
  std::vector<BRepAlgoAPI_Section> sections;
  
  for (float y_station = y_extents[0]; y_station <= y_extents[1]; y_station += (y_extents[1]-y_extents[0])/spanwise_divisions)
  {
    gp_Pln section_plane = gp_Pln(gp_Pnt(0.0,y_station,0.0), gp_Dir(0,1,0));
    BRepAlgoAPI_Section section = BRepAlgoAPI_Section(wing, section_plane);
    //std::array<float, 2> chord = Step::getXExtents(section.Shape());
    //sections.push_back(BRepAlgoAPI_Section(wing, section_plane, true));
    //std::cout << "station: " << y_station << " x min " << chord[0] << " x max " << chord[1] << "\n";
    std::cout << section.Shape().ShapeType() << "\n";
    std::cout << (section.Shape().ShapeType() == TopAbs_COMPOUND ) << "\n";
    //std::cout << "a";
  }
}