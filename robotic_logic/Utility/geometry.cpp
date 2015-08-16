#include "../Include/geometry.h"

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
		if(cart.y == 0)
			a=std::numeric_limits<double>::infinity();
		else
			a=atan(cart.x/cart.y);
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
    for(int i=0 ; i<coordsTemp.size() ; i++)
      coords.push_back(coordsTemp[i].first+center);
  }


	bool polarComparator(const pair < Vector , Vector >& coord1 , const pair < Vector , Vector >& coord2) { 
    if(coord1.second.y>coord2.second.y)
      return true;
    else 
      return coord1.second.x>coord2.second.x;
  }

}

namespace geometry{
   std::ostream& operator<<(std::ostream& out, const Vector& v){
    return out<<"("<<v.x<<" , "<<v.y<<")";
  }
}