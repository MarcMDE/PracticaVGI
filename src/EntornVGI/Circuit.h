#pragma once
#include "OGLObject.h"
#include "Spline.h"
#include "Vector3.h"

enum Circuits {CIRCUIT_1 = 0, CIRCUIT_2 = 1, CERCLE = 2, CIRCUIT_4 = 3, DONUT_PUJADA = 4};

class Circuit : public OGLObject
{
private:
	const string CircuitsFileNames[5] = { "circuits/c1.txt", "circuits/c2.txt", "circuits/c3.txt", "circuits/c4.txt", "circuits/c5.txt" };
	const int CircuitsResolutions[5] = { 50, 100, 30, 100, 70};
	const int CarrilWidth = 30;

	Circuits m_index;
	int m_carrils;
	Spline m_spline;

	void m_GenRoadTexture();
	GLubyte m_roadImg[8][8][4];
	GLuint m_roadTextureId = -1;

public:
	Circuit() : m_carrils(1), OGLObject() {};
	Circuit(int carrils) : m_carrils(carrils), OGLObject() {};
	~Circuit();
	
	void Init();

	Vector3 CalcPosition(float f);
	Vector3 CalcDirection(float f);
	void CalcDirPos(float f, Vector3 & direction, Vector3 & position);
	
	void Load(Circuits c);

	void Draw();
};

