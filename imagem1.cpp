#include "rayTracing.hpp"
#include "cor.hpp"
#include "listaAtingiveis.hpp"
#include "esfera.hpp"
#include "camera.hpp"
#include "material.hpp"
#include "esferaEmMov.hpp"

#include <iostream>
#include <chrono>
 


double atingiuUmaEsfera(const ponto3D& centro, double raio, const raioDeLuz& r){
    vec3 oc = r.origem() - centro;
    auto a = r.direcao().comprimentoAoQuadrado();
    auto bSobre2 = prodEscalar(oc, r.direcao());
    auto c = oc.comprimentoAoQuadrado() - raio*raio;
    auto discriminante = bSobre2*bSobre2 - a*c;
    if(discriminante < 0){
        return -1.0;
    }else{
        return(-bSobre2 -std::sqrt(discriminante)) / a;
    }
}

cor corDoRaio(const raioDeLuz& r, const atingivel& mundo, int recursoes){
    registroImpacto reg;

    //Caso a recursao tenha excedido o limite, este raio nao sera mais calculado
    if(recursoes <= 0){
        return cor(0,0,0);
    }
    if(mundo.atingiu(r, 0.001, infinito, reg)){
        raioDeLuz dispersado;
        cor atenuacao;
        if(reg.matPtr->dispersar(r, reg, atenuacao, dispersado)){
            return atenuacao * corDoRaio(dispersado, mundo, recursoes-1);
        }
        return cor(0,0,0);
        
    }
    
    vec3 direcaoUnitaria = vetorUnitario(r.direcao());
    auto t = 0.5 * (direcaoUnitaria.y() + 1.0);
    return (1.0 - t) * cor(1.0, 1.0, 1.0) + t * cor(0.5, 0.7, 1.0);
}

int main(){

    //Informações da imagem
    const auto aspecto = 3.0 / 2.0; //Formato da imagem. Exemplos:  16:9, 4:3 e etc...
    const int largura = 1200;
    int altura = static_cast<int>(largura/aspecto);
    const int SPP = 500;
    const int profundidadeMax = 25;

    //Mundo
    auto R = cos(pi/4);
    listaAtingiveis mundo;

    auto matChao = std::make_shared<lambertian>(cor(0.8, 0.8, 0.0));
    auto matCen = std::make_shared<lambertian>(cor(0.7, 0.3, 0.3));
    auto matEsq = std::make_shared<metal>(cor(0.8, 0.8, 0.8), 0.0);
    auto matDir = std::make_shared<metal>(cor(0.8, 0.6, 0.2), 0.8);

    mundo.add(std::make_shared<esfera>(ponto3D( 0.0, -100.5, -1.0), 100.0, matChao));
    mundo.add(std::make_shared<esfera>(ponto3D( 0.0,    0.0, -1.0),   0.5, matCen));
    mundo.add(std::make_shared<esfera>(ponto3D(-1.0,    0.0, -1.0),   0.5, matEsq));
    mundo.add(std::make_shared<esfera>(ponto3D( 1.0,    0.0, -1.0),   0.5, matDir));
    
    //Câmera
    ponto3D origem(0,.5,3);
    ponto3D olharPara(0, 0, 0);
    vec3 vecCima(0,1,0);
    auto distParaFoco = 10;
    auto abertura = 0.0;
    camera cam(40.0, aspecto, origem, olharPara, vecCima, abertura, distParaFoco);

    auto inicio = std::chrono::high_resolution_clock::now();

    //Renderização
    std::cout << "P3\n" << largura << ' ' << altura << "\n255\n";

    for(int i = altura-1; i >= 0; --i){
        std::cerr << "\rLinhas restantes: " << i << ' ' << std::flush;
        for(int j = 0; j < largura; ++j){
            cor corDoPixel(0,0,0);
            for(int s = 0; s < SPP; ++s){
                auto u = (j + doubleAleatorio()) / (largura-1);
                auto v = (i + doubleAleatorio()) / (altura-1);
                raioDeLuz r = cam.raio(u,v);
                corDoPixel += corDoRaio(r, mundo, profundidadeMax);
            }
            printarCor(std::cout, corDoPixel, SPP);
        }
    }
    auto fim = std::chrono::high_resolution_clock::now();
    auto duracao = std::chrono::duration_cast<std::chrono::seconds>(fim - inicio);

    std::cerr << "\nRenderizacao concluida!\n\nTempo decorrido: " << duracao.count() << " segundos\n";

}