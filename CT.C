													/* ct.c */
		/*        CT (cross-target) v. 3.51            */

		/* compilato con TC++ 3.0 con opzione large   */


/* Le istruzioni indicate "Non standard C" possono essere eliminate */

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>                                       /* Non standard C */
#include <alloc.h>
#include <conio.h>

/* gestione EOF - Nei casi in cui Š necessario controllare sia la fine file,
		  sia l'eventuale lettura di 0 campi, ad es. perch‚ Š atteso
		  un val. num. e si incontra un carattere, invece di EOF==
		  si trova 0  >=  con il doppio controllo su 0 e su -1 (EOF).
		  Ci• potrebbe dare luogo a problemi nel caso in cui EOF non
		  fosse definito -1 o comunque <0. Nella lettura di stringhe
		  Š stato lasciato EOF, in quanto lo 0 non pu• avere luogo */


	char commenti [101] [128];
	char cancellaSchermo[]={27,'[','2','J',0};      /* Non standard C */
	FILE *ct, *ou, *ini, *lrn, *matr_ai,  *matr_ao,  *matr_t;
	int muto=0;
	unsigned int innesco;

	/* blocco reLearn */

	int reLearn=0, mem_lib;
	float eps1_lrn, eps2_lrn, alfa1_lrn, alfa2_lrn;
	       /* parametri per l'apprendimento ripetuto */
	long int ogni_lrn, quanti_lrn, ncicli_lrn;
	char cs_lrn[2]; char to_lrn[2];

	long int far *lrn_caso0 , far *lrn_caso;
	long int far *lrn_caso20, far *lrn_caso2;
			    /* definisco quanti_lrn posizioni; poich‚ la pos. 0
			       non Š usata, il vettore sar… gestito con
			       lrn_caso=lrn_caso0-1  */
	float far *t0_lrn, far *t_lrn;
			    /* definisco no posizioni; poich‚ la pos. 0 non Š
			       usata, il vettore sar… gestito con t_lrn=t0_lrn-1 */

	float far *ai_lrn;      /* definisco e uso ni+1 posizioni */

	float far *ao0_lrn, far *ao_lrn;
		    /* definisco no posizioni; poich‚ la pos. 0 non Š
		       usata, il vettore sar… gestito con ao_lrn=ao0_lrn-1 */

	float huge **matr_ai_mem, huge **matr_ai_mem0, huge *matr_ai_mem00;
	float huge **matr_ao_mem, huge **matr_ao_mem0, huge *matr_ao_mem00;
	float huge **matr_t_mem,  huge **matr_t_mem0,  huge *matr_t_mem00;


	/* -------------- */

	long int ni, ni_copia, ni_t;
	unsigned long nh, no, nh_t, no_t;
			    /* # nodi input, hidden, output */
	unsigned long n_op_op; long n_op_op2; /* serve per lettura se <0 */
			    /* # operatori+operandi massimo in ciascuna
			       formula */

	int sequenza_ag=0;
			    /* sar… = 1 se n_op_op < 0 indicher… che
			       la trattazione degli agenti, in uso multiagente,
			       sar… sequenziale e non casuale */

	unsigned long n_C = 100, n_M = 100; /* dimensioni dei vettori C e M
					       nel caso in cui manchi l'opzione
					       multiagente indicata da # in apertura
					       del file *.ct */

	long int ciclo, ncicli, ne; /* ogni ne cicli Š calcolato l'errore medio */

	float eps1, eps2, alfa1, alfa2; /* parametri per l'apprendimento */

	clock_t tempo0, tempo1, tempo2, tempo3;         /* Non standard C */

	float fattScala, fattScala1, intervRand;
	char fOut[15], ffOut[15];
	char der_med[2];

	int ogni_quante_r, quante_col;
	int far * quali_col0, far * quali_col;
			    /* si definiscono quante_col posizioni; poich‚ la pos. 0 non Š
			       usata, il vettore sar… gestito quante_col=quante_col0-1 */

	/***** compatibilit… mono agente - multi agente *****/

	long int n_agenti=1, agente;


	/***** gestione MultiAgente *************************/

	long int tipi;

	long int far *vet_agenti, far *vet_agenti0;
			    /* si definiscono tipi posizioni; poich‚ la pos. 0 non Š
			       usata, il vettore sar… gestito con vet_agenti=vet_agenti0-1 */

	long int far *n_per_tipo0, far *n_per_tipo;
			    /* si definiscono tipi posizioni; poich‚ la pos. 0 non Š
			       usata, il vettore sar… gestito con n_per_tipo=n_per_tipo0-1 */
	long int far *ni_per_tipo0, far *ni_per_tipo;
			    /* si definiscono tipi posizioni; poich‚ la pos. 0 non Š
			       usata, il vettore sar… gestito con ni_per_tipo=ni_per_tipo0-1 */
	long int far *nh_per_tipo0, far *nh_per_tipo;
			    /* si definiscono tipi posizioni; poich‚ la pos. 0 non Š
			       usata, il vettore sar… gestito con nh_per_tipo=nh_per_tipo0-1 */
	long int far *no_per_tipo0, far *no_per_tipo;
			    /* si definiscono tipi posizioni; poich‚ la pos. 0 non Š
			       usata, il vettore sar… gestito con no_per_tipo=no_per_tipo0-1 */

	long int far *ni_per_agente0, far *ni_per_agente;
			    /* si definiscono n_agenti posizioni; poich‚ la pos. 0 non Š
			       usata, il vettore sar… gestito con ni_per_agente=ni_per_agente0-1 */
	long int far *nh_per_agente0, far *nh_per_agente;
			    /* si definiscono n_agenti posizioni; poich‚ la pos. 0 non Š
			       usata, il vettore sar… gestito con nh_per_agente=nh_per_agente0-1 */
	long int far *no_per_agente0, far *no_per_agente;
			    /* si definiscono n_agenti posizioni; poich‚ la pos. 0 non Š
			       usata, il vettore sar… gestito con no_per_agente=no_per_agente0-1 */

	long unsigned far *i_pos,   far *i_pos0,
		      far *o_pos,   far *o_pos0,
		      far *mmi_pos, far *mmi_pos0,
		      far *mmo_pos, far *mmo_pos0;
			    /* si definiscono i_veri e o_veri posizioni; poich‚ in ps. 0
			       i vettori non sono utilizzati, si usano sfasati di -1
			       come sopra. */


