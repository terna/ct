#include "ct.h"

/*-------------------------------------------------------------------------*/
													/* ct_io.c */
	void Dati_e_Parametri(char file[]) {
	static char file1[40], file2 [20]=" ", esegui [50] = "copy ";
	static char linea[128], sn;
	static int ss=0, s=0, nuovo_num_h=0, i, n;
				/* la complessa struttura dell'input con la
				   gestione del while(s == 0) serve per
				   neutralizzare eventuali input non validi
				   (es. caratteri in luogo di numeri) */

	ct = fopen(file,"r");


if (muto==0) {
	/* - - - - - - - - - - - - - - - - - - - - - - - */

	/* lettura: ni=# p.e. di input, nh=# p.e. hidden (ä modificabile),
		    no=# p.e. di output */
	fscanf(ct,"%ld",&ni); ni_copia=ni;

if (ni < 0) MultiAgente(-ni,1); 
		       /* ni sarÖ determinato diversamente;
			  qui, indica temporaneamente il num. di agenti */
   
else{   fscanf(ct,"%lu",&nh);
	fscanf(ct,"%lu",&no);
    

	printf(
	"\n# p.e. di input = %ld; # p.e. hidden = %lu; "
	"# p.e. di output %lu;\n"
"Enter per confermare il # di p.e. hidden, oppure introdurre un valore: ",
						  ni, nh, no);

						      
       while (s == 0) {
			fgets(linea,81,stdin);
			if (linea[0]=='\n') s = 1;
			else {ss=s=sscanf(linea,"%lu",&nh); nuovo_num_h=1;}
		      }
    }
	if(ss==EOF)ss=0;

	fscanf(ct,"%ld",&n_op_op2);

        if(n_op_op2<0){n_op_op = -1 * n_op_op2;
                       sequenza_ag=1;
                       /* vedi definizioni iniziali in ct.c */}
        else n_op_op = n_op_op2;

	printf("# operandi+operatori max %lu.\n",n_op_op);

	/* - - - - - - - - - - - - - - - - - - - - - - - */

	Alloc(); /* ad Alloc() si accede dopo che MultiAgente, se richiamata,
		    ha fissato il valore di n_agenti, che per default vale 1 */

	/* - - - - - - - - - - - - - - - - - - - - - - - */

	/* innesco numeri casuali */

	fscanf(ct,"%u",&innesco);
	printf("\nL'attuale innesco dei valori casuali ä %u\n"
"Enter per confermarlo, oppure introdurre un # tra 0 e 65535 (se ä 0, si\n"
"cercano i file .1 e .2 dei pesi e si cont. l'appr. da tali pesi): ",innesco);
	s = 0;
	while (s == 0) {
			fgets(linea,81,stdin);
			if (linea[0]=='\n') s = 1;
			else ss=s=sscanf(linea,"%u",&innesco);
		       }
	if(ss==EOF)ss=0;

	srand(innesco);

	/* - - - - - - - - - - - - - - - - - - - - - - - */

	/* # di cicli */

	fscanf(ct,"%ld",&ncicli);
	fscanf(ct,"%ld",&ne);
     printf(
     "\nL'attuale numero di cicli ä %ld (l'errore medio ä calcolato ogni %ld cicli)\n"
     "Enter per conf. oppure intr. un # (meglio un mult. del secondo #): ",
	ncicli,ne);
	s = 0;
	while (s == 0) {
			fgets(linea,81,stdin);
			if (linea[0]=='\n') s = 1;
			else ss=s=sscanf(linea,"%ld",&ncicli);
		       }
	if(ss==EOF)ss=0;

	/* - - - - - - - - - - - - - - - - - - - - - - - */

	/* fattore di scala: fattScala */

/* fattScala opera comprimendo la scala dei dati di output, supposti tra 0 e 1,
all'intervallo tra 0.5*(1-fattScala) e 1-0.5*(1-fattScala). Ad esempio,
fattScala=1 significa nessuna variazione; fattScala=0.8 fissa l'intervallo tra
minimo e massimo a 0.1--0.9. */

	fscanf(ct,"%f",&fattScala);
	printf("\nL'attuale fattore di scala ä %.1f\n"
"Enter per confermarlo oppure introdurre un valore (tra >0 e Û1)\n"
"[NB 0.8 per l'intervallo 0.1--0.9 di Nshell ]  ",fattScala);
	s = 0;
	while (s == 0) {
			fgets(linea,81,stdin);
			if (linea[0]=='\n') s = 1;
			else ss=s=sscanf(linea,"%f",&fattScala);
		       }
	if(ss==EOF)ss=0;

	/* - - - - - - - - - - - - - - - - - - - - - - - */

	/* intervallo dei valori casuali (tra Ò intervRand) */

	fscanf(ct,"%f",&intervRand);
	printf("\nI valori casuali iniziali dei pesi sono compresi tra Ò%.1f\n"
"Enter per confermare l'intervallo, oppure introdurre un valore (positivo) ",
intervRand);
	s = 0;
	while (s == 0) {
			fgets(linea,81,stdin);
			if (linea[0]=='\n') s = 1;
			else ss=s=sscanf(linea,"%f",&intervRand);
		       }
	if(ss==EOF)ss=0;

	/* - - - - - - - - - - - - - - - - - - - - - - - */

	/* nome dei file di output (con varie estensioni) */

	fscanf(ct,"%s",&fOut);
	if (nuovo_num_h) printf(
		"\nATTENZIONE:\nä cambiato il numero di nodi hidden; "
		"cambia il nome dei file di OUTPUT?");
	printf(
"\n"
"Il nome attuale (con varie estensioni) dei file di output ä: '%s'"
"\n\n"
"Enter per confermare oppure introdurre un nome (max 8 caratteri)  ",fOut);
	s = 0;
	while (s == 0) {
			fgets(linea,81,stdin);
			if (linea[0]=='\n') s = 1;
			else ss=s=sscanf(linea,"%s",&fOut);
		       }
	if(ss==EOF)ss=0;

	/* - - - - - - - - - - - - - - - - - - - - - - - */

	/* lettura: eps1 (2k nel learning con backpropagation),
		    alfa1 (momentum)

		    INPUT-HIDDEN */

	fscanf(ct,"%f", &eps1);
	fscanf(ct,"%f", &alfa1);
	printf("\nINPUT-HIDDEN\n"
	       "\neps (2k nel learning della BP) %.1f;\n"
	       "alfa (momentum) %.1f.\n"
	"Enter per confermare eps, oppure introdurre un valore: ",eps1,alfa1);
	s = 0;
	while (s == 0) {
			fgets(linea,81,stdin);
			if (linea[0]=='\n') s = 1;
			else ss=s=sscanf(linea,"%f",&eps1);
		       }
	if(ss==EOF)ss=0;


	printf("Enter per confermare alfa, oppure introdurre un valore: ");
	s = 0;
	while (s == 0) {
			fgets(linea,81,stdin);
			if (linea[0]=='\n') s = 1;
			else ss=s=sscanf(linea,"%f",&alfa1);
		       }
	if(ss==EOF)ss=0;

	/* - - - - - - - - - - - - - - - - - - - - - - - */
	/* lettura: eps2 (2k nel learning con backpropagation),
		    alfa2 (momentum)

		    HIDDEN-OUTPUT */

	fscanf(ct,"%f", &eps2);
	fscanf(ct,"%f", &alfa2);
	printf("\nHIDDEN-OUTPUT\n"
	       "\neps (2k nel learning della BP) %.1f;\n"
	       "alfa (momentum) %.1f.\n"
	"Enter per confermare eps, oppure introdurre un valore: ",eps2,alfa2);
	s = 0;
	while (s == 0) {
			fgets(linea,81,stdin);
			if (linea[0]=='\n') s = 1;
			else ss=s=sscanf(linea,"%f",&eps2);
		       }
	if(ss==EOF)ss=0;

	printf("Enter per confermare alfa, oppure introdurre un valore: ");
	s = 0;
	while (s == 0) {
			fgets(linea,81,stdin);
			if (linea[0]=='\n') s = 1;
			else ss=s=sscanf(linea,"%f",&alfa2);
		       }
	if(ss==EOF)ss=0;

	/* - - - - - - - - - - - - - - - - - - - - - - - */
	/* calcolo delle derivate ÎaO/ÎaI sui val. 'medi' 0.5 delle aI 
	   (file .dem) */

	fscanf(ct,"%s",&der_med);
	if (der_med[0]=='s') printf(
"\nSi effettua il calcolo delle derivate ÎaO/ÎaI sui val. 'medi' 0.5 delle aI\n");
	if (der_med[0]=='n') printf(
"\nNon si effet. il calcolo delle derivate ÎaO/ÎaI sui val. 'medi' 0.5 delle aI\n");
printf("Enter per confermare, oppure 's' per il calcolo,"
" 'n' per non svolgerlo: ");
	s = 0;
	while (s == 0) {
			fgets(linea,81,stdin);
			if (linea[0]=='\n') s = 1;
			else ss=s=sscanf(linea,"%s",&der_med);
		       }
	if(ss==EOF)ss=0;

    if (der_med[0] != 's' && der_med[0] != 'n'){printf("\n's' o 'n'\n");exit(0);}

	/* - - - - - - - - - - - - - - - - - - - - - - - */

	MaxMin(1);           /* 1 significa input */
			     /* lettura dei valori max e min previsti
				per tutti i nodi di input ed output */

	tipo_riferIn(1);     /* 1 significa input */


	Formule(1);          /* 1 significa input */ 
			     /* formule dei target */

	/* - - - - - - - - - - - - - - - - - - - - - - - */
}

if (muto != 0) {
	fscanf(ct,"%ld",&ni);
if (ni < 0) MultiAgente(-ni,1); 
		       /* ni sarÖ determinato diversamente;
			  qui, indica il num. di agenti */
   
else{   fscanf(ct,"%lu",&nh);
	fscanf(ct,"%lu",&no);
    }
	fscanf(ct,"%ld",&n_op_op2);
			if(n_op_op2<0){n_op_op = -1 * n_op_op2;
				       sequenza_ag=1;
				       /* vedi definizioni iniziali in ct.c */}
			else n_op_op = n_op_op2;
	Alloc();
	fscanf(ct,"%u",&innesco);
	srand(innesco);
	fscanf(ct,"%ld",&ncicli);
	fscanf(ct,"%ld",&ne);
	fscanf(ct,"%f",&fattScala);
	fscanf(ct,"%f",&intervRand);
	fscanf(ct,"%s",&fOut);
	fscanf(ct,"%f", &eps1);
	fscanf(ct,"%f", &alfa1);
	fscanf(ct,"%f", &eps2);
	fscanf(ct,"%f", &alfa2);
	fscanf(ct,"%s",&der_med);
	MaxMin(1);
	tipo_riferIn(1);
	Formule(1);

	/* ä inutile leggere i commenti, perchÇ il file non sarÖ salvato */

}

	/* - - - - - - - - - - - - - - - - - - - - - - - */
	/* commenti */
	i = 0; n = -1;
	while ( i<=100 && 0 != fgets(&commenti[i][0],81,ct) )
		n=i++;

	/* - - - - */

	fclose(ct);
	printf(cancellaSchermo);

	/* - - - - - - - - - - - - - - - - - - - - - - - */

	if (ss != 0) {printf(
	"I parametri sono cambiati; salvare i nuovi parametri (s/n)?");
		      sn=' ';
		      while (sn==' '){sn = getch();
				      if (sn!='s' && sn!='n')sn=' ';
				      }
		      printf("\n\n");
		      if (sn=='s')printf("Salvataggio e backup file\n\n");
		      else ss=0;
		      }

	/* salva il file .ct in .ct0 */

	if (ss != 0) {
	   strcpy(file1,file);
	   strcat(file2,file); strcat(file2,"0");
	   system(strcat(esegui,strcat(file1,file2)));  /* Attenzione, comando
							   MS-DOS              */
	   }

	/* salvataggio dei valori definiti */

	if (ss != 0) {
	   ct=fopen(file,"w");

	   if (ni_copia<0) MultiAgente(0,2);
	   else            fprintf(ct,"%ld %lu %lu\n", ni ,nh, no);
	   fprintf(ct,"%lu\n", n_op_op);
	   fprintf(ct,"%u\n%ld %ld\n%f\n%f\n%s\n%f %f\n%f %f\n%s\n",
		   innesco,ncicli,ne,fattScala,intervRand,fOut,
		   eps1,alfa1,eps2,alfa2,der_med);
	   MaxMin(2);       /* 2 significa output */
	   tipo_riferIn(2); /* " "         "      */
	   Formule(2);      /* " "         "      */

	   for (i=0;i<=n;i++) fprintf(ct,"%s",commenti[i]);

	   if(n == -1) fprintf(ct,"\n");

	   fclose(ct);
	   } 

	}

