#ifndef SPOINTBRUSH_H
#define SPOINTBRUSH_H

#include "ImpBrush.h"

class ScatteredPointBrush : public ImpBrush
{
public:
	ScatteredPointBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);
	void rightMouseMovementBegin(const Point source, const Point target);
	void rightMouseMovementMove(const Point source, const Point target);
	void rightMouseMovementEnd(const Point source, const Point target);
	char* BrushName(void);
};

#endif