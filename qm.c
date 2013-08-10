/*Quine-McCluskey Algorithm Using C*/
/*PLEASE NOTE! ----- The dashes used in the original algorithm are represented using 2's for convenience*/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
int no_var, p, no_min, no_dont;
int k;
int flag = 1;
typedef struct term
{
      int *number;           /*(p)number[0] Contains The Initial Value Of The Minterm In First Run;*/
                                 /*For The Next Run And Beyond, number[0] And Above Are Used*/
                                 /*For Denoting The Minterm Used To Create Pairs/Quads/etc*/
                               
      int *binary;               /*(no_var)Binary Representation Of The Given Minterm*/
      int ones;                  /*Denotes The Number Of 1s In The Binary Number*/
      int used;                  /*Takes Any Value If The Term Has Not Been Used And 1 If Used For Reduction*/
      
      int twos;                  /*Number of 2's in the term*/
      
}TERM;
TERM primeimp[100];              /*Assumed bound on no. of prime implicants*/
int compare(TERM *ptr1, TERM *ptr2)
{    
     if((*ptr1).twos!=(*ptr2).twos)
     return -1;
     
     if(((*ptr1).ones - (*ptr2).ones!= 1)&&((*ptr1).ones - (*ptr2).ones!= -1))
     return -1;
                                                  /*compare() Compares Two Terms, And If Reducible,*/
     int i = 0;                                   /*returns 1, else returns -1*/
     int flag = 0;                                 /*compare() and reduce() to be used together in main()*/     
     
     while(i<no_var)
     {
         if((*((*ptr1).binary + i))!=(*((*ptr2).binary + i)))
         flag++;
         
         i++;
     }
     if(flag==0||flag>1)
     return -1;
     
     if(flag==1)        /*In this if(), add a condition of setting 'used' variable for ptr1,ptr2*/
     {  (*ptr1).used = 1;
        (*ptr2).used = 1;
        return 1;
     }
}

void reduce(TERM *ptr1, TERM *ptr2, TERM *final)         /*Reduces *ptr1 & *ptr2 and returns the object*/
{                                                        /*In main(), obj.binary = malloc(no_var*sizeof(int));*/
     int i=0;                                            /*int x = pow(2, (min_term[0].twos) + 1);*/
     int j=0;                                            /*obj.number = malloc(x*sizeof(int));*/
                                                         /*Sets The Variables number and binary for obj 'final'*/
     while(i<no_var)
     {
             if((*((*ptr1).binary + i))!=(*((*ptr2).binary + i)))
            {
               for(j=0; j<i; j++)
               {
                    (*((*final).binary + j)) = (*((*ptr1).binary + j));
               }
               *((*final).binary + i) = 2;
               for(j=i+1; j<no_var; j++)
               {
                    (*((*final).binary + j)) = (*((*ptr1).binary + j));
               }
              break;     
            }
            i++;
     }
     (*ptr1).used = 1;
     (*ptr2).used = 1;
     
     int pw = pow(2, (*ptr1).twos);
     
     for(i=0;i<pw;i++)
     {
        (*((*final).number + i)) = (*((*ptr1).number + i));
     }     
     for(j=0;j<pw;j++)
     {
        (*((*final).number + i)) = (*((*ptr2).number + j));
        i++;
     }
     (*final).used=0;
}

                                            /*no_terms is the size of ob[];
                                            no_of_terms() returns the number of terms to be present
                                            in the next iteration*/
                                            
                                                                                       
int no_of_terms(TERM ob[], int no_terms)
{
  int check, i, j;
	int ctr = 0;

	for(i=0;i<no_terms;i++)
	{
		for(j=i+1; j<no_terms; j++)
		{
			check = compare(&ob[i], &ob[j]);
			
			if(check==1)
			ctr++;
		}  
		
	}
	return ctr;
}

void setOnes(TERM *ptr)
{    int i;
     int no = 0;
     for(i=0;i<no_var;i++)
     {
        if(*((*ptr).binary + i)==1)
        no++;
     }
     (*ptr).ones = no;
}

