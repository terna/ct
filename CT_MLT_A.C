#include "ct.h"

/*-------------------------------------------------------------------------*/
													/* ct_mlt_a.c */
	void MultiAgente(long int val, int io) {
	static int i, ii, iii, per;
	static unsigned long n_C_copia, n_M_copia, i_veri, o_veri, cum, cont;
        static char provv[20], prov1[20], prov2[20];
        static char *ptr, virgola = ',';

	if(io==1)
	   {
	   tipi=val; /* numero di tipi di agente */

	   fscanf(ct,"%lu",&n_C); n_C_copia=n_C;
		if (n_C==0)n_C=100;
	   fscanf(ct,"%lu",&n_M); n_M_copia=n_M;
		if (n_M==0)n_M=100;

/* { } */  fscanf(ct,"%s",&provv);
           ptr = strchr(provv, virgola);
           if (ptr) {
                     for (i=0;i<ptr-provv;i++)     prov1[i]=provv[i];
                     for (i=0;i<20-(ptr-provv);i++)prov2[i]=provv[i+ptr-provv+1];
                     sscanf(prov1,"%d",&nListe);
                     sscanf(prov2,"%d",&n_mem_ag);
                     }
           else      {
                      sscanf(provv,"%d",&nListe);
                      n_mem_ag=0;
                      }

                      

/* { } */
        if(n_mem_ag != 0 && nListe == 0){
	   printf("Non si possono usare posizioni di memoria agente\n"
                  "senza aver indicato almeno una lista.\n");
	   exit(0);
	   }



	   Avvisa(tipi*sizeof(int long));
	   if ((n_per_tipo0=calloc(tipi,sizeof(int long)))==NULL)           {
	     printf("Memoria insufficiente, ridurre il num. di tipi di agenti.");
	     exit(0);
	     }
	   n_per_tipo=n_per_tipo0-1;

	   if ((ni_per_tipo0=calloc(tipi,sizeof(int long)))==NULL)           {
	     printf("Memoria insufficiente, ridurre il num. di tipi di agenti.");
	     exit(0);
	     }
	   ni_per_tipo=ni_per_tipo0-1;

	   if ((nh_per_tipo0=calloc(tipi,sizeof(int long)))==NULL)           {
	     printf("Memoria insufficiente, ridurre il num. di tipi di agenti.");
	     exit(0);
	     }
	   nh_per_tipo=nh_per_tipo0-1;

	   if ((no_per_tipo0=calloc(tipi,sizeof(int long)))==NULL)           {
	     printf("Memoria insufficiente, ridurre il num. di tipi di agenti.");
	     exit(0);
	     }
	   no_per_tipo=no_per_tipo0-1;

	   for (i=1;i<=tipi;i++){fscanf(ct,"%ld",&n_per_tipo[i]);
				 if(n_per_tipo[i] < 0 && n_per_tipo[i] > -3)
					{printf("Errore: i val. < 0 della l. agenti "
						"(PROD. AUTOM. DI AGENTI) "
						"devono essere < -2.\n\n");
					 exit(0);
					}
				 }
			/* nb sono ammessi valori negativi */ 

	   for (i=1;i<=tipi;i++){
				 fscanf(ct,"%ld",&ni_per_tipo[i]);
				 fscanf(ct,"%ld",&nh_per_tipo[i]);
				 fscanf(ct,"%ld",&no_per_tipo[i]);
				 }

	   ni=0; nh=0; no=0; n_agenti=0;

	   for (i=1;i<=tipi;i++){ /* ricerca del max, per i DIMENSIONAMENTI MULTIPLI */
				 if (ni < ni_per_tipo[i]) ni=ni_per_tipo[i];
				 if (nh < nh_per_tipo[i]) nh=nh_per_tipo[i];
				 if (no < no_per_tipo[i]) no=no_per_tipo[i];
				 n_agenti += abs (n_per_tipo[i]);
				 }


        if(n_mem_ag > 0){
	Avvisa(n_mem_ag * n_agenti * sizeof(float));
        i11(&mem_ag,&mem_ag0,&mem_ag00,n_mem_ag,n_agenti);
                        }
	Avvisa(n_agenti*sizeof(int long));
	if ((vet_agenti0=calloc(n_agenti,sizeof(int long)))==NULL)           {
	     printf("Memoria insufficiente, ridurre il num. di agenti.");
	     exit(0);
	     }
	vet_agenti=vet_agenti0-1;



/* { } */ /*DIMENSIONAMENTI nListe * n_agenti
	    della matrice delle liste e di quella delle liste di ogni agente.

	    uso i10i

	    matrice delle liste
	    M_liste [nListe][(1+n_agenti)*2] con in col 0 il # di elementi
							       della lista
							       [0 se vuota]
						 in col 0+1+n_agenti (2¦ parte
						    di ogni riga, dove copio la
						    stringa originaria per le
						    estrazioni ogni "giorno")
						 il # di elementi va dal valore
						  di cui sopra all'inizio di un 
						  "giorno" a 1 quando non c'Š pi—
						  possibilit… di scelta casuale.
	    
	    matrice delle liste agente, ciascuna di un elemento
	    A_liste [nListe][1+n_agenti] con la posizione di col. 0 non usata
	    
	    */

      if(nListe>0){
	    Avvisa(nListe*(1+n_agenti)*2*sizeof(int));
	    i10i(&M_liste,&M_liste0,&M_liste00,nListe,2*(1+n_agenti));
	    for (i=1; i<=nListe; i++) M_liste[i][0]=0;

	    i10i(&A_liste,&A_liste0,&A_liste00,nListe,1+n_agenti);
	    /* l'azzeramento avviene in prep_lista all'inizio di ogni "giorno" */
		   }





	   /* vettori di nodi per singolo agente */
	   Avvisa(n_agenti*sizeof(int long));
	   if ((ni_per_agente0=calloc(n_agenti,sizeof(int long)))==NULL)           {
	     printf("Memoria insufficiente, ridurre il num. di agenti.");
	     exit(0);
	     }
	   ni_per_agente=ni_per_agente0-1;

	   if ((nh_per_agente0=calloc(n_agenti,sizeof(int long)))==NULL)           {
	     printf("Memoria insufficiente, ridurre il num. di agenti.");
	     exit(0);
	     }
	   nh_per_agente=nh_per_agente0-1;

	   if ((no_per_agente0=calloc(n_agenti,sizeof(int long)))==NULL)           {
	     printf("Memoria insufficiente, ridurre il num. di agenti.");
	     exit(0);
	     }
	   no_per_agente=no_per_agente0-1;


	   iii=1;
	   for (i=1;i<=tipi;i++)
	       for (ii=1;ii<=abs(n_per_tipo[i]);ii++){
						 ni_per_agente[iii]=ni_per_tipo[i];
						 
							if (n_per_tipo[i]<0 && ii>2)ni_per_agente[iii] *= -1;
							/* <0 significa agente non in input ma prodotto internamente */

						 nh_per_agente[iii]=nh_per_tipo[i];
						 no_per_agente[iii]=no_per_tipo[i];
						 iii++;
						 }

	   /* posizioni reali dei nodi */
	   i_veri=0;
	   o_veri=0;
	   for (i=1;i<=n_agenti;i++){i_veri += abs(ni_per_agente[i]);
				     o_veri += no_per_agente[i];
				     }

	   Avvisa(i_veri*sizeof(long unsigned));
	   if ((i_pos0=calloc(i_veri,sizeof(long unsigned)))==NULL)           {
	     printf("Memoria insufficiente, ridurre il num. di agenti.");
	     exit(0);
	     }
	   i_pos=i_pos0-1;
												  
	   Avvisa(o_veri*sizeof(long unsigned));
	   if ((o_pos0=calloc(o_veri,sizeof(long unsigned)))==NULL)           {
	     printf("Memoria insufficiente, ridurre il num. di agenti.");
	     exit(0);
	     }
	   o_pos=o_pos0-1;

	   if ((mmi_pos0=calloc(i_veri,sizeof(long unsigned)))==NULL)           {
	     printf("Memoria insufficiente, ridurre il num. di agenti.");
	     exit(0);
	     }
	   mmi_pos=mmi_pos0-1;

	   if ((mmo_pos0=calloc(o_veri,sizeof(long unsigned)))==NULL)           {
	     printf("Memoria insufficiente, ridurre il num. di agenti.");
	     exit(0);
	     }
	   mmo_pos=mmo_pos0-1;

	   cum=0;per=-1;agente=0;
	   for (i=1;i<=i_veri;i++){
				   if (i > cum) {cum += abs(ni_per_agente[++agente]);
						 cont=0;
						 per++;}
				   i_pos[i]=++cont+per*(ni+1);
				   }

	   cum=0;per=-1;agente=0;
	   for (i=1;i<=i_veri;i++){
				   if (i > cum) {cum += abs(ni_per_agente[++agente]);
						 cont=0;
						 per++;}
				   mmi_pos[i]=++cont+per*(no+ni);
				   }

	   cum=0;per=-1;agente=0;
	   for (i=1;i<=o_veri;i++){
				   if (i > cum) {cum += no_per_agente[++agente];
						 cont=0;
						 per++;}
				   o_pos[i]=++cont+per*no;
				   }

	   cum=0;per=-1;agente=0;
	   for (i=1;i<=o_veri;i++){
				   if (i > cum) {cum += no_per_agente[++agente];
						 cont=0;
						 ni_t=abs(ni_per_agente[agente]);
						 per++;}
				   mmo_pos[i]=++cont+ni_t+per*(no+ni);
				   }

	   }


	if(io==2)
	   {
	   fprintf(ct,"%ld ",-tipi);
	   fprintf(ct,"%lu ", n_C_copia);
	   fprintf(ct,"%lu ",n_M_copia);
/* { } */  fprintf(ct,"%d\n", nListe);
	   for (i=1;i<=tipi;i++)fprintf(ct,"%ld ",n_per_tipo[i]);
				fprintf(ct,"\n");
	   for (i=1;i<=tipi;i++){
				 fprintf(ct,"%ld ",ni_per_tipo[i]);
				 fprintf(ct,"%ld ",nh_per_tipo[i]);
				 fprintf(ct,"%ld ",no_per_tipo[i]);
				 fprintf(ct,"\n");
				 }
	   }

	}

