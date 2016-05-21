//#include "Nurbs.h"
#define GNURBS_MAX_ORDER 16
#include "gen.h"
#include <GL/glut.h>
// 
// find span - see the NURBS Book
// page 68 
// 


int FindSpan (int n, int p, float u, const float *U)
{   

	int low, high, mid; 
	if (u >= U[n+1]) // savety >= check 
		return (n);
	low = p; 
	high = n+1; 
	mid = (low + high)/2; 
	while (u < U[mid] || u >= U[mid+1]) 
	{	if ( u < U[mid]) 
		{ high = mid; 
		}
		else 
		{ low = mid; 
		}
		mid = (low + high)/2;		
	}
	
	return (mid); 

}



// 
// get Basis functions 
// page 70
// 

void BasisFuns ( int i, float u, int p, const float *U, float *Nf ) 
{

	float left[GNURBS_MAX_ORDER];  // could use alloca 
	float right[GNURBS_MAX_ORDER]; 
	float saved, temp; 

	Nf[0]  = 1.0;
	int j;
	for (j=1; j<=p; j++)
	{
		left[j] = u-U[i+1-j];
		right[j] = U[i+j] -u; 
		saved = 0.0; 
		for (int r=0; r<j; r++)
		{ 
			temp = Nf[r]/(right[r+1]+left[j-r]);
			Nf[r] = saved+right[r+1]*temp; 
			saved = left[j-r]*temp;
		}
		Nf[j] = saved; 
	} 
}




// evaluate point on Nurbs Surface 
// version with weight

bool SurfacePoint(
				  float u, float v, int uOrder, int vOrder, int uDimension, int vDimension,
				  const float *uKnot, const float * vKnot,int sstride,int tstride,
				  float *ctlarray,
				  float *dest // result
				  )
{
	
	float Nu[GNURBS_MAX_ORDER]; 
	float Nv[GNURBS_MAX_ORDER]; 

	int pu = uOrder-1;
	int pv = vOrder-1;


	// skip if src not in knot parametric range
	if (u<uKnot[pu]) return false;
	if (u>uKnot[uDimension]) return false;

	if (v<vKnot[pv]) return false;
	if (v>vKnot[vDimension]) return false;

	// find knot vector span and evaluate Bspline Basis functions
	int spanu=FindSpan(uDimension,pu,u,uKnot);
	BasisFuns (spanu, u, pu, uKnot, Nu);

	int spanv=FindSpan(vDimension,pv,v,vKnot);
	BasisFuns (spanv, v, pv, vKnot, Nv);

	float x=0.0;
	float y=0.0;
	float z=0.0;

	//Point result;
	//result.Zero();

	int vi;

	int pvi=(spanv-pv)*uDimension;

	for (vi=0; vi<=pv; vi++, pvi+=uDimension)
	{
		float w= Nv[vi];

		for (int ui=0; ui<=pu; ui++)
		{
			int pui = spanu-pu+ui;
			x += w * Nu[ui] * (*(ctlarray+vi*sstride+ui*tstride+0));
			//cout << *(ctlarray+vi*sstride+ui*tstride+0) << "vi:" << vi << "ui:" << ui << endl;
			y += w * Nu[ui] * (*(ctlarray+vi*sstride+ui*tstride+1));
			z += w * Nu[ui] * (*(ctlarray+vi*sstride+ui*tstride+2));
			//result += w * Nu[ui] * P[pvi+pui];
		
		}

	}


	// TRACE("%f %f %f \n",result.x,result.y,result.z);


	*dest++ = x;
	*dest++ = y;
	*dest++ = z;

	return true;


}


//
// Compute the uk's 
// [Piegl] page 364 
//
void ComputeUkVector(int N, float *t, float* uk)
{
	float d;
	int i; 

	d = t[N] - t[0];
	uk[0] = 0.; 
	for (i=1; i<N; i++)
	{
		uk[i] = t[i]/d;
	}
	uk[N] = 1.;
}
//
// calculate the knotvector  
// page 365 
//
void ComputeKnotVector(int N, int pdim, int m, float *uk, float *u)
{
	int i, j; 

	for (j=0; j<=pdim; j++) 
	{ 
		u[j] = 0.; 
	} 

	for (j=1; j<=N-pdim; j++) 
	{	
		u[j+pdim] = 0.; 
		for (i=j; i<=j+pdim-1; i++)
		{
			u[j+pdim] = u[j+pdim] + uk[i];
		}
		u[j+pdim] = u[j+pdim]/(float) pdim;  
 	}	

	for (j=(m-pdim); j<=m; j++) 
	{ 
		u[j] = 1.;
	}
}

