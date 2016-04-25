/* Special thanks to Andre' for his book "Tricks of 3D game programming Guru's"
w/o this book this library wouldnt of exisited.
*/



#ifndef __MX_MATH__H_
#define __MX_MATH__H_
#include<math.h>
#include<vector>
#include<string>
#include<map>
#include<fstream>
#define mvector std::vector
#define mmap std::map
#define mstring std::string
#define mfstream std::fstream
#include<stdio.h>
#include "mx_tok.h"
#include "mxpixelbuffer.h"




namespace mx3d {

	const float PI = 3.141592654f;

	float sin_look[361];
	float cos_look[361];

	inline void BuildTables() {
		for (int ang = 0; ang <= 360; ang++) {
			float theta = (float)ang*PI/(float)180;
			cos_look[ang] = cos(theta);
			sin_look[ang] = sin(theta);
		}
	}

	inline float fast_cosf(float theta) {
		theta = fmodf(theta,360);

		if (theta < 0) theta+=360.0;

		int theta_int    = (int)theta;
		float theta_frac = theta - theta_int;

		return(cos_look[theta_int] + 
			theta_frac*(cos_look[theta_int+1] - cos_look[theta_int]));
	}

	inline float fast_sinf(float theta) {
		theta = fmodf(theta,360);
		if (theta < 0) theta+=360.0;
		int theta_int    = (int)theta;
		float theta_frac = theta - theta_int;
		return(sin_look[theta_int] + theta_frac*(sin_look[theta_int+1] - sin_look[theta_int]));
	}

	inline float deg2rad(float ang) {
		return ((ang*PI/180.0f));
	}

	inline int rrand(int x, int y) {
		return (x) + (rand()%((y)-(x)+1));
	}


	// 2D Vector
	class vec2D {
	public:
		union {
			float vec[2];
			struct {
				float x,y; // vector x,y variables
			};
		};
		// vector constructor takes x,y to set the x,y variables as
		vec2D(float x, float y) {
			this->x = x, this->y = y;
		}

		// default constructor sets the x,y variables to 0
		vec2D() {
			x = 0;
			y = 0;
		}

		void Set(float x, float y) {
			this->x = x, this->y = y;
		}

		// overloaded = operator
		void operator=(const vec2D &v) {
			x = v.x, y = v.y;
		}

		// adds two vectors and returns the result
		vec2D operator+(const vec2D &v) {
			vec2D p = *this;
			p.x += v.x;
			p.y += v.y;
			return p;
		}

		// add to this vector another vector
		void operator+=(const vec2D &v) {
			x += v.x;
			y += v.y;
		}

		// subtracts two vectors && returns the result
		vec2D operator-(const vec2D &v) {
			vec2D p = *this;
			p.x -= v.x;
			p.y -= v.y;
			return p;
		}

		// sub from this vector another vector
		void operator-=(const vec2D &v) {
			x -= v.x;
			y -= v.y;
		}

		// Scales the vector and returns another vector
		vec2D Scale(float k) {
			vec2D p = *this;
			p.x = k * p.x;
			p.y = k * p.y;
			return p;
		}

		// Scales this vector
		void ScaleThis(float k) {
			x *= k;
			y *= k;
		}

		// gets the Dot Product of two 2D vectors
		float DotProduct(const vec2D &v) {
			return ((x*v.x) + (y*v.y));
		}

		// get the length of the vector
		float Length() {
			return sqrtf(x * x + y * y);
		}

		// normalize the 2D vector
		void Normalize() {
			float length =  sqrtf(x * x + y * y);
			if ( length < float(1E-5))
				return;
			float inv = 1/length;
			x = x * inv;
			y = y * inv;
		}

		// normalize the 2D vector and put the output in v
		void Normalize(vec2D &v) {
			float length =  sqrtf(x * x + y * y);
			if ( length < float(1E-5))
				return;
			float inv = 1/length;
			v.x = x * inv;
			v.y = y * inv;
		}

		// cosine a vector by another vector
		float Cos(vec2D &v) {
			float the_dot = DotProduct(v);
			return ( the_dot / Length() * v.Length() );
		}

		mstring Print(mstring v = "v") {
			mstring p;
			char dat[256];
			sprintf(dat,"%s<%f,%f>", v.c_str(), x,y);
			p = dat;
			return p;
		}

		// overloaded << operator for cout
		/*friend std::ostream &operator<<(std::ostream &out,vec2D &v) {
			//out << v.Print();
			return out;
		}

		// overloaded >> operator for cin
		friend std::istream& operator>>(std::istream &in, vec2D &v) {
			//fflush(stdin);
			//in >> v.x >> v.y;
			return in;
		}*/

	};

	// 3D Vector class
	class vec3D {
	public:
		union {
			float vec[3];
			struct {
				float x,y,z;
			};
		};
		// vectors constructor takes 3 parameters x,y,z values
		vec3D(float x, float y, float z) {
			this->x = x, this->y = y, this->z = z;
		}

		// vectors default constructor takes 0 parameters and sets the x,y,z values to nil
		vec3D() {
			x = y = z = 0;
		}

		// set the x,y,z values
		void Set(float x, float y, float z) {
			this->x = x, this->y = y, this->z = z;
		}

		// overloaded = operator, for setting the vector by another vector
		void operator=(const vec3D &v ) {
			this->x = v.x, this->y = v.y, this->z = v.z;
		}

		// overloaded + operator for addition
		virtual vec3D operator+(const vec3D &v) {
			vec3D p = *this;
			p.x += v.x;
			p.y += v.y;
			p.z += v.z;
			return p;
		}

		// overloaded += operator for addition
		virtual void operator+=(const vec3D &v) {
			x += v.x;
			y += v.y;
			z += v.z;
		}

		// overloaded - operator for subtraction
		vec3D operator-(const vec3D &v) {
			vec3D p = *this;
			p.x -= v.x;
			p.y -= v.y;
			p.z -= v.z;
			return p;
		}

		// overloaded -= operator for subtraction
		void operator-=(const vec3D &v) {
			x -= v.x;
			y -= v.y;
			z -= v.z;
		}

		// Scale vector and return in another vector
		vec3D Scale(float k) {
			vec3D p = *this;
			p.x *= k;
			p.y *= k;
			p.z *= k;
			return p;
		}

		// Scale this vector and leave it 
		void ScaleThis(float k) {
			x *= k;
			y *= k;
			z *= k;
		}

		// Get the Dot Product of this vector by another vector
		float DotProduct(const vec3D &v) {
			return ((x*v.x) + (y*v.y) + (z*v.z));
		}

		// Get the Cross Product of this vector by another vector and return it in temporary variable
		vec3D CrossProduct(const vec3D &v) {
			vec3D p;
			p.x =  ( ( y * v.z ) - ( z * v.y ) );
			p.y = -( ( x * v.z ) - ( z * v.x ) );
			p.z =  ( ( x * v.y ) - ( y * v.x ) );
			return p;
		}

		// Get the Length of the vector
		float Length() {
			return sqrtf( x * x + y * y +  z * z );
		}

		// normalize this vector
		void Normalize() {
			float len = sqrtf( x * x + y * y + z * z );
			if(len < float(1E-5))
				return; // zero length vector
			float inv = 1/len;
			x *= inv;
			y *= inv;
			z *= inv;
		}

		// Noramlize the vector and place it in a new vector
		void Normalize(vec3D &v) {
			float len = sqrtf( x * x + y * y + z * z );
			if(len < float(1E-5)) {
				v = *this;
				return; // zero length vector
			}
			float inv = 1/len;
			v.x = x * inv;
			v.y = y * inv;
			v.z = z * inv;
		}

		// cosine the vector
		float Cos(vec3D &v) {
			float dot = DotProduct(v);
			return (dot / Length() * v.Length());
		}

		// print the vectors data to a string
		virtual mstring Print(mstring v = "v") {
			mstring p;
			char dat[256];
			sprintf(dat,"%s<%f,%f,%f>", v.c_str(), x,y,z);
			p = dat;
			return p;
		}

		// overloaded << operator for cout
/*		friend std::ostream &operator<<(std::ostream &out, vec3D &v) {
///			out << v.Print();
			return out;
		}*/

		// overloaded >> operator for cin
/*		friend std::istream &operator>>(std::istream &in, vec3D &v) {
//			fflush(stdin);
//			in >> v.x >> v.y >> v.z;
			return in;
		}*/

	};

	// 4D vector w is assumed to be 1 for all operations
	class vec4D  {
	public:
		union {
			float vec[4];
			struct {
				float x,y,z,w;
			};
		};

		vec4D(float x, float y, float z, float w)  {
			this->x = x, this->y = y, this->z = z, this->w = 1;
		}

		vec4D() {
			memset(this,0,sizeof(vec4D));
			w = 1;
		}

		vec4D(const vec4D &copy) {
			this->x = copy.x;
			this->y = copy.y;
			this->z = copy.z;
			this->w = copy.w;
		}

		void Set(float x, float y, float z, float w = 1) {
			this->x = x, this->y = y, this->z = z, this->w = w;
		}

		void Set(const vec4D &v) {
			this->x = v.x, this->y = v.y, this->z = v.z, this->w = v.w;
		}
		// overloaded = operator, for setting the vector by another vector
		vec4D &operator=(const vec4D &v ) {
			this->x = v.x, this->y = v.y, this->z = v.z;
			w = 1;
			return *this;
		}

