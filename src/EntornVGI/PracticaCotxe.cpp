#include "stdafx.h"
#include "PracticaCotxe.h"


void PracticaCotxe::glTranslateV(const Vector3 & v)
{
	glTranslatef(v.X(), v.Y(), v.Z());
}

void PracticaCotxe::glRotateV(const Vector3 & v)
{
	glRotatef(v.X() * RAD_TO_DEG, 0, 1, 0);
	glRotatef(v.Y() * RAD_TO_DEG, 0, 0, 1);
	//glRotatef(v.Z() * RAD_TO_DEG, 0, 0, 0);
}

void PracticaCotxe::glScaleV(const Vector3 & v)
{
	glScalef(v.X(), v.Y(), v.Z());
}

void PracticaCotxe::DrawRec(OGLObject * obj)
{
	if (obj->IsActive())
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
}


PracticaCotxe::PracticaCotxe()
{
	m_mainObj = OGLObject(-1, -1);

	m_isPaused = false;
	m_cars = NULL;

	m_currScreen = INICI;
}

PracticaCotxe::~PracticaCotxe()
{
}

void PracticaCotxe::Init(int w, int h)
{
	m_sWidth = w;
	m_sHeigth = h;
	m_nJugadors = 1;

	m_buttonsInici[START].Set(w / 2, h / 2, 200, 75, TXT_B_START, false);
	m_buttonsInici[EXIT].Set(w / 2, h / 2 + 180, 200, 75, TXT_B_EXIT, false);
	m_buttonsSelec[P1].Set(400, 100, 75, 75, TXT_B_SELEC_PC_1, true);
	m_buttonsSelec[P2].Set(500, 100, 75, 75, TXT_B_SELEC_PC_2, false);
	m_buttonsSelec[P3].Set(600, 100, 75, 75, TXT_B_SELEC_PC_3, false);
	m_buttonsSelec[P4].Set(700, 100, 75, 75, TXT_B_SELEC_PC_4, false);
	m_buttonsSelec[C1].Set(400, h-100, 75, 75, TXT_B_SELEC_PC_1, true);
	m_buttonsSelec[C2].Set(500, h-100, 75, 75, TXT_B_SELEC_PC_2, false);
	m_buttonsSelec[C3].Set(600, h-100, 75, 75, TXT_B_SELEC_PC_3, false);
	m_buttonsSelec[C4].Set(700, h-100, 75, 75, TXT_B_SELEC_PC_4, false);
	m_buttonsSelec[NEXT].Set(w-200, h/2, 200, 75, TXT_B_NEXT, false);
	m_buttonsFI[EXITF].Set(w - 200, h / 2, 200, 75, TXT_B_NEXT, false);

	m_circuit.Init(m_nJugadors);
	m_circuit.Load(CIRCUIT_1);

	m_mainObj.SetChildsLength(1);
	m_mainObj.SetChild(0, &m_skyBox);

	m_skyBox.SetChildsLength(1);
	m_skyBox.SetChild(0, &m_circuit);

	float dist = m_circuit.getDistance();

	m_guanyador = 0;

	m_circuit.SetChildsLength(MAX_JUGADORS);
	InitJugadors(w, h);
	setNJugadors(m_nJugadors, w, h, m_circuit.getDistance());

	m_sun.encesa = true;
	m_sun.restringida = false;
	m_isEnd = false;

	m_sun.cutoff = 0.0;
	m_sun.exponent = 0.0;

	m_sun.difusa[0] = 1.0f;		m_sun.difusa[1] = 1.0f;		m_sun.difusa[2] = 1.0f;		m_sun.difusa[3] = 1.0f;
	m_sun.especular[0] = 1.0f;		m_sun.especular[1] = 1.0f;		m_sun.especular[2] = 1.0f;		m_sun.especular[3] = 1.0f;

	//m_sun.posicio.R = -1000.0;	m_sun.posicio.alfa = 90.0;		m_sun.posicio.beta = 0.0;
	m_sun.atenuacio.a = 0.0;		m_sun.atenuacio.b = 0.0;		m_sun.atenuacio.c = 1.0;		// Llum sense atenuació per distància (a,b,c)=(0,0,1)
	m_sun.spotdirection[0] = 0.0;		m_sun.spotdirection[1] = 0.0;		m_sun.spotdirection[2] = 0.0;
	
}

