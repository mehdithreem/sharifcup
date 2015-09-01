#include "../Include/geometry.h"

#define PI 3.14159265
using namespace geometry;

namespace geometry{
    
    Vector :: Vector(){}
    Vector :: Vector(double _x , double _y){
        x = _x;
        y = _y;
    }
    
    bool Vector::operator <(const Vector &v) const {
        return x < v.x || (x == v.x && y < v.y);
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
    
    bool Vector::operator ==(const Vector& v){
        return (v.x==x && v.y==y);
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
    int sign(double x){
        return (0<x)-(x<0);
    }
    
    double cross(const Vector &O, const Vector &A, const Vector &B){
        return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
    }
    
    vector<Vector> convex_hull(vector<Vector> P){
        int n = P.size(), k = 0;
        vector<Vector> H(2*n);
        sort(P.begin(), P.end());
        for (int i = 0; i < n; ++i) {
            while (k >= 2 && cross(H[k-2], H[k-1], P[i]) <= 0) k--;
            H[k++] = P[i];
        }
        for (int i = n-2, t = k+1; i >= 0; i--) {
            while (k >= t && cross(H[k-2], H[k-1], P[i]) <= 0) k--;
            H[k++] = P[i];
        }
        
        H.resize(k);
        return H;
    }


    int angleDiff(Vector v , Vector u){
      double dot = v.x*u.x + v.y*u.y;
      double det = v.x*u.y - v.y*u.x;
      return atan2 (det,dot) * 180 / PI;
    }
}

namespace geometry{
    bool IsIntersect(Vector a , Vector b ,Vector c ,Vector d){
        int s1,s2,t1,t2;
        s1 = sign((c.x-d.x)*(a.y-c.y)-(c.y-d.y)*(a.x-c.x));
        s2 = sign((c.x-d.x)*(b.y-c.y)-(c.y-d.y)*(b.x-c.x));
        
        t1 = sign((a.x-b.x)*(c.y-a.y)-(a.y-b.y)*(c.x-a.x));
        t2 = sign((a.x-b.x)*(d.y-a.y)-(a.y-b.y)*(d.x-a.x));
        
        if((s1&s2&t1&t2)==0){
            if(t1==t2 || s1==s2)
                return false;
            if(a==c || a==d || b==c || b==d || c==d)
                return false;
            return true;
        }
        
        if (s1 != s2 && t1 != t2)
            return true;
        
        return false;
    }
}

