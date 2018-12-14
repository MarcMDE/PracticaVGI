#include "stdafx.h"
#include "PracticaCotxe.h"


void PracticaCotxe::glTranslateV(const Vector3 & v)
{
	glTranslatef(v.X(), v.Y(), v.Z());
}

void PracticaCotxe::glRotateV(const Vector3 & v)
{
	glRotatef(v.X() * RAD_TO_DEG, 0, 1, 0);
	//glRotatef(v.Z() * RAD_TO_DEG, 0, 0, 1);
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

	m_isPaused = false;

	m_currScreen = GAMEPLAY;
}

PracticaCotxe::~PracticaCotxe()
{
}

void PracticaCotxe::Init(int w, int h)
{
	m_circuit.Init(4);
	m_circuit.Load(CIRCUIT_2);

	m_mainObj.SetChildsLength(1);
	m_mainObj.SetChild(0, &m_skyBox);

	m_skyBox.SetChildsLength(1);
	m_skyBox.SetChild(0, &m_circuit);


	setNJugadors(4, w, h);
	
	// Musica de fons... es para a 3 segons de reproducció, si prem 2 vegades M es reprodueix be
	m_music.play();

	m_sun.encesa = true;
	m_sun.difusa[0] = 1.0f;		m_sun.difusa[1] = 1.0f;		m_sun.difusa[2] = 1.0f;		m_sun.difusa[3] = 1.0f;
	m_sun.especular[0] = 1.0f;		m_sun.especular[1] = 1.0f;		m_sun.especular[2] = 1.0f;		m_sun.especular[3] = 1.0f;

	m_sun.posicio.R = -300.0;		m_sun.posicio.alfa = 90.0;		m_sun.posicio.beta = 0.0;		// Posició llum (x,y,z)=(0,0,75)
	m_sun.atenuacio.a = 0.0;		m_sun.atenuacio.b = 0.0;		m_sun.atenuacio.c = 1.0;		// Llum sense atenuació per distància (a,b,c)=(0,0,1)
	m_sun.restringida = false;
	m_sun.spotdirection[0] = 0.0;	m_sun.spotdirection[1] = 0.0;	m_sun.spotdirection[2] = 0.0;
	m_sun.cutoff = 0.0;			m_sun.exponent = 0.0;
}

void PracticaCotxe::Iluminacio(char ilumin, bool ifix, bool ll_amb, LLUM lumin, bool textur, bool textur_map, char obj, bool bc_lin, int step)
{      
	//bool ll_amb=true;
	GLfloat angv, angh;

	// Configuració de la font de llum LIGHT0.
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

void PracticaCotxe::DrawUIElement(int texture, int posX, int posY, int width, int heigth)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_QUADS);
	//glColor3f(1.0f, 0.0f, 0.0f); // Red
	glTexCoord2f(1.0, 0.0); glVertex2f(posX+width/2, posY+heigth/2);
	glTexCoord2f(0.0, 0.0); glVertex2f(posX-width/2, posY+heigth/2);
	glTexCoord2f(0.0, 1.0); glVertex2f(posX-width/2, posY-heigth/2);
	glTexCoord2f(1.0, 1.0); glVertex2f(posX+width/2, posY-heigth/2);
	glEnd();
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