void PracticaCotxe::Iluminacio(char ilumin, bool textur, char obj) {

	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);

	// Configuració de la font de llum LIGHT1
	GLfloat position[]	= { 500.0, 500.0, 1000.0, 1.0 };
	GLfloat ambientg[]	= { 0.5, 0.5, 0.5, 1.0 };

	// Definició de llum ambient
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientg);

	if (m_sun.encesa) {

		glLightfv(GL_LIGHT1, GL_POSITION, position);
		
		glLightfv(GL_LIGHT1, GL_DIFFUSE, m_sun.difusa);
		glLightfv(GL_LIGHT1, GL_SPECULAR, m_sun.especular);

		// Coeficients factor atenuació f_att=1/(ad2+bd+c)
		glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, m_sun.atenuacio.c);
		glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, m_sun.atenuacio.b);
		glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, m_sun.atenuacio.a);
		
		if (m_sun.restringida) {
		
			glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, m_sun.spotdirection);
			glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, m_sun.cutoff);
			glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, m_sun.exponent);
		
		}
		
		glEnable(GL_LIGHT1);
	
	} else {

		glDisable(GL_LIGHT1);

	}

	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	// Selecció del model d'iluminació segons variable ilumin
	switch (ilumin) {

	case FILFERROS:
		
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDisable(GL_COLOR_MATERIAL);

		// Desactivació de la il-luminació
		glDisable(GL_LIGHTING);
		
		break;

	case GOURAUD:
		
		// Càlcul de les normals als vertexs si l'objecte és un fractal
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		glEnable(GL_COLOR_MATERIAL);

		glEnable(GL_NORMALIZE);

		// Il.luminació suau 
		glShadeModel(GL_SMOOTH);

		// Activació de la llum
		glEnable(GL_LIGHTING);
		
		break;

	}

	// Configuració de les textures.
	if (textur)
	{
		// Activació de la textura 0.
		glBindTexture(GL_TEXTURE_2D, 0);

		if ((obj != OBJ3DS) && (obj != OBJOBJ)) {

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		
		}

		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

		glEnable(GL_TEXTURE_2D);
	
	} else {

		glDisable(GL_TEXTURE_2D);
		glDisable(GL_TEXTURE_GEN_S);
		glDisable(GL_TEXTURE_GEN_T);
	
	}

	// Creació de la llista que dibuixarà els eixos ============

	// funció on està codi per dibuixar eixos
	glNewList(EIXOS, GL_COMPILE);
	
	// Dibuix dels eixos sense il.luminació
	glDisable(GL_LIGHTING);
	
	// Dibuixar eixos sense textures
	glDisable(GL_TEXTURE_2D);
	deixos();
	
	if (ilumin != FILFERROS) glEnable(GL_LIGHTING);
	
	if (textur) glEnable(GL_TEXTURE_2D);
	
	glEndList();

	// =========================================================

}

void PracticaCotxe::DrawUIElement(int texture, int posX, int posY, int width, int heigth)
{
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_QUADS);
	//glColor3f(1.0f, 0.0f, 0.0f); // Red
	glTexCoord2f(1.0, 0.0); glVertex2f(posX+width/2, posY+heigth/2);
	glTexCoord2f(0.0, 0.0); glVertex2f(posX-width/2, posY+heigth/2);
	glTexCoord2f(0.0, 1.0); glVertex2f(posX-width/2, posY-heigth/2);
	glTexCoord2f(1.0, 1.0); glVertex2f(posX+width/2, posY-heigth/2);
	glEnd();
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
}

void PracticaCotxe::DrawUIElement(CColor color, int posX, int posY, int width, int heigth)
{
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	glColor4f(color.r, color.g, color.b, color.a);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0, 0.0); glVertex2f(posX + width / 2, posY + heigth / 2);
	glTexCoord2f(0.0, 0.0); glVertex2f(posX - width / 2, posY + heigth / 2);
	glTexCoord2f(0.0, 1.0); glVertex2f(posX - width / 2, posY - heigth / 2);
	glTexCoord2f(1.0, 1.0); glVertex2f(posX + width / 2, posY - heigth / 2);
	glEnd();

	glDisable(GL_BLEND);
}

