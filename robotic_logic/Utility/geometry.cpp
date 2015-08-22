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

// namespace geometry{
//   bool IsIntersect(Vector a , Vector b ,Vector c ,Vector d){
//     double m1,m2,c1,c2;
//     if(a.x==b.x && c.x!=d.x){
//       bool s3,s4;
//       m2 = (c.y-d.y)/(c.x-d.x);
//       c2 = -c.y-m2*c.x;
//       //x-a.x= segment
//       s3 = (c.x-a.x)*(d.x-b.x)>=0 ;
//       s4 = (m2*a.x+c2+a.y)*(m2*b.x+c2+b.y)>=0 ;
//       cout << "r1" << endl;
//       return !(s3||s4);
//     }
//     if(a.x==b.x && c.x==d.x){
//       if(a.x!=c.x){
//       cout << "r2" << endl;
//         return false;
//     }
//       double min1 = min(a.y , b.y) , min2 = min(c.y , d.y) , max1 = max(a.y,b.y) , max2 = max(c.y,d.y);
//       if((min1>min2 && min1<max2)||(max1>min2 && max1<max2)){
//       cout << "r3" << endl;
//         return true;
//     }
//           cout << "r4" << endl;
//       return false;
//     }
//     if(a.x!=b.x && c.x==d.x){
//       bool s3,s4;
//       m1 = (a.y-b.y)/(a.x-b.x);
//       c1 = -a.y-m1*a.x;
//       //x-c.x= segment
//       s3 = (a.x-c.x)*(b.x-c.x)>=0 ;
//       s4 = (m1*c.x+c1+c.y)*(m1*d.x+c1+d.y)>=0 ;
//             cout << "r5" << endl;

//       return !(s3||s4);    
//     }
//     m1 = (a.y-b.y)/(a.x-b.x);
//     m2 = (c.y-d.y)/(c.x-d.x);
//     c1 = a.y-m1*a.x;
//     c2 = c.y-m2*c.x;
//     bool s1,s2;
//     s1 = (m1*c.x+c1-c.y)*(m1*d.x+c1-d.y)>=0 ;
//     s2 = (m2*a.x+c2-a.y)*(m2*b.x+c2-b.y)>=0 ;
//     s1 = s1|s2;
//           cout << "r6" << endl;

//     return !s1;
//   }
// }

namespace geometry {
	// Given three colinear points p, q, r, the function checks if
	// point q lies on line segment 'pr'
	bool onSegment(Vector p, Vector q, Vector r)
	{
	    if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
	        q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
	       return true;
	 
	    return false;
	}
	 
	// To find orientation of ordered triplet (p, q, r).
	// The function returns following values
	// 0 --> p, q and r are colinear
	// 1 --> Clockwise
	// 2 --> Counterclockwise
	int orientation(Vector p, Vector q, Vector r)
	{
	    // See 10th slides from following link for derivation of the formula
	    // http://www.dcs.gla.ac.uk/~pat/52233/slides/Geometry1x1.pdf
	    int val = (q.y - p.y) * (r.x - q.x) -
	              (q.x - p.x) * (r.y - q.y);
	 
	    if (val == 0) return 0;  // colinear
	 
	    return (val > 0)? 1: 2; // clock or counterclock wise
	}
	 
	// The main function that returns true if line segment 'p1q1'
	// and 'p2q2' intersect.
	bool IsIntersect(Vector p1, Vector q1, Vector p2, Vector q2)
	{
		if ((p1.x == p2.x && p1.y == p2.y) || (p1.x == q2.x && p1.y == q2.y) 
			|| (q1.x == p2.x && q1.y == p2.y) || (q1.x == q2.x && q1.y == q2.y))
			return false;

	    // Find the four orientations needed for general and
	    // special cases
	    int o1 = orientation(p1, q1, p2);
	    int o2 = orientation(p1, q1, q2);
	    int o3 = orientation(p2, q2, p1);
	    int o4 = orientation(p2, q2, q1);
	 
	    // General case
	    if (o1 != o2 && o3 != o4)
	        return true;
	 
	    // Special Cases
	    // p1, q1 and p2 are colinear and p2 lies on segment p1q1
	    if (o1 == 0 && onSegment(p1, p2, q1)) return true;
	 
	    // p1, q1 and p2 are colinear and q2 lies on segment p1q1
	    if (o2 == 0 && onSegment(p1, q2, q1)) return true;
	 
	    // p2, q2 and p1 are colinear and p1 lies on segment p2q2
	    if (o3 == 0 && onSegment(p2, p1, q2)) return true;
	 
	     // p2, q2 and q1 are colinear and q1 lies on segment p2q2
	    if (o4 == 0 && onSegment(p2, q1, q2)) return true;
	 
	    return false; // Doesn't fall in any of the above cases
	}
}