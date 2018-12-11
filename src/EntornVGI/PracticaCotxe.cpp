#include "stdafx.h"
#include "PracticaCotxe.h"


void PracticaCotxe::glTranslateV(const Vector3 & v)
{
	glTranslatef(v.X(), v.Y(), v.Z());
}

void PracticaCotxe::glRotateV(const Vector3 & v)
{
	glRotatef(v.X() * RAD_TO_DEG, 0, 1, 0);
	//glRotatef(v.Y() * RAD_TO_DEG, 0, 0, 1);
	//glRotatef(v.Z() * RAD_TO_DEG, 0, 0, 1);
}

void PracticaCotxe::glScaleV(const Vector3 & v)
{
	glScalef(v.X(), v.Y(), v.Z());
}

void PracticaCotxe::DrawRec(OGLObject * obj)
{

	glPushMatrix();

	glTranslateV(obj->GetPosition());	
	glScaleV(obj->GetScale());
	glRotateV(obj->GetRotation());

	obj->Draw();

	int cLength = obj->GetChildsLength();

	// For each child
	for (int i = 0; i < cLength; i++)
	{
		DrawRec(obj->GetChild(i));
	}

	glPopMatrix();
}


PracticaCotxe::PracticaCotxe()
{
	m_mainObj = OGLObject(-1, -1);

	m_carProgress = 0;
	m_carInc = 0.005f;

	m_circuit.Load(CIRCUIT_6);

	m_car.SetBody(OBJ_CAR, TXT_CAR, Vector3().Zero(), Vector3().Zero(), Vector3().One());

	m_car.SetWheel(0, OBJ_WHEEL, TXT_WHEEL, Vector3(14.0f, 0.0f, 7.0f), Vector3().Zero(), Vector3(1, 1, 1));
	// Pos Z debería ser -7 pero para estar siendo afectada por la escala
	m_car.SetWheel(1, OBJ_WHEEL, TXT_WHEEL, Vector3(14.0f, 0.0f, -7.0f), Vector3().Zero(), Vector3(1, 1, -1.0f));
	m_car.SetWheel(2, OBJ_WHEEL, TXT_WHEEL, Vector3(-14.0f, 0.0f, 7.0f), Vector3().Zero(), Vector3(1, 1, 1));
	// Pos Z debería ser -7 pero para estar siendo afectada por la escala
	m_car.SetWheel(3, OBJ_WHEEL, TXT_WHEEL, Vector3(-14.0f, 0.0f, -7.0f), Vector3().Zero(), Vector3(1, 1, -1.0f));

	//m_car.SetChild(5, &m_cam);

	m_circuit.SetChildsLength(1);
	m_circuit.SetChild(0, &m_car);

	m_mainObj.SetChildsLength(1);
	m_mainObj.SetChild(0, &m_circuit);


	m_sun.encesa = true;
	m_sun.difusa[0] = 1.0f;		m_sun.difusa[1] = 1.0f;		m_sun.difusa[2] = 1.0f;		m_sun.difusa[3] = 1.0f;
	m_sun.especular[0] = 1.0f;		m_sun.especular[1] = 1.0f;		m_sun.especular[2] = 1.0f;		m_sun.especular[3] = 1.0f;

	m_sun.posicio.R = 75.0;		m_sun.posicio.alfa = 90.0;		m_sun.posicio.beta = 0.0;		// Posició llum (x,y,z)=(0,0,75)
	m_sun.atenuacio.a = 0.0;		m_sun.atenuacio.b = 0.0;		m_sun.atenuacio.c = 1.0;		// Llum sense atenuació per distància (a,b,c)=(0,0,1)
	m_sun.restringida = false;
	m_sun.spotdirection[0] = 0.0;	m_sun.spotdirection[1] = 0.0;	m_sun.spotdirection[2] = 0.0;
	m_sun.cutoff = 0.0;			m_sun.exponent = 0.0;


	//m_car.SetPosition(m_circuit.CalcPosition(m_carProgress));
}

PracticaCotxe::~PracticaCotxe()
{
}

void PracticaCotxe::Init()
{
	m_circuit.Init();
}

