#include "GameFramework/Component.h"

struct Rect;
struct Circle;

struct CollisonAlgoritm
{
	static bool checkBoxBoxIntersection(const Rect& rect1, const Rect& rect2);
	static bool checkBoxCircleIntersection(const Rect& rect, const Circle& circle);
	static bool checkCircleCircleIntersection(const Circle& circle1, const Circle& circle2);
};