/*------------------------------------------------------------------------*/
													/* ct_io.c */
	void fineFile()
	{
	printf(
"\n\n\nIl file di estensione CT, associato all'applicazione, non contiene\n"
"sufficienti informazioni.\n");
	exit(0);
	}

/*------------------------------------------------------------------------*/
													/* ct_io.c */
	void Messaggio()
	{
	if (muto != 2) {
printf(
"\nI valori di errore BP sono calcolati sui valori scalati con fattScala.\n"
"Le perc. in v.a. sono invece determinate su valori non scalati, nonchÇ\n"
"misurati con le grandezze originarie (non riportate all'intervallo 0ˆ1).\n"
"Le perc. sono calcolate rapportando il tot. degli abs. degli scostamenti\n"
"al totale degli abs. dei valori target.\n\n");
			}
	}


/*------------------------------------------------------------------------*/
													/* ct_io.c */
	void ScriviPesi()
	{
	static unsigned i, j;
	FILE *pesi;

/* output su file, in  ordine di p.e. di provenienza di w */

	strcpy(ffOut,fOut);
	pesi=fopen(strcat(ffOut,".1"),"w");

      for (agente=1;agente<=n_agenti;agente++){
       if(n_agenti>1){ni_t=abs(ni_per_agente[agente]);
		      nh_t=nh_per_agente[agente];}
       else          {ni_t=ni; nh_t=nh;}
	for (j=0;j<=ni_t;j++){
	for (i=1;i<=nh_t;i++){
	fprintf(pesi,"%f ",wih [i][j+(agente-1)*(1+ni)]);}
	fprintf(pesi,"\n");}
	fprintf(pesi,"\n");
      }
	fclose(pesi);

	strcpy(ffOut,fOut);
	pesi=fopen(strcat(ffOut,".2"),"w");

      for (agente=1;agente<=n_agenti;agente++){
       if(n_agenti>1){nh_t=nh_per_agente[agente];
		      no_t=no_per_agente[agente];}
       else          {nh_t=nh; no_t=no;}
	for (j=0;j<=nh_t;j++){
	for (i=1;i<=no_t;i++){
	fprintf(pesi,"%f ",who [i][j+(agente-1)*(1+nh)]);}
	fprintf(pesi,"\n");}
	fprintf(pesi,"\n");
      }
	fclose(pesi);

	}

