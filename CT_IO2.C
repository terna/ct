#include "ct.h"

/*-------------------------------------------------------------------------*/
													/* ct_io2.c */
	void MaxMin(int io)
	{
	static long unsigned i; static char stringa [40]; static int k;

	if (io==1){
	   for (agente=1;agente<=n_agenti;agente++){
	    if (n_agenti>1){ni_t=abs(ni_per_agente[agente]);
			    no_t=no_per_agente[agente];                                                                                                 
			    }
	    else {ni_t=ni; no_t=no;}

if(ni_per_agente[agente]<0) /* di questo agente non ci sono i dati, da costruire con quelli degli
                               ultimi due (qui conta solo l'ultimo) */
{
            /* controllo di coerenza */
            k=0;
	    for (i=1;i<=ni_t+no_t;i++) if(
                 val_iniz   [i+(agente-2)*(ni+no)]!=val_iniz   [i+(agente-3)*(ni+no)] ||
                 val_iniz_SN[i+(agente-2)*(ni+no)]!=val_iniz_SN[i+(agente-3)*(ni+no)] ||
                 min        [i+(agente-2)*(ni+no)]!=min        [i+(agente-3)*(ni+no)] ||
                 max        [i+(agente-2)*(ni+no)]!=max        [i+(agente-3)*(ni+no)] )
                                       k=1;
            if(k==1){
                     printf("\n\nErrore: due agenti tipo da dup. presentano differenze in @, min, max.\n\n");
                     exit(0);
                     }                          


	    for (i=1;i<=ni_t+no_t;i++){
                 val_iniz   [i+(agente-1)*(ni+no)]=val_iniz   [i+(agente-2)*(ni+no)];
                 val_iniz_SN[i+(agente-1)*(ni+no)]=val_iniz_SN[i+(agente-2)*(ni+no)];
                 min        [i+(agente-1)*(ni+no)]=min        [i+(agente-2)*(ni+no)];
                 max        [i+(agente-1)*(ni+no)]=max        [i+(agente-2)*(ni+no)];
                                       }
}


else	    for (i=1;i<=ni_t+no_t;i++){

              if (EOF==fscanf(ct,"%s",stringa))fineFile();
              if (stringa[0]=='@')
                 {
                 if(0 >=sscanf(stringa+1,"%f",&val_iniz[i+(agente-1)*(ni+no)]))fineFile();
                 val_iniz_SN [i+(agente-1)*(ni+no)]=1;
	         if (0  >=fscanf(ct,"%f",&min [i+(agente-1)*(ni+no)]))fineFile(); 
                 }
              else
	      if (0  >=sscanf(stringa,"%f",&min [i+(agente-1)*(ni+no)]))fineFile(); 
	      if (0  >=fscanf(ct,"%f",&max [i+(agente-1)*(ni+no)]))fineFile();

	      if (max[i+(agente-1)*(ni+no)]==min[i+(agente-1)*(ni+no)])
				 {
				  printf("\n\n\n"
				  "!! max=min in un nodo di input o di output.\n");
				  exit(0);
				  }
              if(val_iniz_SN[i+(agente-1)*(ni+no)]==1)
	      if (val_iniz[i+(agente-1)*(ni+no)] >
                       max[i+(agente-1)*(ni+no)] ||
                  val_iniz[i+(agente-1)*(ni+no)] <
                       min[i+(agente-1)*(ni+no)])
				 {
				  printf("\n\n\n"
				  "!! valore iniziale esterno a max o min in un nodo di input.\n");
				  exit(0);
				  }
	    }
	   }
	 }

	if (io==2){
	   for (agente=1;agente<=n_agenti;agente++){
	    if (n_agenti>1){ni_t=abs(ni_per_agente[agente]);
			    no_t=no_per_agente[agente];                                                                                                 
			    }
	    else {ni_t=ni; no_t=no;}

            if(ni_per_agente[agente] > 0){
	    fprintf(ct,"\n");
	    for (i=1;i<=ni_t+no_t;i++){
               if(val_iniz_SN[i+(agente-1)*(ni+no)]==1)
                  fprintf(ct,"@%f ", val_iniz[i+(agente-1)*(ni+no)]);
	       fprintf(ct,"%f ", min[i+(agente-1)*(ni+no)]);
	       fprintf(ct,"%f\n",max[i+(agente-1)*(ni+no)]);
	    }
                                         }
	   }
	 }

	}

