#include "ct.h"


/*-------------------------------------------------------------------------*/
													/* ct_calc.c */
	void Inizio()


	{
	static unsigned i, j;
	static float random;

	/* - - - - - - - - - - - - - - - - - - - - - - - */

	/* azzeramento delle matrici iniziali di variazione */
	for (agente=1;agente<=n_agenti;agente++){
	  for (i = 1; i <= nh; i++) {
		     for (j = 0; j <= ni; j++)
		     dwih [i][j+(agente-1)*(1+ni)] = 0;}
	  for (i = 1; i <= no; i++) {
		     for (j = 0; j <= nh; j++)
		     dwho [i][j+(agente-1)*(1+nh)] = 0;}
	}
	/* - - - - - - - - - - - - - - - - - - - - - - - */

	/* randomizzazione tra ñ intervRand */

	if (innesco==0) LeggiPesi();

	else {
	 for (agente=1;agente<=n_agenti;agente++){
	   for (i=1;i<=nh;i++){
	   for (j=0;j<=ni;j++){
	   random = rand()/32767.0;
	   /* random Š compreso tra 0 e 1 */
	   random = random * 2.0 * intervRand - intervRand;
	   /* ora tra ñ intervRand */
	   wih [i][j+(agente-1)*(1+ni)]= random;}}

	   for (i=1;i<=no;i++){
	   for (j=0;j<=nh;j++){
	   random = rand()/32767.0;
	   /* random Š compreso tra 0 e 1*/
	   random = random * 2.0 * intervRand - intervRand;
	   /* ora tra ñ intervRand */
	   who [i][j+(agente-1)*(1+nh)] = random;}}

	 }
	}

	}

