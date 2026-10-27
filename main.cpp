#include <iostream>
using namespace std;

struct Fila {
    struct Conteudo {
        char nome[100];
        Conteudo* prox;
    };

    struct Disciplina {
        char nome[100];
        int creditos;
        Conteudo* conteudos;
        Disciplina* prox;
    };

    struct Aluno {
        char nome[100];
        char cpf[15];
        int idade;
        int matricula;
        Disciplina* disciplinas;
        Aluno* prox;
    };

    Aluno* inicio = NULL;
    Aluno* fim = NULL;
};

bool comparar(char a[], char b[]) {
    int i = 0;

    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i])
            return false;

        i++;
    }

    return a[i] == b[i];
}

void copiar(char destino[], char origem[]) {
    int i = 0;

    while (origem[i] != '\0') {
        destino[i] = origem[i];
        i++;
    }

    destino[i] = '\0';
}

bool vazia(Fila &f) {
    return f.inicio == NULL;
}

Fila::Aluno* buscarAluno(Fila &f, int mat) {
    Fila::Aluno* aux = f.inicio;

    while (aux != NULL) {
        if (aux->matricula == mat)
            return aux;

        aux = aux->prox;
    }

    return NULL;
}

Fila::Disciplina* buscarDisciplina(Fila::Aluno* a, char nome[]) {
    Fila::Disciplina* aux = a->disciplinas;

    while (aux != NULL) {
        if (comparar(aux->nome, nome))
            return aux;

        aux = aux->prox;
    }

    return NULL;
}

void inserir(Fila &f) {
    Fila::Aluno* novo = new Fila::Aluno;

    cout << "Nome: ";
    cin >> ws;
    cin.getline(novo->nome, 100);

    cout << "CPF: ";
    cin.getline(novo->cpf, 15);

    cout << "Idade: ";
    cin >> novo->idade;

    cout << "Matricula: ";
    cin >> novo->matricula;

    if (buscarAluno(f, novo->matricula) != NULL) {
        cout << "Matricula ja existe!\n";
        delete novo;
        return;
    }

    novo->disciplinas = NULL;
    novo->prox = NULL;

    if (vazia(f)) {
        f.inicio = novo;
        f.fim = novo;
    } else {
        f.fim->prox = novo;
        f.fim = novo;
    }

    cout << "Aluno inserido!\n";
}

void limparConteudos(Fila::Conteudo* c) {
    while (c != NULL) {
        Fila::Conteudo* aux = c;
        c = c->prox;
        delete aux;
    }
}

void limparDisciplinas(Fila::Disciplina* d) {
    while (d != NULL) {
        Fila::Disciplina* aux = d;
        d = d->prox;

        limparConteudos(aux->conteudos);
        delete aux;
    }
}

void remover(Fila &f) {
    if (vazia(f)) {
        cout << "Fila vazia!\n";
        return;
    }

    Fila::Aluno* aux = f.inicio;
    f.inicio = f.inicio->prox;

    if (f.inicio == NULL)
        f.fim = NULL;

    limparDisciplinas(aux->disciplinas);
    delete aux;

    cout << "Aluno removido!\n";
}

void primeiro(Fila &f) {
    if (vazia(f)) {
        cout << "Fila vazia!\n";
        return;
    }

    cout << "Nome: " << f.inicio->nome << endl;
    cout << "Matricula: " << f.inicio->matricula << endl;
}

int tamanho(Fila &f) {
    int cont = 0;
    Fila::Aluno* aux = f.inicio;

    while (aux != NULL) {
        cont++;
        aux = aux->prox;
    }

    return cont;
}