/* { } */

	int nListe, n_mem_ag;
	char lista_start;
	int far **M_liste,  far **M_liste0,  far *M_liste00,
	    far **A_liste,  far **A_liste0,  far *A_liste00;
	    /* vedere le annotazioni in MultiAgente() */

	float far **mem_ag, far **mem_ag0, far *mem_ag00;
	    /* n_mem_ag righe per n_agenti colonne, entrambi
	       con inizio da 1 */

	/***** fine     MultiAgente *************************/


	char  far **tipoIn, far **tipoIn0, far *tipoIn00;
			    /* ni righe e 2 colonne */

	long  far *riferIn0, far *riferIn;
			    /* ni posizioni */

	float far **paramIn, far **paramIn0, far *paramIn00;
			    /* ni righe e 5 colonne, iniziando
			       da riga 1 e da colonna 1 */

	float far **operatore, far **operatore0, far *operatore00;
	float far **operando,  far **operando0,  far *operando00;
			     /* per entrambi, n_op_op righe e no col.
				iniziando da riga 1 e da colonna 1 */
			    
	float far *C0, far *C;
			    /* definisco n_C posizioni; poich‚ la pos. 0 non Š
			       usata, il vettore sar… gestito con C=C0-1 */

	float far *M0, far *M;
			    /* definisco n_M posizioni; poich‚ la pos. 0 non Š
			       usata, il vettore sar… gestito con M=M0-1 */

	float far *max0, far *max;
			    /* definisco no+ni posizioni; poich‚ la pos. 0 non Š
			       usata, il vettore sar… gestito con max=max0-1 */

	float far *min0, far *min;
			    /* definisco no+ni posizioni; poich‚ la pos. 0 non Š
			       usata, il vettore sar… gestito con min=min0-1 */

	int   far *val_iniz_SN0, far *val_iniz_SN;
			    /* definisco no+ni posizioni; poich‚ la pos. 0 non Š
			       usata, il vettore sar… gestito con val_iniz_SN=val_iniz_SN0-1 */

	float far *val_iniz0, far *val_iniz;
			    /* definisco no+ni posizioni; poich‚ la pos. 0 non Š
			       usata, il vettore sar… gestito con val_iniz=val_iniz0-1 */

	float far *t0, far *t;
			    /* definisco no posizioni; poich‚ la pos. 0 non Š
			       usata, il vettore sar… gestito con t=t0-1 */

	float far *ai,
		  *aai,    /* definisco e uso ni+1 posizioni */
	      far *ah,     /* definisco e uso nh+1 posizioni,
			       in ai e ah la posizione 0 Š il bias */
	      far *ao0, far *ao;
			    /* definisco no posizioni; poich‚ la pos. 0 non Š
			       usata, il vettore sar… gestito con ao=ao0-1 */

			    /* weights da .. a ... */
	float far **wih,  far **wih0,  far *wih00,
	      far **dwih, far **dwih0, far *dwih00,
			    /* per entrambi nh righe e ni+1 colonne, con la
			       colona 0 che rappresenta il bias */

	      far **who,  far **who0,  far *who00,
	      far **dwho, far **dwho0, far *dwho00;   
			    /* per entrambi no righe e nh+1 colonne, con la
			       colonna 0 che rappresenta il bias */

	float far **derivate, far **derivate0, far *derivate00;
			    /* no righe e ni colonne */

	float far *deltao0, far *deltao;  
			     /* definisco no posizioni; poich‚ la pos. 0
				non Š usata, il vettore sar… gestito con
				delta=delta0-1 */


	/* prototipi delle funzioni */

	void  Alloc();
	void  Avvisa(unsigned long max);
	void  i10(float far ***a, float far ***a0, float far **a00,
		  unsigned long nr, unsigned long nc);
