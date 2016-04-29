#include "geometry.h"

Geometry::Geometry()
{
  fnx=0;               
  ny=1;                
  nx=1;                
  fsym=0;              
  fc=0.0;                
  flapped=0;         
  tw=0;         
  foil=0.0;   
  T=1.0;                 
  sw=0.0;                
  c=1.0;                 
  dihedral=0.0;             
  b=1.0;                 
  symetric=true;          
  startx=0.0;            
  starty=0.0;            
  startz=0.0;            
  nwing=1;             
  nelem=1;             
  flap_vector = {0.0, 0.0, 0.0};       
  ref_point = {0.0, 0.0, 0.0};   
  cg = {0.0, 0.0, 0.0};
}