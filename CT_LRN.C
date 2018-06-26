#include "ct.h"


/*-------------------------------------------------------------------------*/
													/* ct_lrn.c */
	 void file_lrn(int apri_chiudi)
	 {
	 static char file1[40], file2[40], file3[40], delete[20];

if(apri_chiudi==1){
		  reLearn=1;
		  fscanf(lrn,"%s",file1);
		  strcpy(file2,file1);
		  strcpy(file3,file1);

	if ((t0_lrn =calloc(no*n_agenti,sizeof(float)))==NULL)           {
	   printf("Memoria insufficiente in ct_lrn, ridurre il # dei casi o dei nodi");
	   exit(0);
	   }
	t_lrn =t0_lrn-1;

	if ((ao0_lrn=calloc(no*n_agenti,sizeof(float)))==NULL)           {
	   printf("Memoria insufficiente in ct_lrn, ridurre il # dei casi o dei nodi");
	   exit(0);
	   }
	ao_lrn=ao0_lrn-1;

	if ((ai_lrn=calloc((ni+1)*n_agenti,sizeof(float)))==NULL)         {
	   printf("Memoria insufficiente in ct_lrn, ridurre il # dei casi o dei nodi");
	   exit(0);
	   }

		  /* t|o , cioŠ relearning guardando ai target o agli ao  */
		  fscanf(lrn,"%s",&to_lrn);

		  if (to_lrn[0] != 't' && to_lrn[0] != 'o')
			{printf(
			"\nManca, nel file nome.LRN, l'indicazione 't' o 'o'.\n");
			exit(0);}

		  /* test sullo spazio per le matrici huge; vedere nel comment di
		     Memoria() il problema riscontrato nell'uso, che si aggira
		     con questa chiamata esplicita a farcoreleft () */

		  printf("\nMemoria libera:\n\tfarcoreleft\t%lu\n",
			 farcoreleft());
		  printf("\nMemoria necessaria per le matrici per l'applicazione .LRN,\n"
			 "se gestite in memoria:\t%lu\n\n",
			 (unsigned long)(ni+1)*n_agenti*ncicli*sizeof(float) +
					no*n_agenti*ncicli*sizeof(float));

		  if( (ni+1)*n_agenti*ncicli*sizeof(float) +
		      no*n_agenti*ncicli*sizeof(float)     >  farcoreleft() )

		  {mem_lib=0;
		  printf("Le matrici per l'applicazione .LRN sono gestite su disco.\n\n");

		  if (NULL == (matr_ai=fopen(strcat(file1,":\\matr_ai.tmp"),"w+b")))
				    {printf("\nImpossibile aprire la prima matrice virtuale su disco.\n\n");
				     exit(0);}

		  if(to_lrn[0]=='o')
		  if (NULL == (matr_ao=fopen(strcat(file2,":\\matr_ao.tmp"),"w+b")))
				    {printf("\nImpossibile aprire la seconda matrice virtuale su disco.\n\n");
				     exit(0);}

		  if(to_lrn[0]=='t')
		  if (NULL == (matr_t =fopen(strcat(file3,":\\matr_t.tmp" ),"w+b")))
				    {printf("\nImpossibile aprire la terza matrice virtuale su disco.\n\n");
				     exit(0);}

		  }
		  else
		  {
		  mem_lib=1;
		  printf("Le matrici per l'applicazione .LRN sono gestite in memoria.\n\n");

		  i11h(&matr_ai_mem,&matr_ai_mem0,&matr_ai_mem00,
					  ncicli,(ni+1)*n_agenti);
		  if(to_lrn[0]=='o')
		  i11h(&matr_ao_mem ,&matr_ao_mem0, &matr_ao_mem00,
					  ncicli,no*n_agenti);

		  if(to_lrn[0]=='t')
		  i11h(&matr_t_mem ,&matr_t_mem0, &matr_t_mem00,
					  ncicli,no*n_agenti);

		  }
		  fscanf(lrn,"%f",&eps1_lrn);
		  fscanf(lrn,"%f",&alfa1_lrn);
		  fscanf(lrn,"%f",&eps2_lrn);
		  fscanf(lrn,"%f",&alfa2_lrn);

		  /* parametri per l'apprendimento ripetuto */
		  fscanf(lrn,"%ld",&ogni_lrn);
		  fscanf(lrn,"%ld",&quanti_lrn);
		  fscanf(lrn,"%ld",&ncicli_lrn);

		  /* c|s  */
		  fscanf(lrn,"%s",&cs_lrn);

		  if (cs_lrn[0] != 'c' && cs_lrn[0] != 's')
			{printf(
			"\nManca, nel file nome.LRN, l'indicazione 'c' o 's'.\n");
			exit(0);}

		  if(cs_lrn[0]=='c') {
		   if ((lrn_caso0=calloc(quanti_lrn,sizeof(long int)))==NULL)
				{
				 printf(
		   "Memoria insufficiente in ct_lrn, ridurre la lunghezza del ciclo di re-learn");
				 exit(0);
				 }
		   lrn_caso=lrn_caso0-1;

		   if ((lrn_caso20=calloc(quanti_lrn,sizeof(long int)))==NULL)
				{
				 printf(
		   "Memoria insufficiente in ct_lrn, ridurre la lunghezza del ciclo di re-learn");
				 exit(0);
				 }
		   lrn_caso2=lrn_caso20-1;
		   }

		  }

else              {
		  fclose(matr_ai);
/*                fclose(matr_ao);      */
		  fclose(matr_t);
		  fclose(lrn);

		  sprintf(delete,"del %c:\\matr_*.tmp",file1[0]);
		  if (mem_lib==0) system(delete);
		  }

        }

