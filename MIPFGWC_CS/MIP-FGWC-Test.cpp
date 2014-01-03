#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>
#include <math.h>
#include <string.h>

int N, r, C;
double **U, **V,**X, **UH, **W,**H,**T, **VNext, **IM, **P;
double *Gama, *A, *AH; 
int *MC, *Pop, dem,t,*SC;
double a1, a2, a3, alpha, beta, eps, m, to, nuy, a, b, c,d, check,gama;
// UH - U hieu chinh
// MC - mang lay chi so cua phan tu max
// VNext - V trong buoc tiep theo

// Khoi tao cho mang 2 chieu
double **InitArray (int N, int r)
{
      double **A;
      A = (double **)calloc(N,sizeof(double *));
      for (int i = 0 ; i < N ; i++)
          A[i] = (double *)calloc(r,sizeof(double)); 
      return A;
}

//In ma tran ra man hinh
void PrintTest(double **tg, int n, int m)
{
     int i,j;
     for (i = 0; i<n; i++)
     {
         for (j = 0; j<m; j++)
             printf ("\t%.9f",tg[i][j]);
         printf ("\n");   
     }     
     printf ("\n");  
}

// nhap du lieu
char *splitspace(char *str)
{
    char *p;
    p = str + strlen(str) - 1;
    while(*p == ' ') p--;  
    *(p+1) = 0;
    while(*p != ' ' && p != str) p--;
    if(p == str) return p;
    else *p = 0;
    return p+1;
}

char *split(char *str, char character)
{
    char *p;
    p = str + strlen(str) - 1;
    while(*p != character) p--;
    return p + 1;     
}
//
void Input()
{
    FILE *f;
    int i, j; 
	float tmp;   
    f = fopen("inputMIPFGWC.txt","r");
    int select ;
    if(!f){
         printf("Can't Open File!");
         getch();
         exit(1);
    } 
	char s[100000], *p;
	//nhap N
    fgets(s, 100, f);
    
    do
    {
         p = splitspace(s);
    }
    while(!strstr(p,"N"));
    
    N = int(atoi(split(p,'='))); 
    printf("N = %d",N);
    
    // Nhap r     
    fgets(s,100,f);         
    do
    {
       p = splitspace(s);
    }
    while(!strstr(p,"r"));
    
    r = int(atoi(split(p,'=')));
    printf("\nr = %d", r);
    
    // nhap C
    fgets(s,100,f);         
    do
    {
       p = splitspace(s);
    }
    while(!strstr(p,"C"));
    
    C = int(atoi(split(p,'='))); 
    printf("\nC= %d\n",C);
    
    //Nhap X
    X = InitArray(N, r);
    for (int i = 0 ; i < N ; i++)
    {
        fgets(s, 10000, f);
        for (j = r-1 ; j >= 0; j--)
        {
                X[i][j] =  atof(splitspace(s));  
                
        }
    }
    
    
    // Nhap m
    do
    {
           fgets(s,100,f);
           p = splitspace(s);
    }
  
    while(!strstr(p,"a"));
    
    a = atoi(split(p,'='));
    printf("\n a= %f",a); 
    
    // Nhap b
    do
    {
           fgets(s,100,f); 
           p = splitspace(s);
    }
    while(!strstr(p,"b"));
    
    b = atoi(split(p,'='));
    printf("\n b= %f", b); 
 
    // Nhap c
    do
    {
           fgets(s,100,f); 
           p = splitspace(s);
    }
    while(!strstr(p,"c"));
    
    c = atoi(split(p,'='));
    printf("\n c= %f", c); 
    
    // Nhap d
    do
    {
           fgets(s,100,f); 
           p = splitspace(s);
    }
    while(!strstr(p,"d"));
    
    d = atoi(split(p,'='));
    printf("\n d= %f", d); 
 
 
    // Nhap anpha
    fgets(s,100,f);         
    do
    {
       p = splitspace(s);
    }
    while(!strstr(p, "anpha"));
    alpha = atof(split(p,'=')); 
    printf("\nalpha= %f", alpha);
           
    // Nhap beta
    fgets(s,100,f);         
    
    do
    {
       p = splitspace(s);
    }
    while(!strstr(p,"beta"));
    
    beta = atof(split(p,'=')); 
    printf("\nbeta= %f", beta);
       
    //nhap gama
    fgets(s,100,f);         
    
    do
    {
       p = splitspace(s);
    }
    while(!strstr(p,"gama"));
    
    gama = atof(split(p,'=')); 
    printf("\ngama= %f", gama);
    
    // Nhap eps
    fgets(s,100,f);         
    
    do
    {
        p = splitspace(s);
    }
    while(!strstr(p, "eps"));
    
    eps = atof(split(p,'=')); 
    printf("\neps= %f", eps);  
 
    
    //Nhap V      
    V = InitArray(C, r);
    
    for (int i = 0 ; i < C ; i++)
    {
        fgets(s, 10000, f);
        for (j = r-1 ; j >= 0; j--)
        {
                V[i][j] =  atof(splitspace(s));  
        }
    }
    //*/
    // Nhap m
    fgets(s,100,f); 
    do
    {
       p = splitspace(s);
    }
    
    while(!strstr(p,"m"));
    
    m = atof(split(p,'=')); 
    printf("\n m= %f",m);
    
    // Nhap nuy
    fgets(s, 100, f);
    //puts(""); 
    do
    {
       p = splitspace(s);
    }
    while(!strstr(p,"nuy"));
    
    nuy = atof(split(p,'=')); 
    printf("\nnuy = %f", nuy);
    
    //Nhap to
    fgets(s, 100, f);
    do
    {
       p = splitspace(s);
    }
    while(!strstr(p,"to"));
    
    to = atof(split(p,'=')); 
    printf("\nto = %f", to);
    
    //Nhap a1
    fgets(s, 100, f);
    do
    {
       p = splitspace(s);
    }
    while(!strstr(p,"a1"));
    
    a1 = atof(split(p,'=')); 
    printf("\na1 = %f", a1);
    
    // Nhap a2
    fgets(s, 100, f);
    do
    {
       p = splitspace(s);
    }
    while(!strstr(p,"a2"));
    
    a2 = atof(split(p,'=')); 
    printf("\na2 = %f", a2);
    
    // Nhap a3
    fgets(s, 100, f);
    do
    {
       p = splitspace(s);
    }
    while(!strstr(p,"a3"));
    
    a3 = atof(split(p,'=')); 
    printf("\na3 = %f\n", a3);
    
    // nhap gama
    fgets(s, 100, f);
    Gama = (double *)calloc(C,sizeof(double));
    //puts("");
    for( i = C - 1 ; i >= 0 ; i--)
    {
         *( Gama + i) = atof(splitspace(s));
    }
}

