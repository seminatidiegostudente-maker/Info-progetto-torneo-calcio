#include <iostream>
#include <fstream>
#include <string>

using namespace std;


struct squadra{
    int id; //generato casualmente
    string nome;
    string città;
    string allenatore;
    int statistiche[4]; //statistiche[0] = partite gioc, statistiche[1] = vinte, statistiche[2] = perse, statistiche[3] =pareggi
    int gol[2]; //gol[0] = gol fatti, gol[1] = gol subiti
    int punti;
};

void menu();
void inizializzaStatZero();
void inizializzaGoalZero();
void AggiungiSquadra();
void RicercaSquadrabyID();
void RicercaSquadrabyNome();
void Classifica();
void ListaGol();
void SquadraImbattuta();
void RisultatoPartita();

int main(){
    
}
