/* Le istruzioni indicate "Non standard C" possono essere eliminate */		/* ct.h */

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


	extern char commenti [101] [128];
	extern char cancellaSchermo[];      /* Non standard C */
	extern FILE *ct, *ou, *ini, *lrn, *matr_ai,  *matr_ao,  *matr_t;
	extern int muto;
	extern unsigned int innesco;

        /* blocco reLearn */

        extern int reLearn, mem_lib;
	extern float eps1_lrn, eps2_lrn, alfa1_lrn, alfa2_lrn;
               /* parametri per l'apprendimento ripetuto */
	extern long int ogni_lrn, quanti_lrn, ncicli_lrn;
	extern char cs_lrn[2]; extern char to_lrn[2];

	extern long int far *lrn_caso0 , far *lrn_caso;
	extern long int far *lrn_caso20, far *lrn_caso2;
			    /* definisco quanti_lrn posizioni; poich‚ la pos. 0
			       non Š usata, il vettore sar… gestito con
			       lrn_caso=lrn_caso0-1  */
	extern float far *t0_lrn, far *t_lrn;
			    /* definisco no posizioni; poich‚ la pos. 0 non Š
			       usata, il vettore sar… gestito con t_lrn=t0_lrn-1 */

	extern float far *ai_lrn;      /* definisco e uso ni+1 posizioni */

	extern float far *ao0_lrn, far *ao_lrn;
		    /* definisco no posizioni; poich‚ la pos. 0 non Š
		       usata, il vettore sar… gestito con ao_lrn=ao0_lrn-1 */

	extern float huge **matr_ai_mem, huge **matr_ai_mem0, huge *matr_ai_mem00;
	extern float huge **matr_ao_mem, huge **matr_ao_mem0, huge *matr_ao_mem00;
	extern float huge **matr_t_mem,  huge **matr_t_mem0,  huge *matr_t_mem00;

        /* -------------- */


	extern long int ni, ni_copia, ni_t;
	extern unsigned long nh, no, nh_t, no_t;
			    /* # nodi input, hidden, output */
	extern long n_op_op; extern long n_op_op2; /* serve per lettura se <0 */ 
			    /* # operatori+operandi massimo in ciascuna 
			       formula */

        extern int sequenza_ag;  
                            /* sar… = 1 se n_op_op < 0 indicher… che
                               la trattazione degli agenti, in uso multiagente,
                               sar… sequenziale e non casuale */

	extern unsigned long n_C, n_M;      /* dimensioni dei vettori C e M
					       nel caso in cui manchi l'opzione
					       multiagente indicata da # in apertura
					       del file *.ct */

	extern long int ciclo, ncicli, ne; /* ogni ne cicli Š calcolato l'errore medio */

	extern float eps1, eps2, alfa1, alfa2; /* parametri per l'apprendimento */

	extern clock_t tempo0, tempo1, tempo2, tempo3;         /* Non standard C */ 

	extern float fattScala, fattScala1, intervRand;
	extern char fOut[15], ffOut[15];
	extern char der_med[2];

	extern int ogni_quante_r, quante_col;
	extern int far * quali_col0, far * quali_col;
			    /* si definiscono quante_col posizioni; poich‚ la pos. 0 non Š
			       usata, il vettore sar… gestito quante_col=quante_col0-1 */

	/***** compatibilit… mono agente - multi agente *****/

	extern long int n_agenti, agente;


	/***** gestione MultiAgente *************************/

	extern long int tipi;

        extern long int far *vet_agenti, far *vet_agenti0;
			    /* si definiscono tipi posizioni; poich‚ la pos. 0 non Š
			       usata, il vettore sar… gestito con vet_agenti=vet_agenti0-1 */

	extern long int far *n_per_tipo0, far *n_per_tipo;
			    /* si definiscono tipi posizioni; poich‚ la pos. 0 non Š
			       usata, il vettore sar… gestito con n_per_tipo=n_per_tipo0-1 */
	extern long int far *ni_per_tipo0, far *ni_per_tipo;
			    /* si definiscono tipi posizioni; poich‚ la pos. 0 non Š
			       usata, il vettore sar… gestito con ni_per_tipo=ni_per_tipo0-1 */
	extern long int far *nh_per_tipo0, far *nh_per_tipo;
			    /* si definiscono tipi posizioni; poich‚ la pos. 0 non Š
			       usata, il vettore sar… gestito con nh_per_tipo=nh_per_tipo0-1 */
	extern long int far *no_per_tipo0, far *no_per_tipo;
			    /* si definiscono tipi posizioni; poich‚ la pos. 0 non Š
			       usata, il vettore sar… gestito con no_per_tipo=no_per_tipo0-1 */

	extern long int far *ni_per_agente0, far *ni_per_agente;
			    /* si definiscono n_agenti posizioni; poich‚ la pos. 0 non Š
			       usata, il vettore sar… gestito con ni_per_agente=ni_per_agente0-1 */
	extern long int far *nh_per_agente0, far *nh_per_agente;
			    /* si definiscono n_agenti posizioni; poich‚ la pos. 0 non Š
			       usata, il vettore sar… gestito con nh_per_agente=nh_per_agente0-1 */
	extern long int far *no_per_agente0, far *no_per_agente;
			    /* si definiscono n_agenti posizioni; poich‚ la pos. 0 non Š
			       usata, il vettore sar… gestito con no_per_agente=no_per_agente0-1 */

	extern long unsigned far *i_pos,   far *i_pos0,
		      far *o_pos,   far *o_pos0,
		      far *mmi_pos, far *mmi_pos0,
		      far *mmo_pos, far *mmo_pos0;
			    /* si definiscono i_veri e o_veri posizioni; poich‚ in ps. 0
			       i vettori non sono utilizzati, si usano sfasati di -1
			       come sopra. */


