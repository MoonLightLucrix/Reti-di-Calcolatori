### TRIS

Gli studenti del corso di Reti di Calcolatori del DMI - UNICT hanno deciso, di loro spontanea volontà, di realizzare il gioco del Tris in modalità client-server.

Realizzare un programma scritto in c (o c++) che simuli una partita a "Tris" fra i due **Client**, con il **Server** in mezzo a fare da arbitro. Si assuma che il numero di giocatori sia esattamente 2 e che tutti rispettino il protocollo descritto.
Appena avviato, ogni **Client** si connette al **Server** per registrarsi, fornendo anche le informazioni che il **Server** userà per comunicare durante la partita (ip, porta).
Quando entrambi i **Client** si sono registrati, il **Server** avvia la partita.
Inizia quindi ad interpellare a turno i due giocatori, chiedendo dove porre il loro simbolo sulla griglia. Dopo ogni mossa, il **Server** risponde inviando la griglia aggiornata.
Quando un giocatore ha vinto, il **Server** invia un messaggio di vittoria al vincitore e di sconfitta al perdente, quindi termina la partita.

#### Note e suggerimenti
- Si vince quando ci sono 3 segni uguali in orizzontale, verticale o diagonale.
- I Client dovranno attendere il proprio turno per giocare, probabilmente bloccati da una `recvfrom`, `recv` o `read`.
- Ad ogni mossa, il client indica riga e colonna dove inserire il proprio segno, che verrà inserito sulla casella vuota indicata.
- Non è possibile sovrascrivere una casella già segnata.
- Ogni turno verrà inviata la griglia ai due client, che avrà l'aspetto come:

```
1 |O| | |
2 | |X| |
3 |X|O| |
   1 2 3 