		// overloaded + operator for addition
		virtual vec4D operator+(const vec4D &v) {
			vec4D p = *this;
			p.x += v.x;
			p.y += v.y;
			p.z += v.z;
			p.w += v.w;
			return p;
		}
		// function for adding vectors
		void AddVec(vec4D &src, vec4D &out) {
			src.x += out.x;
			src.y += out.y;
			src.z += out.z;
			src.w = 1;
		}
		// overloaded += operator for addition
		virtual void operator+=(const vec4D &v) {
			x += v.x;
			y += v.y;
			z += v.z;
			w = 1;
		}

		// overloaded - operator for subtraction
		vec4D operator-(const vec3D &v) {
			vec4D p = *this;
			p.x -= v.x;
			p.y -= v.y;
			p.z -= v.z;
			p.w = 1;
			return p;
		}

		// overloaded -= operator for subtraction
		void operator-=(const vec4D &v) {
			x -= v.x;
			y -= v.y;
			z -= v.z;
			w = 1;
		}

		// Scale vector and return in another vector
		vec4D Scale(float k) {
			vec4D p = *this;
			p.x *= k;
			p.y *= k;
			p.z *= k;
			p.w = 1;
			return p;
		}

		// Scale this vector and leave it 
		void ScaleThis(float k) {
			x *= k;
			y *= k;
			z *= k;
			w = 1;
		}

		// Get the Dot Product of this vector by another vector
		float DotProduct(const vec4D &v) {
			return ((x*v.x) + (y*v.y) + (z*v.z));
		}

		// Get the Cross Product of this vector by another vector and return it in temporary variable
		vec4D CrossProduct(const vec4D &v) {
			vec4D p;
			p.x =  ( ( y * v.z ) - ( z * v.y ) );
			p.y = -( ( x * v.z ) - ( z * v.x ) );
			p.z =  ( ( x * v.y ) - ( y * v.x ) );
			p.w = 1;
			return p;
		}

		// Get the Length of the vector
		float Length() {
			return sqrtf( x * x + y * y +  z * z );
		}

		// normalize this vector
		void Normalize() {
			float len = sqrtf( x * x + y * y + z * z );
			if(len < float(1E-5))
				return; // zero length vector
			float inv = 1/len;
			x *= inv;
			y *= inv;
			z *= inv;
			w = 1;
		}

		// Noramlize the vector and place it in a new vector
		void Normalize(vec4D &v) {
			float len = sqrtf( x * x + y * y + z * z );
			if(len < float(1E-5)) {
				v = *this;
				return; // zero length vector
			}
			float inv = 1/len;
			v.x = x * inv;
			v.y = y * inv;
			v.z = z * inv;
			v.w = 1;
		}

		// cosine the vector
		float Cos(vec4D &v) {
			float dot = DotProduct(v);
			return (dot / Length() * v.Length());
		}

		mstring Print(mstring v= "v") {
			mstring p;
			char dat[300];
			sprintf(dat,"%s<%f,%f,%f,%f>", v.c_str(), x,y,z,w);
			p = dat;
			return p;
		}

		void Build(vec4D &vec) {
			x = vec.x - x;
			y = vec.y - y;
			z = vec.z - z;
			w = 1;
		}

		vec4D Build(vec4D &in , vec4D &by) {
			vec4D p;
			p.x = by.x - in.x;
			p.y = by.y - in.y;
			p.z = by.z - in.z;
			p.w = 1;
			return p;
		}

/*		friend std::ostream &operator<<(std::ostream &out, vec4D &v) {
//			out << v.Print();
			return out;
		}

		friend std::istream &operator>>(std::istream &in, vec4D &v) {
//			in >> v.x >> v.y >> v.z >> v.w;
			return in;
		}*/
	};

	// 1x2 Matrix
	class Mat1D {
	public:
		float mat[2];// the array 
		// the constructor
		Mat1D(float m0, float m1) {
			mat[0] = m0, mat[1] = m1;
		}
		// the default constructor
		Mat1D() {
			memset(this, 0, sizeof(Mat1D));
		}

		// Set the values
		void Set(float m0, float m1) {
			mat[0] = m0, mat[1] = m1;
		}

		// the overloaded = operator
		void operator=(Mat1D &m) {
			memcpy(this,&m,sizeof(Mat1D));
		}

		Mat1D operator+(const Mat1D &m) {
			Mat1D p = *this;
			p.mat[0] += m.mat[0];
			p.mat[1] += m.mat[1];
			return p;
		}

		Mat1D operator-(const Mat1D &m) {
			Mat1D p = *this;
			p.mat[0] -= m.mat[0];
			p.mat[1] -= m.mat[1];
			return p;
		}

		Mat1D operator*(const Mat1D &m) {
			Mat1D p = *this;
			p.mat[0] *= m.mat[0];
			p.mat[1] *= m.mat[1];
			return p;
		}

		virtual mstring Print(mstring m = "m") {
			char dat[256];
			mstring p;
			sprintf(dat,"%s = { ", m.c_str());
			for(unsigned int i = 0; i < 2; i++)
				sprintf(dat,"%s%d ", dat, mat[i]);
			sprintf(dat,"%s}\n", dat);
			p = dat;
			return p;
		}

	};

	// 1x3 Matrix
	class Mat1x3D {
	public:
		float mat[3];
		Mat1x3D() {
			memcpy(this,0,sizeof(Mat1x3D));
		}

		Mat1x3D(float m0, float m1 , float m2) {
			mat[0] = m0, mat[1] = m1, mat[2] = m2;
		}
	};
	// 1x4 Matrix
	class Mat1x4D {
	public:
		float mat[4];
		Mat1x4D() {
			memcpy(this,0,sizeof(Mat1x4D));
		}

		Mat1x4D(float m0, float m1, float m2, float m3) {
			mat[0] = m0, mat[1] = m1, mat[2] = m2, mat[3] = m3;
		}
	};

	class Mat4x3D {
	public:
		float mat[4][3];
		Mat4x3D() {
			memcpy(this,0,sizeof(Mat4x3D));
		}
	};

	// 2x2 Matrix
	class Mat2D {
	public:
		float mat[2][2]; // 2x2 matrix
		// matrix default constructor
		Mat2D() {
			memset(mat,0,sizeof(mat));
		}


		// matrix constructor to set the values
		Mat2D(float m00, float m01, float m10, float m11) {
			Set(m00,m01,m10,m11);
		}

		// set the values
		void Set(float m00, float m01, float m10, float m11) {
			mat[0][0] = m00;
			mat[0][1] = m01;
			mat[1][0] = m10;
			mat[1][1] = m11;
		}

		// Load the Identity Matrix
		void LoadIdentity() {
			mat[0][0] = 1, mat[0][1] = 0;
			mat[1][0] = 0, mat[1][1] = 1;
		}

		// overloaded = operator
		void operator=(Mat2D &m) {
			memcpy(this,&m,sizeof(Mat2D));
		}

		// add two matrices together and return in temporary variable 
		Mat2D operator+(const Mat2D &mat) {
			Mat2D m = *this;
			m.mat[0][0] += mat.mat[0][0];
			m.mat[0][1] += mat.mat[0][1];
			m.mat[1][0] += mat.mat[1][0];
			m.mat[1][1] += mat.mat[1][1];
			return m;
		}

		// add another matrix to this matrix
		void operator+=(const Mat2D &m) {
			mat[0][0] += m.mat[0][0];
			mat[0][1] += m.mat[0][1];
			mat[1][0] += m.mat[1][0];
			mat[1][1] += m.mat[1][1];
		}

		// sub another matrix by this matrix and return in temporary varible
		Mat2D operator-(const Mat2D &mat) {
			Mat2D m = *this;
			m.mat[0][0] -= mat.mat[0][0];
			m.mat[0][1] -= mat.mat[0][1];
			m.mat[1][0] -= mat.mat[1][0];
			m.mat[1][1] -= mat.mat[1][1];
		}

		// sub a matrix by this matrix and store in this matrix
		void operator-=(const Mat2D &m) {
			mat[0][0] -= m.mat[0][0];
			mat[0][1] -= m.mat[0][1];
			mat[1][0] -= m.mat[1][0];
			mat[1][1] -= m.mat[1][1];
		}

		// mul a matrix by this matrix and store in temporary variable
		Mat2D operator*(const Mat2D &mat) {
			Mat2D m = *this;
			m.mat[0][0] *= mat.mat[0][0];
			m.mat[0][1] *= mat.mat[0][1];
			m.mat[1][0] *= mat.mat[1][0];
			m.mat[1][1] *= mat.mat[1][1];
			return m;
		}

		// mul a matrix by this matrix and store in this matrix
		void operator*=(const Mat2D &m) {
			mat[0][0] *= m.mat[0][0];
			mat[0][1] *= m.mat[0][1];
			mat[1][0] *= m.mat[1][0];
			mat[1][1] *= m.mat[1][1];
		}

		// Inverse this matrix and set the result in m
		bool Inverse(Mat2D &m) {
			float d = mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
			if(fabs(d) < float(1E-5)) 
				return false;
			float inv = 1.0f/d;
			m.mat[0][0] =  mat[1][1] * inv;
			m.mat[0][1] = -mat[0][1] * inv;
			m.mat[1][0] = -mat[1][0] * inv;
			m.mat[1][1] =  mat[0][0] * inv;
			return true;
		}