/*------------------------------------------------------------------------*/
													/* ct_mlt_a.c */
/* { } */
	void leggi_lista(int io, int tipo, float *v)
	{
	static char stringa [40]; static int i, m, m0, a, d, ss;
	static long int k, vv, n;

        ss=0;

	if(io==1)
	{
	   if(tipo==-10  && muto==0)printf("i{ ");
	   if(tipo==-20  && muto==0)printf("o{ ");
	   if(tipo==-30  && muto==0)printf("t{ ");
	   if(tipo==-100 && muto==0)printf("S{ ");

	   if(n_agenti==1){printf(
			   "\nErrore: l'indicatore { } pu• essere utilizzato soltanto"
			   " nell'uso multiagente.\n\n"); exit(0);}

	   if(nListe  ==0){printf(
			   "\nErrore: l'indicatore { } non pu• essere utilizzato"
			   " se non dichiarato all'inizio.\n\n"); exit(0);}

	   if(0 >= fscanf(ct,"%ld",&n)){printf(
				       "\nErrore: l'indicatore { } deve contenere il # di lista.\n\n");
				       exit(0);}
	   if (muto==0) printf("%ld ",n);

	   if(n > nListe){printf(
			  "\nErrore: indicatore { } con # di lista > max.\n\n");
			  exit(0);}

	   if(n <= 0)    {printf(
			  "\nErrore: # di lista in { } ó 0.\n\n");
			  exit(0);}
	   

	   if(EOF==fscanf(ct,"%s",stringa))fineFile();
	   if (muto==0) printf("%s ",stringa);


	   if(M_liste[n][0]!=0)   /* richiamo di { n } successivo al primo */
		{
                 if(stringa[0]=='#'){printf("\nErrore: #} pu• comparire solo nella prima def. dell'operatore lista\n");
                                     exit(0);
                                     }
                 if(stringa[0]!='}'){printf(
				       "\nErrore: manca } dopo n in un indicatore"
				       " { n } in un richiamo succ. al primo.\n");
				       exit(0);}
		 else{
			/* lettura di k, in }k */
			if(0==sscanf(stringa+1,"%ld",&k))
				    {printf(
					    "\nErrore: manca k dopo un indicatore { }.\n");
				     exit(0);
				     }
			if(k > 9999){printf(
				"\nErrore: valore k >9999 dopo un indicatore { }.\n");
			exit(0);    }
			*v = -(n*10000 + k); /* negativo, per uso con io==2 o io==3 */
		     }
		 }


	   else 
	    { /* primo richiamo dell'operatore { n } */

		  if(0 == sscanf(stringa,"%d",&m)){printf(
					 "\nErrore: manca il # elementi in un indicatore { }.\n\n");
					 exit(0);}
		  if(m>n_agenti){printf("\nErrore: # elementi dichiarato in un "
					"indicatore { } maggiore del # degli agenti.\n");
				 exit(0);}
		  if(m==0)      {printf("\nErrore: # elementi dichiarato in un "
					"indicatore { } NULLO.\n");
				 exit(0);}
	
		  M_liste[n][0]=m;



		if(EOF==fscanf(ct,"%s",stringa))fineFile();

		if(stringa[0]=='.'){
				  /* lettura del primo termine e del passo */
				   if(0>=fscanf(ct,"%d",&a) ||
				      0>=fscanf(ct,"%d",&d))
						{printf("\nErrore: in { . } manca il primo termine o il passo d.\n");
						exit(0);
						}

				   if (muto==0) printf(". %d %d ",a,d);
				   M_liste[n][1]=a;
				   for (i=2;i<=m;i++)M_liste[n][i]=a+(i-1)*d;
				   }

		else               {
				    /* lettura della lista */
				    if(0==sscanf(stringa,"%d",&a))  {printf(
								 "\nErrore: mancano elementi in { }.\n");
								 exit(0);}
				    if (muto==0) printf("%d ",a);
				    M_liste[n][1]=a;
				    for (i=2;i<=m;i++){
					if(0>=fscanf(ct,"%d",&a)){printf(
								 "\nErrore: mancano elementi in { }.\n");
								 exit(0);}
					if (muto==0) printf("%d ",a);
					M_liste[n][i]=a;
						   }
				   }

		/* lettura di } */
		if(EOF==fscanf(ct,"%s",stringa))fineFile();
                if(stringa[0]=='#' && stringa[1]=='}')
                                      {M_liste[n][0] *= -1;
                                       ss=1;
                                       }
		else 
                 if(stringa[0] != '}'){printf("\nErrore: manca } in un indicatore { }.\n");
		   		       exit(0);
				       }

		/* lettura di k, in }k */

		if(0==sscanf(stringa+1+ss,"%ld",&k))
				    {printf(
				     "\nErrore: manca k dopo un indicatore { }.\n");
				     exit(0);
				     }
		if (muto ==0 && ss ==0) printf( "}%ld ",k);
		if (muto ==0 && ss !=0) printf("#}%ld ",k);


		if(k > 9999){printf(
			"\nErrore: valore k >9999 dopo un indicatore { }.\n");
			exit(0);
			 }

		*v = n*10000 + k;


	 }


	}


	if(io==2)
		{
		if(tipo== -10)printf("i{ ");
		if(tipo== -20)printf("o{ ");
		if(tipo== -30)printf("t{ ");
		if(tipo==-100)printf("S{ ");


		vv=*v;
		if(*v<0)vv=-vv;
		k=vv % 10000;
		n=(vv-k)/10000;
			if(*v>0){
				m0=M_liste [n] [0];
                                m=abs(m0);
				printf("%ld %d ",n,m);
				for (i=1;i<=m;i++)printf("%d ",M_liste[n][i]);
				}
			else    {
				printf("%ld ",n);
				}
		if(*v>0 && m0<0) printf("#}%ld ",k);
		else             printf( "}%ld ",k);
		}

	if(io==3)
		{
		if(tipo== -10)fprintf(ct,"i{ ");
		if(tipo== -20)fprintf(ct,"o{ ");
		if(tipo== -30)fprintf(ct,"t{ ");
		if(tipo==-100)fprintf(ct,"t{ ");


		vv=*v;
		if(*v<0)vv=-vv;
		k=vv % 10000;
		n=(vv-k)/10000;
			if(*v>0){
				m0=M_liste [n] [0];
				m=abs(m0);
				fprintf(ct,"%ld %d ",n,m);
				for (i=1;i<=m;i++)fprintf(ct,"%d ",M_liste[n][i]);
				}
			else    {
				fprintf(ct,"%ld ",n);
				}
		if(*v>0 && m0<0) fprintf(ct,"#}%ld ",k);
		else             fprintf(ct, "}%ld ",k);
		}


	}

