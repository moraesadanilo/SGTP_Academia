#include "Historico.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
using namespace std;

// Adicionar registro ao histórico
void Historico::adicionarRegistro(const RegistroTreino& registro) {
    registros.push_back(registro);                                       // No vector registroS addd o registro passado pelo método.
    
}

// Exibir histórico completo
void Historico::exibirHistorico() const {
    if (registros.empty()) {                    
        std::cout << "Nenhum registro encontrado.\n";
        return;
    }

    std::cout << "===== HISTORICO DE TREINOS =====\n\n";
    for (const auto& salvo : registros) {
        cout << "Data/Hora: " << salvo.dataHora << "\n";
        cout << "Ficha ID: " << salvo.idFicha << " - " << salvo.nomeFicha << "\n";
        cout << "Tempo Total: " << salvo.tempoTotal << " min\n";
        cout << "Calorias Totais: " << salvo.caloriasTotal << " kcal\n";
        cout << "----------------------------------------\n";
    }
}

// Getter de registros
const std::vector<RegistroTreino>& Historico::getRegistros() const {
    //static std::vector<RegistroTreino> vazio; // Placeholder para compilar
    return registros; 
}

// Carregar histórico do arquivo - usa txt para alimentar o sistema com dados salvos
void Historico::carregarDeArquivo() {
    
    ifstream arquivo("historico.txt");
    if (!arquivo.is_open()) return;             //Verifica se abriu corretamente

    registros.clear();                          // limpar o vetor antes de carregar o conteúdo do arquivo e evita duplicação dos registros toda vez que carregar

    string linha;                               //cria linha de armazenamento atual  

    while (getline(arquivo, linha)) {           //ler cada linha do arquivo 
        stringstream ss(linha);                 //ler trechas de uma linha completa 
        
        RegistroTreino r;                       //cria o registro que receberar os dados
        string token;                           //strig de armazenamento temporario 

        getline(ss, r.dataHora, ';');           //da linha toda ler ate ";" e salva em dadaHora.
        
        getline(ss, token, ';');
        r.idFicha = stoi(token);                //conversao de caracter para inteiro

        getline(ss, r.nomeFicha, ';');

        getline(ss, token, ';');
        r.tempoTotal = stod(token);

        getline(ss, token, ';');
        r.caloriasTotal = stod(token);

        registros.push_back(r);                  //adicina ao fim do vector
    }
}

// Salvar histórico no arquivo
void Historico::salvarEmArquivo() const {
    
    ofstream arquivo("historico.txt");                 
    if (!arquivo.is_open()) {                                       //Verifica se abriu corretamente
        std::cerr << "Erro ao abrir arquivo de historico.\n";
        return;
    }

    for (const auto& r : registros) {                  //percorre o container, e de cada registro undividual "r" extrai os dados. 
        arquivo << r.dataHora << ";"                  // Escrever dados separados por (`;`).            
                << r.idFicha << ";"
                << r.nomeFicha << ";"
                << r.tempoTotal << ";"
                << r.caloriasTotal << endl;         //encerra a linha de dados no arquivo.
    }
    //Todos os campos são separados por ponto e vírgula (`;`)
}