/*-------------------------------------------------------------------------*/
													/* ct_lrn.c */
       void  vW(FILE *m, long nc, long r, long c, float *v)
       {
       fseek(m,4L*((r-1)*nc+c-1),SEEK_SET);
       fwrite(v,4,1,m);
       }

/*-----------------------------------------------------------------*/
													/* ct_lrn.c */
       float vR(FILE *m, long nc, long r, long c)
       {
       float static v;
       fseek(m,4L*((r-1)*nc+c-1),SEEK_SET);
       fread(&v,4,1,m);
       return v;
       }


/*-------------------------------------------------------------------------*/
													/* ct_lrn.c */
	void Calcolo_lrn()
	{
	static unsigned i, j;

	/* pesi da j a i, in notazione (i,j) */

      for (agente=1;agente<=n_agenti;agente++){
       if(n_agenti>1){ni_t=abs(ni_per_agente[agente]);
		      nh_t=nh_per_agente[agente];
		      no_t=no_per_agente[agente];}
       else          {ni_t=ni; nh_t=nh; no_t=no;}

	/* determinazione del vettore di attivazioni hidden
	   (in ai_lrn Š compreso l'elemento bias) */

	ah [0+(agente-1)*(nh+1)] = 1; /* bias */
	for (i = 1; i <= nh_t; i++)
	{
		ah [i+(agente-1)*(nh+1)] = 0;
		for (j = 0; j <= ni_t; j++)
			 ah [i+(agente-1)*(nh+1)] += wih [i][j+(agente-1)*(ni+1)]
						     * ai_lrn [j+(agente-1)*(ni+1)];
		ah [i+(agente-1)*(nh+1)] = Flog(ah [i+(agente-1)*(nh+1)]);
	};

	/* determinazione del vettore di attivazioni output
	   (in ah Š compreso l'elemento bias) */

	for (i = 1; i <= no_t; i++)
	{
		ao_lrn [i+(agente-1)*no] = 0;
		for (j = 0; j <= nh_t; j++)
			 ao_lrn [i+(agente-1)*no] += who [i][j+(agente-1)*(nh+1)]
						 * ah [j+(agente-1)*(nh+1)];
		ao_lrn [i+(agente-1)*no] = Flog(ao_lrn [i+(agente-1)*no]);
	};
      }

	}

