#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "scatteredcirclebrush.h"
#include <cmath>
extern float frand();

ScatteredCircleBrush::ScatteredCircleBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)
{
}

void ScatteredCircleBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	int size = pDoc->getSize();


	BrushMove(source, target);
}

void ScatteredCircleBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;
	int size = pDoc->getSize();
	int n = 40;
	double R = size / 2;

	for (int i = 0; i < 4; i++)
	{
		int xr = rand() % size;
		int yr = rand() % size;
		int newx = target.x;
		int newy = target.y;
		Point newp(source.x + xr - size / 2, source.y + yr - size / 2);

		glBegin(GL_POLYGON);
		SetColor(newp);
		for (int i = 0; i < n; i++)
		{
			glVertex2d(newp.x + R * cos(2 * M_PI * i / n), newp.y + R * sin(2 * M_PI * i / n));
		}
		glEnd();
	}
}

void ScatteredCircleBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}


void ScatteredCircleBrush::rightMouseMovementBegin(const Point source, const Point target)
{
	glLineWidth(1);
	originPoint = source;
}

void ScatteredCircleBrush::rightMouseMovementMove(const Point source, const Point target)
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

void ScatteredCircleBrush::rightMouseMovementEnd(const Point source, const Point target)
{
	// do nothing so far
}