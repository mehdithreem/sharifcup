//
//  geometry.h
//  robotic_logic
//
//  Created by Nahal on 8/9/15.
//  Copyright (c) 2015 Nahal. All rights reserved.
//

#ifndef robotic_logic_geometry_h
#define robotic_logic_geometry_h
#include <math.h>
#include <iostream>
#include <limits>
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

namespace geometry{
	class Vector{
	public:
		double x,y;
		Vector(double _x , double _y);
		Vector operator +(const Vector& v)const;
		Vector operator *(const Vector& v)const;
		Vector operator /(const Vector& v)const;
		Vector operator /(double n)const;
		Vector operator -(const Vector& v)const;
		Vector operator -()const;
		void operator=(const Vector& v);
    bool operator ==(const Vector& v1);
		double size()const;
  };
  std::ostream& operator<<(std::ostream& out, const Vector& v);

	Vector cart2polar (Vector cart);
	bool polarComparator(const pair < Vector , Vector >& coord1 , const pair < Vector , Vector >& coord2);
	void sortCoordsByPolar(std::vector< geometry::Vector >& coords ,geometry::Vector center);
  bool IsIntersect(Vector a , Vector b ,Vector c ,Vector d);
  int sign(double x);
};



#endif
