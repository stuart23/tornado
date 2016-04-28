class state
{
public:
  state();
  
  float airspeed; //airspeed (m/s)
  float alpha; //angle of attack (rad)
  float beta; //angle of sideslip (rad)
  float p; //roll rate (rad/s)
  float q; //pitch rate (rad/s)
  float r; //yaw rate (rad/s)
  float alphadot; //Angle of attack time derivative (rad/s)
  float betadot; //Angle of sidesliptime derivative (rad/s)
  float altitude; //Altitude, meters.
  float density; //Air density, kg/m^3.
  float pgcorr; //Prandtl-Glauert compressibillity correction.

};