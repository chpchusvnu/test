#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

float *teta,*p;
//float *anpha;
int **rating_train,**rating_test,*matrix;
int **rating;
int nm;
int r;
int N;
int C;
float **input;
float avg [10000];
double *anpha;
int Ntest[10000][10000];
int NU,ni;
int weight_user[1000];
int ** d_user;
int *new_user;
float U[10000][10000];
int cluster[1000][1000];
int new_movie[2000];
int V[100][100];
int item,sum_Rate;
float H;
int R[10000][10000];
int Rtest[10000][10000];
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
void data_info(){
	FILE *f;
	f=fopen("info.txt","r");
	if(!f){
		printf("Khong tim duoc tep");
		exit(0);
	}
	char *str=(char*)malloc(100*sizeof(char));
	int i,j;
	fscanf(f,"%d",&N);
	
	//printf("%d",N);
	
	fflush(stdin);
	fgets(str,100,f);
	fflush(stdin);
	fscanf(f,"%d",&item);
	fflush(stdin);
	fgets(str,100,f);
	rating=(int**)malloc(N*sizeof(int*));
	for(i=1;i<=N;i++)
		rating[i]=(int*)malloc(item*sizeof(int));
	for(i=1;i<=N;i++)
		for(j=1;j<=item;j++)
			rating[i][j]=0;
	fclose(f);
}
void data_rating(){
	
	FILE *f;
	f=fopen("rating.txt","r");
	if(!f){
		printf("Khong tim duoc tep");
		exit(0);
	}
	
	int i,j,w;
	int x;
		
	while(!feof(f)){
		fscanf(f,"%d%d%d",&i,&j,&w);
		
		rating[i][j] = w;
		
		fscanf(f,"%d",&x);
	}
	
	fclose(f);
}	
void data_user(){
	FILE *f;
	f=fopen("user.txt","r");
	if(!f){
		printf("Khong tim duoc tep");
		exit(0);
	}
	
	d_user=(int**)malloc(N*10* sizeof(int*));
	int i,j;
	for(i = 1;i <= N;i++)
		d_user[i]=(int*)malloc(4*10*sizeof(int));
		
	for(i = 1;i <= N;i++){
		for(j = 1;j <= 4;j++){
			d_user[i][j] = 0;
		}
	}
	char *a = (char *)malloc(100*5*sizeof(char));        
	char **b = (char **)malloc(100*5*sizeof(char));
	char *p;
	int count1,count2;
	count1=0;
	while(fgets(a,100,f)!= NULL){
		p = strtok(a, "|");
		int index = 0; 
		
		count1++;
		count2=0;
		    
		while(p != NULL){        
	    	b[index] = p;    
			index++;               
			p = strtok(NULL, "|");       
		}
		r = index - 2;
		count2++;
		d_user[count1][count2]=atoi(b[0]);
		count2++;
		d_user[count1][count2] = atoi(b[1]);
		if(strcmp(b[2],"M") == 0) {
			count2++;
	
			d_user[count1][count2]=1;
		}
		if(strcmp(b[2],"F")==0){
			count2++;
		
			d_user[count1][count2]=0;
		}
		
		if(strcmp(b[3],"administrator")==0){
			count2 ++;
			d_user[count1][count2]=0;
		} 
		if(strcmp(b[3],"artist") == 0){
			count2++;
			d_user[count1][count2] = 1;
		} 
		if(strcmp(b[3],"doctor") == 0){
			count2++;
		
			d_user[count1][count2]=2;
		} 
		if(strcmp(b[3],"educator")==0){
			count2++;
		
			d_user[count1][count2]=3;
		} 
		if(strcmp(b[3],"engineer")==0){
			count2++;
		
			d_user[count1][count2]=4;
		} 
		if(strcmp(b[3],"entertainment")==0){
			count2++;
		
			d_user[count1][count2]=5;
		} 
		if(strcmp(b[3],"executive")==0){
			count2++;
		
			d_user[count1][count2]=6;
		}
		if(strcmp(b[3],"healthcare")==0){
			count2++;
			d_user[count1][count2]=7;
		} 
		if(strcmp(b[3],"homemaker")==0){
			count2++;
			d_user[count1][count2]=8;
			//printf("?");
		} 
		if(strcmp(b[3],"lawyer")==0){
			count2++;
			d_user[count1][count2]=9;
		} 
		if(strcmp(b[3],"librarian")==0){
			count2++;
			d_user[count1][count2]=10;
		}
		if(strcmp(b[3],"marketing")==0){
		 	count2++;
			d_user[count1][count2]=11;
		} 
		if(strcmp(b[3],"none")==0){
			count2++;
			d_user[count1][count2]=12;
		} 
		if(strcmp(b[3],"other")==0){
			count2++;
			d_user[count1][count2]=13;
		}
		if(strcmp(b[3],"programmer")==0){
			count2++;
			d_user[count1][count2]=14;
		}
		if(strcmp(b[3],"retired")==0){
			count2++;
			d_user[count1][count2]=15;
		}
		if(strcmp(b[3],"salesman")==0){
			count2++;
			d_user[count1][count2]=16;
		}
		if(strcmp(b[3],"scientist")==0){
			count2++;
			d_user[count1][count2]=17;
		}
		if(strcmp(b[3],"student")==0){
			count2++;
			d_user[count1][count2]=18;
		}
		if(strcmp(b[3],"technician")==0){
			count2++;
			  d_user[count1][count2]=19;
		}
		if(strcmp(b[3],"writer")==0){
			count2++;
			d_user[count1][count2]=20;
			
		}
			
	}
	
	
}
void select_user_hidden(){
	int i,j;
	
	rating_train = (int**)malloc( N * sizeof(int*));
	for(i = 1;i <= N;i++)
		rating_train[i] = (int*)malloc(item * sizeof(int));
	rating_test = (int**) malloc(N * sizeof(int*));
	for(i = 1;i <= N;i++)
		rating_test[i]=(int*)malloc(item *sizeof(int));
	//int dem = 0;
	//int x;
	
	matrix = (int*)malloc((N/3) * sizeof(int));
	for(i = 1; i <= (N/3);i++){
		matrix[i] = i;
	}
	
	for(i = 1;i <= N;i++){
		for(j = 1;j <= item;j++){
		rating_train[i][j]=0;
		rating_test[i][j]=0;
		}
	}
	
	for(i = 1;i <= N;i++){
		for(j = 1;j <= item;j++){
			rating_train[i][j] = rating[i][j];
		}
	}
		
			
	for(i = 1;i <= (N/3); i++){
		for(j = 1;j <= item; j++)
			rating_test[matrix[i]][j] = rating[matrix[i]][j];
	}
		
			
	for(i = 1;i <=  (N/3); i++){
		for(j = 1;j <= item;j++)
			rating_train[matrix[i]][j]=0;
	}
	
	
	/*for(i = 1; i < 314 ;i++){
		printf("%d\n",matrix[i]);
	}*/

	
}

