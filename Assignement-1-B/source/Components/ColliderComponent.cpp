#include "../../include/components/ColliderComponent.h"

void ColliderComponent::setBoundingBoxLocation(Vector2f position)
{
	boundingBox.setTopLeft(position);
	boundingBox.setBottomRight(Vector2f((position.x + bboxSize.x), (position.y + bboxSize.y)));
}

const Vector2f& ColliderComponent::getBboxSize() const
{
	return bboxSize;
}
