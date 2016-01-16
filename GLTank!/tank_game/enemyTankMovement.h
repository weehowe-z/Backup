#include <GL/glut.h>		// Need to include it here because the GL* types are required
#define PI 3.1415265359
#define PIdiv180 3.1415265359/180.0

/////////////////////////////////
//Note: All angles in degrees  //
/////////////////////////////////

struct SF3dVectorEnemyTank  //Float 3d-vect, normally used
{
	GLfloat x,y,z;
};
struct SF2dVectorEnemyTank
{
	GLfloat x,y;
};

class enemyTankMovement
{
private:		/*Not used for rendering the camera, but for "moveforwards"
							So it is not necessary to "actualize" it always. It is only
							actualized when ViewDirChanged is true and moveforwards is called*/
	bool ViewDirChanged;
	GLfloat RotatedX, RotatedY, RotatedZ;	
	void GetViewDir ( void );
public:
	SF3dVectorEnemyTank Position;
	SF3dVectorEnemyTank ViewDir;
	enemyTankMovement();				//inits the values (Position: (0|0|0) Target: (0|0|-1) )
	double Render(int switchVar);	//executes some glRotates and a glTranslate command
							//Note: You should call glLoadIdentity before using Render
	void Move ( SF3dVectorEnemyTank Direction );
	void RotateX ( GLfloat Angle );
	void RotateY ( GLfloat Angle );
	void RotateZ ( GLfloat Angle );
	void RotateXYZ ( SF3dVectorEnemyTank Angles );
	void MoveForwards ( GLfloat Distance );
};


SF3dVectorEnemyTank F3dVectorEnemyTank ( GLfloat x, GLfloat y, GLfloat z );
SF3dVectorEnemyTank AddF3dVectors ( SF3dVectorEnemyTank * u, SF3dVectorEnemyTank * v);
void AddF3dVectorToVector ( SF3dVectorEnemyTank * Dst, SF3dVectorEnemyTank * V2);