		// calculate the Determinate
		float Determinate() {
			return (mat[0][0] * mat[1][1] - mat[1][0] * mat[0][1]);
		}

		void Swap(Mat2D &m, int c, Mat1D &m2) {
			m.mat[0][c] = m2.mat[0];
			m.mat[1][c] = m2.mat[1];
		}

		bool Solve2x2(Mat2D &m1, Mat1D &m2, Mat1D &m3) {
			float det_a = m1.Determinate();
			if(fabs(det_a) < float(1E-5))
				return false;
			Mat2D wm;
			wm = m1;
			Swap(wm,0,m3);
			float det_a_b = wm.Determinate();
			m2.mat[0] = det_a_b / det_a;
			wm = m1;
			Swap(wm,1,m3);
			det_a_b = wm.Determinate();
			m2.mat[1] = det_a_b / det_a;
			return true;
		}

		// Print matrix to string
		virtual mstring Print(mstring m = "m") {
			mstring p;
			char dat[256];
			sprintf(dat,"%s = {\n", m.c_str());
			for(unsigned int i = 0; i < 2; i++) {
				for(unsigned int z = 0; z < 2; z++)  {
					sprintf(dat,"%s%f ", dat,mat[i][z]);
				}
				sprintf(dat,"%s\n", dat);
			}
			sprintf(dat,"%s}\n", dat);
			p = dat;
			return p;
		}
	};

	// 3x3 Matrix 
	class Mat3D {
	public:
		float mat[3][3];// the array
		Mat3D() {// constructor
			memset(this,0,sizeof(Mat3D));
		}
		// another constructor
		Mat3D(float m00, float m01, float m02, float m10, float m11, float m12, float m20, float m21, float m22) {
			Set(m00,01,m02,m10,m11,m12,m20,m21,m22);
		}

		// Set the values of the array
		void Set(float m00, float m01, float m02, float m10, float m11, float m12, float m20, float m21, float m22) {
			mat[0][0] = m00;
			mat[0][1] = m01;
			mat[0][2] = m02;
			mat[1][0] = m10;
			mat[1][1] = m11;
			mat[1][2] = m12;
			mat[2][0] = m20;
			mat[2][1] = m21;
			mat[2][2] = m22;
		}

		// Load the Identity Matrix
		void LoadIdentity() {
			mat[0][0] = 1, mat[0][1] = 0, mat[0][2] = 0;
			mat[1][0] = 0, mat[1][1] = 1, mat[1][2] = 0;
			mat[2][0] = 0, mat[2][1] = 0, mat[2][2] = 1;
		}

		// add the matrix
		Mat3D operator+(const Mat3D &m) {
			Mat3D p = *this;
			for(i = 0; i < 3; i++)
				for(z = 0; z < 3; z++)
					p.mat[i][z] += m.mat[i][z];
			return p;
		}

		// add equal the matrix
		void operator+=(const Mat3D &m) {
			for(i = 0; i < 3; i++)
				for(z = 0; z < 3; z++)
					mat[i][z] += m.mat[i][z];
		}

		// multiply the matrix
		Mat3D operator*(const Mat3D &m) {
			Mat3D p = *this;
			for(i = 0; i < 3; i++) 
				for(z = 0; z < 3; z++)
					p.mat[i][z] *= m.mat[i][z];
			return p;
		}

		// multiply equal the matrix
		void operator*=(const Mat3D &m) {
			for(i = 0; i < 3; i++)
				for(z = 0; z < 3; z++)
					mat[i][z] *= m.mat[i][z];
		}

		void MulVec(vec3D &in, vec3D &out) {
			for(z = 0; z < 3; z++) {
				float s = 0;
				for(i = 0; i < 3; i++) {
					s += in.vec[z] * mat[i][z]; 
				}
				out.vec[z] = s;
			}
		}

		// dunno if this works! try it & see
		bool Inverse(Mat3D  &out) {
			float d = mat[0][0] * (mat[1][1] * mat[2][2] - mat[2][1] * mat[1][2]) - mat[0][1] * (mat[1][0] * mat[2][2] - mat[2][0] * mat[1][2]) + mat[0][2] * (mat[1][0] * mat[2][1] - mat[2][0] * mat[1][1]);
			if(fabs(d) < float(1E-5))
				return false;

			float inv = 1.0f/d;

			out.mat[0][0] =  inv*(mat[1][1]*mat[2][2]-mat[2][1]*mat[1][2]);
			out.mat[1][0] = -inv*(mat[1][0]*mat[2][2]-mat[2][0]*mat[1][2]);
			out.mat[2][0] =  inv*(mat[1][0]*mat[2][1]-mat[2][0]*mat[1][1]);

			out.mat[1][0] =  -inv*(mat[0][1]*mat[2][2]-mat[2][1]*mat[0][2]);
			out.mat[1][1] =   inv*(mat[0][0]*mat[2][2]-mat[2][0]*mat[0][2]);
			out.mat[2][1] =  -inv*(mat[0][0]*mat[2][1]-mat[2][0]*mat[0][1]);

			out.mat[0][2] =  inv*(mat[0][1]*mat[1][2]-mat[1][1]*mat[0][2]);
			out.mat[1][2] = -inv*(mat[0][0]*mat[1][2]-mat[1][0]*mat[0][2]);
			out.mat[2][2] =  inv*(mat[0][0]*mat[1][1]-mat[1][0]*mat[0][1]);

			return true;

		}

		// same goes for this one
		float Determinate() {
			return mat[0][0]*(mat[1][1]*mat[2][2]-mat[2][1]*mat[1][2])-mat[0][1]*(mat[1][0]*mat[2][2]-mat[2][0]*mat[1][2])+mat[0][2]*(mat[1][0]*mat[2][1]-mat[2][0]*mat[1][1]);
		}

		void Swap(Mat3D &out, int c, Mat1x3D &in) {
			out.mat[0][c] = in.mat[0];
			out.mat[1][c] = in.mat[1];
			out.mat[2][c] = in.mat[2];
		}

		bool Solve3x3(Mat3D &m1, Mat1x3D &m1d, Mat1x3D &m2) {
			float d =  m1.Determinate();
			if(fabs(d) < float(1E-5))
				return false; 
			Mat3D wm;
			wm = m1;
			Swap(wm,0,m2);
			float d_x = wm.Determinate();
			m1d.mat[0] = d/d_x;
			wm = m1;
			Swap(wm,1,m2);
			float d_y = wm.Determinate();
			m1d.mat[1] = d/d_y;
			wm = m1;
			Swap(wm,2,m2);
			float d_z = wm.Determinate();
			m1d.mat[2] = d/d_z;
			return true;
		}

	private:
		unsigned int i,z;
	};

	// A 4X4 Matrix
	class Mat4D {
	public:	
		float mat[4][4];
		Mat4D(float m00, float m01, float m02, float m03, float m10,float m11,float m12,float m13, float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33) {
			Set(m00,m01,m02,m03,m10,m11,m12,m13,m20,m21,m22,m23,m30,m31,m32,m33);
		}
		Mat4D() {
			memset(this,0,sizeof(Mat4D));
		}
		void Set(float m00, float m01, float m02, float m03, float m10,float m11,float m12,float m13, float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33) {
			mat[0][0] = m00;
			mat[0][1] = m01;
			mat[0][2] = m02;
			mat[0][3] = m03;
			mat[1][0] = m10;
			mat[1][1] = m11;
			mat[1][2] = m12;
			mat[1][3] = m13;
			mat[2][0] = m20;
			mat[2][1] = m21;
			mat[2][2] = m22;
			mat[2][3] = m23;
			mat[3][0] = m30;
			mat[3][1] = m31;
			mat[3][2] = m32;
			mat[3][3] = m33;
		}
		mstring Print(mstring m = "m") {
			mstring p;
			char dat[256];
			sprintf(dat,"%s = {\n", m.c_str());
			for(unsigned int i = 0; i < 4; i++) {
				for(unsigned int z = 0; z < 4; z++)  {
					sprintf(dat,"%s%f ", dat,mat[i][z]);
				}
				sprintf(dat,"%s\n", dat);
			}
			sprintf(dat,"%s}\n", dat);
			p = dat;
			return p;
		}
		void operator=(const Mat4D &m) {
			memcpy(this,&m, sizeof(Mat4D));
		}

		Mat4D operator+(const Mat4D &m) {
			Mat4D p = *this;
			for(i = 0; i < 4; i++)
				for(z = 0; z < 4; z++)
					p.mat[i][z] += m.mat[i][z];
			return p;
		}

		void operator+=(const Mat4D &m) {
			for(i = 0; i < 4; i++)
				for(z = 0; z < 4; z++)
					mat[i][z] += m.mat[i][z];
		}

		Mat4D operator*(const Mat4D &m) {
			Mat4D p;
			for(i = 0; i < 4; i++)
				for(z = 0; z < 4; z++) {
					float sum = 0;
					for(int index = 0; index < 4; index++) {
						sum += mat[i][index] * m.mat[index][z];
					}
					p.mat[i][z] = sum;
				}
				return p;
		}