// max mang
double maxarr(int n, int check, double *A)
{
       int i;
       double max = *(A+0), k = 0;
       for(i = 0 ;i < n ; i++)
       {
            if(*(A+i)>=max)
            {
                           max = *(A+i);
                           k = double(i);
            }
       }
       if(check == 1)
       {
            return max;// tra ve gia tri lon nhat cua mang
       }
       else if(check == 2)
       {
            return k;// tra ve vi tri lon nhat cua mang
       }
}

// min cua mang
double minarr(int n, int check, double *A)
{
       int i;
       double min = *(A+0), k = 0;
       for(i = 0 ; i < n ; i++)
       {
            if(*(A+i)<=min)
            {
                           min = *(A+i);
                           k = double(i);
            }
       }
       if(check == 1)
       {
           return min;// tra ve gia tri nho nhat cua mang
       }
       else if(check == 2)
       {
            return k;// tra ve chi so nho nhat cua mang
       }
}

// tinh 2 gia tri 2 vector tru cho nhau
double calculate(int n, double *A, double *B)
{
       int i;
       double value = 0, temp, temp_A, temp_B;
       
       double *AB;
       AB = (double *)calloc(n,sizeof(double));
       
       for(i = 0 ; i < n ; i++)
       {
             temp_A = *(A+i);
             temp_B = *(B+i);
             *(AB+i) = temp_A - temp_B;
       }
       
       for(i = 0 ; i < n; i++)
       {
             temp = *(AB+i);
             value += temp*temp;
       }
       free(AB);
       
       return value;
}

