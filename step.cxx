#include "step.h"
#include "sys/stat.h"
#include "unistd.h"
#include "iostream"
#include "string"
#include "stdexcept"

Step::Step(std::string input_filename)
{
  std::cout << input_filename;
  filename = input_filename;
  loadFile(filename);
}

bool Step::loadFile(std::string filename)
{
  std::cout << filename;
  if ( access( filename.c_str(), F_OK ) == -1 )
  {
    throw std::invalid_argument( "File is not readable" );
  }
  std::cout << "hello";
  try
  {
  IFSelect_ReturnStatus stat = reader.ReadFile(filename.c_str() ); 
  }
    catch (int e)
  {
    std::cout << "An exception occurred. Exception Nr. " << e << '\n';
  }
  //std::cout << reader.NbShapes();
  exit(69);
}