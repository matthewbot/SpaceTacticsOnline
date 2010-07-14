#include "MotionComponent.h"
#include <STO/shared/position/PositionComponent.h>
#include <STO/shared/serial/DataVisitor.h>
#include <iostream>

using namespace sto;
using namespace mge;
using namespace std;

MotionComponent::MotionComponent(PositionComponent &pos) : pos(pos) { }
MotionComponent::MotionComponent(PositionComponent &pos, float hs, float vs, float rotspeed)
: pos(pos), motion(hs, vs), rotspeed(rotspeed) { }
MotionComponent::MotionComponent(PositionComponent &pos, const mge::Vector2D &motion, float rotspeed)
: pos(pos), motion(motion), rotspeed(rotspeed) { }
MotionComponent::~MotionComponent() { }

void MotionComponent::setMotion(const mge::Vector2D &motion) { this->motion = motion; }

void MotionComponent::tick(float tdelta) {
	pos.setPosition(pos.getPosition() + motion*tdelta);
	pos.setRotation(pos.getRotation() + rotspeed*tdelta);
}

void MotionComponent::visitData(DataVisitor &v) {
	v.visit(motion.getX());
	v.visit(motion.getY());
	v.visit(rotspeed, 3);
}
