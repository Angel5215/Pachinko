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
#define _MAX_FRAMES_ 200

//	Para la animación por keyframes
struct Frame {
	
};


//float pos_camX = 0, pos_camY = 0, pos_camZ = -5; 
//int eye_camX = 0, eye_camY = 0.0, eye_camZ = 0;



float text_der = 1.0;
float text_izq = 0.0;

//Activacion de luces
bool luz1 = true;
bool luz2 = false;
bool luz3 = false;
bool luz4 = false;

GLfloat Ambient[]= { 0.3, 0.3, 0.3, 1.0f };	
GLfloat Diffuse[]= { 0.85, 0.85, 0.85, 1.0f };	// Diffuse Light Values
GLfloat Specular[] = { 0.85, 0.85, 0.85, 1.0 };				// Specular Light Values
GLfloat Position[]= { -10, 10, 2, 0.0f };				// Light Position
//GLfloat Position2[]= { 0, 0, 0, 1.0f };			// Light Position
//GLfloat Position[]= { 0.0f, 0.0f, 3.0f, 0.0f };				// Light Position
//GLfloat Position2[]= { 0.0f, -5.0f, 0.0f, 1.0f };			// Light Position

GLfloat Ambient2[]= { 0.2, 0.2, 0.2, 1.0f };	
GLfloat Diffuse2[]= { 0.7, 0.7, 0.0, 1.0f };	// Diffuse Light Values
GLfloat Specular2[] = { 0.7, 0.7, 0.7, 1.0 };				// Specular Light Values
GLfloat Position2[]= { 0, 0, 5, 1.0f };				// Light Position

//	Posición de la luz 4
GLfloat Ambient4[]= { 0.23, 0.23, 0.23, 1.0f };	
GLfloat Diffuse4[]= { 0.5, 0.f, 0.7, 1.0f };	// Diffuse Light Values
GLfloat Specular4[] = { 0.7, 0.7, 0.7, 1.0 };				// Specular Light Values
GLfloat Position4[]= { 0, 0, 0, 1.0f };				// Light Position


//	Cámara para ver el tablero desde fuera
float g_lookupdown = 0.0f;
CCamera camaraUsuario;

//	Posición de la canica metálica y su cámara
CCamera camaraCanica;
float c_posX = 0.f;
float c_posY = 0.f;
float c_posZ = 0.f;
float c_lookupdown = 0.f;
float c_lookrightleft = 0.f;
bool isBallCameraEnabled = false;

GLfloat Ambient3[]= { 0.2, 0.2, 0.2, 1.0f };	
GLfloat Diffuse3[]= { 0.0, 0.0, 0.85, 1.0f };	// Diffuse Light Values
GLfloat Specular3[] = { 0.85, 0.85, 0.85, 1.0 };				// Specular Light Values
GLfloat Position3[]= { c_posX, c_posY, c_posZ, 1.0f };	


//	Objeto para realizar figuras
CFiguras figures;

//	Objeto para modelos 3ds
CModel clavo;
CModel escudo;
CModel cofre;

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

//sapphire
GLfloat sapphire_ambient[] = {0.0215,	0.1745,	0.0215, 1.0};
GLfloat sapphire_diffuse[] = {0.07568,	0.61424, 0.07568, 1.0};
GLfloat sapphire_specular[] = {0.633,	0.727811,	0.633, 1.0};
GLfloat sapphire_shininess = 0.6;

//gold 0.24725	0.1995	0.0745	0.75164	0.60648	0.22648	0.628281	
//	0.555802	0.366065	0.4
GLfloat gold_ambient[] = {0.0215,	0.1745,	0.0215, 1.0};//{0.05375,	0.05,	0.06625, 1.0};
GLfloat gold_diffuse[] = {0.07568,	0.61424, 0.07568, 1.0};//{0.18275,	0.17,	0.22525, 1.0};
GLfloat gold_specular[] = {0.633,	0.727811,	0.633, 1.0};//{0.332741,	0.328634,	0.346435, 1.0};
GLfloat gold_shininess = 0.6;

// Material plata
GLfloat silver_ambient[] = {0.19225, 0.19225, 0.19225, 1.0};//{0.05375,	0.05,	0.06625, 1.0};
GLfloat silver_diffuse[] = {0.50754, 0.50754, 0.50754, 1.0};//{0.18275,	0.17,	0.22525, 1.0};
GLfloat silver_specular[] = {0.508273, 0.508273, 0.508273, 1.0};//{0.332741,	0.328634,	0.346435, 1.0};
GLfloat silver_shininess = 0.4;

