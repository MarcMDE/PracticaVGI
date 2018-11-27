#pragma once
#include "OGLObject.h"
#include "Spline.h"

enum Circuits {CIRCUIT_1 = 1, CIRCUIT_2 = 2};

class Circuit : public OGLObject
{
private:
	const string CircuitsFileNames[2] = { "circuits/c1.txt", "circuits/c2.txt" };
	const int CircuitsResolutions[2] = { 50, 100 };
	const int CarrilWidth = 30;

	Spline m_spline;
	Circuits m_index;
	int m_carrils;

public:
	Circuit() : OGLObject() {};
	Circuit(int carrils);
	~Circuit();
	
	void Load(Circuits c);

	void Draw();
};

