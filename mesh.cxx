#include "mesh.h"
#include "step.h"
#include <BRepAlgoAPI_Section.hxx>
#include <gp_Pln.hxx>
#include <Bnd_Box.hxx>
#include <BRepBndLib.hxx>
#include "Standard_Macro.hxx"


Mesh::Mesh(TopoDS_Shape wing, int spanwise_divisions)
{
  std::array<float, 2> y_extents = Step::getYExtents(wing);
  std::vector<BRepAlgoAPI_Section> sections;
  
  float delta_y = (y_extents[1]-y_extents[0])/spanwise_divisions;
  for (float y_station = y_extents[0]; y_station <= y_extents[1]; y_station += delta_y)
  {
    gp_Pln section_plane = gp_Pln(gp_Pnt(0.0,y_station,0.0), gp_Dir(0,1,0));
    BRepAlgoAPI_Section section = BRepAlgoAPI_Section(wing, section_plane);
    Handle<TopoDS_TShape> stu = section.Shape().TShape();
    std::cout << section.Shape().ShapeType() << "\n";
    /*
    TopTools_ListOfShape edges = section.SectionEdges();
    if ( edges.Extent() > 0 )
    {
      for ( TopoDS_Shape q : edges )
      {
        std::array<float, 2> chord = Step::getXExtents(q);
        std::cout << "station: " << y_station << " x min " << chord[0] << " x max " << chord[1] << " type: " << q.ShapeType() << "\n";
      }
    }
    */
    
    //for (TopoDS_Shape b = a.begin(); b != a.end(); b++)
    //{
    //std::array<float, 2> chord = Step::getXExtents(b);
    //std::cout << "station: " << y_station << " x min " << chord[0] << " x max " << chord[1] << "\n";
      
    //}
    //sections.push_back(BRepAlgoAPI_Section(wing, section_plane, true));
    //std::cout << "station: " << y_station << " x min " << chord[0] << " x max " << chord[1] << "\n";
    //std::cout << section.Shape().ShapeType() << "\n";
    //std::cout << (section.Shape().ShapeType() == TopAbs_COMPOUND ) << "\n";
    //std::cout << "a";
  }
}