void save_train_and_test(){
	int i,j;
	FILE *f;
	f=fopen("testing.txt","w");
	if(!f){
		printf("Khong tim duoc tep");
		exit(0);
	}
	
	//printf("%d\t",N);
	for(i = 1;i <= N;i++)
		for(j = 1;j <= item;j++){
			if(rating_test[i][j]>0){
				fprintf(f,"%d ",i);
				fprintf(f,"%d ",j);
				fprintf(f,"%d\n",rating_test[i][j]);
			}
		}
	fclose(f);
	f=fopen("training.txt","w");
	if(!f){
		printf("Khong tim duoc tep");
		exit(0);
	}
	for(i = 1;i <= N;i++)
		for(j = 1;j <= item;j++){
			if(rating_train[i][j]>0){
				fprintf(f,"%d ",i);
				fprintf(f,"%d ",j);
				fprintf(f,"%d\n",rating_train[i][j]);
			}
		}
	fclose(f);
}
void center_cluster(){
	int i,j,k;
	
	/*for( i = 1; i <= C;i++){
		for(j = 1; j <= r;j++){
			V[i][j]  = 0;
		}
	}*/
	
	//C = 2;
	//int m = (N-N/3)/C;
	
	
	for(k = 1; k <= C; k ++){
		
		V[k][1] = rand()%100;
		V[k][2] = rand()%2;
		V[k][3] = rand()% 20;
	}
}
void inputMIPFGWC(int l){
	FILE *f1,*f2;
	int a,b,c,d;
	float anpha,beta,gama,eps,m,nuy,to,a1,a2,a3;
	f1 = fopen("thamso.txt","r");
	if(!f1){
		printf("Can't open file");
		exit(0);
	}
	char str1[100],*p1;
	fgets (str1,100,f1);
	do
    {
         p1 = splitspace(str1);
         
    }
    while(!strstr(p1,"C"));
    C = atoi(split(p1,'=')); 
    fgets (str1,100,f1);
	do
    {
         p1 = splitspace(str1);
    }
    while(!strstr(p1,"a"));
    
    a = atoi(split(p1,'='));
    //printf("a = %d\n",a);
    fgets (str1,100,f1);
	// nhap b
	do
    {
    	//system("MIP-FGWC.exe");
         p1 = splitspace(str1);
    }
    while(!strstr(p1,"b"));
    
    b = atoi(split(p1,'='));
   // printf("b = %d\n",b);
    
    fgets (str1,100,f1);
	// nhap c
	do
    {
         p1 = splitspace(str1);
    }
    while(!strstr(p1,"c"));
    
    c = atoi(split(p1,'='));
    //printf("c = %d\n",c);
    fgets (str1,100,f1);
	// nhap d
	do
    {
         p1 = splitspace(str1);
    }
    while(!strstr(p1,"d"));
    
    d = atoi(split(p1,'='));
    //printf("d = %d\n",d);
    fgets (str1,100,f1);
	// nhap anpha
	do
    {
       p1 = splitspace(str1);
    }
    while(!strstr(p1,"anpha"));
    
    anpha = atof(split(p1,'='));
   // printf("anpha = %f\n",anpha);
    // nhap beta
    fgets (str1,100,f1);
	do
    {
       p1 = splitspace(str1);
    }
    while(!strstr(p1,"beta"));
    
    beta = atof(split(p1,'='));
    //printf("beta = %f\n",beta);
    // nhap gama
    fgets (str1,100,f1);
	do
    {
       p1 = splitspace(str1);
    }
    while(!strstr(p1,"gama"));
    
    gama = atof(split(p1,'='));
    //printf("gama = %f\n",gama);
    // nhap espsilon
    fgets (str1,100,f1);
	do
    {
       p1 = splitspace(str1);
    }
    while(!strstr(p1,"eps"));
    
    eps = atof(split(p1,'='));
    //printf("eps = %f\n",eps);
    // nhap m
    fgets (str1,100,f1);
	do
    {
       p1 = splitspace(str1);
    }
    while(!strstr(p1,"m"));
    
    m = atof(split(p1,'='));
    //printf("m = %f\n",m);
    // nhap nuy
    fgets (str1,100,f1);
	do
    {
       p1 = splitspace(str1);
    }
    while(!strstr(p1,"nuy"));
    
    nuy = atof(split(p1,'='));
    //printf("nuy = %f\n",nuy);
    // nhap to
    fgets (str1,100,f1);
	do
    {
       p1 = splitspace(str1);
    }
    while(!strstr(p1,"to"));
    
    to = atof(split(p1,'='));
    
    // nhap a1
    fgets (str1,100,f1);
	do
    {
       p1 = splitspace(str1);
    }
    while(!strstr(p1,"a1"));
    
    a1 = atof(split(p1,'='));
    //printf("a1 = %f\n",a1);
    // nhap a2
    fgets (str1,100,f1);
	do
    {
       p1 = splitspace(str1);
    }
    while(!strstr(p1,"a2"));
    
    a2 = atof(split(p1,'='));
    //printf("a3 = %f\n",a2);
    // nhap a3
    fgets (str1,100,f1);
	do
    {
       p1 = splitspace(str1);
    }
    while(!strstr(p1,"a3"));
    
    a3 = atof(split(p1,'='));
    //printf("a3 = %f\n",a3);
    
    fclose(f1);
	//data_user();
	//r = rindex ;
	//printf("%d\n",r);
	center_cluster();
	//FILE * f2;
	f2 = fopen("inputMIPFGWC.txt","w");
	if(!f2){
		printf("Khong mo dc tep");
		exit(0);
	}
	
	int i,j,k;
	fprintf(f2,"N=%d\n",630);
	fprintf(f2,"r=%d\n",r);
	fprintf(f2,"C=%d\n",C);
	//printf("N = %d\t",N);
	for(i = N/3+1;i <= N;i++){
		for(k = 2;k <= r+1; k++){
			if(k == r+1){
				fprintf(f2,"%d",d_user[i][k]);
			}
			else{
				fprintf(f2,"%d ",d_user[i][k]);
			}
		}
		fprintf(f2,"\n");
	}
	
	for(j = 2;j <= r + 1;j++){
		if(j == r+1){
				fprintf(f2,"%d",d_user[l][j]);
			}
			else{
				fprintf(f2,"%d ",d_user[l][j]);
			}
		//fprintf(f2,"%d ", d_user[l][j]);
	}
	
	
	fprintf(f2,"\na=%d\n",a);
	fprintf(f2,"b=%d\n",b);
	fprintf(f2,"c=%d\n",c);
	fprintf(f2,"d=%d\n",d);
	fprintf(f2,"anpha=%6f\n",anpha);
	fprintf(f2,"beta=%6f\n",beta);
	fprintf(f2,"gama=%6f\n",gama);
	fprintf(f2,"eps=%6f\n",eps);
	
	center_cluster();
	
	//printf("???");
	for(i = 1;i <= C;i++){
		for(j = 1; j <= r;j++){
			if(j == r){
				fprintf(f2,"%d",V[i][j]);
			}
			else{
				fprintf(f2,"%d ",V[i][j]);
			}
			
		}
		fprintf(f2,"\n");
	}
	//printf("hehehe\n");
	fprintf(f2,"m=%6f\n",m);
	fprintf(f2,"nuy=%6f\n",nuy);
	fprintf(f2,"to=%6f\n",to);
	fprintf(f2,"a1=%6f\n",a1);
	fprintf(f2,"a2=%6f\n",a2);
	fprintf(f2,"a3=%6f\n",a3);
	fprintf(f2,"1.000000 1.000000 1.000000");
	fclose(f2);	
}
void data_input(){
	FILE *f;
	f=fopen("outputMIPFGWC.txt","r");
	//printf("hoho");
	if(!f){
		printf("Can't open file");
		exit(0);
	}
	
	int i,j;
	char *str;
	float x;
	
	str=(char*)malloc(100*sizeof(char));
	fgets(str,100,f);
	//printf("hehehoho");
	N = atof(split(str,'='));
	//printf("%d\n",N);
	fgets(str,100,f);
	r = atof(split(str,'='));
	//printf("%d\n",r);
	fgets(str,100,f);
	C = atof(split(str,'='));
	//printf("%d\n",C);
	free(str);
	
	for(i = 1;i <= N*r;i++)
		fscanf(f,"%f",&x);
	
	input = (float **)malloc(N*sizeof(float*));
	for(i = 1;i <= N;i++){
		input[i]=(float*)malloc(r*sizeof(float));
		for(j = 1;j <= C;j++){	
			fscanf(f,"%f",&x);
			//printf("%f\t",x);
			input[i][j]=x;
		}
		//printf("\n");
	}
	fclose(f);
	f=fopen("output_Cluster.txt","w");
	for(i = 1;i <= N;i++){
		for(j = 1;j <= C;j++)
			fprintf(f,"%f  ",input[i][j]);
		fprintf(f,"\n");
	}
	fclose(f);		
}
void clustering(){
	
	float y;
	FILE *f;
	int cs;
	f = fopen("output_Cluster.txt","r");
	if(!f){
		printf("Can't open file");
	}
	int i,j;
	for(i = 1;i <= N;i++){
		for(j = 1; j <= C; j++){
			cluster[i][j] = 0;
		}
	}
	float max [10000];
//	max = (float*)malloc(N*5*sizeof(float));
	for(i = 1;i <= N;i++){
		max[i] =0;
	}
	for(i= 1 ;i <= N;i++){	
		for(j = 1;j <= C;j++){	
			fscanf(f,"%f",&y);
			U[i][j]=y;
		}
	}
		
	for(i = 1;i <= N;i++){
		for(j = 1;j<= C;j++){
			if(max[i] < U[i][j]){
				max[i] = U[i][j];
				cs = j;
			}
		}
		cluster[i][cs] = 1;
	}
	f=fopen("output_Cum.txt","w");
	if(!f){
		printf("Khong mo duoc tep de ghi");
		exit(0);
	}
	
	for(i = 1;i <= N;i++){
		for(j = 1;j <= C;j++)
			fprintf(f,"%d  ",cluster[i][j]);
		fprintf(f,"\n");
	}
	
	fclose(f);	
}
void rating_input(){
	FILE *f;
	f = fopen("training.txt","r");
	if(!f){
		printf("Khong tim thay tep danh gia cua nguoi dung");
	}
	 char str[100];
	 
	 int i,j,n,k,l,h,t;
	 int count = 0;
	 while(fgets(str,100,f)){
	 	count = count +1;
	 }
	 
	 n = count;
	 
	 fclose(f);
	 f = fopen("training.txt","r");
	 if(!f){
	 	printf("Khong mo duoc tep training.txt");
	 	exit(0);
	 }
	 //printf("item = %d\n",item);
	 
	 for(i = 1;i <= N;i++){
	 	//printf("???");
	 	for(j = 1;j <= item;j++){
	 		R[i][j] = 0;	
	 	}
	 }
	 for(k = 1;k <= n;k++){
	 	fscanf(f,"%d%d%d",&l,&h,&t);
	 	R[l-314][h]= t;
	 }
	 printf("%d\t",R[1][4]);
	 fclose(f);	
	 f = fopen("demo.txt","w");
	 if(!f){
	 	printf("Khong mo duoc tep");
	 	exit(0);
	 }
	 for(i = 1; i <= N; i++){
	 	for(j = 1; j <= item; j++){
	 		fprintf(f,"%d ",R[i][j]);
	 	}
	 	fprintf(f,"\n");
	 }
	 fclose(f);
}
void movie_input(){
	FILE *f;
	
	f = fopen("testing.txt","r");
	if(!f){
		printf("Khong mo duoc tep");
		exit(0);
	}
	
	char str[100];
	int i,j,k,t;
	int count1 = 0, count2 = 0;
	
	while(fgets(str,100,f)){
		count1++;
	}
	fclose(f);
	f = fopen("testing.txt","r");
	if(!f){
		printf("Khong mo duoc tep");
		exit(0);
	}
	
	while(!feof(f)){
		
		fscanf(f,"%d%d%d",&i,&j,&k);
		int dem = 0;
		for(t = 1; t <= count2; t++){
			if(j != new_movie[t]){
				dem++;
			}
		}
		if(dem==count2){
            count2++;
			new_movie[count2] = j;
		}
		nm = count2;
		
	}	
	fclose(f);
}
void new_rating(){
	FILE * f;
	f = fopen("testing.txt","r");
	if(!f){
		printf("Khong mo duoc file");
		exit(0);
	}
	int i,j;
	/**Rtest = (int **)malloc((N/3)*sizeof(int *));
	for(i = 1; i <= N/3;i++){
		Rtest[i] = (int *)malloc(item * sizeof(int *));
	}*/
	int k,h,l;
	int count = 0;
	while(!feof(f)){
		count ++;
		fscanf(f,"%d%d%d",&k,&h,&j);
		Rtest[k][h] = j;
	}
	//printf("hkhkhkhkhkhkhkhkhkhkh:%d\t",Rtest[1][1]);
	sum_Rate = count-1;
	//printf("Sum = %d",sum_Rate);
	
	fclose(f);
	f = fopen("demo2.txt","w");
	 if(!f){
	 	printf("khong mo duoc file de ghi");
	 	exit(0);
	 }
	for(i = 1;i <= 314;i++){
		for(j = 1;j <= item ;j++){
			fprintf(f,"%d ",Rtest[i][j]);
		}
		fprintf(f,"\n");
	}
	fclose(f);
	
}
void avg_item_rating(){
	int i,j;
	
//	avg =(float*)malloc( item *sizeof(float));
	for(i=1;i<=item;i++)
	   avg[i]=0;
	for(i = 1;i <= item;i++){
		int dem = 0;
		int s = 0;
		
		for(j = 1;j <= N;j++){
			if(R[j][i] > 0){
				
				s = s + R[j][i];
				//printf("%d\t",s);
				dem++;	
				//printf("%d\n",dem);
			}
		}
		if(dem!=0)
		  avg[i]=(float)s/dem;
		
	}
	//printf("hear\n");
}

