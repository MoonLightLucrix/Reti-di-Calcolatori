# Il pacchetto "Cocco Bello"

Gli studenti del corso di Reti di Calcolatori hanno deciso di implementare un tool per l'impresa "Cocco Bello", al fine di ottimizzare le vendite nelle spiagge libere di Catania.<br>
L'impresa metterà a disposizione una sequenza di prodotti con prezzo e quantità a disposizione. Un generico cliente richiederà la lista dei prodotti disponibili e potrà avere la possibilità di acquistare uno o più prodotti, specificandone la quantità. Dopo l'acquisto di un prodotto, la relativa quantità verrà aggiornata.<br>
Il servizio deve prevedere la possibilità di autenticare un utente prima dell'acquisto di un prodotto (<ins>non necessariamente deve essere implementata la funzione di registrazione</ins>)

Usare **<ins>Socket TCP</ins>** e **<ins>Protocollo IPv4</ins>**!!

---

### Istruzioni per la compilazione

Usare il comando `make` su questa directory, se la compilazione è andata a buon fine gli eseguibili verranno creati all'interno della directory `bin`.

---

### Profili con cui eseguire l'accesso

Avviato il client verrà richiesto di inserire prima un **username** e successivamente una **password** questi sono disponibili all'interno del file `tableUtente.txt` siccome la password salvata all'interno del file è codificata con un algoritmo Hash di tipo **SHA-256** e successivamente convertita in esadecimale, per eseguire l'accesso saranno forniti di seguito tutti gli username e le rispettive password per poter accedere al server e testare il corretto funzionamento del programma:

1. Username: _Ciccio_<br>
   Password: `BuongiornoATutti`

2. Username: _MatrixNeo_<br>
   Password: `NotoStreamerCatanese`

3. Username: _GattoVolante_<br>
   Password: `PiazzaArmerina`

4. Username: _StellaMare_<br>
   Password: `PizzaMargherita`

5. Username: _CiccioPasticcio_<br>
   Password: `SoleLuna`