//
//  main.c
//  linguagemC
//
//  Created by Carlos Barcelos on 25/08/19.
//  Copyright © 2019 Carlos Barcelos. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 100

typedef struct pupilsList Plist;
typedef struct pupils Pupils;

//Function invocation
Plist* createList(void);
Pupils readPupil(Pupils alunos, Plist* pointer);
void includePupil(Pupils pupil, Plist* pointer, int position);
void insertIntoLast(Plist* pointer, Pupils pupil);
void insertIntoFirst(Plist* pointer, Pupils pupil);
void insertAfterName(char searchedName[MAX], Plist* pointer, Pupils pupil);
void searchForName(char searchedName[MAX], Plist* pointer);
void deleteFirst(Plist* pointer);
void deleteLast(Plist* pointer);
void deleteForId(Plist* pointer, int searchedId);
void printMedia(Plist* pointer, int id);
void printFunc(int i, Plist* pointer);

//Structs
struct pupils {
    int id, phone;
    float g1, g2;
    char mail[MAX], name[MAX];
};


struct pupilsList {
    Pupils pupils[MAX];
    int fl;
};

//Main
int main() {
    int option = 0, cont, searchedId;
    char searchedName[MAX];
    Plist* listaAlunos = NULL;
    Pupils alunos;
    do {
        fpurge(stdin);
        printf("\n**************\nMENU PRINCIPAL\n**************\n");
        printf("1 - Criar lista\n2 - Incluir no final\n3 - Incluir no início\n4 - Incluir após um nome(ler um nome, encontrar na lista e incluir na posição posterior)\n5 - Consultar por nome (ler um nome e mostrar o registro do nome procurado)\n6 - Excluir do início\n7 - Excluir do fim\n8 - Excluir por código\n9 - Listar todos os registros\n10 - Listar com médias finais ( listar os nomes dos alunos com suas médias finais calculadas)\n11 - Sair\n");
        scanf("%d", &option);
        switch (option) {
            case 1:
                if (listaAlunos == NULL) {
                    listaAlunos = createList();
                    printf("*---- Cadastre o primeiro aluno ----*\n");
                    includePupil(readPupil(alunos, listaAlunos), listaAlunos, 0);
                } else {
                    printf("Você já tem uma lista criada!\n");
                }
                break;
            case 2:
                if (listaAlunos != NULL) {
                    printf("\n*---- Inserir novo aluno no final da lista ----*\n");
                    insertIntoLast(listaAlunos, readPupil(alunos, listaAlunos));
                    printf("Você incluiu no final da lista o aluno chamado %s\n", listaAlunos -> pupils[listaAlunos -> fl].name);
                } else {
                    printf("Você não criou uma lista! Selecione a opção 1 para criar.\n");
                }
                break;
            case 3:
                if (listaAlunos != NULL) {
                    printf("\n*---- Inserir novo aluno no início da lista ----*\n");
                    insertIntoFirst(listaAlunos, readPupil(alunos, listaAlunos));
                    printf("Você incluiu no inicio da lista o aluno chamado %s\n", listaAlunos -> pupils[0].name);
                } else {
                    printf("Você não criou uma lista! Selecione a opção 1 para criar.\n");
                }
                break;
            case 4:
                if (listaAlunos != NULL) {
                    printf("*---- Insira o nome que você deseja inserir após ----*\n");
                    fpurge(stdin);
                    fgets(searchedName, MAX, stdin);
                    insertAfterName(searchedName, listaAlunos, readPupil(alunos, listaAlunos));
                } else {
                    printf("Você não criou uma lista! Selecione a opção 1 para criar.\n");
                }
                break;
            case 5:
                if (listaAlunos != NULL) {
                    printf("*---- Insira o nome que você deseja buscar ----*\n");
                    fpurge(stdin);
                    fgets(searchedName, MAX, stdin);
                    searchForName(searchedName, listaAlunos);
                } else {
                    printf("Você não criou uma lista! Selecione a opção 1 para criar.\n");
                }
                break;
            case 6:
                if (listaAlunos != NULL) {
                    deleteFirst(listaAlunos);
                } else {
                    printf("Você não criou uma lista! Selecione a opção 1 para criar.\n");
                }
                break;
            case 7:
                if (listaAlunos != NULL) {
                    deleteLast(listaAlunos);
                } else {
                    printf("Você não criou uma lista! Selecione a opção 1 para criar.\n");
                }
                break;
            case 8:
                if (listaAlunos != NULL) {
                    printf("*---- Insira o código do aluno que você deseja excluir ----*\n");
                    scanf("%d", &searchedId);
                    deleteForId(listaAlunos, searchedId);
                } else {
                    printf("Você não criou uma lista! Selecione a opção 1 para criar.\n");
                }
                break;
            case 9:
                if (listaAlunos != NULL) {
                    if (listaAlunos -> fl >= 0){
                        printf("\n*---- Alunos inseridos na lista ----*\n");
                        for (int i = 0; i <= listaAlunos -> fl; i++){
                            printFunc(i, listaAlunos);
                        }
                    } else {
                        printf("A lista não contém nenhum aluno!\n");
                    }
                } else {
                    printf("Você não criou uma lista! Selecione a opção 1 para criar.\n");
                }
                break;
            case 10:
                if (listaAlunos != NULL) {
                    printf("\n*---- Media dos alunos ----*\n");
                    for (cont = 0; cont <= listaAlunos -> fl; cont++){
                        printMedia(listaAlunos, cont);
                    }
                } else {
                    printf("Você não criou uma lista! Selecione a opção 1 para criar.\n");
                }
                break;
            case 11:
                break;
            default:
                printf("Você deve escolher uma opção válida! [1 - 11]\n");
                break;
        }
    } while (option != 11);
}

