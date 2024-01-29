# Il pacchetto "Christmas"!

Gli studenti d'informatica del corso di Reti di Calcolatori hanno deciso di implementare un server **Christmas** in grado di ricevere e gestire i bigliettini di Natale contenenti messaggi del tipo "*Oggi supererò il laboratorio di Reti*".

Un generico client avrà la possibiltà di
- inviare un messaggio al server
- fare una richiesta per ricevere tutti i messaggi giù inviati (solo dello specifico client).
- Modificare e/o cancellare un messaggio specifico.

Il server dovrà essere progettato in modo da memorizzare qualsiasi messaggio (associandolo allo specifico client) e gestire le operazioni precedentemente elencate.

**Quando il client invierà il carattere "q",** il programma (per lo specifico client) terminerà.

Usare **<ins>Socket UDP</ins>!!** e **<ins>Protocollo IPv4</ins>**