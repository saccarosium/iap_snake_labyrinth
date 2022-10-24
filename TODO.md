# Coso che gestisce mappa @Luca_Barban

- [ ] far muovere il personaggio senza andare sui muri
    - [ ] registrare ogni singola mossa del giocatore
- [ ] gestire punteggio
- [ ] gestire come interagire coi nemici
- [ ] implementare portali che portalano ad un altra parte della mappa

*facoltativo*

- [ ] genera una mappa casuale ad ogni gioco

# Coso che gestisce UI @Luca_Saccarola

- [ ] implementare un menu iniziale
    - [ ] modalita di gioco (interattiva e AI)
    - [ ] opzioni custom
      * navigazione (HJKL, WASD, ARROWS)
      * personaggio
      * colorscheme
- [ ] mappa al centro che si scala in automatico a seconda del terminale (se terminale troppo piccolo stampare errore)
- [ ] leggenda mutabile dei keybindings

# Coso che risolve il labirinto @Paolo_Mozzoni

- [ ] algoritmo che solve con miglior punteggio
- [ ] algoritmo sempre destra
- [ ] algoritmo random

# Q&A

- [x] cosa viene compilato per il codice (se po usa make)?
    - si
- [x] si puo usa altri comandi oltre ad NSWO?
    - quello che vogliamo

# Notes

- funzioni prefissate dal nome del file
```c
    // file: ai.c
    ai_search_path();
```

- generalmente converrebbe avere all'interno del file una struttura con lo stesso nome
```c
    // file: ai.c
    typedef struct ai {
        // ...
    } ai;
```

- avere una funzione per allocare e inizializzare le varie strutture
```c
    ai *ai_create() {
        ai *a = xmalloc(sizeof(ai));
        // set stuff up

        return a;
    }
```