/*------------------------------------------------------------------------*/
													/* ct_calc.c */
	void RPN_Target()
	{
	static long int i, ag, n_ag, caso; static int nop, l, ll;
	static long unsigned n, n_mm, quale_mem, quale_ag;
	static float R [101]; /* registri di calcolo */

	for (ll=1;ll<=n_C;ll++) C [ll] =-1; 
	for (ll=1;ll<=n_M;ll++) M [ll] = 0;


             for (i=1;i<=n_agenti;i++) vet_agenti[i]=i;
             n_ag=n_agenti;




     for (ag=1;ag<=n_agenti;ag++){

     if(sequenza_ag==0)
     {
      if(n_agenti>1){
      caso=Dado(n_ag--);
      agente=vet_agenti[caso];
      for (i=caso;i<=n_ag;i++) vet_agenti[i]=vet_agenti[i+1];
                     }
      else agente=1;
     }
     else agente=ag; /* caso di voluta non casualit…, vedi help
                        sull'impiego multiagente */

      if(n_agenti>1){no_t=no_per_agente[agente];
		     ni_t=abs(ni_per_agente[agente]);}
      else          {no_t=no; ni_t=ni;}


	for (i=1;i<=no_t;i++){

	    /* i valori effettivi saranno trasformati con
	       Scala(Intervallo_0_1(R[1],ni_t+i+(agente-1)*(ni+no)))

	       vedi al termine PUNTO CENTRALE DELL'ALGORITMO        */

	    nop=0;
	    while (operatore [++nop][i+(agente-1)*no]!=0)
	      {

	      /* + */
	      if (operatore[nop][i+(agente-1)*no]==1){
					R[1]=R[2]+R[1];
					for (l=2;l<=99;l++)R[l]=R[l+1];
					}   

	      /* - */
	      if (operatore[nop][i+(agente-1)*no]==2){
					R[1]=R[2]-R[1];
					for (l=2;l<=99;l++)R[l]=R[l+1];
					}   

	      /* * */
	      if (operatore[nop][i+(agente-1)*no]==3){
					R[1]=R[2]*R[1];
					for (l=2;l<=99;l++)R[l]=R[l+1];
					}   

	      /* / */
	      if (operatore[nop][i+(agente-1)*no]==4){
					if(R[1]==0){printf("\n\nDivisione per 0.\n"
							   "Calcolo target %ld nell'agente %ld"
							   " nel ciclo %ld\n",
							   i,agente,ciclo);
						    exit(0);
						    }
					R[1]=R[2]/R[1];
					for (l=2;l<=99;l++)R[l]=R[l+1];
					}

/* { } */
	      /* i{ */
	      if (operatore[nop][i+(agente-1)*no]==-10){
							for (l=100;l>=2;l--)R[l]=R[l-1];
							usa_lista(-10,nop,i,agente,&n,&n_mm);
							R[1]=deIntervallo_0_1(ai[n],n_mm);
							}

	      /* o{ */
	      if (operatore[nop][i+(agente-1)*no]==-20){
							for (l=100;l>=2;l--)R[l]=R[l-1];
							usa_lista(-20,nop,i,agente,&n,&n_mm);
							R[1]=deIntervallo_0_1(deScala(ao[n]),n_mm);
							}

	      /* t{ */
	      if (operatore[nop][i+(agente-1)*no]==-30){
							for (l=100;l>=2;l--)R[l]=R[l-1];
							usa_lista(-30,nop,i,agente,&n,&n_mm);
							  if(n>=i+(agente-1)*no){
							  printf("\nErrore logico: un target tenta di accedere"
							  " ad un target non ancora calcolato.\n");
							  exit(0);
										 }

							R[1]=deIntervallo_0_1(deScala(t [n]),n_mm);
							}

	      /* S{ */
	      if (operatore[nop][i+(agente-1)*no]==-100){
							usa_lista(-100,nop,i,agente,&quale_mem,&quale_ag);
							   if(mem_ag[quale_mem][quale_ag] != 999999000)
								R[1]=mem_ag[quale_mem][quale_ag];
							   else
								mem_ag[quale_mem][agente]=R[1];
							}


	      /* H */
	      if (operatore[nop][i+(agente-1)*no]==5){
					n=operando[nop][i+(agente-1)*no];
					for(ll=1;ll<n;ll++)
					  {
					   if(R[1]*R[1]<R[2]*R[2])
					      R[1]=R[2];
					for (l=2;l<=99;l++)R[l]=R[l+1];
					  }
					}   

	      /* h */
	      if (operatore[nop][i+(agente-1)*no]==6){
					n=operando[nop][i+(agente-1)*no];
					for(ll=1;ll<n;ll++)
					  {
					   if(R[1]<R[2])
					      R[1]=R[2];
					for (l=2;l<=99;l++)R[l]=R[l+1];
					  }
					}   

	      /* e */
	      if (operatore[nop][i+(agente-1)*no]==7){
                                        if(R[4]>R[3])R[1]=R[2];
					for (l=2;l<=97;l++)R[l]=R[l+3];
					}   

	      /* E */
	      if (operatore[nop][i+(agente-1)*no]==8){
                                        if(R[4]>=R[3])R[1]=R[2];
					for (l=2;l<=97;l++)R[l]=R[l+3];
					}   

	      /* u */
	      if (operatore[nop][i+(agente-1)*no]==9){
					if(R[4]==R[3])R[1]=R[2];
					for (l=2;l<=97;l++)R[l]=R[l+3];
					}   

	      /* attivazione input # ... */
	      if (operatore[nop][i+(agente-1)*no]==10){
					for (l=100;l>=2;l--)R[l]=R[l-1];
					n=operando[nop][i+(agente-1)*no];
					n_mm=n;
					if(n_agenti>1){n=i_pos[n];n_mm=mmi_pos[n_mm];}
					R[1]=deIntervallo_0_1(ai[n],n_mm);
					}

	      /* attivazione output # ... */
	      if (operatore[nop][i+(agente-1)*no]==20){
					for (l=100;l>=2;l--)R[l]=R[l-1];
					n=operando[nop][i+(agente-1)*no];
					n_mm=n;
					if(n_agenti==1)n_mm=n+ni_t;
					if(n_agenti> 1){n=o_pos[n];n_mm=mmo_pos[n_mm];}
					R[1]=deIntervallo_0_1(deScala(ao[n]),n_mm);
					}

	      /* valore target # ... */
	      if (operatore[nop][i+(agente-1)*no]==30){
					for (l=100;l>=2;l--)R[l]=R[l-1];
					n=operando[nop][i+(agente-1)*no];
					n_mm=n;
					if(n_agenti==1)n_mm=n+ni_t;
					if(n_agenti> 1){n=o_pos[n];n_mm=mmo_pos[n_mm];}
					if(n>=i+(agente-1)*no){
						 printf("\nErrore logico: un target tenta di accedere"
						 " ad un target non ancora calcolato.\n");
						 exit(0);
							      }
					R[1]=deIntervallo_0_1(deScala(t[n]),n_mm);
					}   

	      /* numero positivo */
	      if (operatore[nop][i+(agente-1)*no]==100){
					for (l=100;l>=2;l--)R[l]=R[l-1];
					R[1]=operando[nop][i+(agente-1)*no];
					}   

	      /* numero negativo */
	      if (operatore[nop][i+(agente-1)*no]==200){
					for (l=100;l>=2;l--)R[l]=R[l-1];
					R[1]= - operando[nop][i+(agente-1)*no];
					}   

	      /* costante C */
	      if (operatore[nop][i+(agente-1)*no]==300){
					for (l=100;l>=2;l--)R[l]=R[l-1];
					n=operando[nop][i+(agente-1)*no]; if(n>n_C){
						 printf("\nErrore in applicazione: si tenta di accedere"
						 " ad una costante casuale\nin posizione > max.\n");
						 exit(0);
								     }
					if (C[n] == -1.) C[n]=Caso(1.0);                          
					R[1]= C[n];
					}   

	      /* richiamo M */
	      if (operatore[nop][i+(agente-1)*no]==400){
					n=operando[nop][i+(agente-1)*no]; if(n>n_M){
						 printf("\nErrore in applicazione: si tenta di accedere"
						 " ad una posizione di memoria\nin posizione > max.\n");
						 exit(0);
								     }
					M[n]=R[1];
					}   

	      /* richiamo R */
	      if (operatore[nop][i+(agente-1)*no]==401){
					for (l=100;l>=2;l--)R[l]=R[l-1];
					n=operando[nop][i+(agente-1)*no]; if(n>n_M){
						 printf("\nErrore in applicazione: si tenta di accedere"
						 " ad una posizione di memoria\nin posizione > max.\n");
						 exit(0);
								     }
					R[1]= M[n];
					}   

	      }



						 /* PUNTO CENTRALE DELL'
						    ALGORITMO, PERCHE'
						    GARANTISCE IL RISPETTO
						    DEGLI INTERVALLI DI
						    APPLICAZIONE DELLE 
						    GRANDEZZE TARGET E QUINDI
						    DELLE ATTIVAZIONI OUTPUT,
						    DEGLI INPUT DA ESSE 
						    DERIVATI ...                */

	  if(R[1] > max [ni_t+i+(agente-1)*(ni+no)])R[1] = max [ni_t+i+(agente-1)*(ni+no)];
	  if(R[1] < min [ni_t+i+(agente-1)*(ni+no)])R[1] = min [ni_t+i+(agente-1)*(ni+no)];
	  t[i+(agente-1)*no]=Scala(Intervallo_0_1(R[1],ni_t+i+(agente-1)*(ni+no)));
			    }
     }

	if(to_lrn[0]=='t')
	if (reLearn != 0) for (agente=1;agente<=n_agenti;agente++)
                          for (i=1;i<=no;i++){
			  if(mem_lib==0)vW(matr_t ,no*n_agenti,ciclo,(agente-1)*no+i,&t [(agente-1)*no+i]);
			  else          matr_t_mem[ciclo][(agente-1)*no+i]=t [(agente-1)*no+i];
                                             }

	}

