#pragma once
#include "Car.h"
#include "camara.h"
#include "OGLObject.h"
#include "DynamicOGLObject.h"
#include "Circuit.h"
#include "UIButton.h"

#define PC_DEVELOP

#define MAX_JUGADORS 4

#define BUTTONS_INICI 2
#define BUTTONS_SELEC 9
#define BUTTONS_PAUSE 1

// Definició de les tecles del teclat i del ratolí
/*

#define DAV 87 // W
#define DAR 83 // S
#define ESQ 65 // A
#define DRT 68 // D

*/

#define ESP 32 // Espai
#define PAUSE 80 // P

//const int DAV[MAX_JUGADORS] = { 87, 84, 73 }; // W, T, I
const int DAV[MAX_JUGADORS] = { 50, 53, 56, 39 }; // 2, 5, 8, '
const int DAR[MAX_JUGADORS] = { 49, 52, 55, 58 }; // 1, 4, 7, 9

enum SCREENS { INICI=0, SELECCIO=1, GAMEPLAY=2 };
enum B_INICI { START=0, EXIT=1 };
enum B_SELEC { P1=0, P2, P3, P4, C1, C2, C3, C4, NEXT };
enum B_PAUSE { EXITB =0 };

class PracticaCotxe
{
private:

	float a = 0;

	float vX = 0;
	float vY = 1;
	float vZ = 0;

	UIButton m_buttonsInici[BUTTONS_INICI];
	UIButton m_buttonsSelec[BUTTONS_SELEC];
	UIButton m_buttonsPause[BUTTONS_PAUSE];

	//Car m_car = Car(4, Vector3(0, 0, 0), Vector3().Zero(), Vector3().One());
	Car *m_cars;
	int m_nJugadors;
	OGLObject m_mainObj;
	LLUM m_sun;
	Circuit m_circuit;
	camara m_cam = camara(-100, 0, 0, 0, 25, 0, 0, 5, 0);
	SCREENS m_currScreen;
	bool m_isPaused;

	float m_carProgress;
	float m_carInc;

	void glTranslateV(const Vector3& v);
	void glRotateV(const Vector3& v);
	void glScaleV(const Vector3& v);
	void DrawRec(OGLObject* obj);
	void Iluminacio(char ilumin, bool ifix, bool ll_amb, LLUM lumin, bool textur, bool textur_map, char obj, bool bc_lin, int step);
	void DrawUIElement(int texture, int posX, int posY, int width, int heigth);
	void DrawUIElement(CColor color, int posX, int posY, int width, int heigth);
	void OnButtonClick();
public:
	PracticaCotxe();
	~PracticaCotxe();

	void Init();

	void Draw(/*CColor col_object, bool ref_mat, bool sw_mat[4]*/);
	void DrawInterface(int w, int h);
	void Procesa_Teclat(UINT nChar, UINT nRepCnt);
	void Update();
	void setNJugadors(int i);
};

