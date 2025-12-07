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
    carregarExercicios();       // Carregar exercicios.txt
    carregarFichas();           // Carregar fichas.txt
    historico.carregarDeArquivo();
}

// Salvar dados nos arquivos
void Sistema::salvarDados() {
    salvarExercicios(); // Salvar exercicios.txt
    salvarFichas();     //Salvar ficha.txt
    
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

// salvar exercícios em txt
void Sistema::salvarExercicios() {
    ofstream arquivo("exercicios.txt");
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir arquivo de exercicios para salvar.\n";
        return;
    }

    for (const auto& e : exercicios) {
        // Campos Comuns: ID;TIPO;NOME;ATIVO;
        arquivo << e->getId() << ";"
                << e->getTipo() << ";"
                << e->getNome() << ";"
                << (e->isAtivo() ? "1" : "0") << ";";

        if (e->getTipo() == 2) {                        // Forca
            Forca* f = dynamic_cast<Forca*>(e);
            arquivo << f->getCarga() << ";"
                    << f->getSeries() << ";"
                    << f->getRepeticoes() << ";"
                    << f->getTempoDescanso() << endl;
        } else if (e->getTipo() == 1) {                 // Cardio
            Cardio* c = dynamic_cast<Cardio*>(e);
            arquivo << c->getDuracao() << ";"
                    << c->getCaloriasPorMinuto() << endl;
        }
    }
}

// Salvar fichas em txt
void Sistema::salvarFichas() {
    ofstream arquivo("fichas.txt");
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir arquivo de fichas para salvar.\n";
        return;
    }

    for (const auto& f : fichas) {
        // Campos Base: ID_FICHA;NOME_FICHA;
        arquivo << f->getId() << ";"
                << f->getNome() << ";";

        // Lista de IDs dos exercícios, separados por vírgula
        const auto& exerciciosFicha = f->getExercicios();
        for (size_t i = 0; i < exerciciosFicha.size(); ++i) {
            arquivo << exerciciosFicha[i]->getId();
            if (i < exerciciosFicha.size() - 1) {
                arquivo << ","; // Separador de IDs
            }
        }
        arquivo << endl; // Nova linha para a próxima ficha
    }
}

// carregar exercícios a partir de arquivo
void Sistema::carregarExercicios() {
    ifstream arquivo("exercicios.txt");
    if (!arquivo.is_open()) return; // Se não existir, apenas retorna

    exercicios.clear(); // Limpa o vetor antes de carregar

    string linha;
    int maiorId = 0;
    while (getline(arquivo, linha)) {
        stringstream ss(linha);
        string token;

        // Leitura dos campos comuns de Exercicio
        getline(ss, token, ';');
        int id = stoi(token);

        getline(ss, token, ';');
        int tipo = stoi(token); // 1=Cardio, 2=Forca

        string nome;
        getline(ss, nome, ';');

        getline(ss, token, ';');
        bool ativo = (token == "1");

        Exercicio* e = nullptr;

        if (tipo == 2) { // Forca
            double carga;
            int series, repeticoes, tempoDescanso;

            getline(ss, token, ';'); carga = stod(token);
            getline(ss, token, ';'); series = stoi(token);
            getline(ss, token, ';'); repeticoes = stoi(token);
            getline(ss, token, ';'); tempoDescanso = stoi(token);

            e = new Forca(id, nome, ativo, carga, series, repeticoes, tempoDescanso);

        } else if (tipo == 1) { // Cardio
            int duracao;
            double caloriasPorMinuto;

            getline(ss, token, ';'); duracao = stoi(token);
            getline(ss, token, ';'); caloriasPorMinuto = stod(token);

            e = new Cardio(id, nome, ativo, duracao, caloriasPorMinuto);
        }

        if (e) {
            exercicios.push_back(e);
            if (id > maiorId) maiorId = id;
        }
    }

    Exercicio::atualizarProximoId(maiorId);
}

// Carregar fichas a partir de arquivo 
void Sistema::carregarFichas() {
    ifstream arquivo("fichas.txt");
    if (!arquivo.is_open()) return;             // Verifica se arquivo abriu

    // Limpa o vetor de fichas antes de carregar
    for (auto* f : fichas) delete f;        
    fichas.clear();

    string linha;
    int maiorIdFicha = 0;

    while (getline(arquivo, linha)) {
        stringstream ss(linha);
        string token;

        // Leitura da Ficha
        getline(ss, token, ';');
        int idFicha = stoi(token);

        string nomeFicha;
        getline(ss, nomeFicha, ';');

        // Cria a ficha
        Ficha* f = new Ficha(idFicha, nomeFicha);
        
        // Leitura dos IDs dos exercícios
        string idsExerciciosStr;
        getline(ss, idsExerciciosStr);      // Lê o resto da linha

        stringstream ssIds(idsExerciciosStr);
        string idExStr;

        while (getline(ssIds, idExStr, ',')) {
            if (idExStr.empty()) continue;

            int idEx = stoi(idExStr);
            Exercicio* ex = buscarExercicioPorId(idEx);
            
            // Adiciona o exercício se ele for encontrado
            if (ex) {
                f->adicionarExercicio(ex);
            }
        }

        fichas.push_back(f);
        if (idFicha > maiorIdFicha) maiorIdFicha = idFicha;
    }

    Ficha::atualizarProximoId(maiorIdFicha);
}