void PracticaCotxe::OnButtonClickInici(int x, int y)
{
	B_INICI b;

	int i = 0;
	while (i < BUTTONS_INICI && !m_buttonsInici[i].IsClicked(x, y))
	{
		i++;
	}

	if (i < BUTTONS_INICI)
	{
		b = (B_INICI)i;

		switch (b)
		{
		case START:
			m_currScreen = SELECCIO;
			break;
		case EXIT:
			// TODO: EXIT
			break;
		default:
			break;
		}
	}

}

void PracticaCotxe::OnButtonClickSelec(int x, int y)
{
	B_SELEC b;

	int i = 0;
	while (i < BUTTONS_SELEC && !m_buttonsSelec[i].IsClicked(x, y))
	{
		i++;
	}

	if (i < BUTTONS_SELEC)
	{
		b = (B_SELEC)i;

		if ((int)b < 4)
		{
			for (int j = 0; j < 4; j++) m_buttonsSelec[j].Unselect();
		}
		else if ((int)b > 3 && (int)b < BUTTONS_SELEC - 1)
		{
			for (int j = 4; j < BUTTONS_SELEC - 1; j++) m_buttonsSelec[j].Unselect();
		}

		m_buttonsSelec[b].Select();

		switch (b)
		{
		case P1:
			setNJugadors(1, m_sWidth, m_sHeigth, m_circuit.getDistance());
			break;
		case P2:
			setNJugadors(2, m_sWidth, m_sHeigth, m_circuit.getDistance());
			break;
		case P3:
			setNJugadors(3, m_sWidth, m_sHeigth, m_circuit.getDistance());
			break;
		case P4:
			setNJugadors(4, m_sWidth, m_sHeigth, m_circuit.getDistance());
			break;
		case C1:
			if (m_circuit.GetCurrCircuit() != CIRCUIT_1)
			{
				m_circuit.Load(CIRCUIT_1);
				setNJugadors(m_nJugadors, m_sWidth, m_sHeigth, m_circuit.getDistance());
			}
			break;
		case C2:
			if (m_circuit.GetCurrCircuit() != CIRCUIT_2)
			{
				m_circuit.Load(CIRCUIT_2);
				setNJugadors(m_nJugadors, m_sWidth, m_sHeigth, m_circuit.getDistance());
			}
			break;
		case C3:
			if (m_circuit.GetCurrCircuit() != CIRCUIT_3)
			{
				m_circuit.Load(CIRCUIT_3);
				setNJugadors(m_nJugadors, m_sWidth, m_sHeigth, m_circuit.getDistance());
			}
			break;
		case C4:

			if (m_circuit.GetCurrCircuit() != CIRCUIT_4)
			{
				m_circuit.Load(CIRCUIT_4);
				setNJugadors(m_nJugadors, m_sWidth, m_sHeigth, m_circuit.getDistance());
			}

			break;
		case NEXT:

			m_circuit.SetRotation(Vector3(0, 0, 0));
			m_buttonsSelec[b].Unselect();
			m_circuit.LoadPowerUps();
			m_currScreen = GAMEPLAY;

			break;
		default:
			break;
		}
	}
}

void PracticaCotxe::OnButtonClickFI(int x, int y)
{
	if (m_buttonsFI[EXITF].IsClicked(x, y)) {
		Reset();
		m_circuit.UnsetPowerUps();
		m_currScreen = INICI;
	}
}

