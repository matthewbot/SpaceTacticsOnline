#include "ThrusterComponent.h"
#include <STO/shared/position/PositionComponent.h>
#include <STO/shared/motion/MotionComponent.h>
#include <STO/shared/serial/DataVisitor.h>
#include <algorithm>
#include <cmath>
#include <iostream>

using namespace sto;
using namespace mge;
using namespace std;

ThrusterComponent::ThrusterComponent(MotionComponent &mot, const ThrusterStats &stats)
: mot(mot), stats(stats), speed(ThrusterStats::CRUISE) { }

static const int ROTCYCLES=3;

void ThrusterComponent::tick(float tdelta) {
	for (int i=0; i < ROTCYCLES; i++) { // helps rotation precision, prevents overshooting when rotating
		doRotation(tdelta/ROTCYCLES);
	}
	doSpeed(tdelta);
}

void ThrusterComponent::doRotation(float tdelta) {
	ThrusterStats::SpeedStat &stat = stats.stat[speed];

	float rotspeed = mot.getRotSpeed();

	float braketime = fabs(rotspeed / stat.rotbrake);
	float remaining = destdir - mot.getPositionComponent().getRotation();

	if (remaining > PI)
		remaining -= 2*PI;
	else if (remaining < -PI)
		remaining += 2*PI;

	if (remaining > 0) {
		float brakeamt = rotspeed*braketime - .5f*stat.rotbrake*braketime*braketime;

		if (brakeamt > remaining-0.05f) {
			rotspeed = max(rotspeed - stat.rotbrake*tdelta, 0.0f);
		} else {
			rotspeed = min(rotspeed + stat.rotaccel*tdelta, stat.rotmaxspeed);
		}
	} else if (remaining < 0) {
		float brakeamt = rotspeed*braketime + .5f*stat.rotbrake*braketime*braketime;

		if (brakeamt < remaining+0.05f) {
			rotspeed = min(rotspeed + stat.rotbrake*tdelta, 0.0f);
		} else {
			rotspeed = max(rotspeed - stat.rotaccel*tdelta, -stat.rotmaxspeed);
		}
	}
	
	mot.setRotSpeed(rotspeed);
}

void ThrusterComponent::doSpeed(float tdelta) {
	Vector2D newmotion;
	const Vector2D &curmotion = mot.getMotion();
	ThrusterStats::SpeedStat &stat = stats.stat[speed];	

	float magnitude = curmotion.getMagnitude();

	if (magnitude <= stat.maxspeed) {
		newmotion = curmotion + Vector2D::fromAngle(mot.getPositionComponent().getRotation(), stat.accel*tdelta);
		if (newmotion.getMagnitude() > stat.maxspeed)
			newmotion.setMagnitude(stat.maxspeed);
	} else {
		newmotion = curmotion;
		newmotion.setMagnitude(newmotion.getMagnitude() - stat.brake*tdelta);
	}
	
	mot.setMotion(newmotion);
}

void ThrusterComponent::visitData(DataVisitor &v) {
	v.visit(destdir, 4);
	v.visit((char &)speed);
}
