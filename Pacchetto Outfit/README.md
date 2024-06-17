# Pacchetto Outfit!

Gli studendi di informatica del corso di Reti di Calcolatori hanno deciso di implementare un sistema centralizzato per l'acquisto di abiti online.

Un generico client invierà un _**Pacchetto Outfit**_ al server _**Outfit**_ al fine di effettuare una delle seguenti operazioni:

**1.** Chiedere la lista degli abiti disponibili (incluse taglie e prezzo)<br>
**2.** Acquistare uno o più abiti (scegliendo anche la quantità)<br>
**3.** Fare il reso di un abito (il prodotto viene restituito e aggiornata la lista degli abiti disponibili)<br>
**4.** Concludere l'operazione (quando il client invia la parola "FINE" la connessione verrà cancellata e il processo client terminerà la sua esecuzione)<br>

Il server restituirà i seguenti messaggi in base all'operazione scelta dal client:
- Per l'operazione numero 2, il server, oltre ad inviare la lista degli abiti scelti (con tutti i dettagli elencati precedentemente), invierà il messaggio "Sei sicuro di voler confermare l'operazione?". Se il client risponde con "Si" allora il server risponderà con il messaggio "Operazione effettuata", altrimenti se la risposta sarà "No" il server invierà il messaggio "Operazione annullata". In quest'ultimo caso, il client potrà scegliere di effettuare una delle 4 operazione precedentemente elencate.
- Per l'operazione numero 3, il server invierà il messaggio "Sei sicuro di voler confermare l'operazione?". Se il client risponde con "Si" allora il server risponderà con il messaggio "Reso effettuato", altrimenti se la risposta sarà "No" il server invierà il messaggio "Reso annullato". In quest'ultimo caso, il client potrà scegliere di effettuare una delle 4 operazioni precedentemente elencate.

Usare **<ins>Socket TCP</ins>**!! e **<ins>Protocollo IPv4</ins>**.

---

Per compilare il programma usare il comando `make`, se tutto è andato a buon fine gli eseguibili del Server e del Client si troveranno all'interno della directory `bin`.
