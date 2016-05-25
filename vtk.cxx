#include "vtk.h"
#include "iostream"
#include "vtkLine.h"
#include <armadillo>

Vtk::Vtk()
{
  writer = vtkSmartPointer<vtkXMLPolyDataWriter>::New();
  polydata = vtkSmartPointer<vtkPolyData>::New();
  points = vtkSmartPointer<vtkPoints>::New();
  lines = vtkSmartPointer<vtkCellArray>::New();
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

void Vtk::AddProfile(arma::mat profile)
{
  std::vector<vtkIdType> point_ids;
  
  for (int i = 0; i < profile.n_cols; ++i) {
    point_ids.push_back(points->InsertNextPoint(profile(0,i),profile(1,i),profile(2,i)));
    //cout << "X " << profile(0,i) << " Y " << profile(1,i) << " Z " << profile(2,i) << "\n";
  }
  
  //cout << "array size: " << point_ids.size() << "\n";
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
  
  std::cout << "File written to: " << output_filename << "\n"; 
  return true;
}