//		0.3

//	temp
float xx = 0.f;
float yy = 0.f;
float zz = 0.f;
float zzz = 0.f;

void InitGL ( GLvoid )     // Inicializamos parametros
{
	glClearColor(0.5f, 0.5f, 0.8f, 0.0f);				// Azul de fondo	

	//glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);
	//glEnable(GL_LIGHT1);
	glEnable(GL_TEXTURE_2D);

	glShadeModel (GL_SMOOTH);
	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, Diffuse);
	glLightfv(GL_LIGHT1, GL_AMBIENT, Ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, Specular);
	glLightfv(GL_LIGHT1, GL_POSITION, Position);
	//glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, Position2);
	
	glLightfv(GL_LIGHT2, GL_AMBIENT, Ambient2);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, Diffuse2);
	glLightfv(GL_LIGHT2, GL_SPECULAR, Specular2);
	glLightfv(GL_LIGHT2, GL_POSITION, Position2);

	glLightfv(GL_LIGHT3, GL_AMBIENT, Ambient3);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, Diffuse3);
	glLightfv(GL_LIGHT3, GL_SPECULAR, Specular3);
	glLightfv(GL_LIGHT3, GL_POSITION, Position3);

	//	Luz ligada a keyframes
	glLightfv(GL_LIGHT4, GL_AMBIENT, Ambient4);
	glLightfv(GL_LIGHT4, GL_DIFFUSE, Diffuse4);
	glLightfv(GL_LIGHT4, GL_SPECULAR, Specular4);
	glLightfv(GL_LIGHT4, GL_POSITION, Position4);


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
	escudo._3dsLoad("models/escudo.3ds");
	cofre._3dsLoad("models/chest.3ds");
	//COLOR plata = {0.5, 0.5, 0.5, 1.0};
	//CMaterial *material = new CMaterial;
	//material->SetDiffuse(plata);
	//escudo.MaterialList.InsertFirst(material);
	//escudo.LoadTextureImages();
	//escudo.GLIniTextures();
	escudo.VertexNormals();
	cofre.VertexNormals();
	//escudo.ReleaseTextureImages();
	//escudo.FlipNormals();

	//	Posición Cámara
	camaraUsuario.Position_Camera(0, 0, 30, 0, 0, 27, 0, 1, 0);
	camaraCanica.Position_Camera(c_posX + 2.5, c_posY + 2.5, c_posZ,
								c_posX, c_posY, c_posZ, 0, 1, 0);
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

	if(luz1){
		glEnable(GL_LIGHT1);
	}
	else {
		glDisable(GL_LIGHT1);
	}

	if(luz2){
		glEnable(GL_LIGHT2);
	}
	else {
		glDisable(GL_LIGHT2);
	}

	if(luz3){
		glEnable(GL_LIGHT3);
	}
	else {
		glDisable(GL_LIGHT3);
	}

	if(luz4){
		glEnable(GL_LIGHT4);
	}
	else {
		glDisable(GL_LIGHT4);
	}

	glPushMatrix();
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(1,1,1);
	glTranslatef(Position[0],Position[1],Position[2]);
	figures.esfera(1,20,20,0);
	glDisable(GL_COLOR_MATERIAL);
	glPopMatrix();

		glPushMatrix();
			glTranslatef(-11.5, -5, 0);
			glPushMatrix();
			glRotatef(-130,0,0,1);
			glRotatef(180,0,1,0);
			figures.canal(1,7,30,0);
			glPopMatrix();

			glPushMatrix(); //canal
				glTranslatef(-0.05, 4.6, 0);
				glRotatef(25, 0, 0, -1);
				glMaterialfv(GL_FRONT, GL_AMBIENT, cromo_ambient);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, cromo_diffuse);
				glMaterialfv(GL_FRONT, GL_SPECULAR, cromo_specular);
				glMaterialf(GL_FRONT, GL_SHININESS, cromo_shininess * 128.0);
				glRotatef(180,0,1,0);
				figures.canal(1, 5, 30, 0);
			glPopMatrix(); // canal
			glRotatef(180,0,1,0);
			figures.canal(1, 5, 30, 0);

			
		glPopMatrix();

		glPushMatrix();	//	Circunferencia
			glTranslatef(0, 0, -2.5);
			glRotatef(90, 1, 0, 0);
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ruby_ambient);
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, ruby_diffuse);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, ruby_specular);
			glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, ruby_shininess * 128.0);
			figures.cilindro(11, 5, 80, 0);
		glPopMatrix();	//	Circunferencia

		glPushMatrix();	//	Bandeja
			glTranslatef(-10, -14.5, 8.01);

			glPushMatrix();	//	Botón
				//glTranslatef(25.9, 2.3, -6.6);
				glTranslatef(18.3, 0.7, -5);
				glRotatef(90, 1, 0, 0);
				glEnable(GL_COLOR_MATERIAL);
				glColor3f(0.4578, 0, 0);
				figures.boton(0.8, 1, 10, 0);
				glColor3f(1, 1, 1);
				glDisable(GL_COLOR_MATERIAL);
			glPopMatrix();	//	Botón



			figures.bandeja(3.5, 10, 10, pared.GLindex);
		glPopMatrix();	//	Bandeja

		figures.prisma4(30, 30, 6, fondo.GLindex, pared.GLindex, ventana.GLindex);

	glPopMatrix();
}

