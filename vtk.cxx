#include "vtk.h"
#include "iostream"
#include "vtkPoints.h"

Vtk::Vtk()
{
  writer = vtkSmartPointer<vtkXMLPolyDataWriter>::New();
  polydata = vtkSmartPointer<vtkPolyData>::New();

  
  std::cout << "DONE";
}

void Vtk::AddLine(std::array<float, 3> point1, std::array<float, 3> point2)
{
  vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
 
  points->InsertNextPoint(point1);
  points->InsertNextPoint(point2);
  
  polydata->SetPoints(points);
 
}

bool Vtk::WriteFile(std::string output_filename)
{
  writer->SetFileName(output_filename.c_str());
  writer->SetInputData(polydata);
  writer->Write();
  
  return true;
}