/* { } */
	void  i10i(int far ***a, int far ***a0, int far **a00,
		   unsigned long nr, unsigned long nc);
	void  i10c(char far ***a, char far ***a0, char far **a00,
		   unsigned long nr, unsigned long nc);
	void  i11(float far ***a, float far ***a0, float far **a00,
		  unsigned long nr, unsigned long nc);
	float Flog(float);
	void  Calcolo();
        void  Calcolo_lrn();
	void  RPN_Target();
	void  Apprendimento();
        void  Apprendimento_lrn();
	void  Inizio();
	void  Dati_e_Parametri(char file[]);
	void  MultiAgente(long int, int);
	void  Input();
	float Intervallo_0_1(float, long unsigned);
	float deIntervallo_0_1(float, long unsigned);
	void  ScriviPesi();
	void  LeggiPesi();
	void  Help(int videoStampa, float vers);
	void  Messaggio();
	void  Derivate();
	float Scala(float);
	float deScala(float);
	void  MaxMin(int);
	void  fineFile();
	void  tipo_riferIn(int);
	void  Formule(int);
	float fSin(float min, float amp, float arco, float rit, float range);
	float Caso(float range);
	int   Dado(int m);
/* { } */
	void  leggi_lista(int io, int tipo, float *v);
	void  usa_lista(int tipo, int nop, long int i, long int agente, long unsigned *n, long unsigned *n_mm);
	void  prep_lista();
	void  file_ou(float perct0, float errore0, float perc0);
	void  file_ini();
        void  file_lrn(int apri_chiudi);
        void  vW(FILE *m, long nc, long r, long c, float *v);
        float vR(FILE *m, long nc, long r, long c);
        void  pesi_lrn();
	void  Memoria(unsigned long mem);
	void  i11h(float huge ***a, float huge ***a0, float huge **a00,
		   unsigned long nr, unsigned long nc);
	void  caso_lrn(long int);
	long
	 int  Dado2(long int);
	long
	 int  DadoEscl(long int);


