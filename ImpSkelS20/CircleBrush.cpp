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

void CircleBrush::rightMouseMovementBegin(const Point source, const Point target)
{
	glLineWidth(1);
	originPoint = source;
}

void CircleBrush::rightMouseMovementMove(const Point source, const Point target)
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

void CircleBrush::rightMouseMovementEnd(const Point source, const Point target)
{
	// do nothing so far
}