void PracticaCotxe::Iluminacio(char ilumin, bool ifix, bool ll_amb, LLUM lumin, bool textur, bool textur_map, char obj, bool bc_lin, int step)
{
	//bool ll_amb=true;
	GLfloat angv, angh;

	// Configuració de la font de llum LIGHT0
	GLfloat position[] = { 0.0,0.0,200.0,1.0 };
	GLfloat especular[] = { 0.0,0.0,0.0,1.0 };
	GLfloat ambientg[] = { .5,.5,.5,1.0 };

	// Definició de llum ambient segons booleana ll_amb
	if (ll_amb) glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientg);
	else glLightModelfv(GL_LIGHT_MODEL_AMBIENT, especular);

	if (lumin.encesa) {
		if (!ifix) glLightfv(GL_LIGHT0, GL_POSITION, position);
		else {	// Conversió angles graus -> radians
			angv = lumin.posicio.alfa*pi / 180;
			angh = lumin.posicio.beta*pi / 180;

			// Conversió Coord. esfèriques -> Coord. cartesianes
			position[0] = lumin.posicio.R*cos(angh)*cos(angv);
			position[1] = lumin.posicio.R*sin(angh)*cos(angv);
			position[2] = lumin.posicio.R*sin(angv);
			position[3] = 1.0;
			glLightfv(GL_LIGHT0, GL_POSITION, position);
		}
		glLightfv(GL_LIGHT0, GL_DIFFUSE, lumin.difusa);
		glLightfv(GL_LIGHT0, GL_SPECULAR, lumin.especular);

		// Coeficients factor atenuació f_att=1/(ad2+bd+c)
		glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, lumin.atenuacio.c);
		glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, lumin.atenuacio.b);
		glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, lumin.atenuacio.a);
		if (lumin.restringida) {
			glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, lumin.spotdirection);
			glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, lumin.cutoff);
			glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, lumin.exponent);
		}
		glEnable(GL_LIGHT0);
	}
	else glDisable(GL_LIGHT0);

	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	// Selecció del model d'iluminació segons variable ilumin
	switch (ilumin)
	{
	case PUNTS:
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		glEnable(GL_COLOR_MATERIAL);

		// Desactivació de l'ocultació de cares
		glDisable(GL_DEPTH_TEST);

		// Desactivació de la il.luminació
		glDisable(GL_LIGHTING);
		break;

	case FILFERROS:
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDisable(GL_COLOR_MATERIAL);

		// Desactivació de l'ocultació de cares
		//		glDisable(GL_DEPTH_TEST);

		// Desactivació de la il-luminació
		glDisable(GL_LIGHTING);
		break;

	case PLANA:
		// Càlcul de les normals a les cares si l'objecte és un fractal
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		// Dibuix de les cares back com a línies en Il.luminacio PLANA i SUAU
		if (bc_lin) glPolygonMode(GL_BACK, GL_LINE);

		glEnable(GL_COLOR_MATERIAL);

		// Ocultació de cares
		//		glEnable(GL_DEPTH_TEST);

		glEnable(GL_NORMALIZE);
		// Il.luminació per cares planes
		glShadeModel(GL_FLAT);

		// Activació de la llum
		glEnable(GL_LIGHTING);
		break;

	case GOURAUD:
		// Càlcul de les normals als vertexs si l'objecte és un fractal
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		// Dibuix de les cares back com a línies en Il.luminacio PLANA i SUAU
		if (bc_lin) glPolygonMode(GL_BACK, GL_LINE);

		glEnable(GL_COLOR_MATERIAL);

		// Ocultació de cares
		//    	glEnable(GL_DEPTH_TEST);

		glEnable(GL_NORMALIZE);

		// Il.luminació suau 
		glShadeModel(GL_SMOOTH);

		// Activació de la llum
		glEnable(GL_LIGHTING);
		break;
	}

	//// Configuració de les textures.
	if (textur)
	{
		// Activació de la textura 0.
		glBindTexture(GL_TEXTURE_2D, 0);

		if ((obj != OBJ3DS) && (obj != OBJOBJ))
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}

		// Pregunta 9 enunciat
		if (textur_map) glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		else glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

		// Generació coordenades textura automàtiques per als objectes Fractals.
		/*	  if (obj == O_FRACTAL)
			  {	  glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
				  glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);

		// Coeficicients coordenades textura per a fractals
		//			      sfPlane =     p1,p2,p3,p4
				  GLfloat sfPlane[4] = {  ,  ,  ,  }; // s=p1*x0+p2*y0+p3*z0+p4*w0 on p=(x0,y0,z0,w0)
				  //	  tfPlane =     p1,p2,p3,p4
				  GLfloat tfPlane[4] = {  ,  ,  ,  }; // t=p1*x0+p2*y0+p3*z0+p4*w0 on p=(x0,y0,z0,w0)

				  glTexGenfv(GL_S, GL_OBJECT_PLANE, sfPlane);
				  glTexGenfv(GL_T, GL_OBJECT_PLANE, tfPlane);

				  glEnable(GL_TEXTURE_GEN_S);
				  glEnable(GL_TEXTURE_GEN_T);
			  }
		*/
		// Coeficicients generació coordenades textura automàtiques per a resta d'objectes
		 /*	  else
			  {	glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
			  glTexGeni(GL_T,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);

		// Generació coordenades textura.
			  GLfloat sPlane[4] = { -1.0f, 1.0f, 0.0f, 1.0f };
			  GLfloat tPlane[4] = { -1.0f, 0.0f, 1.0f, 1.0f };

			  glTexGenfv(GL_S, GL_OBJECT_PLANE, sPlane);
			  glTexGenfv(GL_T, GL_OBJECT_PLANE, tPlane);

			  glEnable(GL_TEXTURE_GEN_S);
			  glEnable(GL_TEXTURE_GEN_T);
			  }
		*/
		glEnable(GL_TEXTURE_2D);
	}
	else {
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_TEXTURE_GEN_S);
		glDisable(GL_TEXTURE_GEN_T);
	}

	// Creació de la llista que dibuixarà els eixos
	//   funció on està codi per dibuixar eixos
	glNewList(EIXOS, GL_COMPILE);
	// Dibuix dels eixos sense il.luminació
	//	if (ilumin!=FILFERROS) 
	glDisable(GL_LIGHTING);
	// Dibuixar eixos sense textures
	//	if (textura) 
	glDisable(GL_TEXTURE_2D);
	deixos();
	if (ilumin != FILFERROS) glEnable(GL_LIGHTING);
	if (textur) glEnable(GL_TEXTURE_2D);
	glEndList();
}