/*------------------------------------------------------------------------*/
													/* ct.c */
	void main(int argc, char *argv[])
	{

	char file1 [40], file2 [40], file3[40];
	float aoo, tt, perc=0, perct=0, errore=0, perc0, perct0, errore0;
	unsigned i, ii, iii, j;

tempo0 =
 clock() / CLK_TCK;                             /* Non standard C */

	printf("%sCT v. 3.51   ž (p.d. software) - "
	"Istituto 'G. Prato' dell'Universit… di Torino\nPietro Terna"
	" - dicembre 1995 [inizio settembre 1990]\n\n",cancellaSchermo);

	if ((argc==1) || (argc==2 && (0==strcmp(argv[1],"/m")))
		      || (argc==2 && (0==strcmp(argv[1],"/M"))))
   {printf("\nManca il nome del file (di estensione sottintesa 'ct').\n"
    "'ct /h' per ottenere l'help; ct /H per stamparlo.\n");
    exit(0);}

	if (0 == strcmp(argv[1],"/h")) Help(1, 3.51);
	if (0 == strcmp(argv[1],"/H")) Help(2, 3.51);

	if ((argc==3) && (0 == strcmp(argv[2],"/m"))){
	   printf("Utilizzazione 'muta'.\n");
	   muto=1;
	   }
	if ((argc==3) && (0 == strcmp(argv[2],"/M"))){
	   printf("Utilizzazione 'muta'.\n");
	   muto=2;
	   }


	strcpy(file1,argv[1]); 
	strcpy(file2,file1);
        strcpy(file3,file1);

	/* argv[1] contiene il nome del file (di est. .ct)
	   passato come parametro al programma */   

	if (NULL == (ct=fopen(strcat(file1,".ct"),"r"))){
	   printf("File non trovato [una possibile fonte di errore Š "
		  "l'aver scritto l'estensione\ndel file].\n");
	   exit(0);
	   }
	fclose(ct);

	/* inizializzazioni e parametri eventuali da file .ini */

        ogni_quante_r=1;
        quante_col=0;
	if (NULL != (ini=fopen(strcat(file2,".ini"),"r"))) file_ini();



	Dati_e_Parametri(file1);



        /* parametri eventuali da file .lrn */

        reLearn=0;
	if (NULL != (lrn=fopen(strcat(file3,".lrn"),"r"))) file_lrn(1);


	if (ncicli == 0){
	   printf(
"\n\n\nAttenzione!\nCT non prevede la possibilit… di un numero di cicli di calcolo pari a 0.");
	   exit(0);
	   }

	fattScala1=(1.-fattScala)*0.5;

	Inizio();

	strcpy(ffOut,fOut);
	ou=fopen(strcat(ffOut,".ou"),"w");

tempo1 = clock() / CLK_TCK;                             /* Non standard C */

	
	
	for (ciclo=1; ciclo<=ncicli; ciclo++)
	{

/* { } */        
	if(nListe>0)prep_lista();


	/*  pattern */

	Input();        /* valori scalati tra 0 e 1 */


	Calcolo();

	RPN_Target(); /* valori scalati tra (0.5-0.5*fattScala) e
					       0.5+0.5*fattScala)   */

	    /* pre-calcolo dell'errore */
	    errore0=perc0=perct0=0;
      for (agente=1;agente<=n_agenti;agente++){
	if (n_agenti>1)no_t=no_per_agente[agente];
	else           no_t=no;
	for (i=1;i<=no_t;i++){   ii=i+(agente-1)*no;
				 if (n_agenti>1)iii=i+abs(ni_per_agente[agente])+(agente-1)*(ni+no);
				 else           iii=i+ni;

				 errore0 += (ao[ii]-t[ii])*(ao[ii]-t[ii])/2;
			      /* valore standard di errore nella BP
				 determinato sui valori scalati con
				 fattScala                          */
			      aoo=deIntervallo_0_1(deScala(ao [ii]),iii);
			      tt =deIntervallo_0_1(deScala(t  [ii]),iii);
			      perc0 += fabs(aoo-tt); perct0 += fabs(tt);
			      /* perc. di errore sul singolo nodo,
				 calcolata eliminando l'influenza di 
				 fattScala e riportando i valori all'
				 intervallo originario              */
			    }
      }

	    /* output valori grezzi nel file .ou */

	file_ou(perct0, errore0, perc0);
				       

if (muto != 2){

	       errore += errore0;

	       perc += perc0; perct += perct0;

	/* ogni ne cicli si manda in output la media degli ultimi ne errori */

	if (0==ciclo % ne) {

	   errore /= ne;
	   if(perct==0)perct=0.0001;
	   perc   /= perct;
	   printf("# %7ld: Err. medio BP %f",ciclo,errore);
	   printf(";  |err. %% medio| per nodo out.%7.2f\n",perc*100.);
	   errore=0;perc=0; perct=0;
	   }
}
if (muto==2 && 0== ciclo % ne) printf("*");

	Apprendimento();

/*reLearn */

        if(reLearn != 0 && 0 == ciclo % ogni_lrn) pesi_lrn();

	}


tempo2 = clock() / CLK_TCK;                             /* Non standard C */

	fclose(ou);

	Messaggio();

	ScriviPesi();

	Derivate();

tempo3 = clock() / CLK_TCK;                             /* Non standard C */

printf("\nSecondi: - di calcolo %ld\n"
	 "         - totali     %ld\n",tempo2-tempo1,
				       tempo3-tempo0);  /* Non standard C */

        if(reLearn==1)file_lrn(2);

	}

