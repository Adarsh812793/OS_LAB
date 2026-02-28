#include<stdio.h>
#include<stdlib.h>
int main()
{
    int n,arr[50],key,new[50];
    printf("Enter the number of elements:");
    scanf("%d",&n);
    printf("Enter the elements:");
    for(int i=0;i<n;i++)
        scanf("%d",&arr[i]);
    int dup=-1;
    for(int i=0;i<n;i++)
    {
        int num=arr[i];
        for(int j=0;j<n;j++)
        {
            if(i!=j && arr[j]==num)
            {
                dup=arr[j];
                break;
            }
        }
        if(dup!=-1)
            break;
    }
    if(dup==-1)
        printf("No duplicates found");
    else
        printf("Duplicate element: %d",dup);
}