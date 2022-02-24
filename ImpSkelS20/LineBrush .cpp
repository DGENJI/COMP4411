#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "Linebrush.h"
#include <cmath>

extern float frand();

LineBrush::LineBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)
{
}

void LineBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	int size = pDoc->getSize();
	int width = pDoc->getWidth();
	int angle = pDoc->getAngle();



	BrushMove(source, target);
}

void LineBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	int size = pDoc->getSize();
	int width = pDoc->getWidth();
	int angle = pDoc->getAngle();
	double r = size / 2;
	double an = 2 * M_PI * angle / 360;

	glLineWidth((float)width);
	glBegin(GL_LINES);
	SetColor(source);

	glVertex2d(target.x + r * cos(an), target.y + r * sin(an));
	glVertex2d(target.x - r * cos(an), target.y - r * sin(an));

	glEnd();
}

void LineBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}