void PracticaCotxe::Draw(/*CColor col_object, bool ref_mat, bool sw_mat[4]*/)
{
	// Assignació de les variables de color i reflexió als valors de les variables per paràmetre
	//color_objecte = col_object;
	//reflexio_material = ref_mat;
	//for (int i = 0; i < 4; i++) sw_materials[i] = sw_mat[i];


#ifndef PC_DEVELOP
	// CAMARA ----------------------------------------------------------------------------
	// Neteja dels buffers de color i profunditat
	CColor col_fons;
	col_fons.r = 0;
	col_fons.g = 0;
	col_fons.b = 0;
	col_fons.a = 1;

	Fons(col_fons);

	Vector3 cameraPosition = m_car.GetPosition();
	cameraPosition-= Vector3(m_car.GetDirection().X() * 60, 0, m_car.GetDirection().Z() * 60);
	cameraPosition += Vector3(0, 35, 0);
	gluLookAt(cameraPosition.X(), cameraPosition.Y(), cameraPosition.Z(), m_car.GetPosition().X(), m_car.GetPosition().Y() + 20, m_car.GetPosition().Z(), 0, 1, 0);

	// Iluminacio fixe respecte la camara (després glLookAt)
	Iluminacio(GOURAUD, true, true, m_sun, true, true, 'a', false, 0);

	// Test de Visibilitat
	//if (testv) glEnable(GL_CULL_FACE);
	//else glDisable(GL_CULL_FACE);

	// Ocultacions (Z-buffer)
	//if (oculta) glEnable(GL_DEPTH_TEST);
	//else glDisable(GL_DEPTH_TEST);

	// Dibuix de les cares back com a línies en Il.luminacio PLANA i SUAU
	//if (bck_ln) glPolygonMode(GL_BACK, GL_LINE);


	// -----------------------------------------------------------------------------------
#else
	// Dibuix dels eixos
	glCallList(EIXOS);
#endif

	glColor3f(1, 1, 1);
	glEnable(GL_TEXTURE_2D);

	DrawRec(&m_mainObj);

	/*
	glBindTexture(GL_TEXTURE_2D, TXT_TEST);
	glutSolidCube(10);
	glBegin(GL_QUADS);

		glTexCoord2f(0.0, 0.0); glVertex3f(-2.0, -2.0, 0.0); 
		glTexCoord2f(0.0, 1.0); glVertex3f(-2.0, 2.0, 0.0);
		glTexCoord2f(1.0, 1.0); glVertex3f(2.0, 2.0, 0.0);
		glTexCoord2f(1.0, 0.0); glVertex3f(2.0, -2.0, 0.0);

	glEnd();
	*/

	// Enviar les comandes gràfiques a pantalla
	glFlush();
}

void PracticaCotxe::DrawInterface(int w, int h)
{
	glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
	glColor3f(1.0f, 0.0f, 0.0f); // Red
	glVertex2f(w / 2 - 100, 200);    // x, y
	glVertex2f(w / 2 + 100, 200);
	glVertex2f(w / 2 + 100, 300);
	glVertex2f(w / 2 - 100, 300);
	glEnd();
}

void PracticaCotxe::Procesa_Teclat(UINT nChar, UINT nRepCnt) {
	Vector3 rotation;
	Vector3 rotation2;
	Vector3 newPos;
	Vector3 dir;
	Vector3 pos;
	int rx = 0;
	int ry = 0;
	int rz = 0;

	switch (nChar) {

		case DAV:
			m_carProgress += m_carInc;
			if (m_carProgress >= 1) m_carProgress -= 1;

			dir = m_circuit.CalcDirection(m_carProgress);
			//dir.Normalize();

			newPos = m_circuit.CalcPosition(m_carProgress);
			
			m_car.Move(newPos, dir);

			//a += 0.5f;

			break;

		case DAR:

			////m_car.Translate(Vector3(-1, 0, 0));
			//m_carProgress -= m_carInc;
			//if (m_carProgress <= 0) m_carProgress += 1;
			//m_car.SetPosition(m_circuit.CalcPosition(m_carProgress));

			break;


		case ESQ:

			m_car.Translate(Vector3(0, 0, -1));

			break;


		case DRT:

			m_car.Translate(Vector3(0, 0, 1));

			break;


		case ESP:

			m_car.SetPosition(Vector3().Zero());
			break;
	
	}

}
