#include <iostream>
#include <string>
#include <vector>
#include <limits.h>
using namespace std;

// Jumlah kota
#define V 5

// Nama kota
#define GENES ABCDE

// Memulai value node
#define START 0

// Initial population size
#define POP_SIZE 10

// Struktur GNOME
// string mendefinisikan path yang dilalui
// oleh salesman sementara fitness value
// dari path disimpan di integer

struct individual {
	string gnome;
	int fitness;
};

// Fungsi untuk mengembalikan angka random dari awal hingga akhir
int rand_num(int start, int end)
{
	int r = end - start;
	int rnum = start + rand() % r;
	return rnum;
}

// Fungsi untuk memeriksa apakah karakter sudah pernah muncul dalam string
bool repeat(string s, char ch)
{
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == ch)
			return true;
	}
	return false;
}

// Fungsi untuk  mengembalikan GNOME mutan
// GNOME mutan adalah sebuah string dengan pertukaran random dari
// dua gen untuk membentuk variasi dalam spesies
string mutatedGene(string gnome)
{
	while (true) {
		int r = rand_num(1, V);
		int r1 = rand_num(1, V);
		if (r1 != r) {
			char temp = gnome[r];
			gnome[r] = gnome[r1];
			gnome[r1] = temp;
			break;
		}
	}
	return gnome;
}

// Berfungsi untuk mengembalikan string GNOME valid 
// yang diperlukan untuk membuat populasi
string create_gnome()
{
	string gnome = "0";
	while (true) {
		if (gnome.size() == V) {
			gnome += gnome[0];
			break;
		}
		int temp = rand_num(1, V);
		if (!repeat(gnome, (char)(temp + 48)))
			gnome += (char)(temp + 48);
	}
	return gnome;
}

// Function to return the fitness value of a gnome.
// The fitness value is the path length
// of the path represented by the GNOME.
int cal_fitness(string gnome)
{
	int map[V][V] = { { 0, 2, INT_MAX, 12, 5 },
					{ 2, 0, 4, 8, INT_MAX },
					{ INT_MAX, 4, 0, 3, 3 },
					{ 12, 8, 3, 0, 10 },
					{ 5, INT_MAX, 3, 10, 0 } };
	int f = 0;
	for (int i = 0; i < gnome.size() - 1; i++) {
		if (map[gnome[i] - 48][gnome[i + 1] - 48] == INT_MAX)
			return INT_MAX;
		f += map[gnome[i] - 48][gnome[i + 1] - 48];
	}
	return f;
}

// Function to return the updated value
// of the cooling element.
int cooldown(int temp)
{
	return (90 * temp) / 100;
}

// Comparator for GNOME struct.
bool lessthan(struct individual t1,
			struct individual t2)
{
	return t1.fitness < t2.fitness;
}

// Fungsi utilitas untuk masalah TSP.
void TSPUtil(int map[V][V])
{
	// Nomor Generasi
	int gen = 1;
	// Jumlah Iterasi Gen
	int gen_thres = 5;

	vector<struct individual> population;
	struct individual temp;

	// Mengisi kumpulan GNOME.
	for (int i = 0; i < POP_SIZE; i++) {
		temp.gnome = create_gnome();
		temp.fitness = cal_fitness(temp.gnome);
		population.push_back(temp);
	}

	cout << "\nInitial population: " << endl
		<< "GNOME	 FITNESS VALUE\n";
	for (int i = 0; i < POP_SIZE; i++)
		cout << population[i].gnome << " "
			<< population[i].fitness << endl;
	cout << "\n";

	bool found = false;
	int temperature = 10000;

	// Iterasi untuk melakukan persilangan populasi dan mutasi gen.
	while (temperature > 1000 && gen <= gen_thres) {
		sort(population.begin(), population.end(), lessthan);
		cout << "\nCurrent temp: " << temperature << "\n";
		vector<struct individual> new_population;

		for (int i = 0; i < POP_SIZE; i++) {
			struct individual p1 = population[i];

			while (true) {
				string new_g = mutatedGene(p1.gnome);
				struct individual new_gnome;
				new_gnome.gnome = new_g;
				new_gnome.fitness = cal_fitness(new_gnome.gnome);

				if (new_gnome.fitness <= population[i].fitness) {
					new_population.push_back(new_gnome);
					break;
				}
				else {

                    // Menerima anak-anak yang ditolak dengan probabilitas 
                    // yang mungkin di atas ambang batas
					float prob = pow(2.7,
									-1 * ((float)(new_gnome.fitness
												- population[i].fitness)
										/ temperature));
					if (prob > 0.5) {
						new_population.push_back(new_gnome);
						break;
					}
				}
			}
		}

		temperature = cooldown(temperature);
		population = new_population;
		cout << "Generation " << gen << " \n";
		cout << "GNOME	 FITNESS VALUE\n";

		for (int i = 0; i < POP_SIZE; i++)
			cout << population[i].gnome << " "
				<< population[i].fitness << endl;
		gen++;
	}
}

int main()
{

	int map[V][V] = { { 0, 2, INT_MAX, 12, 5 },
					{ 2, 0, 4, 8, INT_MAX },
					{ INT_MAX, 4, 0, 3, 3 },
					{ 12, 8, 3, 0, 10 },
					{ 5, INT_MAX, 3, 10, 0 } };
	TSPUtil(map);
}