/*------------------------------------------------------------------------*/
													/* ct_mlt_a.c */
/* { } */
	void prep_lista()
	{
	static long int i, j, d;
	d=1+n_agenti;
       
	for (i=1;i<=nListe;i++)	for(j=0;j<=abs(M_liste[i][0]);j++)
				     M_liste[i][d+j]=M_liste[i][j];

	for (i=1;i<=nListe;i++)
	    for (j=1;j<=n_agenti;j++) A_liste[i][j]=0;

        for (i=1;i<=n_mem_ag;i++) for (j=1;j<=n_agenti;j++)
            mem_ag [i] [j] = 999999000;
	}

/*------------------------------------------------------------------------*/
													/* ct_mlt_a.c */
/* { } */
	void usa_lista(int tipo, int nop, long int ii, long int agente, long unsigned *nodo, long unsigned *n_mm)
	{

/*

Quando Cross_Target trova gli operatori -10, -20, -30 , -100, attenzione che 
il controllo se l'operatore { } Š gi… stato visto per quell'agente in quel
giorno si fa su A_liste; in questo modo anche se m (n. di elementi originario)
della lista Š 1, si mette il # nell'altro ecc.
Anzi, anche se la lista contiene solo pi— un elemento, esso pu• essere usato
pi— volte. Se l'agente dovesse scegliere se stesso, su un elemento solo lo
farebbe; NB solo per• se esiste un solo elemento sin dall'inizio, altrimenti va
in errore.

Normalmente, se campiona se stesso, ricampiona;
(se i soggetti si scelgono fra loro e se sono in # pari, alla fine devono restarne 2).

Segnalato nell'help che { n 1 a1 }k pu• essere usato (anche semplicemente per
gestire la numerazione relativa e non assoluta; in tal caso per• con un # di
lista diverso per ogni soggetto; inoltre il soggetto pu• scegliere se stesso).


IDEA base: controlla se A_liste di questo agente e questa lista Š vuoto; se no,
prosegue passando indietro i valori; se s, ci copia l'elemento di lista che sceglie e
copia nell'agente scelto il # di questo.

*/

	static float v; static long int vv, k;
	static int n, m, m0, quale, i, d, s;

		v=operando [nop] [ii+(agente-1)*no];
                if (v < 0) v=-v; /* necessario per coerenza con leggi_lista() */
		vv=v;
		k=vv % 10000; /* k indirizzo relativo all'interno dell'agente
				 senza tenere conto dei nodi bias */

                if(tipo==-10 && k > abs(ni_per_agente[agente])){
                                                           printf(
                                                           "Posizione relativa k dell'unit… "
                                                           "di input in { }k, > del # di nodi input.\n\n");
                                                           exit(0);
                                                           }

                if(tipo==-20 && k > no_per_agente[agente]){
                                                           printf(
                                                           "Posizione relativa k dell'unit… "
                                                           "di output in { }k, > del # di nodi output.\n\n");
                                                           exit(0);
                                                           }

                if(tipo==-30 && k > no_per_agente[agente]){
                                                           printf(
                                                           "Posizione relativa k del target "
                                                           "in { }k, > del # di nodi output.\n\n");
                                                           exit(0);
                                                           }

                if(tipo==-100 && k > n_mem_ag)            {
                                                           printf(
                                                           "Indicazione k di memoria agente "
                                                           "in S{ }k, > del max indicato.\n\n");
                                                           exit(0);
                                                           }

		n =(v-k)/10000;/* n  Š il # di lista */

	if (A_liste [n][agente] != 0) /* lista gi… utilizzata direttamente o
					 indirettamente per questo agente */
		{
		if(tipo==-10) {*nodo = k + (A_liste [n][agente]-1)*(ni+1);
			       *n_mm = k + (A_liste [n][agente]-1)*(ni+no);}

		if(tipo==-20
		|| tipo==-30) {*nodo = k + (A_liste [n][agente]-1)*no;
			       *n_mm = k + (A_liste [n][agente]-1)*(ni+no)+abs(ni_per_agente[agente]);}

		if(tipo==-100){*nodo = k;
			       *n_mm = A_liste [n][agente];}

		}

	else    {

		d = 1+n_agenti;
		m = abs(M_liste[n][d]); /* m  Š il # di elementi residui della lista  */
		m0= M_liste[n][0];      /* m0 Š il # iniziale di elementi della lista*/

		if(m==0){printf("Numero nullo di elementi nella lista { } in presenza\n"
				"di scelte ancora da compiere: probabilmente il # di soggetti\n"
				"Š dispari e si stanno costruendo delle coppie,\n"
                                "oppure Š carente la lista (con soggetti pari).\n\n");
			 exit(0);
			}


		if(m ==1) {quale = M_liste[n][d+1];
			   if(quale==agente && abs(m0) != 1){printf("Autoscelta vietata in una lista { } con # elementi iniziale diverso da 1.\n\n");
						             exit(0);}

                           A_liste[n][agente]=quale;
if(m0>0)                   A_liste[n][quale]=agente;	/* forse inutile, se m==1, ma mantiene la coerenza della regola */
			  }

		if(m !=1) {
			   quale=agente;
			   while(quale==agente){s=Dado(m);
						quale=M_liste[n][d+s];
					       }

if(m0>0)
{                          A_liste[n][agente]=quale;

			   for (i=s;i<=m-1;i++)M_liste[n][d+i]=M_liste[n][d+i+1];
			   m--;

			   A_liste[n][quale]=agente;

			   s=0;
			   for (i=1;i<=m;i++) if(M_liste[n][d+i]==agente) s=i;
			   if (s!=0){   
			   	     for (i=s;i<=m-1;i++)M_liste[n][d+i]=M_liste[n][d+i+1];
			   	     m--;
				    }
}
			  }  


                M_liste[n][d]=m;

		if(tipo==-10) {*nodo = k + (quale-1)*(ni+1);
			       *n_mm = k + (quale-1)*(ni+no);}

		if(tipo==-20
		|| tipo==-30) {*nodo = k + (quale-1)*no;
			       *n_mm = k + (quale-1)*(ni+no)+abs(ni_per_agente[agente]);}

		if(tipo==-100){*nodo = k;
			       *n_mm = quale;}

		}
		
	} 
