#include <stdio.h>
#include <stdlib.h>

int step(int x,int y)
{
    if(x==0 && y==0)
    {
        return 0;
    }
    else if(x==0 ^ y==0)
    {
        return 1;
    }
    else
    {
        return step(x,y-1)+step(x-1,y);
    }
}

int game()
{
        const int sizeX=8;
        const int sizeY=8;
        for(int y = 0; y < sizeY; ++y)
        {
            for(int x=0;x<sizeX;++x)
            {
                printf("%8d",step(x,y));
            }
            printf("\n");
        }
        return 0;
}

void mission1()
{
    int a,i, mass[99];
   for(i=0;i<99;i++)
   {
       mass[i]=0;
   }
   printf("enter number:\n");
   scanf_s("%d",&a);
   i=0;
   while(a!=0)
   {
       if(a%2==0)
       {
           mass[i]=0;
           a=a/2;
       }
       else
        {
           mass[i]=1;
           a=a/2;
        }
       i++;
   }
   i=i-1;
   for(;i>=0;i--)
   {
       printf("%d",mass[i]);
   }
       printf("\n");
       return 0;

}

double mission2(double  a, long b)
{

    if(b==0)
    {
        return 1;
    }
    if(b<0)
    {
        return mission2(1/a,b-1);
    }
    if(b%2)
    {
        return a*mission2(a,b-1);
    }
    return mission2(a*a,b/2);

}

double fun()
{
    double a;
    long b;
        printf("Enter two numbers:\n");
   while (scanf ("%lf %ld", &a, &b) == 2)
     {
        printf("Your answer:\n");
        printf("%lf\n", mission2 (a, b));
        return 0;
     }

}

double mission3(double x,long n)
{
    if(n==0) return 1;
    if(n<0) return mission3(1/x,-n);
    return x*mission3(x,n-1);

}

void fun1()
{
    double x;
    long n;
    printf("Enter two number\n");
    while(scanf("%lf %ld",&x,&n)==2)
    {
        printf("Your answer:\n");
        printf("%lf\n",mission3(x,n));
        return 0;

    }

}



int main()
{
    printf("Mission 1\n");
    mission1();
    printf("----------------\n");
    printf("Mission 2.1\n");
    fun1();
    printf("----------------\n");
    printf("mission 2.2\n");
    fun();
    printf("----------------\n");
    printf("mission 3\n");
    game();
    printf(".......\n");
    return 0;

}







