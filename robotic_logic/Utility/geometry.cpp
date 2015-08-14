#include "geometry.h"

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
