#include <iostream>
#include <vector>
#include "../Include/geometry.h"
using namespace std;
using namespace geometry;

int main(){
  double _x,_y;
  Vector test(10,10);
  vector <Vector> k;
  while(cin>>_x>>_y){
    Vector in(_x , _y);
    cout<<in+test<<endl;
    cout<<in*test<<endl;
    cout<<in/2<<endl;
    cout<<in/test<<endl;
    cout<<in-test<<endl;
    cout<<-in<<endl;
    cout<<in.size()<<endl;
    test = in;
    cout<<cart2polar(test);
    k.push_back(test);
    cout<<test<<endl;
    sortCoordsByPolar(k , Vector(0,0));
    for(int i=0 ; i<k.size() ; i++)
      cout<<k[i]<<endl;
  }

}