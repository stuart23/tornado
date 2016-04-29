#include <iostream>
#include <array>

class Geometry
{
public:
  Geometry();
  
  int fnx;                  //number of panels on flap chords (2d array)
  int ny;                   //number of panels in span (2d array)
  int nx;                   //number of panels on chord (2d array)
  int fsym;                 //flap deflection symmetry boolean bit  (2d array)
  float fc;                 //flap chord in percent of wingchord (2d array)
  int control_surfaces;     //flapped partition(wing part) boolean bit (2d array)
  float tw;                 //partition twist (3d array)<1 inboard, 2 outboard>
  float foil;               //Partition airfoils (3d array)
  float T;                  //Taper ratio (2d array)
  float sw;                 //Sweep (2d array)
  float c;                  //Root chord (2d array)
  float dihedral;           //Dihedral (2d array)
  float b;                  //span(distance root->tip chord) (2d array)
  bool symetric;            //Wing symmetry boolean bit (2d array)
  float startx;             //Partition starting coordinate (2d array)
  float starty;             // ---"----
  float startz;             // ---"----
  int nwing;                //number of wings (scalar)
  int nelem;                //number of partitions on each wing (1d array)
  std::array<float, 3> flap_vector;          //Flap deflection vector
  std::array<float, 3> ref_point;      //System reference point
  std::array<float, 3> cg;             //System center of gravity (around which all rotations occur)
};