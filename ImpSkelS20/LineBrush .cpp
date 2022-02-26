#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "Linebrush.h"
#include <math.h>
#include <iostream>
#include <time.h>

extern float frand();

LineBrush::LineBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)
{
}

void LineBrush::BrushBegin(const Point source, const Point target)
{
	if (strokeDirectionType == BRUSH_DIRECTION)
	{
		originPoint = source;
	}
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
	double RGBPX1 = 0;
	double RGBPY1 = 0;
	double RGBPX2 = 0;
	double RGBPY2 = 0;
	double newAngle = 0;
	Point pX1(source.x - 1, source.y);
	Point pY1(source.x, source.y - 1);
	Point pX2(source.x + 1, source.y);
	Point pY2(source.x, source.y + 1);
	GLubyte* colorPX1 = pDoc->GetOriginalPixel(pX1);
	GLubyte* colorPY1 = pDoc->GetOriginalPixel(pY1);
	GLubyte* colorPX2 = pDoc->GetOriginalPixel(pX2);
	GLubyte* colorPY2 = pDoc->GetOriginalPixel(pY2);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	switch (strokeDirectionType)
	{
	case SRM:
		glLineWidth((float)width);
		glBegin(GL_LINES);
		SetColor(source);
		glVertex2d(target.x + r * cos(an), target.y + r * sin(an));
		glVertex2d(target.x - r * cos(an), target.y - r * sin(an));
		glEnd();
		break;
	case GRADIENT:
		glLineWidth((float)width);
		glBegin(GL_LINES);
		SetColor(source);
		RGBPX1 = (colorPX1[0] * 0.299 + colorPX1[1] * 0.587 + colorPX1[2] * 0.114);
		RGBPY1 = (colorPY1[0] * 0.299 + colorPY1[1] * 0.587 + colorPY1[2] * 0.114);
		RGBPX2 = (colorPX2[0] * 0.299 + colorPX2[1] * 0.587 + colorPX2[2] * 0.114);
		RGBPY2 = (colorPY2[0] * 0.299 + colorPY2[1] * 0.587 + colorPY2[2] * 0.114);
		newAngle = atan2((RGBPY2 - RGBPY1), (RGBPX2 - RGBPX1));
		glVertex2d(target.x + r * cos(newAngle), target.y + r * sin(newAngle));
		glVertex2d(target.x - r * cos(newAngle), target.y - r * sin(newAngle));
		glEnd();
		break;
	case BRUSH_DIRECTION:
		float angle = atan2((float)(source.y - originPoint.y), (float)(source.x - originPoint.x));
		glLineWidth((float)width);
		glBegin(GL_LINES);
		SetColor(source);
		glVertex2d(target.x + r * cos(angle), target.y + r * sin(angle));
		glVertex2d(target.x - r * cos(angle), target.y - r * sin(angle));
		glEnd();
		originPoint = source;
		break;
	}
}

void LineBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}

void LineBrush::rightMouseMovementBegin(const Point source, const Point target)
{
	glLineWidth(1);
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
	else if (source.y - originPoint.y < 0) {
		angle = 360.0 + angle;
	}
	ImpressionistDoc* pDoc = GetDocument();
	if (strokeDirectionType == SRM)
	{
		pDoc->setSize((int)sqrt(pow((source.y - originPoint.y), 2) + pow((source.x - originPoint.x), 2)));
		pDoc->setAngle((int)angle);
	}
}