void corona()
{
	glPushMatrix();
		glScalef(0.7, 0.7, 0.7);
		glTranslatef(0, -5, 0);
		glPushMatrix();
			glScalef(4, 3, 3);
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, gold_ambient);
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, gold_diffuse);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, gold_specular);
			glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, gold_shininess * 128.0);
			figures.prisma2(0, 0);
		glPopMatrix();


		//	Parte delantera
		glPushMatrix();
			glTranslatef(0, 1.5, 1);
			glPushMatrix();
				glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, gold_ambient);
				glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, gold_diffuse);
				glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, gold_specular);
				glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, gold_shininess * 128.0);
				figures.cono(2, 0.5, 5, 0);

				glPushMatrix();
					glTranslatef(0, 2.2, 0);
					glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ruby_ambient);
					glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, ruby_diffuse);
					glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, ruby_specular);
					glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, ruby_shininess * 128.0);
					figures.esfera(0.25, 5, 5, 0);
				glPopMatrix();
			glPopMatrix();
			
			glPushMatrix();
				glTranslatef(-1.75, 0, 0.25);
				glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, gold_ambient);
				glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, gold_diffuse);
				glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, gold_specular);
				glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, gold_shininess * 128.0);
				figures.cono(1.5, 0.25, 5, 0);

				glPushMatrix();
					glTranslatef(0, 1.7, 0);
					glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ruby_ambient);
					glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, ruby_diffuse);
					glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, ruby_specular);
					glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, ruby_shininess * 128.0);
					figures.esfera(0.25, 5, 5, 0);
				glPopMatrix();

			glPopMatrix();

			glPushMatrix();
				glTranslatef(1.75, 0, 0.25);
				glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, gold_ambient);
				glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, gold_diffuse);
				glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, gold_specular);
				glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, gold_shininess * 128.0);
				figures.cono(1.5, 0.25, 5, 0);

				glPushMatrix();
					glTranslatef(0, 1.7, 0);
					glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ruby_ambient);
					glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, ruby_diffuse);
					glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, ruby_specular);
					glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, ruby_shininess * 128.0);
					figures.esfera(0.25, 5, 5, 0);
				glPopMatrix();

			glPopMatrix();
		glPopMatrix();


		//	Parte trasera
		glPushMatrix();
			glTranslatef(0, 1.5, -1);
			glPushMatrix();
				glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, gold_ambient);
				glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, gold_diffuse);
				glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, gold_specular);
				glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, gold_shininess * 128.0);
				figures.cono(2, 0.5, 5, 0);

				glPushMatrix();
					glTranslatef(0, 2.2, 0);
					glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ruby_ambient);
					glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, ruby_diffuse);
					glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, ruby_specular);
					glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, ruby_shininess * 128.0);
					figures.esfera(0.25, 5, 5, 0);
				glPopMatrix();

			glPopMatrix();
			
			glPushMatrix();
				glTranslatef(-1.75, 0, -0.25);
				glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, gold_ambient);
				glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, gold_diffuse);
				glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, gold_specular);
				glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, gold_shininess * 128.0);
				figures.cono(1.5, 0.25, 5, 0);

				glPushMatrix();
					glTranslatef(0, 1.7, 0);
					glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ruby_ambient);
					glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, ruby_diffuse);
					glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, ruby_specular);
					glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, ruby_shininess * 128.0);
					figures.esfera(0.25, 5, 5, 0);
				glPopMatrix();

			glPopMatrix();

			glPushMatrix();
				glTranslatef(1.75, 0, -0.25);
				glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, gold_ambient);
				glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, gold_diffuse);
				glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, gold_specular);
				glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, gold_shininess * 128.0);
				figures.cono(1.5, 0.25, 5, 0);

				glPushMatrix();
					glTranslatef(0, 1.7, 0);
					glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ruby_ambient);
					glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, ruby_diffuse);
					glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, ruby_specular);
					glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, ruby_shininess * 128.0);
					figures.esfera(0.25, 5, 5, 0);
				glPopMatrix();

			glPopMatrix();
		glPopMatrix();



	glPopMatrix();
}

