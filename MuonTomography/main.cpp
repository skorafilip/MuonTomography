#include <iostream>
#include <cmath>
#include <random>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

#define e 2.718281828459


class Material {
public:

	double X0;

	double row, col;


	Material(double r, double c, double x0) {
		row=r;
		col = c;
		X0 = x0;
	}

};


class Particle {
public:
	double angle;
	double momentum, mass, velocity;
	double x, y;

	Particle() {
		momentum = 3000;
		mass = 105.658367;
		velocity = 1 / sqrt(1 + mass * mass / momentum / momentum);
		x = 3;
		y = 0;
		angle = 0;
	}


};





int main() {
	//material 6x10 cm, L=10
	//pixel 1x1 cm
	int nrow = 10;
	int ncol = 6;



	//init materials
	vector<vector<Material*>> rows;
	for (int n = 0; n < nrow; n++) {

		vector<Material*> column;
		for (int m = 0; m < ncol; m++) {
			column.push_back(new Material(n,m, 36.1));
		}
		rows.push_back(column);
	}



	//init particle
	Particle particle;



	//move

	random_device rd;
	mt19937 gen(rd());


	for (int n = 0; n < nrow; n++) {

		cout << particle.x << " , " << particle.y << endl;
		cout << particle.angle << endl;
		cout << particle.momentum << endl << endl;


		double row, col;

		double x = particle.x;
		double y = particle.y;

		for (int m = 0; m < ncol; m++) {
			if (x>=m&&x<m+1) {
				col = m;
				break;
			}
		}

		for (int m = 0; m < nrow; m++) {
			if (y >= m && y < m + 1) {
				row = m;
				break;
			}
		}



		//calculating change of angle 

		double LX0 = 1 / rows[row][col]->X0;
		//double beta = velocity;
		double stddev = 13.6  / (particle.velocity*particle.momentum)*sqrt(LX0)*(1 + 0.0038*log(LX0));

		normal_distribution<double> ndist(0, stddev);

		particle.angle += ndist(gen);



		//calculating next x
		double dx = tan(particle.angle);
		if (particle.angle < 0) { dx = -dx; }
		particle.x += dx;
		particle.y += 1;



		//calculating energy drop
		double EnergyDrop = (1 / e) *(LX0)*particle.momentum;
		particle.momentum -= EnergyDrop;

	}

	cout << particle.x << " , " << particle.y << endl;
	cout << particle.angle << endl;
	cout << particle.momentum << endl;




	int confirm;
	cout << "Enter k to close:";
	cin >> confirm;




}


/*
double mom = 3000;
double Drop = (1 / e) *mom;
mom -= Drop;
cout << mom << endl << endl;

double moment = 3000;
for (int i = 0; i < 10; i++) {
	double EnergyDrop = (1 / e) *0.1*moment;
	moment -= EnergyDrop;
	cout << moment << endl << endl;
}



for (int n = 0; n < nrow; n++) {

	for (int m = 0; m < ncol; m++) {
		cout << rows[n][m]->row<<" , "<< rows[n][m]->col <<'\t';
	}
	cout << endl;
}
*/