double sim(int a,int b){
	int i;
	double numerator=0;
	double denominator1,denominator2;
	denominator1=0;
	denominator2=0;
	//avg_item_rating();
	for(i = 1;i <= N;i++){
		if((R[i][a]>0)&&(R[i][b]>0)){
			numerator = numerator + (double)(R[i][a]-avg[a])*(R[i][b]-avg[b]);
			denominator1 = denominator1 + (double)pow((R[i][a] - avg[a]),2);
			denominator2 = denominator2 + (double)pow((R[i][b] - avg[b]),2);		
		}
	}
	double result;
	
	if(denominator1 !=0 &&denominator2 != 0){
		result = (double)numerator/sqrt(denominator1*denominator2);
	}else{
		result =0;
	}
	return result;
}
int similar_movie(int a){
	int i;
	
	double x[2000];
	for(i = 1;i <= item;i++){
		if(i != a){
			//printf("%d\t",i);
			x[i] = sim(a,i);
			//printf("%lf\n",x[i]);	
		}else{
			x[i] = 0;
		}	
	}
	
	//printf("\nhelp");
	double max = 0;
	int cs;
	for (i = 1; i <= item; i++){
		if(max < x[i]){
			max = x[i];
			cs = i;
		}
	}
	//printf("%d\n",cs);
	return cs;
}
void similar_anpha(int k){
	
    const float pi = 3.14159;
    int count_anpha = 0;
    int count_entropy = 1;
    /*anpha = (double*)malloc(k*sizeof(double));
    teta = (float*)malloc((k/2+1) * sizeof(float));
    p = (float*)malloc((k/2+1)*sizeof(float));*/
    teta[1] = 0;p[1] = 0;
    
    while(count_anpha < k){
        count_entropy++;
        teta[count_entropy]=teta[count_entropy-1]+p[count_entropy-1]+1/(2*pi)*cos(2*pi*teta[count_entropy-1]);
        p[count_entropy]=teta[count_entropy]-teta[count_entropy-1];
        count_anpha++;
        anpha[count_anpha]=(double)fabs(p[count_entropy]);
        if(count_anpha==k)
            break;
        count_anpha++;
        anpha[count_anpha]=(double)fabs(teta[count_entropy]);
    }
    	//printf("\nyoyoyoyoyoyoyoyoyoyo\n");
    
}

