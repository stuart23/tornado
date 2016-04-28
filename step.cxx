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
  std::cout << reader.NbShapes();
}