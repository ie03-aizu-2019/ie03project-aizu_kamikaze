#include<stdio.h>
#include<stdlib.h>
int main(){
  int xp1,xp2,xq1,xq2,yp1,yp2,yq1,yq2,detA;
  double x,y,s,t,EPS = 0.00000005;

  //printf("input  : ");
  scanf("%d %d %d %d %d %d %d %d",&xp1,&yp1,&xq1,&yq1,&xp2,&yp2,&xq2,&yq2);

  detA = (xq1 - xp1)*(yp2 - yq2) + (xq2 - xp2)*(yq1 - yp1);
  printf("detA = %d\n",detA);

  if(detA >= -EPS && detA <= EPS){
    //printf("交差無し1\n");
    printf("NA\n");
    return 0;
  }

  s = (double)((yp2 - yq2)*(xp2 - xp1) + (xq2 - xp2)*(yp2 - yp1))/(double)detA;
  t = (double)((yp1 - yq1)*(xp2 - xp1) + (xq1 - xp1)*(yp2 - yp1))/(double)detA;

  printf("s = %lf t = %lf\n",s,t);

  if((s <= 0 || s >= 1) || (t <= 0 || t >= 1)){
    //printf("交差無し2\n");
    printf("NA\n");
    return 0;
  }

  x = (double)xp1 + (double)(xq1 - yp1)*s;
  y = (double)yp1 + (double)(yq1 - yp1)*t;

  printf("x = %lf y = %lf\n",x,y);

  return 0;

}
