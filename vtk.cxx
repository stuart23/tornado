#include "vtk.h"
#include "iostream"
#include "vtkLine.h"

Vtk::Vtk()
{
  writer = vtkSmartPointer<vtkXMLPolyDataWriter>::New();
  polydata = vtkSmartPointer<vtkPolyData>::New();
  points = vtkSmartPointer<vtkPoints>::New();
  lines = vtkSmartPointer<vtkCellArray>::New();
  
  std::cout << "DONE";
}

void Vtk::AddLine(float* point1, float* point2)
{
  vtkIdType start_point = points->InsertNextPoint(point1);
  vtkIdType end_point = points->InsertNextPoint(point2);
  
  polydata->SetPoints(points);
  
  vtkSmartPointer<vtkLine> line = vtkSmartPointer<vtkLine>::New();
  line->GetPointIds()->SetId(0, start_point);
  line->GetPointIds()->SetId(1, end_point);
  
  lines->InsertNextCell(line);
}
void Vtk::AddLine(std::array<float, 3> point1, std::array<float, 3> point2)
{
  AddLine(&point1[0], &point2[0]);
}

bool Vtk::WriteFile(std::string output_filename)
{
  polydata->SetLines(lines);
  writer->SetFileName(output_filename.c_str());
  writer->SetInputData(polydata);
  writer->Write();
  
  return true;
}