#include <iostream>
#include <math.h>
#include <fstream>
#include <string>
using std::fstream;

struct Voxel {
	float r, g, b; 
	float a;
	
	bool isOn; 
};


struct verticie {
	float x, y, z;
	bool exists;
	int n;
};


 class Sculptor {
protected:
	Voxel*** v;
	int nx, ny, nz; 
	float r, g, b, a; 
	int i, j, k;
public:
	Sculptor(int _nx, int _ny, int _nz);
	~Sculptor();
	void setColor(float r_, float g_, float b_, float alpha_);
	void putVoxel(int x, int y, int z);
	void cutVoxel(int x, int y, int z);
	void putBox(int x0, int x1, int y0, int y1, int z0, int z1);
	void cutBox(int x0, int x1, int y0, int y1, int z0, int z1);
	void putSphere(int xcenter, int ycenter, int zcenter, int radius);
	void cutSphere(int xcenter, int ycenter, int zcenter, int radius);
	void putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz);
	void cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz);
	void writeOFF(const char* filename);
	void freemem();
	void show();
};
 
 Sculptor::Sculptor(int _nx, int _ny, int _nz) {
	 int i, j, k;
	 nx = _nx; ny = _ny; nz = _nz;
	v = (Voxel***)malloc(_nx * sizeof(Voxel**));
	if (v == NULL){
		std::cout << "Out of memory";
		exit(0);
	}
	for (i = 0; i < _nx; i++) {
		v[i] = (Voxel**)malloc(_ny * sizeof(Voxel*));
		for (j = 0; j < _ny; j++) {
			v[i][j] = (Voxel*)malloc(_nz * sizeof(Voxel));
		}
	}
	for (i = 0; i < nx; i++) {
		for (j = 0; j < ny; j++) {
			for (k = 0; k < nz; k++) {
				v[i][j][k].isOn=0;
			}
		}
	}
 };

 Sculptor::~Sculptor(void) {
	 
 }



 void Sculptor::setColor(float r_, float g_, float b_, float alpha_) {
	r = r_; g = g_; b = b_; a = alpha_;
 };

 void Sculptor::putVoxel(int x, int y, int z) {
	 if ((0 <= x) && (x < nx) && (0 <= y) && (y < ny) && (0 <= z) && (z < nz)) {
		 v[x][y][z].isOn = true;
		 v[x][y][z].r = r; v[x][y][z].g = g; v[x][y][z].b = b; v[x][y][z].a = a;
	 }
 };
 void Sculptor::cutVoxel(int x, int y, int z) {
	 v[x][y][z].isOn = false;
 };
 void Sculptor::putBox(int x0, int x1, int y0, int y1, int z0, int z1) {
	 for (i = x0; i <= x1; i++) {
		 for (j = y0; j <= y1; j++) {
			 for (k = z0; k <= z1; k++) {
				 if ((0 <= i) && (i < nx) && (0 <= j) && (j < ny) && (0 <= k) && (k < nz)) {
					 v[i][j][k].isOn = true;
					 v[i][j][k].r = r; v[i][j][k].g = g; v[i][j][k].b = b; v[i][j][k].a = a;
				 }
			 }
		 }
	 }
 };
 void Sculptor::cutBox(int x0, int x1, int y0, int y1, int z0, int z1) {
	 for (i = x0; i <= x1; i++) {
		 for (j = y0; j <= y1; j++) {
			 for (k = z0; k <= z1; k++) {
				 if ((0 <= i) && (i < nx) && (0 <= j) && (j < ny) && (0 <= k) && (k < nz)) {
					 v[i][j][k].isOn = false;
				 }
			 }
		 }
	 }
 };
 void Sculptor::putSphere(int xcenter, int ycenter, int zcenter, int radius) {
	 for (i = xcenter - (radius); i <= xcenter + radius; i++) {
		 for (j = ycenter - radius; j <= ycenter + radius; j++) {
			 for (k = zcenter - radius; k <= zcenter + radius; k++) {
				 if ((0 <= i)&&(i < nx) && (0 <= j)&&(j < ny) && (0 <= k)&&(k < nz)) {
					 if (((pow((i - xcenter), 2)) + (pow((j - ycenter), 2)) + (pow((k - zcenter), 2))) <= (pow(radius, 2))) {
						 v[i][j][k].isOn = true;
						 v[i][j][k].r = r; v[i][j][k].g = g; v[i][j][k].b = b; v[i][j][k].a = a;
					 }
				 }
			 }
		 }
	 }
 };
 void Sculptor::cutSphere(int xcenter, int ycenter, int zcenter, int radius) {
	 for (i = xcenter - (radius); i <= xcenter + radius; i++) {
		 for (j = ycenter - radius; j <= ycenter + radius; j++) {
			 for (k = zcenter - radius; k <= zcenter + radius; k++) {
				 if ((0 <= i) && (i < nx) && (0 <= j) && (j < ny) && (0 <= k) && (k < nz)) {
					 if (((pow((i - xcenter), 2)) + (pow((j - ycenter), 2)) + (pow((k - zcenter), 2))) <= (pow(radius, 2))) {
						 v[i][j][k].isOn = false;
					 }
				 }
			 }
		 }
	 }
 };
 void Sculptor::putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz) {
	 for (i = xcenter - rx; i <= xcenter + rx; i++) {
		 for (j = ycenter - ry; j <= ycenter + ry; j++) {
			 for (k = zcenter - rz; k <= zcenter + rz; k++) {
				 if ((0 <= i) && (i < nx) && (0 <= j) && (j < ny) && (0 <= k) && (k < nz)) {
					 if (((pow((i - xcenter), 2) / pow(rx, 2)) + (pow((j - ycenter), 2) / pow(ry, 2)) + (pow((k - zcenter), 2) / pow(rz, 2))) <= 1) {
						 v[i][j][k].isOn = true;
						 v[i][j][k].r = r; v[i][j][k].g = g; v[i][j][k].b = b; v[i][j][k].a = a;
					 }
				 }
			 }
		 }
	 }
 };
 void Sculptor::cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz) {
	 for (i = xcenter - rx; i <= xcenter + rx; i++) {
		 for (j = ycenter - ry; j <= ycenter + ry; j++) {
			 for (k = zcenter - rz; k <= zcenter + rz; k++) {
				 if ((0 <= i) && (i < nx) && (0 <= j) && (j < ny) && (0 <= k) && (k < nz)) {
					 if (((pow((i - xcenter), 2) / pow(rx, 2)) + (pow((j - ycenter), 2) / pow(ry, 2)) + (pow((k - zcenter), 2) / pow(rz, 2))) <= 1) {
						 v[i][j][k].isOn = false;
					 }
				 }
			 }
		 }
	 }
 };


 void Sculptor::freemem(void) {
	 int i, j, k;
	 for (i = 0; i < nx; i++) {
		 for (j = 0; j < ny; j++) {
			 free(v[i][j]); std::cout << "liberado v[" << i << "][" << j << "] \n";
		 }
		 free(v[i]); std::cout << "liberado v[" << i << "]\n";
	 }
	 free(v); std::cout << "Finalizado\n\n";
 }



 void Sculptor::show(void) {
	 int i, j, k;
	 for (k = 0; k < nz; k++) {
		 std::cout << std::endl << " z=" << k << std::endl;
		 for(j = ny-1; j>= 0; j--) {
			 for (i = 0; i < nx; i++) {
				 if (v[i][j][k].isOn) { std::cout << "X ";}
				 else {
					 std::cout << "  ";
			 };
			 }
		  std::cout<<"\n";
		 }
	 }
 }



 void Sculptor::writeOFF(const char* filename){
	 int i, k, j, n=0;
	 int nv=0, nc;
	 verticie*** ver;
	 fstream file;
	 ver = (verticie***)malloc((nx+1) * sizeof(verticie**));
	 if (ver == NULL) {
		 std::cout << "Out of memory";
		 exit(0);
	 }
	 for (i = 0; i < (nx+1); i++) {
		 ver[i] = (verticie**)malloc((ny+1) * sizeof(verticie*));
		 for (j = 0; j < (ny+1); j++) {
			 ver[i][j] = (verticie*)malloc((nz+1) * sizeof(verticie));
		 }
	 }
	 for (i = 0; i < (nx+1); i++) {
		 for (j = 0; j < (ny+1); j++) {
			 for (k = 0; k < (nz+1); k++) {
				 ver[i][j][k].exists = 0;
			 }
		 }
	 }

	 file.open(filename, std::ios::out);
	 for (i = 0; i < (nx+1); i++) {
		 for (j = 0; j < (ny+1); j++) {
			 for (k = 0; k < (nz + 1); k++) {
				 nc = 0;
				 if ((0 <= i) && (i < nx) && (0 <= j) && (j < ny) && (0 <= k) && (k < nz)) { if (v[i][j][k].isOn) { nc++; } }
				 if ((0 <= i) && (i < nx) && (0 <= j) && (j < ny) && (0 <= k-1) && (k-1 < nz)) { if (v[i][j][k-1].isOn) { nc++; } }
				 if ((0 <= i) && (i < nx) && (0 <= j-1) && (j-1 < ny) && (0 <= k) && (k < nz)) { if (v[i][j-1][k].isOn) { nc++; } }
				 if ((0 <= i) && (i < nx) && (0 <= j-1) && (j-1 < ny) && (0 <= k-1) && (k-1 < nz)) { if (v[i][j-1][k-1].isOn) { nc++; } }
				 if ((0 <= i-1) && (i-1 < nx) && (0 <= j) && (j < ny) && (0 <= k) && (k < nz)) { if (v[i-1][j][k].isOn) { nc++; } }
				 if ((0 <= i-1) && (i-1 < nx) && (0 <= j) && (j < ny) && (0 <= k-1) && (k-1 < nz)) { if (v[i-1][j][k-1].isOn) { nc++; } }
				 if ((0 <= i-1) && (i-1 < nx) && (0 <= j-1) && (j-1 < ny) && (0 <= k) && (k < nz)) { if (v[i-1][j-1][k].isOn) { nc++; } }
				 if ((0 <= i-1) && (i-1 < nx) && (0 <= j-1) && (j-1 < ny) && (0 <= k-1) && (k-1 < nz)) { if (v[i-1][j-1][k-1].isOn) { nc++; } }
				 if ((nc > 0) && (nc < 8)) {
					 nv++;
					 ver[i][j][k].x = i - 0.5;
					 ver[i][j][k].y = j - 0.5;
					 ver[i][j][k].z = k - 0.5;
					 ver[i][j][k].exists = true;
				 }
			 }
		 }
	 }
	 nc = 0;
	 for ( i = 0; i < nx; i++) {
		 for (j = 0; j < ny; j++) {
			 for (k = 0; k < nz; k++) {
				 if (v[i][j][k].isOn) {
					 if (i + 1 < nx) { if (v[i + 1][j][k].isOn == 0) { nc++; } }
					 else { nc++; }
					 if (i - 1 >= 0) { if (v[i - 1][j][k].isOn == 0) { nc++; } }
					 else { nc++; }
					 if (j + 1 < ny) { if (v[i][j + 1][k].isOn == 0) { nc++; } }
					 else { nc++; }
					 if (j - 1 >= 0) { if (v[i][j - 1][k].isOn == 0) { nc++; } }
					 else { nc++; }
					 if (k + 1 < nz) { if (v[i][j][k + 1].isOn == 0) { nc++; } }
					 else { nc++; }
					 if (k - 1 >= 0) { if (v[i][j][k - 1].isOn == 0) { nc++; } }
					 else {
						 nc++;
					 }
				 }
			 }
		 }
	 }
	 std::cout <<"\nNumero de verticies: "<< nv<<"\n";
	 std::cout <<"\nNumero de faces: "<< nc<<"\n";
	 std::cout << "\n Caminho do arquivo:" << filename<<"\n";
	 file << "OFF\n"<< nv << " "<< nc <<" 0\n";
	 for (i = 0; i < (nx + 1); i++) {
		 for (j = 0; j < (ny + 1); j++) {
			 for (k = 0; k < (nz + 1); k++) {
				 if (ver[i][j][k].exists) {
					 file << ver[i][j][k].x << " " << ver[i][j][k].y << " " << ver[i][j][k].z << "\n";
					 ver[i][j][k].n = n;
					 n++;
				 }
			 }
		 }
	 }
	 for (i = 0; i < nx; i++) {
		 for (j = 0; j < ny; j++) {
			 for (k = 0; k < nz; k++) {
				 if (v[i][j][k].isOn) {
					 if (i + 1 < nx) { if (v[i + 1][j][k].isOn == 0) { 
						 file << ver[i + 1][j][k].n << " ";
						 file << ver[i + 1][j+1][k].n << " ";
						 file << ver[i + 1][j][k+1].n << " ";
						 file << ver[i + 1][j+1][k+1].n << " ";
						 file << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << "\n"
						 ; } }
					 else { 
						 file << ver[i + 1][j][k].n << " ";
						 file << ver[i + 1][j + 1][k].n << " ";
						 file << ver[i + 1][j][k + 1].n << " ";
						 file << ver[i + 1][j + 1][k + 1].n << " ";
						 file << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << "\n";
					 }
					 if (i - 1 >= 0) { if (v[i - 1][j][k].isOn == 0) {
						 file << ver[i][j][k].n << " ";
						 file << ver[i][j + 1][k].n << " ";
						 file << ver[i][j][k + 1].n << " ";
						 file << ver[i][j + 1][k + 1].n << " ";
						 file << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << "\n";
					 } }
					 else {
						 file << ver[i][j][k].n << " ";
						 file << ver[i][j + 1][k].n << " ";
						 file << ver[i][j][k + 1].n << " ";
						 file << ver[i][j + 1][k + 1].n << " ";
						 file << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << "\n";
					 }
					 if (j + 1 < ny) { if (v[i][j + 1][k].isOn == 0) { 
						 file << ver[i+1][j+1][k].n << " ";
						 file << ver[i][j + 1][k].n << " ";
						 file << ver[i+1][j+1][k + 1].n << " ";
						 file << ver[i][j + 1][k + 1].n << " ";
						 file << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << "\n";
						  } }
					 else { 
						 file << ver[i + 1][j + 1][k].n << " ";
						 file << ver[i][j + 1][k].n << " ";
						 file << ver[i + 1][j + 1][k + 1].n << " ";
						 file << ver[i][j + 1][k + 1].n << " ";
						 file << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << "\n";
					 }
					 if (j - 1 >= 0) { if (v[i][j - 1][k].isOn == 0) { 
						 file << ver[i + 1][j][k].n << " ";
						 file << ver[i][j][k].n << " ";
						 file << ver[i + 1][j][k + 1].n << " ";
						 file << ver[i][j][k + 1].n << " ";
						 file << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << "\n";
						 } 
					 }
					 else {
						 file << ver[i + 1][j][k].n << " ";
						 file << ver[i][j][k].n << " ";
						 file << ver[i + 1][j][k + 1].n << " ";
						 file << ver[i][j][k + 1].n << " ";
						 file << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << "\n";
					 }
					 if (k + 1 < nz) { if (v[i][j][k + 1].isOn == 0) { 
						 file << ver[i + 1][j][k+1].n << " ";
						 file << ver[i+1][j+1][k+1].n << " ";
						 file << ver[i][j+1][k + 1].n << " ";
						 file << ver[i][j][k + 1].n << " ";
						 file << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << "\n"; 
					 } 
					 }
					 else {
						 file << ver[i + 1][j][k+1].n << " ";
						 file << ver[i+1][j+1][k+1].n << " ";
						 file << ver[i][j+1][k + 1].n << " ";
						 file << ver[i][j][k + 1].n << " ";
						 file << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << "\n";
					 }
					 if (k - 1 >= 0) { if (v[i][j][k - 1].isOn == 0) {
						 file << ver[i + 1][j][k].n << " ";
						 file << ver[i + 1][j + 1][k].n << " ";
						 file << ver[i][j + 1][k].n << " ";
						 file << ver[i][j][k].n << " ";
						 file << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << "\n";
					 } }
					 else {
					
						 file << ver[i + 1][j][k].n << " ";
						 file << ver[i + 1][j + 1][k].n << " ";
						 file << ver[i][j + 1][k].n << " ";
						 file << ver[i][j][k].n << " ";
						 file << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << "\n";
					 }
				 }
			 }
		 }
	 }



 };


