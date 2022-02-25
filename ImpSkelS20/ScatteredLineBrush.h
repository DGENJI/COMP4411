#ifndef SLINEBRUSH_H
#define SLINEBRUSH_H

#include "ImpBrush.h"

class ScatteredLineBrush : public ImpBrush
{
public:
	ScatteredLineBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);
	void rightMouseMovementBegin(const Point source, const Point target);
	void rightMouseMovementMove(const Point source, const Point target);
	void rightMouseMovementEnd(const Point source, const Point target);
	char* BrushName(void);
};

#endif