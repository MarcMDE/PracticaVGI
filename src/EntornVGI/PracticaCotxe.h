#pragma once
#include "Car.h"
#include "camara.h"
#include "OGLObject.h"
#include "DynamicOGLObject.h"
#include "Circuit.h"

#define PC_DEVELOP

// Definició de les tecles del teclat W, A, S, D, Espai
#define DAV 87 // W
#define DAR 83 // S
#define ESQ 65 // A
#define DRT 68 // D
#define ESP 32 // Espai


class PracticaCotxe
{
private:

	float a = 0;

	float vX = 0;
	float vY = 1;
	float vZ = 0;

	Car m_car = Car(4, Vector3(0, 0, 0), Vector3().Zero(), Vector3().One());
	OGLObject m_mainObj;
	LLUM m_sun;
	Circuit m_circuit;
	camara m_cam = camara(-100, 0, 0, 0, 25, 0, 0, 5, 0);

	float m_carProgress;
	float m_carInc;

	void glTranslateV(const Vector3& v);
	void glRotateV(const Vector3& v);
	void glScaleV(const Vector3& v);
	void DrawRec(OGLObject* obj);
	void Iluminacio(char ilumin, bool ifix, bool ll_amb, LLUM lumin, bool textur, bool textur_map, char obj, bool bc_lin, int step);
public:
	PracticaCotxe();
	~PracticaCotxe();

	void Init();

	void Draw(/*CColor col_object, bool ref_mat, bool sw_mat[4]*/);
	void DrawInterface(int w, int h);
	void Procesa_Teclat(UINT nChar, UINT nRepCnt);

};

