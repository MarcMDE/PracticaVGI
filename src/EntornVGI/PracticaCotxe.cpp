#include "stdafx.h"
#include "PracticaCotxe.h"


void PracticaCotxe::glTranslateV(const Vector3 & v)
{
	glTranslatef(v.X(), v.Y(), v.Z());
}

void PracticaCotxe::glRotateV(const Vector3 & v)
{
	// TODO: rotate call
//glRotatef()
}

void PracticaCotxe::glScaleV(const Vector3 & v)
{
	glScalef(v.X(), v.Y(), v.Z());
}

void PracticaCotxe::DrawRec(OGLObject * obj)
{
	glPushMatrix();
	glScaleV(obj->GetScale());
	glRotateV(obj->GetRotation());
	glTranslateV(obj->GetPosition());

	if (obj->GetGLIndex() != 0)
	{
		glCallList(obj->GetGLIndex());
	}

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
	m_mainObj = OGLObject(0);
	m_carProgress = 0;
	m_carInc = 0.005f;


	m_car.SetWheel(0, OBJ_WHEEL, Vector3(14.0f, 0.0f, 7.0f), Vector3().Zero(), Vector3(1, 1, 1));
	// Pos Z deber�a ser -7 pero para estar siendo afectada por la escala
	m_car.SetWheel(1, OBJ_WHEEL, Vector3(14.0f, 0.0f, 7.0f), Vector3().Zero(), Vector3(1, 1, -1.0f));
	m_car.SetWheel(2, OBJ_WHEEL, Vector3(-14.0f, 0.0f, 7.0f), Vector3().Zero(), Vector3(1, 1, 1));
	// Pos Z deber�a ser -7 pero para estar siendo afectada por la escala
	m_car.SetWheel(3, OBJ_WHEEL, Vector3(-14.0f, 0.0f, 7.0f), Vector3().Zero(), Vector3(1, 1, -1.0f));

	m_mainObj.SetChildsLength(1);
	m_mainObj.SetChild(0, m_car.GetBody());

	m_car.GetDynamicBody()->SetPosition(m_circuit.GetPosition(m_carProgress));

	glEnable(GL_LIGHT1);

	


	m_sun.encesa = true;
	m_sun.difusa[0] = 1.0f;			m_sun.difusa[1] = 0.0f;			m_sun.difusa[2] = 1.0f;			m_sun.difusa[3] = 1.0f;
	m_sun.especular[0] = 1.0f;		m_sun.especular[1] = 1.0f;		m_sun.especular[2] = 1.0f;		m_sun.especular[3] = 1.0f;

	m_sun.posicio.R = 75.0;			m_sun.posicio.alfa = 90.0;		m_sun.posicio.beta = 0.0;		// Posici� llum (x,y,z)=(0,0,75)
	m_sun.atenuacio.a = 0.0;		m_sun.atenuacio.b = 0.0;		m_sun.atenuacio.c = 1.0;		// Llum sense atenuaci� per dist�ncia (a,b,c)=(0,0,1)
	m_sun.restringida = false;
	m_sun.spotdirection[0] = 0.0;	m_sun.spotdirection[1] = 0.0;	m_sun.spotdirection[2] = 0.0;
	m_sun.cutoff = 0.0;				m_sun.exponent = 0.0;
}
//
//void Iluminacio(char ilumin, bool ifix, bool ll_amb, LLUM lumin, bool textur, bool textur_map, char obj, bool bc_lin, int step)
//{
//	//bool ll_amb=true;
//	GLfloat angv, angh;
//
//	// Configuraci� de la font de llum LIGHT0
//	GLfloat position[] = { 0.0,0.0,200.0,1.0 };
//	GLfloat especular[] = { 0.0,0.0,0.0,1.0 };
//	GLfloat ambientg[] = { .5,.5,.5,1.0 };
//
//	// Definici� de llum ambient segons booleana ll_amb
//	if (ll_amb) glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientg);
//	else glLightModelfv(GL_LIGHT_MODEL_AMBIENT, especular);
//
//	if (lumin.encesa) {
//		if (!ifix) glLightfv(GL_LIGHT1, GL_POSITION, position);
//		else {	// Conversi� angles graus -> radians
//			angv = lumin.posicio.alfa*pi / 180;
//			angh = lumin.posicio.beta*pi / 180;
//
//			// Conversi� Coord. esf�riques -> Coord. cartesianes
//			position[0] = lumin.posicio.R*cos(angh)*cos(angv);
//			position[1] = lumin.posicio.R*sin(angh)*cos(angv);
//			position[2] = lumin.posicio.R*sin(angv);
//			position[3] = 1.0;
//			glLightfv(GL_LIGHT1, GL_POSITION, position);
//		}
//		glLightfv(GL_LIGHT1, GL_DIFFUSE, lumin.difusa);
//		glLightfv(GL_LIGHT1, GL_SPECULAR, lumin.especular);
//
//		// Coeficients factor atenuaci� f_att=1/(ad2+bd+c)
//		glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, lumin.atenuacio.c);
//		glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, lumin.atenuacio.b);
//		glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, lumin.atenuacio.a);
//		if (lumin.restringida) {
//			glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, lumin.spotdirection);
//			glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, lumin.cutoff);
//			glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, lumin.exponent);
//		}
//		glEnable(GL_LIGHT1);
//	}
//	else glDisable(GL_LIGHT1);
//
//	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
//
//	// Selecci� del model d'iluminaci� segons variable ilumin
//	switch (ilumin)
//	{
//	case PUNTS:
//		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
//		glEnable(GL_COLOR_MATERIAL);
//
//		// Desactivaci� de l'ocultaci� de cares
//		glDisable(GL_DEPTH_TEST);
//
//		// Desactivaci� de la il.luminaci�
//		glDisable(GL_LIGHTING);
//		break;
//
//	case FILFERROS:
//		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//		glDisable(GL_COLOR_MATERIAL);
//
//		// Desactivaci� de l'ocultaci� de cares
//		//		glDisable(GL_DEPTH_TEST);
//
//		// Desactivaci� de la il-luminaci�
//		glDisable(GL_LIGHTING);
//		break;
//
//	case PLANA:
//		// C�lcul de les normals a les cares si l'objecte �s un fractal
//		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//		// Dibuix de les cares back com a l�nies en Il.luminacio PLANA i SUAU
//		if (bc_lin) glPolygonMode(GL_BACK, GL_LINE);
//
//		glEnable(GL_COLOR_MATERIAL);
//
//		// Ocultaci� de cares
//		//		glEnable(GL_DEPTH_TEST);
//
//		glEnable(GL_NORMALIZE);
//		// Il.luminaci� per cares planes
//		glShadeModel(GL_FLAT);
//
//		// Activaci� de la llum
//		glEnable(GL_LIGHTING);
//		break;
//
//	case GOURAUD:
//		// C�lcul de les normals als vertexs si l'objecte �s un fractal
//		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//		// Dibuix de les cares back com a l�nies en Il.luminacio PLANA i SUAU
//		if (bc_lin) glPolygonMode(GL_BACK, GL_LINE);
//
//		glEnable(GL_COLOR_MATERIAL);
//
//		// Ocultaci� de cares
//		//    	glEnable(GL_DEPTH_TEST);
//
//		glEnable(GL_NORMALIZE);
//
//		// Il.luminaci� suau 
//		glShadeModel(GL_SMOOTH);
//
//		// Activaci� de la llum
//		glEnable(GL_LIGHTING);
//		break;
//	}
//
//	// Configuraci� de les textures.
//	if (textur)
//	{
//		// Activaci� de la textura 0.
//		//!!glBindTexture(GL_TEXTURE_2D, textures[0]);
//
//		if ((obj != OBJ3DS) && (obj != OBJOBJ))
//		{
//			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//
//			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//		}
//
//		// Pregunta 9 enunciat
//		if (textur_map) glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
//		else glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
//
//		// Generaci� coordenades textura autom�tiques per als objectes Fractals.
//		/*	  if (obj == O_FRACTAL)
//			  {	  glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
//				  glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
//
//		// Coeficicients coordenades textura per a fractals
//		//			      sfPlane =     p1,p2,p3,p4
//				  GLfloat sfPlane[4] = {  ,  ,  ,  }; // s=p1*x0+p2*y0+p3*z0+p4*w0 on p=(x0,y0,z0,w0)
//				  //	  tfPlane =     p1,p2,p3,p4
//				  GLfloat tfPlane[4] = {  ,  ,  ,  }; // t=p1*x0+p2*y0+p3*z0+p4*w0 on p=(x0,y0,z0,w0)
//
//				  glTexGenfv(GL_S, GL_OBJECT_PLANE, sfPlane);
//				  glTexGenfv(GL_T, GL_OBJECT_PLANE, tfPlane);
//
//				  glEnable(GL_TEXTURE_GEN_S);
//				  glEnable(GL_TEXTURE_GEN_T);
//			  }
//		*/
//		// Coeficicients generaci� coordenades textura autom�tiques per a resta d'objectes
//		 /*	  else
//			  {	glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
//			  glTexGeni(GL_T,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
//
//		// Generaci� coordenades textura.
//			  GLfloat sPlane[4] = { -1.0f, 1.0f, 0.0f, 1.0f };
//			  GLfloat tPlane[4] = { -1.0f, 0.0f, 1.0f, 1.0f };
//
//			  glTexGenfv(GL_S, GL_OBJECT_PLANE, sPlane);
//			  glTexGenfv(GL_T, GL_OBJECT_PLANE, tPlane);
//
//			  glEnable(GL_TEXTURE_GEN_S);
//			  glEnable(GL_TEXTURE_GEN_T);
//			  }
//		*/
//		glEnable(GL_TEXTURE_2D);
//	}
//	else {
//		glDisable(GL_TEXTURE_2D);
//		glDisable(GL_TEXTURE_GEN_S);
//		glDisable(GL_TEXTURE_GEN_T);
//	}
//
//	// Creaci� de la llista que dibuixar� els eixos
//	//   funci� on est� codi per dibuixar eixos
//	glNewList(EIXOS, GL_COMPILE);
//	// Dibuix dels eixos sense il.luminaci�
//	//	if (ilumin!=FILFERROS) 
//	glDisable(GL_LIGHTING);
//	// Dibuixar eixos sense textures
//	//	if (textura) 
//	glDisable(GL_TEXTURE_2D);
//	//!!!!!deixos();
//	if (ilumin != FILFERROS) glEnable(GL_LIGHTING);
//	if (textur) glEnable(GL_TEXTURE_2D);
//	glEndList();
//}


