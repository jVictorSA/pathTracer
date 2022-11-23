# pathTracer
Path Tracer desenvolvido para a primeira edição do Code Fest do IC-UFAL

![Imagem de exemplo](/imgs/Exemplo.jpg "Imagem de Exemplo")  
* Cena 3D renderizada com o código presente em [main.cpp][1]

[1]: https://github.com/jVictorSA/pathTracer/blob/main/main.cpp/ "Title"

Código baseado no Ray Tracing in One Weekend de Peter Shirley.  
Disponível em: https://github.com/RayTracing/raytracing.github.io.

### Parâmetros
* SSP - Samples por pixels - Melhoram a qualidade da imagem jogando mais pixels na cena. Aumenta o tempo de execução  
* Largura - Largura da imagem - Define a largura da imagem. Aumenta o tamanho da imagem e o tempo de execução  
* Aspecto - Proporção da imagem - Define a proporção (formato) da imagem. Exemplos 16:9, 4:3, etc...  
* Profundidade - Número máximo da recursão dos raios de luz na cena - Quanto maior melhor a qualidade da imagem e maior o tempo de execução  


### Compilação - g++
```
g++ main.cpp -O3 -o main
```

### Execução - Linux
```
./main > <nome_da_imagem>.ppm
```
Exemplo:
```
./main > imagem.ppm
```

### Execução - Windows
```
main.exe > <nome_da_imagem>.ppm
```
Exemplo:
```
main.exe > imagem.ppm
```
<br>
Para quaisquer dúvidas entre em contato: jvsa@ic.ufal.br  

### Imagens de exemplo
![Imagem de exemplo 2](/imgs/imagem3.jpg "Imagem de Exemplo 2")  
* Cena 3D renderizada com o código presente em [imagem3.cpp][2]

[2]: https://github.com/jVictorSA/pathTracer/blob/main/imagem3.cpp/ "Title"

![Imagem de exemplo 3](/imgs/imagem1.jpg "Imagem de Exemplo 3")  
* Cena 3D renderizada com o código presente em [imagem1.cpp][3]

[3]: https://github.com/jVictorSA/pathTracer/blob/main/imagem1.cpp/ "Title"

![Imagem de exemplo 4](/imgs/imagem2.jpg "Imagem de Exemplo 4")  
* Cena 3D renderizada com o código presente em [imagem2.cpp][4]

[4]: https://github.com/jVictorSA/pathTracer/blob/main/imagem2.cpp/ "Title"