/* { } */

	extern int nListe, n_mem_ag;
	extern char lista_start;
	extern int far **M_liste,  far **M_liste0,  far *M_liste00,
	    far **A_liste,  far **A_liste0,  far *A_liste00;
	    /* vedere le annotazioni in MultiAgente() */

        extern float far **mem_ag, far **mem_ag0, far *mem_ag00;
            /* n_mem_ag righe per n_agenti colonne, entrambi 
               con inizio da 1 */



	/***** fine     MultiAgente *************************/


	extern char  far **tipoIn, far **tipoIn0, far *tipoIn00;
			    /* ni righe e 2 colonne */

	extern long  far *riferIn0, far *riferIn;
			    /* ni posizioni */

	extern float far **paramIn, far **paramIn0, far *paramIn00;
			    /* ni righe e 5 colonne, iniziando
			       da riga 1 e da colonna 1 */

	extern float far **operatore, far **operatore0, far *operatore00;
	extern float far **operando,  far **operando0,  far *operando00;
			     /* per entrambi, n_op_op righe e no col.
				iniziando da riga 1 e da colonna 1 */
			    
	extern float far *C0, far *C;
			    /* definisco n_C posizioni; poich‚ la pos. 0 non Š
			       usata, il vettore sar… gestito con C=C0-1 */

	extern float far *M0, far *M;
			    /* definisco n_M posizioni; poich‚ la pos. 0 non Š
			       usata, il vettore sar… gestito con M=M0-1 */

	extern float far *max0, far *max;
			    /* definisco no+ni posizioni; poich‚ la pos. 0 non Š
			       usata, il vettore sar… gestito con max=max0-1 */

	extern float far *min0, far *min;
			    /* definisco no+ni posizioni; poich‚ la pos. 0 non Š
			       usata, il vettore sar… gestito con min=min0-1 */

	extern int   far *val_iniz_SN0, far *val_iniz_SN;
			    /* definisco no+ni posizioni; poich‚ la pos. 0 non Š
			       usata, il vettore sar… gestito con val_iniz_SN=val_iniz_SN0-1 */

	extern float far *val_iniz0, far *val_iniz;
			    /* definisco no+ni posizioni; poich‚ la pos. 0 non Š
			       usata, il vettore sar… gestito con val_iniz=val_iniz0-1 */

	extern float far *t0, far *t;
			    /* definisco no posizioni; poich‚ la pos. 0 non Š
			       usata, il vettore sar… gestito con t=t0-1 */

	extern float far *ai,
		  *aai,    /* definisco e uso ni+1 posizioni */
	      far *ah,     /* definisco e uso nh+1 posizioni,
			       in ai e ah la posizione 0 Š il bias */
	      far *ao0, far *ao;
			    /* definisco no posizioni; poich‚ la pos. 0 non Š
			       usata, il vettore sar… gestito con ao=ao0-1 */

			    /* weights da .. a ... */
	extern float far **wih,  far **wih0,  far *wih00,
	      far **dwih, far **dwih0, far *dwih00,
			    /* per entrambi nh righe e ni+1 colonne, con la
			       colona 0 che rappresenta il bias */

	      far **who,  far **who0,  far *who00,
	      far **dwho, far **dwho0, far *dwho00;   
			    /* per entrambi no righe e nh+1 colonne, con la
			       colonna 0 che rappresenta il bias */

	extern float far **derivate, far **derivate0, far *derivate00;
			    /* no righe e ni colonne */

	extern float far *deltao0, far *deltao;  
			     /* definisco no posizioni; poich‚ la pos. 0
				non Š usata, il vettore sar… gestito con
				delta=delta0-1 */


	/* prototipi delle funzioni */

	extern void  Alloc();
	extern void  Avvisa(unsigned long max);
	extern void  i10(float far ***a, float far ***a0, float far **a00,
		  unsigned long nr, unsigned long nc);
