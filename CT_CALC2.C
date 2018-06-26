#include "ct.h"


/*-------------------------------------------------------------------------*/
													/* ct_calc2.c */
	float Intervallo_0_1 (float a, long unsigned i)

	{  
	a=(a - min[i])/(max[i] - min[i]);
	return a;
	}


/*-------------------------------------------------------------------------*/
													/* ct_calc2.c */
	float deIntervallo_0_1 (float a, long unsigned i)

	{  
	a=a*(max[i] - min[i]) + min[i];
	return a;
	}


/*------------------------------------------------------------------------*/
													/* ct_calc2.c */
	float fSin(float min, float amp, float arco, float rit, float range)
	{
	if (arco==0){
		     printf("\nIl valore di 'arco' non puï essere = 0 in fSin");
		     exit(0);}

	return min + (sin(((ciclo+rit)*2*3.141593)/arco)+1)*amp/2. +
		     Caso(range) - range/2.;
	}

/*-------------------------------------------------------------------------*/
													/* ct_calc2.c */
	float Caso(float range)
	/* produce un valore casuale equidistribuito tra 0 e range */
	{
	return (rand()/32767.0)*range;
	}

/*-------------------------------------------------------------------------*/
													/* ct_calc2.c */
	int   Dado(int   range)
	/* produce un valore casuale intero equidistribuito tra 0 e range */
	{
        static int d;
	d = 1 + (rand()/32767.0)*range;
        if (d > range) d=range;
        return d;
	}

/*------------------------------------------------------------------------*/
													/* ct_calc2.c */
	void  Derivate()
	{
	/* nota interna per pt
	   indici coerenti come lettere con l'appunto 'master.chi'
		i per input
		j per hidden
		k per output
		*/
	static unsigned i, j, k;
	static float sum;
	static long int agente;  /* ridefinito per evitare il conflitto
				    con 'agente' in Calcolo()           */
	FILE *deriv;

	/* sç/no calcolo */

	if (der_med[0]=='s') {
	   if (muto == 0) {
	     printf("Calcolo delle derivate ÎaO/ÎaI sui punti medi,\n"
		    "riferite a valori aO scalati con fattScala e\n"
		    "derivanti da target riportati all'intervallo 0ˆ1.\n");
	     printf("Append al file %s.dem\n",fOut);
	     printf("L'output - distinto per agenti se pió d'uno - ä per ordine di aO\n"
		    "e - all'interno - di aI.\n");
	     }

	     strcpy(ffOut,fOut);
	     deriv=fopen(strcat(ffOut,".dem"),"a");

	/* impostazione vettore di input su valori medi */

	     for (agente=1;agente<=n_agenti;agente++){
		if (n_agenti>1) ni_t=abs(ni_per_agente[agente]);
		else            ni_t=ni;

		ai[0+(agente-1)*(ni+1)]=1;
		for (i=1;i<=ni_t;i++) ai [i+(agente-1)*(ni+1)] = 0.5;
	     }
		/* calcolo delle attivazioni ah e ao */

		Calcolo();

	     for (agente=1;agente<=n_agenti;agente++){
		if (n_agenti>1){ni_t=abs(ni_per_agente[agente]);
				nh_t=nh_per_agente[agente];
				no_t=no_per_agente[agente];}
		else           {ni_t=ni;nh_t=nh;no_t=no;}

		/* derivate aO/aI */

		for (k=1;k<=no_t;k++) {
		for (i=1;i<=ni_t;i++) {
				     sum=0;
				     for (j=1;j<=nh_t;j++)
						    sum=sum+who[k][j+(agente-1)*(nh+1)]*
							ah[j+(agente-1)*(nh+1)]*(1-ah[j+(agente-1)*(nh+1)])*
							wih[j][i+(agente-1)*(ni+1)];
			derivate[k][i]=ao[k+(agente-1)*no]*(1-ao[k+(agente-1)*no])*sum;
				     }
				     }

		for (k=1;k<=no_t;k++){for (i=1;i<=ni_t;i++)
					fprintf(deriv,"%.3f ",derivate[k][i]);
				      fprintf(deriv,"\n");
				      }
		fprintf(deriv,"\n");
	     }
		fclose(deriv);

	}
	}

/*------------------------------------------------------------------------*/
