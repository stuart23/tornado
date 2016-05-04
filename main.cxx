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
  Mesh b = Mesh(a.shapes[0]);
  
  Vtk c = Vtk();
  
  

  /*for ( std::vector<std::array<double, 3>> profile : b.profiles)
    c.AddProfile(profile);
  
  c.WriteFile(std::string("My_vtk.vtp"));
  */
  return 0;
}