/* { } */
	extern void  i10i(int far ***a, int far ***a0, int far **a00,
		   unsigned long nr, unsigned long nc);
	extern void  i10c(char far ***a, char far ***a0, char far **a00,
		   unsigned long nr, unsigned long nc);
	extern void  i11(float far ***a, float far ***a0, float far **a00,
		  unsigned long nr, unsigned long nc);
	extern float Flog(float);
	extern void  Calcolo();
        extern void  Calcolo_lrn();
	extern void  RPN_Target();
	extern void  Apprendimento();
        extern void  Apprendimento_lrn();
	extern void  Inizio();
	extern void  Dati_e_Parametri(char file[]);
	extern void  MultiAgente(long int, int);
	extern void  Input();
	extern float Intervallo_0_1(float, long unsigned);
	extern float deIntervallo_0_1(float, long unsigned);
	extern void  ScriviPesi();
	extern void  LeggiPesi();
	extern void  Help(int videoStampa, float vers);
	extern void  Messaggio();
	extern void  Derivate();
	extern float Scala(float);
	extern float deScala(float);
	extern void  MaxMin(int);
	extern void  fineFile();
	extern void  tipo_riferIn(int);
	extern void  Formule(int);
	extern float fSin(float min, float amp, float arco, float rit, float range);
	extern float Caso(float range);
	extern int   Dado(int m);
/* { } */
	extern void  leggi_lista(int io, int tipo, float *v);
	extern void  usa_lista(int tipo, int nop, long int i, long int agente, long unsigned *n, long unsigned *n_mm);
	extern void  prep_lista();
	extern void  file_ou(float perct0, float errore0, float perc0);
	extern void  file_ini();
        extern void  file_lrn(int apri_chiudi);
        extern void  vW(FILE *m, long nc, long r, long c, float *v);
        extern float vR(FILE *m, long nc, long r, long c);
        extern void  pesi_lrn();
	extern void  Memoria(unsigned long mem);
	extern void  i11h(float huge ***a, float huge ***a0, float huge **a00,
			  unsigned long nr, unsigned long nc);
	extern void  caso_lrn(long int);
	extern long
		int  Dado2(long int);
	extern long
		int  DadoEscl(long int);
