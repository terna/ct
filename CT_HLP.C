#include "ct.h"

/*-------------------------------------------------------------------------*/
													/* ct_hlp.c */
	void Help(int videoStampa, float vers)
	{

	FILE *help;

	if (videoStampa==1) help=stdout;
	if (videoStampa==2) help=stdprn;

        /* verso stdprn, con il compilatore bc v2,
           \n genera lf, ma non cr; il problema si risolve indicando \n\r
	   che sembra non dare inconvenienti con tc, nÇ verso  stdprn, nÇ
           verso stdout                                                    */

fprintf(help,"v.%.2f › "
"Uso: 'ct nome [/m|M]'. nome.ct (l'estensione .ct ä obblig., ma non\n\r"
"deve essere scritta) ä un file contenente le informazioni che seguono e\n\r"
" /m rappresenta l'opzione di funzion. muto del programma, per l'uso batch\n\r"
"(/M esclude gli output su video, per aumentare la velocitÖ).\n\r"
"- # pe input; # pe hidden (mod. in ct); # pe output;\n\r"
"- # operatori+operandi max in ciascuna formula dei target (compreso ' ;');\n\r"
"- valore innesco dei # casuali, modificabile in ct (int. tra 0 e 65525);\n\r"
"- # tot. cicli (mod. in ct); # cicli cui corrisp. un calcolo di err. medio\n\r"
"  o un * in out. se 'muto' (meglio se sottomultiplo del prec. # tot. cicli);\n\r"
"- fattore di scala (modificabile in ct); nel dubbio 0.8;\n\r"
"- range dei pesi casuali (Ò il # indicato, modificabile in ct);\n\r"
"- nome dei file di servizio, con varie estensioni (modificabile in ct);\n\r",
vers);
fprintf(help,
"- learning r. (Ó) e momentum (‡) tra input  e hidden (modif. in ct);\n\r"
"- learning r. (Ó) e momentum (‡) tra hidden e output (modif. in ct);\n\r"
"- s|n per scegliere se calc. le deriv. ÎaO/ÎaI su val. 'medi' 0.5 delle aI;\n\r"
"      (la scelta ä modificabile in ct).\n\r");
fprintf(help,
"- una coppia di valori min-max per ogni nodo di input e di output (nell'\n\r"
"  ordine dei nodi di input e quindi di output), con un eventuale valore iniz.\n\r"
"  (per i nodi input o output) scritto @val senza spazi dopo @, prima del min.\n\r"
"  NB, i val. iniz. dei nodi output valgono anche per i target (se necess.).\n\r");

if (videoStampa==1){
printf("Premere un tasto per continuare.");getch();
printf(cancellaSchermo);}
else fprintf(help,"\n\r\n\r--------------------\n\r");

fprintf(help,
"  PER I NODI DI INPUT (con una indicazione, in sequenza, per ciascuno):\n\r"
"  t k, collega il nodo di input al target k del ciclo precedente;\n\r"
"  o k, collega il nodo di input alla attivazione di output k del c. prec.;\n\r"
"  i k, collega il nodo di input alla attivazione di  input k del c. prec.;\n\r"
"  I k, collega il nodo di input alla attivazione di  input k del c. att.;\n\r"
"  s min amp arco rit range, applica all'input il valore della f. sin nell'\n\r"
"    interv. di output minˆmin+amp, ripetendo un ciclo compl. in arco 'giorni',\n\r"
"    con inizio del ciclo al giorno 'rit'; se 'range' > 0, a sin si aggiunge\n\r"
"    un valore casuale equidistribuito nell'interv. -range/2 ˆ range/2.\n\r"
"  c min range, valore cas. uniforme nell'intervallo 'min' ˆ 'min' + 'range'.\n\r"
"  R n, richiamo del contenuto della memoria n del ciclo precedente; questo\n\r"
"    operatore ä attivo dal secondo 'giorno' o ciclo; per il primo giorno vale\n\r"
"    il valore iniziale (eventualmente assegnato con @, vedi sopra);\n\r"
"  f procedura da sviluppare in C\n\r\n\r");

if (videoStampa==1){printf("Premere un tasto per continuare.\n\r\n\r");getch();
printf(cancellaSchermo);}
else fprintf(help,"\n\r--------------------\n\r");

fprintf(help,
"  PER I TARGET (con una indicazione - conclusa da ' ;' - per ciascuno, in\n\r"
"                sequenza: la prima indicazione ä per il primo target, ecc.);\n\r"
"  si indicano gli elementi - operandi e operatori in notazione RPN - sulla\n\r"
"  base dei quali si definisce la formula che determina il target;\n\r"
"  possono essere elementi della formula: costanti numeriche (iniziare con 'm'\n\r"
"  se negative); attiv. di input indicate con 'i' seguito immediatamente dal\n\r"
"  # del nodo; attiv. di output indicate con 'o' seguito immediatamente dal #\n\r"
"  del nodo; target (giÖ calcolati in precedenti formule) indicati con 't' se-\n\r"
"  guito immediatamente dal # del nodo; operatori '+' '-' '*' '/';\n\r\n\r"
"  operatore speciale: Hn sceglie il pió grande in val. ass. degli n valori\n\r"
"  che lo precedono (tali dopo l'applicazione degli operatori agli operandi con\n\r"
"  la RPN; nella versione hn, l'op. tiene conto del segno dei valori;\n\r\n\r"
"  costante numerica speciale: Cn, v.c. 0ˆ1 (con n si sceglie tra 100\n\r"
"  valori disponibili, che si modificano ad ogni ciclo di calcolo, restando\n\r"
"  eguali per tutti i target all'interno di un singolo ciclo;\n\r\n\r"
"  immissione del valore corrente nella Memoria n (di 100): Mn (con un uso spec.\n\r"
"  per i t. est.); le 100 pos. di M e C sono aumentabili nel caso MULTI-AGENTE;\n\r"
"  richiamo dalla Memoria n: Rn; le pos. di mem. sono azzerate 'ogni giorno';\n\r\n\r"
"  tutti i valori sono nella scala effettiva dei dati grezzi;\n\r"
"  i valori sono comunque costretti nell'intervallo minˆmax fissato sopra.\n\r");

if (videoStampa==1){printf("Premere un tasto per continuare.");getch();
printf(cancellaSchermo);}
else fprintf(help,"\n\r--------------------\n\r");

fprintf(help,
"Operatore 'Se' (si applica a 4 operandi) , scritto 'e' o 'E' nei target:\n\r\n\r"
"a b c d e    mette c nel r. 1 se a > b; altrimenti mette (lascia) d in r. 1;\n\r"
"quindi annulla gli operandi;\n\r\n\r"
"a b c d E    opera nello stesso modo, con il controllo a Ú b.\n\r\n\r"
"L'operatore ä disponibile anche nella forma\n\r"
"a b c d u    con il controllo a = b.\n\r\n\r"
);

if (videoStampa==1){
printf("Premere un tasto per le informazioni sugli usi speciali.");getch();
printf(cancellaSchermo);}
else fprintf(help,"\n\r\n\r--------------------\n\r");

fprintf(help,
"Se l'innesco dei # casuali ä 0, saranno cercati i file di estensione\n\r"
".1 e .2, con nome uguale a quello dei file di servizio sopra citato, per\n\r"
"CONTINUARE l'apprendimento partendo dai pesi precedenti.\n\r\n\r"
"L'apprendimento avverrÖ per il # di cicli sopra definito e i nuovi pesi\n\r"
"saranno salvati in file .1 e .2 con lo stesso nome di quelli usati in\n\r"
"lettura.\n\rLa mancanza di tali file in input ä segnalata; errori nel numero\n\r"
"dei pesi contenuti nei file danno luogo a messaggi di errore.\n\r\n\r"
"ATTENZIONE alla coerenza degli eventuali cicli sinusoidali in input\n\r"
"e dei rispettivi ritardi; riprendendo il learning possono esserci incoerenze.\n\r"
);

fprintf(help,

"\n\rDOPO L'ULTIMA FORMULA DEI TARGET possono essere aggiunte ulteriori righe\n\r"
"nel file, con scopo di commento (in numero max di 100, pió l'eventuale uso\n\r"
"dello spazio restante nella riga dell'ultima fomula).\n\r"

"\n\rOgni run del programmma produce un file .ou contenente: attivazioni input,\n\r"
"attivazioni output, target. [NB sono valori grezzi, misurati nel proprio\n\r"
"intervallo effettivo].\n\r"
"Le ultime due colonne riportano i valori di errore [(‰e^2)/2 e err. %].\n\r\n\r");

if (videoStampa==1){
printf("Premere un tasto per le informazioni sull'impiego di target esterni.");
getch(); printf(cancellaSchermo);}
else fprintf(help,"\n\r--------------------\n\r");

fprintf(help,
"TARGET ESTERNI. Se si propone dall'esterno un target - ad es. una costante -\n\r"
"ad una congettura di effetto, l'ordinario target di tipo cross ottenuto dalle\n\r"
"azioni puï dover essere egualmente calcolato per costruire, partendo dalle\n\r"
"differenze tra cross-target e attivazioni di output, la preparazione dei\n\r"
"target per le congetture relative alle azioni.\n\r\n\r"
"Ciï puï essere fatto direttamente nella formula dei target per le azioni\n\r"
"oppure, per mantenere uno schema ordinato, conservando la preparazione del\n\r"
"cross-target interno per gli effetti, immettendo il risultato in memoria con\n\r"
"Mn e aggiungendo nella formula RPN il target esterno. Ad esempio:\n\r\n\r"
" ... (calcolo CT) M1 0  [in cui 0 ä il target esterno].\n\r\n\r"
"Il valore del cross-target sarÖ poi richiamato con R1 nelle formule dei target\n\r"
"azioni.\n\r\n\r"
"I registri di memoria sono azzerati all'inizio di ogni ciclo = pattern.\n\r");

if (videoStampa==1){
printf(
"\n\r\n\rPremere un tasto per una indicazione preliminare sull'impiego MULTI-AGENTE.");
getch(); printf(cancellaSchermo);}
else fprintf(help,"\n\r\n\r--------------------\n\r");

fprintf(help,
"Impiego MULTI-AGENTE.\n\r\n\r"
"NB agenti trattati in ordine casuale ogni 'giorno'.\n\r\n\r"
"Ciï puï determinare degli inconvenienti se nelle formule dei target si fa\n\r"
"riferimento a target di altri agenti; target che, data la casualitÖ\n\r"
"del richiamo degli agenti, potrebbero non essere ancora definiti.\n\r\n\r"
"In tal caso si deve utilizzare l'ordine sequenziale, che si ottiene premettendo\n\r"
"il segno meno al valore che indica il # di operatori+operandi max in ciascuna\n\r"
"formula dei target (valore che, di per sÇ, non puï che essere positivo).\n\r\n\r"
"NB la questione non ä controllabile al livello della sintassi, che verifica\n\r"
"solo che al momento della costruzione delle formule non si richiamino target\n\r"
"non in sequenza, prima di tutto all'interno dello stesso soggetto; se poi gli\n\r"
"agenti sono attivati in ordine casuale . . .\n\r"
"Ma il problema ä ancora pió complesso se si tiene conto che i target non in\n\r"
"sequenza tra pió soggetti possono essere scambiati anche tramite operatori\n\r"
"M e R.\n\r\n\r");

if (videoStampa==1){
printf("\n\r\n\rPremere un tasto per altre informazioni sull'impiego MULTI-AGENTE.");
getch(); printf(cancellaSchermo);}
else fprintf(help,"\n\r\n\r--------------------\n\r");


fprintf(help,
"Impiego MULTI-AGENTE.\n\r"
"Il primo elemento del file .ct deve essere il numero di TIPI di agenti,\n\r"
"SCRITTO COME NUMERO NEGATIVO, seguito: dalla dimensione dei vettori C e M \n\r"
"[rispettivamente, numeri causali e memorie temporanee utilizzabili in ogni\n\r"
"singolo ciclo; per i default (100) indicare 0 0, altrimenti un'altra coppia\n\r"
"di valori]; dal numero di indicatori_lista utilizzati (vedi oltre).\n\r"       /* { } */
"Segue l'indicazione del numero di agenti (elenco) per ciascun tipo.  Se uno o\n\r"
"pió valori sono <0, per essi opera la produz. automatica di agenti (vedere).\n\r"
"Infine si riportano le terne di valori di num. di pe input, hidden e output\n\r"
"di ciascun tipo di agente. [Riprendere, seguendo il caso monoagente, dal # max\n\r"
"di operatori + operandi in ciacuna formula dei target, compreso ; ].\n\r\n\r"
"N.B. tutti i nodi di input e i target devono essere descritti, con i relativi\n\r"
"val. min e max, come se appartenessero ad un'unica rete neurale.\n\r"
"La numerazione-utente dei nodi di input, output e dei target ä continua da 1\n\r"
"in poi (per l'input, si ignorino le posizioni bias), come se appartenessero\n\r"
"ad un'unica rete.\n\r"
"Attenzione: i val minˆmax di ogni nodo per ogni agente sono indicati raggrup-\n\r"
"pati per agente (prima i nodi input poi quelli output, agente per agente). In-\n\r"
"vece le indicazioni strutturali per i nodi input e le formule dei target sono\n\r"
"consecutive (prima tutti gli input di tutti gli agenti, poi tutti i target di\n\r"
"tutti gli agenti).\n\r"
"Memo: esiste un nodo bias nello strato input e in quello hidden per ciascuno\n\r"
"degli agenti, con specifici pesi (il tutto ä gestito internamente dal progr.).\n\r");

/* { } */
if (videoStampa==1){
printf("Premere un tasto per le inf. su PROD. AUT. DI AGENTI e INDICATORI_LISTA.");
getch(); printf(cancellaSchermo);}
else fprintf(help,"\n\r\n\r--------------------\n\r");

fprintf(help,"PRODUZIONE AUTOMATICA DI AGENTI\n\r"
"Per i valori negativi della lista del numero di agenti per popolazione (che\n\r"
"devono comunque essere in mod. >2) si descriveranno compiutamente solo due\n\r"
"agenti; gli altri saranno prodotti automaticamente, modificando tutti quegli\n\r"
"elementi che risultano differenziati nell'esame comparato dei due casi inte-\n\r"
"ramente descritti.\n\r"
"Negli input le modificazioni non sono ammesse per i parametri di c o s.\n\r"
"Nelle formule dei target NON devono essere modificati, nei due casi confron-\n\r"
"tati, i numeri n di lista. NON deve essere modificato n in Hn o hn.\n\r"
"Tutti le altre indicazioni numeriche, quali i valori di i, o , t, nonchÇ i\n\r"
"valori numerici veri e propri, in quanto diversi tra i due agenti base, sa-\n\r"
"ranno ulteriormente differenziati nella produzione automatica.\n\r\n\r"
"Ulteriori agenti, collocati dopo quelli prodotti automaticamente, devono essere\n\r"
"costruiti tenendo conto della numerazione dei nodi di input e di output attri-\n\r"
"buita agli agenti prodotti automaticamente.\n\r\n\r");
fprintf(help,"INDICATORI_LISTA\n\r"
"Con la notazione { } si rappresentano indicatori detti indicatore lista perchÇ\n\r"
"costituiti da una pluralitÖ di riferimenti, tra cui ne sarÖ a volta a volta\n\r"
"scelto uno a caso. Tale indicatore lista ä utilizzabile soltanto nelle formule\n\r"
"dei target, se l'uso ä multiagente, dopo 'i', 'o', 't'.\n\r"
"Scopo dell'indicatore ä consentire la scelta casuale tra agenti, su liste.\n\r"
);

if (videoStampa==1){printf("\n\rPremere un tasto.");
getch(); printf(cancellaSchermo);}
else fprintf(help,"\n\r\n\r--------------------\n\r");

fprintf(help,
"L'indicatore { } ha la seguente struttura (nb gli spazi sono obbligatori):\n\r"
"x{ n }k                       NEI RICHIAMI SUCCESSIVI AL PRIMO\n\r"
"in cui x vale i/o/t, n ä il numero di lista, k (che vale da 1 a # nodi del\n\r"
"tipo in questione) indica il nodo contraddistinto dalla posizione relativa all'\n\r"
"interno di un singolo agente, ignorando i nodi bias; (nb ciï ä diverso rispetto\n\r"
"alla notazione di ct applic. a casi diversi da { }, in quanto l'individuazione\n\r"
"dei nodi ä altrimenti assoluta, come se la rna fosse unica, ignorando comunque\n\r"
"i nodi bias).\n\r"
"x{ n m a1 a2 a3 ... am }k    NEL PRIMO RICHIAMO, SE DI ADOTTA LA FORMA 'ELENCO'\n\r"
"con m = numero degli oggetti della lista.\n\r"
"x{ n m . a1 d }k             NEL PRIMO RICHIAMO, SE SI ADOTTA LA FORMA 'PUNTO'\n\r"
"d ä il passo di incremento, per cui la lista sarÖ espansa come segue:\n\r"
"a1   a1+d   a1+2d   ...   a1+(m-1)d\n\r"
"In ogni applicazione opera, per ogni lista { n } e in ogni ciclo di learning,\n\r"
"la selezione a caso del soggetto interlocutore per ogni agente. Se l'agente A\n\r"
"sceglie - per la lista n - l'agente B, nÇ A nÇ B compaiono pió nella lista;\n\r"
"inoltre, da quel momento, la lista n di A contiene solo B e la l. n di B con-\n\r"
"tiene solo A. Se la l. ha un solo ag., la scelta ä quella e la l. non diventa\n\r"
"vuota. L'agente A non puï scegl. se stesso, anche se A unico nella l., a meno\n\r"
"che la lista abbia un solo elemento sin dall'inizio (vedere oltre !). L'agente\n\r"
"che sceglie e l'agente scelto tengono comportamenti reciproci, sulla base delle\n\r" 
"regole - specifiche di ogni caso - su cui si basa la costruzioni dei target."
);

if (videoStampa==1){printf("\n\rPremere un tasto.");
getch(); printf(cancellaSchermo);}
else fprintf(help,"\n\r\n\r\n\r--------------------\n\r");

fprintf(help,
"L'indicatore puï anche assumere la forma z{ n 1 a1 }k [z=i|o|t] e puï quindi\n\r"
"essere usato per gestire la numerazione relativa [!] e non assoluta; in tale\n\r"
"caso perï con un # di lista diverso per ogni soggetto (e sempre solo in appli-\n\r"
"cazioni multiagente).\n\r\n\r\n\r"
);

fprintf(help,
"Se nella prima definizione di un operatore lista si indica, prima della }, il\n\r"
"segno #, preceduto, ma non seguito da spazio, nelle forme\n\r\n\r"
"         x{ n m a1 a2 a3 ... am #}k  oppure\n\r\n\r"
"         x{ n m . a1 d #}k\n\r\n\r"
"si ottiene un operatore lista che non elimina le scelte fatte dalla lista e\n\r"
"che non vincola l'agente B, scelto da A, a scegliere a sua volta A.\n\r"
"Si tratta di una specificazione della lista utile in particolare per la costru-\n\r"
"zione di modelli fondati sull'imitazione.\n\r"
"Ovviamente la scelta fatta dall'agente A resta ferma per altri richiami che\n\r"
"l'agente stesso faccia al medesimo operatore lista nello stesso 'giorno'.\n\r\n\r"
);

if (videoStampa==1){printf("\n\rPremere un tasto.");
getch(); printf(cancellaSchermo);}
else fprintf(help,"\n\r\n\r\n\r--------------------\n\r");

fprintf(help,
"Un uso particolare della struttura MULTIAGENTE, con o senza operatori { }, ä\n\r"
"quello di 'appendere' ad un agente fittizio un input che serve ritardato, in\n\r"
"'giorni' successivi, per l'agente o per gli agenti veri, ma che non si vuole\n\r"
"sia in input nel giorno stesso per quegli agenti; all'agente fittizio - intro-\n\r"
"dotto per questo o altri scopi - si attribuiscono 0 nodi hidden e 0 output.\n\r\n\r\n\r"
);

fprintf(help,
"Scambio di MEMORIE AGENTE tramite operatori lista, con la notazione S{...\n\r"
"Il numero massimo di posizioni di memoria disponibili per ogni agente ä\n\r"
"indicato all'inizio, con la notazione a,b in cui a ä il # di operatori lista\n\r"
"e ',b' indica - se presente - il # [b] massimo di memorie agente.\n\r"
"Funzionamento: l'agente ha nel r. 1 di calcolo il v. x; con S{ }k guarda nella\n\r"
"mem. ag. k dell'altro agente; se contiene un valore lo copia nel r. 1 al posto\n\r"
"di x [l'agente 'ä stato scelto'];\n\r"
"                              se no, lascia nel r. 1 il v. x e lo copia nella\n\r"
"memoria agente k propria [l'agente 'sceglie l'altro']\n\r\n\r"
);

if (videoStampa==1){printf("\n\rPremere un tasto.");
getch(); printf(cancellaSchermo);}
else fprintf(help,"--------------------\n\r");

fprintf(help,
"GESTIONE DEL FILE .OU (report delle attivazioni dei nodi input, output, dei\n\r"
"target, ...) secondo il contenuto del file nome.ini, se esiste. 'nome' deve\n\r"
"essere uguale al nome del file .ct dell'applicazione.\n\r\n\r"
"Il file .ou, in difetto di altra indicazione, contiene: una riga per ogni\n\r"
"'giorno' della simulazione; in ogni riga, il # di giorno, un segno |, tutte\n\r"
"le attivazioni input, un segno |, tutte le attivazioni output, un segno |,\n\r"
"tutti i target, un segno |, l'errore bp e l'errore percentuale.\n\r\n\r"
"Nel file .ini si indicano:\n\r"
"# indicante ogni quanti 'giorni' della simulazione avviene l'output: ogni\n\r"
"giorno, ogni secondo 'giorno', ..., ogni decimo ...;\n\r"
"# di col. da mandare in out. (senza conteggiare i segni |), dalla 1 all'\n\r"
"ultima indicata (0 se tutte); se 0, il successivo input ä omesso;\n\r"
"una sequenza di tanti elementi 0 o 1 quante sono le col. da trattare; 1 indica\n\r"
"sç output, 0 no; es. 0 1 0 0 1, su 5 colonne manda in output la 2¶ e la 5¶.\n\r\n\r"
);

if (videoStampa==1){printf("\n\rPremere un tasto.");
getch(); printf(cancellaSchermo);}
else fprintf(help,"--------------------\n\r");

fprintf(help,
"GESTIONE DEL LEARNING RIPETUTO TRAMITE IL FILE nome.LRN; nome = nome del file\n\r"
"di estensione .ct con cui si sta lavorando.\n\r"
"Se il file ä presente, opera il learning ripetuto durante l'esperimento,\n\r"
"secondo le regole che seguono.\n\r"
"Il file inizia con la lettera (es. d) indicante il disco da usare, se manca lo\n\r"
"spazio in memoria, per le matrici in cui sono conservati i dati necessari per\n\r"
"il learning ripetuto; se ä disponibile un RAM Disk, indicare quello.\n\r"
"Seguono: l'indicazione t|o per l'uso dei target o degli output per il relearn;\n\r"
"         le indicazioni di eps1, alfa1, eps2, alfa2 da utilizzare nel learning\n\r"
" ripetuto; NB indicarli anche se eguali ai valori del learning on line interno\n\r"
" del metodo CT; NB NB se si vuole rendere inefficace tale learning on line ä\n\r"
" sufficiente indicare i valori eps1, eps2, alfa1, alfa2 del file .ct pari a 0;\n\r"
"         l'indicazione del numero di giorno 'ogni quanti' il learning ripetuto\n\r"
" deve avere luogo (ad es. 1 = ogni giorno; 10 = ogni decimo giorno ...);\n\r"
"         l'indicazione del numero di giorni all'indietro la cui storia ä da\n\r"
" utilizzare per il learning ripetuto (se si indica un numero maggiore del\n\r"
" numero di giorni effettivamente trascorsi, saranno usati tutti; NB questo ä\n\r"
" il modo per usare sempre tutta la storia pregressa ai fini del learning);\n\r"
"         il numero di cicli di learning da effettuare ad ogni re-learning (ä\n\r"
" meglio sia un multiplo del valore precedente);\n\r"
"         l'indicazione c|s a seconda che il learning debba avvenire in ordine\n\r"
" casuale o sequenziale (sempre nell'ambito dei 'giorni' indicati).\n\r"
"Il learning ripetuto non produce output a sÇ su video; i cambiamenti si notano\n\r"
"dall'output ordinario dei giorni successivi."
);

if (videoStampa==1){printf("\n\rPremere un tasto.");
getch(); printf(cancellaSchermo);}
else fprintf(help,"--------------------\n\r");

fprintf(help,
"Considerazioni sui valori eps e alfa nella GESTIONE DEL LEARNING RIPETUTO.\n\r\n\r"
"Il solo eps (1 e 2) nullo nel file .ct non annulla la correzione dei pesi nel\n\r"
"normale training on line, per via di alfa (1 e 2) che se non nullo riporta\n\r"
"nella fase on line l'effetto del learning off line.\n\r\n\r"
"Se si usano in .ct esp e alfa nulli, mentre in .lrn alfa ä non nullo, si noti\n\r"
"che quando riprende il learning off line dopo un tratto di learning (fittizio)\n\r"
"on line, l'effetto di momentum ä inizialmente distorto (nel primo ciclo).\n\r\n\r"
"Visualizzazione dell'errore: come nel learning on line, anche in quello ripetu-\n\r"
"to off line con il re-learning, l'output delle valutazioni di errore avviene\n\r"
"prima del calcolo della correzione dei pesi; l'effetto dell'ultima correzione\n\r"
"in assoluto dunque non compare. Nel caso del learning off line puï trattarsi\n\r"
"di una correzione (derivante dal learning ripetuto su un sottoinsieme di casi)\n\r"
"anche molto significativa.\n\r\n\r"
);


if(videoStampa==2)fprintf(help,"\n\r\n\r--------------------\n\r\f");
close(help);
exit(0);
	}

