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
#include "cmodel\CModel.h"
#include <ctime>

float pos_camX = 0, pos_camY = 0, pos_camZ = -5; 
int eye_camX = 0, eye_camY = 0.0, eye_camZ = 0;

float text_der = 1.0;
float text_izq = 0.0;

GLfloat Diffuse[]= { 0.5, 0.5, 0.5, 1.0f };				// Diffuse Light Values
GLfloat Specular[] = { 0.0, 0.0, 0.0, 1.0 };				// Specular Light Values
//GLfloat Position[]= { 0, 0, 10, 1.0f };				// Light Position
//GLfloat Position2[]= { 0, 0, 0, 1.0f };			// Light Position
GLfloat Position[]= { 0.0f, 3.0f, 3.0f, 1.0f };				// Light Position
GLfloat Position2[]= { 0.0f, -5.0f, 0.0f, 1.0f };			// Light Position


//	Cámara para ver el tablero desde fuera
float g_lookupdown = 0.0f;
CCamera camaraUsuario;


//	Objeto para realizar figuras
CFiguras figures;

//	Objeto para modelos 3ds
CModel clavo;
CModel escudo;

//	Texturas
CTexture fondo;
CTexture pared;
CTexture ventana;
CTexture rojo;

//	Material (cromeo) 
//chrome	0.25	0.25	0.25	0.4	0.4	0.4	0.774597	0.774597	0.774597	0.6
GLfloat cromo_ambient[] = {0.25, 0.25, 0.25, 1.0};
GLfloat cromo_diffuse[] = {0.4, 0.4, 0.4, 1.0};
GLfloat cromo_specular[] = {0.774597, 0.774597, 0.774597, 1.0};
GLfloat cromo_shininess = 0.6;

//	ruby 0.1745	0.01175	0.01175	0.61424	0.04136	0.04136	0.727811	0.626959	0.626959	0.6
GLfloat ruby_ambient[] = {0.1745,	0.01175,	0.01175, 1.0};
GLfloat ruby_diffuse[] = {0.61424,	0.04136,	0.04136, 1.0};
GLfloat ruby_specular[] = {0.727811,	0.626959,	0.626959, 1.0};
GLfloat ruby_shininess = 0.6;

//	temp
float xx = 0.f;
float yy = 0.f;
float zz = 0.f;
float zzz = 0.f;

void InitGL ( GLvoid )     // Inicializamos parametros
{
	glClearColor(0.5f, 0.5f, 0.8f, 0.0f);				// Azul de fondo	

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_TEXTURE_2D);

	glShadeModel (GL_SMOOTH);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, Diffuse);
	//glLightfv(GL_LIGHT0, GL_AMBIENT, Diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, Specular);
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

	rojo.LoadTGA("textures/red.tga");
	rojo.BuildGLTexture();
	rojo.ReleaseImage();

	//	Cargar modelos 3ds
	clavo._3dsLoad("models/nail.3ds");
	escudo._3dsLoad("models/shield.3ds");
	//escudo.LoadTextureImages();
	//escudo.GLIniTextures();
	escudo.VertexNormals();
	//escudo.ReleaseTextureImages();
	escudo.FlipNormals();

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

		glPushMatrix();
			glTranslatef(-11.5, -15, 0);
			glPushMatrix();
				glTranslatef(-0.05, 14.6, 0);
				glRotatef(25, 0, 0, -1);
				glMaterialfv(GL_FRONT, GL_AMBIENT, cromo_ambient);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, cromo_diffuse);
				glMaterialfv(GL_FRONT, GL_SPECULAR, cromo_specular);
				glMaterialf(GL_FRONT, GL_SHININESS, cromo_shininess * 128.0);
				figures.cilindro(1, 5, 30, 0);
			glPopMatrix();
			figures.cilindro(1, 15, 30, 0);
		glPopMatrix();

		glPushMatrix();	//	Circunferencia
			glTranslatef(0, 0, -2.5);
			glRotatef(90, 1, 0, 0);
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ruby_ambient);
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, ruby_diffuse);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, ruby_specular);
			glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, ruby_shininess * 128.0);
			figures.cilindro(11, 5, 30, 0);
		glPopMatrix();	//	Circunferencia

		glPushMatrix();	//	Bandeja
			glTranslatef(-10, -14.5, 8.01);

			glPushMatrix();	//	Botón
				glTranslatef(6.01, 0, 0);
				glRotatef(90, 0, 0, 1);
				glEnable(GL_COLOR_MATERIAL);
				glColor3f(0.4578, 0, 0);
				figures.boton(1, 1, 10, 0);
				glColor3f(1, 1, 1);
				glDisable(GL_COLOR_MATERIAL);
			glPopMatrix();	//	Botón



			figures.bandeja(3.5, 10, 10, pared.GLindex);
		glPopMatrix();	//	Bandeja

		figures.prisma4(30, 30, 6, fondo.GLindex, pared.GLindex, ventana.GLindex);

	glPopMatrix();
}

