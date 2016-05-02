#include "iostream"
#include <vector>
#include "opencascade/STEPControl_Reader.hxx"

class Step
{
public:	
  Step(std::string input_filename);
  std::vector<TopoDS_Shape> shapes;
  std::array<float, 2> getXExtents(TopoDS_Shape the_shape);
  
private:
  bool loadFile(std::string filename);
  std::array<float, 6> getExtents(TopoDS_Shape the_shape);
  
  std::string filename; //Imported step filename
  STEPControl_Reader reader; //Open Cascade Step file reader
};