#include <GL/glut.h>		// Need to include it here because the GL* types are required
#define PI 3.1415265359
#define PIdiv180 3.1415265359/180.0

/////////////////////////////////
//Note: All angles in degrees  //
/////////////////////////////////

struct SF3dVectorTank  //Float 3d-vect, normally used
{
	GLfloat x,y,z;
};
struct SF2dVectorTank
{
	GLfloat x,y;
};

class userTank
{
private:		/*Not used for rendering the camera, but for "moveforwards"
							So it is not necessary to "actualize" it always. It is only
							actualized when ViewDirChanged is true and moveforwards is called*/
	bool ViewDirChanged;
	GLfloat RotatedX, RotatedY, RotatedZ;	
	void GetViewDir ( void );
public:
	SF3dVectorTank Position;
	SF3dVectorTank ViewDir;
	userTank();				//inits the values (Position: (0|0|0) Target: (0|0|-1) )
	double Render(int switchVar);	//executes some glRotates and a glTranslate command
							//Note: You should call glLoadIdentity before using Render
	void Move ( SF3dVectorTank Direction );
	void RotateX ( GLfloat Angle );
	void RotateY ( GLfloat Angle );
	void RotateZ ( GLfloat Angle );
	void RotateXYZ ( SF3dVectorTank Angles );
	void MoveForwards ( GLfloat Distance );
	/*void setLastPos();
	void setLastDir();*/
};


SF3dVectorTank F3dVectorTank ( GLfloat x, GLfloat y, GLfloat z );
SF3dVectorTank AddF3dVectors ( SF3dVectorTank * u, SF3dVectorTank * v);
void AddF3dVectorToVector ( SF3dVectorTank * Dst, SF3dVectorTank * V2);
