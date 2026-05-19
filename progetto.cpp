#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;


const string FILE_SQUADRE = "squadre.txt";
const string FILE_ID = "id_counter.txt"; //file che tiene conto del numero di squadre 
int MAX_SQUADRE = 100;

struct Squadra {
    int id;
    char nome[50];
    char citta[50];
    char allenatore[50];
    int giocate;
    int vinte;
    int pareggiate;
    int perse;
    int gol_fatti;
    int gol_subiti;
    int punti;
};

int leggiIdCounter();
void salvaIdCounter(int id);
int caricaSquadre(Squadra squadre[]);
void salvaSquadre(const Squadra squadre[], int n_squadre);
void aggiungiSquadra(Squadra squadre[], int& n_squadre);
void ordinaClassifica(Squadra squadre[], int n_squadre);
void visualizzaClassifica(Squadra squadre[], int n_squadre);
void ricercaSquadra(const Squadra squadre[], int n_squadre);
void squadrePiuGol(const Squadra squadre[], int n_squadre);
void squadreImbattute(const Squadra squadre[], int n_squadre);
void registraPartita(Squadra squadre[], int n_squadre);
void rimuoviSquadra(Squadra squadre[], int& n_squadre);
void menuVisualizzazione(Squadra squadre[], int n_squadre);

// 1. Legge il contatore ID dal file
int leggiIdCounter() {
    ifstream file(FILE_ID);
    int id = 1;
    if (file.is_open()) {
        file >> id;
        file.close();
    }
    return id;
}

// 2. Salva il contatore ID su file
void salvaIdCounter(int id) {
    ofstream file(FILE_ID);
    if (file.is_open()) {
        file << id;
        file.close();
    }
}

// 3. Aggiunge le squadre dal file 
int caricaSquadre(Squadra squadre[]) {
    ifstream file(FILE_SQUADRE);
    int cont = 0;
    if (file.is_open()) {
        while (file >> squadre[cont].id) {
            file.ignore(); // ignora lo spazio
            file.getline(squadre[cont].nome, 50, ';');
            file.getline(squadre[cont].citta, 50, ';');
            file.getline(squadre[cont].allenatore, 50, ';');
            file >> squadre[cont].giocate >> squadre[cont].vinte >> squadre[cont].pareggiate
                 >> squadre[cont].perse >> squadre[cont].gol_fatti >> squadre[cont].gol_subiti
                 >> squadre[cont].punti;
            cont++;
        }
        file.close();
    }
    return cont;
}

// 4. Salva le squadre su file 
void salvaSquadre(const Squadra squadre[], int n_squadre) {
    ofstream file(FILE_SQUADRE);
    if (file.is_open()) {
        for (int i = 0; i < n_squadre; i++) {
            file << squadre[i].id << " "
                 << squadre[i].nome << ";"
                 << squadre[i].citta << ";"
                 << squadre[i].allenatore << ";"
                 << squadre[i].giocate << " "
                 << squadre[i].vinte << " "
                 << squadre[i].pareggiate << " "
                 << squadre[i].perse << " "
                 << squadre[i].gol_fatti << " "
                 << squadre[i].gol_subiti << " "
                 << squadre[i].punti << "\n";
        }
        file.close();
    } else {
        cout << "Errore nel salvataggio del file squadre\n";
    }
}

// 5. CREATE Aggiunta di una nuova squadra
void aggiungiSquadra(Squadra squadre[], int& n_squadre) {
    if (n_squadre >= MAX_SQUADRE) {
        cout << "Raggiunto il limite massimo di squadre.\n";
        return;
    }
    
    Squadra s;
    s.id = leggiIdCounter();
    
    cout << "Inserisci nome squadra: ";
    cin.ignore();
    cin.getline(s.nome, 50);
    cout << "Inserisci citta': ";
    cin.getline(s.citta, 50);
    cout << "Inserisci allenatore: ";
    cin.getline(s.allenatore, 50);
    
    s.giocate = 0; s.vinte = 0; s.pareggiate = 0; s.perse = 0;
    s.gol_fatti = 0; s.gol_subiti = 0; s.punti = 0;
    
    squadre[n_squadre] = s;
    n_squadre++;
    
    salvaIdCounter(s.id + 1); // incrementa l'ID
    salvaSquadre(squadre, n_squadre);
    
    cout << "Squadra aggiunta con successo! ID: " << s.id << "\n";
}

// 6. Ordina la classifica per punti, differenza reti, gol fatti
void ordinaClassifica(Squadra squadre[], int n_squadre) {
    for (int i = 0; i < n_squadre - 1; i++) {
        for (int j = 0; j < n_squadre - i - 1; j++) {
            bool scambia = false;
            int diff_j = squadre[j].gol_fatti - squadre[j].gol_subiti;
            int diff_j1 = squadre[j+1].gol_fatti - squadre[j+1].gol_subiti;
            
            if (squadre[j].punti < squadre[j+1].punti) {
                scambia = true;
            } else if (squadre[j].punti == squadre[j+1].punti) {
                if (diff_j < diff_j1) {
                    scambia = true;
                } else if (diff_j == diff_j1) {
                    if (squadre[j].gol_fatti < squadre[j+1].gol_fatti) {
                        scambia = true;
                    }
                }
            }
            
            if (scambia) {
                Squadra temp = squadre[j];
                squadre[j] = squadre[j+1];
                squadre[j+1] = temp;
            }
        }
    }
}