void setTwos(TERM *ptr)
{    int i;
     int no = 0;
     for(i=0;i<no_var;i++)
     {
        if(*((*ptr).binary + i)==2)
        no++;
     }
     (*ptr).twos = no;
}      
void toBinary(TERM *ptr)
{
     int x = *((*ptr).number);
     int i;
     for(i=no_var-1;i>=0;i--)
     {
         *((*ptr).binary + i) = x%2;
         x = x/2;
     }
     
}    
void print(TERM ob)   /*'a' Denotes The No. of Numbers Pointed By *number */
{    int i;
     int a = pow(2, ob.twos);
     for(i=0;i<a;i++)
     {  
        printf("%d, ", *((ob.number) + i));
     }
     printf("\t");
     
     for(i=0;i<no_var;i++)
     {
        printf("%d", *((ob.binary) + i));
     }
     printf("\n");
}

void prime(TERM temp1[], int size, int prevsize)
{	
    if(size==0)
    return;
	
	int l, i, j, x, check, run;
	
	l=0;
	
	  TERM temp[size];
	  for(i=0;i<prevsize;i++)
	  {
 		   for(j=i+1;j<prevsize;j++)
		   {
  			   check = compare(&temp1[i], &temp1[j]);
			   if(check==1)
			   {    temp[l].binary = malloc(no_var*sizeof(int));
			        x = pow(2, (temp1[i].twos) + 1);
			        temp[l].number = malloc(x*sizeof(int));
			    	reduce(&temp1[i], &temp1[j], &temp[l]);
				    setOnes(&temp[l]);
				    setTwos(&temp[l]);
				    l++;
  			    }
     		 }
  	   }
        
        flag++;
        if(size>0)
        printf("\n\nAfter %d Reductions:\n", flag);
        for(i=0;i<l;i++)
        print(temp[i]);
        
        
	    int prev = size;
	    int size2 = no_of_terms(temp, size);
	    
	    for(i=0;i<l;i++)
	    {
                        for(j=i+1;j<l;j++)
                        {
                                        check = compare(&temp[i],&temp[j]);
                                        if(check==1)
                                        {
                                                    temp[i].used = 1;
                                                    temp[j].used = 1;
                                        }
                        }
          }  
	    
	    

	    for(i=0;i<l;i++)
	    {
		 if(temp[i].used==1)            /*Storing the unused values of current reduction*/
		 continue;
		 else
  	     {   primeimp[k].binary = malloc(no_var*sizeof(int));
		     x = pow(2, (temp[i].twos) + 1);
		     primeimp[k].number = malloc(x*sizeof(int));
		  	 primeimp[k] = temp[i];
			 k++;
		  }
	   }
    
    if(size2>0)
	prime(temp, size2, prev);
	       
}

void rem_repeat(TERM *ptr1, TERM *ptr2)
{
     int i,j;
     int flag = 0;
     for(i=0;i<no_var;i++)
     {
                 if( *((*ptr1).binary + i) == *((*ptr2).binary + i) )
                 {
                     flag++;
                 }
     }
     
     if( flag==no_var )
     {
         /*Repeated Case*/
         (*ptr2).used = 1;
     }
     else
     (*ptr2).used = 0;
}                                         

