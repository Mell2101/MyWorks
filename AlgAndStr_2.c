#include<stdio.h>
#include<math.h>
int Check(int x)
{
    for(int i=2;pow(i,2)<=x;i++)
    {
        if(x%i==0)
        {
            return 0;
        }
        return 1;
    }

}

int CheckTwo(int y)
{
    if(y==1)
    {
        return 0 ;
    }
    for(int i=2;i<y;i++)
    {
        if(y%i==0)
        {
          return 0;
        }
    }
    return 1;
}



 void main()
 {

    printf(Check(5698) ? "simpl\n" : "not simpl\n");
    printf("--------------\n");
    printf(CheckTwo(2) ? "simpl Two check" : "not simpl Two check");

 }


