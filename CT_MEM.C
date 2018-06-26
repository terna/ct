#include "ct.h"

/*-------------------------------------------------------------------------*/
													/* ct_mem.c */
	void Alloc()
	{
	/* memoria dinamica */
        static int i;

	Avvisa(ni*n_agenti*2*sizeof(char));
	i10c(&tipoIn,&tipoIn0,&tipoIn00,ni*n_agenti,2lu);

	Avvisa(ni*n_agenti*5*sizeof(float));
	i11(&paramIn,&paramIn0,&paramIn00,ni*n_agenti,5lu);

	Avvisa(n_op_op*no*n_agenti*sizeof(float));
	i11(&operatore,&operatore0,&operatore00,n_op_op,no*n_agenti);
	i11(&operando, &operando0, &operando00,n_op_op,no*n_agenti);

	if ((riferIn0=calloc(ni*n_agenti,sizeof(long)))==NULL)           {
	   printf("Memoria insufficiente, ridurre il # dei casi o dei nodi");
	   exit(0);
	   }
	riferIn=riferIn0-1;

	Avvisa(n_C * sizeof(float));
	if ((C0=calloc(n_C,sizeof(float)))==NULL)           {
	   printf("Memoria insufficiente, ridurre la dim. del vettore C");
	   exit(0);
	   }
	C=C0-1;

	Avvisa(n_M * sizeof(float));
	if ((M0=calloc(n_M,sizeof(float)))==NULL)           {
	   printf("Memoria insufficiente, ridurre la dim. del vettore M");
	   exit(0);
	   }
	M=M0-1;

	Avvisa((ni+no)*n_agenti*sizeof(float));
	if ((max0=calloc((no+ni)*n_agenti,sizeof(float)))==NULL)           {
	   printf("Memoria insufficiente, ridurre il # dei casi o dei nodi");
	   exit(0);
	   }
	max=max0-1;

	if ((min0=calloc((no+ni)*n_agenti,sizeof(float)))==NULL)           {
	   printf("Memoria insufficiente, ridurre il # dei casi o dei nodi");
	   exit(0);
	   }
	min=min0-1;

	if ((val_iniz_SN0=calloc((no+ni)*n_agenti,sizeof(int)))==NULL)           {
	   printf("Memoria insufficiente, ridurre il # dei casi o dei nodi");
	   exit(0);
	   }
	val_iniz_SN=val_iniz_SN0-1;

	if ((val_iniz0=calloc((no+ni)*n_agenti,sizeof(float)))==NULL)           {
	   printf("Memoria insufficiente, ridurre il # dei casi o dei nodi");
	   exit(0);
	   }
	val_iniz=val_iniz0-1;
        for (i=1;i<=no+ni;i++) val_iniz[i]=0;

	if ((t0=calloc(no*n_agenti,sizeof(float)))==NULL)           {
	   printf("Memoria insufficiente, ridurre il # dei casi o dei nodi");
	   exit(0);
	   }
	t=t0-1;

	if ((ai=calloc((ni+1)*n_agenti,sizeof(float)))==NULL)         {
	   printf("Memoria insufficiente, ridurre il # dei casi o dei nodi");
	   exit(0);
	   }

	if ((aai=calloc((ni+1)*n_agenti,sizeof(float)))==NULL)         {
	   printf("Memoria insufficiente, ridurre il # dei casi o dei nodi");
	   exit(0);
	   }

	Avvisa((nh+1)*n_agenti*sizeof(float));
	if ((ah=calloc((nh+1)*n_agenti,sizeof(float)))==NULL)         {
	   printf("Memoria insufficiente, ridurre il # dei casi o dei nodi");
	   exit(0);
	   }

	if ((ao0=calloc(no*n_agenti,sizeof(float)))==NULL)          {
	   printf("Memoria insufficiente, ridurre il # dei casi o dei nodi");
	   exit(0);
	   }
	ao=ao0-1;

if (reLearn != 0){
	if ((ao0_lrn=calloc(no*n_agenti,sizeof(float)))==NULL)          {
	   printf("Memoria insufficiente, ridurre il # dei casi o dei nodi");
	   exit(0);
	   }
	ao_lrn=ao0_lrn-1;}

	Avvisa(nh*(ni+1)*n_agenti*sizeof(float));
	i10(&wih,&wih0,&wih00,nh,(ni+1)*n_agenti);

	i10(&dwih,&dwih0,&dwih00,nh,(ni+1)*n_agenti);

	Avvisa(no*(nh+1)*n_agenti*sizeof(float));
	i10(&who,&who0,&who00,no,(nh+1)*n_agenti);

	i10(&dwho,&dwho0,&dwho00,no,(nh+1)*n_agenti);

	Avvisa(no*ni*sizeof(float));
	i11(&derivate,&derivate0,&derivate00,no,ni);

	if ((deltao0=calloc(no,sizeof(float)))==NULL)      {
	   printf("Memoria insufficiente, ridurre il # dei casi o dei nodi");
	   exit(0);
	   }
	deltao=deltao0-1;

	}

