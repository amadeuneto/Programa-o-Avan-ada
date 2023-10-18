#include "Sculptor.h"
#include <cmath>
#include <fstream>
#include <iostream>
#include <stdlib.h>

using namespace std;

Sculptor::Sculptor(int _nx, int _ny, int _nz) {
  nx = _nx;
  ny = _ny;
  nz = _nz;

  r = 0;
  g = 0;
  b = 0;
  a = 0;

  v = new Voxel **[_nx]; // Alocação de memória da 1 dimensão da matriz
  for (int i = 0; i < _nx; i++) {
    v[i] = new Voxel *[_ny]; // Alocação de memória da 2 dimensão da matriz

    for (int j = 0; j < _ny; j++) {
      v[i][j] = new Voxel[_nz]; // Alocação de memória da 3 dimensão da matriz

      for (int k = 0; k < _nz; k++) {
        this->v[i][j][k].r = 0;
        this->v[i][j][k].g = 0;
        this->v[i][j][k].b = 0;
        this->v[i][j][k].a = 0;
        this->v[i][j][k].isOn = false;
      }
    }
  }
}

Sculptor::~Sculptor() { // Liberação da memória alocada
  for (int i = 0; i < nx; i++) {
    for (int j = 0; j < ny; j++) {
      delete[] v[i][j]; // Liberação da última alocação
    }
    delete[] v[i]; // Liberação da penúltima
  }
  delete[] v; // Liberação da primeira
}
// Atribuição das cores a partir dos parâmetros
void Sculptor::setColor(float red, float green, float blue, float alpha) {

  this->r = red;
  this->g = green;
  this->b = blue;
  this->a = alpha;
}
// Ativaçao de um único voxel
void Sculptor::putVoxel(int x, int y, int z) {
  this->v[x][y][z].r = this->r;
  this->v[x][y][z].g = this->g;
  this->v[x][y][z].b = this->b;
  this->v[x][y][z].a = this->a;
  this->v[x][y][z].isOn = true;
}
// Desativação de uma único voxel
void Sculptor::cutVoxel(int x, int y, int z) { this->v[x][y][z].isOn = false; }
void Sculptor::putBox(int x0, int x1, int y0, int y1, int z0, int z1) {
  if ((this->nx >= x0 && this->nx >= x1) &&
      (this->ny >= y0 && this->ny >= y1) &&
      (this->nz >= z0 && this->nz >= z1)) {
    for (int i = x0; i < x1; i++) {
      for (int j = y0; j < y1; j++) {
        for (int k = z0; k < z1; k++) {
          this->v[i][j][k].r = this->r;
          this->v[i][j][k].g = this->g;
          this->v[i][j][k].b = this->b;
          this->v[i][j][k].a = this->a;
          this->v[i][j][k].isOn = true;
        }
      }
    }
  }
}
void Sculptor::cutBox(int x0, int x1, int y0, int y1, int z0, int z1) {
  if ((this->nx >= x0 && this->nx >= x1) &&
      (this->ny >= y0 && this->ny >= y1) &&
      (this->nz >= z0 && this->nz >= z1)) {
    for (int i = x0; i < x1; i++) {
      for (int j = y0; j < y1; j++) {
        for (int k = z0; k < z1; k++) {
          this->v[i][j][k].isOn = false;
        }
      }
    }
  }
}
void Sculptor::putSphere(int xcenter, int ycenter, int zcenter, int radius) {
  for (int i = 0; i < nx; i++) {
    for (int j = 0; j < ny; j++) {
      for (int k = 0; k < nz; k++) {
        if ((pow(i - xcenter, 2) + pow(j - ycenter, 2) + pow(k - zcenter, 2)) <=
            pow(radius, 2)) {
          this->v[i][j][k].r = this->r;
          this->v[i][j][k].g = this->g;
          this->v[i][j][k].b = this->b;
          this->v[i][j][k].a = this->a;
          this->v[i][j][k].isOn = true;
        }
      }
    }
  }
}
void Sculptor::cutSphere(int xcenter, int ycenter, int zcenter, int radius) {
  for (int i = 0; i < nx; i++) {
    for (int j = 0; j < ny; j++) {
      for (int k = 0; k < nz; k++) {
        if ((pow(i - xcenter, 2) + pow(j - ycenter, 2) + pow(k - zcenter, 2)) <=
            pow(radius, 2)) {
          this->v[i][j][k].isOn = false;
        }
      }
    }
  }
}
void Sculptor::putEllipsoid(int xcenter, int ycenter, int zcenter, int rx,
                            int ry, int rz) {
  for (int i = 0; i < nx; i++) {
    for (int j = 0; j < ny; j++) {
      for (int k = 0; k < nz; k++) {
        if (((pow(i - xcenter, 2) / pow(rx, 2)) +
             (pow(j - ycenter, 2) / pow(ry, 2)) +
             (pow(k - zcenter, 2) / pow(rz, 2))) <= 1) {
          this->v[i][j][k].r = this->r;
          this->v[i][j][k].g = this->g;
          this->v[i][j][k].b = this->b;
          this->v[i][j][k].a = this->a;
          this->v[i][j][k].isOn = true;
        }
      }
    }
  }
}