void addDisciplina(Fila &f) {
    int mat;
    char nome[100];

    cout << "Matricula: ";
    cin >> mat;

    Fila::Aluno* a = buscarAluno(f, mat);

    if (a == NULL) {
        cout << "Aluno nao encontrado!\n";
        return;
    }

    cout << "Disciplina: ";
    cin >> ws;
    cin.getline(nome, 100);

    if (buscarDisciplina(a, nome) != NULL) {
        cout << "Disciplina ja existe!\n";
        return;
    }

    Fila::Disciplina* novo = new Fila::Disciplina;

    copiar(novo->nome, nome);

    cout << "Creditos: ";
    cin >> novo->creditos;

    novo->conteudos = NULL;
    novo->prox = NULL;

    if (a->disciplinas == NULL) {
        a->disciplinas = novo;
    } else {
        Fila::Disciplina* aux = a->disciplinas;

        while (aux->prox != NULL)
            aux = aux->prox;

        aux->prox = novo;
    }

    cout << "Disciplina adicionada!\n";
}

void removerDisciplina(Fila &f) {
    int mat;
    char nome[100];

    cout << "Matricula: ";
    cin >> mat;

    Fila::Aluno* a = buscarAluno(f, mat);

    if (a == NULL) {
        cout << "Aluno nao encontrado!\n";
        return;
    }

    cout << "Disciplina: ";
    cin >> ws;
    cin.getline(nome, 100);

    Fila::Disciplina* aux = a->disciplinas;
    Fila::Disciplina* ant = NULL;

    while (aux != NULL && !comparar(aux->nome, nome)) {
        ant = aux;
        aux = aux->prox;
    }

    if (aux == NULL) {
        cout << "Disciplina nao encontrada!\n";
        return;
    }

    if (ant == NULL)
        a->disciplinas = aux->prox;
    else
        ant->prox = aux->prox;

    limparConteudos(aux->conteudos);
    delete aux;

    cout << "Disciplina removida!\n";
}

void listarDisciplinas(Fila &f) {
    int mat;

    cout << "Matricula: ";
    cin >> mat;

    Fila::Aluno* a = buscarAluno(f, mat);

    if (a == NULL) {
        cout << "Aluno nao encontrado!\n";
        return;
    }

    Fila::Disciplina* aux = a->disciplinas;

    if (aux == NULL) {
        cout << "Sem disciplinas!\n";
        return;
    }

    while (aux != NULL) {
        cout << "Disciplina: " << aux->nome << endl;
        cout << "Creditos: " << aux->creditos << endl;

        aux = aux->prox;
    }
}

void addConteudo(Fila &f) {
    int mat;
    char nome[100];

    cout << "Matricula: ";
    cin >> mat;

    Fila::Aluno* a = buscarAluno(f, mat);

    if (a == NULL) {
        cout << "Aluno nao encontrado!\n";
        return;
    }

    cout << "Disciplina: ";
    cin >> ws;
    cin.getline(nome, 100);

    Fila::Disciplina* d = buscarDisciplina(a, nome);

    if (d == NULL) {
        cout << "Disciplina nao encontrada!\n";
        return;
    }

    Fila::Conteudo* novo = new Fila::Conteudo;

    cout << "Conteudo: ";
    cin.getline(novo->nome, 100);

    novo->prox = NULL;

    if (d->conteudos == NULL) {
        d->conteudos = novo;
    } else {
        Fila::Conteudo* aux = d->conteudos;

        while (aux->prox != NULL)
            aux = aux->prox;

        aux->prox = novo;
    }

    cout << "Conteudo adicionado!\n";
}

void removerConteudo(Fila &f) {
    int mat;
    char nome[100], conteudo[100];

    cout << "Matricula: ";
    cin >> mat;

    Fila::Aluno* a = buscarAluno(f, mat);

    if (a == NULL) {
        cout << "Aluno nao encontrado!\n";
        return;
    }

    cout << "Disciplina: ";
    cin >> ws;
    cin.getline(nome, 100);

    Fila::Disciplina* d = buscarDisciplina(a, nome);

    if (d == NULL) {
        cout << "Disciplina nao encontrada!\n";
        return;
    }

    cout << "Conteudo: ";
    cin.getline(conteudo, 100);

    Fila::Conteudo* aux = d->conteudos;
    Fila::Conteudo* ant = NULL;

    while (aux != NULL && !comparar(aux->nome, conteudo)) {
        ant = aux;
        aux = aux->prox;
    }

    if (aux == NULL) {
        cout << "Conteudo nao encontrado!\n";
        return;
    }

    if (ant == NULL)
        d->conteudos = aux->prox;
    else
        ant->prox = aux->prox;

    delete aux;

    cout << "Conteudo removido!\n";
}

