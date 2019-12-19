#include<stdio.h>
#include<math.h>

double f1(double t,double x,double y,double v,double s);
double f2(double t,double x,double y,double v,double s);
double f3(double t,double x,double y,double v,double s);
double f4(double t,double x,double y,double v,double s);

int fopen_s();

int main(){
  int tmax;
  double k1[4],k2[4],k3[4],k4[4];

  double x,y,v,s,t,dt;

  x=0.01;
  y=-0.01;
  v=0.0;
  s=0.0;
  dt=0.01;

  tmax=5000;

  FILE *orbit;
  orbit = fopen("orbit.txt","w");

  for(t=0;t<tmax;t+=dt){

k1[0]=dt*f1(t,x,y,v,s);
k1[1]=dt*f2(t,x,y,v,s);
k1[2]=dt*f3(t,x,y,v,s);
k1[3]=dt*f4(t,x,y,v,s);


k2[0]=dt*f1(t+dt/2.0,x+k1[0]/2.0,y+k1[1]/2.0,v+k1[2]/2.0,s+k1[3]/2.0);
k2[1]=dt*f2(t+dt/2.0,x+k1[0]/2.0,y+k1[1]/2.0,v+k1[2]/2.0,s+k1[3]/2.0);
k2[2]=dt*f3(t+dt/2.0,x+k1[0]/2.0,y+k1[1]/2.0,v+k1[2]/2.0,s+k1[3]/2.0);
k2[3]=dt*f4(t+dt/2.0,x+k1[0]/2.0,y+k1[1]/2.0,v+k1[2]/2.0,s+k1[3]/2.0);

k3[0]=dt*f1(t+dt/2.0,x+k2[0]/2.0,y+k2[1]/2.0,v+k2[2]/2.0,s+k2[3]/2.0);
k3[1]=dt*f2(t+dt/2.0,x+k2[0]/2.0,y+k2[1]/2.0,v+k2[2]/2.0,s+k2[3]/2.0);
k3[2]=dt*f3(t+dt/2.0,x+k2[0]/2.0,y+k2[1]/2.0,v+k2[2]/2.0,s+k2[3]/2.0);
k3[3]=dt*f4(t+dt/2.0,x+k2[0]/2.0,y+k2[1]/2.0,v+k2[2]/2.0,s+k2[3]/2.0);

k4[0]=dt*f1(t+dt,x+k3[0],y+k3[1],v+k3[2],s+k3[3]);
k4[1]=dt*f2(t+dt,x+k3[0],y+k3[1],v+k3[2],s+k3[3]);
k4[2]=dt*f3(t+dt,x+k3[0],y+k3[1],v+k3[2],s+k3[3]);
k4[3]=dt*f4(t+dt,x+k3[0],y+k3[1],v+k3[2],s+k3[3]);


x+=(k1[0]+2.0*k2[0]+2.0*k3[0]+k4[0])/6;
y+=(k1[1]+2.0*k2[1]+2.0*k3[1]+k4[1])/6;
v+=(k1[2]+2.0*k2[2]+2.0*k3[2]+k4[2])/6;
s+=(k1[3]+2.0*k2[3]+2.0*k3[3]+k4[3])/6;

fprintf(&*orbit,"%f %f %f %f %f\n",t,x,y,v,s);
}

fclose(&*orbit);
return 0;
}

double f1(double t,double x,double y,double v,double s)
{

return(v);
}

double f2(double t,double x,double y,double v,double s)
{
  return(s);
}

double f3(double t,double x,double y,double v,double s)
{
  double mp, q, Q, L, k;

  mp=0.00000000000000000000000000000091;
  q=0.00000000000000000016;
  Q=1.0;
  L=0.1;
  k=9000000000.0;

 double a,b,c;

 a=k*q*q/mp;
 b=k*q*Q/mp;
 c=pow(L*L+x*x,1.5);

 double Fp;


 Fp=-a*(2*x/c)+b/((x-y)*(x-y));

 return(Fp);
}

double f4(double t,double x,double y,double v,double s)

{

 double mq,q, Q, L, k;

  mq=0.00000000000000000000000000000091;
  q=0.00000000000000000016;
  Q=1.0;
  L=0.1;
  k=9000000000.0;

 double e,f,g;

 e=k*q*q/mq;
 f=k*q*Q/mq;
 g=pow(L*L+y*y,1.5);

 double Fq;

 Fq=e*(2*y/g)-f/((x-y)*(x-y));

 return(Fq);
}
