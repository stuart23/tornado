#include "vtkSmartPointer.h"
#include <vtkXMLPolyDataWriter.h>
#include <vtkCellArray.h>
#include "vtkPolyData.h"
#include "vtkPoints.h"
#include "array"

class Vtk
{
public:
  Vtk();
  bool WriteFile(std::string output_filename);
  void AddLine(float* point1, float* point2);
  void AddLine(std::array<float, 3> point1, std::array<float, 3> point2);
  void AddProfile(std::vector<std::array<double, 3>> points);
  
private:
  vtkSmartPointer<vtkXMLPolyDataWriter> writer;
  vtkSmartPointer<vtkPolyData> polydata;
  vtkSmartPointer<vtkPoints> points;
  vtkSmartPointer<vtkCellArray> lines;
};