void perro() {

	glPushMatrix();

	glTranslatef(-3, -1.75, 0);
			glPushMatrix();
				glScalef(6.0, 3.5, 1.0);
				figures.prismaJerarquico(0, 0);	// A
			glPopMatrix();

			glPushMatrix();
				glTranslatef(0.75, 0, 0);
				glRotatef(0.0, 0.0, 0.0, 1.0);
				glTranslatef(-0.75, -4.0, 0);
				glScalef(1.5, 4, 1.0);
				//glColor3f(1.0, 0.0, 0.0);
				figures.prismaJerarquico(0, 0);		// E
			glPopMatrix();

			glPushMatrix();
				glTranslatef(5.25, 0, 0);
				glRotatef(0.0, 0.0, 0.0, 1.0);
				glTranslatef(-0.75, -4.0, 0);
				glScalef(1.5, 4, 1.0);
				//glColor3f(1.0, 1.0, 0.0);
				figures.prismaJerarquico(0, 0);		// F
			glPopMatrix();


			glPushMatrix();
				glTranslatef(0, 3.25, 0);
				glRotatef(0.0, 0, 0, 1);
				glTranslatef(-3, -0.25, 0);
				glScalef(3, 0.5, 1);
				//glColor3f(0.0, 1.0, 0.0);
				figures.prismaJerarquico(0, 0);		// G
			glPopMatrix();

			glPushMatrix();
				glTranslatef(4, 3.5, 0);
				glPushMatrix();
					glScalef(2, 3, 1);
					//glColor3f(0, 0, 1);
					figures.prismaJerarquico(0, 0);	//B
				glPopMatrix();

				glPushMatrix();
					glTranslatef(2, 0.5, 0);
					glScalef(1.5, 0.5, 1);
					//glColor3f(0, 1, 1);
					figures.prismaJerarquico(0, 0);	//D
				glPopMatrix();

				glPushMatrix();
					glTranslatef(0, 3, 0);
					glScalef(0.5, 1.5, 1);
					//glColor3f(1, 1, 1);
					figures.prismaJerarquico(0, 0);	//C
				glPopMatrix();
			glPopMatrix();

	glPopMatrix();
}

void obstaculos()
{
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(0, 1, 1);
	for(int i = 0; i < 4; i++)
	{ 
		glPushMatrix();
			glTranslatef(-8 + i * 2, 5, -2.99);
			glRotatef(90, 1, 0, 0);
			glScalef(2, 2, 2);
			clavo.GLrender(NULL, _SHADED, 1.0);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(8 - i * 2, 5, -2.99);
			glRotatef(90, 1, 0, 0);
			glScalef(2, 2, 2);
			clavo.GLrender(NULL, _SHADED, 1.0);
		glPopMatrix();
	}

	for(int i = 0; i < 4; i++)
	{ 
		glPushMatrix();
			glTranslatef(-8.5 + i * 2, 3.5, -2.99);
			glRotatef(90, 1, 0, 0);
			glScalef(2, 2, 2);
			clavo.GLrender(NULL, _SHADED, 1.0);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(8.5 - i * 2, 3.5, -2.99);
			glRotatef(90, 1, 0, 0);
			glScalef(2, 2, 2);
			clavo.GLrender(NULL, _SHADED, 1.0);
		glPopMatrix();
	}

	for(int i = 0; i < 4; i++)
	{ 
		glPushMatrix();
			glTranslatef(-8 + i * 2, 2, -2.99);
			glRotatef(90, 1, 0, 0);
			glScalef(2, 2, 2);
			clavo.GLrender(NULL, _SHADED, 1.0);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(8 - i * 2, 2, -2.99);
			glRotatef(90, 1, 0, 0);
			glScalef(2, 2, 2);
			clavo.GLrender(NULL, _SHADED, 1.0);
		glPopMatrix();
	}

	glDisable(GL_COLOR_MATERIAL);
	glColor3f(1, 1, 1);
}

void jackpots()
{
	//glDisable(GL_LIGHT0);
	glColor3f(0.5, 0.5, 0.5);
	glEnable(GL_COLOR_MATERIAL);
	glPushMatrix();
		
		glTranslatef(0, 0, 0);
		//glRotatef(90, 0, 1, 0);
		glScalef(0.03, 0.03, 0.03);
		escudo.GLrender(NULL, _SHADED, 1.0);

	glPopMatrix();
	glDisable(GL_COLOR_MATERIAL);
	glColor3f(1, 1, 1);
	//glEnable(GL_LIGHT0);
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
		
		glPushMatrix();
			glTranslatef(xx, yy, zz);
			figures.esfera(zzz, 30, 30, 0);

		glPopMatrix();
		
		jackpots();
		obstaculos();
		perro();
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

		case 'p':
			yy += 0.1;
			break;

		case 'P':
			yy -= 0.1;
			break;

		case 'o':
			xx += 0.1;
			break;

		case 'O':
			xx -= 0.1;
			break;

		case 'i':
			zz += 0.1;
			break;

		case 'I':
			zz -= 0.1;
			break;

		case 'u':
			zzz += 0.1;
			break;

		case 'U':
			zzz -= 0.1;
			break;

		case 'l':
			printf("(%f, %f, -2.99)\n", xx, yy);
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