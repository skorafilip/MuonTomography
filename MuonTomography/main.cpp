#include "Material.h"
#include "Particle.h"
#include "MuonTomography.h"

void move(vector<vector<Material*>> rows, Particle* particle);


void start_test(vector<vector<Material*>> rows, int nparticles) {
	ofstream writeOF;
	writeOF.open("outputfile.dat");
	//srand(time(NULL));
	//(double)(rand() % 10000) / 1000
	//int  xx = 0;
	for (int p = 0; p < nparticles; p++) {
		//init particle
		double xx = fmod((double)((100 * p / (double)nparticles)),10);
		Particle* particle = new Particle(3000, 0, xx, 0);
		double x1 = particle->x;
		double a1 = particle->angle;

		move(rows, particle);


		double x2 = particle->x;
		double a2 = particle->angle;


		//counting cross point
		double x = (sin(a1)*(x2*cos(a2) - x1 * cos(a2) - 10 * sin(a2))) / (sin(a1)*cos(a2) - sin(a2)*cos(a1)) + x1;
		double y = (cos(a1)*(x2*cos(a2) - x1 * cos(a2) - 10 * sin(a2))) / (sin(a1)*cos(a2) - sin(a2)*cos(a1));
		writeOF << x << '\t' << y << endl;

	}

	writeOF.close();

}

void move(vector<vector<Material*>> rows, Particle* particle) {
	random_device rd;
	mt19937 gen(rd());
	for (int n = 0; n < rows.size(); n++) {

		int row = 0;
		int col = 0;

		double x = particle->x;
		double y = particle->y;

		//box checkers
		for (int m = 0; m < rows[0].size(); m++) {
			if (x >= m && x < m + 1) {
				col = m;
				break;
			}
		}

		for (int m = 0; m < rows.size(); m++) {
			if (y >= m && y < m + 1) {
				row = m;
				break;
			}
		}



		//compute_angle
		double LX0 = 1 / rows[row][col]->X0;
		double stddev = 13.6 / (particle->velocity*particle->momentum)*sqrt(LX0)*(1 + 0.0038*log(LX0));

		normal_distribution<double> ndist(0, stddev);
		double value = ndist(gen);
		particle->angle += value;




		//calculating next x
		double dx = tan(particle->angle);
		particle->x += dx;
		particle->y += 1;



		//calculating energy drop
		double EnergyDrop = (1 / e) *(LX0)*particle->momentum;
		particle->momentum -= EnergyDrop;

	}

}


vector<vector<Material*>> init_material(double width, double length) {

	vector<vector<Material*>> rows;
	for (int n = 0; n < length; n++) {

		vector<Material*> column;
		for (int m = 0; m < width; m++) {
			if (m > 5) {
				column.push_back(new Material(n, m, 10000000));

			}
			else {
				column.push_back(new Material(n, m, 1));
			}
		}
		rows.push_back(column);
	}

	return rows;
}


int main() {
	//material 6x10 cm, L=10
	//pixel 1x1 cm
	int nrow = 10;
	int ncol = 10;
	int nparticles = 100000;

	//init materials
	vector<vector<Material*>> rows = init_material(ncol, nrow);

	start_test(rows, nparticles);
	//int confirm;
	//cin >> confirm;

}
