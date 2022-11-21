#ifndef COR_HPP
#define COR_HPP

#include "vec3.hpp"

#include <iostream>
//Escreve a cor do pixel no arquivo.
//Paramêtros: out(stream de saida) - coresDosPixels(cor) - int(SPP{Sample por pixel})
void printarCor(std::ostream &out, cor coresDosPixels, int SPP){
    auto r = coresDosPixels.x();
    auto g = coresDosPixels.y();
    auto b = coresDosPixels.z();

    //Dividir a cor por numero de samples
    auto escala = 1.0 / SPP;
    r = std::sqrt(escala * r);
    g = std::sqrt(escala * g);
    b = std::sqrt(escala * b);

    out << static_cast<int>(255.999 * clamp(r, 0.0, 0.999)) << ' '
        << static_cast<int>(255.999 * clamp(g, 0.0, 0.999)) << ' '
        << static_cast<int>(255.999 * clamp(b, 0.0, 0.999)) << '\n';
}

#endif