/*------------------------------------------------------------------------*/
													/* ct_io.c */
	void LeggiPesi()
	{
	static long unsigned i, j; static int test;
	FILE *pesi;

/* input da file, in  ordine di p.e. di provenienza di w */

	strcpy(ffOut,fOut);
	if (NULL==(pesi=fopen(strcat(ffOut,".1"),"r"))) {
	   printf("Manca il file dei pesi di estensione .1");
	   exit(0);
	   }

      for (agente=1;agente<=n_agenti;agente++){
       if(n_agenti>1){ni_t=abs(ni_per_agente[agente]);
		      nh_t=nh_per_agente[agente];}
       else          {ni_t=ni; nh_t=nh;}
	for (j=0;j<=ni_t;j++){
	for (i=1;i<=nh_t;i++){
	if(0  >=fscanf(pesi,"%f",&wih [i][j+(agente-1)*(ni+1)])){
	   printf("\nMancano dati nel file di pesi %s",ffOut);
	   exit(0);
	   }
	}}
      }

	if(EOF != fscanf(pesi,"%d",&test)){
	   printf("\nEccesso di dati nel file di pesi %s",ffOut);
	   exit(0);
	   }
	fclose(pesi);

	strcpy(ffOut,fOut);
	if (NULL==(pesi=fopen(strcat(ffOut,".2"),"r"))) {
	   printf("Manca il file dei pesi di estensione .2");
	   exit(0);
	   }


      for (agente=1;agente<=n_agenti;agente++){
       if(n_agenti>1){nh_t=nh_per_agente[agente];
		      no_t=no_per_agente[agente];}
       else          {nh_t=nh; no_t=no;}
	for (j=0;j<=nh_t;j++){
	for (i=1;i<=no_t;i++){
	if(0  >=fscanf(pesi,"%f",&who [i][j+(agente-1)*(nh+1)])){
	   printf("\nMancano dati nel file di pesi %s",ffOut);
	   exit(0);
	   }
	}}
      }

	if(EOF != fscanf(pesi,"%d",&test)){
	   printf("\nEccesso di dati nel file di pesi %s",ffOut);
	   exit(0);
	   }
	fclose(pesi);

	}