void listarConteudos(Fila &f) {
    int mat;
    char nome[100];

    cout << "Matricula: ";
    cin >> mat;

    Fila::Aluno* a = buscarAluno(f, mat);

    if (a == NULL) {
        cout << "Aluno nao encontrado!\n";
        return;
    }
    cout << "Disciplina: ";
    cin >> ws;
    cin.getline(nome, 100);

    Fila::Disciplina* d = buscarDisciplina(a, nome);

    if (d == NULL) {
        cout << "Disciplina nao encontrada!\n";
        return;
    }

    Fila::Conteudo* aux = d->conteudos;

    if (aux == NULL) {
        cout << "Sem conteudos!\n";
        return;
    }

    while (aux != NULL) {
        cout << "Conteudo: " << aux->nome << endl;
        aux = aux->prox;
    }
}

void listar(Fila &f) {
    if (vazia(f)) {
        cout << "Fila vazia!\n";
        return;
    }

    Fila::Aluno* a = f.inicio;

    while (a != NULL) {
        cout << "\nNome: " << a->nome << endl;
        cout << "CPF: " << a->cpf << endl;
        cout << "Idade: " << a->idade << endl;
        cout << "Matrcula: " << a->matricula << endl;

        Fila::Disciplina* d = a->disciplinas;

        if (d == NULL)
            cout << "Sem disciplinas!\n";

        while (d != NULL) {
            cout << "Disciplina: " << d->nome << endl;
            cout << "Credtos: " << d->creditos << endl;

            Fila::Conteudo* c = d->conteudos;

            if (c == NULL)
                cout << "Sem conteudos!\n";

            while (c != NULL) {
                cout << "Conteudo: " << c->nome << endl;
                c = c->prox;
            }

            d = d->prox;
        }

        cout << "--------------------\n";
        a = a->prox;
    }
}

int main() {
    Fila f;
    int op;

    do {
        cout << "\n1 - Inserir aluno";
        cout << "\n2 - Remover aluno";
        cout << "\n3 - Primeiro aluno";
        cout << "\n4 - Tamanho";
        cout << "\n5 - Adicionar disciplina";
        cout << "\n6 - Remover disciplina";
        cout << "\n7 - Listar disciplinas";
        cout << "\n8 - Adicionar conteudo";
        cout << "\n9 - Remover conteudo";
        cout << "\n10 - Listar conteudos";
        cout << "\n11 - Listar alunos";
        cout << "\n0 - Sair";
        cout << "\nOpcao: ";
        cin >> op;

        switch (op) {
            case 1:
                inserir(f);
                break;

            case 2:
                remover(f);
                break;

            case 3:
                primeiro(f);
                break;

            case 4:
                cout << "Tamanho: " << tamanho(f) << endl;
                break;

            case 5:
                addDisciplina(f);
                break;

            case 6:
                removerDisciplina(f);
                break;

            case 7:
                listarDisciplinas(f);
                break;

            case 8:
                addConteudo(f);
                break;

            case 9:
                removerConteudo(f);
                break;

            case 10:
                listarConteudos(f);
                break;

            case 11:
                listar(f);
                break;

            case 0:
                cout << "Saindo...\n";
                break;

            default:
                cout << "Opcao invalida!\n";
        }

    } while (op != 0);

    while (!vazia(f)) {
        Fila::Aluno* aux = f.inicio;
        f.inicio = aux->prox;

        limparDisciplinas(aux->disciplinas);
        delete aux;
    }

    f.fim = NULL;

    return 0;
}