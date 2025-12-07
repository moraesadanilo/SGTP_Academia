#include "Sistema.h"
#include "Cardio.h"
#include "Forca.h"
#include "Utils.h"
#include <iostream>
#include <fstream>
#include <limits>
#include <sstream>
using namespace std;

Sistema::Sistema() {
    carregarDados();
}

Sistema::~Sistema() {
    salvarDados();
    // Apaga todos os exercícios
    for (auto* e : exercicios)
        delete e;
    exercicios.clear();

    // Apaga todas as fichas
    for (auto* f : fichas)
        delete f;
    fichas.clear();
}

// Carregar dados dos arquivos
void Sistema::carregarDados() {
    // Carregar exercicios.txt
    // Carregar fichas.txt
    historico.carregarDeArquivo();
}

// Salvar dados nos arquivos
void Sistema::salvarDados() {
    // Salvar exercicios.txt
    // Salvar fichas.txt
    





    /*
    //  SALVAR FICHAS.TXT
    ofstream arquivoficha("ficha.txt");                 
    if (!arquivoficha.is_open()) {                                       //Verifica se abriu corretamente
        std::cerr << "Erro ao abrir arquivo de historico.\n";
        return;
    }

    for (const auto& f : fichas) {                  //percorre o container, e de cada ficha undividual e extrai os dados. 
        arquivoficha << f.getId() << ";"                            
                     << f.getNome() << endl;
        //Todos os campos são separados por ponto e vírgula (`;`)      
    }
    */



    
    //  SALVAR HISTORICO.TXT CHAMANDO METODO DA CLASSE
    historico.salvarEmArquivo();
}

// Buscar exercício por ID
Exercicio* Sistema::buscarExercicioPorId(int id) {
    for (auto* exercicio_individual : exercicios) {                             //percore cada exercicio armazenado dentro de exercicio'S'. 
        if (exercicio_individual->getId() == id && exercicio_individual->isAtivo()) {
            return exercicio_individual;
        }
    }

    return nullptr;         // retorno em caso de nao localizado.
}

// Buscar ficha por ID
Ficha* Sistema::buscarFichaPorId(int id) {
    for (auto* ficha_indvidual : fichas) {                                  //percore cada ficha armazenada dentro de ficha'S'.
        if (ficha_indvidual->getId() == id) {
            return ficha_indvidual;
        }
    }
    
    return nullptr;        // retorno em caso de nao localizado.
}

// Cadastrar novo exercício
void Sistema::cadastrarExercicio() {
    int tipo;
    cout << "Tipo (1-Forca, 2-Cardio): ";
    cin >> tipo;
    cin.ignore();

    string nome;
    cout << "Nome: ";
    getline(cin, nome);

    Exercicio* novo = nullptr;          //// ponteiro para um Exercicio, inicializado apontando para nenhum local
    if (tipo == 1) {
        int series, repeticoes, tempoDescanso;
        double carga;
        cout << "Series: ";
        cin >> series;
        cout << "Repeticoes: ";
        cin >> repeticoes;
        cout << "Carga (Kg): ";
        cin >> carga;
        cout << "Descanso (s): ";
        cin >> tempoDescanso;
        cin.ignore(); 

        novo = new Forca(nome, carga, series, repeticoes, tempoDescanso);   
    } 
    else if (tipo == 2) {
        int duracao;
        double intensidade;
        cout << "Duracao (min): ";
        cin >> duracao;
        cout << "Intensidade (calorias/min): ";
        cin >> intensidade;
        cin.ignore();

        novo = new Cardio(nome, duracao, intensidade); 
    }

    exercicios.push_back(novo);
    cout << "Exercicio cadastrado!";
    pausar();
}

// Listar exercícios ativos
void Sistema::listarExercicios() {
    for (auto* exercicio_individual : exercicios) {
        if (exercicio_individual->isAtivo()) { exercicio_individual->exibirDetalhes();}
        //exercicio_individual->exibirDetalhes();      
    }
    pausar();
}

// Desativar exercício
void Sistema::excluirExercicio() {
    int id;
    cout << "Codigo do exercicio: ";
    cin >> id;

    Exercicio* execicio = buscarExercicioPorId(id);
    if (!execicio) {
        cout << "Exercicio nao encontrado.\n";
        return;
    }

    execicio->desativar();
    cout << "Exercicio desativado!\n";
}

// Criar nova ficha
void Sistema::criarFicha() {
    cin.ignore();
    string nome;
    cout << "Nome do treino: ";
    getline(cin, nome);

    Ficha* nova = new Ficha(nome);
    fichas.push_back(nova);

    cout << "Treino criado! ID: " << nova->getId()<<endl;
    pausar();
}

// Adicionar exercício à ficha
void Sistema::adicionarExercicioFicha() {
    int idFicha, idEx;
    cout << "Cod. do treino: ";
    cin >> idFicha;
    cout << "Cod. do exercicio: ";
    cin >> idEx;
    
    Ficha* ficha = buscarFichaPorId(idFicha);
    Exercicio* exercicio = buscarExercicioPorId(idEx);

    if (!ficha || !exercicio) {
        cout << "Treino ou exercicio nao encontrado."<<endl;
        return;
    }

    ficha->adicionarExercicio(exercicio);
    cout << "Exercicio adicionado!"<<endl;
    pausar();
}

// Listar todas as fichas
void Sistema::listarFichas() {
    for (auto* ficha_treino : fichas) {
        ficha_treino->exibirFicha();
    }
    pausar();
}

// Registrar treino realizado
void Sistema::registrarTreino() {

    int idFicha;
    cout << "Cod. do treino realizado: ";
    cin >> idFicha;

    Ficha* ficha = buscarFichaPorId(idFicha);                       //Busca a Ficha por id
    if (!ficha) {
        cout << "Treino nao encontrado. Registro cancelado!\n";
        return;
    }

    // Criar registro
    RegistroTreino registro;
    
    registro.dataHora = getDataHoraAtual();
    registro.idFicha = ficha->getId();
    registro.nomeFicha = ficha->getNome();
    registro.tempoTotal = ficha->calcularTempoTotal();
    registro.caloriasTotal = ficha->calcularCaloriasTotais();

    historico.adicionarRegistro(registro);                          //Adiciona ao Historico

    cout << "\nTreino registrado com sucesso!\n";
    cout << "Atividade: " <<ficha->getNome() <<"\n";
    cout << "Tempo total: " << registro.tempoTotal << " min\n";
    cout << "Calorias: " << registro.caloriasTotal << " cal\n";
    
    pausar();
}


// Exibir histórico de treinos
void Sistema::exibirHistorico() {
    
    historico.exibirHistorico();
    pausar();

}
