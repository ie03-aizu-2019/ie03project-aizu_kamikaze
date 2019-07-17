#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

#define NMAX 1000
#define MMAX 500
#define QMAX 100
#define INF 100000000
#define WHITE 0
#define GRAY 1
#define BLACK 2

void calcDetA(int xp1,int yp1,int xq1,int yq1,int xp2, int yp2, int xq2, int yq2);
double calcDistance(double xp1,double yp1,double xq1,double yq1);
double calcCrossPoint(int point_b, int point_e);
double dijkstra(int start, int goal);


typedef struct{
  double x;
  double y;
  int row[2];
  int column[2];
  int cross;
}Point;

int N,M,P,Q,i,j,b[QMAX],e[QMAX],k = 0,K,num1,num2,num_cross,num_k;
  
  double EPS = 0.00000005,tmp,XX[NMAX],YY[NMAX],dijk;
  char S[QMAX][10],D[QMAX][10];

int count,c,m;
double cost[100] = {},used[100] = {},via[100];
double Adj[QMAX][QMAX] = {};
double s,t,detA,dest[QMAX][QMAX],dijk;
Point point[NMAX];
Point crosspoint[NMAX];

void calcDetA(int xp1,int yp1,int xq1,int yq1,int xp2, int yp2, int xq2, int yq2){
  detA = (xq1 - xp1)*(yp2 - yq2) + (xq2 - xp2)*(yq1 - yp1);
      
  s = (double)((yp2 - yq2)*(xp2 - xp1) + (xq2 - xp2)*(yp2 - yp1))/(double)detA;
  t = (double)((yp1 - yq1)*(xp2 - xp1) + (xq1 - xp1)*(yp2 - yp1))/(double)detA;

}

double calcCrossPoint(int point_b, int point_e){
  double crosspoint;
  crosspoint = (double)point_b + ((double)point_e - (double)point_b)*(double)s;
  return crosspoint;
}

void AddAdjacency(int row, int column){
  double dist;
  dist = calcDistance(point[row].x,point[row].y,point[column].x,point[column].y);
  Adj[row][column] = dist;
}

double calcDistance(double xp1,double yp1,double xq1,double yq1){
  double dist;
  double x,y;

  x = (double)(xp1 - xq1);
  y = (double)(yp1 - yq1);
  
  dist = sqrt(pow(x,2.0) + pow(y,2.0));
  return dist;
}



double dijkstra(int start,int goal){
  int i,point;
  double min;

  //printf("%d %d\n",start + 1,goal + 1);
  
  cost[start] = 0;
  while(1){
    min = INF;
    for(i = 0 ; i < N + num_k ; i++){
      if(!used[i] && min > cost[i]){
	min = cost[i];
	//printf("%d %.2lf\n",i,min);
	point = i;
	//printf("%d\n",point);
      }
    }
    if(point == goal) {
      //printf("test3 %d %lf\n",point,cost[goal]);
      return cost[goal];
    }

    for(i = 0 ; i < N + num_k ; i++){
      //printf("%lf\n",Adj[point][i]);
      //printf("%lf %lf %lf\n",cost[i],Adj[point][i],cost[point]);
      if(cost[i] > Adj[point][i] + cost[point]){
	cost[i] = Adj[point][i] + cost[point];
	via[i] = point;
	//printf("test2 %d %lf %lf %lf\n",i,Adj[point][i],cost[point],cost[i]);
      }
    }
    used[point] = 1;
  }
}