void PracticaCotxe::Draw(/*CColor col_object, bool ref_mat, bool sw_mat[4]*/)
{
	// Assignació de les variables de color i reflexió als valors de les variables per paràmetre
	//color_objecte = col_object;
	//reflexio_material = ref_mat;
	//for (int i = 0; i < 4; i++) sw_materials[i] = sw_mat[i];
	glColor4f(1, 1, 1, 1);

#ifndef PC_DEVELOP
	// CAMARA ----------------------------------------------------------------------------
	// Neteja dels buffers de color i profunditat
	CColor col_fons;
	col_fons.r = 0;
	col_fons.g = 0;
	col_fons.b = 0;
	col_fons.a = 1;
	glViewport(0, 0, m_sWidth, m_sHeigth);
	Fons(col_fons);

	/*Fons(col_fons);*/
	Vector3 cameraPosition;

	switch (m_currScreen)
	{
	case INICI:
		cameraPosition = Vector3(0, 250, 500);
		//glViewport(0, 0, m_sWidth, m_sHeigth);
		//Fons(col_fons);
		glLoadIdentity();
		gluLookAt(cameraPosition.X(), cameraPosition.Y(), cameraPosition.Z(), 0, 0, 0, 0, 1, 0);
		break;
	case SELECCIO:
		cameraPosition = Vector3(0, 250, 500);
		//glViewport(0, 0, m_sWidth, m_sHeigth);
		//Fons(col_fons);

		glLoadIdentity();
		gluLookAt(cameraPosition.X() - 1400, cameraPosition.Y() + 700, cameraPosition.Z(), 0, 0, 0, 0, 1, 0);

		Iluminacio(GOURAUD, true, 'a');
		DrawRec(&m_mainObj);
		break;
	case GAMEPLAY:
		glEnable(GL_SCISSOR_TEST);
		for (int i = 0; i < m_nJugadors; i++) {
			cameraPosition = m_cars[i].GetPosition();
			cameraPosition -= Vector3(m_cars[i].GetDirection().X() * 60, m_cars[i].GetDirection().Y() * 25, m_cars[i].GetDirection().Z() * 60);
			cameraPosition += Vector3(0, 35, 0);

			//Projeccio_Perspectiva(m_w[i][0], m_h[i][0], m_w[i][1], m_h[i][1], 75);
			glViewport(m_w[i][0], m_h[i][0], m_w[i][1], m_h[i][1]);
			glScissor(m_w[i][0], m_h[i][0], m_w[i][1], m_h[i][1]);
			Fons(col_fons);

			glLoadIdentity();
			gluLookAt(cameraPosition.X(), cameraPosition.Y(), cameraPosition.Z(), m_cars[i].GetPosition().X(), m_cars[i].GetPosition().Y() + 20, m_cars[i].GetPosition().Z(), 0, 1, 0);
			// Iluminacio fixe respecte la camara (després glLookAt)
			Iluminacio(GOURAUD, true, 'a');
			DrawRec(&m_mainObj);
		}
		glDisable(GL_SCISSOR_TEST);
		break;

	case FI:
		cameraPosition = Vector3(0, 250, 500);
		glViewport(0, 0, m_sWidth, m_sHeigth);
		Fons(col_fons);

		glLoadIdentity();
		gluLookAt(cameraPosition.X(), cameraPosition.Y(), cameraPosition.Z(), 0, 0, 0, 0, 1, 0);

		Iluminacio(GOURAUD, true, 'a');
		DrawRec(&m_mainObj);
		break;

	default:
		break;
	}

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
	DrawRec(&m_mainObj);
	// Dibuix dels eixos
	glCallList(EIXOS);
#endif

	// Dibuixa PoweUP
	//PowerUp pw;

	//pw.Init(TXT_BOOST);
	//pw.Draw();

	// Enviar les comandes gràfiques a pantalla
	glFlush();

}

