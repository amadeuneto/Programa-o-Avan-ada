#include "Sculptor.h"
#include <iostream>
//#include <iomanip>

int main(void) {

  Sculptor coala(100, 100, 100);

  // cabeça OK
  coala.setColor(0.502, 0.502, 0.502, 1.0); // cinza 
  coala.putSphere(49, 45, 40, 20);

  // orelhas OK
  coala.setColor(0.502, 0.502, 0.502, 1.0); //cinza 
  coala.putSphere(32, 43, 25, 14); // orelha direita
  coala.putSphere(66, 43, 25, 14); // orelha esquerda
  
  // parte interna da orelha OK
  coala.setColor(0.9, 0.6, 0.7, 0.6); // rosa claro
  coala.putSphere(32, 32, 27, 6); // orelha direita
  coala.putSphere(66, 32, 27, 6); // orelha esquerda 
  
  // olhos OK
  coala.setColor(1.0, 0.53, 0.6, 1.0); // azul esverdeado
  coala.putBox(57, 59, 27, 28, 33, 37); // esquerdo
  coala.putBox(40, 42, 27, 28, 33, 37); // direito

  // nariz OK
  coala.setColor(0.0, 1.0, 0.0, 1.0); // preto
  coala.putSphere(49, 27, 40, 3);

  // boca OK
  coala.setColor(0.0, 1.0, 0.0, 1.0); // preto
  coala.putEllipsoid(49, 26, 49, 3, 1, 1);

  coala.writeOFF((char *)"coala.off");

  std::cout << "Programa finalizado com sucesso" << std::endl;

  return 0;
} 
 //(0.83, 0.83, 0.83, 1.0); // cinza claro