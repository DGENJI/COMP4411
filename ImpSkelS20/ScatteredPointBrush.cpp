#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "scatteredpointbrush.h"

extern float frand();

ScatteredPointBrush::ScatteredPointBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)
{
}

void ScatteredPointBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	int size = pDoc->getSize();



	glPointSize(1);

	BrushMove(source, target);
}

void ScatteredPointBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;
	int size = pDoc->getSize();
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	for (int i = 0; i < size*4; i++)
	{
		int xr = rand() % size;
		int yr = rand() % size;
		int newx = target.x;
		int newy = target.y;
		Point newp(source.x + xr - size / 2, source.y + yr - size / 2);

		glBegin(GL_POINTS);
		SetColor(newp);

		glVertex2d(newp.x, newp.y);

		glEnd();
	}
}

void ScatteredPointBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}


void ScatteredPointBrush::rightMouseMovementBegin(const Point source, const Point target)
{
	glLineWidth(1);
	originPoint = source;
}

void ScatteredPointBrush::rightMouseMovementMove(const Point source, const Point target)
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

void ScatteredPointBrush::rightMouseMovementEnd(const Point source, const Point target)
{
	// do nothing so far
}