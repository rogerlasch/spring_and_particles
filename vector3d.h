

#ifndef VEC_H
#define VEC_H

#include<sstream>
#include<iostream>
#include<string>
#include<numeric>

using namespace std;

class vector3d{
public:
float x;
float y;
float z;
vector3d(){
x=0;
y=0;
z=0;
}
vector3d(float x, float y, float z)
{
this->x=x;
this->y=y;
this->z=z;
}

vector3d(const vector3d& dv)
{
*this=dv;
}

float& operator[](unsigned int axis)
{
switch(axis)
{
case 0:
return this->x;
case 1:
return this->y;
case 2:
return this-> z;
default:
throw std::runtime_error("Invalid axis on vector3d");
}
}

float operator[](unsigned int axis)const
{
switch(axis)
{
case 0:
return this->x;
case 1:
return this->y;
case 2:
return this-> z;
default:
throw std::runtime_error("Invalid axis on vector3d");
}
}

vector3d& operator=(const vector3d& dv)
{
this->x=dv.x;
this->y=dv.y;
this->z=dv.z;
return *this;
}

vector3d& operator=(const float points[3] )
{
/*
vector<float> df(points);
switch(df.size())
{
case 1:
{
this->x=df[0];
break;
}
case 2:
{
this->x=df[0];
this->y=df[1];
break;
}
case 3:
{
this->x=df[0];
this->y=df[1];
this->z=df[2];
break;
}
}
*/
x=points[0];
y=points[1];
z=points[2];
return *this;
}

bool operator==(const vector3d& dv)const
{
return this->x==dv.x&&this->y==dv.y&&this->z==dv.z;
}

bool operator==(const float  dv[3])const
{
return x==dv[0]&&y==dv[1]&&z==dv[2];
}

vector3d& operator-()
{
this->x=-x;
this->y=-y;
this->z=-z;
return *this;
}

vector3d& operator+=(float escalar)
{
this->x+=escalar;
this->y+=escalar;
this->z+=escalar;
return *this;
}

vector3d& operator-=(float escalar)
{
this->x-=escalar;
this->y-=escalar;
this->z-=escalar;
return *this;
}

vector3d& operator*=(float escalar)
{
this->x*=escalar;
this->y*=escalar;
this->z*=escalar;
return *this;
}

vector3d& operator/=(float escalar)
{
if(escalar==0) escalar=1.0f;
this->x/=escalar;
this->y/=escalar;
this->z/=escalar;
return *this;
}

vector3d& operator-=(const vector3d& dv)
{
this->x-=dv.x;
this->y-=dv.y;
this->z-=dv.z;
return *this;
}

vector3d& operator+=(const vector3d& dv)
{
this->x+=dv.x;
this->y+=dv.y;
this->z+=dv.z;
return *this;
}

vector3d& operator*=(const vector3d& dv)
{
this->x*=dv.x;
this->y*=dv.y;
this->z*=dv.z;
return *this;
}

vector3d& operator/=(const vector3d& v )
{
if(v.x!=0)
{
this->x/=v.x;
}
if(v.y!=0)
{
this->y/=v.y;
}
if(v.z!=0)
{
this->z/=v.z;
}
return *this;
}

bool isNull()const
{
return fabs(x)<numeric_limits<float>::epsilon()&&fabs(y)<numeric_limits<float>::epsilon()&&fabs(z)<numeric_limits<float>::epsilon();
}

//Calcula a magnitude do vetor, ou comprimento.
float length()const
{
return sqrt(x*x+y*y+z*z);
}

//Normaliza o vetor...
vector3d& normalize()
{
float len=sqrt(x*x+y*y+z*z);
if(len<=numeric_limits<float>::epsilon()) len=1.0f;
this->x/=len;
this->y/=len;
this->z/=len;
if(fabs(this->x)<numeric_limits<float>::epsilon()) this->x=0.0f;
if(fabs(this->y)<numeric_limits<float>::epsilon()) this->y=0.0f;
if(fabs(this->z)<numeric_limits<float>::epsilon()) this->z=0.0f;
return *this;
}

//Inverte o vetor...
vector3d& inverse()
{
this->x=-this->x;
this->y=-this->y;
this->z=-this->z;
return *this;
}

//Inverte o vetor retornando um novo vetor.
vector3d inverse(const vector3d& v)
{
return vector3d(-v.x, -v.y, -v.z);
}

//Normaliza o vetor, versão estática.
//Útil quando precisamos manter o original intácto.
vector3d normalize(const vector3d& v)
{
float len=sqrt(v.x*v.x+v.y*v.y+v.z*v.z);
if(len<=numeric_limits<float>::epsilon()) len=1.0f;
vector3d v2(v.x/len, v.y/len, v.z/len);
if(fabs(v2.x)<numeric_limits<float>::epsilon()) v2.x=0.0f;
if(fabs(v2.y)<numeric_limits<float>::epsilon()) v2.y=0.0f;
if(fabs(v2.z)<numeric_limits<float>::epsilon()) v2.z=0.0f;
return v2;
}

//Calcula o produto entre 2 vetores...
float dotProduct(const vector3d& v1, const vector3d&  v2)
{
//just multiply everything and add.
return ((v1.x*v2.x)+(v1.y*v2.y)+(v1.z*v2.z));
}

//Calcula o produto cruzado entre 2 vetores...
vector3d crossProduct(const vector3d& v1, const vector3d& v2)
{
vector3d v;
v.x=v1.y*v2.z - v1.z*v2.y;
v.y=-v1.x*v2.z + v1.z*v2.x;
v.z= v1.x*v2.y - v1.y*v2.x;
return v;
}

//Calcula o produto triplo entre 3 vetores...
float tripleProduct(const vector3d& a, const vector3d& b, const vector3d& c)
{
//return a.x * (b.y * c.z - c.y * b.z) - a.y * (b.x * c.z - c.x * b.z) + a.z * (b.x * c.y - c.x * b.y);
return dotProduct(crossProduct(a, b), c);
}

string toString()const
{
stringstream ss;
ss<<fixed;
ss<<x<<":"<<y<<":"<<z;
return ss.str();
}
};