// 7. READ: Visualizzazione classifica completa
void visualizzaClassifica(Squadra squadre[], int n_squadre) {
    if (n_squadre == 0) {
        cout << "Nessuna squadra presente.\n";
        return;
    }
    ordinaClassifica(squadre, n_squadre);
    
    cout << "\nCLASSIFICA\n";
    cout << "Pos\tID\tNome\t\tPt\tG\tV\tN\tP\tGF\tGS\tDR \n";
    for (int i = 0; i < n_squadre; i++) {
        cout << i+1 << "\t" << squadre[i].id << "\t" << squadre[i].nome << "\t\t"
             << squadre[i].punti << "\t" << squadre[i].giocate << "\t"
             << squadre[i].vinte << "\t" << squadre[i].pareggiate << "\t"
             << squadre[i].perse << "\t" << squadre[i].gol_fatti << "\t"
             << squadre[i].gol_subiti << "\t" << (squadre[i].gol_fatti - squadre[i].gol_subiti) << "\n";
    }
}

// 8. READ: Ricerca squadra per ID o Nome


void ricercaSquadra(const Squadra squadre[], int n_squadre) {
    cout << "Cerca per (1) ID o (2) Nome: ";
    int scelta;
    cin >> scelta;
    
    bool trovata = false;
    if (scelta == 1) {
        int id;
        cout << "Inserisci ID: ";
        cin >> id;
        for (int i = 0; i < n_squadre; i++) {
            if (squadre[i].id == id) {
                cout << "\nSquadra Trovata: " << squadre[i].nome << " (" << squadre[i].citta << ")\nAllenatore: " << squadre[i].allenatore << "\n";
                cout << "Punti: " << squadre[i].punti << " | Giocate: " << squadre[i].giocate << " | Vinte: " << squadre[i].vinte << " | Perse: " << squadre[i].perse <<
                "| Pareggiate: " << squadre[i].pareggiate << "\n"<<"| Gol fatti: " << squadre[i].gol_fatti << "\n" << "| Gol subiti: " << squadre[i].gol_subiti << "\n"
                << "| Differenza reti: " << (squadre[i].gol_fatti - squadre[i].gol_subiti) << "\n";
                trovata = true;
                break;
            }
        }
    } else {
        char nome[50];
        cout << "Inserisci Nome: ";
        cin.ignore();
        cin.getline(nome, 50);
        for (int i = 0; i < n_squadre; i++) {
            if (strcmp(squadre[i].nome, nome) == 0) {
                cout << "\nSquadra Trovata (ID " << squadre[i].id << ")\nCitta': " << squadre[i].citta << "\nAllenatore: " << squadre[i].allenatore << "\n";
                cout << "Punti: " << squadre[i].punti << " | Vinte: " << squadre[i].vinte << " | Perse: " << squadre[i].perse <<"| Pareggiate: " << squadre[i].pareggiate <<
                 "\n"<<"| Gol fatti: " << squadre[i].gol_fatti << "\n" << "| Gol subiti: " << squadre[i].gol_subiti << "\n"
                  << "| Differenza reti: " << (squadre[i].gol_fatti - squadre[i].gol_subiti) << "\n";
                trovata = true;
            }
        }
    }
    
    if (!trovata) cout << "Squadra non trovata.\n";
}



// 9. READ: Squadre con più gol segnati
void squadrePiuGol(const Squadra squadre[], int n_squadre) {
    if (n_squadre == 0) return;
    int max_gol = -1;
    for (int i = 0; i < n_squadre; i++) {
        if (squadre[i].gol_fatti > max_gol) max_gol = squadre[i].gol_fatti;
    }
    
    cout << "\nSquadre con piu' gol segnati (" << max_gol << " gol):\n";
    for (int i = 0; i < n_squadre; i++) {
        if (squadre[i].gol_fatti == max_gol) {
            cout << "- " << squadre[i].nome << "\n";
        }
    }
}

// 10. READ: Squadre imbattute
void squadreImbattute(const Squadra squadre[], int n_squadre) {
    cout << "\nSquadre ancora imbattute:\n";
    bool trovata = false;
    for (int i = 0; i < n_squadre; i++) {
        if (squadre[i].perse == 0 && squadre[i].giocate > 0) {
            cout << "- " << squadre[i].nome << "\n";
            trovata = true;
        }
    }
    if (!trovata) cout << "Nessuna squadra imbattuta (con almeno 1 partita giocata).\n";
}