int sum4cluster(int n, int cluster, int *A)
{
    int i, k = 0;
    for(i = 0; i < n ; i++)
    {
          if(*(A+i) == cluster)
          {
                    k++;
          }
    }
    return k;
}

// khoi tao tam cum 
void init_center_cluster()
{
     int i, j, k = 0, p, q;
     int  tmp, *MB, *ME, l = N/C;//, *C;
     
     int tmp_1; 
     
     double temp, tmp_max, tmp_min;
     double  *TMP1, *TMP2;
     srand(time(NULL));
     V = InitArray(C, r);
     
     MB = (int *)calloc(C,sizeof(int));// mang chi so bat dau
     ME = (int *)calloc(C,sizeof(int));// mang chi so ket thuc
     MC = (int *)calloc(N,sizeof(int));
     TMP1 = (double *)calloc(C*r,sizeof(double));
     TMP2 = (double *)calloc(C*r,sizeof(double));
     SC = (int*) calloc(N,sizeof(int));// so phan tu trong cum
     for(i = 0 ; i < C ; i++)
     {
           *(SC + i) = l;
           *(MB+i) = l*i;
           *(ME+i) = (l*(i+1))-1;
     }
     
     *(ME+C-1) = N-1; 
     *(SC + C-1) = N - l*(C-1);
     
     for(k = 0 ; k < C ; k++ )
     {
           for(j = 0 ; j < r ; j++)
           {
                 p = 0;
                 for( i = *(MB+k); i<=*(ME+k); i++)
                 {
                      if(k != C-1)
                      {
                           *(TMP1 + p) = X[i][j];
                           *(MC + i) = k;
                      }
                      else
                      {
                          *(TMP2 + p) = X[i][j];
                          *(MC + i) = k;
                      } 
                      p++;
                 }
                 if(k != C-1)
                 {
                      tmp_max = maxarr(*(SC+k), 1, TMP1); 
                      tmp_min = minarr(*(SC+k), 1, TMP1);
                      tmp_max = tmp_max-tmp_min;
                      if (tmp_max!=0)
                      {
                         tmp = rand()%(long)(tmp_max +1)+long(tmp_min);
                         tmp_1 = rand()%10000;
                         V[k][j] = (float)(tmp) + float(tmp_1)/1000000;
                      }
                      
                 }
                 else
                 {
                     tmp_max = maxarr(*(SC+k), 1, TMP2); 
                     tmp_min = minarr(*(SC+k), 1, TMP2);
                     tmp_max = tmp_max-tmp_min;
                      if (tmp_max!=0)
                      {
                         
                         tmp = rand()%(long)(tmp_max+1) + long(tmp_min);
                         tmp_1 = rand()%10000;
                         V[k][j] = (float)(tmp) + (float)(tmp_1)/1000000;
                      }
                      
                 }
           }
     }
     
     fflush(stdin);
     /*
     printf("\n\n______________V init_____________\n");
     for(i = 0 ; i < C ; i++)
     {
          puts("");
          for(j = 0 ; j < r ; j++)
          {
                             printf("%f ",V[i][j]);
          }
     }
     puts("");
     */
     free(MB);free(ME);
     free(TMP1);free(TMP2);
     //free(C);
}

