#include "step.h"
#include "sys/stat.h"
#include "unistd.h"
#include "iostream"
#include "string"
#include <Bnd_Box.hxx>
#include <BRepBndLib.hxx>

Step::Step(std::string input_filename)
{
  filename = input_filename;
  loadFile(filename);
}

bool Step::loadFile(std::string filename)
{
  if ( access( filename.c_str(), F_OK ) == -1 )
  { 
    throw std::invalid_argument( "File is not readable" );
  }
  
  IFSelect_ReturnStatus stat = reader.ReadFile(filename.c_str() ); 
  if ( stat != 1 )
  {
    throw std::invalid_argument( "Step file transfer failed" );
  }

  reader.TransferRoot();
  std::cout << "Step file contains " << reader.NbShapes() << " shapes.\n";
  int num_non_solids = 0;
  for (int i = 1; i < reader.NbShapes() + 1; i++)
  {
    if ( reader.Shape(i).ShapeType() == TopAbs_SOLID )
    {
      shapes.push_back(reader.Shape(i))
      ;
    }
    else
    {
      num_non_solids++;
    }
  }
  std::cout << "Translated " << shapes.size() << " solids. Ignored " << num_non_solids << " non-solids.\n";
}

std::array<float, 6> Step::getExtents(TopoDS_Shape the_shape)
{
  Standard_Real xmin, ymin, zmin, xmax, ymax, zmax; 
  Bnd_Box B;
  BRepBndLib::Add(the_shape, B);
  B.Get(*&xmin, *&ymin, *&zmin, *&xmax, *&ymax, *&zmax);
  return std::array<float, 6>{(float) xmin, (float) ymin, (float) zmin, (float) xmax, (float) ymax, (float) zmax};
}

std::array<float, 2> Step::getXExtents(TopoDS_Shape the_shape)
{
  return std::array<float, 2>{getExtents(the_shape)[0], getExtents(the_shape)[3]};
}

std::array<float, 2> Step::getYExtents(TopoDS_Shape the_shape)
{
  return std::array<float, 2>{getExtents(the_shape)[1], getExtents(the_shape)[4]};
}

std::array<float, 2> Step::getZExtents(TopoDS_Shape the_shape)
{
  return std::array<float, 2>{getExtents(the_shape)[2], getExtents(the_shape)[5]};
}
