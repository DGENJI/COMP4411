#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "CircleBrush.h"
#include <cmath>

extern float frand();

CircleBrush::CircleBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)
{
}

void CircleBrush::BrushBegin(const Point source, const Point target)
{
	BrushMove(source, target);
}

void CircleBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	int size = pDoc->getSize();
	int n = 40;
	double R = size / 2;
	glBegin(GL_POLYGON);
	SetColor(source);
	for (int i = 0; i < n; i++)
	{
		glVertex2d(target.x + R * cos(2 * M_PI * i / n), target.y + R * sin(2 * M_PI * i / n));
	}
	glEnd();
}

void CircleBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}