/*------------------------------------------------------------------------*/
													/* ct_io.c */
	void  file_ou(float perct0, float errore0, float perc0)
	{
	static int conta; static unsigned m;
        static float perct0C;

	conta=0;

	if (ciclo % ogni_quante_r==0)
{
    
	if (quante_col==0 || (++conta<=quante_col && quali_col[conta]==1))
	fprintf(ou,"%7ld | ",ciclo);

	    for (agente=1;agente<=n_agenti;agente++){
	      if (n_agenti>1)ni_t=abs(ni_per_agente[agente]);
	      else           ni_t=ni;
	      for (m=1;m<=ni_t;m++)
		  if (quante_col==0 || (++conta<=quante_col && quali_col[conta]==1))
		  fprintf(ou,"%.3f ",deIntervallo_0_1(ai[m+(agente-1)*(ni+1)],
							 m+(agente-1)*(ni+no)));
						     }
	    fprintf(ou,"| ");

	    for (agente=1;agente<=n_agenti;agente++){
	      if (n_agenti>1){ni_t=abs(ni_per_agente[agente]);no_t=no_per_agente[agente];}
	      else           {ni_t=ni;no_t=no;}
	      for (m=1;m<=no_t;m++)
		  if (quante_col==0 || (++conta<=quante_col && quali_col[conta]==1))
		  fprintf(ou,"%.3f ",deIntervallo_0_1(
					      deScala(ao[m+(agente-1)*no]),
							 m+ni_t+(agente-1)*(ni+no)));
						     }
	    fprintf(ou,"| ");

	    for (agente=1;agente<=n_agenti;agente++){
	      if (n_agenti>1){ni_t=abs(ni_per_agente[agente]);no_t=no_per_agente[agente];}
	      else           {ni_t=ni;no_t=no;}
	      for (m=1;m<=no_t;m++)
	          if (quante_col==0 || (++conta<=quante_col && quali_col[conta]==1))
		  fprintf(ou,"%.3f ",deIntervallo_0_1(
		                   	      deScala(t[m+(agente-1)*no]),
							 m+ni_t+(agente-1)*(ni+no)));
						     }
	    fprintf(ou,"| ");


	    perct0C=perct0; if(perct0C==0)perct0C=0.0001;
	    if (quante_col==0 || (++conta<=quante_col && quali_col[conta]==1))
	    fprintf(ou,"%.5f ",errore0);
	    if (quante_col==0 || (++conta<=quante_col && quali_col[conta]==1))
            fprintf(ou,"%.3f",100*perc0/perct0C);


	fprintf(ou,"\n");
}	
	}

/*------------------------------------------------------------------------*/
													/* ct_io.c */
	void  file_ini()
	{
	static int i;

	fscanf(ini,"%d",&ogni_quante_r);
	fscanf(ini,"%d",&quante_col);

	if (quante_col != 0)
	{
		Avvisa(quante_col*sizeof(int));
		if ((quali_col0=calloc(quante_col,sizeof(int)))==NULL){
			printf("Errore nel numero di colonne da mandare"
			       " in output.\n");
			exit(0);}
		quali_col=quali_col0-1;

	for (i=1;i<=quante_col;i++)
		fscanf(ini,"%d",&quali_col[i]);
	}
	
	}
