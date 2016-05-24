#include "vtkSmartPointer.h"
#include <vtkXMLPolyDataWriter.h>
#include <vtkCellArray.h>
#include "vtkPolyData.h"
#include "vtkPoints.h"
#include "array"
#include <armadillo>

class Vtk
{
public:
  Vtk();
  bool WriteFile(std::string output_filename);
  void AddLine(float* point1, float* point2);
  void AddLine(std::array<float, 3> point1, std::array<float, 3> point2);
  void AddProfile(arma::mat profile);
  
private:
  vtkSmartPointer<vtkXMLPolyDataWriter> writer;
  vtkSmartPointer<vtkPolyData> polydata;
  vtkSmartPointer<vtkPoints> points;
  vtkSmartPointer<vtkCellArray> lines;
};