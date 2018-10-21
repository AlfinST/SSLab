#include<stdio.h>
int main()
{
 int i,j,sum=0,n;
 int d[20];
 int disk;   //loc of head
 int temp,max;     
 int Range;
 int dloc;   //loc of disk in array
 printf("Enter Range\t");
  scanf( "%d",&Range);
  printf("enter number of location\t");
 scanf("%d",&n);
 printf("enter position of head\t");
 scanf("%d",&disk);
 printf("enter elements of disk queue\n");
 for(i=0;i<n;i++)
 {
 scanf("%d",&d[i]);
 }
 d[n]=disk;
 n=n+1;
 for(i=0;i<n;i++)    // sorting disk locations
 {
  for(j=i;j<n;j++)
  {
    if(d[i]>d[j])
    {
    temp=d[i];
    d[i]=d[j];
    d[j]=temp;
    }
  }
 }
 max=d[n];
 for(i=0;i<n;i++)   // to find loc of disc in array
 {
 if(disk==d[i]) { dloc=i; break;  }
 }
 /////////////////////Movement////////////////////////////
if ((d[dloc] - d[dloc -1]) < (d[dloc+ 1] - d[dloc]) ) // it goes left 
{   
  printf("It goes left\n");
  for(i=dloc;i>=0;i--)
    {
        printf("%d -->",d[i]);
    }
  printf("0 -->");
  for(i=dloc+1;i<n;i++)
  {
    printf("%d-->",d[i]);
  }
  printf("stop\n");
  printf("head ::%d\n",disk);
  sum=2*(Range-d[dloc])+ d[0];
}
else                                                // goes right
{
    printf("It goes right\n");
  for(i=dloc;i<n;i++)
  {
    printf("%d-->",d[i]);
  }
  printf("100-->");
  for(i=dloc-1;i>=0;i--)
    {
        printf("%d -->",d[i]);
    }
    printf("stop\n");

  printf("head ::%d\n",disk);

  sum=2*(Range)-d[dloc]-d[0];
}
 printf("\nmovement of total cylinders %d\n",sum);
 printf("Avg movements =%f\n",sum/(n-1.0) );
 return 0;
}