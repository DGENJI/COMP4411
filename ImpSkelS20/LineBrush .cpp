#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "Linebrush.h"
#include <math.h>
#include <cmath>
#include <iostream>

extern float frand();

LineBrush::LineBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)
{
}

void LineBrush::BrushBegin(const Point source, const Point target)
{
	BrushMove(source, target);
}

void LineBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	int size = pDoc->getSize();
	int width = pDoc->getWidth();
	int angle = pDoc->getAngle();
	float r = size / 2;
	float an = 2 * M_PI * angle / 360;

	glLineWidth((float)width);
	glBegin(GL_LINES);
	SetColor(source);

	//switch (strokeDirectionType)
	//{
	//default:
		glVertex2d(target.x + r * cos(an), target.y + r * sin(an));
		glVertex2d(target.x - r * cos(an), target.y - r * sin(an));
	//	break;
	//}

	glEnd();
}

void LineBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}

void LineBrush::rightMouseMovementBegin(const Point source, const Point target)
{
	glPointSize(1);
	originPoint = source;
}

void LineBrush::rightMouseMovementMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("PointBrush::BrushMove  document is NULL\n");
		return;
	}

	glBegin(GL_LINES);
	glColor3ub(255, 0, 0);

	glVertex2d(originPoint.x, originPoint.y);
	glVertex2d(source.x, source.y);

	glEnd();
}

void LineBrush::rightMouseMovementEnd(const Point source, const Point target)
{
	float angle = atan(((float)(source.y - originPoint.y)) / ((float)(source.x - originPoint.x))) * 180.0f / 3.1415926;
	if (source.x - originPoint.x < 0)
	{
		angle = 180.0 + angle;
	}
	else if(source.y - originPoint.y < 0) {
		angle = 360.0 + angle;
	}
	ImpressionistDoc* pDoc = GetDocument();
	pDoc->setAngle((int)angle);
}