int main(){

  for(i = 0 ; i < 100 ; i++){
    for(j = 0 ; j < 100 ; j++){
      Adj[i][j] = INF;
    }
  }
  
  scanf("%d %d %d %d",&N,&M,&P,&Q);
  for(i = 0 ; i < N ; i++){
    scanf("%lf %lf",&point[i].x,&point[i].y);
  }

  for(j = 0 ; j < M ; j++){
    scanf("%d %d",&b[j],&e[j]);
    b[j] = b[j] - 1;
    e[j] = e[j] - 1;
    AddAdjacency(b[j],e[j]);
    AddAdjacency(e[j],b[j]);
    //Adj[b[j]][e[j]] = 1;
    //dist[b[j]][e[j]] = calcDistance(x[b[j] - 1],y[b[j] - 1], x[e[j] - 1],y[e[j] - 1]);
  }

  num_cross = N;
  for(i = 0 ; i < M ; i++){
    for(j = 0 ; j < M ; j++){
      if(i >= j)continue;
      calcDetA(point[b[i]].x,point[b[i]].y, point[e[i]].x,point[e[i]].y, point[b[j]].x,point[b[j]].y, point[e[j]].x,point[e[j]].y);
      
      if(detA < -EPS || detA > EPS){
	if((s > 0.000000 && s < 1.000000) && (t > 0.000000 && t < 1.000000)){
	  
	  crosspoint[k].x = calcCrossPoint(point[b[i]].x,point[e[i]].x);
	  crosspoint[k].y = calcCrossPoint(point[b[i]].y,point[e[i]].y);
	  //printf("x = %lf y = %lf\n",crosspoint[k].x,crosspoint[k].y);

	  crosspoint[num_cross].row[0] = b[i];
	  crosspoint[num_cross].column[0] = e[i];
	  crosspoint[num_cross].row[1] = b[j];
	  crosspoint[num_cross].column[1] = e[j];

	  
	  crosspoint[num_cross].cross = num_cross;

	  num_cross++;

	  //AddAdjacency(b[i],e[i]);
	  //AddAdjacency(b[j],e[j]);

	  k++;
	}
      }
    }
  }
  num_k = k;

  for(i = 0 ; i < k ; i++){
    for(j = i + 1 ; j < k ; j++){
      if(crosspoint[i].x > crosspoint[j].x){
	tmp = crosspoint[i].x;
	crosspoint[i].x = crosspoint[j].x;
	crosspoint[j].x = tmp;
	
	tmp = crosspoint[i].y;
	crosspoint[i].y = crosspoint[j].y;
	crosspoint[j].y = tmp;
      }
      else if(crosspoint[i].x == crosspoint[j].x){
	if(crosspoint[i].y > crosspoint[j].y){
	  tmp = crosspoint[i].x;
	  crosspoint[i].x = crosspoint[j].x;
	  crosspoint[j].x = tmp;
	  
	  tmp = crosspoint[i].y;
	  crosspoint[i].y = crosspoint[j].y;
	  crosspoint[j].y = tmp;
	}
      }
    }
  }

  j = 0;
  for(i = N ; i < N + k ; i++){
    point[i].x = crosspoint[j].x;
    point[i].y = crosspoint[j].y;
    j++;


    AddAdjacency(crosspoint[i].row[0],crosspoint[i].cross);
    //printf("%d %d\n",crosspoint[i].row[0],crosspoint[i].cross);
    AddAdjacency(crosspoint[i].cross,crosspoint[i].row[0]);
    AddAdjacency(crosspoint[i].column[0],crosspoint[i].cross);
    AddAdjacency(crosspoint[i].cross,crosspoint[i].column[0]);
    AddAdjacency(crosspoint[i].row[1],crosspoint[i].cross);
    AddAdjacency(crosspoint[i].cross,crosspoint[i].row[1]);
    AddAdjacency(crosspoint[i].column[1],crosspoint[i].cross);
    AddAdjacency(crosspoint[i].cross,crosspoint[i].column[1]);
  }

  /*for(i = 0 ; i < 10 ; i++){
    printf("%lf %lf\n",point[i].x,point[i].y);
    }*/

  for(i = N ; i < N + k ; i++){
    for(j = N ; j < N + k ; j++){
      if(i == j)continue;
      if((crosspoint[i].row[0] == crosspoint[j].row[0]) && (crosspoint[i].column[0] == crosspoint[j].column[0]) || (crosspoint[i].row[0] == crosspoint[j].row[1]) && (crosspoint[i].column[0] == crosspoint[j].column[1]) || (crosspoint[i].row[1] == crosspoint[j].row[0]) && (crosspoint[i].column[1] == crosspoint[j].column[0]) || (crosspoint[i].row[1] == crosspoint[j].row[1]) && (crosspoint[i].column[1] == crosspoint[j].column[1]))AddAdjacency(crosspoint[i].cross,crosspoint[j].cross);
    }
  }

  count = j;
  c = i;

  m = M;

  
  

  for(k = 0 ; k < Q ; k++){
    scanf("%s %s %d",S[k],D[k],&K);
    if(S[k][0] == 'C'){
      for(i = 0 ; i < strlen(S[k]) ; i++){
	S[k][i] = S[k][i + 1];
	//if(XX[S[k][i]] != NULL)
	num1 = N + atoi(S[k]);
	
      }
    }
    else num1 = atoi(S[k]);
    if(D[k][0] == 'C'){
      for(i = 0 ; i < strlen(D[k]) ; i++){
	D[k][i] = D[k][i + 1];
	num2 = N + atoi(D[k]);
      }
    }
    else num2 = atoi(D[k]);
    if(num1 > c || num2 > c)printf("NA\n");
    else {
      for(i = 0 ; i < 100 ; i++){
	cost[i] = INF;
	used[i] = 0;
	via[i] = -1;
	}
      dijk = dijkstra(num1 - 1,num2 - 1);
      printf("%.5lf\n",dijk);
    }
  }
  
  for(i = 0 ; i < 9 ; i++){
    for(j = 0 ; j < 9 ; j++){
      printf("%.5lf ",Adj[i][j]);
    }
    printf("\n");
  }

  
  
  return 0;
}