/*-------------------------------------------------------------------------*/
													/* ct_calc.c */
	void Calcolo()
	{
	static unsigned i, j;

	/* pesi da j a i, in notazione (i,j) */

      for (agente=1;agente<=n_agenti;agente++){
       if(n_agenti>1){ni_t=abs(ni_per_agente[agente]);
		      nh_t=nh_per_agente[agente];
		      no_t=no_per_agente[agente];}
       else          {ni_t=ni; nh_t=nh; no_t=no;}

	/* determinazione del vettore di attivazioni hidden
	   (in ai Š compreso l'elemento bias) */

	ah [0+(agente-1)*(nh+1)] = 1; /* bias */
	for (i = 1; i <= nh_t; i++)
	{
		ah [i+(agente-1)*(nh+1)] = 0;
		for (j = 0; j <= ni_t; j++)
			 ah [i+(agente-1)*(nh+1)] += wih [i][j+(agente-1)*(ni+1)] 
						     * ai [j+(agente-1)*(ni+1)];
		ah [i+(agente-1)*(nh+1)] = Flog(ah [i+(agente-1)*(nh+1)]);
	};

	/* determinazione del vettore di attivazioni output
	   (in ah Š compreso l'elemento bias) */

	for (i = 1; i <= no_t; i++)
	{
		ao [i+(agente-1)*no] = 0;
		for (j = 0; j <= nh_t; j++)
			 ao [i+(agente-1)*no] += who [i][j+(agente-1)*(nh+1)] 
						 * ah [j+(agente-1)*(nh+1)];
		ao [i+(agente-1)*no] = Flog(ao [i+(agente-1)*no]);
	};
      }

	if(to_lrn[0]=='o')
	if (reLearn != 0) for (agente=1;agente<=n_agenti;agente++)
			  for (i=1;i<=no;i++){
			  if(mem_lib==0)vW(matr_ao,no*n_agenti,ciclo,(agente-1)*no+i,&ao[(agente-1)*no+i]);
			  else          matr_ao_mem[ciclo][(agente-1)*no+i]=ao[(agente-1)*no+i];
					     }

	}

