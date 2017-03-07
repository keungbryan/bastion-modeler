#include <windows.h>
#include <Fl/gl.h>
#include <gl/glu.h>

#include "camera.h"

#pragma warning(push)
#pragma warning(disable : 4244)

#ifndef M_PI
#define M_PI 3.141592653589793238462643383279502
#endif 

const float kMouseRotationSensitivity		= 1.0f/90.0f;
const float kMouseTranslationXSensitivity	= 0.03f;
const float kMouseTranslationYSensitivity	= 0.03f;
const float kMouseZoomSensitivity			= 0.08f;

void MakeDiagonal(Mat4f &m, float k)
{
	register int i,j;

	for (i=0; i<4; i++)
		for (j=0; j<4; j++)
			m[i][j] = (i==j) ? k : 0.0f;
}

void MakeHScale(Mat4f &m, const Vec3f &s)	
{
	MakeDiagonal(m,1.0f);
	m[0][0] = s[0]; m[1][1] = s[1];	m[2][2] = s[2];
}

void MakeHTrans(Mat4f &m, const Vec3f &s)
{
	MakeDiagonal(m,1.0f);
	m[0][3] = s[0]; m[1][3] = s[1]; m[2][3] = s[2];
}

void MakeHRotX(Mat4f &m, float theta)
{
	MakeDiagonal(m,1.0f);
	float cosTheta = cos(theta);
	float sinTheta = sin(theta);
	m[1][1] = cosTheta;
	m[1][2] = -sinTheta;
	m[2][1] = sinTheta;
	m[2][2] = cosTheta;
}

void MakeHRotY(Mat4f &m, float theta)
{
	MakeDiagonal(m,1.0f);
	float cosTheta = cos(theta);
	float sinTheta = sin(theta);
	m[0][0] = cosTheta;
	m[2][0] = -sinTheta;
	m[0][2] = sinTheta;
	m[2][2] = cosTheta;
}

void MakeHRotZ(Mat4f &m, float theta)
{
	MakeDiagonal(m,1.0f);
	float cosTheta = cos(theta);
	float sinTheta = sin(theta);
	m[0][0] = cosTheta;
	m[0][1] = -sinTheta;
	m[1][0] = sinTheta;
	m[1][1] = cosTheta;
}


void Camera::calculateViewingTransformParameters() 
{
	Mat4f dollyXform;
	Mat4f azimXform;
	Mat4f elevXform;
	Mat4f twistXform;
	Mat4f originXform;

	Vec3f upVector;

	MakeHTrans(dollyXform, Vec3f(0,0,mDolly));
	MakeHRotY(azimXform, mAzimuth);
	MakeHRotX(elevXform, mElevation);
	MakeDiagonal(twistXform, 1.0f);
	MakeHTrans(originXform, mLookAt);
	
	mPosition = Vec3f(0,0,0);
	// grouped for (mat4 * vec3) ops instead of (mat4 * mat4) ops
	mPosition = originXform * (azimXform * (elevXform * (dollyXform * mPosition)));

	if ( fmod((double)mElevation, 2.0*M_PI) < 3*M_PI/2 && fmod((double)mElevation, 2.0*M_PI) > M_PI/2 )
		mUpVector= Vec3f(0,-1,0);
	else
		mUpVector= Vec3f(0,1,0);

	mDirtyTransform = false;
}

Camera::Camera() 
{
	mElevation = mAzimuth = mTwist = 0.0f;
	mDolly = -20.0f;
	mElevation = 0.2f;
	mAzimuth = (float)M_PI;

	mLookAt = Vec3f( 0, 0, 0 );
	mCurrentMouseAction = kActionNone;

	calculateViewingTransformParameters();
}

void Camera::clickMouse( MouseAction_t action, int x, int y )
{
	mCurrentMouseAction = action;
	mLastMousePosition[0] = x;
	mLastMousePosition[1] = y;
}

