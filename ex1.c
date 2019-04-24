#include<stdio.h>
#include<stdlib.h>
int main(){
  int N,M,P,Q,x[4],y[4],i,j,b[2],e[2],detA;
  double X,Y,s,t,EPS = 0.00000005;

  scanf("%d %d %d %d",&N,&M,&P,&Q);
  for(i = 0 ; i < N ; i++){
    scanf("%d %d",&x[i],&y[i]);
  }

  for(j = 0 ; j < M ; j++){
    scanf("%d %d",&b[j],&e[j]);
  }

  for(i = 0 ; i < M ; i++){
    for(j = 0 ; j < M ; j++){
      if(i == b[j] - 1){
	tmp = x[i];
	X[i] == x[i];
      }
    }
  }
  
  //detA = (x[1] - x[b[j] - 1])*(y[2] - y[3]) + (x[3] - x[2])*(y[1] - y[b[j] - 1]);

  detA = (x[1] - x[0])*(y[2] - y[3]) + (x[3] - x[2])*(y[1] - y[0]);
  //detA = (xq1 - xp1)*(yp2 - yq2) + (xq2 - xp2)*(yq1 - yp1);
  printf("detA = %d\n",detA);

  if(detA >= -EPS && detA <= EPS){
    //printf("交差無し1\n");
    printf("NA\n");
    return 0;
  }

  s = (double)((y[2] - y[3])*(x[2] - x[0]) + (x[3] - x[2])*(y[2] - y[0]))/(double)detA;
  t = (double)((y[0] - y[1])*(x[2] - x[0]) + (x[1] - x[0])*(y[2] - y[0]))/(double)detA;

  /*s = (double)((yp2 - yq2)*(xp2 - xp1) + (xq2 - xp2)*(yp2 - yp1))/(double)detA;
    t = (double)((yp1 - yq1)*(xp2 - xp1) + (xq1 - xp1)*(yp2 - yp1))/(double)detA;*/
  //printf("s = %lf t = %lf\n",s,t);

  if((s <= 0 || s >= 1) || (t <= 0 || t >= 1)){
    //printf("交差無し2\n");
    printf("NA\n");
    return 0;
  }

  X = (double)x[0] + (double)(x[1] - y[0])*s;
  Y = (double)y[0] + (double)(y[1] - y[0])*s;

  /*x = (double)xp1 + (double)(xq1 - yp1)*s;
    y = (double)yp1 + (double)(yq1 - yp1)*s;*/
  printf("x = %.5lf y = %.5lf\n",X,Y);

  return 0;

}