void PracticaCotxe::OnButtonClickInici(B_INICI b)
{
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

void PracticaCotxe::OnButtonClickSelec(B_SELEC b)
{
	for (int i = 0; i < BUTTONS_SELEC; i++) m_buttonsSelec[i].Unselect();

	m_buttonsSelec[b].Select();

	switch (b)
	{
	case P1:
		m_nJugadors = 1;
		break;
	case P2:
		m_nJugadors = 2;
		break;
	case P3:
		m_nJugadors = 3;
		break;
	case P4:
		m_nJugadors = 4;
		break;
	case C1:
		if (m_circuit.GetCurrCircuit() != CIRCUIT_1)
		{
			m_circuit.Load(CIRCUIT_1);
		}
		break;
	case C2:
		if (m_circuit.GetCurrCircuit() != CIRCUIT_2)
		{
			m_circuit.Load(CIRCUIT_2);
		}
		break;
	case C3:
		if (m_circuit.GetCurrCircuit() != CIRCUIT_4)
		{
			m_circuit.Load(CIRCUIT_4);
		}
		break;
	case C4:

		if (m_circuit.GetCurrCircuit() != CIRCUIT_6)
		{
			m_circuit.Load(CIRCUIT_6);
		}

		break;
	case NEXT:

		m_buttonsSelec[b].Unselect();
		m_currScreen = GAMEPLAY;

		break;
	default:
		break;
	}
}

void PracticaCotxe::OnButtonClickPause(B_PAUSE b)
{
	switch (b)
	{
	case EXITB:
		m_currScreen = INICI;
		break;
	default:
		break;
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

	/*Fons(col_fons);*/

	for (int i = 0; i < m_nJugadors; i++) {
		Vector3 cameraPosition = m_cars[i].GetPosition();
		cameraPosition -= Vector3(m_cars[i].GetDirection().X() * 60, 0, m_cars[i].GetDirection().Z() * 60);
		cameraPosition += Vector3(0, 35, 0);

		//Projeccio_Perspectiva(m_w[i][0], m_h[i][0], m_w[i][1], m_h[i][1], 75);
		glViewport(m_w[i][0], m_h[i][0], m_w[i][1], m_h[i][1]);
		glScissor(m_w[i][0], m_h[i][0], m_w[i][1], m_h[i][1]);
		Fons(col_fons);

		glLoadIdentity();
		gluLookAt(cameraPosition.X(), cameraPosition.Y(), cameraPosition.Z(), m_cars[i].GetPosition().X(), m_cars[i].GetPosition().Y() + 20, m_cars[i].GetPosition().Z(), 0, 1, 0);
		// Iluminacio fixe respecte la camara (després glLookAt)
		Iluminacio(GOURAUD, true, true, m_sun, true, true, 'a', false, 0);
		DrawRec(&m_mainObj);
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

	//DrawRec(&m_mainObj);

	
	glBindTexture(GL_TEXTURE_2D, TXT_TEST);
	glutSolidCube(10);
	glBegin(GL_QUADS);

		glTexCoord2f(0.0, 0.0); glVertex3f(-2.0, -2.0, 0.0); 
		glTexCoord2f(0.0, 1.0); glVertex3f(-2.0, 2.0, 0.0);
		glTexCoord2f(1.0, 1.0); glVertex3f(2.0, 2.0, 0.0);
		glTexCoord2f(1.0, 0.0); glVertex3f(2.0, -2.0, 0.0);

	glEnd();
	

	// Enviar les comandes gràfiques a pantalla
	glFlush();
}

void PracticaCotxe::DrawInterface(int w, int h)
{

	glDisable(GL_SCISSOR_TEST);
	glViewport(0, 0, w, h);

	glDisable(GL_TEXTURE_2D);
	GLfloat ambientgi[] = { 1,1,1,1 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientgi);

	switch (m_currScreen)
	{
	case INICI:

		// TODO: Dibuixar titol
		//DrawUIElement(TXT_TITLE, w/2, h /2 - 250, 400, 200);
		
		for(int i=0; i<BUTTONS_INICI; i++)
		{
			m_buttonsInici[i].Draw();
		}

		break;
	case SELECCIO:

		// TODO: Dibuixar etiquetes Circuit i Jugadors

		for (int i = 0; i < BUTTONS_SELEC; i++)
		{
			m_buttonsSelec[i].Draw();
		}

		break;
	case GAMEPLAY:
		// TODO: Dibuixar botons per cada jugador (accions restants i voltes que porten (les voltes encara no les feu))

		for (int i = 0; i < BUTTONS_SELEC; i++)
		{
			m_buttonsSelec[i].Draw();
		}

		if (m_isPaused)
		{

			DrawUIElement({ 0.2f, 0.2f, 0.2f, 0.6f }, w / 2, h / 2, w, h);
			// DRAW exit button

			// TODO: Dibuixar text pausa
		}

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

	switch (nChar) {

	case PAUSE:

		if (m_currScreen == GAMEPLAY) {

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

		break;

	}

}

void PracticaCotxe::Update()
{
	switch (m_currScreen)
	{
	case INICI:

		for (int i = 0; i < BUTTONS_INICI; i++)
		{

		}

		break;
	case SELECCIO:



		break;
	case GAMEPLAY:

		if (!m_isPaused)
		{
			Vector3 dir, pos;
			for (int i = 0; i < m_nJugadors; i++)
			{
				m_circuit.CalcDirPos(m_cars[i].GetProgress(), i, dir, pos);
				m_cars[i].Move(pos, dir);
			}
		}
		else
		{

		}

		break;
	default:
		break;
	}
}

void PracticaCotxe::setNJugadors(int nJugadors, int w, int h) {

	if (nJugadors <= MAX_JUGADORS) {

		m_nJugadors = nJugadors;

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
			m_h[0][0] = 0;

			// Fi
			m_w[0][1] = w / 2;
			m_h[0][1] = h / 2;

			// ===========================

			// Player 2 ==================

			// Inici
			m_w[1][0] = w / 2;
			m_h[1][0] = 0;

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

		m_cars = new Car[nJugadors];
		m_circuit.SetChildsLength(m_nJugadors);

		for (int i = 0; i < m_nJugadors; i++) {

			m_cars[i].Init(4, Vector3(0, 0, 0), Vector3().Zero(), Vector3().One());

			m_cars[i].SetBody(OBJ_CAR+i, -1, Vector3().Zero(), Vector3().Zero(), Vector3().One());

			m_cars[i].SetWheel(0, OBJ_WHEEL, -1, Vector3(14.0f, 0.0f, 7.0f), Vector3().Zero(), Vector3(1, 1, 1));
			m_cars[i].SetWheel(1, OBJ_WHEEL, -1, Vector3(14.0f, 0.0f, -7.0f), Vector3().Zero(), Vector3(1, 1, -1.0f));
			m_cars[i].SetWheel(2, OBJ_WHEEL, -1, Vector3(-14.0f, 0.0f, 7.0f), Vector3().Zero(), Vector3(1, 1, 1));
			m_cars[i].SetWheel(3, OBJ_WHEEL, -1, Vector3(-14.0f, 0.0f, -7.0f), Vector3().Zero(), Vector3(1, 1, -1.0f));

			m_circuit.SetChild(i, &m_cars[i]);
		}

		// Situar cotxes a posicio de sortida
		Update();
	}

}