/*------------------------------------------------------------------------*/
													/* ct_lrn.c */
	void Apprendimento_lrn()
	{
	static unsigned i, ii, j, k;
	float delta, somma;
	/* pesi da j a i, in notazione (i,j) */


	/* correzione pesi nell'apprendimento */

    for (agente=1;agente<=n_agenti;agente++){

	/* da hidden a output */
	if (n_agenti>1){ni_t=abs(ni_per_agente[agente]);
			nh_t=nh_per_agente[agente];
			no_t=no_per_agente[agente];}
	else           {ni_t=ni;nh_t=nh;no_t=no;}

	for (i = 1; i <= no_t; i++)
	{       ii=i+(agente-1)*no;
		deltao [i] = (t_lrn [ii] - ao_lrn [ii]) * ao_lrn [ii] * (1.0 - ao_lrn [ii]);
		for (j = 0; j <= nh_t; j++)
		{
			dwho  [i][j+(agente-1)*(1+nh)] =
				       eps2_lrn * deltao [i] * ah [j+(agente-1)*(1+nh)] +
				       alfa2_lrn * dwho [i][j+(agente-1)*(1+nh)];
		}
	};

	/* da input a hidden */

	for (i = 1; i <= nh_t; i++)
	{
			somma = 0;
			for (k = 1; k <= no_t; k++)
						{ somma += deltao [k] *
							   who [k][i+(agente-1)*(1+nh)];}
		delta = ah [i+(agente-1)*(1+nh)] * (1.0 - ah [i+(agente-1)*(1+nh)]) * somma;
		for (j = 0; j <= ni_t; j++)
		{
			dwih  [i][j+(agente-1)*(1+ni)] =
				       eps1_lrn * delta * ai_lrn [j+(agente-1)*(1+ni)] +
				       alfa1_lrn * dwih [i][j+(agente-1)*(1+ni)];
		}
	};

	/* correzione pesi */

	for (i=1;i<=nh_t;i++){
	for (j=0;j<=ni_t;j++){
	wih [i][j+(agente-1)*(1+ni)] += dwih [i][j+(agente-1)*(1+ni)];}};

	for (i=1;i<=no_t;i++){
	for (j=0;j<=nh_t;j++){
	who [i][j+(agente-1)*(1+nh)] += dwho [i][j+(agente-1)*(1+nh)];}};
    }
	}


/*------------------------------------------------------------------------*/
													/* ct_lrn.c */
	void pesi_lrn()
	{
	static long int ciclo_lrn, quanti_lrn2, giorno, giorno_c, conta,
	agente, i;

if (cs_lrn[0]=='s')   /*  apprendimento sequenziale */
{

	    quanti_lrn2=quanti_lrn;
	    if(quanti_lrn > ciclo) quanti_lrn2=ciclo;
	    giorno=ciclo-quanti_lrn2+1;

	for (ciclo_lrn=1;ciclo_lrn<=ncicli_lrn;ciclo_lrn++)
	    {

		 for (agente=1;agente<=n_agenti;agente++)
		 for (i=0;i<=ni;i++){
		 if(mem_lib==0)ai_lrn[(agente-1)*(ni+1)+i]=
			       vR(matr_ai,(ni+1)*n_agenti,giorno,(agente-1)*(ni+1)+i+1);
		 else          ai_lrn[(agente-1)*(ni+1)+i]=
			       matr_ai_mem[giorno][(agente-1)*(ni+1)+i+1];
				    }

		 for (agente=1;agente<=n_agenti;agente++)
		 for (i=1;i<=no;i++){

		 if(to_lrn[0]=='o')
		 if(mem_lib==0)t_lrn [(agente-1)*no+i]    =
			       vR(matr_ao,no*n_agenti,giorno,(agente-1)*no+i);
		 else          t_lrn [(agente-1)*no+i]    =
			       matr_ao_mem[giorno][(agente-1)*no+i];

		 if(to_lrn[0]=='t')
		 if(mem_lib==0)t_lrn [(agente-1)*no+i]    =
			       vR(matr_t ,no*n_agenti,giorno,(agente-1)*no+i);
		 else          t_lrn [(agente-1)*no+i]    =
			       matr_t_mem[giorno][(agente-1)*no+i];
				    }

		 Calcolo_lrn();
		 Apprendimento_lrn();


	     giorno++; if (giorno>ciclo)giorno=ciclo-quanti_lrn2+1;

	    }
}
else                  /* apprendimento in ordine casuale */
{

	    quanti_lrn2=quanti_lrn;
	    if(quanti_lrn > ciclo) quanti_lrn2=ciclo;
	    giorno=ciclo-quanti_lrn2+1;
	    conta=1;

	    /* vettore lrn_caso di quanti_lrn2 elementi a caso
	       tra ciclo-quanti_lrn2+1  e  ciclo */
	    caso_lrn(quanti_lrn2);

	for (ciclo_lrn=1;ciclo_lrn<=ncicli_lrn;ciclo_lrn++)
	    {
		 giorno_c=lrn_caso[conta];
		 for (agente=1;agente<=n_agenti;agente++)
		 for (i=0;i<=ni;i++){
		 if(mem_lib==0)ai_lrn[(agente-1)*(ni+1)+i]=
			       vR(matr_ai,(ni+1)*n_agenti,giorno_c,(agente-1)*(ni+1)+i+1);
		 else          ai_lrn[(agente-1)*(ni+1)+i]=
			       matr_ai_mem[giorno_c][(agente-1)*(ni+1)+i+1];
				    }

		 for (agente=1;agente<=n_agenti;agente++)
		 for (i=1;i<=no;i++){

		 if(to_lrn[0]=='o')
		 if(mem_lib==0)t_lrn [(agente-1)*no+i]    =
			       vR(matr_ao,no*n_agenti,giorno_c,(agente-1)*no+i);
		 else          t_lrn [(agente-1)*no+i]    =
			       matr_ao_mem[giorno_c][(agente-1)*no+i];

		 if(to_lrn[0]=='t')
		 if(mem_lib==0)t_lrn [(agente-1)*no+i]    =
			       vR(matr_t ,no*n_agenti,giorno_c,(agente-1)*no+i);
		 else          t_lrn [(agente-1)*no+i]    =
			       matr_t_mem[giorno_c][(agente-1)*no+i];
				    }

		 Calcolo_lrn();
		 Apprendimento_lrn();


	     if(ciclo_lrn!=ncicli_lrn){
	     giorno++;conta++; if (giorno>ciclo){
						caso_lrn(quanti_lrn2);
						giorno=ciclo-quanti_lrn2+1;
						conta=1;}
				       }

	    }

}

	}