main()
{     int i,j;  /*Make 'k' a global variable*/
      printf("------------------Quine-McCluskey Boolean Minimizer------------------\n");
      printf("------------------Created By Karthik Gopalakrishnan------------------\n");
      printf("\n\nPLEASE NOTE! The '-'s Used In The Algorithm Are Represented\nBy The Digit '2' For Convenience!\n");
      printf("--Input--\n");
      printf("How Many Variables?\n");
      scanf("%d", &no_var);
      
      p = pow(2,no_var);
      
      
re_enter: printf("How Many Minterms?\n");
      scanf("%d", &no_min);
      
      if(no_min<=0||no_min>p)
      {
         printf("Sorry! Illegal Number Of Minterms! Please Re-Enter!\n");
         goto re_enter;
      }
      
re_enter2:printf("How Many Don't Cares?\n");
      scanf("%d", &no_dont);
      
      if(no_dont<0||no_dont>p-no_min)
      {
          printf("Sorry! Illegal Number Of Don't Cares! Please Re-Enter!\n");
          goto re_enter2;
      }
      
               TERM min_term[no_min];
               
                /*Input Of Minterms & Calculation Of Various Entities Within The Structure*/
                printf("Enter The Minterms:\n");
                
                for(i=0; i<no_min; i++)
                {        min_term[i].number = malloc(sizeof(int));
                         min_term[i].binary = malloc(no_var*sizeof(int));
                         
                         if(min_term[i].number!=NULL&&min_term[i].binary!=NULL)
                         {
                         
                         
                start:   scanf("%d", (min_term[i].number));
                         if(*(min_term[i].number)>p-1)
                         {
                             printf("Illegal Term! Please Re-Enter!\n");
                             goto start;
                         }
                         toBinary(&min_term[i]);
                         setOnes(&min_term[i]);
                         setTwos(&min_term[i]);
                          }
                }   
      
                 TERM dont_care[no_dont];
                 
                 if(no_dont>0)
                 printf("Enter The Don't Cares:\n");
                 /*Input Of Don't Cares & Calculation Of Various Entities Within The Structure*/
                 
                 for(i=0; i<no_dont; i++)
                 {        dont_care[i].number = malloc(sizeof(int));
                          dont_care[i].binary = malloc(no_var*sizeof(int));
                          
                          if(dont_care[i].number!=NULL&&dont_care[i].binary!=NULL)
                          {
                          
                 start2:  scanf("%d", (dont_care[i].number));
                          for(j=0;j<no_min;j++)
                          {
                               if((*(min_term[j].number)==*(dont_care[i].number))||(*(dont_care[i].number)>p-1))
                               {
                                     printf("Illegal Term! Please Re-Enter!\n");
                                     goto start2;
                               }
                          toBinary(&dont_care[i]);
                          setOnes(&dont_care[i]);
                          setTwos(&dont_care[i]);
                          }
                          }
                 }
      
      printf("Minterm\tBinary\n");                   /*Initial Values Of Minterms*/
      for(i=0;i<no_min;i++)
      {
          print(min_term[i]);
      }
      if(no_dont>0)                                   /*Initial Values Of Don't Cares, If Any*/
      {          printf("Don't Care Binary\n");
                   for(i=0;i<no_dont;i++)
                   {
                       print(dont_care[i]);
                   }
      }

      /*FLAG! Initialization Of Minterms And Don't Cares Done!*/
      
      /*Start The Reduction Of Minterms*/
      int ctr=0;
      int check;
      for(i=0; i<no_min;i++)
      {        
                for(j=i+1; j<no_min; j++)
                {
                   check = compare(&min_term[i], &min_term[j]);     
                   
                   if(check==1)
                    ctr++;
                }
                for(k=0;k<no_dont;k++)
                {
                   check = compare(&min_term[i], &dont_care[k]);
                   
                   if(check==1)
                   ctr++;
                }
      }                                              
      for(k=0;k<no_dont;k++)
      {
             for(j=k+1;j<no_dont;j++)
             {
                 check = compare(&dont_care[k], &dont_care[j]);
                 
                 if(check==1)
                 ctr++;
             }
      }
                                /*At this pt, ctr holds the value of no. of terms on first red*/               
      TERM firstred[ctr];    
      
      
      /*Now actually reducing and storing in firstred*/
      ctr = 0;
      int x;
      for(i=0; i<no_min;i++)
      {        
                for(j=i+1; j<no_min; j++)
                {
                   check = compare(&min_term[i], &min_term[j]);     
                   
                   if(check==1)
                   {             
                               firstred[ctr].binary = malloc(no_var*sizeof(int));
                               x = pow(2, (min_term[i].twos) + 1);           
                               firstred[ctr].number = malloc(x*sizeof(int));
                               
                               if(firstred[ctr].binary!=NULL&&firstred[ctr].number!=NULL)
                               { reduce(&min_term[i], &min_term[j], &firstred[ctr]);
                                 setOnes(&firstred[ctr]);
                                 setTwos(&firstred[ctr]);
                                 ctr++;
                               }
                   }
                }
                for(k=0;k<no_dont;k++)
                {
                   check = compare(&min_term[i], &dont_care[k]);
                   
                   if(check==1)
                   {           
                               firstred[ctr].binary = malloc(no_var*sizeof(int));
                               x = pow(2, (min_term[i].twos) + 1);            
                               firstred[ctr].number = malloc(x*sizeof(int));
                               if(firstred[ctr].binary!=NULL&&firstred[ctr].number!=NULL)
                               { reduce(&min_term[i], &dont_care[k], &firstred[ctr]);
                                 setOnes(&firstred[ctr]);
                                 setTwos(&firstred[ctr]);
                                 ctr++;
                               }
                   }
                }
      }                                              
      for(k=0;k<no_dont;k++)
      {
             for(j=k+1;j<no_dont;j++)
             {
                 check = compare(&dont_care[k], &dont_care[j]);
                   if(check==1)
                   {                            
                               firstred[ctr].binary = malloc(no_var*sizeof(int));
                               x = pow(2, (dont_care[k].twos) + 1);              
                               firstred[ctr].number = malloc(x*sizeof(int));
                               
                               if(firstred[ctr].binary!=NULL&&firstred[ctr].number!=NULL)
                               { reduce(&dont_care[k], &dont_care[j], &firstred[ctr]);
                                 setOnes(&firstred[ctr]);
                                 setTwos(&firstred[ctr]);
                                 ctr++;
                               }
                   }
             }
      }
      
      printf("\n\nAfter 1 Reduction:\n");
      
      for(i=0;i<ctr;i++)
      print(firstred[i]);
      
      k=0;
      /*Storing The Prime Implicants From The 0th Iteration*/
      for(i=0;i<no_min;i++)
      {
                           if(min_term[i].used==1)
                           continue;
                           else
                           {   primeimp[k].binary = malloc(no_var*sizeof(int));
                               x = pow(2, (min_term[i].twos) + 1);
                               primeimp[k].number = malloc(x*sizeof(int));
                               primeimp[k] = min_term[i];
                               k++;
                           }
      }
      for(i=0;i<no_dont;i++)
      {
                            if(dont_care[i].used==1)
                            continue;
                            else
                            {
                                primeimp[k].binary = malloc(no_var*sizeof(int));
                                x = pow(2, (dont_care[i].twos) + 1);
                                primeimp[k].number = malloc(x*sizeof(int));
                                primeimp[k] = dont_care[i];
                                k++;
                            }
      }
      
      for(i=0;i<ctr;i++)
      {
                        for(j=i+1; j<ctr; j++)
                        {
                                   check = compare(&firstred[i], &firstred[j]);
                        }
      }

      for(i=0; i<ctr; i++)
      {
               if(firstred[i].used==1)
               continue;
               else                      /*Storing the unused values of firstred*/
               {
                   primeimp[k].binary = malloc(no_var*sizeof(int));
                   x = pow(2, (firstred[i].twos) + 1);
                   primeimp[k].number = malloc(x*sizeof(int));
                   primeimp[k] = firstred[i];
                   k++;
               }
      }
      

   /* TERM temp1[ctr];	/*ctr holds the value of the size of firstred at this point*/

    /* int run;
    for(run=0;run<ctr;run++)
    {   
        temp1[run].binary = malloc(no_var*sizeof(int));
        x = pow(2, (firstred[run].twos) + 1);
        temp1[run].number = malloc(x*sizeof(int));
        temp1[run] = firstred[run];
    }
*/
    int l;
    int prevsize = ctr;
    int size;
    size = no_of_terms(firstred, ctr);

    
    prime(firstred, size, prevsize);

    printf("\n\nThe Prime Implicants (Including The Repeated Ones) Are:\n");
    
    for(i=0;i<k;i++)
    {
                    print(primeimp[i]);
    }

    /*Prime Implicants Found! Now to find essential prime implicants*/
    
    for(i=0;i<k;i++)
    {
                    for(j=i+1;j<k;j++)
                    {   rem_repeat(&primeimp[i], &primeimp[j]);
                    }
    }
    
    printf("\n\nThe Unique Prime Implicants Are:\n");
    for(i=0;i<k;i++)
    {
                    if(primeimp[i].used!=1)
                    print(primeimp[i]);
    }
    
   /* printf("The Repeated Prime Implicants Are:\n");
    
    for(i=0;i<k;i++)
    {
          if(primeimp[i].used==1)
          print(primeimp[i]);
    }
    */
    system("pause");
                       
}