/*------------------------------------------------------------------------*/
													/* ct_io2.c */
	void tipo_riferIn(int io)
	{
	static long unsigned i; static int k, m;

	if (io==1){
	   for (agente=1;agente<=n_agenti;agente++){
	    if (n_agenti>1)ni_t=abs(ni_per_agente[agente]);
	    else ni_t=ni;


if(ni_per_agente[agente]<0) /* di questo agente non ci sono i dati, da costruire con quelli degli
                               ultimi due (tenendo conto delle differenze tra i valori numerici) */
{
            /* controllo di coerenza */
            k=0;
	    for (i=1;i<=ni_t;i++) if(
                 tipoIn [i+(agente-2)*ni] [0] != tipoIn [i+(agente-3)*ni] [0])
                                     k=1;
            for (i=1;i<=ni_t;i++)
                for (m=1;m<=5;m++)
                 if(paramIn [i+(agente-2)*ni][m] != paramIn [i+(agente-3)*ni][m])
                                     k=1;

            if(k==1){
                     printf("\n\nErrore: due agenti tipo da dup. presentano differenze vietate\nin input.\n\n");
                     exit(0);
                     }                          

	    for (i=1;i<=ni_t;i++){
                 tipoIn [i+(agente-1)*ni] [0] = tipoIn [i+(agente-2)*ni] [0];

                for (m=1;m<=5;m++)
                 paramIn [i+(agente-1)*ni][m] = paramIn [i+(agente-2)*ni][m];

                if(riferIn [i+(agente-2)*ni] == riferIn [i+(agente-3)*ni])
                                             riferIn [i+(agente-1)*ni] = riferIn [i+(agente-2)*ni];

                else                         riferIn [i+(agente-1)*ni] = riferIn [i+(agente-2)*ni] +
                                             riferIn [i+(agente-2)*ni] - riferIn [i+(agente-3)*ni];

                                  }

}


else	    for (i=1;i<=ni_t;i++){
	      if (EOF==fscanf(ct,"%s", tipoIn  [i+(agente-1)*ni]))fineFile(); /* volutamente
										 con un solo indice 
										 e senza & */
	      /* i valori possibili per il primo dei due caratteri (quello
		 puntato dal solo primo indice) della stringa di due caratteri
		 (riga della matrice tipoIn(ni,2)
		 sono:
			't' = valore da copiare da un target del ciclo -1;
			'o' = valore da copiare da una a. output del ciclo -1;
			'i' = valore da copiare da una a.  input del ciclo -1;
			'I' = valore da copiare da una a.  input del ciclo  0;
			's' = sinusoide, con ampiezza 0öamp dell'intervallo
			      in ordinata, con intervallo di 'arco' giorni corrispondente
			      ad un ciclo completo sinusoidale e con ripetizione dal giorno 'rit',
			      pi— il caso, se 'range' > 0; l'addendo casuale sar… compreso
			      nell'intervallo 0ö'range';
			'c' = caso (uniforme) con intervallo tra 'min' e 'min + range';
                        'R' = richiamo della memoria n del ciclo precedente (vedere help per il
                              primo giorno);
			'f' = funzione speciale da definire in C.
			      NB in due punti qui, nonch‚ in Input()      */   

	      if (tipoIn [i+(agente-1)*ni] [0] != 't' && tipoIn [i+(agente-1)*ni] [0] != 'o' && tipoIn [i+(agente-1)*ni] [0] != 'i' 
											     && tipoIn [i+(agente-1)*ni] [0] != 'I'
	       && tipoIn [i+(agente-1)*ni] [0] != 's' && tipoIn [i+(agente-1)*ni] [0] != 'c' && tipoIn [i+(agente-1)*ni] [0] != 'R'
               && tipoIn [i+(agente-1)*ni] [0] != 'f')
		  {printf("%c = tipo di input non valido\n",tipoIn[i+(agente-1)*ni][0]);
		   exit(0);}

	      if (tipoIn [i+(agente-1)*ni] [0] == 'f')
		  {printf("f = tipo di procedura di gestione input non sviluppata\n");
		  exit(0);}

	      if (tipoIn [i+(agente-1)*ni] [0] == 't')
	      if (0  >=fscanf(ct,"%ld",&riferIn [i+(agente-1)*ni]))fineFile();

	      if (tipoIn [i+(agente-1)*ni] [0] == 'o')
	      if (0  >=fscanf(ct,"%ld",&riferIn [i+(agente-1)*ni]))fineFile();

	      if (tipoIn [i+(agente-1)*ni] [0] == 'i')
	      if (0  >=fscanf(ct,"%ld",&riferIn [i+(agente-1)*ni]))fineFile();

	      if (tipoIn [i+(agente-1)*ni] [0] == 'I')
	      if (0  >=fscanf(ct,"%ld",&riferIn [i+(agente-1)*ni]))fineFile();

	      if (tipoIn [i+(agente-1)*ni] [0] == 's')
	      if (0  >=fscanf(ct,"%f",&paramIn [i+(agente-1)*ni][1]) || /* min   */
		  0  >=fscanf(ct,"%f",&paramIn [i+(agente-1)*ni][2]) || /* amp   */
		  0  >=fscanf(ct,"%f",&paramIn [i+(agente-1)*ni][3]) || /* arco  */
		  0  >=fscanf(ct,"%f",&paramIn [i+(agente-1)*ni][4]) || /* rit   */
		  0  >=fscanf(ct,"%f",&paramIn [i+(agente-1)*ni][5])    /* range */
						       )fineFile();

	      if (tipoIn [i+(agente-1)*ni] [0] == 'c')
	      if (0  >=fscanf(ct,"%f",&paramIn [i+(agente-1)*ni][1]) || /* range */
		  0  >=fscanf(ct,"%f",&paramIn [i+(agente-1)*ni][2])
						       )fineFile();

	      if (tipoIn [i+(agente-1)*ni] [0] == 'R')
	      if (0  >=fscanf(ct,"%ld",&riferIn [i+(agente-1)*ni]))fineFile();

	    }
	   }
	 }

	if (io==2){
	   for (agente=1;agente<=n_agenti;agente++){
	    if (n_agenti>1)ni_t=abs(ni_per_agente[agente]);
	    else ni_t=ni;

            if(ni_per_agente[agente] > 0){
	    fprintf(ct,"\n");
	    for (i=1;i<=ni_t;i++){
	      fprintf(ct,"%c ",tipoIn [i+(agente-1)*ni] [0]); 

	      if (tipoIn [i+(agente-1)*ni] [0] == 't')
		 fprintf(ct,"%ld\n",riferIn [i+(agente-1)*ni]);

	      if (tipoIn [i+(agente-1)*ni] [0] == 'o')
		 fprintf(ct,"%ld\n",riferIn [i+(agente-1)*ni]);

	      if (tipoIn [i+(agente-1)*ni] [0] == 'i')
		 fprintf(ct,"%ld\n",riferIn [i+(agente-1)*ni]);

	      if (tipoIn [i+(agente-1)*ni] [0] == 'I')
		 fprintf(ct,"%ld\n",riferIn [i+(agente-1)*ni]);

	      if (tipoIn [i+(agente-1)*ni] [0] == 's')
		 fprintf(ct,"%f %f %f %f %f\n",paramIn [i+(agente-1)*ni][1],paramIn [i+(agente-1)*ni][2],
					       paramIn [i+(agente-1)*ni][3],paramIn [i+(agente-1)*ni][4],
					       paramIn [i+(agente-1)*ni][5]);

	      if (tipoIn [i+(agente-1)*ni] [0] == 'c')
		 fprintf(ct,"%f %f\n",paramIn [i+(agente-1)*ni][1],paramIn [i+(agente-1)*ni][2]);

	      if (tipoIn [i+(agente-1)*ni] [0] == 'R')
		 fprintf(ct,"%ld\n",riferIn [i+(agente-1)*ni]);


	    }
                                          }
	   }
	 }

	}
