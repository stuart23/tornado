#include "vtkSmartPointer.h"
#include <vtkXMLPolyDataWriter.h>
#include "vtkPolyData.h"

class Vtk
{
public:
  Vtk();
  bool WriteFile(std::string output_filename);
  
private:
  vtkSmartPointer<vtkXMLPolyDataWriter> writer;
  vtkSmartPointer<vtkPolyData> polydata;
};