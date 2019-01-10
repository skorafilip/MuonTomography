#pragma once

#include "MuonTomography.h"

class Particle {
public:
	double angle;
	double momentum, mass, velocity;
	double x, y;

	Particle() {
		momentum = 3000;
		mass = 105.658367;
		velocity = 1 / sqrt(1 + mass * mass / momentum / momentum);
		x = 5;
		y = 0;
		angle = 0;
	}

	Particle(double momentum, double angle, double x, double y) {
		this->momentum = momentum;
		this->x = x;
		this->y = y;
		this->angle = angle;


		mass = 105.658367;
		velocity = 1 / sqrt(1 + mass * mass / momentum / momentum);

	}



};