/*----------------------------------------------------------------------*/


	void caso_lrn(long int n)
	{

	static long int i;
	for (i=1;i<=n;i++)
	lrn_caso[i]=ciclo-n+DadoEscl(n);

	}


/*-----------------------------------------------------------------------*/

	long int Dado2(long int m)
	{
	static long int d;
	static long int dd;
	dd=rand();dd = (dd*m)/32767; d = dd + 1;
				     if (d == m + 1) d = m;
	return d;
	}


/*-----------------------------------------------------------------------*/

	long int DadoEscl(long int np) /* Dado esclusivo */
	{
	static long int i, ja, jb, m, d, epoca=1;
	if (epoca==1){
		     m=np;  /* i casi vanno da 1 a np */
		     for (i=1;i<=np;  i++) lrn_caso2 [i] = i;
		     for (i=1;i<=np-1;i++){
					  d = Dado2(m);
					  lrn_caso [i] = lrn_caso2 [d];
					  ja = jb = 1;
					  while (ja <= m){ /* i casi estratti
							      sono "tolti dall'
							      urna"*/
						     if (ja != d)
						     lrn_caso2[jb++]=lrn_caso2[ja++];
						     else ja++;}
					  m--;
					  }
		     lrn_caso [np] = lrn_caso2 [1];
		     }

	d = lrn_caso[epoca];
	epoca++; if (epoca == np + 1) epoca = 1;
	return d;
	}


/*----------------------------------------------------------------------*/
													/* ct_lrn.c */
/*      # 1¦ riga: 1; # 1¦ colonna: 1. float HUGE                                   */
	void  i11h(float huge ***a, float huge ***a0, float huge **a00,
		  unsigned long nr, unsigned long nc)
	{
	static long unsigned i; static float huge **b;
	Memoria(nr*nc*sizeof(float));
	if ((*a00=farcalloc(nr*nc,sizeof(float)))==NULL)  {
	   printf("Memoria insufficiente, ridurre il # dei casi o dei nodi");
	   exit(0);
	   }
        Memoria(nr*sizeof(float));
	if ((*a0=farcalloc(nr,sizeof(float huge *)))==NULL)  {
	   printf("Memoria insufficiente, ridurre il # dei casi o dei nodi");
	   exit(0);
	   }
	for (i=0;i<=nr-1;i++) {b=*a0+i;*b=*a00+i*nc-1;}
	*a=*a0-1;   
	}

/*--------------------------------------------------------------------------*/
													/* ct_lrn.c */
	void Memoria(unsigned long mem)
	{
/* La funzione farcalloc, usata obbligatoriamente perch‚ nell'help Borland
   Turbo C++ 2.0 solo per essa si dice che "far pointers (or huge pointers
   if blocks are larger than 64K) are used to access the allocated blocks",
   ha dato per• luogo a blocchi di macchina, senza uscita dalla funzione
   stessa, per alcune quantit… di richiesta di memoria - es. test con 70000
   hidden - violando la condizione standard di ritorno con NULL in tali 
   casi.
   Aggiungo quindi questo controllo esplicito, pur non annullando il control-
   lo su NULL nella chiamata a farcalloc. In effetti farcalloc alloca pi—
   memoria del valore 'mem' qui controllato, arrotondando a multipli di 16
   byte la memoria o aggiungendo 16 byte quando la richiesta sia di per s‚ un
   multiplo esatto (comportamento non dichiarato, ma da me riscontrato).
*/
        if (mem > farcoreleft()){
	   printf("*Memoria insufficiente, ridurre il # dei casi o dei nodi");
           exit(0);
           }
	}
