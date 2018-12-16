#pragma once
#include "OGLObject.h"
#include "Spline.h"
#include "Vector3.h"

enum Circuits {CIRCUIT_1 = 0, CIRCUIT_2 = 1, CIRCUIT_3 = 2, CIRCUIT_4 = 3, DONUT_PUJADA = 4, CIRCUIT_6 = 5};

class Circuit : public OGLObject
{
private:
	const string CircuitsFileNames[6] = { "circuits/c1.txt", "circuits/c2.txt", "circuits/c3.txt", "circuits/c4.txt", "circuits/c5.txt", "circuits/c6.txt" };
	const int CircuitsResolutions[6] = { 50, 100, 30, 150, 70, 20};
	const int CarrilWidth = 40;

	Circuits m_index;
	int m_carrils;
	Spline m_spline;

	void m_GenRoadTexture();
	GLubyte m_roadImg[8][8][4];
	GLuint m_roadTextureId = -1;

public:
	Circuit() : m_carrils(3), OGLObject() {};
	~Circuit();
	
	void Init(int carrils);

	Vector3 CalcPosition(float f);
	Vector3 CalcDirection(float f);
	void CalcDirPos(float f, int c, Vector3 & direction, Vector3 & position);
	Circuits GetCurrCircuit();
	void SetCarrils(int c);
	
	void Load(Circuits c);

	float getDistance();

	void Draw();
};

