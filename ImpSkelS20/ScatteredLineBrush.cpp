#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "scatteredLineBrush.h"
#include "math.h"
#include "time.h"

extern float frand();

ScatteredLineBrush::ScatteredLineBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)
{
}

void ScatteredLineBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;
	if (strokeDirectionType == BRUSH_DIRECTION)
	{
		originPoint = source;
	}
	BrushMove(source, target);
}

void ScatteredLineBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;
	int size = pDoc->getSize();
	int width = pDoc->getWidth();
	int angle = pDoc->getAngle();
	float r = size / 2;
	float an = 2 * M_PI * angle / 360;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	for (int i = 0; i < 4; i++)
	{
		int xr = rand() % size;
		int yr = rand() % size;
		int newx = target.x;
		int newy = target.y;
		Point newp(source.x + xr - size / 2, source.y + yr - size / 2);
		r = (rand() % size/2 + 1);
		double RGBPX1 = 0;
		double RGBPY1 = 0;
		double RGBPX2 = 0;
		double RGBPY2 = 0;
		double newAngle = 0;
		Point pX1(newp.x - 1, newp.y);
		Point pY1(newp.x, newp.y - 1);
		Point pX2(newp.x + 1, newp.y);
		Point pY2(newp.x, newp.y + 1);
		GLubyte* colorPX1 = pDoc->GetOriginalPixel(pX1);
		GLubyte* colorPY1 = pDoc->GetOriginalPixel(pY1);
		GLubyte* colorPX2 = pDoc->GetOriginalPixel(pX2);
		GLubyte* colorPY2 = pDoc->GetOriginalPixel(pY2);
		
		switch (strokeDirectionType)
		{
		case SRM:
			glLineWidth((float)width);
			glBegin(GL_LINES);
			SetColor(newp);
			glVertex2d(newp.x + r * cos(an), newp.y + r * sin(an));
			glVertex2d(newp.x - r * cos(an), newp.y - r * sin(an));
			glEnd();
			break;
		case GRADIENT:
			glLineWidth((float)width);
			glBegin(GL_LINES);
			SetColor(newp);
			RGBPX1 = (colorPX1[0] * 0.299 + colorPX1[1] * 0.587 + colorPX1[2] * 0.144);
			RGBPY1 = (colorPY1[0] * 0.299 + colorPY1[1] * 0.587 + colorPY1[2] * 0.144);
			RGBPX2 = (colorPX2[0] * 0.299 + colorPX2[1] * 0.587 + colorPX2[2] * 0.144);
			RGBPY2 = (colorPY2[0] * 0.299 + colorPY2[1] * 0.587 + colorPY2[2] * 0.144);
			newAngle = atan2((RGBPY2 - RGBPY1), (RGBPX2 - RGBPX1));
			glVertex2d(newp.x + r * cos(newAngle), newp.y + r * sin(newAngle));
			glVertex2d(newp.x - r * cos(newAngle), newp.y - r * sin(newAngle));
			glEnd();
			break;
		case BRUSH_DIRECTION:
			if(!((source.y - originPoint.y == 0) && (source.x - originPoint.x == 0)))
			{
				float angle = atan2((float)(source.y - originPoint.y), (float)(source.x - originPoint.x));
				glLineWidth((float)width);
				glBegin(GL_LINES);
				SetColor(newp);
				glVertex2d(newp.x + r * cos(angle), newp.y + r * sin(angle));
				glVertex2d(newp.x - r * cos(angle), newp.y - r * sin(angle));
				glEnd();
			}
			break;
		}
	}
	originPoint = source;
}

void ScatteredLineBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}


void ScatteredLineBrush::rightMouseMovementBegin(const Point source, const Point target)
{
	glLineWidth(1);
	originPoint = source;
}

void ScatteredLineBrush::rightMouseMovementMove(const Point source, const Point target)
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

void ScatteredLineBrush::rightMouseMovementEnd(const Point source, const Point target)
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