void new_user2(int b){
    int i,j,k,l,h;
    //printf("%d\t",b);
    h = similar_movie(b);
    
   	//printf("h = %d\t",h);
   //printf("hear N = %d\t",cluster[630][1]);
    //weight_user = (int *)malloc(N * sizeof(int));
    for(i = 1; i <= N -1; i++){
    	weight_user[i] = 0;
    }
    for(j = 1;j <= C;j++){
    	printf(" cluster = %d",cluster[N][j]);
    	if(cluster[N][j] > 0){
    		
    		for(k = 1;k <= N - 1;k++){
				
    			if(cluster[k][j] > 0){
    				
    				if(R[k][b] > 0){
    					weight_user[k] = R[k][b];
    						
    				}else{
    					weight_user[k] = R[k][h];			
    				}	
    			}	
    		}
    		
    	}	
    }
    printf("Bo phim tuong dong nhat voi %d la: %d\n",b,h);	
}
int new_user_rating(){
	int i,j,k,t;
	int R;
	float tu_so =0;
	float mau_so = 0;
	float tich1;
	//float tich2;
	int count =0;
	//printf("hoho");
	
	for(i =1;i <= N -1;i++){
		//printf("\n%d\t",weight_user[i]);
		if(weight_user[i] > 0){
			count = count ++;	
		}
	}
	printf("count = %d\t",count);
	similar_anpha(count+1); 
	for(j = 1 ; j < count + 1; j++){
		mau_so = mau_so + anpha[j];
	}
	printf("mau_so = %f",mau_so);
	int h = 1;
	j =1;
	
	while ( (h <= N-1) && (j <= count +1)){
		if(weight_user[h] > 0){
			tu_so = tu_so + weight_user[h]*anpha[j];
			h  = h+1;
			j = j +1;
		}else{
			h = h +1;
		}
	}
	printf("Tu so la:%f\t",tu_so);
	//free(anpha);
	//printf("ok hear");
	float x;
	if(mau_so != 0){
		x = (float) tu_so/ mau_so;
	}	
	R =  round(x);
	printf("R = %d\t",R);
	return R;
	
}