/*----------------------------------------------------------------------*/
													/* ct_mem.c */									   
	void Avvisa (unsigned long max)
	{
	if (max > 65536L) {
	   printf(
	"\n\nUn vettore o una matrice sono > 64k; usare pointer huge,\n"
	"modificando tutte le indicazioni far in huge e utilizzando\n"
	"farcalloc() in luogo di calloc().\n");
	   exit(0);
	   }
	}


/*-----------------------------------------------------------------------*/
													/* ct_mem.c */							   
/*      le i?? sono funzioni di attribuzione della memoria
	a matrici bidimensionali - versione char

	# 1¦ riga: 1; # 1¦ colonna: 0.                                   */
	void  i10c(char far ***a, char far ***a0, char far **a00,
		  unsigned long nr, unsigned long nc)
	{
	static long unsigned i; static char far **b;
	if ((*a00=calloc(nr*nc,sizeof(char)))==NULL)  {
	   printf("Memoria insufficiente, ridurre il # dei casi o dei nodi");
	   exit(0);
	   }
	if ((*a0=calloc(nr,sizeof(char far *)))==NULL)  {
	   printf("Memoria insufficiente, ridurre il # dei casi o dei nodi");
	   exit(0);
	   }
	for (i=0;i<=nr-1;i++) {b=*a0+i;*b=*a00+i*nc;}
	*a=*a0-1;   
	}


/*----------------------------------------------------------------------*/
													/* ct_mem.c */
/*      le i?? sono funzioni di attribuzione della memoria
	a matrici bidimensionali

	# 1¦ riga: 1; # 1¦ colonna: 0.                                   */
	void  i10(float far ***a, float far ***a0, float far **a00,
		  unsigned long nr, unsigned long nc)
	{
	static long unsigned i; static float far **b;
	if ((*a00=calloc(nr*nc,sizeof(float)))==NULL)  {
	   printf("Memoria insufficiente, ridurre il # dei casi o dei nodi");
	   exit(0);
	   }
	if ((*a0=calloc(nr,sizeof(float far *)))==NULL)  {
	   printf("Memoria insufficiente, ridurre il # dei casi o dei nodi");
	   exit(0);
	   }
	for (i=0;i<=nr-1;i++) {b=*a0+i;*b=*a00+i*nc;}
	*a=*a0-1;   
	}

/*-----------------------------------------------------------------------*/
													/* ct_mem.c */
/*      # 1¦ riga: 1; # 1¦ colonna: 0.                                   */

	void  i10i(int far ***a, int far ***a0, int far **a00,
		   unsigned long nr, unsigned long nc)
	{
	static long unsigned i; static int far **b;
	if ((*a00=calloc(nr*nc,sizeof(int)))==NULL)  {
	   printf("Memoria insufficiente, ridurre il # dei casi o dei nodi");
	   exit(0);
	   }
	if ((*a0=calloc(nr,sizeof(int far *)))==NULL)  {
	   printf("Memoria insufficiente, ridurre il # degli indicatori { }");
	   exit(0);
	   }
	for (i=0;i<=nr-1;i++) {b=*a0+i;*b=*a00+i*nc;}
	*a=*a0-1;   
	}

/*-----------------------------------------------------------------------*/
													/* ct_mem.c */
/*      # 1¦ riga: 1; # 1¦ colonna: 1.                                   */
	void  i11(float far ***a, float far ***a0, float far **a00,
		  unsigned long nr, unsigned long nc)
	{
	static long unsigned i; static float far **b;
	if ((*a00=calloc(nr*nc,sizeof(float)))==NULL)  {
	   printf("Memoria insufficiente, ridurre il # dei casi o dei nodi");
	   exit(0);
	   }
	if ((*a0=calloc(nr,sizeof(float far *)))==NULL)  {
	   printf("Memoria insufficiente, ridurre il # dei casi o dei nodi");
	   exit(0);
	   }
	for (i=0;i<=nr-1;i++) {b=*a0+i;*b=*a00+i*nc-1;}
	*a=*a0-1;   
	}

