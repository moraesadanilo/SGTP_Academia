#include "Cardio.h"
#include <iostream>
using namespace std;

// Construtor para novos cadastros
Cardio::Cardio(std::string nome, int duracao, double caloriasPorMinuto) 
    : Exercicio(nome),                      // inicializa o nome e demais informações da classe base.
    duracao(duracao),                       // inicializa e guarda duração do treino.
    caloriasPorMinuto(caloriasPorMinuto){   // inicializa e guarda calorias/min.  
}

// Construtor para leitura de arquivo
Cardio::Cardio(int id, std::string nome, bool ativo, int duracao, double caloriasPorMinuto)
    : Exercicio(id, nome, ativo),
    duracao(duracao),                           // inicializa e guarda duração do treino em minutos.
    caloriasPorMinuto(caloriasPorMinuto){       // inicializa e guarda calorias/min.
}

// Exibir detalhes do exercício
void Cardio::exibirDetalhes() const {

    cout << "--- Detalhes do Exercicio ---\n";
    cout << "Tipo: Cardio\n";
    cout << "Cod. "<< getId() << " -> " << "Nome: " << getNome() << "\n";
    cout << "Status: " << (isAtivo() ? "Ativo" : "Inativo") << "\n";
    cout << "Duracao: " << duracao << " minutos\n";
    cout << "Intensidade: " << caloriasPorMinuto << "calorias/min" << "\n";
    //cout << "Calorias gastas: " << calcularCaloriasGastas() << "\n";
    cout << "-------------------------\n";
    
}

// Calcular tempo estimado (duração em minutos)
double Cardio::calcularTempoEstimado() const {
    return  duracao;                                // O tempo estimado do treino é exatamente a duração cadastrada.
}

// Calcular calorias gastas
double Cardio::calcularCaloriasGastas() const {
    return duracao * caloriasPorMinuto;             //Cálculo de Calorias: Multiplica-se a duração pelo gasto calórico por minuto.
}

// Retornar tipo do exercício (1 = Cardio)
int Cardio::getTipo() const {
    return 1; 
}

// Getter de duração  ( em minutos ) 
int Cardio::getDuracao() const {
    return duracao;             
}

// Getter de calorias por minuto
double Cardio::getCaloriasPorMinuto() const {
    return caloriasPorMinuto; 
}