void PracticaCotxe::DrawInterface(int w, int h)
{
	glColor3f(1, 1, 1);

	glDisable(GL_TEXTURE_2D);
	GLfloat ambientgi[] = { 1,1,1,1 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientgi);

	switch (m_currScreen)
	{
	case INICI:
		glViewport(0, 0, w, h);
		DrawUIElement(TXT_TITLE, w/2, h /2 - 200, 400, 200);
		
		for(int i=0; i<BUTTONS_INICI; i++)
		{
			m_buttonsInici[i].Draw();
		}

		DrawUIElement({ 1, 0.7f, 0.9f, 1.0f }, w / 2, h / 2, w, h);

		break;

	case SELECCIO:
		glViewport(0, 0, w, h);
		// TODO: Dibuixar etiquetes Circuit i Jugadors
		DrawUIElement(TXT_PLAYERS, 150, 100, 200, 75);
		DrawUIElement(TXT_CIRCUIT, 150, h - 100, 200, 75);

		for (int i = 0; i < BUTTONS_SELEC; i++)
		{
			m_buttonsSelec[i].Draw();
		}

		break;
	case GAMEPLAY:
		if (m_isPaused)
		{
			glViewport(0, 0, w, h);
			DrawUIElement(TXT_PAUSA, w / 2, (h / 2), 250, 75);
			DrawUIElement({ 0.2f, 0.2f, 0.2f, 0.6f }, w / 2, h / 2, w, h);
			// DRAW exit button

			// TODO: Dibuixar text pausa
		}

		// TODO: Dibuixar botons per cada jugador (accions restants i voltes que porten (les voltes encara no les feu))
		glEnable(GL_SCISSOR_TEST);
		for (int i = 0; i < m_nJugadors; i++)
		{
			glViewport(m_w[i][0], m_h[i][0], m_w[i][1], m_h[i][1]);
			glScissor(m_w[i][0], m_h[i][0], m_w[i][1], m_h[i][1]);

			for (int j = 0; j < m_cars[i].getBoosts(); j++)
			{
				DrawUIElement(TXT_BOOST, 60, 60 + (80+10)*j, 80, 80);

			}
			int nL = m_cars[i].getLaps();
			if (nL >= MAX_LAPS) nL = MAX_LAPS - 1;

			if (m_nJugadors == 1) {

				DrawUIElement(TXT_LAP + nL, m_w[i][1] / 2, 80, 100, 100);

			} else {

				DrawUIElement(TXT_LAP + nL, m_w[i][1], 80, 100, 100);

			}

		}
		glDisable(GL_SCISSOR_TEST);
		break;

	case FI:
		glViewport(0, 0, w, h);
		// TODO: Dibuixar etiquetes Circuit i Jugadors
		DrawUIElement(TXT_FI, w / 2, (h / 2) - 75, 675, 75);
		DrawUIElement(TXT_FI + m_guanyador, w / 2, (h / 2) + 75, 75, 75);

		m_buttonsSelec[8].Draw();

		break;

	default:
		break;
	}

	GLfloat ambientg[] = { .5,.5,.5,1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientg);
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

	switch (nChar) 
	{
	case PAUSE:

		if (m_currScreen == GAMEPLAY)
		{
			// Pause només funciona a gameplay screen
			m_isPaused = !m_isPaused;

		}

		break;

	case MUSIC:

		m_music.toggle();

		break;

		/*case DAV[0]:
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

		//m_car.Translate(Vector3(0, 0, -1));

		break;


		case DRT:

		//m_car.Translate(Vector3(0, 0, 1));

		break;*/


	case ESP:

		for (int i = 0; i < m_nJugadors; i++) {

			m_cars[i].ResetProgress();

		}

		break;

	default:

		if (m_currScreen == GAMEPLAY && !m_isPaused)
		{
			int i = 0;
			while (i < m_nJugadors && DAV[i] != nChar) i++;

			if (i != m_nJugadors) {

				// El jugador i ha apretat la tecla cap endavant
				m_cars[i].Boost();

			}

			i = 0;
			while (i < m_nJugadors && DAR[i] != nChar) i++;

			if (i != m_nJugadors) {

				// El jugador i ha apretat la tecla cap endarrere
				m_cars[i].Brake();

			}
		}

		break;

	}

}

void PracticaCotxe::Update()
{
	switch (m_currScreen)
	{
	case INICI:
		m_circuit.SetRotation(Vector3(0, 0, 0));
		break;
	case SELECCIO:
		m_circuit.Rotate(Vector3(m_circuitRotation, 0, 0));

		break;
	case GAMEPLAY:

		if (!m_isPaused)
		{
			Vector3 dir, pos;

			m_circuit.UpdatePowerUps();

			for (int i = 0; i < m_nJugadors; i++)
			{
				m_circuit.CalcDirPos(m_cars[i].GetProgress(), i, dir, pos);
				m_cars[i].Move(pos, dir);
				bool PUColission = m_circuit.GetPUColission(m_cars[i].GetPosition(), i);

				if (PUColission) {

					if (m_cars[i].CheckPU()) {

						m_cars[i].AddBoost();

					} else {

						m_cars[i].UpdatePU();

					}

				} else {

					m_cars[i].UpdatePU();

				}

				if (m_cars[i].getLaps() >= MAX_LAPS) {

					m_isEnd = true;
					m_music.stop();
					m_guanyador = i + 1;
					m_currScreen = FI;

				}
			}

			if (m_isEnd) {

				for (int i = 0; i < m_nJugadors; i++) {

					m_cars[i].ResetLaps();
				
				}
			
			}

		}
		else
		{

		}

		break;

	case FI:


		break;

	default:
		break;
	}
}

