Applicazione sviluppata in C++ per la gestione completa di un torneo di calcio. Il programma permette di gestire le squadre partecipanti (inserire, eliminare e modificare dati), registrare i risultati delle partite e visualizzare classifiche.

I dati vengono salvati su file di testo (squadre.txt e id_counter.txt).
Uso operazioni CRUD con un menu :

-Create (Aggiungi Squadra): 
    Inserimento di una nuova squadra con nome, città e allenatore. Assegnazione di  un ID univoco che incrementa.
-Read (Visualizza e Cerca):
    Classifica completa: Ordinata per punti, differenza reti e gol fatti.
    Ricerca: Possibilità di cercare una singola squadra tramite ID o nome per vedere le statistiche.
    Statistiche: Visualizzazione delle squadre con il miglior attacco (più gol fatti) e delle squadre ancora imbattute (0 sconfitte).
-Update (Registra Partita): 
    Inserendo l'ID di due squadre e il risultato della partita, si aggiornano i punti (3 per vittoria, 1 pareggio), le partite giocate e i gol.
-Delete (Rimuovi Squadra): 
    Eliminazione di una squadra dal torneo tramite il suo ID, con messaggio di conferma.