// Desativação de um bloco de voxels em forma de elipsóide
void Sculptor::cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx,
                            int ry, int rz) {
  for (int i = 0; i < nx; i++) {
    for (int j = 0; j < ny; j++) {
      for (int k = 0; k < nz; k++) {
        if (((pow(i - xcenter, 2) / pow(rx, 2)) +
             (pow(j - ycenter, 2) / pow(ry, 2)) +
             (pow(k - zcenter, 2) / pow(rz, 2))) <= 1) {
          this->v[i][j][k].isOn = false;
        }
      }
    }
  }
}
// Gravação do arquivo
void Sculptor::writeOFF(char *filename) {
  int total_vox = 0, cont_vox = 0;

  ofstream arquivo;       // Objeto da classe ofstream
  arquivo.open(filename); // Abrindo o fluxo para o arquivo

  for (int i = 0; i < nx; i++) {
    for (int j = 0; j < ny; j++) {
      for (int k = 0; k < nz; k++) {
        if (this->v[i][j][k].isOn == true) {
          total_vox++;
        }
      }
    }
  }

  arquivo << "OFF" << endl;
  arquivo << 8 * total_vox << " " << 6 * total_vox << " "
          << "0" << endl;

  // Definição das coordenadas dos vértices do voxel
  for (int i = 0; i < nx; i++) {
    for (int j = 0; j < ny; j++) {
      for (int k = 0; k < nz; k++) {
        if (this->v[i][j][k].isOn == true) {

          arquivo << i - 0.5 << " " << j + 0.5 << " " << k - 0.5 << endl;
          arquivo << i - 0.5 << " " << j - 0.5 << " " << k - 0.5 << endl;
          arquivo << i + 0.5 << " " << j - 0.5 << " " << k - 0.5 << endl;
          arquivo << i + 0.5 << " " << j + 0.5 << " " << k - 0.5 << endl;
          arquivo << i - 0.5 << " " << j + 0.5 << " " << k + 0.5 << endl;
          arquivo << i - 0.5 << " " << j - 0.5 << " " << k + 0.5 << endl;
          arquivo << i + 0.5 << " " << j - 0.5 << " " << k + 0.5 << endl;
          arquivo << i + 0.5 << " " << j + 0.5 << " " << k + 0.5 << endl;
        }
      }
    }
  }
  // Especificações das faces e apresentação das cores no formato RGBA
  for (int i = 0; i < nx; i++) {
    for (int j = 0; j < ny; j++) {
      for (int k = 0; k < nz; k++) {
        if (this->v[i][j][k].isOn == true) {

          arquivo << "4"
                  << " " << 8 * cont_vox + 0 << " " << 8 * cont_vox + 3 << " "
                  << 8 * cont_vox + 2 << " " << 8 * cont_vox + 1 << " "
                  << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b
                  << " " << v[i][j][k].a << endl;
          arquivo << "4"
                  << " " << 8 * cont_vox + 4 << " " << 8 * cont_vox + 5 << " "
                  << 8 * cont_vox + 6 << " " << 8 * cont_vox + 7 << " "
                  << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b
                  << " " << v[i][j][k].a << endl;
          arquivo << "4"
                  << " " << 8 * cont_vox + 0 << " " << 8 * cont_vox + 1 << " "
                  << 8 * cont_vox + 5 << " " << 8 * cont_vox + 4 << " "
                  << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b
                  << " " << v[i][j][k].a << endl;
          arquivo << "4"
                  << " " << 8 * cont_vox + 0 << " " << 8 * cont_vox + 4 << " "
                  << 8 * cont_vox + 7 << " " << 8 * cont_vox + 3 << " "
                  << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b
                  << " " << v[i][j][k].a << endl;
          arquivo << "4"
                  << " " << 8 * cont_vox + 3 << " " << 8 * cont_vox + 7 << " "
                  << 8 * cont_vox + 6 << " " << 8 * cont_vox + 2 << " "
                  << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b
                  << " " << v[i][j][k].a << endl;
          arquivo << "4"
                  << " " << 8 * cont_vox + 1 << " " << 8 * cont_vox + 2 << " "
                  << 8 * cont_vox + 6 << " " << 8 * cont_vox + 5 << " "
                  << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b
                  << " " << v[i][j][k].a << endl;

          cont_vox++;
        }
      }
    }
  }

  arquivo.close(); // fechando o fluxo
}