void MIPFGWC()
{
     int i,j,k,p,dd, *Tempdd,dd1,dd2;
     double d, tmp_sum_u;
     int tmp_j, tmp_k;
     double tmp_u, tmp,tmp_h,tmp_w;
     double **XV, **Upr;
     double sum_1, sum_2, sum_3, temp, max_A;
     double *TEMP_X,*TEMP_V, *TMP_Vk, *TMP_Vp,*MRU1, *MRU2, *TMP, *TMP_Pr;
     double **TMP_VV, *SUM4V, **TMP_VN;
     double  *TMP_VNext, *D, temp1,temp2,temp3, *hs1, *hs2, *hs3,max;
     D = (double *)calloc(C,sizeof(double));
     
     SUM4V = (double *)calloc(C,sizeof(double));
     TEMP_X  = (double *)calloc(r,sizeof(double));
     TEMP_V  = (double *)calloc(r,sizeof(double));
     TMP_Vk = (double *)calloc(r,sizeof(double));// V[i]
     TMP_Vp = (double *)calloc(r,sizeof(double));// V[p]
     TMP = (double *)calloc(C,sizeof(double));
     TMP_Pr = (double *)calloc(C,sizeof(double));
     MRU1 = (double *)calloc(N,sizeof(double));
     MRU2 = (double *)calloc(N,sizeof(double));
     Tempdd = (int *)calloc(C,sizeof(int));
     hs1 = (double*) calloc (C, sizeof(double));// he so cua U[k]
     hs2 = (double*) calloc (C, sizeof(double));
     hs3 = (double*) calloc (C, sizeof(double));
     //SC = (int *)calloc(1000000,sizeof(int));
     A = (double *)calloc(N,sizeof(double));
     AH = (double *)calloc(N,sizeof(double));
     TMP_VV = InitArray(N, C);
     TMP_VN = InitArray(C, r);
     
     //A = InitArray(N,C);
     XV = InitArray(N,C);
     T = InitArray(N, C);
     U = InitArray(N, C);
     H = InitArray(N, C);
     W = InitArray(C, C);
     UH = InitArray(N, C);
     VNext = InitArray(C, r);
     Upr = InitArray(N, C);
     P = InitArray(C,C);
     
     check = 100000;
     dem = 0;
     while (check>=eps)
     {
           // ______Tinh X*V______________
           for ( k = 0 ; k < C ; k++)
           {
              for ( i = 0 ; i < N ; i++)
              {
                   for (j = 0; j < r ; j++)
                   {
                              *(TEMP_X + j) = X[i][j];
                              *(TEMP_V + j) = V[k][j];
                   }
                   
                   tmp = calculate(r,TEMP_X,TEMP_V);
                   XV[i][k]  = tmp;
                   
                   
                   //_________Tinh T_________________
                   T[i][k] = 1/(1+ (pow((a2*pow(tmp,2)),double(1/(nuy-1)))/(*(Gama+k))));
              }
           }
           //PrintTest(T,N,C);
           //_________________Tinh ma tran U____________
           fflush(stdin);
           for ( k = 0 ; k < C ; k++)
           {
		  	  //puts("\n");
              for(i = 0; i < N ; i++)
              {
                   tmp_u = 0;
                   for( p = 0 ; p < C ; p++)
                   {
                        tmp_u += XV[i][k]/XV[i][p];
                   }
                   
                   U[i][k] = 1/pow(tmp_u,double(2/(m-1)));
                   
              }
           }
           //PrintTest(U,N,C);
           
           //________Tinh Ma Tran H __________
           fflush(stdin);
           for( k = 0 ; k < C ; k++)
           {
              for(i = 0; i < N ; i++)
              {
                   tmp_h = 0;
                   for( p = 0 ; p < C ; p++)
                   {
                        tmp_h += XV[i][k]/XV[i][p];
                   }
                   H[i][k] = 1/pow(tmp_h,double(2/(to-1)));
              }
           }
           //PrintTest(H,N,C);
           
           //------------Tim gia tri do thuoc lon nhat va vi tri cua no
           fflush(stdin);
           for ( i = 0 ; i < N ; i++)
           {    
                MC[i]=0;
                for (k = 0 ; k < C ; k++)
                {
                   *(TMP + k) = U[i][k];
                   *(TMP_Pr + k) = Upr[i][k];// Upr - ma tran do thuoc cua buoc trc
                }
              
                *(MC + i) = int(maxarr(C, 2, TMP));
                //printf (" mc = %d",MC[i]);
                *(MRU1 + i) = maxarr(C, 1, TMP); //MRU1 - cac max cua tung hang U
                *(MRU2 + i) = maxarr(C, 1, TMP_Pr); //MRU2 - cac max cua tung hang Upr
                //*/
           }
           //______________Tinh Pop_________________
         
           fflush(stdin);
           for (k = 0; k < C ; k++)
           {
               *(Pop + k) = sum4cluster(N, k, MC);//Tinh Pop[k];
               //printf("Pop[%d] = %d\n",k,Pop[k]);
           }
           
           // ----------------tinh IM
           double **TMP_IM,*TEMP1_IM, *TEMP2_IM;
           int *mark1, *mark2;
           mark1 = (int*) calloc (C,sizeof(int));
           mark2 = (int*) calloc (C,sizeof(int));
           IM = InitArray(C,C);
           int dd;
         
           fflush(stdin);
         
           for (i = 0; i < N; i++)
           {
               dd=0;
               for (j = 0; j < C; j++)
               {
                 
                   if (Upr[i][j] == 0)
                      dd++;
               }
               if (dd==C)
                  break;
           }
           if (dd==C)
           {
              for (i = 0; i < C; i++)
              {
                  for (j = 0; j < C; j ++)
                      IM[i][j] = 1;    
              }
            
            }
            else
            {
             
                for (i = 0; i < N; i++)
                {
                    for (j = 0; j < C; j++)
                    {
                        mark1[j] = 0;
                        mark2[j] = 0;
                    }
                    for (j = 0; j < C; j++)
                    {
                        if (U[i][j] == MRU1[i])
                           mark1[j] = 1;
                        if (Upr[i][j] == MRU2[i])
                           mark2[j] = 1;
                    }
               
                    
                    for (j = 0; j < C; j++)
                    {
                   
                        if (mark1[j] == 1 && mark2[j] == 0)
                        {
                           for (k = 0; k < C; k++)
                           {
                               if (mark2[k] == 1)
                               {
                                  if (k!=j)
                                  {
                                     IM[j][k]++;
                                     IM[k][j]++;
                                  }
                                  else
                                      IM[j][k] = 1;
                               }
                          
                           }   
                        }
                    
                    }
               }
            }
            for (i = 0; i < C; i++)
            {
                for (j = 0; j < C; j++)
                {
                    if (IM[i][j] == 0)
                       IM[i][j] = 1;
                }
            }
            //PrintTest(IM,C,C);
            
            for (i = 0; i < N; i ++)
                for (j = 0; j < C; j++)
                    Upr[i][j] = U[i][j];
            
            //----------Tinh ma tran P------------
            int t,h;
            double *mark, maxP;
            mark = (double*)calloc((N),sizeof(double));
            fflush(stdin);
            for (i = 0; i < C; i++)
            {
                for (j = i+1; j < C; j++)
                {
                    //r (t = j; t < C; t++)
                    //
                    for (k = 0; k < N; k++)
                        mark[k] = 0;
                    for (k = 0; k < N; k++)
                    {
                        if (pow(U[k][j]- U[k][i],2)<0.1&&(U[k][j]>0))
                        {
                           mark[k] = k;
                        }
                        
                    }
                    dd = 0;
                    for (t = 0; t < N; t++)
                        if (mark[t]>0)
                           dd++;
                        maxP = 0;
              
                    if (dd>1)
                    {
                       for (t = 0; t < N; t++)
                       {
                      
                           temp = 0;
                           for (k = t+1; k < N; k++)
                           {
                               if (mark[t] =!0 && mark[k]!=0&&mark[t] == MRU1[t])
                               {

                                  for (h = 0; h < r; h++)
                                  {
                                      temp = temp + pow(fabs(X[(int) mark[k]][h]-X[(int) mark[t]][h]),2);
                                  }
                                  if (maxP<temp)
                                     maxP = temp;
                               }
                          
                             
                          }    
                       }
                    }
                    else 
                         maxP = 1;
                    P[i][j] = maxP;
                    P[j][i] = maxP;
                    if (P[i][j] == 0)
                    {
                       P[i][j] = 1;
                       P[j][i] = 1;
                    }
              
              }
              P[i][i]=1;
          
          }
          //PrintTest(P,C,C);
          
          //___________________Tinh ma tran trong so W_________
         
         fflush(stdin);
         
         for( k = 0 ; k < C ; k++)
         {
		  	  //puts("");
              for( p = 0; p < C ; p++)
              {
                    if( k == p)
                    {
                        W[k][p] = 0;
                    }
                    else
                    {
                       for( j = 0 ; j < r ; j++)
                       {
                            *(TMP_Vk + j) = V[k][j];
                            *(TMP_Vp + j) = V[p][j];
                       }
                       tmp_w = calculate(r, TMP_Vk, TMP_Vp);
                       
                       
                       W[k][p] = (pow(*(Pop + k)*(*(Pop+p)),b)*pow(P[k][p],c)*pow(IM[k][p],d))/pow(tmp_w, a);
                    }
                    if ((W[k][p] == 0) && (k!=p))
                       W[k][p] = 1;
                    
              }
              
         }
         
          //____________Tinh U hieu chinh___________________
         
         //__________________Tinh A
         fflush(stdin);
         
         
         for (i = 0; i < N; i ++)
         {
             for (j = 0; j < C; j++)
             {
                 hs1[j] = 0;
                 hs2[j] = 0;
                 hs3[j] = 0;
             }
         
             for (j = 0; j < C; j++)
             {
                 temp1 = alpha*U[i][j]; temp2 = beta*W[j][0]; temp3 = 0;
                 for (t = 1; t < j; t++)
                 {
                     temp1 = temp1 + beta*W[j][t]*hs1[t];
                     temp2 = temp2 + beta*W[j][t]*hs2[t];
                     temp3 = temp3 + beta*W[j][t]*hs3[t];
                 }
                 for (t = j; t < C; t++)
                 {
                     temp3 = temp3 + gama*W[j][t]*U[i][t];
                 }
                 hs1[j] = temp1;
                 hs2[j] = temp2;
                 hs3[j] = temp3;
             
             }
             temp1 = 0; temp2 = 0; temp3 = 0;
             for (j = 0; j < C; j++)
             {
                 temp1 = temp1 + hs2[j]*hs3[0] + hs3[j];
                 temp2 = temp2 + hs2[j]*hs1[0] + hs1[j];
             }
         
             A[i] = temp1/(1-temp2);
             //printf("\nA[%d] = %f",i,A[i]);
         }  
         //------------Tinh U hieu chinh-----------------
         fflush(stdin);
         sum_1 = 0;
         max = fabs(A[0]);
         
         for (i = 0; i < N; i++)
         {
             
             if (fabs(max) < fabs(A[i]))
             {
                max = A[i];
             }
             //printf("\nA[%d] = %f",i,A[i]);
             sum_1 = sum_1+A[i];
          }
          
          
          sum_1 = (sum_1+max)/2;
          //printf ("\nsum = %f",(sum_1+max)/2);
          for (i = 0; i < N; i++)
          {
              temp1=0;
              for (j = 0; j < C-1; j++)
              
              {
                  temp2 = 0; temp3 = 0;
                  for (t = 0; t < j; t++)
                  {
                      temp2 = temp2 + beta*W[j][t]*UH[i][t];
                  }
                  for (t = j; t < C; t++)
                  {
                      temp3 = temp3 + gama*W[j][t]*U[i][t];
                  }
                  UH[i][j] = U[i][j]*alpha + temp2 + temp3/sum_1;
                  temp1 = temp1 + UH[i][j];
              }
              UH[i][C-1] = 1 - temp1;
              //printf ("\nU = %f",U[i][C-1]);
      
          }
          // ---------kiem tra dieu kien UH>U
          for (i = 0; i < C; i ++)
             Tempdd[i] = 0;
          for (j = 0; j < C; j ++)
          {
             dd1 = 0;
             dd2 = 0;
             for (i = 0; i < N; i++)
             {
                 if (U[i][j]>UH[i][j])
                    dd1++;
                 if (U[i][j]<UH[i][j])
                      dd2++;
             }
             if (dd1>dd2&&dd2>0)
                Tempdd[j] = 1;
             //printf ("temdd %f \n",Tempdd[j]);
          }
          dd1=0;
          for (i = 0; i < C; i++)
              if (Tempdd[i]>0)
                dd1++;
          if (dd1==C)
             break;
          // kiem tra UH tang hoan toan
          for (i = 0; i < C; i ++)
             Tempdd[i] = 0;
          for (j = 0; j < C-1; j++)
          {
             dd1=0;
             for (i = 0; i < N; i++)
             {
                 if (UH[i][j]<UH[i][j+1])
                    dd1++;
             }    
             if (dd1==N)
                Tempdd[j] = 1;
             //printf("\ndd = %f");
             
          }
          dd1=0;
          for (i = 0; i < C; i++)
              if (Tempdd[i]>0)
                 dd1++;
          if (dd1==C)
             break;
          //_______________Tính V tu ma tran U da hieu chinh_____________
         
         
         //tinh tong cua U, H, T
         double temp1, temp2;
              fflush(stdin);
         
              for (j = 0; j < C; j++)
              {
             
                  for (i = 0 ; i < r ; i++)
                  {
                      temp1 = 0;
                      temp2 = 0;
                      for (k = 0 ; k < N ; k++)
                      {
                          temp1  = temp1 + a1*pow(UH[k][j], m) + a2*pow(T[k][j], nuy) + a3*pow(H[k][j], to);
                          temp2 = temp2 + (a1*pow(UH[k][j], m) + a2*pow(T[k][j], nuy) + a3*pow(H[k][j], to))*X[k][i];
                      }
                      VNext[j][i] = temp2/temp1;
                  }
             }
         //PrintTest(V,C,r);
         //PrintTest(VNext,C,r);
         
         
         TMP_VNext = (double *)calloc(10*r,sizeof(double));
         //________________________V(t+1) - V(t)
         
         for(k = 0 ; k < C ; k++)
         {
              for(j = 0 ; j < r ; j++)
              {
                    *(TEMP_V + j) = V[k][j];
                    *(TMP_VNext + j) = VNext[k][j];
                    
              }
              
              *(D + k) = calculate(r, TMP_VNext, TEMP_V);
         }
         check = 0;
         for (i = 0; i < C; i++)
             check = check + D[i];
         if (check >= eps)
         {
            fflush(stdin);
            for (i = 0; i < N; i++)
                for (j = 0; j < C; j++)
                    U[i][j] = UH[i][j];
         }
         fflush(stdin);
         for (i = 0; i < C; i++)
             for (j = 0; j < r; j++)
                 V[i][j] = VNext[i][j];
         
         
         
         dem ++;
           
     }
}

