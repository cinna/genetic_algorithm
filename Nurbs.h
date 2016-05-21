#include <GL/glut.h>

class Nurbs
{
public:
	
	int FindSpan (int , int , float , const float *);
	void BasisFuns ( int , float , int , const float *, float * ); 
	bool SurfacePoint(
					  float , float , int , int , int , int ,
					  const float *, const float * ,int ,int ,
					  float *,
					  float * // result
					  );
	void ComputeUkVector(int , float *, float* );
	void ComputeKnotVector(int , int , int , float *, float *);
	void fitness (gen &);
	void init_surface(void)
};