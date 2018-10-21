#include <stdio.h>

// int bt[20],p[20],n;

void fill(int bt[],int p[],int n)
{	
	int i;
    printf("\nEnter Burst Time:\n");
    for(i=0;i<n;i++)
    {
        printf("p%d:",i+1);
        scanf("%d",&bt[i]);
        p[i]=i+1;           //contains process number
    }
}

    
void fcfs(int p[],int bt[],int n)
{
	int i,j;
	float  tat[20],wt[20],avgwt,avgtat;
	wt[0]=0.0;    //waiting time for first process is 0
 
    //calculating waiting time
    for(i=1;i<n;i++)
    {
        wt[i]=0.0;
        for(j=0;j<i;j++)
            wt[i]+=bt[j];
    }
 
    printf("\nProcess\t\tBurst Time\tWaiting Time\tTurnaround Time");
 
    //calculating turnaround time
    for(i=0;i<n;i++)
    {
        tat[i]=bt[i]+wt[i];
        avgwt+=wt[i];
        avgtat+=tat[i];
        printf("\nP[%d]\t\t%d\t\t%f\t\t%f",i+1,bt[i],wt[i],tat[i]);
    }
 
    avgwt/=n;
    avgtat/=n;
    printf("\n\nAverage Waiting Time:%f",avgwt);
    printf("\nAverage Turnaround Time:%f\n",avgtat);

}

void sjf(int p[],int bt[],int n)
{
	int pos,i,j,temp,wt[20],tat[20];
	float avgwt,avgtat,total=0.0;
	for(i=0;i<n;i++)
    {
        pos=i;
        for(j=i+1;j<n;j++)
        {
            if(bt[j]<bt[pos])
                pos=j;
        }
 
        temp=bt[i];
        bt[i]=bt[pos];
        bt[pos]=temp;
 
        temp=p[i];
        p[i]=p[pos];
        p[pos]=temp;
	}
	wt[0]=0;            //waiting time for first process will be zero
 
    //calculate waiting time
    for(i=1;i<n;i++)
    {
        wt[i]=0;
        for(j=0;j<i;j++)
            wt[i]+=bt[j];
 
        total+=wt[i];
    }
 
    avgwt=total/n;      //average waiting time
    total=0;
 
    printf("\nProcess\t    Burst Time    \tWaiting Time\tTurnaround Time");
    for(i=0;i<n;i++)
    {
        tat[i]=bt[i]+wt[i];     //calculate turnaround time
        total+=tat[i];
        printf("\np%d\t\t  %d\t\t    %d\t\t\t%d",p[i],bt[i],wt[i],tat[i]);
    }
 
    avgtat=total/n;     //average turnaround time
    printf("\n\nAverage Waiting Time=%f",avgwt);
    printf("\nAverage Turnaround Time=%f\n",avgtat);
 
}

void rr(int bt[],int n)
{
  int count,j,time,remain,flag=0,time_quantum; 
  int wait_time=0,turnaround_time=0,at[20],rt[20]; 
  remain=n; 
  for(count=0;count<n;count++) 
  { 
    printf("Enter Arrival Time for Process Process Number %d :",count+1); 
    scanf("%d",&at[count]);
    rt[count]=bt[count]; 
  } 
  printf("Enter Time Quantum:\t"); 
  scanf("%d",&time_quantum); 
  printf("\n\nProcess\t|Turnaround Time|Waiting Time\n\n"); 
  for(time=0,count=0;remain!=0;) 
  { 
    if(rt[count]<=time_quantum && rt[count]>0) 
    { 
      time+=rt[count]; 
      rt[count]=0; 
      flag=1; 
    } 
    else if(rt[count]>0) 
    { 
      rt[count]-=time_quantum; 
      time+=time_quantum; 
    } 
    if(rt[count]==0 && flag==1) 
    { 
      remain--; 
      printf("P[%d]\t|\t%d\t|\t%d\n",count+1,time-at[count],time-at[count]-bt[count]); 
      wait_time+=time-at[count]-bt[count]; 
      turnaround_time+=time-at[count]; 
      flag=0; 
    } 
    if(count==n-1) 
      count=0; 
    else if(at[count+1]<=time) 
      count++; 
    else 
      count=0; 
  } 
  printf("\nAverage Waiting Time= %f\n",wait_time*1.0/n ); 
  printf("Avg Turnaround Time = %f\n",turnaround_time*1.0/n); 
  
}

void main()
{
	int i,j,n,choice;
	int bt[20],p[20];
	 printf("Enter number of process:");
   scanf("%d",&n);
	 printf("Choose Type of Scheduling:\n\n\t 1.FCFS\n\t 2.SJF\n\t 3.Round_Robin\n\nEnter Choice::");
   scanf("%d",&choice);
   switch(choice)
   {
   		case 1:	
   				fill(bt,p,n);
   				fcfs(p,bt,n);
				break;
   		case 2:	
   				fill(bt,p,n);
   				sjf(p,bt,n);
   				break;
   		case 3:
   				fill(bt,p,n);
   				rr(bt,n);
   				break;

   		default:printf("(╯°□ °）╯︵ // You Had one Job!\n");
   }    

}