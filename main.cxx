#include "iostream"
#include "step.h"
#include "mesh.h"

int main(int argc, char **argv) {
  if ( argc != 2 )
  { 
    throw std::invalid_argument( "Wrong number of arguments. Invoke with \"tornado step_file.stp\"" );
  }
  Step a = Step(argv[1]);
  Mesh b = Mesh(a.shapes[0], 20);
  return 0;
}
