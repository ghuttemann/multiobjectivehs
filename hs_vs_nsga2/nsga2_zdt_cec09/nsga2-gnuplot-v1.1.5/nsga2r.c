/* NSGA-II routine (implementation of the 'main' function) */

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <unistd.h>
# include <sys/time.h>
# include <string.h>

# include "global.h"
# include "rand.h"

int nreal;
int nbin;
int nobj;
int ncon;
int popsize;
double pcross_real;
double pcross_bin;
double pmut_real;
double pmut_bin;
double eta_c;
double eta_m;
int stopping_criteria;
int do_sampling;
long long cur_cycles;
long long n_cycles;
long long cur_msec, sampling_msec, iter_msec;
long long total_time, n_msec;
long long start_time;
long long iter_start;
long long curgen, ngen;
int nbinmut;
int nrealmut;
int nbincross;
int nrealcross;
int *nbits;
double *min_realvar;
double *max_realvar;
double *min_binvar;
double *max_binvar;
int bitlength;
int choice;
int obj1;
int obj2;
int obj3;
int angle1;
int angle2;
test_problem problem_function;

int stop(int criteria,
	 long long iter_msec, long long n_msec,
	 long long curgen, long long ngen,
	 long long cycles);
long long getTimeMillis();
/*
void sampling(population *pop, int stop_criteria, long long interval, 
        int curgen, long long *iter_msec, FILE *sampling_output);
*/

