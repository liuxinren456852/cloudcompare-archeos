//##########################################################################
//#                                                                        #
//#                               CCLIB                                    #
//#                                                                        #
//#  This program is free software; you can redistribute it and/or modify  #
//#  it under the terms of the GNU Library General Public License as       #
//#  published by the Free Software Foundation; version 2 of the License.  #
//#                                                                        #
//#  This program is distributed in the hope that it will be useful,       #
//#  but WITHOUT ANY WARRANTY; without even the implied warranty of        #
//#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         #
//#  GNU General Public License for more details.                          #
//#                                                                        #
//#          COPYRIGHT: EDF R&D / TELECOM ParisTech (ENST-TSI)             #
//#                                                                        #
//##########################################################################

#ifndef CC_GEOM_HEADER
#define CC_GEOM_HEADER

#ifdef _MSC_VER
//To get rid of the really annoying warnings about template class exportation
#pragma warning( disable: 4251 )
#endif

#include "CCTypes.h"

//system
#include <math.h> //for sqrt, fabs

//! 3D Vector (templated version)
template <class Type> class Vector3Tpl
{
public:

	union
	{
		struct
		{
			Type x,y,z;
		};
		Type u[3];
	};

	//! Default constructor
	/** Inits vector to (0,0,0).
	**/
	inline Vector3Tpl(Type s = 0) : x(s),y(s),z(s) {}

	//! Constructor from a triplet of coordinates
	/** Inits vector to (x,y,z).
	**/
	inline Vector3Tpl(Type _x, Type _y, Type _z) : x(_x),y(_y),z(_z) {}

	//! Constructor from an array of 3 elements
	inline Vector3Tpl(const Type p[]) : x(p[0]),y(p[1]),z(p[2]) {}
	
	//! Copy constructor
	inline Vector3Tpl(const Vector3Tpl& v) : x(v.x),y(v.y),z(v.z) {}

	//! Dot product
	inline Type dot(const Vector3Tpl& v) const { return (x*v.x)+(y*v.y)+(z*v.z); }
	//! Cross product
	inline Vector3Tpl cross(const Vector3Tpl &v) const { return Vector3Tpl((y*v.z)-(z*v.y), (z*v.x)-(x*v.z), (x*v.y)-(y*v.x)); }
	//! Returns vector square norm
	inline Type norm2() const { return (x*x)+(y*y)+(z*z); }
	//! Returns vector norm
	inline Type norm() const { return sqrt(norm2()); }
	//! Sets vector norm to unity
	inline void normalize() { Type n = norm2(); if (n>0) *this /= sqrt(n); }
	//! Returns a normalized vector which is orthogonal to this one
	inline Vector3Tpl orthogonal() const { Vector3Tpl ort; vorthogonal(u, ort.u); return ort; }

	//! Inverse operator
	inline Vector3Tpl operator - () const { Vector3Tpl V(-x,-y,-z); return V; }
	//! In-place addition operator
	inline Vector3Tpl& operator += (const Vector3Tpl& v) { x+=v.x; y+=v.y; z+=v.z; return *this; }
	//! In-place substraction operator
	inline Vector3Tpl& operator -= (const Vector3Tpl& v) { x-=v.x; y-=v.y; z-=v.z; return *this; }
	//! In-place multiplication (by a scalar) operator
	inline Vector3Tpl& operator *= (Type v) { x*=v; y*=v; z*=v; return *this; }
	//! In-place division (by a scalar) operator
	inline Vector3Tpl& operator /= (Type v) { x/=v; y/=v; z/=v; return *this; }
	//! Addition operator
	inline Vector3Tpl operator + (const Vector3Tpl& v) const { return Vector3Tpl(x+v.x, y+v.y, z+v.z); }
	//! Substraction operator
	inline Vector3Tpl operator - (const Vector3Tpl& v) const { return Vector3Tpl(x-v.x, y-v.y, z-v.z); }
	//! Multiplication operator
	inline Vector3Tpl operator * (Type s) const { return Vector3Tpl(x*s, y*s, z*s); }
	//! Division operator
	inline Vector3Tpl operator / (Type s) const { return Vector3Tpl(x/s, y/s, z/s); }
	//! Cross product operator
	inline Vector3Tpl operator * (const Vector3Tpl& v) const { return cross(v); }
	//! Copy operator
	inline Vector3Tpl& operator = (const Vector3Tpl &v) { x=v.x; y=v.y; z=v.z; return *this; }
	//! Dot product operator
	inline Type operator && (const Vector3Tpl &v) const { return dot(v); }
	//! Direct coordinate access
	inline Type& operator [] (unsigned i) { return u[i]; }
	//! Direct coordinate access (const)
	inline const Type& operator [] (unsigned i) const { return u[i]; }

	static inline void vdivide(const Type p[], Type s, Type r[]) {r[0]=p[0]/s; r[1]=p[1]/s; r[2]=p[2]/s;}
	static inline void vdivide(Type p[], Type s) {p[0]/=s; p[1]/=s; p[2]/=s;}
	static inline void vmultiply(const Type p[], Type s, Type r[]) {r[0]=p[0]*s; r[1]=p[1]*s; r[2]=p[2]*s;}
	static inline void vmultiply(Type p[], Type s) {p[0]*=s; p[1]*=s; p[2]*=s;}
	static inline Type vdot(const Type p[], const Type q[]) {return (p[0]*q[0])+(p[1]*q[1])+(p[2]*q[2]);}
	static inline void vcross(const Type p[], const Type q[], Type r[]) {r[0]=(p[1]*q[2])-(p[2]*q[1]); r[1]=(p[2]*q[0])-(p[0]*q[2]); r[2]=(p[0]*q[1])-(p[1]*q[0]);}
	static inline void vcopy(const Type p[], Type q[]) {q[0]=p[0]; q[1]=p[1]; q[2]=p[2];}
	static inline void vset(Type p[], Type s) {p[0]=p[1]=p[2]=s;}
	static inline void vset(Type p[], Type x, Type y, Type z) {p[0]=x; p[1]=y; p[2]=z;}
	static inline void vadd(const Type p[], const Type q[], Type r[]) {r[0]=p[0]+q[0]; r[1]=p[1]+q[1]; r[2]=p[2]+q[2];}
	static inline void vsubstract(const Type p[], const Type q[], Type r[]) {r[0]=p[0]-q[0]; r[1]=p[1]-q[1]; r[2]=p[2]-q[2];}
	static inline void vcombination(Type a, const Type p[], Type b, const Type q[], Type r[]) {r[0]=(a*p[0])+(b*q[0]); r[1]=(a*p[1])+(b*q[1]); r[2]=(a*p[2])+(b*q[2]);}
	static inline void vcombination(const Type p[], Type b, const Type q[], Type r[]) {r[0]=p[0]+(b*q[0]); r[1]=p[1]+(b*q[1]); r[2]=p[2]+(b*q[2]);}
	static inline void vnormalize(Type p[]) {Type n = vnorm2(p); if (n>0) vdivide(p, sqrt(n));}
	static inline Type vnorm2(const Type p[]) {return (p[0]*p[0])+(p[1]*p[1])+(p[2]*p[2]);}
	static inline Type vdistance2(const Type p[], const Type q[]) {return ((p[0]-q[0])*(p[0]-q[0]))+((p[1]-q[1])*(p[1]-q[1]))+((p[2]-q[2])*(p[2]-q[2]));}
	static inline Type vnorm(const Type p[]) {return sqrt(vnorm2(p));}
	static inline Type vdistance(const Type p[], const Type q[]) {return sqrt(vdistance2(p, q));}

	static inline void vorthogonal(const Type p[], Type q[])
	{
		if (fabs(p[0]) <= fabs(p[1]) && fabs(p[0]) <= fabs(p[2]))
		{
			q[0]=0; q[1]=p[2]; q[2]=-p[1];
		}
		else if (fabs(p[1]) <= fabs(p[0]) && fabs(p[1]) <= fabs(p[2]))
		{
			q[0]=-p[2]; q[1]=0; q[2]=p[0];
		}
		else
		{
			q[0]=p[1]; q[1]=-p[0]; q[2]=0;
		}
		vnormalize(q);
	}

};