//Functions
Plist* createList(void) {
    Plist* pointer = (Plist*)malloc(sizeof(Plist));
    if (pointer != NULL) {
        pointer -> fl = 0;
        printf("\n**************************\nUma nova lista foi criada!\n**************************\n");
    }
    return pointer;
}

Pupils readPupil(Pupils alunos, Plist* pointer){
    int i;
    bool test = false;
    printf("Codigo: ");
    do{
        scanf("%d", &alunos.id);
        for (i = 0; i <= pointer -> fl; i++){
            if (alunos.id == pointer -> pupils[i].id){
                printf("O código digitado já está em uso!\n");
                test = true;
                break;
            } else {
                test = false;
            }
        }
    } while (test == true);
    printf("Nome: ");
    fpurge(stdin);
    fgets(alunos.name, MAX, stdin);
    printf("Telefone: ");
    scanf("%d", &alunos.phone);
    printf("E-mail: ");
    fpurge(stdin);
    fgets(alunos.mail, MAX, stdin);
    printf("Nota G1: ");
    do {
        scanf("%f", &alunos.g1);
        if (alunos.g1 < 0 || alunos.g1 > 10){
            printf("A nota deve ser entre 0 ~ 10!\n");
        }
    } while (alunos.g1 < 0 || alunos.g1 > 10);
    printf("Nota G2: ");
    do {
        scanf("%f", &alunos.g2);
        if (alunos.g2 < 0 || alunos.g2 > 10){
            printf("A nota deve ser entre 0 ~ 10!\n");
        }
    } while (alunos.g2 < 0 || alunos.g2 > 10);
    
    return alunos;
}

void includePupil(Pupils pupil, Plist* pointer, int position){
        pointer -> pupils[position] = pupil;
}

void printFunc(int i, Plist* pointer) {
    printf("Codigo: %d\n", pointer -> pupils[i].id);
    printf("Nome: %s", pointer -> pupils[i].name);
    printf("Telefone: %d\n", pointer -> pupils[i].phone);
    printf("E-mail: %s", pointer -> pupils[i].mail);
    printf("G1: %.2f\n", pointer -> pupils[i].g1);
    printf("G2: %.2f\n\n", pointer -> pupils[i].g2);
}

