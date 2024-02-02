#include<conio.h>
void main()
{
    int n,i,j,temp;
    float avwt=0.0,avtat=0.0;
    printf("Enter the number of processes: ");
    scanf("%d",&n);
    int bt[n],p[n],wt[n],tat[n];
    for(i=0;i<n;i++)
    {
        printf("Enter the burst time of process %d: ",i+1);
        scanf("%d",&bt[i]);
        p[i]=i+1;
    }
    //sorting burst time in ascending order using selection sort
    for(i=0;i<n-1;i++)
    {
        for(j=i+1;j<n;j++)
        {
            if(bt[i]>bt[j])
            {
                temp=bt[i];
                bt[i]=bt[j];
                bt[j]=temp;
                temp=p[i];
                p[i]=p[j];
                p[j]=temp;
            }
        }
    }
    wt[0]=0;
    for(i=1;i<n;i++)
    {
        wt[i]=0;
        for(j=0;j<i;j++)
        {
            wt[i]+=bt[j];
        }
        avwt+=wt[i];
    }
    avwt/=n;
    for(i=0;i<n;i++)
    {
        tat[i]=bt[i]+wt[i];
        avtat+=tat[i];
    }
    avtat/=n;
    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time");
    for(i=0;i<n;i++)
    {
        printf("\nP%d\t\t%d\t\t%d\t\t%d",p[i],bt[i],wt[i],tat[i]);
    }
    printf("\nAverage Waiting Time: %f",avwt);
    printf("\nAverage Turnaround Time: %f",avtat);
    getch();
}