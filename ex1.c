#include<stdio.h>
#include<stdlib.h>
int main(){
  int N,M,P,Q,x1[4],y1[4],x[4],y[4],i,j,b[2],e[2],detA;
  double X,Y,s,t,EPS = 0.00000005;

  scanf("%d %d %d %d",&N,&M,&P,&Q);
  for(i = 0 ; i < N ; i++){
    scanf("%d %d",&x1[i],&y1[i]);
  }

  for(j = 0 ; j < M ; j++){
    scanf("%d %d",&b[j],&e[j]);
  }

  i = 0;
  for(j = 0 ; j < M ; j++){
    x[b[j] - 1] = x1[i];
    y[b[j] - 1] = y1[i];
    x[e[j] - 1] = x1[i + 1];
    y[e[j] - 1] = y1[i + 1];
    i += 2;
  }

  detA = (x[1] - x[0])*(y[2] - y[3]) + (x[3] - x[2])*(y[1] - y[0]);
  //printf("detA = %d\n",detA);

  if(detA >= -EPS && detA <= EPS){
    //printf("交差無し1\n");
    printf("NA\n");
    return 0;
  }

  s = (double)((y[2] - y[3])*(x[2] - x[0]) + (x[3] - x[2])*(y[2] - y[0]))/(double)detA;
  t = (double)((y[0] - y[1])*(x[2] - x[0]) + (x[1] - x[0])*(y[2] - y[0]))/(double)detA;
  //printf("s = %lf t = %lf\n",s,t);

  if((s <= 0 || s >= 1) || (t <= 0 || t >= 1)){
    //printf("交差無し2\n");
    printf("NA\n");
    return 0;
  }

  X = (double)x[0] + (double)(x[1] - y[0])*s;
  Y = (double)y[0] + (double)(y[1] - y[0])*s;

  printf("x = %.5lf y = %.5lf\n",X,Y);

  return 0;

}
