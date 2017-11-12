//Semestre 2016 - 2
//************************************************************//
//************************************************************//
//************** Alumno (s): *********************************//
//*************	Vázquez Álvarez Ángel Eduardo			******//
//************** Quiñones Rivera Josué Emanuel*			******//
//************************************************************//
#include "texture.h"
#include "figuras.h"
#include "Camera.h"
#include <ctime>

float pos_camX = 0, pos_camY = 0, pos_camZ = -5; 
int eye_camX = 0, eye_camY = 0.0, eye_camZ = 0;

float text_der = 1.0;
float text_izq = 0.0;

GLfloat Diffuse[]= { 0.5f, 0.5f, 0.5f, 1.0f };				// Diffuse Light Values
GLfloat Specular[] = { 1.0, 1.0, 1.0, 1.0 };				// Specular Light Values
GLfloat Position[]= { 0.0f, 3.0f, 0.0f, 1.0f };				// Light Position
GLfloat Position2[]= { 0.0f, -5.0f, 0.0f, 1.0f };			// Light Position

//	Cámara para ver el tablero desde fuera
float g_lookupdown = 0.0f;
CCamera camaraUsuario;


//	Objeto para realizar figuras
CFiguras figures;

//	Texturas
CTexture fondo;
CTexture pared;
CTexture ventana;

void InitGL ( GLvoid )     // Inicializamos parametros
{
	glClearColor(0.5f, 0.5f, 0.8f, 0.0f);				// Azul de fondo	

	glEnable(GL_TEXTURE_2D);

	//glShadeModel (GL_SMOOTH);
	glLightfv(GL_LIGHT0, GL_POSITION, Position);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, Position2);
	

	glClearDepth(1.0f);									// Configuramos Depth Buffer
	glEnable(GL_DEPTH_TEST);							// Habilitamos Depth Testing
	glDepthFunc(GL_LEQUAL);								// Tipo de Depth Testing a realizar
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	//	Procesar imagenes

	fondo.LoadTGA("textures/darksels2.tga");
	fondo.BuildGLTexture();
	fondo.ReleaseImage();

	ventana.LoadTGA("textures/vidrio2.tga");
	ventana.BuildGLTexture();
	ventana.ReleaseImage();

	pared.LoadTGA("textures/darksels.tga");
	pared.BuildGLTexture();
	pared.ReleaseImage();

	//	Posición Cámara
	camaraUsuario.Position_Camera(0, 0, 30, 0, 0, 27, 0, 1, 0);
}


void renderBitmapCharacter(float x, float y, float z, void *font,char *string)
{
  
  char *c;     //Almacena los caracteres a escribir
  glRasterPos3f(x, y, z);	//Posicion apartir del centro de la ventana
  //glWindowPos2i(150,100);
  for (c=string; *c != '\0'; c++) //Condicion de fin de cadena
  {
    glutBitmapCharacter(font, *c); //imprime
  }
}

void cajaPachinko()
{
	glPushMatrix();
	figures.prisma4(30, 30, 6, fondo.GLindex, pared.GLindex, ventana.GLindex);

	glPushMatrix();
	glPopMatrix();

	glPopMatrix();
}

void display ( void )   // Creamos la funcion donde se dibuja
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glLoadIdentity();

	glPushMatrix();	//	1

	glRotatef(g_lookupdown, 1, 0, 0);
	gluLookAt(camaraUsuario.mPos.x, camaraUsuario.mPos.y, camaraUsuario.mPos.z,
		camaraUsuario.mView.x, camaraUsuario.mView.y, camaraUsuario.mView.z,
		camaraUsuario.mUp.x, camaraUsuario.mUp.y, camaraUsuario.mUp.z);
		
		cajaPachinko();

	glPopMatrix();	//	1

	glEnable(GL_TEXTURE_2D);

	glutSwapBuffers ( );

}

void reshape ( int width , int height )   // Creamos funcion Reshape
{
  if (height==0)										// Prevenir division entre cero
	{
		height=1;
	}

	glViewport(0,0,width,height);	

	glMatrixMode(GL_PROJECTION);						// Seleccionamos Projection Matrix
	glLoadIdentity();

	// Tipo de Vista
	
	glFrustum (-0.1, 0.1,-0.1, 0.1, 0.1, 50.0);

	glMatrixMode(GL_MODELVIEW);							// Seleccionamos Modelview Matrix
	glLoadIdentity();
}

void animacion()
{
	text_izq-= 0.01;
	text_der-= 0.01;
	if(text_izq<-1)
		text_izq=0;
	if(text_der<0)
		text_der=1;

	glutPostRedisplay();
}

void keyboard ( unsigned char key, int x, int y )  // Create Keyboard Function
{
	switch ( key ) {
		case 'w':   //Movimientos de camara
		case 'W':
			camaraUsuario.Move_Camera(CAMERASPEED + 0.2);
			//eye_camZ -= 0.5f;
			break;

		case 's':
		case 'S':
			camaraUsuario.Move_Camera(-(CAMERASPEED + 0.2));
			//eye_camZ += 0.5f;
			break;

		case 'a':
		case 'A':
			camaraUsuario.Strafe_Camera(-(CAMERASPEED + 0.4));
			//eye_camX -= 0.5f;
			break;
		case 'd':
		case 'D':
			camaraUsuario.Strafe_Camera(CAMERASPEED + 0.4);
			//eye_camX += 0.5f;
			break;

		case 27:        // Cuando Esc es presionado...
			exit ( 0 );   // Salimos del programa
			break;        
		default:        // Cualquier otra
			break;
  }
	glutPostRedisplay();
}

void arrow_keys ( int a_keys, int x, int y )  // Funcion para manejo de teclas especiales (arrow keys)
{
  switch ( a_keys ) {
	case GLUT_KEY_PAGE_UP:
		camaraUsuario.UpDown_Camera(CAMERASPEED);
		//eye_camY += 0.5f;
		break;

	case GLUT_KEY_PAGE_DOWN:
		camaraUsuario.UpDown_Camera(-CAMERASPEED);
		//eye_camY -= 0.5f;
		break;

    case GLUT_KEY_UP:     // Presionamos tecla ARRIBA...
		g_lookupdown -= 1.0f;
		break;

    case GLUT_KEY_DOWN:               // Presionamos tecla ABAJO...
		g_lookupdown += 1.0f;
		break;

	case GLUT_KEY_LEFT:
		camaraUsuario.Rotate_View(-CAMERASPEED);
		break;

	case GLUT_KEY_RIGHT:
		camaraUsuario.Rotate_View(CAMERASPEED);
		break;
    default:
      break;
  }
  glutPostRedisplay();
}


int main ( int argc, char** argv )   // Main Function
{
  glutInit            (&argc, argv); // Inicializamos OpenGL
  glutInitDisplayMode (GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); // Display Mode (Clores RGB y alpha | Buffer Doble )
  glutInitWindowSize  (500, 500);	// Tamaño de la Ventana
  glutInitWindowPosition (0, 0);	//Posicion de la Ventana
  glutCreateWindow    ("Practica 7"); // Nombre de la Ventana
  //glutFullScreen     ( );         // Full Screen
  InitGL ();						// Parametros iniciales de la aplicacion
  glutDisplayFunc     ( display );  //Indicamos a Glut función de dibujo
  glutReshapeFunc     ( reshape );	//Indicamos a Glut función en caso de cambio de tamano
  glutKeyboardFunc    ( keyboard );	//Indicamos a Glut función de manejo de teclado
  glutSpecialFunc     ( arrow_keys );	//Otras
  glutIdleFunc		  ( animacion );
  glutMainLoop        ( );          // 

  return 0;
}