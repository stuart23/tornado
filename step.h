#include "iostream"

class Step
{
public:	
  Step(std::string input_filename);
  
private:
  bool loadFile(std::string filename);
  
  std::string filename; //Imported step filename
  STEPControl_Reader reader; //Open Cascade Step file reader
};