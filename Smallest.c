#include<stdio.h>
#include<stdlib.h>
int main()
{
    int n,arr[50],key;
    printf("Enter the number of elements:");
    scanf("%d",&n);
    printf("Enter the elements:");
    for(int i=0;i<n;i++)
        scanf("%d",&arr[i]);
    int min=arr[0];
    for(int i=1;i<n;i++)
    {
        if(arr[i]<min)
            min=arr[i];
    }
    printf("Smallest number in array: %d",min);
}