#pragma once
#include "transformableobject.h"
class Vertex :
	public TransformableObject
{
public:
	Vertex(void);
	Vertex(const Vertex & v);
	Vertex(const Point & p);
	~Vertex(void);

	Vertex & operator=(const Vertex & v);

	void draw();
};

