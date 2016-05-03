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

void Vtk::AddProfile(std::vector<std::array<double, 3>> profile)
{
  std::vector<vtkIdType> point_ids;
  
  for (std::array<double, 3> profile_point : profile)
  {
    point_ids.push_back(points->InsertNextPoint(profile_point[0],profile_point[1],profile_point[2]));
    //cout << "X " << profile_point[0] << " Y " << profile_point[1] << " Z " << profile_point[2] << "\n";
  }
  cout << "array size: " << point_ids.size() << "\n";
  for (int index = 1; index < point_ids.size(); index++)
  {
    vtkSmartPointer<vtkLine> line = vtkSmartPointer<vtkLine>::New();
    line->GetPointIds()->SetId(0, point_ids[index - 1]);
    line->GetPointIds()->SetId(1, point_ids[index]);
    //cout << "index1 " << point_ids[index - 1] << " index2 " << point_ids[index] << "\n";
    lines->InsertNextCell(line);
  } 
}

bool Vtk::WriteFile(std::string output_filename)
{
  polydata->SetPoints(points);
  polydata->SetLines(lines);
  writer->SetFileName(output_filename.c_str());
  writer->SetInputData(polydata);
  writer->Write();
  
  return true;
}