		void operator*=(const Mat4D &m) {
			for(i = 0; i < 4; i++)
				for(z = 0; z < 4; z++)
					mat[i][z] *= m.mat[i][z];
		}

		void Swap(Mat4D &out, int c, Mat1x4D &in) {
			out.mat[0][c] = in.mat[0];
			out.mat[1][c] = in.mat[1];
			out.mat[2][c] = in.mat[2];
			out.mat[3][c] = in.mat[3];
		}

		vec4D MulVec(vec4D &in) {
			vec4D out;
			for(int col = 0; col < 4; col++) {
				float s = 0;
				for(int row = 0; row < 4; row++) {
					s += (in.vec[row] * mat[row][col]);
				}
				out.vec[col] = s;
			}
			return out;
		}

		void MulVec(vec3D &in, vec3D &out) {
			for(z = 0; z < 3; z++) {
				float s = 0;
				for(i = 0; i < 3; i++) {
					s += in.vec[z] * mat[i][z];
				}
				s += mat[i][3];
				out.vec[z] = s;
			}
		}

		void MulVec(vec3D &v1, Mat4x3D &in, vec3D &out ) {
			for(z = 0; z < 3; z++) {
				float s = 0;
				for(i = 0;  i < 3; i++) {
					s += v1.vec[i] * in.mat[i][z];
				}
				s += in.mat[i][3];
				out.vec[z] = s;
			}
		}

		void MulVec(vec3D &v1, Mat4D &in, vec3D &out) {
			for(z = 0; z < 3; z++) {
				float s = 0;
				for(i = 0; i < 3; i++) {
					s += in.mat[i][z] * v1.vec[i];
				}
				s += in.mat[i][3];
				out.vec[z] = s;
			}
		}

		void MulVec(vec4D &v1, Mat4D &in, vec4D &out) {
			for(int col = 0; col < 4; col++) {
				float sum = 0.0f;
				for(int row = 0; row < 4; row++) {
					sum += (v1.vec[row]*in.mat[row][col]);
				}
				out.vec[col] = sum;
			}
		}

		void MulVec(vec4D &v1, Mat4x3D &in, vec4D &out) {
			for(z = 0; z < 3; z++) {
				float s = 0;
				for(i = 0; i < 4; i++) {
					s += v1.vec[i] * in.mat[i][z];
				}
				out.vec[z] = s;
			}

			out.vec[3] = v1.vec[3];
		}

		bool Inverse(Mat4D &m) {
			float d = ( mat[0][0] * ( mat[1][1] * mat[2][2] - mat[1][2] * mat[2][1]) - mat[0][1] *(mat[1][0] * mat[2][2] - mat[1][2] * mat[2][0] ) + mat[0][2] *(mat[1][0] * mat[2][1] - mat[1][1] * mat[2][0] ));

			if(fabs(d) < float(1E-5)) 
				return false;

			float inv = 1.0f/d;
			m.mat[0][0] =  inv *( mat[1][1] * mat[2][2] - mat[1][2] * mat[2][1] );
			m.mat[0][1] = -inv *( mat[0][1] * mat[2][2] - mat[0][2] * mat[2][1] );
			m.mat[0][2] =  inv *( mat[0][1] * mat[1][2] - mat[0][2] * mat[1][1] );
			m.mat[0][3] = 0.0f;

			m.mat[1][0] = -inv *(mat[1][0] * mat[2][2] - mat[1][2] * mat[2][0] );
			m.mat[1][1] =  inv *(mat[0][0] * mat[2][2] - mat[0][2] * mat[2][0] );
			m.mat[1][2] = -inv *(mat[0][0] * mat[1][2] - mat[0][2] * mat[1][0] );
			m.mat[1][3] = 0.0f;

			m.mat[2][0] =  inv *(mat[1][0] * mat[2][1] - mat[1][1] * mat[2][0] );
			m.mat[2][1] = -inv *(mat[0][0] * mat[2][1] - mat[0][1] * mat[2][0] );
			m.mat[2][2] =  inv *(mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0] );
			m.mat[2][3] = 0.0f;

			m.mat[3][0] =  -(mat[3][0] * m.mat[0][0] + mat[3][1] * m.mat[1][0] + mat[3][2] * m.mat[2][0] );
			m.mat[3][1] =  -(mat[3][0] * m.mat[0][0] + mat[3][1] * m.mat[1][1] + mat[3][2] * m.mat[2][1] );
			m.mat[3][2] =  -(mat[3][0] * m.mat[0][2] + mat[3][1] * m.mat[1][2] + mat[3][2] * m.mat[2][2] );
			m.mat[3][3] = 1.0f; // should be zero but Im not sure

			return true;
		}

		void LoadIdentity() {
			mat[0][0] = 1, mat[0][1] = 0, mat[0][2] = 0, mat[0][3] = 0;
			mat[1][0] = 0, mat[1][1] = 1, mat[1][2] = 0, mat[1][3] = 0;
			mat[2][0] = 0, mat[2][1] = 0, mat[2][2] = 1, mat[2][3] = 0;
			mat[3][0] = 0, mat[3][1] = 0, mat[3][2] = 0, mat[3][3] = 1;
		}

		void BuildXYZ(float theta_x, float theta_y, float theta_z) {

			Mat4D mx, my, mz, mtmp;
			float sin_theta = 0, cos_theta = 0;
			int rot_seq = 0;
			LoadIdentity();

			if (fabs(theta_x) > float(1E-5)) // x
				rot_seq = rot_seq | 1;

			if (fabs(theta_y) > float(1E-5)) // y
				rot_seq = rot_seq | 2;

			if (fabs(theta_z) > float(1E-5)) // z
				rot_seq = rot_seq | 4;

			switch(rot_seq) {
				case 0:
					return;
				case 1: // x 
					cos_theta = fast_cosf(theta_x);
					sin_theta = fast_sinf(theta_x);
					mx.Set( 1,    0,          0,         0,0,    cos_theta,  sin_theta, 0,0,   -sin_theta, cos_theta, 0,0,    0,          0,         1);
					*this = mx;
					break;
				case 2://  y
					cos_theta = fast_cosf(theta_y);
					sin_theta = fast_sinf(theta_y);
					my.Set(cos_theta, 0, -sin_theta, 0,  
						0,         1,  0,         0,
						sin_theta, 0, cos_theta,  0,
						0,         0, 0,          1);
					*this = my; 
					break;
				case 3://  xy
					cos_theta = fast_cosf(theta_x);
					sin_theta = fast_sinf(theta_x);
					mx.Set(1,    0,          0,         0,
						0,    cos_theta,  sin_theta, 0,
						0,   -sin_theta, cos_theta, 0,
						0,    0,          0,         1);
					cos_theta = fast_cosf(theta_y);
					sin_theta = fast_sinf(theta_y);
					my.Set(cos_theta, 0, -sin_theta, 0,  
						0,         1,  0,         0,
						sin_theta, 0, cos_theta,  0,
						0,         0, 0,          1);
					*this = mx * my;
					break;
				case 4: // z rotation
					cos_theta = fast_cosf(theta_z);
					sin_theta = fast_sinf(theta_z);
					mz.Set(
						cos_theta, sin_theta, 0, 0,  
						-sin_theta, cos_theta, 0, 0,
						0,         0,         1, 0,
						0,         0,         0, 1);
					*this = mz;
					break;
				case 5: // xz
					cos_theta = fast_cosf(theta_x);
					sin_theta = fast_sinf(theta_x);
					mx.Set(
						1,    0,          0,         0,
						0,    cos_theta,  sin_theta, 0,
						0,   -sin_theta, cos_theta, 0,
						0,    0,          0,         1);
					cos_theta = fast_cosf(theta_z);
					sin_theta = fast_sinf(theta_z);
					mz.Set( 
						cos_theta, sin_theta, 0, 0,  
						-sin_theta, cos_theta, 0, 0,
						0,         0,         1, 0,
						0,         0,         0, 1);
					*this = mx * mz;
					break;
				case 6: // yz
					cos_theta = fast_cosf(theta_y);
					sin_theta = fast_sinf(theta_y);
					my.Set(
						cos_theta, 0, -sin_theta, 0,  
						0,         1,  0,         0,
						sin_theta, 0, cos_theta,  0,
						0,         0, 0,          1);
					cos_theta = fast_cosf(theta_z);
					sin_theta = fast_sinf(theta_z);
					mz.Set(
						cos_theta, sin_theta, 0, 0,  
						-sin_theta, cos_theta, 0, 0,
						0,         0,         1, 0,
						0,         0,         0, 1);
					*this = my * mz;
					break;
				case 7:
					cos_theta = fast_cosf(theta_x);
					sin_theta = fast_sinf(theta_x);
					mx.Set(
						1,    0,         0,         0,
						0,    cos_theta, sin_theta, 0,
						0,   -sin_theta, cos_theta, 0,
						0,    0,         0,         1);
					cos_theta = fast_cosf(theta_y);
					sin_theta = fast_sinf(theta_y);
					my.Set(
						cos_theta, 0, -sin_theta, 0,  
						0,         1,  0,         0,
						sin_theta, 0,  cos_theta,  0,
						0,         0,  0,          1);
					cos_theta = fast_cosf(theta_z);
					sin_theta = fast_sinf(theta_z);
					mz.Set(
						cos_theta, sin_theta, 0, 0,  
						-sin_theta, cos_theta, 0, 0,
						0,         0,         1, 0,
						0,         0,         0, 1);
					mtmp = mx * my * mz;
					*this = mtmp;
					break;
			}
		}

