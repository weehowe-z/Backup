#include <cmath>
#include <iostream>
#include "windows.h"
#include "enemyTankMovement.h"

SF3dVectorEnemyTank F3dVector ( GLfloat x, GLfloat y, GLfloat z )
{
	SF3dVectorEnemyTank tmp;
	tmp.x = x;
	tmp.y = y;
	tmp.z = z;
	return tmp;
}
SF3dVectorEnemyTank AddF3dVectors (SF3dVectorEnemyTank* u, SF3dVectorEnemyTank* v)
{
	SF3dVectorEnemyTank result;
	result.x = u->x + v->x;
	result.y = u->y + v->y;
	result.z = u->z + v->z;
	return result;
}
void AddF3dVectorToVector ( SF3dVectorEnemyTank * Dst, SF3dVectorEnemyTank * V2)
{
	Dst->x += V2->x;
	Dst->y += V2->y;
	Dst->z += V2->z;
}


/***************************************************************************************/

enemyTankMovement::enemyTankMovement()
{
	//Init with standard OGL values:
	Position = F3dVector (	0.0, 
							0.0,
							0.0);
	ViewDir = F3dVector(	0.0,
							0.0,
							-1.0);
	ViewDirChanged = false;
	//Only to be sure:
	RotatedX = 0.0;
	RotatedY = 0.0;
	RotatedZ = 0.0;
}

void enemyTankMovement::GetViewDir( void )
{
	SF3dVectorEnemyTank Step1, Step2;
	//Rotate around Y-axis:
	Step1.x = cos( (RotatedY + 90.0) * PIdiv180);
	Step1.z = -sin( (RotatedY + 90.0) * PIdiv180);
	//Rotate around X-axis:
	double cosX = cos (RotatedX * PIdiv180);
	Step2.x = Step1.x * cosX;
	Step2.z = Step1.z * cosX;
	Step2.y = sin(RotatedX * PIdiv180);
	//Rotation around Z-axis not yet implemented, so:
	ViewDir = Step2;
}
void enemyTankMovement::Move (SF3dVectorEnemyTank Direction)
{
	AddF3dVectorToVector(&Position, &Direction );
}

void enemyTankMovement::RotateY (GLfloat Angle)
{
	RotatedY += Angle;
	ViewDirChanged = true;
}

void enemyTankMovement::RotateX (GLfloat Angle)
{
	RotatedX += Angle;
	ViewDirChanged = true;
}


double enemyTankMovement::Render(int switchVar)
{
	if(switchVar==0) 
		return RotatedX;
	if(switchVar==1) 
		return RotatedY;
	if(switchVar==2) 
		return RotatedZ;
	if(switchVar==3) 
		return Position.x;
	if(switchVar==4) 
		return Position.y;
	if(switchVar==5) 
		return Position.z;
}

void enemyTankMovement::MoveForwards( GLfloat Distance )
{
	if (ViewDirChanged) GetViewDir();
	SF3dVectorEnemyTank MoveVector;

	MoveVector.x = ViewDir.x * -Distance;
	MoveVector.y = ViewDir.y * -Distance;
	MoveVector.z = ViewDir.z * -Distance;

	AddF3dVectorToVector(&Position, &MoveVector );
}
