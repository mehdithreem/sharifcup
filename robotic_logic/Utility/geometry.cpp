#include "../Include/geometry.h"

#define PI 3.14159265
using namespace geometry;

namespace geometry{

	Vector :: Vector(double _x , double _y){
			x = _x;
			y = _y;
	}

	Vector Vector:: operator +(const Vector& v)const{
			return Vector(x+v.x , y+v.y);
	}

	Vector Vector:: operator *(const Vector& v)const{
			return Vector(x*v.x , y*v.y);
	}

	Vector Vector:: operator /(const Vector& v)const{
			if( v.x==0 && v.y==0)
					throw "Dividion by Zero";
			return Vector(x/v.x , y/v.y);
	}

	Vector Vector:: operator /(double n)const{
			if( n==0)
					throw "Dividion by Zero";
			return Vector(x/n , y/n);
	}


	Vector Vector:: operator -(const Vector& v)const{
			return Vector(x-v.x , y-v.y);
	}

	Vector Vector:: operator -()const{
			return Vector(-x , -y);
	}

	void Vector:: operator=(const Vector& v){
		x=v.x; y=v.y;
	}
 
	double Vector:: size()const{
			return sqrt(x*x + y*y);
	}
}

namespace geometry{

	Vector cart2polar (Vector cart){
		double r,a;
		r=cart.size();
		
		if(cart.x == 0){
			a=-90;
			if (cart.y > 0)
				a = -a;
		}
		else
			a=atan(cart.y/cart.x)*180/PI;

		if (cart.x < 0 ){
			if(cart.y < 0)
				a -= 180;
			else
				a += 180;	
		}
		
		return Vector(r,a);
	}
}

namespace geometry{
	
  void sortCoordsByPolar(std::vector< geometry::Vector >& coords ,geometry::Vector center) { 
    vector<pair <geometry::Vector,geometry::Vector> > coordsTemp;
    for(int i=0 ; i<coords.size() ; i++){
      pair<geometry::Vector,geometry::Vector> t = make_pair(coords[i]-center , cart2polar(coords[i]-center));
      coordsTemp.push_back(t);
    }
    sort(coordsTemp.begin() , coordsTemp.end() , polarComparator);
    coords.clear();
    for(int i=0 ; i<coordsTemp.size() ; i++){
      coords.push_back(coordsTemp[i].first+center);
      // cout << coordsTemp[i].first+center << " + " << coordsTemp[i].second << endl;
    }
  }


	bool polarComparator(const pair < Vector , Vector >& coord1 , const pair < Vector , Vector >& coord2) {
    if(coord1.second.y==coord2.second.y)
      return coord1.second.x<coord2.second.x;
    else 
      return coord1.second.y<coord2.second.y;
  }

}

namespace geometry{
   std::ostream& operator<<(std::ostream& out, const Vector& v){
    return out<<"("<<v.x<<" , "<<v.y<<")";
  }
}

namespace geometry{
  bool IsIntersect(Vector a , Vector b ,Vector c ,Vector d){
    double m1,m2,c1,c2;
    m1 = (a.y-b.y)/(a.x-b.x);
    m2 = (c.y-d.y)/(c.x-d.x);
    c1 = a.y-m1*a.x;
    c2 = c.y-m2*c.x;
    return !(((m1*c.x+c1-c.y)*(m1*d.x+c1-d.y)>=0)|((m2*a.x+c2-a.y)*(m2*b.x+c2-b.y)>=0));
  }
}