//Functions

ostream& operator<<(ostream& os, const vector3d& dv)
{
os<<dv.x<<":"<<dv.y<<":"<<dv.z;
return os;
}

//overloads
//Aqui existem outras sobrecargas para operações entre vetores, bem como operadores de subtração adição, e etc...

vector3d operator+(const vector3d& v, float s)
{
return vector3d(v.x+s, v.y+s, v.z+s);
}

vector3d operator+(float s, const vector3d& v)
{
return vector3d(v.x+s, v.y+s, v.z+s);
}

vector3d operator-(const vector3d& v, float s)
{
return vector3d(v.x-s, v.y-s, v.z-s);
}

vector3d operator-(float s, const vector3d& v)
{
return vector3d(v.x-s, v.y-s, v.z-s);
}

vector3d operator*(const vector3d& v, float s)
{
return vector3d(v.x*s, v.y*s, v.z*s);
}

vector3d operator*(float s, const vector3d& v)
{
return vector3d(v.x*s, v.y*s, v.z*s);
}

vector3d operator/(const vector3d& v, float s)
{
if(s==0) s=1.0f;
return vector3d(v.x/s, v.y/s, v.z/s);
}

vector3d operator/(float s, const vector3d& v)
{
if(s==0) s=1.0f;
return vector3d(v.x/s, v.y/s, v.z/s);
}

vector3d operator+(const vector3d& v1, const vector3d& v2)
{
return vector3d(v1.x+v2.x, v1.y+v2.y, v1.z+v2.z);
}

vector3d operator-(const vector3d& v1, const vector3d& v2)
{
return vector3d(v1.x-v2.x, v1.y-v2.y, v1.z-v2.z);
}

vector3d multiVec(const vector3d& v1, const vector3d& v2)
{
return vector3d(v1.x*v2.x, v1.y*v2.y, v1.z*v2.z);
}

float operator*(const vector3d& v1, const vector3d& v2)
{
return((v1.x*v2.x)+(v1.y*v2.y)+(v1.z*v2.z));
}

vector3d operator/(const vector3d& v1, const vector3d& v2)
{
return vector3d(v1.x/((v2.x!=0) ? v2.x : 1.0f), v1.y/((v2.y!=0) ? v2.y : 1.0f), v1.z/((v2.z!=0) ? v2.z : 1.0f));
}

vector3d operator^(const vector3d& v1, const vector3d& v2)
{
vector3d v;
v.x=v1.y*v2.z - v1.z*v2.y;
v.y=-v1.x*v2.z + v1.z*v2.x;
v.z= v1.x*v2.y - v1.y*v2.x;
return v;
}
#endif
