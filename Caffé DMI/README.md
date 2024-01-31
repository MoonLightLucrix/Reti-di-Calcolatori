# Caffè DMI

Gli studenti di informatica del corso di Reti di Calcolatori hanno deciso di implementare un sistema centralizzato per una nuova gestione delle macchinette del caffè del DMI posizionati nei vari blocchi (1,2,3).

Un generico client (che sarà associato ad una specifica LAN in base al blocco di appartenenza), si collegherà al server ***Caffè DMI*** (**<ins>stabilirà una concessione</ins>**) ed effettuerà, in modo sequenziale le seguenti operazioni:

1. Il client riceverà (dal server) l'elenco di tutti i prodotti disponibili. Il client visualizzerà i prodotti secondo il seguente schema:<br>
    ***ID_prodotto_1, Nome_Prodotto_1, Prezzo_1, Quantità_1***<br>
    ***ID_prodotto_2, Nome_Prodotto_2, Prezzo_2, Quantità_2***<br>
    ***......***<br>
    ***ID_prodotto_N, Nome_Prodotto_N, Prezzo_N, Quantità_N***<br>
2. Il client, invierà la seguente stringa, contenente il prodotto scelto:<br>
    ***ID_prodotto, quantità***
3. Nel caso in cui la quantità non è disponibile, il server notificherà il messaggio "quantità non disponibile". Altrimenti, verrà mandato il messaggio "Prodotto erogato". In quest'ultimo caso, il server aggiornerà la quantità disponibile per quel prodotto.
4. Il client inserirà il carattere "c" per continuare (in questo caso si riparte dal punto 1), oppure il carattere "q" per concludere l'acquisto (in questo caso la connessione con il server si concluderà).

Usare **<ins>SocketTCP</ins>!!** e **<ins>Protocollo IPv4</ins>**