int main() {	
	int lx = 0, ly = 0, lz = 0;
	int a=0, a1, a2, a3, a4, a5, a6;
	std::string filename;
	std::cout << "Digite as dimensoes desejadas(x,y,z): ";
	std::cin >> lx >> ly >> lz;
	if((lx==0)&&(ly==0)&&(lz==0)){exit(0);}
	Sculptor cursor(lx, ly, lz);
	std::cout << "...\nConstruindo Matriz com dimenssoes: " << lx << " " << ly << " " << lz<<std::endl;
	while (a < 12) {
		std::cout << "a= " << a;
		std::cout << "..\nEscolha a opcao digitando o numero correspondente\n1-Mudar cor\n2-Colocar Voxel\n3-Tirar Voxel\n4-Colocar Cubo\n5-Tirar Cubo\n6-Colocar Esfera\n7-Tirar Esfera\n8-Colocar Elipsoide\n9-Tirar Elipsoide\n10-Salvar(WIP)\n11-Mostrar\n12-Sair\n\n";
		std::cin >> a;
		switch (a) {
		case 1:
			std::cout << "Digite a cor em RGB e a transparencia de 1 até 0(R, G, B, a) ";
			std::cin >> a1 >> a2 >> a3 >> a4;
			if ((a1 >= 0) && (a1 <= 1) && (a2 >= 0) && (a2 <= 1) && (a3 >= 0) && (a3 <= 1) && (a4 >= 0) && (a4 <= 1)) {
				std::cout << "Cor do cursor mudada para" << a1 << " " << a2 << " " << a3 << " " << a4;
				cursor.setColor(a1, a2, a3, a4);
				break;
			}
			else { break; }
		case 2:
			std::cout << "\nDigite a posicao(x, y, z) ";
		std::cin >> a1 >> a2 >> a3;
		cursor.putVoxel(a1, a2, a3);
		std::cout << "Colocado voxel em" << a1 << " " << a2 << " " << a3 << "\n";
		break;
		case 3:
			std::cout << "\nDigite a posicao(x, y , z) ";
			std::cin >> a1 >> a2 >> a3;
			cursor.cutVoxel(a1, a2, a3);
			std::cout << "Tirado voxel em" << a1 << " " << a2 << " " << a3 << "\n";
			break;
		case 4:
			std::cout << "\nDigite as posicoes das verticies(x0, x1, y0, y1, z0, z1) ";
			std::cin >> a1 >> a2 >> a3 >> a4 >> a5 >> a6;
			cursor.putBox(a1, a2, a3, a4, a5, a6);
			std::cout << "Colocado cubo de x=" << a1 << "até x=" << a2 << " y" << a3 << " até y=" << a4 << " z=" << a5 << " até z=" << a6 << "\n";
			break;
		case 5:
			std::cout << "\nDigite as posicao das verticies(x0, x1, y0, y1, z0, z1) ";
			std::cin >> a1 >> a2 >> a3 >> a4 >> a5 >> a6;
			cursor.cutBox(a1, a2, a3, a4, a5, a6);
			std::cout << "Trirado de x=" << a1 << "até x=" << a2 << " y" << a3 << " até y=" << a4 << " z=" << a5 << " até z=" << a6 << "\n";
			break;
		case 6:
			std::cout << "\nDigite as posicao do centro e o raio(x, y, z, r) ";
			std::cin >> a1 >> a2 >> a3 >> a4;
			cursor.putSphere(a1, a2, a3, a4);
			std::cout << "Colocada esfera com centro" << a1 << " " << a2 << " " << a3 << " e raio " << a4 << "\n";
			break;
		case 7:
			std::cout << "\nDigite as posicao do centro e o raio(x, y, z, r) ";
			std::cin >> a1 >> a2 >> a3 >> a4;
			cursor.cutSphere(a1, a2, a3, a4);
			std::cout << "Tirada esfera com centro" << a1 << " " << a2 << " " << a3 << " e raio " << a4 << "\n";
			break;
		case 8:
			std::cout << "\nDigite as posicao do centro e dimensoes do raio(x, y, z, rx, ry, rz) ";
			std::cin >> a1 >> a2 >> a3 >> a4 >> a5 >> a6;
			cursor.putEllipsoid(a1, a2, a3, a4, a5, a6);
			std::cout << "Colocado elipsoide com centro " << a1 << " " << a2 << " " << a3 << " e dimensoes do raio " << a4 << " " << a5 << " " << a6 << "\n";
			break;
		case 9: 
			std::cout << "\nDigite as posicao do centro e dimensoes do raio(x, y, z, rx, ry, rz) ";
			std::cin >> a1 >> a2 >> a3 >> a4 >> a5 >> a6;
			cursor.cutEllipsoid(a1, a2, a3, a4, a5, a6);
			std::cout << "Tirado elipsoide com centro " << a1 << " " << a2 << " " << a3 << " e dimensoes do raio " << a4 <<" "<< a5 << " " << a6 << "\n";
			break;
		case 10:
			std::cout << "\nDigite o nome/endereco do arquivo: \n ";
			std::cin >> filename;
			cursor.writeOFF(filename.c_str());
			break;
		case 11:
			std::cout << "\nMostrando Matriz\n";
			cursor.show();
			break;
		case 12:
			break;
		
		}
	}
	return 0;
}