void perro() {

	glPushMatrix();
	glScalef(0.65,0.65,0.65);
	glTranslatef(-3, -2, -4.5);

		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, sapphire_ambient);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, sapphire_diffuse);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, sapphire_specular);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, sapphire_shininess * 128.0);
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
	for(int i = 0; i < 6; i++)
	{ 
		glPushMatrix();
			glTranslatef(-11 + i * 1.7, 7.0, -4.51);
			glRotatef(90, 1, 0, 0);
			glScalef(2, 2, 2);
			clavo.GLrender(NULL, _SHADED, 1.0);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(11 - i * 1.7, 7.0, -4.51);
			glRotatef(90, 1, 0, 0);
			glScalef(2, 2, 2);
			clavo.GLrender(NULL, _SHADED, 1.0);
		glPopMatrix();
	}

	for(int i = 0; i < 5; i++)
	{ 
		glPushMatrix();
			glTranslatef(-10+ i * 2, 5.5, -4.51);
			glRotatef(90, 1, 0, 0);
			glScalef(2, 2, 2);
			clavo.GLrender(NULL, _SHADED, 1.0);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(10 - i * 2, 5.5, -4.51);
			glRotatef(90, 1, 0, 0);
			glScalef(2, 2, 2);
			clavo.GLrender(NULL, _SHADED, 1.0);
		glPopMatrix();
	}

	for(int i = 0; i < 4; i++)
	{ 
		glPushMatrix();
			glTranslatef(-11 + i * 2, 4.0, -4.51);
			glRotatef(90, 1, 0, 0);
			glScalef(2, 2, 2);
			clavo.GLrender(NULL, _SHADED, 1.0);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(11 - i * 2, 4.0, -4.51);
			glRotatef(90, 1, 0, 0);
			glScalef(2, 2, 2);
			clavo.GLrender(NULL, _SHADED, 1.0);
		glPopMatrix();
	}

	for(int i = 0; i < 3; i++)
	{ 
		glPushMatrix();
		glTranslatef(-8 + i * 2, 2.5, -4.51);
		glRotatef(90, 1, 0, 0);
		glScalef(2, 2, 2);
		clavo.GLrender(NULL, _SHADED, 1.0);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(8 - i * 2, 2.5, -4.51);
		glRotatef(90, 1, 0, 0);
		glScalef(2, 2, 2);
		clavo.GLrender(NULL, _SHADED, 1.0);
		glPopMatrix();
	}

	

	//Tornillos centrales superiores

	for (int i = 0; i <= 15; i++){
		const double PI = 3.1415926535897;
		const double angulo = PI / (2 * 15);
		const double radio = 3;
		glPushMatrix();
			glTranslatef(-5 + radio * cos(i * angulo), 9 + radio * sin(i * angulo), -4.51);
			glRotatef(90, 1, 0, 0);
			glScalef(2, 2, 2);
			clavo.GLrender(NULL, _SHADED, 1.0);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(5 + radio * cos(PI / 2 + i * angulo), 9 + radio * sin(PI / 2 + i * angulo), -4.51);
			glRotatef(90, 1, 0, 0);
			glScalef(2, 2, 2);
			clavo.GLrender(NULL, _SHADED, 1.0);
		glPopMatrix();
	}
	/*for(int i = 0, j = 0; i < 8, j < 8; i++, j++){ 
		glPushMatrix();
			//glTranslatef(-8 + i * 0.5, 12.0 - j * 0.5, -2.99);
			glTranslatef(-5 + 3 * cos(i), )
			glRotatef(90, 1, 0, 0);
			glScalef(2, 2, 2);
			clavo.GLrender(NULL, _SHADED, 1.0);
		glPopMatrix();

		glPushMatrix();
			//glTranslatef(8 - i * 0.5, 12.0 - j * 0.5, -2.99);
			glRotatef(90, 1, 0, 0);
			glScalef(2, 2, 2);
			clavo.GLrender(NULL, _SHADED, 1.0);
		glPopMatrix();
	}*/

	//Tornillos jackpot (izq)
	for(int i = 0, j = 0; i < 8, j < 8; i++, j++){ 
		glPushMatrix();
		glTranslatef(-15.0 + i * 0.2, 0.9 -j * 0.2, -4.51);
		glRotatef(90, 1, 0, 0);
		glScalef(2, 2, 2);
		clavo.GLrender(NULL, _SHADED, 1.0);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(15.0 - i * 0.2, 0.9 -j * 0.2, -4.51);
		glRotatef(90, 1, 0, 0);
		glScalef(2, 2, 2);
		clavo.GLrender(NULL, _SHADED, 1.0);
		glPopMatrix();
	}
	//Tornillos jackpot (der)
	for(int i = 0, j = 0; i < 8, j < 8; i++, j++){ 
		glPushMatrix();
		glTranslatef(-10.0 - i * 0.2, 0.9 -j * 0.2, -4.51);
		glRotatef(90, 1, 0, 0);
		glScalef(2, 2, 2);
		clavo.GLrender(NULL, _SHADED, 1.0);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(10.0 + i * 0.2, 0.9 -j * 0.2, -4.51);
		glRotatef(90, 1, 0, 0);
		glScalef(2, 2, 2);
		clavo.GLrender(NULL, _SHADED, 1.0);
		glPopMatrix();
	}

	//Tornillos para coronas  inferiores.
	for(int i = 0; i < 5; i++)
	{ 
		glPushMatrix();
		glTranslatef(-13.5 + i * 2, -5.8, -4.51);
		glRotatef(90, 1, 0, 0);
		glScalef(2, 2, 2);
		clavo.GLrender(NULL, _SHADED, 1.0);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(13.5 - i * 2, -5.8, -4.51);
		glRotatef(90, 1, 0, 0);
		glScalef(2, 2, 2);
		clavo.GLrender(NULL, _SHADED, 1.0);
		glPopMatrix();
	}

	for(int i = 0; i < 5; i++)
	{ 
		glPushMatrix();
		glTranslatef(-14.5 + i * 2, -7.3, -4.51);
		glRotatef(90, 1, 0, 0);
		glScalef(2, 2, 2);
		clavo.GLrender(NULL, _SHADED, 1.0);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(14.5 - i * 2, -7.3, -4.51);
		glRotatef(90, 1, 0, 0);
		glScalef(2, 2, 2);
		clavo.GLrender(NULL, _SHADED, 1.0);
		glPopMatrix();
	}

	for(int i = 0; i < 5; i++)
	{ 
		glPushMatrix();
		glTranslatef(-13.5 + i * 2, -8.8, -4.51);
		glRotatef(90, 1, 0, 0);
		glScalef(2, 2, 2);
		clavo.GLrender(NULL, _SHADED, 1.0);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(13.5 - i * 2, -8.8, -4.51);
		glRotatef(90, 1, 0, 0);
		glScalef(2, 2, 2);
		clavo.GLrender(NULL, _SHADED, 1.0);
		glPopMatrix();
	}

	//Tornillo de pruebas
	/*glPushMatrix();
	glTranslatef(xx,yy,-4.51);
	glRotatef(90, 1, 0, 0);
	glScalef(2, 2, 2);
	clavo.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();*/


	//Tornillos verticales
	for(int i = 0; i < 8; i++)
	{ 
		glPushMatrix();
		glTranslatef(-3.5, -4.8 - i * 0.5, -4.51);
		glRotatef(90, 1, 0, 0);
		glScalef(2, 2, 2);
		clavo.GLrender(NULL, _SHADED, 1.0);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(3.5, -4.8 - i * 0.5, -4.51);
		glRotatef(90, 1, 0, 0);
		glScalef(2, 2, 2);
		clavo.GLrender(NULL, _SHADED, 1.0);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-1.5, -4.8 - i * 0.5, -4.51);
		glRotatef(90, 1, 0, 0);
		glScalef(2, 2, 2);
		clavo.GLrender(NULL, _SHADED, 1.0);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(1.5, -4.8 - i * 0.5, -4.51);
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
	glColor3f(1, 1, 0.5);
	glEnable(GL_COLOR_MATERIAL);
	glPushMatrix();
		
		glTranslatef(-12.5,-3.1,-3.6);
		glRotatef(75, 0, 1, 0);
		//glScalef(0.03, 0.03, 0.03);
		glScalef(0.3, 0.3, 0.3);
		escudo.GLrender(NULL, _SHADED, 1);

	glPopMatrix();

	glPushMatrix();

	glTranslatef(12.5,-3.1,-3.6);
	glRotatef(75, 0, 1, 0);
	//glScalef(0.03, 0.03, 0.03);
	glScalef(0.3, 0.3, 0.3);
	escudo.GLrender(NULL, _SHADED, 1);

	glPopMatrix();
	glColor3f(0, 0, 1);
	glPushMatrix();
		glTranslatef(-2.5, -12.7, -1.8);
		glRotatef(90, 1, 0, 0);
		glScalef(0.01, 0.01, 0.01);
		cofre.GLrender(&cofre.center, _SHADED, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2.5, -12.7, -1.8);
	glRotatef(90, 1, 0, 0);
	glScalef(0.01, 0.01, 0.01);
	cofre.GLrender(&cofre.center, _SHADED, 1);
	glPopMatrix();

	glDisable(GL_COLOR_MATERIAL);
	glColor3f(1, 1, 1);
	//glEnable(GL_LIGHT0);
}

