#include "step.h"
#include "sys/stat.h"
#include "unistd.h"
#include "iostream"
#include "string"

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
      shapes.push_back(reader.Shape(i));
    }
    else
    {
      num_non_solids++;
    }
  }
  std::cout << "Translated " << shapes.size() << " solids. Ignored " << num_non_solids << " non-solids.\n";
}