int main (int argc, char **argv)
{
    int i;
    FILE *fpt0;
    FILE *fpt1;
    FILE *fpt2;
    FILE *fpt3;
    FILE *fpt4;
    FILE *fpt5;
    FILE *fpt6;
    FILE *gp;
    population *parent_pop;
    population *child_pop;
    population *mixed_pop;
    if (argc<2)
    {
        printf("\n Usage ./nsga2r random_seed \n");
        exit(1);
    }
    seed = (double)atof(argv[1]);
    if (seed<=0.0 || seed>=1.0)
    {
        printf("\n Entered seed value is wrong, seed value must be in (0,1) \n");
        exit(1);
    }
    fpt0 = fopen("pareto_front.txt","w");
    fpt1 = fopen("initial_pop.out","w");
    fpt2 = fopen("final_pop.out","w");
    fpt3 = fopen("best_pop.out","w");
    fpt4 = fopen("all_pop.out","w");
    fpt5 = fopen("params.out","w");
    fprintf(fpt1,"# This file contains the data of initial population\n");
    fprintf(fpt2,"# This file contains the data of final population\n");
    fprintf(fpt3,"# This file contains the data of final feasible population (if found)\n");
    fprintf(fpt4,"# This file contains the data of all generations\n");
    fprintf(fpt5,"# This file contains information about inputs as read by the program\n");
    printf("\n Enter the problem relevant and algorithm relevant parameters ... ");
    printf("\n Enter the problem name : ");
    scanf("%s", problem_name);
    for (i=0; i < problem_count; i++)
    {
        if (strcasecmp(problems[i], problem_name) == 0)
            break;
    }
    if (i < problem_count)
    {
        problem_function = (test_problem) get_problem_function(problem_name);
    }
    else
    {
        printf("\n Problem read is : %s", problem_name);
        printf("\n Wrong problem name entered, hence exiting \n");
        exit (1);
    }
    printf("\n Enter the population size (a multiple of 4) : ");
    scanf("%d",&popsize);
    if (popsize<4 || (popsize%4)!= 0)
    {
        printf("\n population size read is : %d",popsize);
        printf("\n Wrong population size entered, hence exiting \n");
        exit (1);
    }
    printf("\n Enter the number of cycles to run the algorithm : ");
    scanf("%lld", &n_cycles);
    if (n_cycles < 0)
      {
	printf("\n number of cycles read is : %lld", n_cycles);
	printf("\n Wrong number of cycles entered, hence exiting \n");
	exit(1);
      }
    printf("\n Enter the stopping criteria (0 for # of generations, 1 for # of miliseconds) : ");
    scanf("%d", &stopping_criteria);
    if (stopping_criteria == 0)
    { /* number of generations */
        printf("\n Enter the number of generations : ");
        scanf("%lld",&ngen);
        if (ngen<1)
	{
            printf("\n number of generations read is : %lld",ngen);
            printf("\n Wrong nuber of generations entered, hence exiting \n");
            exit (1);
        }
    }
    else if (stopping_criteria == 1)
    { /* number of miliseconds */
        printf("\n Enter the number of miliseconds : ");
        scanf("%lld", &n_msec);
        if (n_msec < 1)
        {
            printf("\n number of miliseconds read is : %lld", n_msec);
            printf("\n Wrong number of miliseconds entered, hence exiting\n");
            exit(1);
        }
    }
    else
    { /* error */
        printf("\n stopping criteria entered is : %d", stopping_criteria);
        printf("\n Wrong stopping criteria entered, hence exiting\n");
        exit(1);
    }
    printf("\n Do you want to print sampling information (0 for NO, 1 for YES) : ");
    scanf("%d", &do_sampling);
    if (do_sampling!=0 && do_sampling!=1)
    {
        printf("\n Entered the wrong choice, hence exiting, choice entered was %d\n",do_sampling);
        exit(1);
    }
    printf("\n Enter the number of objectives : ");
    scanf("%d",&nobj);
    if (nobj<1)
    {
        printf("\n number of objectives entered is : %d",nobj);
        printf("\n Wrong number of objectives entered, hence exiting \n");
        exit (1);
    }
    printf("\n Enter the number of constraints : ");
    scanf("%d",&ncon);
    if (ncon<0)
    {
        printf("\n number of constraints entered is : %d",ncon);
        printf("\n Wrong number of constraints enetered, hence exiting \n");
        exit (1);
    }
    printf("\n Enter the number of real variables : ");
    scanf("%d",&nreal);
    if (nreal<0)
    {
        printf("\n number of real variables entered is : %d",nreal);
        printf("\n Wrong number of variables entered, hence exiting \n");
        exit (1);
    }
    if (nreal != 0)
    {
        min_realvar = (double *)malloc(nreal*sizeof(double));
        max_realvar = (double *)malloc(nreal*sizeof(double));
        for (i=0; i<nreal; i++)
        {
            printf ("\n Enter the lower limit of real variable %d : ",i+1);
            scanf ("%lf",&min_realvar[i]);
            printf ("\n Enter the upper limit of real variable %d : ",i+1);
            scanf ("%lf",&max_realvar[i]);
            if (max_realvar[i] <= min_realvar[i])
            {
                printf("\n Wrong limits entered for the min and max bounds of real variable, hence exiting \n");
                exit(1);
            }
        }
        printf ("\n Enter the probability of crossover of real variable (0.6-1.0) : ");
        scanf ("%lf",&pcross_real);
        if (pcross_real<0.0 || pcross_real>1.0)
        {
            printf("\n Probability of crossover entered is : %e",pcross_real);
            printf("\n Entered value of probability of crossover of real variables is out of bounds, hence exiting \n");
            exit (1);
        }
        printf ("\n Enter the probablity of mutation of real variables (1/nreal) : ");
        scanf ("%lf",&pmut_real);
        if (pmut_real<0.0 || pmut_real>1.0)
        {
            printf("\n Probability of mutation entered is : %e",pmut_real);
            printf("\n Entered value of probability of mutation of real variables is out of bounds, hence exiting \n");
            exit (1);
        }
        printf ("\n Enter the value of distribution index for crossover (5-20): ");
        scanf ("%lf",&eta_c);
        if (eta_c<=0)
        {
            printf("\n The value entered is : %e",eta_c);
            printf("\n Wrong value of distribution index for crossover entered, hence exiting \n");
            exit (1);
        }
        printf ("\n Enter the value of distribution index for mutation (5-50): ");
        scanf ("%lf",&eta_m);
        if (eta_m<=0)
        {
            printf("\n The value entered is : %e",eta_m);
            printf("\n Wrong value of distribution index for mutation entered, hence exiting \n");
            exit (1);
        }
    }
    printf("\n Enter the number of binary variables : ");
    scanf("%d",&nbin);
    if (nbin<0)
    {
        printf ("\n number of binary variables entered is : %d",nbin);
        printf ("\n Wrong number of binary variables entered, hence exiting \n");
        exit(1);
    }
    if (nbin != 0)
    {
        nbits = (int *)malloc(nbin*sizeof(int));
        min_binvar = (double *)malloc(nbin*sizeof(double));
        max_binvar = (double *)malloc(nbin*sizeof(double));
        for (i=0; i<nbin; i++)
        {
            printf ("\n Enter the number of bits for binary variable %d : ",i+1);
            scanf ("%d",&nbits[i]);
            if (nbits[i] < 1)
            {
                printf("\n Wrong number of bits for binary variable entered, hence exiting");
                exit(1);
            }
            printf ("\n Enter the lower limit of binary variable %d : ",i+1);
            scanf ("%lf",&min_binvar[i]);
            printf ("\n Enter the upper limit of binary variable %d : ",i+1);
            scanf ("%lf",&max_binvar[i]);
            if (max_binvar[i] <= min_binvar[i])
            {
                printf("\n Wrong limits entered for the min and max bounds of binary variable entered, hence exiting \n");
                exit(1);
            }
        }
        printf ("\n Enter the probability of crossover of binary variable (0.6-1.0): ");
        scanf ("%lf",&pcross_bin);
        if (pcross_bin<0.0 || pcross_bin>1.0)
        {
            printf("\n Probability of crossover entered is : %e",pcross_bin);
            printf("\n Entered value of probability of crossover of binary variables is out of bounds, hence exiting \n");
            exit (1);
        }
        printf ("\n Enter the probability of mutation of binary variables (1/nbits): ");
        scanf ("%lf",&pmut_bin);
        if (pmut_bin<0.0 || pmut_bin>1.0)
        {
            printf("\n Probability of mutation entered is : %e",pmut_bin);
            printf("\n Entered value of probability  of mutation of binary variables is out of bounds, hence exiting \n");
            exit (1);
        }
    }
    if (nreal==0 && nbin==0)
    {
        printf("\n Number of real as well as binary variables, both are zero, hence exiting \n");
        exit(1);
    }
    choice=0;
    printf("\n Do you want to use gnuplot to display the results realtime (0 for NO) (1 for yes) : ");
    scanf("%d",&choice);
    if (choice!=0 && choice!=1)
    {
        printf("\n Entered the wrong choice, hence exiting, choice entered was %d\n",choice);
        exit(1);
    }
    if (choice==1)
    {
        gp = popen(GNUPLOT_COMMAND,"w");
        if (gp==NULL)
        {
            printf("\n Could not open a pipe to gnuplot, check the definition of GNUPLOT_COMMAND in file global.h\n");
            printf("\n Edit the string to suit your system configuration and rerun the program\n");
            exit(1);
        }
        if (nobj==2)
        {
            printf("\n Enter the objective for X axis display : ");
            scanf("%d",&obj1);
            if (obj1<1 || obj1>nobj)
            {
                printf("\n Wrong value of X objective entered, value entered was %d\n",obj1);
                exit(1);
            }
            printf("\n Enter the objective for Y axis display : ");
            scanf("%d",&obj2);
            if (obj2<1 || obj2>nobj)
            {
                printf("\n Wrong value of Y objective entered, value entered was %d\n",obj2);
                exit(1);
            }
            obj3 = -1;
        }
        else
        {
            printf("\n #obj > 2, 2D display or a 3D display ?, enter 2 for 2D and 3 for 3D :");
            scanf("%d",&choice);
            if (choice!=2 && choice!=3)
            {
                printf("\n Entered the wrong choice, hence exiting, choice entered was %d\n",choice);
                exit(1);
            }
            if (choice==2)
            {
                printf("\n Enter the objective for X axis display : ");
                scanf("%d",&obj1);
                if (obj1<1 || obj1>nobj)
                {
                    printf("\n Wrong value of X objective entered, value entered was %d\n",obj1);
                    exit(1);
                }
                printf("\n Enter the objective for Y axis display : ");
                scanf("%d",&obj2);
                if (obj2<1 || obj2>nobj)
                {
                    printf("\n Wrong value of Y objective entered, value entered was %d\n",obj2);
                    exit(1);
                }
                obj3 = -1;
            }
            else
            {
                printf("\n Enter the objective for X axis display : ");
                scanf("%d",&obj1);
                if (obj1<1 || obj1>nobj)
                {
                    printf("\n Wrong value of X objective entered, value entered was %d\n",obj1);
                    exit(1);
                }
                printf("\n Enter the objective for Y axis display : ");
                scanf("%d",&obj2);
                if (obj2<1 || obj2>nobj)
                {
                    printf("\n Wrong value of Y objective entered, value entered was %d\n",obj2);
                    exit(1);
                }
                printf("\n Enter the objective for Z axis display : ");
                scanf("%d",&obj3);
                if (obj3<1 || obj3>nobj)
                {
                    printf("\n Wrong value of Z objective entered, value entered was %d\n",obj3);
                    exit(1);
                }
                printf("\n You have chosen 3D display, hence location of eye required \n");
                printf("\n Enter the first angle (an integer in the range 0-180) (if not known, enter 60) :");
                scanf("%d",&angle1);
                if (angle1<0 || angle1>180)
                {
                    printf("\n Wrong value for first angle entered, hence exiting \n");
                    exit(1);
                }
                printf("\n Enter the second angle (an integer in the range 0-360) (if not known, enter 30) :");
                scanf("%d",&angle2);
                if (angle2<0 || angle2>360)
                {
                    printf("\n Wrong value for second angle entered, hence exiting \n");
                    exit(1);
                }
            }
        }
    }
    printf("\n Input data successfully entered, now performing initialization \n");
    fprintf(fpt5,"\n Problem name = %s",problem_name);
    fprintf(fpt5,"\n Population size = %d",popsize);
    fprintf(fpt5,"\n Number of cycles = %lld",n_cycles);
    fprintf(fpt5,"\n Stopping criteria = %d",stopping_criteria);
    fprintf(fpt5,"\n Print sampling information = %d",do_sampling);
    fprintf(fpt5,"\n Number of miliseconds = %lld",n_msec);
    fprintf(fpt5,"\n Number of generations = %lld",ngen);
    fprintf(fpt5,"\n Number of objective functions = %d",nobj);
    fprintf(fpt5,"\n Number of constraints = %d",ncon);
    fprintf(fpt5,"\n Number of real variables = %d",nreal);
    if (nreal!=0)
    {
        for (i=0; i<nreal; i++)
        {
            fprintf(fpt5,"\n Lower limit of real variable %d = %e",i+1,min_realvar[i]);
            fprintf(fpt5,"\n Upper limit of real variable %d = %e",i+1,max_realvar[i]);
        }
        fprintf(fpt5,"\n Probability of crossover of real variable = %e",pcross_real);
        fprintf(fpt5,"\n Probability of mutation of real variable = %e",pmut_real);
        fprintf(fpt5,"\n Distribution index for crossover = %e",eta_c);
        fprintf(fpt5,"\n Distribution index for mutation = %e",eta_m);
    }
    fprintf(fpt5,"\n Number of binary variables = %d",nbin);
    if (nbin!=0)
    {
        for (i=0; i<nbin; i++)
        {
            fprintf(fpt5,"\n Number of bits for binary variable %d = %d",i+1,nbits[i]);
            fprintf(fpt5,"\n Lower limit of binary variable %d = %e",i+1,min_binvar[i]);
            fprintf(fpt5,"\n Upper limit of binary variable %d = %e",i+1,max_binvar[i]);
        }
        fprintf(fpt5,"\n Probability of crossover of binary variable = %e",pcross_bin);
        fprintf(fpt5,"\n Probability of mutation of binary variable = %e",pmut_bin);
    }
    fprintf(fpt5,"\n Seed for random number generator = %e",seed);
    bitlength = 0;
    if (nbin!=0)
    {
        for (i=0; i<nbin; i++)
        {
            bitlength += nbits[i];
        }
    }
    fprintf(fpt1,"# of objectives = %d, # of constraints = %d, # of real_var = %d, # of bits of bin_var = %d, constr_violation, rank, crowding_distance\n",nobj,ncon,nreal,bitlength);
    fprintf(fpt2,"# of objectives = %d, # of constraints = %d, # of real_var = %d, # of bits of bin_var = %d, constr_violation, rank, crowding_distance\n",nobj,ncon,nreal,bitlength);
    fprintf(fpt3,"# of objectives = %d, # of constraints = %d, # of real_var = %d, # of bits of bin_var = %d, constr_violation, rank, crowding_distance\n",nobj,ncon,nreal,bitlength);
    fprintf(fpt4,"# of objectives = %d, # of constraints = %d, # of real_var = %d, # of bits of bin_var = %d, constr_violation, rank, crowding_distance\n",nobj,ncon,nreal,bitlength);
    nbinmut = 0;
    nrealmut = 0;
    nbincross = 0;
    nrealcross = 0;
    parent_pop = (population *)malloc(sizeof(population));
    child_pop = (population *)malloc(sizeof(population));
    mixed_pop = (population *)malloc(sizeof(population));
    allocate_memory_pop (parent_pop, popsize);
    allocate_memory_pop (child_pop, popsize);
    allocate_memory_pop (mixed_pop, 2*popsize);
    if (do_sampling) {
        fpt6 = fopen("sampling.txt", "w");
    }
    randomize();
    initialize_pop (parent_pop);

    printf("\n Initialization done, now performing first generation");
    decode_pop(parent_pop);
    evaluate_pop (parent_pop, problem_function);
    assign_rank_and_crowding_distance (parent_pop);
    report_pop (parent_pop, fpt1);
    fprintf(fpt4,"# gen = 1\n");
    report_pop(parent_pop, fpt4);
    printf("\n gen = 1");
    fflush(stdout);
    if (choice!=0) onthefly_display (parent_pop,gp,1);
    fflush(fpt1);
    fflush(fpt2);
    fflush(fpt3);
    fflush(fpt4);
    fflush(fpt5);

    curgen = 0;
    cur_msec = 0;
    total_time = getTimeMillis();
    start_time = getTimeMillis();

    for (cur_cycles = 0; cur_cycles < n_cycles; cur_cycles++)
    {
        iter_start = getTimeMillis();
        iter_msec = 0; /* restart msec elapsed */
        while (!stop(stopping_criteria, iter_msec, n_msec, curgen, ngen, cur_cycles+1))
        {
            selection (parent_pop, child_pop);
            mutation_pop (child_pop);
            decode_pop(child_pop);
            evaluate_pop(child_pop, problem_function);
            merge (parent_pop, child_pop, mixed_pop);
            fill_nondominated_sort (mixed_pop, parent_pop);
        
            /* Comment following five lines if information for all
               generations is not desired, it will speed up the execution */
            //fprintf(fpt4,"# gen = %lld, # sec = %lld\n",curgen, cur_msec);
            //report_pop(parent_pop,fpt4);
            //fflush(fpt4);
            //if (choice!=0) onthefly_display (parent_pop,gp,curgen);
            //printf("\n gen = %lld, msec = %lld",curgen, cur_msec);

            curgen++; /* update number of generations */
            iter_msec = getTimeMillis() - iter_start; /* update msec elapsed */
        }

        cur_msec = getTimeMillis() - start_time;

	if (do_sampling) {
            sampling_msec = getTimeMillis();
            report_pareto_front(parent_pop, fpt6, cur_msec, curgen);
            long long elapsed = getTimeMillis() - sampling_msec;
            start_time += elapsed;
        }
    }

    cur_msec = getTimeMillis() - start_time;

    if (do_sampling) {
        fclose(fpt6);
    }
    printf("\n Generations finished, now reporting solutions");
    report_pop(parent_pop,fpt2);
    report_feasible(parent_pop,fpt3);
    report_pareto_front(parent_pop, fpt0, cur_msec, curgen);
    if (nreal!=0)
    {
        fprintf(fpt5,"\n Number of crossover of real variable = %d",nrealcross);
        fprintf(fpt5,"\n Number of mutation of real variable = %d",nrealmut);
    }
    if (nbin!=0)
    {
        fprintf(fpt5,"\n Number of crossover of binary variable = %d",nbincross);
        fprintf(fpt5,"\n Number of mutation of binary variable = %d",nbinmut);
    }
    fprintf(fpt5,"\n");
    fprintf(fpt5,"\n Total time = %lld ms.",getTimeMillis() - total_time);
    fprintf(fpt5,"\n Exec time  = %lld ms.",getTimeMillis() - start_time);
    fprintf(fpt5,"\n Iterations = %lld",curgen);

    fflush(stdout);
    fflush(fpt0);
    fflush(fpt1);
    fflush(fpt2);
    fflush(fpt3);
    fflush(fpt4);
    fflush(fpt5);
    fclose(fpt0);
    fclose(fpt1);
    fclose(fpt2);
    fclose(fpt3);
    fclose(fpt4);
    fclose(fpt5);
    if (choice!=0)
    {
        pclose(gp);
    }
    if (nreal!=0)
    {
        free (min_realvar);
        free (max_realvar);
    }
    if (nbin!=0)
    {
        free (min_binvar);
        free (max_binvar);
        free (nbits);
    }
    deallocate_memory_pop (parent_pop, popsize);
    deallocate_memory_pop (child_pop, popsize);
    deallocate_memory_pop (mixed_pop, 2*popsize);
    free (parent_pop);
    free (child_pop);
    free (mixed_pop);
    printf("\n Routine successfully exited \n");
    return (0);
}

int stop(int criteria,
	 long long iter_msec,
	 long long n_msec,
	 long long curgen,
	 long long ngen,
	 long long cycles)
{
  if ((criteria == 1 && iter_msec >= n_msec) ||
      (criteria == 0 && curgen < ngen * cycles))
    return 1;

  return 0;
}

long long getTimeMillis()
{
    long long seconds, miliseconds;
    struct timeval tv;

    if (gettimeofday(&tv, NULL) == -1)
    {
        fprintf(stderr, "%s(): %s", __func__, "Error al obtener el tiempo.");
        exit(EXIT_FAILURE);
    }

    /* Guardamos los tiempos en long long int */
    seconds = tv.tv_sec;
    miliseconds = tv.tv_usec;

    /* Convertimos los tiempos a milisegundos */
    seconds = seconds * 1000;
    miliseconds = miliseconds / 1000;

    /* Retornamos el resultado */
    return (seconds + miliseconds);
}