// 11. UPDATE: Registra il risultato di una partita
void registraPartita(Squadra squadre[], int n_squadre) {
    int id1, id2, gol1, gol2;
    int idx1 = -1, idx2 = -1;
    
    visualizzaClassifica(squadre, n_squadre);
    cout << "\nInserisci ID Squadra Casa: "; cin >> id1;
    cout << "Inserisci ID Squadra Trasferta: "; cin >> id2;
    
    for (int i = 0; i < n_squadre; i++) {
        if (squadre[i].id == id1) idx1 = i;
        if (squadre[i].id == id2) idx2 = i;
    }
    
    if (idx1 == -1 || idx2 == -1 || idx1 == idx2) {
        cout << "ID non validi.\n";
        return;
    }
    
    cout << "Gol segnati da " << squadre[idx1].nome << ": "; cin >> gol1;
    cout << "Gol segnati da " << squadre[idx2].nome << ": "; cin >> gol2;
    
    // Aggiornamento statistiche squadra 1
    squadre[idx1].giocate++;
    squadre[idx1].gol_fatti += gol1;
    squadre[idx1].gol_subiti += gol2;
    
    // Aggiornamento statistiche squadra 2
    squadre[idx2].giocate++;
    squadre[idx2].gol_fatti += gol2;
    squadre[idx2].gol_subiti += gol1;
    
    // Gestione esito
    if (gol1 > gol2) {
        squadre[idx1].vinte++; squadre[idx1].punti += 3;
        squadre[idx2].perse++;
    } else if (gol1 < gol2) {
        squadre[idx2].vinte++; squadre[idx2].punti += 3;
        squadre[idx1].perse++;
    } else {
        squadre[idx1].pareggiate++; squadre[idx1].punti += 1;
        squadre[idx2].pareggiate++; squadre[idx2].punti += 1;
    }
    
    salvaSquadre(squadre, n_squadre);
    cout << "Risultato registrato con successo\n";
}

// 12. DELETE: Rimuovi una squadra
void rimuoviSquadra(Squadra squadre[], int& n_squadre) {
    int id;
    cout << "Inserisci l'ID della squadra da rimuovere: ";
    cin >> id;
    
    int idx = -1;
    for (int i = 0; i < n_squadre; i++) {
        if (squadre[i].id == id) {
            idx = i;
            break;
        }
    }
    
    if (idx == -1) {
        cout << "Squadra non trovata.\n";
        return;
    }
    
    cout << "Stai per rimuovere la squadra " << squadre[idx].nome << ". Sei sicuro? (s/n): ";
    char conferma;
    cin >> conferma;
    
    if (conferma == 's' || conferma == 'S') {
        for (int i = idx; i < n_squadre - 1; i++) {
            squadre[i] = squadre[i+1];
        }
        n_squadre--;
        salvaSquadre(squadre, n_squadre);
        cout << "Squadra rimossa.\n";
    } else {
        cout << "Operazione annullata.\n";
    }
}

// Menudi visualizzazione
void menuVisualizzazione(Squadra squadre[], int n_squadre) {
    int scelta;
    do {
        cout << "\nMENU VISUALIZZAZIONE E RICERCA\n";
        cout << "1. Classifica completa\n";
        cout << "2. Dettaglio singola squadra\n";
        cout << "3. Squadre con piu' gol segnati\n";
        cout << "4. Squadre imbattute\n";
        cout << "0. Torna al menu principale\n";
        cout << "Scelta: ";
        cin >> scelta;
        
        switch (scelta) {
            case 1: visualizzaClassifica(squadre, n_squadre); break;
            case 2: ricercaSquadra(squadre, n_squadre); break;
            case 3: squadrePiuGol(squadre, n_squadre); break;
            case 4: squadreImbattute(squadre, n_squadre); break;
        }
    } while (scelta != 0);
}

int main() {
    Squadra squadre[MAX_SQUADRE];
    int n_squadre = caricaSquadre(squadre);
    int scelta;
    
    do {
        cout << "\nGESTIONE TORNEO DI CALCIO\n";
        cout << "1. Aggiungi Squadra (CREATE)\n";
        cout << "2. Visualizzazione e Ricerca (READ)\n";
        cout << "3. Registra Risultato Partita (UPDATE)\n";
        cout << "4. Rimuovi Squadra (DELETE)\n";
        cout << "0. Esci\n";
        cout << "Scelta: ";
        cin >> scelta;
        
        switch (scelta) {
            case 1: aggiungiSquadra(squadre, n_squadre); 
                break;
            case 2: menuVisualizzazione(squadre, n_squadre); 
                break;
            case 3: registraPartita(squadre, n_squadre); 
                break;
            case 4: rimuoviSquadra(squadre, n_squadre); 
                break;
            case 0: cout << "Uscita dal programma.\n"; 
                break;
            default: cout << "Scelta non valida.\n"; 
                break;
        }
    } while (scelta != 0);
    
    return 0;
}