// Multiplication of a 3D vector by a scalar (front) operator
inline Vector3Tpl<float> operator * (float s, const Vector3Tpl<float> &v) {return v*s;}
inline Vector3Tpl<double> operator * (double s, const Vector3Tpl<double> &v) {return v*s;}

//! 2D Vector
template <class Type> class Vector2Tpl
{
public:

	union
	{
		struct
		{
			Type x,y;
		};
		Type u[2];
	};

	//! Default constructor
	/** Inits vector to (0,0).
		\param s default init value for both coordinates
	**/
	inline Vector2Tpl(Type s = 0) : x(s), y(s) {}

	//! Constructor from a couple of coordinates
	/** Inits vector to (x,y).
		\param _x x coordinate
		\param _y y coordinate
	**/
	inline Vector2Tpl(Type _x, Type _y) : x(_x), y(_y) {}

	//! Returns vector square norm
	inline Type norm2() const { return (x*x)+(y*y); }
	//! Returns vector norm
	inline Type norm() const { return sqrt(norm2()); }
	//! Sets vector norm to unity
	inline void normalize() { Type n = norm2(); if (n>0) *this /= sqrt(n); }

	//! Inverse operator
	inline Vector2Tpl& operator - () {x=-x; y=-y; return *this;}
	//! In-place addition operator
	inline Vector2Tpl& operator += (const Vector2Tpl& v) {x+=v.x; y+=v.y; return *this;}
	//! In-place substraction operator
	inline Vector2Tpl& operator -= (const Vector2Tpl& v) {x-=v.x; y-=v.y; return *this;}
	//! In-place multiplication (by a scalar) operator
	inline Vector2Tpl& operator *= (Type v) {x*=v; y*=v; return *this;}
	//! In-place division (by a scalar) operator
	inline Vector2Tpl& operator /= (Type v) {x/=v; y/=v; return *this;}
	//! Addition operator
	inline Vector2Tpl operator + (const Vector2Tpl& v) const {return Vector2Tpl(x+v.x, y+v.y);}
	//! Substraction operator
	inline Vector2Tpl operator - (const Vector2Tpl& v) const {return Vector2Tpl(x-v.x, y-v.y);}
	//! Multiplication operator
	inline Vector2Tpl operator * (Type s) const {return Vector2Tpl(x*s, y*s);}
	//! Division operator
	inline Vector2Tpl operator / (Type s) const {return Vector2Tpl(x/s, y/s);}
	//! Copy operator
	inline Vector2Tpl& operator = (const Vector2Tpl &v) {x=v.x; y=v.y; return *this;}
	//! Direct coordinate access
	inline Type& operator [] (unsigned i) {return u[i];}
	//! Direct coordinate access (const)
	inline const Type& operator [] (unsigned i) const {return u[i];}
};

//! Default 3D Vector
typedef Vector3Tpl<PointCoordinateType> CCVector3;

//! Double 3D Vector
typedef Vector3Tpl<PointCoordinateType> CCVector3d;

//! Default 2D Vector
typedef Vector2Tpl<PointCoordinateType> CCVector2;

//! Int 2D Vector
typedef Vector2Tpl<int> CCVector2i;

#endif //CC_GEOM_HEADER
