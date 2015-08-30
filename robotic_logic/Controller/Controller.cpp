#include"Controller.h"
geometry::Vector  setV(vector<geometry::Vector> path , geometry::Vector velocity){
  geometry::Vector dx = path[1] - path[0];
  //if((dx - velocity).size()<maxV)
  return dx-velocity;
}