/*------------------------------------------------------------------------*/
													/* ct_io2.c */
	void Formule(int io)
	{
	static char stringa [40]; static long unsigned i, j, l; static int nop, nout; static float v;
	static char string2 [40]; static int k;

	/* input */
	if (io==1 && muto==0)printf("\nDopo ogni formula target premere un tasto per continuare\n");
	if (io==1){
	 for (agente=1;agente<=n_agenti;agente++){
	   if (n_agenti>1)no_t=no_per_agente[agente];
	   else no_t=no;

if(ni_per_agente[agente]<0) /* di questo agente non ci sono i dati, da costruire con quelli degli
                               ultimi due (tenendo conto delle differenze tra i valori numerici) */
{
            /* controllo di coerenza */
            k=0;
	    for (i=1;i<=no;i++) 
            for (j=1;j<=n_op_op;j++) {
              if(operatore [j] [i+(agente-2)*no] != operatore [j] [i+(agente-3)*no]) k=1;

	      if(operatore [j] [i+(agente-2)*no] < 0 &&
		 abs(operando  [j] [i+(agente-2)*no]) != abs(operando  [j] [i+(agente-3)*no])) k=1;

              if((operatore [j] [i+(agente-2)*no] ==  5 ||
                  operatore [j] [i+(agente-2)*no] ==  6)
                  &&
                  operando  [j] [i+(agente-2)*no] != operando  [j] [i+(agente-3)*no]) k=1;
                                      }


            if(k==1){
                     printf("\n\nErrore: due agenti tipo da dup. presentano differenze vietate\nnei target.\n\n");
                     exit(0);
                     }                          

	    for (i=1;i<=no;i++) 
            for (j=1;j<=n_op_op;j++) {
                 operatore [j] [i+(agente-1)*no]  = operatore [j] [i+(agente-2)*no];

	      if(operando  [j] [i+(agente-2)*no] == operando  [j] [i+(agente-3)*no] ||
		 operatore [j] [i+(agente-2)*no] < 0)
		 operando  [j] [i+(agente-1)*no]  = operando  [j] [i+(agente-2)*no];
              else
		 operando  [j] [i+(agente-1)*no]  = operando  [j] [i+(agente-2)*no] +
                 operando  [j] [i+(agente-2)*no]  - operando  [j] [i+(agente-3)*no];
                                      }



}

else{	   if (muto==0)printf("\n");
	   for (i=1;i<=no_t;i++){

		   stringa[0]=' '; nop = 0;
		   while (stringa[0] != ';')
			 {
			  if(EOF==fscanf(ct,"%s",stringa))fineFile(); /* qui come, in altri casi, & pu•
									  o no esserci */
			  if(stringa[0]=='+'){if(++nop==n_op_op)
						      {printf(
						      "\nTroppi operatori+operandi nella formula del target # %d\n",
						      i);
						      exit(0);
						       }   
					       operando [nop][i+(agente-1)*no]=0;
					       operatore[nop][i+(agente-1)*no]=1; /* '+' */               
					      }
			  if(stringa[0]=='-'){if(++nop==n_op_op)
						      {printf(
						      "\nTroppi operatori+operandi nella formula del target # %d\n",
						      i);
						      exit(0);
						       }   
					       operando [nop][i+(agente-1)*no]=0;
					       operatore[nop][i+(agente-1)*no]=2; /* '-' */    
					      }
			  if(stringa[0]=='*'){if(++nop==n_op_op)
						      {printf(
						      "\nTroppi operatori+operandi nella formula del target # %d\n",
						      i);
						      exit(0);
						       }   
					       operando [nop][i+(agente-1)*no]=0;
					       operatore[nop][i+(agente-1)*no]=3; /* '*' */        
					      }
			  if(stringa[0]=='/'){if(++nop==n_op_op)
						      {printf(
						      "\nTroppi operatori+operandi nella formula del target # %d\n",
						      i);
						      exit(0);
						       }   
					       operando [nop][i+(agente-1)*no]=0;
					       operatore[nop][i+(agente-1)*no]=4; /* '/' */               
					      }

			  if(stringa[0]=='H'){if(++nop==n_op_op)
						      {printf(
						      "\nTroppi operatori+operandi nella formula del target # %d\n",
						      i);
						      exit(0);
						       }   
					       if(0==sscanf(stringa+1,"%f",&v))
							   {printf("\nIndicazione scorretta in un operatore H "
								   "nella formula del target %d\n",i);
							    exit(0);
							    }                   
					       operando [nop][i+(agente-1)*no]=v;
					       operatore[nop][i+(agente-1)*no]=5; /* operatore H */
					      }
			  
			  if(stringa[0]=='h'){if(++nop==n_op_op)
						      {printf(
						      "\nTroppi operatori+operandi nella formula del target # %d\n",
						      i);
						      exit(0);
						       }   
					       if(0==sscanf(stringa+1,"%f",&v))
							   {printf("\nIndicazione scorretta in un operatore H "
								   "nella formula del target %d\n",i);
							    exit(0);
							    }                   
					       operando [nop][i+(agente-1)*no]=v;
					       operatore[nop][i+(agente-1)*no]=6; /* operatore h */
					      }
			  
			  if(stringa[0]=='e'){if(++nop==n_op_op)
						      {printf(
						      "\nTroppi operatori+operandi nella formula del target # %d\n",
						      i);
						      exit(0);
						       }   
					       operando [nop][i+(agente-1)*no]=0;
					       operatore[nop][i+(agente-1)*no]=7; /* 'e' */               
					      }

	  		  if(stringa[0]=='E'){if(++nop==n_op_op)
						      {printf(
						      "\nTroppi operatori+operandi nella formula del target # %d\n",
						      i);
						      exit(0);
						       }   
					       operando [nop][i+(agente-1)*no]=0;
					       operatore[nop][i+(agente-1)*no]=8; /* 'E' */               
					      }

			  if(stringa[0]=='u'){if(++nop==n_op_op)
						      {printf(
						      "\nTroppi operatori+operandi nella formula del target # %d\n",
						      i);
						      exit(0);
						       }
					       operando [nop][i+(agente-1)*no]=0;
					       operatore[nop][i+(agente-1)*no]=9; /* 'u' */
					      }

			  if(stringa[0]=='i'){if(++nop==n_op_op)
						      {printf(
						      "\nTroppi operatori+operandi nella formula del target # %d\n",
						      i);
						      exit(0);
						       }   
/* { } */                                      sscanf(stringa+1,"%c",&lista_start);
					       if(lista_start=='{'){leggi_lista(1,-10,&v);
								    operando [nop][i+(agente-1)*no]=v; /* attivazione input da lista */
								    operatore[nop][i+(agente-1)*no]=-10; nout=1;
								    }
					       else                {
					       if(0==sscanf(stringa+1,"%f",&v))
							   {printf("\nIndicazione scorretta di una attivazione "
								   "nella formula del target %d\n",i);
							    exit(0);}                   
					       operando [nop][i+(agente-1)*no]=v; /* attivazione input # ... */
					       operatore[nop][i+(agente-1)*no]=10;          
								    }
					      }
			  
			  if(stringa[0]=='o'){if(++nop==n_op_op)
						      {printf(
						      "\nTroppi operatori+operandi nella formula del target # %d\n",
						      i);
						      exit(0);
						       }   
/* { } */                                      sscanf(stringa+1,"%c",&lista_start);
					       if(lista_start=='{'){leggi_lista(1,-20,&v);
								    operando [nop][i+(agente-1)*no]=v; /* attivazione output da lista */
								    operatore[nop][i+(agente-1)*no]=-20; nout=1;
								    }
					       else                {
					       if(0==sscanf(stringa+1,"%f",&v))
							   {printf("\nIndicazione scorretta di una attivazione "
								   "nella formula del target %d\n",i);
							    exit(0);}                   
					       operando [nop][i+(agente-1)*no]=v; /* attivazione output # ... */
					       operatore[nop][i+(agente-1)*no]=20;          
								    }
					      }
			  
			  if(stringa[0]=='t'){if(++nop==n_op_op)
						      {printf(
						      "\nTroppi operatori+operandi nella formula del target # %d\n",
						      i);
						      exit(0);
						       }
                                               sscanf(stringa+1,"%c",&lista_start);
					       if(lista_start=='{'){leggi_lista(1,-30,&v);
								    operando [nop][i+(agente-1)*no]=v; /* attivazione target da lista */
								    operatore[nop][i+(agente-1)*no]=-30; nout=1;
								    }
					       else                {
					       if(0==sscanf(stringa+1,"%f",&v))
							   {printf("\nIndicazione scorretta di una attivazione "
								   "nella formula del target %d\n",i);
							    exit(0);}                   
					       operando [nop][i+(agente-1)*no]=v; /* valore target # ... */
					       operatore[nop][i+(agente-1)*no]=30;          
								    }
					      }

			  if(stringa[0]=='S'){if(++nop==n_op_op)
						      {printf(
						      "\nTroppi operatori+operandi nella formula del target # %d\n",
						      i);
						      exit(0);
						       }   
/* { } */                                      sscanf(stringa+1,"%c",&lista_start);
					       if(lista_start=='{'){leggi_lista(1,-100,&v);
								    operando [nop][i+(agente-1)*no]=v; /* S{ } */
								    operatore[nop][i+(agente-1)*no]=-100; nout=1;
								    }
					       else
							   {printf("\nIndicazione S{ } scorretta  "
								   "nella formula del target %d\n",i);
							    exit(0);}                   
					      }


                                              
                                              			  
			  if(stringa[0]=='C'){if(++nop==n_op_op)
						      {printf(
						      "\nTroppi operatori+operandi nella formula del target # %d\n",
						      i);
						      exit(0);
						       }   
					       if(0==sscanf(stringa+1,"%f",&v))
							   {printf("\nIndicazione scorretta in una costante C "
								   "nella formula del target %d\n",i);
							    exit(0);
							    }                   
					       operando [nop][i+(agente-1)*no]=v; /* costante C */
					       operatore[nop][i+(agente-1)*no]=300;          
					      }
                          if(stringa[0]=='M'){if(++nop==n_op_op)
						      {printf(
						      "\nTroppi operatori+operandi nella formula del target # %d\n",
						      i);
						      exit(0);
						       }   
					       if(0==sscanf(stringa+1,"%f",&v))
							   {printf("\nIndicazione scorretta in un richiamo M "
								   "nella formula del target %d\n",i);
							    exit(0);
							    }                   
					       operando [nop][i+(agente-1)*no]=v; /* richiamo M */
					       operatore[nop][i+(agente-1)*no]=400;          
					      }
			  if(stringa[0]=='R'){if(++nop==n_op_op)
						      {printf(
						      "\nTroppi operatori+operandi nella formula del target # %d\n",
						      i);
						      exit(0);
						       }   
					       if(0==sscanf(stringa+1,"%f",&v))
							   {printf("\nIndicazione scorretta in un richiamo R "
								   "nella formula del target %d\n",i);
							    exit(0);
							    }                   
					       operando [nop][i+(agente-1)*no]=v; /* richiamo R */
					       operatore[nop][i+(agente-1)*no]=401;          
					      }


	/* ultima possibilit…: un numero */
			  if(stringa[0]=='m' ||
			    (stringa[0]>='0' &&
			     stringa[0]<='9')){
					      if(++nop==n_op_op)
						      {printf(
						      "\nTroppi operatori+operandi nella formula del target # %d\n",
						      i);
						      exit(0);
						       }   
					      if(stringa[0]=='m')strcpy(string2,stringa+1);
						else strcpy(string2,stringa);
					      if(0==sscanf(string2,"%f",&v))
							   {printf("\nIndicazione scorretta di un valore numerico "
								   "nella formula del target %d\n",i);
							    exit(0);
							    }                   
					       operando [nop][i+(agente-1)*no]=v; /* numero positivo o negativo */
					       operatore[nop][i+(agente-1)*no]=100;
					       if(stringa[0]=='m')
						 operatore[nop][i+(agente-1)*no]=200;          
					      }
			    


			  if (muto==0 && nout==0 && operatore[nop][i+(agente-1)*no] != 0)printf("%s ",stringa); nout=0;
			  } 


		   if(muto==0){printf("\n");
			       l=0;
			       while(operatore[++l][i+(agente-1)*no]!=0)
				     {
				      if(operatore[l][i+(agente-1)*no]==1)printf("+ ");
				      if(operatore[l][i+(agente-1)*no]==2)printf("- ");
				      if(operatore[l][i+(agente-1)*no]==3)printf("* ");
				      if(operatore[l][i+(agente-1)*no]==4)printf("/ ");
				      if(operatore[l][i+(agente-1)*no]== 5)printf("H%.0f ",operando[l][i+(agente-1)*no]);
				      if(operatore[l][i+(agente-1)*no]== 6)printf("h%.0f ",operando[l][i+(agente-1)*no]);
	    			      if(operatore[l][i+(agente-1)*no]==7)printf("e ");
	       			      if(operatore[l][i+(agente-1)*no]==8)printf("E ");
				      if(operatore[l][i+(agente-1)*no]==9)printf("u ");
				      if(operatore[l][i+(agente-1)*no]==10)printf("i%.0f ",operando[l][i+(agente-1)*no]);
				      if(operatore[l][i+(agente-1)*no]==20)printf("o%.0f ",operando[l][i+(agente-1)*no]);
				      if(operatore[l][i+(agente-1)*no]==30)printf("t%.0f ",operando[l][i+(agente-1)*no]);
/* { } */                             if(operatore[l][i+(agente-1)*no]== -10)leggi_lista(2, -10,&operando[l][i+(agente-1)*no]);
/* { } */                             if(operatore[l][i+(agente-1)*no]== -20)leggi_lista(2, -20,&operando[l][i+(agente-1)*no]);
/* { } */                             if(operatore[l][i+(agente-1)*no]== -30)leggi_lista(2, -30,&operando[l][i+(agente-1)*no]);
/* { } */                             if(operatore[l][i+(agente-1)*no]==-100)leggi_lista(2,-100,&operando[l][i+(agente-1)*no]);
				      if(operatore[l][i+(agente-1)*no]==100)printf("%.5f ",operando[l][i+(agente-1)*no]);
				      if(operatore[l][i+(agente-1)*no]==200)printf("m%.5f ",operando[l][i+(agente-1)*no]);
				      if(operatore[l][i+(agente-1)*no]==300)printf("C%.0f ",operando[l][i+(agente-1)*no]);
				      if(operatore[l][i+(agente-1)*no]==400)printf("M%.0f ",operando[l][i+(agente-1)*no]);
				      if(operatore[l][i+(agente-1)*no]==401)printf("R%.0f ",operando[l][i+(agente-1)*no]);
				      }
			       printf(";\n");getch();
			       }
	  }
}
	 }
	}

	/* output */
	if (io==2){
	 for (agente=1;agente<=n_agenti;agente++){
	   if (n_agenti>1)no_t=no_per_agente[agente];
	   else no_t=no;

           if(ni_per_agente[agente] > 0){
	   fprintf(ct,"\n");
	   for (i=1;i<=no_t;i++)
		  {
			       l=0;
			       while(operatore[++l][i+(agente-1)*no]!=0)
				     {
				      if(operatore[l][i+(agente-1)*no]==1)fprintf(ct,"+ ");
				      if(operatore[l][i+(agente-1)*no]==2)fprintf(ct,"- ");
				      if(operatore[l][i+(agente-1)*no]==3)fprintf(ct,"* ");
				      if(operatore[l][i+(agente-1)*no]==4)fprintf(ct,"/ ");
				      if(operatore[l][i+(agente-1)*no]==5)fprintf(ct,"H%.0f ",operando[l][i+(agente-1)*no]);
				      if(operatore[l][i+(agente-1)*no]==6)fprintf(ct,"h%.0f ",operando[l][i+(agente-1)*no]);
	    			      if(operatore[l][i+(agente-1)*no]==7)fprintf(ct,"e ");
	       			      if(operatore[l][i+(agente-1)*no]==8)fprintf(ct,"E ");
				      if(operatore[l][i+(agente-1)*no]==9)fprintf(ct,"u ");
				      if(operatore[l][i+(agente-1)*no]==10)fprintf(ct,"i%.0f ",operando[l][i+(agente-1)*no]);
				      if(operatore[l][i+(agente-1)*no]==20)fprintf(ct,"o%.0f ",operando[l][i+(agente-1)*no]);
				      if(operatore[l][i+(agente-1)*no]==30)fprintf(ct,"t%.0f ",operando[l][i+(agente-1)*no]);
/* { } */                             if(operatore[l][i+(agente-1)*no]== -10)leggi_lista(3, -10,&operando[l][i+(agente-1)*no]);
/* { } */                             if(operatore[l][i+(agente-1)*no]== -20)leggi_lista(3, -20,&operando[l][i+(agente-1)*no]);
/* { } */                             if(operatore[l][i+(agente-1)*no]== -30)leggi_lista(3, -30,&operando[l][i+(agente-1)*no]);
/* { } */                             if(operatore[l][i+(agente-1)*no]==-100)leggi_lista(3,-100,&operando[l][i+(agente-1)*no]);
				      if(operatore[l][i+(agente-1)*no]==100)fprintf(ct,"%.5f ",operando[l][i+(agente-1)*no]);
				      if(operatore[l][i+(agente-1)*no]==200)fprintf(ct,"m%.5f ",operando[l][i+(agente-1)*no]);
				      if(operatore[l][i+(agente-1)*no]==300)fprintf(ct,"C%.0f ",operando[l][i+(agente-1)*no]);
				      if(operatore[l][i+(agente-1)*no]==400)fprintf(ct,"M%.0f ",operando[l][i+(agente-1)*no]);
				      if(operatore[l][i+(agente-1)*no]==401)fprintf(ct,"R%.0f ",operando[l][i+(agente-1)*no]);
				      }
				      if(agente==n_agenti && i==no_t)
							  fprintf(ct,";");
						     else fprintf(ct,";\n");
 
		   }
	 }
                                        }
	}

	}
