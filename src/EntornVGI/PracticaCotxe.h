#pragma once
#include "Car.h"
#include "OGLObject.h"
class PracticaCotxe
{
private:
	Car car = Car(OBJ_CAR, 4, Vector3(0, 0, 0), Vector3().Zero(), Vector3().One());
	OGLObject mainObj;

	void glTranslateV(const Vector3& v);
	void glRotateV(const Vector3& v);
	void glScaleV(const Vector3& v);
	void DrawRec(OGLObject* obj);
public:
	PracticaCotxe();
	~PracticaCotxe();
	void Draw(/*CColor col_object, bool ref_mat, bool sw_mat[4]*/);

};