void Camera::dragMouse( int x, int y )
{
	Vec3f mouseDelta   = Vec3f(x,y,0.0f) - mLastMousePosition;
	mLastMousePosition = Vec3f(x,y,0.0f);

	switch(mCurrentMouseAction)
	{
	case kActionTranslate:
		{
			calculateViewingTransformParameters();

			double xTrack =  -mouseDelta[0] * kMouseTranslationXSensitivity;
			double yTrack =  mouseDelta[1] * kMouseTranslationYSensitivity;

			Vec3f transXAxis = mUpVector ^ (mPosition - mLookAt);
			transXAxis /= sqrt((transXAxis*transXAxis));
			Vec3f transYAxis = (mPosition - mLookAt) ^ transXAxis;
			transYAxis /= sqrt((transYAxis*transYAxis));

			setLookAt(getLookAt() + transXAxis*xTrack + transYAxis*yTrack);
			
			break;
		}
	case kActionRotate:
		{
			float dAzimuth		=   -mouseDelta[0] * kMouseRotationSensitivity;
			float dElevation	=   mouseDelta[1] * kMouseRotationSensitivity;
			
			setAzimuth(getAzimuth() + dAzimuth);
			setElevation(getElevation() + dElevation);
			
			break;
		}
	case kActionZoom:
		{
			float dDolly = -mouseDelta[1] * kMouseZoomSensitivity;
			setDolly(getDolly() + dDolly);
			break;
		}
	case kActionTwist:
		// Not implemented
	default:
		break;
	}

}

void Camera::releaseMouse( int x, int y )
{
	mCurrentMouseAction = kActionNone;
}


void Camera::applyViewingTransform() {
	if( mDirtyTransform )
		calculateViewingTransformParameters();

	// Place the camera at mPosition, aim the camera at
	// mLookAt, and twist the camera such that mUpVector is up
	/*gluLookAt(	mPosition[0], mPosition[1], mPosition[2],
				mLookAt[0],   mLookAt[1],   mLookAt[2],
				mUpVector[0], mUpVector[1], mUpVector[2]);*/
	lookAt(mPosition, mLookAt, mUpVector);
}

void Camera::lookAt(Vec3f eye, Vec3f at, Vec3f up) {
	/*
	* f = at - eye
	* normalize f -> F
	* normalize up -> U
	* s = F X U
	*     sx = FyUz - FzUy
	*     sy = FzUx - FxUz
	*     sz = FxUy - FyUx
	* IMPORTANT: NORMALIZE s
	* V = s X F
	* M = [ { sx, sy, sz, 0 },
	*       { Vx, Vy, Vz, 0 },
	*       { -Fx, -Fy, -Fz, 0 },
	*       { 0, 0, 0, 1} ]
	*
	* glMultMatrixF(M)
	* glTranslated(-eyex, -eyey, -eyez)
	*/

	Vec3f f = Vec3f(at[0] - eye[0], at[1] - eye[1], at[2] - eye[2]);
	//normalize f (-z-axis)
	float fd = sqrtf((f[0] * f[0]) + (f[1] * f[1]) + (f[2] * f[2]));
	Vec3f F = Vec3f(f[0] / fd, f[1] / fd, f[2] / fd);
	//normalize up (y-axis)
	float upd = sqrtf((up[0] * up[0]) + (up[1] * up[1]) + (up[2] * up[2]));
	Vec3f U = Vec3f(up[0] / upd, up[1] / upd, up[2] / upd);
	//s = F X U
	Vec3f s = Vec3f(F[1] * U[2] - F[2] * U[1],
					F[2] * U[0] - F[0] * U[2],
					F[0] * U[1] - F[1] * U[0]);
	//normalize s (x-axis)
	float sd = sqrtf((s[0] * s[0]) + (s[1] * s[1]) + (s[2] * s[2]));
	s[0] /= sd;
	s[1] /= sd;
	s[2] /= sd;
	//V = s X F (new y-axis)
	Vec3f V = Vec3f(s[1] * F[2] - s[2] * F[1],
					s[2] * F[0] - s[0] * F[2],
					s[0] * F[1] - s[1] * F[0]);

	GLfloat M[4][4];
	M[0][0] = s[0];
	M[1][0] = s[1];
	M[2][0] = s[2];
	M[3][0] = 0.0;

	M[0][1] = V[0];
	M[1][1] = V[1];
	M[2][1] = V[2];
	M[3][1] = 0.0;

	M[0][2] = -F[0];
	M[1][2] = -F[1];
	M[2][2] = -F[2];
	M[3][2] = 0.0;

	M[0][3] = 0.0;
	M[1][3] = 0.0;
	M[2][3] = 0.0;
	M[3][3] = 1.0;

	glMultMatrixf(&M[0][0]);
	glTranslated(-eye[0], -eye[1], -eye[2]);
}

#pragma warning(pop)