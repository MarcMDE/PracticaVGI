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

	m_car.SetWheel(0, OBJ_WHEEL, Vector3(14.0f, 0.0f, 7.0f), Vector3().Zero(), Vector3(1, 1, 1));
	// Pos Z debería ser -7 pero para estar siendo afectada por la escala
	m_car.SetWheel(1, OBJ_WHEEL, Vector3(14.0f, 0.0f, 7.0f), Vector3().Zero(), Vector3(1, 1, -1.0f));
	m_car.SetWheel(2, OBJ_WHEEL, Vector3(-14.0f, 0.0f, 7.0f), Vector3().Zero(), Vector3(1, 1, 1));
	// Pos Z debería ser -7 pero para estar siendo afectada por la escala
	m_car.SetWheel(3, OBJ_WHEEL, Vector3(-14.0f, 0.0f, 7.0f), Vector3().Zero(), Vector3(1, 1, -1.0f));

	m_mainObj.SetChildsLength(1);
	m_mainObj.SetChild(0, m_car.GetBody());

	m_sun.encesa = true;
	m_sun.difusa[0] = 1.0f;			m_sun.difusa[1] = 0.0f;			m_sun.difusa[2] = 1.0f;			m_sun.difusa[3] = 1.0f;
	m_sun.especular[0] = 1.0f;		m_sun.especular[1] = 1.0f;		m_sun.especular[2] = 1.0f;		m_sun.especular[3] = 1.0f;

	m_sun.posicio.R = 75.0;			m_sun.posicio.alfa = 90.0;		m_sun.posicio.beta = 0.0;		// Posició llum (x,y,z)=(0,0,75)
	m_sun.atenuacio.a = 0.0;		m_sun.atenuacio.b = 0.0;		m_sun.atenuacio.c = 1.0;		// Llum sense atenuació per distància (a,b,c)=(0,0,1)
	m_sun.restringida = false;
	m_sun.spotdirection[0] = 0.0;	m_sun.spotdirection[1] = 0.0;	m_sun.spotdirection[2] = 0.0;
	m_sun.cutoff = 0.0;				m_sun.exponent = 0.0;
}


PracticaCotxe::~PracticaCotxe()
{
}

void PracticaCotxe::Draw(/*CColor col_object, bool ref_mat, bool sw_mat[4]*/)
{
	// Assignació de les variables de color i reflexió als valors de les variables per paràmetre
	//color_objecte = col_object;
	//reflexio_material = ref_mat;
	//for (int i = 0; i < 4; i++) sw_materials[i] = sw_mat[i];

	m_circuit.Draw(true, 50, SPLINE);
	m_circuit.DrawCircuit();
	DrawRec(&m_mainObj);

	/*glCallList(OBJ_CAR);

	glPushMatrix();
		glTranslatef(14.0f, 0.0f, 7.0f);
		glCallList(OBJ_WHEEL);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(14.0f, 0.0f, -7.0f);
		glScalef(1, 1, -1.0f);
		glCallList(OBJ_WHEEL);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-14.0f, 0.0f, 7.0f);
		glCallList(OBJ_WHEEL);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-14.0f, 0.0f, -7.0f);
		glScalef(1, 1, -1.0f);
		glCallList(OBJ_WHEEL);
	glPopMatrix();*/

	// Enviar les comandes gràfiques a pantalla
	glFlush();
}

void PracticaCotxe::Procesa_Teclat(UINT nChar, UINT nRepCnt) {

	switch (nChar) {

		case DAV:

			m_car.GetDynamicBody()->Translate(Vector3(1, 0, 0));

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