void entradas(){

	glPushMatrix();
	glTranslatef(-7,1.1,-3.1);
	corona();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(7,1.1,-3.1);
	corona();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-7.1,-9,-3.1);
	corona();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(7.1,-9,-3.1);
	corona();
	glPopMatrix();

}

void display ( void )   // Creamos la funcion donde se dibuja
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glLoadIdentity();

	glPushMatrix();	//	1

	

	if(isBallCameraEnabled)
	{
		//camaraCanica.Position_Camera(c_posX + 3, c_posY + 3, c_posZ,
			//c_posX, c_posY, c_posZ, 0, 1, 0);

		glRotatef(c_lookupdown, 1, 0, 0);
		//glRotatef(c_lookrightleft, 0, 1, 0);		

		gluLookAt(camaraCanica.mPos.x, camaraCanica.mPos.y, camaraCanica.mPos.z,
			camaraCanica.mView.x, camaraCanica.mView.y, camaraCanica.mView.z,
			camaraCanica.mUp.x, camaraCanica.mUp.y, camaraCanica.mUp.z);

		/*gluLookAt(c_posX + 3, c_posY + 3, c_posZ, c_posX, c_posY, c_posZ,
			camaraCanica.mUp.x, camaraCanica.mUp.y, camaraCanica.mUp.z);*/
	}
	else
	{
		glRotatef(g_lookupdown, 1, 0, 0);
		
		gluLookAt(camaraUsuario.mPos.x, camaraUsuario.mPos.y, camaraUsuario.mPos.z,
			camaraUsuario.mView.x, camaraUsuario.mView.y, camaraUsuario.mView.z,
			camaraUsuario.mUp.x, camaraUsuario.mUp.y, camaraUsuario.mUp.z);
	}
		
		//	Canica metálica que puede moverse con WASD
		//	Para acceder a ella, apretar 0
		glPushMatrix();
			
			//	Crear luz tipo Spotlight hacia donde ve la camara
			GLfloat PositionSpot3[] = {camaraCanica.mView.x, camaraCanica.mView.y, camaraCanica.mView.z};
			Position3[0] = camaraCanica.mPos.x;
			Position3[1] = camaraCanica.mPos.y;
			Position3[2] = camaraCanica.mPos.z;

			//	Actualizar posición de la canica en tercera persona y la
			//	dirección de la luz.
			glTranslatef(camaraCanica.mView.x, camaraCanica.mView.y, camaraCanica.mView.z);
			glLightfv(GL_LIGHT3,GL_POSITION, Position3);
			glLightfv(GL_LIGHT3,GL_SPOT_DIRECTION,PositionSpot3);
			
			//	Agregar material metálico (plata)
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, silver_ambient);
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, silver_diffuse);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, silver_specular);
			glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, silver_shininess * 128.0);
			figures.esfera(0.8, 20, 20, 0);  //canica con camara ligada

		glPopMatrix();
		
		jackpots();
		obstaculos();
		perro();
		
		entradas();

		glPushMatrix();
		glScalef(1.5,1.5,1.5);
		cajaPachinko();
		glPopMatrix();

		

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
			if(isBallCameraEnabled)
			{
				//c_posX -= 0.3;
				camaraCanica.Move_Camera(CAMERASPEED + 0.2);
			}
			else
			{
				camaraUsuario.Move_Camera(CAMERASPEED + 0.2);
			}
			//eye_camZ -= 0.5f;
			break;

		case 's':
		case 'S':
			if(isBallCameraEnabled)
			{
				//c_posX += 0.3;
				camaraCanica.Move_Camera(-(CAMERASPEED + 0.2));
			}
			else
			{
				camaraUsuario.Move_Camera(-(CAMERASPEED + 0.2));
			}
			//eye_camZ += 0.5f;
			break;

		case 'a':
		case 'A':
			if(isBallCameraEnabled)
			{
				//c_posZ += 0.3;
				camaraCanica.Strafe_Camera(-(CAMERASPEED + 0.4));
			}
			else
			{
				camaraUsuario.Strafe_Camera(-(CAMERASPEED + 0.4));
			}
			//eye_camX -= 0.5f;
			break;
		case 'd':
		case 'D':
			if(isBallCameraEnabled)
			{
				//c_posZ -= 0.3;
				camaraCanica.Strafe_Camera(CAMERASPEED + 0.4);
			}
			else
			{
				camaraUsuario.Strafe_Camera(CAMERASPEED + 0.4);
			}
			//eye_camX += 0.5f;
			break;

		case '0':
			isBallCameraEnabled = !isBallCameraEnabled;
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

		case '1':
			luz1 = !luz1;
			break;
		case '2':
			luz2 = !luz2;
			break;
		case '3':
			luz3 = !luz3;
			break;
		case '4':
			luz4 = !luz4;
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
			printf("(%f, %f, %f)\n", xx, yy, zz);
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
		if (isBallCameraEnabled)
		{
			//c_posY -= 0.3;
			camaraCanica.UpDown_Camera(CAMERASPEED);
		}
		else
		{
			camaraUsuario.UpDown_Camera(CAMERASPEED);
		}
		//eye_camY += 0.5f;
		break;

	case GLUT_KEY_PAGE_DOWN:
		if (isBallCameraEnabled)
		{
			//c_posY += 0.3;
			camaraCanica.UpDown_Camera(-CAMERASPEED);
		}
		else
		{
			camaraUsuario.UpDown_Camera(-CAMERASPEED);
		}
		//eye_camY -= 0.5f;
		break;

    case GLUT_KEY_UP:     // Presionamos tecla ARRIBA...
		if (isBallCameraEnabled)
		{
			c_lookupdown -= 1.0f;
		}
		else
		{
			g_lookupdown -= 1.0f;
		}
		break;

    case GLUT_KEY_DOWN:               // Presionamos tecla ABAJO...
		if (isBallCameraEnabled)
		{
			c_lookupdown += 1.0f;
		}
		else
		{
			g_lookupdown += 1.0f;
		}
		//g_lookupdown += 1.0f;
		break;

	case GLUT_KEY_LEFT:
		if (isBallCameraEnabled)
		{
			//c_lookrightleft -= 1.0f;
			camaraCanica.Rotate_View(-CAMERASPEED);
		}
		else
		{
			camaraUsuario.Rotate_View(-CAMERASPEED);
		}
		//camaraUsuario.Rotate_View(-CAMERASPEED);
		break;

	case GLUT_KEY_RIGHT:
		if (isBallCameraEnabled)
		{
			//c_lookrightleft += 1.0f;
			camaraCanica.Rotate_View(CAMERASPEED);
		}
		else
		{
			camaraUsuario.Rotate_View(CAMERASPEED);
		}
		//camaraUsuario.Rotate_View(CAMERASPEED);
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