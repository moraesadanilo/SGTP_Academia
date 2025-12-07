#include "Ficha.h"
#include <iostream>
#include <iomanip>
using namespace std;

int Ficha::proximoId = 1;

// Construtor para novos cadastros
Ficha::Ficha(std::string nome) : nomeTreino(nome){
    this->id = proximoId++;                                 // Inicializa o 'id' e depois incrementa 'proximoId'
}

// Construtor para leitura de arquivo
Ficha::Ficha(int id, std::string nome) : id(id), nomeTreino(nome)  {
    if (id >= proximoId){
        proximoId = id + 1;
    }
}

// Destrutor (não deletar exercícios, apenas limpar vector)
Ficha::~Ficha() {
    exercicios.clear();
}

// Adicionar exercício à ficha
void Ficha::adicionarExercicio(Exercicio* novoexercicio) {
    exercicios.push_back(novoexercicio); 
}

// Exibir ficha completa com exercícios e totais
void Ficha::exibirFicha() const {
    
    if (exercicios.empty()) {
        cout << "===== TREINO : "<<nomeTreino<<" (ID: "<< id <<") =====\n";
        cout << "Nenhum exercicio adicionado a esta ficha.\n"; // Adicionar esta linha
    }else{
        cout << "===== TREINO : "<<nomeTreino<<" (ID: "<< id <<") =====\n";
        for (const auto& exercicio : exercicios) {
                exercicio->exibirDetalhes();                 // POLIMORFISMO AQUI - exibe detalhes de acordo com a classe filha.
        }
        //cout << "-------------------------\n";
        cout << "TEMPO TOTAL: "<< calcularTempoTotal() <<"min. \n";
        cout << "GASTO CALORICO: "<< calcularCaloriasTotais() <<"cal. \n";
        cout << "============================\n";
    }
}

// Calcular tempo total da ficha
double Ficha::calcularTempoTotal() const {
    double total = 0.0;
    for (const auto& exercicio : exercicios) {
            total += exercicio->calcularTempoEstimado();  // POLIMORFISMO AQUI - Calcula o tempo com base na formula da classe filha.
        }
    return total;
}

// Calcular calorias totais da ficha
double Ficha::calcularCaloriasTotais() const {
    double total = 0.0;
    for (const auto& exercicio : exercicios) {
            total += exercicio->calcularCaloriasGastas();  // POLIMORFISMO AQUI - Calcula as  calorias com base na formula da classe filha.
        }
    return total;
}

// Getters
int Ficha::getId() const { 
    return id; 
}

std::string Ficha::getNome() const { 
    return nomeTreino; 
}

const std::vector<Exercicio*>& Ficha::getExercicios() const {
    static std::vector<Exercicio*> vazio;   // Placeholder para compilar
    return exercicios;                      // Implementar
}

// Atualizar próximo ID
void Ficha::atualizarProximoId(int maiorId) {
    if (maiorId >= proximoId) {
    proximoId = maiorId + 1;
    }   
}

