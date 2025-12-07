#include "Forca.h"
#include <iostream>
using namespace std;

// Construtor para novos cadastros
Forca::Forca(std::string nome, double carga, int series, int repeticoes, int tempoDescanso)
    : Exercicio(nome),                      // inicializa o nome e demais informações da classe base.
    carga(carga),                           // inicializa e guarda peso em kg
    series(series),                         // inicializa e guarda quantas vezes realiza o exercício
    repeticoes(repeticoes),                 // inicializa e guarda quantos movimentos por série
    tempoDescanso(tempoDescanso){           // inicializa e guarda pausa entre séries em segundos
}

// Construtor para leitura de arquivo
Forca::Forca(int id, std::string nome, bool ativo, double carga, int series, int repeticoes, int tempoDescanso)
    : Exercicio(id, nome, ativo),
    carga(carga),                           // inicializa e guarda peso em kg
    series(series),                         // inicializa e guarda quantas vezes realiza o exercício
    repeticoes(repeticoes),                 // inicializa e guarda quantos movimentos por série
    tempoDescanso(tempoDescanso){           // inicializa e guarda pausa entre séries em segundos {
}

// Exibir detalhes do exercício
void Forca::exibirDetalhes() const {
    
    cout << "--- Detalhes do Exercicio ---\n";
    cout << "Tipo: Forca\n";
    cout << "Cod. "<< getId() << " -> " << "Nome: " << getNome() << "\n";
    cout << "Status: " << (isAtivo() ? "Ativo" : "Inativo") << "\n";
    cout << "series: " <<series <<" | Repeticoes: "<< repeticoes << " | Carga: " << carga << " | Descanso : "<< tempoDescanso <<"s" << "\n";
    //cout << "Calorias gastas: " << calcularCaloriasGastas() << "\n";
    cout << "-------------------------\n";

}

// Calcular tempo estimado (em minutos)
double Forca::calcularTempoEstimado() const {

    //O tempo total é a soma do tempo fazendo força mais o tempo descansando.
    int tempoTotal = (series * repeticoes * 3 ) + (series * tempoDescanso);            //Resultado em segundos.
  
    return tempoTotal/60.0;           // Converter segundos para minutos (dividindo por 60.0) antes de retornar.

}

// Calcular calorias gastas
double Forca::calcularCaloriasGastas() const {
    
    return series * repeticoes * carga * 0.15;     //Fórmula de estimativa baseada no volume de carga levantado.

}

// Retornar tipo do exercício (2 = Força)
int Forca::getTipo() const {
    return 2; 
}

// Getters
double Forca::getCarga() const { 
    return carga; 
}

int Forca::getSeries() const { 
    return series; 
}

int Forca::getRepeticoes() const { 
    return repeticoes; 
}

int Forca::getTempoDescanso() const { 
    return tempoDescanso;
}
