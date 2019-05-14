#include<stdio.h>
#include<stdlib.h>

void calcDetA(int xp1,int yp1,int xq1,int yq1,int xp2, int yp2, int xq2, int yq2);

double s,t,detA;
int main(){
  int N,M,P,Q,x[200],y[200],i,j,b[100],e[100],k = 0;
  double X[1000],Y[1000],EPS = 0.00000005,tmp;

  scanf("%d %d %d %d",&N,&M,&P,&Q);
  for(i = 0 ; i < N ; i++){
    scanf("%d %d",&x[i],&y[i]);
  }

  for(j = 0 ; j < M ; j++){
    scanf("%d %d",&b[j],&e[j]);
  }

  for(i = 0 ; i < M ; i++){
    for(j = 0 ; j < M ; j++){
      if(i >= j)continue;
      calcDetA(x[b[i] - 1],y[b[i] - 1], x[e[i] - 1],y[e[i] - 1], x[b[j] - 1],y[b[j] - 1], x[e[j] - 1],y[e[j] - 1]);

      if(detA < -EPS || detA > EPS){
	if((s > 0.000000 && s < 1.000000) && (t > 0.000000 && t < 1.000000)){
	  
	  X[k] = (double)x[b[i] - 1] + (double)(x[e[i] - 1] - x[b[i] - 1])*(double)s;
	  Y[k] = (double)y[b[i] - 1] + (double)(y[e[i] - 1] - y[b[i] - 1])*(double)s;

	  k++;
	}
      }
    }
  }

  for(i = 0 ; i < k ; i++){
    for(j = i + 1 ; j < k ; j++){
      if(X[i] > X[j]){
	tmp = X[i];
	X[i] = X[j];
	X[j] = tmp;
      }
    }
  }

  for(i = 0 ; i < k ; i++){
    printf("x = %.5lf y = %.5lf\n",X[i],Y[i]);
  }

  return 0;

}

void calcDetA(int xp1,int yp1,int xq1,int yq1,int xp2, int yp2, int xq2, int yq2){
  detA = (xq1 - xp1)*(yp2 - yq2) + (xq2 - xp2)*(yq1 - yp1);
  //printf("detA = %lf\n",detA);
      
  s = (double)((yp2 - yq2)*(xp2 - xp1) + (xq2 - xp2)*(yp2 - yp1))/(double)detA;
  t = (double)((yp1 - yq1)*(xp2 - xp1) + (xq1 - xp1)*(yp2 - yp1))/(double)detA;
  //printf("s = %lf t = %lf\n",s,t);

}