//in vao tep
void Output()
{
     FILE *f;
     int i,j,k,p;
     double tmp_u,*TEMP_X,*TEMP_V,**XV,tmp;
     f = fopen ("outputMIPFGWC.txt","w");
     fprintf (f,"N=%d\n",N);
     fprintf (f,"r=%d\n",r);
     fprintf (f,"C=%d\n",C);
     
     XV = InitArray(N,C);
     TEMP_X = (double*) calloc (r,sizeof(double));
     TEMP_V = (double*) calloc (r,sizeof(double));
     // in ma tran X
     for (i = 0; i < N; i++)
     {
         for (j = 0; j < r; j++)
         {
             fprintf (f," %f",X[i][j]);
         }
         fprintf(f,"\n");
     }
     // In ma tran U
     for (i = 0; i < N; i++)
     {
         for (j = 0; j < C; j++)
         {
             fprintf (f," %f",U[i][j]);
         }
         fprintf(f,"\n");
     }
     
     // in ma tran V
     for (i = 0; i < C; i++)
     {
         for (j = 0; j < r; j++)
         {
             fprintf (f," %f",V[i][j]);
         }
         fprintf(f,"\n");
     }
     fprintf(f,"dem=%d\n",dem);
     fprintf(f,"t=%d\n",t);
     fclose(f);
}

int main()
{ 
    //int start;
    
    Input();
    U = InitArray(N, C);
    T = InitArray(N, C);
    H = InitArray(N, C);
    //V = InitArray(C, r);
    W = InitArray(C, C);
    UH = InitArray(N, C);
    VNext = InitArray(C, r);
    
    MC = (int *)calloc(1000000,sizeof(int));
    SC = (int *)calloc(1000000,sizeof(int));
    Pop = (int *)calloc(1000000,sizeof(int));
    //A = (double *)calloc(N,sizeof(double));
    
    //init_center_cluster();
    PrintTest(V,C,r);
    t = clock();
    
    MIPFGWC();
    ///PrintTest(U,N,C);
    //PrintTest(X,N,r);
    t =  clock() - t;
    printf("\n thoi gian thuc hien la %d",t);
    Output();
    printf ("\n So buoc lap = %d",dem);
    free(A);
    free(V);
    free(X);
    free(H);
    free(T);
    free(U);
    free(W);
    free(UH);
    free(VNext);
    free(Pop);
    free(MC);
    free(SC);
    //getch();
    return 0;    
}