void MIPFGWC_CS(){
	int i,j,k;
	/*for(i = 1; i <= 314; i++){
		for(j = 1;j <= item;j ++){
			Ntest[i][j] = 0;
		}
	}*/
	for(i = 1; i <= 314; i++){
		inputMIPFGWC(matrix[i]);
		system("MIP-FGWC-Test.exe");
		printf("ok");
		data_input();
		/*getch();
		printf("ok2");*/
		clustering();
		/*getch();
		printf("ok3");*/
		rating_input();
		/*getch();
		printf("ok4");*/
		avg_item_rating();
		/*getch();
		printf("ok5");*/
		new_rating();
		/*getch();
		printf("ok6");*/
		
		//int x;
		movie_input();
		/*getch();
		printf("ok6");
		/*for(i = 1; i <= 30; i++){
			printf("%d\t",new_movie[i]);
		}*/
		for(j = 1; j <= item; j++){
			if(Rtest[i][new_movie[j]] > 0){
				//getch();
				printf("\nj = %d\t",j);
				//g/etch();
				printf("phim = %d\t",new_movie[j]);
				//getch();
				printf("\ni = %d\t",i);
				//getch();
				//printf("hear 2");
				new_user2(new_movie[j]);
				//getch();
				//printf("hear 3");
				//x = new_user_rating();
				//getch();
				//printf("x = %d\t",x);
				Ntest[i][new_movie[j]] = new_user_rating();
				printf("\n%d\t",Ntest[i][j]);	
				printf("\nyoyoyoyoyoyoyoyoyoyo\n");
			}else{
				Ntest[i][j] = 0;
			}
		}
	}
}
void Hieu_suat(){
	int i,j;
	int count = 0;
	for(i = 1;i <= N/3; i++){
		for(j = 1;j < item;j++){
			if((Ntest[i][j] != 0)&& (Rtest[i][j] != 0)){
				if(Ntest[i][j] == Rtest[i][j]){
					count = count + 1;
				}
			}
		}
	}
	H = count / sum_Rate;
}

int main(){
	
    int i,j;
	data_info();
	
	data_user();
	data_rating();
	select_user_hidden();
	save_train_and_test();
	/*inputMIPFGWC(1);
	//printf("ok");
	data_input();
	clustering();
	rating_input();
	avg_item_rating();
	//for(i=1;i<=item;i++){
		new_user2(100);
	   new_user_rating();
	//}
	  
	/*for(i=1;i<=item;i++)
	   printf("%d\t%f\n",i,avg[i]);*/
	//printf("ok");
	//new_rating();
	//getch();
	anpha = (double*)malloc(500*sizeof(double));
    teta = (float*)malloc(500 * sizeof(float));
    p = (float*)malloc(500*sizeof(float));
	MIPFGWC_CS();
	printf("ok");
	return 0;
	

}
