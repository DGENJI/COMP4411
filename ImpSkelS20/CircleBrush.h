#ifndef CIRCLEBRUSH_H
#define CIRCLEBRUSH_H

#include "ImpBrush.h"

class CircleBrush : public ImpBrush
{
public:
	CircleBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);
	void rightMouseMovementBegin(const Point source, const Point target);
	void rightMouseMovementMove(const Point source, const Point target);
	void rightMouseMovementEnd(const Point source, const Point target);
	char* BrushName(void);
};

#endif