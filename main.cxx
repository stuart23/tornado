#include "iostream"
#include "step.h"
#include "mesh.h"
#include "vtk.h"

int main(int argc, char **argv) {
  if ( argc != 2 )
  { 
    throw std::invalid_argument( "Wrong number of arguments. Invoke with \"tornado step_file.stp\"" );
  }
  Step a = Step(argv[1]);
  Mesh b = Mesh(a.shapes[0], 20);
  
  Vtk c = Vtk();
  
  float pnt1 [3] = {0., 1., 2.};
  float pnt2 [3] = {3., 4., 5.};
  float pnt3 [3] = {6., 4., 1.};
  float pnt4 [3] = {8., 7., 9.};
  
  c.AddLine(pnt1, pnt2);
  c.AddLine(pnt2, pnt3);
  c.AddLine(pnt3, pnt4);
  c.WriteFile(std::string("My_vtk.vtp"));
  std::cout << "DOOOONE";
  
  return 0;
}
