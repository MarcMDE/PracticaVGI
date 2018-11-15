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
	mainObj = OGLObject(0);

	car.SetWheel(0, OBJ_WHEEL, Vector3(14.0f, 0.0f, 7.0f), Vector3().Zero(), Vector3(1, 1, 1));
	// Pos Z debería ser -7 pero para estar siendo afectada por la escala
	car.SetWheel(1, OBJ_WHEEL, Vector3(14.0f, 0.0f, 7.0f), Vector3().Zero(), Vector3(1, 1, -1.0f));
	car.SetWheel(2, OBJ_WHEEL, Vector3(-14.0f, 0.0f, 7.0f), Vector3().Zero(), Vector3(1, 1, 1));
	// Pos Z debería ser -7 pero para estar siendo afectada por la escala
	car.SetWheel(3, OBJ_WHEEL, Vector3(-14.0f, 0.0f, 7.0f), Vector3().Zero(), Vector3(1, 1, -1.0f));

	mainObj.SetChildsLength(1);
	mainObj.SetChild(0, car.GetBody());
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

	DrawRec(&mainObj);

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

			car.GetDynamicBody()->Translate(Vector3(5, 0, 0));

			break;

		case DAR:

			car.GetDynamicBody()->Translate(Vector3(-5, 0, 0));

			break;


		case ESQ:

			car.GetDynamicBody()->Translate(Vector3(0, 0, -5));

			break;


		case DRT:

			car.GetDynamicBody()->Translate(Vector3(0, 0, 5));

			break;


		case ESP:

			//

			break;
	
	}

}