/*------------------------------------------------------------------------*/
													/* ct_calc.c */
	void Apprendimento()
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
		deltao [i] = (t [ii] - ao [ii]) * ao [ii] * (1.0 - ao [ii]);
		for (j = 0; j <= nh_t; j++)
		{
			dwho  [i][j+(agente-1)*(1+nh)] = 
				       eps2 * deltao [i] * ah [j+(agente-1)*(1+nh)] +
				       alfa2 * dwho [i][j+(agente-1)*(1+nh)];
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
				       eps1 * delta * ai [j+(agente-1)*(1+ni)] +
				       alfa1 * dwih [i][j+(agente-1)*(1+ni)];
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
													/* ct_calc.c */
	float Flog(float x)
	{
	return 1.0 / (1.0 + exp(-x));
	}

/*------------------------------------------------------------------------*/
													/* ct_calc.c */
	float deScala(float x)
	{
	static float y;
	y=(x-fattScala1)/fattScala;
	if (y<0.) y=0.;
	if (y>1.) y=1.;
	return y;
	}

/*------------------------------------------------------------------------*/
													/* ct_calc.c */
	float Scala(float x)
	{
	return x*fattScala+fattScala1;
	}

/*------------------------------------------------------------------------*/
													/* ct_calc.c */
	void Input()
	{
	static long unsigned i, pos;
        static float MM;

	/* primo ciclo */
					      /* I VALORI INIZIALI, SE NECESSARI,
						 RISULTANO INTERMEDI NELLA SCALA
						 EFFETTIVA MIN ö MAX, in quanto
						 posti = 0.5 nella scala 0 ö 1

                                                 a meno che operi val_iniz_SN==1   */  

	if (ciclo == 1) for (agente=1;agente<=n_agenti;agente++) /* si inizializzano
								    anche i sovrabbondanti */
                       {if(n_agenti>1) ni_t=abs(ni_per_agente[agente]);
                        else           ni_t=ni;

			   for (i=1;i<=ni;i++)  if(val_iniz_SN[i+(agente-1)*(ni+no)]==1)
                                                    ai [i+(agente-1)*(ni+1)]=
                                                       Intervallo_0_1(val_iniz[i+(agente-1)*(ni+no)],
                                                          i+(agente-1)*(ni+no));
                                                else ai [i+(agente-1)*(ni+1)]= 0.5;

			   for (i=1;i<=no;i++)  if(val_iniz_SN[i+ni_t+(agente-1)*(ni+no)]==1)
                                                    {ao [i+(agente-1)*no]=
                                                       Scala(Intervallo_0_1(val_iniz[i+ni_t+(agente-1)*(ni+no)],
                                                          i+ni_t+(agente-1)*(ni+no)));
                                                     t  [i+(agente-1)*no]=
                                                       Scala(Intervallo_0_1(val_iniz[i+ni_t+(agente-1)*(ni+no)],
                                                          i+ni_t+(agente-1)*(ni+no)));
                                                    }
                                                else
                                                     {ao [i+(agente-1)*no]    = 0.5;
						       t [i+(agente-1)*no]    = 0.5;}
			  }

	/* si copiano anche i sovrabbondanti */

	for (agente=1;agente<=n_agenti;agente++)
	    for (i=1;i<=ni;i++)
		aai[i+(agente-1)*(ni+1)]=ai[i+(agente-1)*(ni+1)];

	/* bias di input */

      for (agente=1;agente<=n_agenti;agente++){
       if(n_agenti>1) ni_t=abs(ni_per_agente[agente]);
       else           ni_t=ni;

	ai [0+(agente-1)*(ni+1)] = 1;

	for (i=1;i<=ni_t;i++) {

	   /* input di tipo 't' */
	   if (tipoIn [i+(agente-1)*ni][0] == 't')
				{pos=riferIn [i+(agente-1)*ni];
				 if (n_agenti>1)pos=o_pos[pos];
				 ai[i+(agente-1)*(ni+1)]=deScala(t[pos]);}
			     /* qui si dovrebbero applicare 
				deIntervallo_0_1 e poi Intevallo_0_1
				dunque non si applicano               */

	   /* input di tipo 'o' */
	   if (tipoIn [i+(agente-1)*ni][0] == 'o')
				{pos=riferIn [i+(agente-1)*ni];
				 if (n_agenti>1)pos=o_pos[pos];
				 ai[i+(agente-1)*(ni+1)]=deScala(ao[pos]);}
			     /* qui si dovrebbero applicare 
				deIntervallo_0_1 e poi Intevallo_0_1
				dunque non si applicano               */

	   /* input di tipo 'i' */
	   if (tipoIn [i+(agente-1)*ni][0] == 'i') 
				{pos=riferIn [i+(agente-1)*ni];
				 if (n_agenti>1)pos=i_pos[pos];
				 ai[i+(agente-1)*(ni+1)]=aai[pos];}
			     /* qui si dovrebbero applicare 
				deIntervallo_0_1 e poi Intevallo_0_1
				dunque non si applicano               */

	   /* input di tipo 'I' */
	   if (tipoIn [i+(agente-1)*ni][0] == 'I') {
				      pos=riferIn [i+(agente-1)*ni];
				      if (n_agenti>1) pos=i_pos[pos];
				      if (i+(agente-1)*(ni+1) > pos)
					   ai[i+(agente-1)*(ni+1)]=ai[pos];
				      else{printf("\nErrore logico: un input tenta di accedere"
					   " ad un input non ancora calcolato.\n");
					   exit(0);
					   }
				      }
			     /* qui si dovrebbero applicare 
				deIntervallo_0_1 e poi Intevallo_0_1
				dunque non si applicano               */

	   /* input di tipo 's' */
	   if (tipoIn [i+(agente-1)*ni][0] == 's') ai[i+(agente-1)*(ni+1)]=
	      Intervallo_0_1 (fSin(paramIn[i+(agente-1)*ni][1],paramIn[i+(agente-1)*ni][2],paramIn[i+(agente-1)*ni][3],
				   paramIn[i+(agente-1)*ni][4],paramIn[i+(agente-1)*ni][5]),i+(agente-1)*(ni+no));

	   /* input di tipo 'c' */
	   if (tipoIn [i+(agente-1)*ni][0] == 'c') ai[i+(agente-1)*(ni+1)]=
	      Intervallo_0_1 (paramIn[i+(agente-1)*ni][1]+Caso(paramIn[i+(agente-1)*ni][2]),i+(agente-1)*(ni+no));

	   /* input di tipo 'R' */

           /* qui non opera il PUNTO CENTRALE DELL'ALGORITMO (vedi RPN_Target)
              e pertanto Š necessario troncare tra min e max i valori M prima di
              applicare Intervallo_0_1                                          */

	   if (tipoIn [i+(agente-1)*ni][0] == 'R' && ciclo > 1)
				{pos=riferIn [i+(agente-1)*ni];
                                 MM=M[pos];

                                 if(MM > max [i+(agente-1)*(ni+no)])MM = max [i+(agente-1)*(ni+no)];
                                 if(MM < min [i+(agente-1)*(ni+no)])MM = min [i+(agente-1)*(ni+no)];

				 ai[i+(agente-1)*(ni+1)]=
                                 Intervallo_0_1(MM,i+(agente-1)*(ni+no));}


	   }
      }


      if (reLearn != 0) for (agente=1;agente<=n_agenti;agente++)
                        for (i=0;i<=ni;i++){
			if(mem_lib==0)vW(matr_ai,(ni+1)*n_agenti,ciclo,(agente-1)*(ni+1)+i+1,&ai[(agente-1)*(ni+1)+i]);
                        else          matr_ai_mem[ciclo][(agente-1)*(ni+1)+i+1]=ai[(agente-1)*(ni+1)+i];
                                           }
	 }