	private:
		unsigned int i,z;

	};

	struct paramLine2D {
		vec2D p0,p1,v;

		paramLine2D() {
			memset(this,0,sizeof(paramLine2D));
		}

		paramLine2D(vec2D &p0, vec2D &p1, vec2D &v) {
			Set(p0,p1,v);
		}

		void Set(vec2D &p0, vec2D &p1, vec2D &v) {
			this->p0 = p0, this->p1 = p1, this->v = v;
		}


		void Init(vec2D &p0, vec2D &p1) {
			this->p0 = p0;
			this->p1 = p1;
			v = p0 - p1;
		}

		vec2D ComputePoint(float t, vec2D &p) {
			vec2D y = p;
			y.x = p0.x + v.x * t;
			y.y = p0.y + v.y * t;
			return y;
		}

		int Intersect(paramLine2D &p, float &x, float &y) {
			float det = v.x * p.v.x - v.y * p.v.y;
			if(fabs(det) < float(1E-5))
				return 0;
			x = (p.v.x * (p0.y - p.p0.y) - p.v.y * ( p0.x - p.p0.x )) / det;
			y = (v.x * (p0.y - p.p0.y) - v.y * ( p0.x - p.p0.x)) / det;

			if(x >= 0 && x <= 1 && y >= 0 && y <= 1)
				return 1;
			return 2;
		}

		int Intersect(paramLine2D &p, vec2D &out) {

			float det = v.x * p.v.x - v.y * p.v.y;
			if(fabs(det) < float(1E-5))
				return 0;
			float x = (p.v.x * (p0.y - p.p0.y) - p.v.y * ( p0.x - p.p0.x )) / det;
			float y = (v.x * (p0.y - p.p0.y) - v.y * ( p0.x - p.p0.x)) / det;

			out.x = p0.x + v.x * x;
			out.y = p0.y + v.y * x;

			if(x >= 0 && x <= 1 && y >= 0 && y <= 1)
				return 1;

			return 2;
		}

	};

	struct paramLine3D {
		vec3D p0,p1,v;

		paramLine3D() {
			memset(this,0,sizeof(paramLine3D));
		}

		paramLine3D(vec3D &p0, vec3D &p1, vec3D &v) {
			Set(p0,p1,v);
		}

		void operator=(paramLine3D &p) {
			memcpy(this,&p,sizeof(paramLine2D));
		}

		void Set(vec3D &p0, vec3D &p1, vec3D &v) {
			this->p0 = p0, this->p1 = p1, this->v = v;
		}

		void Init(vec3D &p0, vec3D &p) {
			this->p0 = p0;
			this->p1 = p1;
			v = p0 - p1;
		}

		vec3D ComputePoint(float t, vec3D &p) {
			vec3D y = p;
			y.x = p0.x + v.x * t;
			y.y = p0.y + v.y * t;
			y.z = p0.z + v.z * t;
			return y;
		}
	};

	struct Plane3D {
		vec3D p0,v;

		Plane3D() {
			memset(this,0,sizeof(Plane3D));
		}

		Plane3D(vec3D &p0, vec3D &v) {
			this->p0 = p0, this->v = v;
		}

		void Set(vec3D &p0, vec3D &v, bool norm) {

			this->p0 = p0;

			if(!norm)
				this->v = v;
			else {
				this->v.Normalize(v);
			}
		}
	};

	struct Polar {
		float r, theta;
	};

	struct CyType {
		float r, theta, z;
	};

	struct SpType {
		float p, theta, pi;
	};

	class QuatType {
	public:
		union {
			float p[4];
			struct {
				float x,y,z,w;
			};
		};

		QuatType() {
			memset(this,0,sizeof(QuatType));
		}

		QuatType(float x, float y, float z, float w) {
			this->x = x, this->y = y, this->z = z, this->w = w;
		}

		void operator=(QuatType &t) {
			memcpy(this,&t,sizeof(QuatType));
		}

		QuatType operator+(const QuatType &t) {
			QuatType p = *this;
			p.x += t.x;
			p.y += t.y;
			p.z += t.z;
			p.w += t.w;
			return p;
		}

		QuatType operator-(const QuatType &t) {
			QuatType p = *this;
			p.x -= t.x;
			p.y -= t.y;
			p.z -= t.z;
			p.w -= t.w;
			return p;
		}

		QuatType operator*(const QuatType &t) {
			QuatType p;
			float prod0 = (z - y) * (t.y - t.z);
			float prod1 = (w + x) * (t.w + t.x);
			float prod2 = (w - x) * (t.y + t.z);
			float prod3 = (y + z) * (t.w - t.x);
			float prod4 = (z - x) * (t.x - t.y);
			float prod5 = (z + x) * (t.x + t.y);
			float prod6 = (w + y) * (t.w - t.z);
			float prod7 = (w - y) * (t.w + t.z);

			float prod8 = prod5 + prod6 + prod7;
			float prod9 = 0.5f * (prod4 + prod8);
			p.w = prod0+prod9-prod5;
			p.x = prod1+prod9-prod8;
			p.y = prod2+prod9-prod7;
			p.z = prod3+prod9-prod6;
			return p;
		}

		void operator*=(const QuatType &t) {
			float prod0 = (z - y) * (t.y - t.z);
			float prod1 = (w + x) * (t.w + t.x);
			float prod2 = (w - x) * (t.y + t.z);
			float prod3 = (y + z) * (t.w - t.x);
			float prod4 = (z - x) * (t.x - t.y);
			float prod5 = (z + x) * (t.x + t.y);
			float prod6 = (w + y) * (t.w - t.z);
			float prod7 = (w - y) * (t.w + t.z);

			float prod8 = prod5 + prod6 + prod7;
			float prod9 = 0.5f * (prod4 + prod8);
			w = prod0+prod9-prod5;
			x = prod1+prod9-prod8;
			y = prod2+prod9-prod7;
			z = prod3+prod9-prod6;
		}
		void Conj() {
			x = -x;
			y = -y;
			z = -z;
		}

		void Scale(float f) {
			x = x*f;
			y = y*f;
			z = z*f;
			w = w*f;
		}

		float Norm() {
			return sqrtf( w * w + x * x + y * y + z * z );
		}

		float Norm2() {
			return ( w*w + x*x + y*y + z*z );
		}

		void Normalize() {
			float inv = 1.0f/(sqrtf( ( w * w + x * x + y * y + z * z ) ));
			x *= inv;
			y *= inv;
			z *= inv;
			w *= inv;
		}

		void Inverse() {
			x = -x;
			y = -y;
			z = -z;
		}

		void InverseNormal() {
			float inv = 1.0f/(sqrtf( ( w * w + x * x + y * y + z * z ) ));
			x *= -inv;
			y *= -inv;
			z *= -inv;
			w *= inv;
		}

		QuatType TripleProduct(QuatType p1, QuatType p2) {
			QuatType p = *this;
			p *= p1;
			p *= p2;
			return p;
		}

		void vec3DthetaQuat(float theta, const vec3D &v) {
			float theta_2 = 0.5f * theta;
			float sin_f = fast_sinf(theta_2);
			x = sin_f * v.x;
			y = sin_f * v.y;
			z = sin_f * v.z;
			w = fast_cosf(theta_2);
		}

		void vec4DthetaQuat(float theta, const vec4D &v) {
			float theta_2 = 0.5f * theta;
			float sin_f = fast_sinf(theta_2);
			x = sin_f * v.x;
			y = sin_f * v.y;
			z = sin_f * v.z;
			w = fast_cosf(theta_2);
		}

		void EulerZYX(float theta_x, float theta_y, float theta_z) {
			float cos_z_2 = 0.5f*fast_cosf(theta_z);
			float cos_y_2 = 0.5f*fast_cosf(theta_y);
			float cos_x_2 = 0.5f*fast_cosf(theta_x);
			float sin_z_2 = 0.5f*fast_sinf(theta_z);
			float sin_y_2 = 0.5f*fast_sinf(theta_y);
			float sin_x_2 = 0.5f*fast_sinf(theta_x);
			w = cos_z_2*cos_y_2*cos_x_2 + sin_z_2*sin_y_2*sin_x_2;
			x = cos_z_2*cos_y_2*sin_x_2 - sin_z_2*sin_y_2*cos_x_2;
			y = cos_z_2*sin_y_2*cos_x_2 + sin_z_2*cos_y_2*sin_x_2;
			z = sin_z_2*cos_y_2*cos_x_2 - cos_z_2*sin_y_2*sin_x_2;
		}

		void QuatToVec3D(float *theta, vec3D &v) {

			*theta = acosf(w);
			float sinf_theta_inv = 1.0f/sinf(*theta);
			v.x    = x*sinf_theta_inv;
			v.y    = y*sinf_theta_inv;
			v.z    = z*sinf_theta_inv;
			*theta*=2;
		}

	};


	// triangle structure
	struct Triangle  {
		vec4D vlist[3],tlist[3];
		int color;
		int attr;
		int state;
		int vert[3];
		Triangle()  {
			memset(this,0,sizeof(Triangle));
		}

		// Initalize a triangle with Vertex and Transformation Vertex
		Triangle(vec4D vlist[3], vec4D tlist[3]) {
			for(unsigned int i = 0; i < 3; i++) {
				this->vlist[i] = vlist[i];
				this->tlist[i] = tlist[i];
			}
		}

	};

	enum { MX_ACTIVE = 0x1, MX_CULLED, MX_VISIBLE, MX_CLIPPED, MX_BACKFACE };

	
	class RenderList {
	public:
		mvector<Triangle> polys;
		int num_polys;
		RenderList() {
			num_polys = 0;
		}
		
		void RemoveFaces(vec4D &pos) {
			for(unsigned int i = 0; i < polys.size(); i++) {
				if(polys[i].state == 0 || polys[i].state & MX_ACTIVE || polys[i].state & MX_VISIBLE ) // not active
					continue;
				vec4D u,v,n,b;
				u = u.Build(polys[i].tlist[0], polys[i].tlist[1]);
				v = v.Build(polys[i].tlist[0], polys[i].tlist[2]);
				n = u.CrossProduct(v);
				b = b.Build(polys[i].tlist[0], pos);
				float dot = n.DotProduct(b);
				if(dot <= 0.0f) {
					polys[i].state = MX_BACKFACE;
				}
			}
		}

		void Reset() {
			if(!polys.empty()) {
				polys.erase(polys.begin(),polys.end());
//				polys.erase();
//				std::cout << "TEST\n";
//				polys.erase();
			}
			num_polys = 0;
		}

		void TransformRenderList(Mat4D &mrot, int type) {
			switch(type) {
				case 0: { // TRANSFORM LOCAL
					for(int i = 0; i < num_polys; i++) {
						if(polys[i].state == 0 || polys[i].state == MX_BACKFACE)
							continue;
						for(int z = 0; z < 3; z++) {
							polys[i].vlist[z] = mrot.MulVec(polys[i].vlist[z]);
						}
					}
				}
				break;
			}
		}
		
		void RemoveFaces(vec4D &matrix_rotation, vec4D &pos) {
			for(unsigned int i = 0; i < polys.size(); i++) {
				if(polys[i].state == 0) // not active
					continue;
				vec4D u,v,n,b;
				u = u.Build(polys[i].tlist[0], polys[i].tlist[1]);
				v = v.Build(polys[i].tlist[0], polys[i].tlist[2]);
				n = u.CrossProduct(v);
				b = b.Build(polys[i].tlist[0], pos);
				float dot = n.DotProduct(b);
				if(dot <= 0.0f) {
					polys[i].state = MX_BACKFACE;
				}
			}
		}
		

		void ModelToWorld(vec4D &pos, int type) {
			switch(type) {
				case 0: {
					for(int col = 0; col < this->num_polys; col++)
					{
						if(this->polys[col].state == 0 || polys[col].state == MX_BACKFACE)
							continue;
						for(int vertex = 0; vertex < 3; vertex++) {
							this->polys[col].tlist[vertex] = (polys[col].vlist[vertex] + pos);
						} 
					}
						}
						break;
				case 1:
					break;
			}
		}

		void BuildRenderList(Triangle &triangles) {
			polys.push_back(triangles);
			num_polys++;
		}

	};

	class mxObject {
	public:
		int id, state, attr;
		float avg_rad, max_rad;
		vec4D world_pos, dir, ux, uy, uz;
		int num_vertices, num_polys;
		mvector<vec4D> local, trans;
		mvector<Triangle> vlist;

		// load my format
		bool LoadMX(mstring source, vec4D &scale, vec4D &obj_pos, vec4D &rotation) {
			return false;
			mfstream file;
			file.open(source.c_str(),std::ios::in);
			if(!file.is_open())
				return false;

			this->world_pos = obj_pos;
			
			int num_vertex = 0, num_polys = 0, got_vertex = 0, got_polys = 0;

			bool get_vertex = false, get_polys = false;
			D3DCOLOR cur_color;

			mstring header;
			getline(file, header);
			if(header != ".mx_format")
				return false;

			while(!file.eof()) {
				mstring cur_line;
				getline(file, cur_line);
				if(cur_line[0] == '/' || cur_line[0] == '#' || cur_line.length() < 2)
					continue;
				mvector<mstring> tok_vec;
				token::tokenize<mstring>(cur_line,mstring(" "), tok_vec);

				
				if(tok_vec[0] == "tri" && tok_vec.size() > 2) {
					num_vertex = atoi(tok_vec[1].c_str()), num_polys = atoi(tok_vec[2].c_str());
					get_vertex = true;
					this->num_vertices = num_vertex;
					this->num_polys = num_polys;
				}
				else if(tok_vec[0] == "color" && tok_vec.size() > 3) {
					cur_color = D3DCOLOR_XRGB(atoi(tok_vec[1].c_str()),atoi(tok_vec[2].c_str()),atoi(tok_vec[3].c_str()));
				}
				else if(get_vertex == true && tok_vec.size() > 2) {
					vec4D vertex;
					vertex.x = float(atof(tok_vec[0].c_str())*scale.x);
					vertex.y = float(atof(tok_vec[1].c_str())*scale.y);
					vertex.z = float(atof(tok_vec[2].c_str())*scale.z);
					vertex.w = 1;
					this->local.push_back(vertex);
					memset(&vertex,0,sizeof(vertex));
					this->trans.push_back(vertex);
					if(++got_vertex > num_vertex-1) {
						get_vertex = false;
						get_polys = true;
						continue;
					}
				}
				else if(get_polys == true && tok_vec.size() > 4) {
					Triangle tri;
					int count = atoi(tok_vec[1].c_str());
					tri.vert[0] = atoi(tok_vec[2].c_str());
					tri.vert[1] = atoi(tok_vec[3].c_str());
					tri.vert[2] = atoi(tok_vec[4].c_str());
					tri.state = atoi(tok_vec[0].c_str());
					tri.color = cur_color;
					this->vlist.push_back(tri);
				}
			}

			file.close();

			return true;
		}

		// load andre's format
		bool LoadPLG(mstring plg,vec4D &scale, vec4D &obj_pos, vec4D &rotation, D3DCOLOR rcolor) {
			mfstream file;
			file.open(plg.c_str(), std::ios::in);
			if(!file.is_open()) {
				printf("FAILED TO OPEN FILE STREAM!");
				return false;
			}
			this->world_pos = obj_pos;
			while(!file.eof()) {
				mstring cur_line;
				getline(file,cur_line);
				if(cur_line[0] == '#' || cur_line.length() < 2)
					continue;
				char type[256];
				int num_v, num_p;
				sscanf(cur_line.c_str(),"%s %d %d", type, &num_v, &num_p);
				int counter = 0;
				if(strcmp(type,"tri") != 0) {
				}
				this->num_polys = num_p;
				this->num_vertices = num_v;

				while(counter < num_v) {
					getline(file,cur_line);
					if(cur_line[0] == '#' || cur_line.length() < 2)
						continue;
					vec4D vertex;
					sscanf(cur_line.c_str(), "%f %f %f", &vertex.x, &vertex.y, &vertex.z);
					vertex.w = 1;
					vertex.x *= scale.x;
					vertex.y *= scale.y;
					vertex.z *= scale.z;
					this->local.push_back(vertex);
					
					memset(&vertex,0,sizeof(vertex));
					this->trans.push_back(vertex);
					counter++;
					
					
				}
				counter = 0;
				//ComputeRad();
				while(counter < num_p) {
					getline(file,cur_line);
						if(cur_line[0] == '#' || cur_line.length() < 2)
							continue;
					Triangle tri;
					int num = 0;
					sscanf(cur_line.c_str(),"%x %d %d %d %d",&tri.state, &num, &tri.vert[0], &tri.vert[1], &tri.vert[2]);
					tri.color = rcolor;
					this->vlist.push_back(tri);
					counter++;
				}
			}

			file.close();
			return true;
		}

		float ComputeRad() {
			max_rad = 0;
			avg_rad = 0;
			for(unsigned int i = 0; i < local.size(); i++) {
				float dist = sqrtf( local[i].x + local[i].x * local[i].y + local[i].y * local[i].z + local[i].z );
				avg_rad += dist;
				if(avg_rad > max_rad) 
					max_rad = dist;	
			}
			avg_rad /= float(local.size());
			return max_rad;
		}

		bool CullObject(bool cull_x, bool cull_y, bool cull_z,Mat4D &camera_pos, float far_z, float near_z, float viewplane_width,float viewplane_height, float view_dist) {
			vec4D s_p;
			s_p = camera_pos.MulVec(world_pos);

			if(cull_z == true) {
				if(((s_p.z - this->max_rad) > far_z) || ((s_p.z+this->max_rad) < near_z) ) {
					this->state = MX_CULLED;
					return true;
				}
			}

			if(cull_x == true) {
				float z_test = (0.5f)*viewplane_width*s_p.z/view_dist;
				if(s_p.x+max_rad > z_test)
				{
					this->state = MX_CULLED;
					return true;
				}
				else if(s_p.x+max_rad < -z_test) {
					this->state = MX_CULLED;
					return true;
				}
			}
			if(cull_y == true) {
				float z_test = (0.5f)*viewplane_height*s_p.z/view_dist;
				if(s_p.y+max_rad > z_test) {
					this->state = MX_CULLED;
					return true;
				}
				else if(s_p.y+max_rad < -z_test) {
					this->state = MX_CULLED;
					return true;
				}
			}

			return false;
		}
		void ModelToWorld(int type = 0) {
			switch(type) {
				case 0:
					{
						for(unsigned int i = 0; i < local.size(); i++) {
							trans[i] = local[i] + world_pos;
						}
						break;
					}
			}
		}

		void TransformObject(Mat4D &mrot, int type=0) {
			switch(type) {
				case 0: 
					{
						for(unsigned int i = 0; i < local.size(); i++)  {
							local[i] = mrot.MulVec(local[i]);
						}
					}
					break;
			}
		}

		// the 4D vector pos, is the position of the camera
		void RemoveFaces(Mat4D &mrot, vec4D &pos) {
			for(unsigned int i = 0; i < this->vlist.size(); i++) {
				if(vlist[i].state == 0) // not active
					continue;
				vec4D u,v,n,b;
				int v1 = vlist[i].vert[0], v2 = vlist[i].vert[1] , v3 = vlist[i].vert[2];
				u = u.Build(trans[v1], trans[v2]);
				v = v.Build(trans[v1], trans[v3]);
				n = u.CrossProduct(v);
				b = b.Build(trans[v1], pos);
				float dot = n.DotProduct(b);
				if(dot <= 0.0f) {
					vlist[i].state = MX_BACKFACE;
				}
			}
		}

		void BuildRenderList(RenderList &l) {
			for(unsigned int i = 0; i < vlist.size(); i++) {
				Triangle tri;
				tri.state = vlist[i].state;
				tri.color = vlist[i].color;
				tri.attr  = vlist[i].color;
				tri.vlist[0] = local[vlist[i].vert[0]];
				tri.vlist[1] = local[vlist[i].vert[1]];
				tri.vlist[2] = local[vlist[i].vert[2]];
				tri.tlist[0] = trans[vlist[i].vert[0]];
				tri.tlist[1] = trans[vlist[i].vert[1]];
				tri.tlist[2] = trans[vlist[i].vert[2]];
				l.BuildRenderList(tri);
			}
		}

		void Reset() {
			for(unsigned int i = 0; i < this->vlist.size(); i++)
				vlist[i].state = MX_ACTIVE;

		}
	};


	

	class Camera {
	public:
		int state, attr;
		vec4D pos, dir, u, v, n, target;
		float view_dist, fov, near_clip_z, far_clip_z;
		Plane3D rt_clip_plane, lt_clip_plane,tp_clip_plane,bt_clip_plane;
		float viewplane_height, viewplane_width;
		float viewport_width, viewport_height, viewport_center_x, viewport_center_y;
		float aspect_ratio;
		Mat4D mcam, mper, mscr;

		Camera() {
			memset(this,0,sizeof(Camera));
		}

		void InitalizeForEuler() {
			pos.x = 100;
			pos.y = 200;
			pos.z = 300;
			dir.x = -48;
			dir.y = 0;
			dir.z = 0;
			BuildEuler(5);
		}

		void Init(int attr, vec4D &pos, vec4D &cam_dir, vec4D *cam_target, float near_clip_z, float far_clip_z, float fov, float viewport_width, float viewport_height) {
			this->attr = attr;
			this->pos = pos;
			this->dir = cam_dir;
			u.Set(1,0,0);
			v.Set(0,1,0);
			n.Set(0,0,1);
			if(cam_target != 0)
				target = *cam_target;
			else
				memset(&target,0,sizeof(target));

			this->near_clip_z = near_clip_z;
			this->far_clip_z = far_clip_z;

			this->viewport_height = viewport_height;
			this->viewport_width = viewport_width;
			this->viewport_center_x = (viewport_width-1)/2;;
			this->viewport_center_y =(viewport_height-1)/2;
			this->aspect_ratio =  float(float(viewport_width)/float(viewport_height));
			mcam.LoadIdentity();
			mper.LoadIdentity();
			mscr.LoadIdentity();

			this->fov = fov;
			this->viewplane_width = 2.0f;
			this->viewplane_height = 2.0f/this->aspect_ratio;
			float tan_fov_div2 = tan(deg2rad(fov/2));
			this->view_dist = (0.5f) * (this->viewplane_width)*tan_fov_div2;
			if(fov == 90.0f) {
				vec3D pt_origin(0,0,0);
				vec3D vn(1,0,-1);
				rt_clip_plane.Set(pt_origin, vn, true);
				vn.Set(-1,0,-1);
				lt_clip_plane.Set(pt_origin, vn, true);
				vn.Set(0,1,-1);
				tp_clip_plane.Set(pt_origin, vn, true);
				vn.Set(0,-1,-1);
				bt_clip_plane.Set(pt_origin, vn, true);
			}
			else {
				vec3D pt_origin(0,0,0);
				vec3D vn;
				vn.Set(this->view_dist, 0, this->viewplane_width / 2.0f);
				rt_clip_plane.Set(pt_origin,vn,true);
				vn.Set(this->view_dist, 0, this->viewplane_width/2.0f);
				lt_clip_plane.Set(pt_origin,vn,true);
				vn.Set(0,this->view_dist, this->viewplane_width/2.0f);
				tp_clip_plane.Set(pt_origin,vn,true);
				vn.Set(0,this->view_dist, this->viewplane_width/2.0f);
				bt_clip_plane.Set(pt_origin,vn,true);
			}

		}

		void BuildEuler(int cam_rot_seq) {
			Mat4D mt_inv
				( 1,0,0,0,
				0,1,0,0,
				0,0,1,0,
				-pos.x,-pos.y,-pos.z, 1
				);
			float theta_x = dir.x;
			float theta_y = dir.y;
			float theta_z = dir.z;

			float cos_theta = fast_cosf(theta_x);
			float sin_theta = -fast_sinf(theta_x);
			Mat4D mx_inv (1, 0,    0,         0,
				0,    cos_theta, sin_theta, 0,
				0,   -sin_theta, cos_theta, 0,
				0,    0,         0,         1);

			cos_theta = fast_cosf(theta_y);
			sin_theta = -fast_sinf(theta_y);

			Mat4D my_inv(cos_theta, 0, -sin_theta, 0,  
				0,         1,  0,         0,
				sin_theta, 0,  cos_theta,  0,
				0,         0,  0,          1);

			cos_theta = fast_cosf(theta_z);
			sin_theta = -fast_sinf(theta_z);

			Mat4D mz_inv(cos_theta, sin_theta, 0, 0,  
				-sin_theta, cos_theta, 0, 0,
				0,         0,         1, 0,
				0,         0,         0, 1);

			Mat4D mtmp, mrot;
			switch(cam_rot_seq) {
				case 0://XYZ
					mtmp = mx_inv * my_inv;
					mrot = mtmp * mz_inv;
					break;
				case 1://YXZ
					mtmp = my_inv * mx_inv;
					mrot = mtmp * mz_inv;
					break;
				case 2://XZY
					mtmp = mx_inv * mz_inv;
					mrot = mtmp * my_inv;
					break;
				case 3://YZX
					mtmp = my_inv * mz_inv;
					mrot = mtmp * mx_inv;
					break;
				case 4://ZYX
					mtmp = mz_inv * my_inv;
					mrot = mtmp * mx_inv;
					break;
				case 5://ZXY
					mrot = mz_inv * mx_inv * my_inv;
					break;
			}

			this->mcam = mt_inv * mrot;
		}

		void BuildUVN(int type) {
			Mat4D mt_inv(1,0,0,0,0,1,0,0,0,0,1,0,-pos.x,-pos.y,-pos.z, 1), mt_uvn, mtmp;
			if(type == 1) {// Sphereical

				
				// to do:
			}
			n = n.Build(pos,target);
			v.Set(0,1,0,1);
			u = v.CrossProduct(n);
			v = n.CrossProduct(u);
			u.Normalize();
			v.Normalize();
			n.Normalize();
			mt_uvn.Set(u.x,v.x,n.x,0,u.y,v.y,n.y,0,u.z,v.z,n.z,0,0,0,0,1);
			mcam = mt_inv * mt_uvn;
		}

		void CameraToPerspective(RenderList &l) {
			for(int i = 0; i < l.num_polys; i++) {
				if(l.polys[i].state == 0 || l.polys[i].state == MX_BACKFACE)
					continue;
				else
					for(int z = 0; z < 3; z++) {
						float cur_z = l.polys[i].tlist[z].z;
						l.polys[i].tlist[z].x = this->view_dist * l.polys[i].tlist[z].x/ cur_z;
						l.polys[i].tlist[z].y = this->view_dist * l.polys[i].tlist[z].y * this->aspect_ratio / cur_z;
					}
			}
		}

		void CameraToPerspective(mxObject &m) {

			for(unsigned int i = 0; i < m.trans.size(); i++) {
				m.trans[i].x = view_dist*m.trans[i].x/m.trans[i].z;
				m.trans[i].y = view_dist*m.trans[i].y*aspect_ratio/m.trans[i].z;
			}

		}

		void PerspectiveToScreen(RenderList &l) {
			for(int i = 0; i < l.num_polys; i++) {
				if(l.polys[i].state == 0 || l.polys[i].state == MX_BACKFACE)
					continue;

				float alpha =  (0.5f * viewport_width - 0.5f);
				float beta  =  (0.5f * viewport_height - 0.5f);
	

				for(int z = 0; z < 3; z++) {
					l.polys[i].tlist[z].x = alpha + alpha * l.polys[i].tlist[z].x;
					l.polys[i].tlist[z].y = beta  - beta  * l.polys[i].tlist[z].y;
				}
			}
		}

		void PerspectiveToScreen(mxObject &o) {
			float alpha = (0.5f*viewport_width-0.5f);
			float beta  = (0.5f*viewport_height-0.5f);

			for(unsigned int i = 0; i < o.trans.size(); i++) {
				o.trans[i].x = alpha+alpha * o.trans[i].x;
				o.trans[i].y = beta-beta * o.trans[i].y;
			}

		}

		void BuildPerspective(Mat4D &m) {
			float alpha = (0.5f*viewport_width-0.5f);
			float beta  = (0.5f*viewport_height-0.5f);
			m.Set(alpha,0,0,0,0,-beta,0,0,alpha,beta,1,0,0,0,0,1);
		}

		void WorldToCamera(RenderList &l) {
			for(int row = 0; row < l.num_polys; row++) {

				if(l.polys[row].state == 0 || l.polys[row].state == MX_BACKFACE)
					continue;
				for(int col = 0; col < 3; col++) {
					vec4D r;
					r = mcam.MulVec(l.polys[row].tlist[col]);
					l.polys[row].tlist[col] = r; 
				}
			}
		}

		void WorldToCamera(mxObject &m) {
			for(unsigned int i = 0; i < m.trans.size(); i++) 
				m.trans[i] = mcam.MulVec(m.trans[i]);
		}
	};


	class PipeLine {
//		mxHwnd *mx;
	public:
		PipeLine() {
//			mx = 0;
		}
		int max_clip_x,max_clip_y,min_clip_x,min_clip_y;

		void Begin() {
//			this->mx = &mx;
			clip_min_x = clip_min_y  = min_clip_x = min_clip_y = 0;
			clip_max_x = front->w - 1;
			clip_max_y = front->h - 1;
			max_clip_x = front->w - 1;
			max_clip_y = front->h - 1;
			//this->mx->paint.Lock();
			buf = lock(front, front->format->BitsPerPixel);
		}

		void DrawPolys(RenderList &l) {
			for(unsigned int i = 0; i < l.polys.size(); i++) {;
			if(l.polys[i].state == 0 || l.polys[i].state == MX_BACKFACE )
				continue;
			else {
				DrawClipedLine(int(l.polys[i].tlist[0].x), int(l.polys[i].tlist[0].y), int(l.polys[i].tlist[1].x), int(l.polys[i].tlist[1].y), l.polys[i].color);
				DrawClipedLine(int(l.polys[i].tlist[1].x), int(l.polys[i].tlist[1].y), int(l.polys[i].tlist[2].x), int(l.polys[i].tlist[2].y), l.polys[i].color);
				DrawClipedLine(int(l.polys[i].tlist[2].x), int(l.polys[i].tlist[2].y), int(l.polys[i].tlist[0].x), int(l.polys[i].tlist[0].y), l.polys[i].color);
			}
			}
		}

		void DrawObject(mxObject &o) {

			for(unsigned int i = 0; i < o.vlist.size(); i++) {
				if(o.vlist[i].state == 0 || o.vlist[i].state == MX_BACKFACE)
					continue;
				int vertex_one = o.vlist[i].vert[0], vertex_two = o.vlist[i].vert[1] , vertex_three = o.vlist[i].vert[2];
				DrawClipedLine(int(o.trans[vertex_one].x), int(o.trans[vertex_one].y), int(o.trans[vertex_two].x), int(o.trans[vertex_two].y), o.vlist[i].color);
				DrawClipedLine(int(o.trans[vertex_two].x), int(o.trans[vertex_two].y), int(o.trans[vertex_three].x), int(o.trans[vertex_three].y), o.vlist[i].color);
				DrawClipedLine(int(o.trans[vertex_three].x), int(o.trans[vertex_three].y),int(o.trans[vertex_one].x), int(o.trans[vertex_one].y), o.vlist[i].color);

			}
		}

		int clip_min_x, clip_max_x, clip_min_y, clip_max_y;


		enum LINE_CODE { CODE_C = 0x0000, CODE_N = 0x0008, CODE_S = 0x0004, CODE_E = 0x0002, CODE_W = 0x0001, CODE_NE = 0x000a, CODE_SE = 0x0006,CODE_NW = 0x0009 ,CODE_SW = 0x0005 };


		bool ClipLine(int &x1, int &y1, int &x2, int &y2) {
			int xc1 = x1, yc1 = y1, xc2 = x2, yc2 = y2;
			int p1_code = 0,p2_code = 0;
			if (y1 < clip_min_y)
				p1_code |= CODE_N;
			else
				if (y1 > clip_max_y)
					p1_code |= CODE_S;

			if (x1 < clip_min_x)
				p1_code |= CODE_W;
			else
				if (x1 > clip_max_x)
					p1_code |= CODE_E;

			if (y2 < clip_min_y)
				p2_code |= CODE_N;
			else
				if (y2 > clip_max_y)
					p2_code |= CODE_S;

			if (x2 < clip_min_x)
				p2_code |= CODE_W;
			else
				if (x2 > clip_max_x)
					p2_code |= CODE_E;

			if(p1_code && p2_code)
				return false;

			if(p1_code == 0 && p2_code)
				return true;
			switch(p2_code) {
				case CODE_C: break;
				case CODE_N:
					yc2 = clip_min_y;
					xc2 = x2 + (clip_min_y-y2)*(x1-x2)/(y1-y2);
					break;
				case CODE_S:
					yc2 = clip_max_y;
					xc2 = x2 + (clip_max_y-y2)*(x1-x2)/(y1-y2);
					break;
				case CODE_W:
					xc2 = clip_min_x;
					yc2 = y2 + (clip_min_x-x2)*(y1-y2)/(x1-x2);
					break;
				case CODE_E:
					xc2 = clip_max_x;
					yc2 = y2 + (clip_max_x-x2)*(y1-y2)/(x1-x2);
					break;
				case CODE_NE: {
					yc2 = clip_min_x;
					xc2 = x2 + int(0.5+(clip_min_x-y2)*(x1-x2)/(y1-y2));

					if (xc2 < clip_min_x || xc2 > clip_max_x) {
						xc2 = clip_max_x;
						yc2 = y2 + int(0.5+(clip_max_x-x2)*(y1-y2)/(x1-x2));
					} 
							  }
							  break;
				case CODE_SE:  {

					yc2 = clip_max_y;
					xc2 = x2 + int(0.5+(clip_max_y-y2)*(x1-x2)/(y1-y2));
					if (xc2 < clip_min_x || xc2 > clip_max_x) {
						xc2 = clip_max_x;
						yc2 = y2 + int(0.5+(clip_max_x-x2)*(y1-y2)/(x1-x2));
					} 
							   }
							   break;

				case CODE_NW:
					yc2 = clip_min_y;
					xc2 = x2 + int(0.5+(clip_min_y-y2)*(x1-x2)/(y1-y2));
					if (xc2 < clip_min_x || xc2 > clip_max_x) {
						xc2 = clip_min_x;
						yc2 = y2 + int(0.5+(clip_min_x-x2)*(y1-y2)/(x1-x2));
					} 
					break;
				case CODE_SW:
					yc2 = clip_max_y;
					xc2 = x2 + int(0.5+(clip_max_y-y2)*(x1-x2)/(y1-y2));
					if (xc2 < clip_min_x || xc2 > clip_max_x)	{
						xc2 = clip_min_x;
						yc2 = int(y2 + 0.5+(clip_min_x-x2)*(y1-y2)/(x1-x2));
					}
					break;
				default:
					break;

			}

			if ((xc1 < clip_min_x) || (xc1 > clip_max_x) ||(yc1 < clip_min_y) || (yc1 > clip_max_y) ||(xc2 < clip_min_x) || (xc2 > clip_max_x) || (yc2 < clip_min_y) || (yc2 > clip_max_y) )
				return false;
			x1 = xc1;
			y1 = yc1;
			x2 = xc2;
			y2 = yc2;

			return true;
		}

		void DrawClipedLine(int x1, int y1, int x2, int y2, D3DCOLOR color) {
			if(ClipLine(x1,y1,x2,y2))
			{
				drawline(x1,y1,x2,y2,color);
			}	
		}

		
		void DrawSolidPolys(RenderList &l) {

			for(unsigned int i = 0; i < l.polys.size(); i++) {
				if(l.polys[i].state == 0 || l.polys[i].state == MX_BACKFACE )
					continue;
					drawtri(int(l.polys[i].tlist[0].x), int(l.polys[i].tlist[0].y), int(l.polys[i].tlist[1].x), int(l.polys[i].tlist[1].y), int(l.polys[i].tlist[2].x), int(l.polys[i].tlist[2].y), l.polys[i].color);
			}
		}


		void End() {
//			mx->paint.UnLock();
			unlock(front);
		}

	};

}


#endif
