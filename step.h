#include "iostream"
#include <vector>
#include "opencascade/STEPControl_Reader.hxx"

class Step
{
public:	
  Step(std::string input_filename);
  std::vector<TopoDS_Shape> shapes;
  
private:
  bool loadFile(std::string filename);
  
  std::string filename; //Imported step filename
  STEPControl_Reader reader; //Open Cascade Step file reader
};