#include "PositionComponent.h"
#include <STO/shared/serial/DataVisitor.h>

using namespace sto;
using namespace mge;

PositionComponent::PositionComponent() : parentpos(0) { }
PositionComponent::PositionComponent(float x, float y, float rot, PositionComponent *parentpos)
: parentpos(parentpos), pos(x, y), rot(rot) { }
PositionComponent::~PositionComponent() { }

const mge::Vector2D PositionComponent::getPosition() const {
	if (parentpos)
		return parentpos->pos + pos;
	else
		return pos;
}

float PositionComponent::getX() const {
	if (parentpos)
		return parentpos->pos.getX() + pos.getX();
	else
		return pos.getX();
}

float PositionComponent::getY() const {
	if (parentpos)
		return parentpos->pos.getY() + pos.getY();
	else
		return pos.getY();
}

float PositionComponent::getRotation() const {
	if (parentpos)
		return parentpos->rot + rot;
	else
		return rot;
}

void PositionComponent::setPosition(const Vector2D &pos) {
	this->pos = pos;
}

void PositionComponent::setRotation(float rot) {
	static const float TWOPI = 2*PI;
	
	while (rot >= TWOPI)
		rot -= TWOPI;
		
	while (rot < 0)
		rot += TWOPI;
		
	this->rot = rot;
}

void PositionComponent::visitData(DataVisitor &v) {
	v.visit(pos.getX());
	v.visit(pos.getY());
	v.visit(rot, 4);
}