void clearPupil(Plist* pointer, int position){
    Pupils emptyPupil;
    pointer -> pupils[position].id = 0;
    strcpy(pointer -> pupils[position].name, emptyPupil.name);
    pointer -> pupils[position].phone = emptyPupil.phone;
    strcpy(pointer -> pupils[position].mail, emptyPupil.mail);
    pointer -> pupils[position].g1 = emptyPupil.g1;
    pointer -> pupils[position].g2 = emptyPupil.g2;
}


void insertIntoLast(Plist* pointer, Pupils pupil) {
    char option;
    if (pointer -> fl < 100){
        pointer -> fl++;
        pointer -> pupils[pointer -> fl] = pupil;
    } else {
        printf("Sua lista já está completa, não é possível adicionar ao fim!\n Deseja sobreescrever o último da lista? (s / n)\n");
        do {
            fpurge(stdin);
            fgets(&option, 1, stdin);
            if (option == 's' || option == 'S'){
                pointer -> pupils[99] = pupil;
            } else if (option == 'n' || option == 'N') {
                break;
            } else {
                printf("Opção inválida!\n");
            }
        } while (option != 'n' && option != 'N');
    }
}

void insertIntoFirst(Plist* pointer, Pupils pupil){
    int i;
    pointer -> fl++;
    for (i = pointer -> fl; i >= 0; i--) {
        if(i == 0) {
            pointer -> pupils[i] = pupil;
        } else {
            pointer -> pupils[i] = pointer -> pupils[i - 1];
        }
    }
}

void insertAfterName(char searchedName[MAX], Plist* pointer, Pupils pupil){
    int i, j;
    for (i = 0; i <= pointer -> fl; i++){
        if (strcmp(pointer -> pupils[i].name, searchedName) == 0) {
            pointer -> fl++;
            for (j = pointer -> fl; j >= i; j--) {
                pointer -> pupils[j] = pointer -> pupils[j - 1];
                if(j == i + 1) {
                    pointer -> pupils[j] = pupil;
                    break;
                }
            }
        } else {
            printf("O nome %s não está na lista! Lembre-se de respeitar letras MAIÚSCULAS e minúsculas.\n", searchedName);
        }
    }
}

void searchForName(char searchedName[MAX], Plist* pointer){
    int i;
    for (i = 0; i <= pointer -> fl; i++){
        if (strcmp(pointer -> pupils[i].name, searchedName) == 0) {
            printf("\nAluno encontrado na posição %d\n", i);
            printFunc(i, pointer);
        } else {
            printf("O nome %s não está na lista! Lembre-se de respeitar letras MAIÚSCULAS e minúsculas.\n", searchedName);
        }
    }
}

void deleteFirst(Plist* pointer){
    int i;
    printf("Você removeu da lista o aluno na primeira posição - Nome: %s", pointer -> pupils[0].name);
    for (i = 0; i < pointer -> fl; i++) {
        pointer -> pupils[i] = pointer -> pupils[i + 1];
    }
    pointer -> fl--;
}

void deleteLast(Plist* pointer){
    printf("Você removeu da lista o aluno na última posição - Nome: %s", pointer -> pupils[pointer -> fl].name);
    pointer -> fl --;
}

void deleteForId(Plist* pointer, int searchedId){
    int i;
    for (i = 0; i <= pointer -> fl; i++){
        if (pointer -> pupils[i].id == searchedId) {
            printf("Você removeu da lista o aluno chamado: %s", pointer -> pupils[i].name);
            clearPupil(pointer, i);
        } else {
            printf("O código procurado não existe!\n");
        }
    }
}

void printMedia(Plist* pointer, int id){
    float media;
    media = (pointer -> pupils[id].g1 + (pointer -> pupils[id].g2 * 2)) / 3;
    printf("Aluno: %s", pointer -> pupils[id].name);
    printf("Media: %.2f\n", media);
    printf("*---- // ----*\n");
}