PracticaCotxe::~PracticaCotxe()
{
}

void PracticaCotxe::Draw(/*CColor col_object, bool ref_mat, bool sw_mat[4]*/)
{
	// Assignaci� de les variables de color i reflexi� als valors de les variables per par�metre
	//color_objecte = col_object;
	//reflexio_material = ref_mat;
	//for (int i = 0; i < 4; i++) sw_materials[i] = sw_mat[i];

	m_circuit.Draw(true, 50);
	m_circuit.DrawCircuit();
	DrawRec(&m_mainObj);

	// Enviar les comandes gr�fiques a pantalla
	glFlush();
}

void PracticaCotxe::Procesa_Teclat(UINT nChar, UINT nRepCnt) {

	switch (nChar) {

		case DAV:

			m_car.GetDynamicBody()->Translate(Vector3(1, 0, 0));
			m_carProgress += m_carInc;
			if (m_carProgress >= 1) m_carProgress -= 1;

			m_car.GetDynamicBody()->SetPosition(m_circuit.GetPosition(m_carProgress));

			break;

		case DAR:

			m_car.GetDynamicBody()->Translate(Vector3(-1, 0, 0));

			break;


		case ESQ:

			m_car.GetDynamicBody()->Translate(Vector3(0, 0, -1));

			break;


		case DRT:

			m_car.GetDynamicBody()->Translate(Vector3(0, 0, 1));

			break;


		case ESP:

			m_car.GetDynamicBody()->SetPosition(Vector3().Zero());
			break;
	
	}

}
