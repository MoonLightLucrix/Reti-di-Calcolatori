# Avanti un altro… pacchetto!

Il gioco finale di **Avanti un altro.. (versione semplificata)** è arrivato al DMI e gli studenti del corso di Reti di Calcolatori hanno deciso di implementarlo tramite Socket TCP. Un generico studente dovrà rispondere in modo errato **<ins>a 10 domande</ins>.**

_**<ins>Avanti un altro… pacchetto! Dettagli implementativi:</ins>**_

Il server, dopo aver stabilito una connessione con il giocatore, memorizzerà il nome e genererà un nuomero casuale intero compreso tra 10.000 e 300.000 euro, rappresentante il montepremi. Il server, quindi, notificherà al client il seguente messaggio _"NOME-GIOCATORE stai giocando per un importo di K euro. Iniziamo?"_<br>
Ricevuta la conferma di inzio gioco, il server invierà una domanda alla volta e riceverà una risposta dal client.<br>
Ogni volta che il client risponderà "in modo errato" (ovvero sarà la risposta corretta per le regole del gioco), il montepremi verrà **scalato di 10.000 EURO** e il server comincerà dalla prima domanda (notificando prima al client il valore del montepremi).<br>
La domanda che il server invierà al client dovrà contenere solo due risposte (1 corretta e 1 sbagliata).<br>
Nel caso in cui il client indovina tutte le domande, allora il server invierà il seguente messaggio "Congratulazioni, hai vinto XX euro". Se il monepremi raggiungerà il valore 0, allora il server invierà al client "Hai perso!". In entrambi i casi, la connessione tra client e server terminerà.

Usare **<ins>Socket TCP</ins>** e **<ins>Protocollo IPv4</ins>!!**

---

Per compilare il programma usare il comando `make` su questa directory, se tutto è andato a buon fine gli eseguibili del Server e del Client si troveranno all'interno della directory `bin`.