void PracticaCotxe::InitJugadors(int w, int h) {

	m_nJugadors = 1;

	if (m_nJugadors == 1) { // For SOLO mode

		// Inici
		m_w[0][0] = 0;
		m_h[0][0] = 0;

		// Fi
		m_w[0][1] = w;
		m_h[0][1] = h;

	}

	// MAX_JUGADORS -> m_nJugadors
	m_cars = new Car[MAX_JUGADORS];

	for (int i = 0; i < MAX_JUGADORS; i++) {

		m_cars[i].Init(4, Vector3(0, 0, 0), Vector3().Zero(), Vector3().One());

		m_cars[i].SetBody(OBJ_CAR+i, -1, Vector3().Zero(), Vector3().Zero(), Vector3().One());

		m_cars[i].SetWheel(0, OBJ_WHEEL, -1, Vector3(14.0f, 0.0f, 7.0f), Vector3().Zero(), Vector3(1, 1, 1));
		m_cars[i].SetWheel(1, OBJ_WHEEL, -1, Vector3(14.0f, 0.0f, -7.0f), Vector3().Zero(), Vector3(1, 1, -1.0f));
		m_cars[i].SetWheel(2, OBJ_WHEEL, -1, Vector3(-14.0f, 0.0f, 7.0f), Vector3().Zero(), Vector3(1, 1, 1));
		m_cars[i].SetWheel(3, OBJ_WHEEL, -1, Vector3(-14.0f, 0.0f, -7.0f), Vector3().Zero(), Vector3(1, 1, -1.0f));

		m_circuit.SetChild(i, &m_cars[i]);
	}

	//// Situar cotxes a posicio de sortida
	//Update();
}

void PracticaCotxe::Reset()
{
	m_circuit.Load(CIRCUIT_1);
	setNJugadors(1, m_sWidth, m_sHeigth, m_circuit.getDistance());
	for (int i = 0; i < BUTTONS_SELEC; i++) {

		m_buttonsSelec[i].Unselect();

	}

	m_buttonsSelec[C1].Select();
	m_buttonsSelec[P1].Select();
}

void PracticaCotxe::setNJugadors(int nJugadors, int w, int h, float dist)
{
	m_nJugadors = nJugadors;
	m_circuit.SetCarrils(nJugadors);

	if (nJugadors == 1) { // For SOLO mode

							// Inici
		m_w[0][0] = 0;
		m_h[0][0] = 0;

		// Fi
		m_w[0][1] = w;
		m_h[0][1] = h;

	}
	else if (nJugadors == 2) { // For 2 players

		// Player 1 ==================
		// Inici
		m_w[0][0] = 0;
		m_h[0][0] = h / 4;

		// Fi
		m_w[0][1] = w / 2;
		m_h[0][1] = h / 2;

		// ===========================

		// Player 2 ==================

		// Inici
		m_w[1][0] = w / 2;
		m_h[1][0] = h / 4;

		// Fi
		m_w[1][1] = w / 2;
		m_h[1][1] = h / 2;

		// ===========================

	}
	else { //For 3 or 4 players

		// Player 1 ==================

		// Inici
		m_w[2][0] = 0;
		m_h[2][0] = 0;

		// Fi
		m_w[2][1] = w / 2;
		m_h[2][1] = h / 2;

		// ===========================

		// Player 2 ==================

		// Inici
		m_w[3][0] = w / 2;
		m_h[3][0] = 0;

		// Fi
		m_w[3][1] = w / 2;
		m_h[3][1] = h / 2;

		// ===========================

		// Player 3 ==================

		// Inici
		m_w[0][0] = 0;
		m_h[0][0] = h / 2;

		// Fi
		m_w[0][1] = w / 2;
		m_h[0][1] = h / 2;

		// ===========================

		// Player 4 ==================

		// Inici
		m_w[1][0] = w / 2;
		m_h[1][0] = h / 2;

		// Fi
		m_w[1][1] = w / 2;
		m_h[1][1] = h / 2;

		// ===========================

	}

	for (int i = 0; i < MAX_JUGADORS; i++) {
		m_cars[i].SetMoveValues(dist);
	}

	// Situar cotxes a posicio de sortida
	Vector3 dir, pos;
	for (int i = 0; i < MAX_JUGADORS; i++)
	{
		m_cars[i].SetActive(i < m_nJugadors);
		m_circuit.CalcDirPos(m_cars[i].GetProgress(), i, dir, pos);
		m_cars[i].Move(pos, dir);

		if (m_cars[i].getLaps() >= MAX_LAPS) {

			m_isPaused = true;
			m_music.stop();
			m_guanyador = i + 1;

		}
	}
}

SCREENS PracticaCotxe::GetCurrScreen()
{
	return m_currScreen;
}
