#pragma once
#include "OGLObject.h"
#include "Spline.h"
#include "Vector3.h"

enum Circuits {CIRCUIT_1 = 1, CIRCUIT_2 = 2};

class Circuit : public OGLObject, public Spline
{
private:
	const string CircuitsFileNames[2] = { "circuits/c1.txt", "circuits/c2.txt" };
	const int CircuitsResolutions[2] = { 50, 100 };
	const int CarrilWidth = 30;

	Circuits m_index;
	int m_carrils;

public:
	Circuit() : m_carrils(1), OGLObject() {};
	Circuit(int carrils) : m_carrils(carrils), OGLObject() {};
	~Circuit();
	
	void Load(Circuits c);

	void Draw() const;
};
