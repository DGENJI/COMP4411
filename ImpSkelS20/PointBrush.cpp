//
// PointBrush.cpp
//
// The implementation of Point Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "pointbrush.h"

extern float frand();

PointBrush::PointBrush( ImpressionistDoc* pDoc, char* name ) :
	ImpBrush(pDoc,name)
{
}

void PointBrush::BrushBegin( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	int size = pDoc->getSize();



	glPointSize( (float)size );

	BrushMove( source, target );
}

void PointBrush::BrushMove( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	if ( pDoc == NULL ) {
		printf( "PointBrush::BrushMove  document is NULL\n" );
		return;
	}

	glBegin( GL_POINTS );
		SetColor( source );

		glVertex2d( target.x, target.y );

	glEnd();
}

void PointBrush::BrushEnd( const Point source, const Point target )
{
	// do nothing so far
}

void PointBrush::rightMouseMovementBegin(const Point source, const Point target)
{
	glLineWidth(1);
	originPoint = source;
}

void PointBrush::rightMouseMovementMove(const Point source, const Point target)
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

void PointBrush::rightMouseMovementEnd(const Point source, const Point target)
{
	// do nothing so far
}