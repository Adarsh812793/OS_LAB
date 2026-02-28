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
    printf("Enter the element to be searched:");
    scanf("%d",&key);
    for(int i=0;i<n;i++)
    {
        if(arr[i]==key)
        {
            printf("Element found at position %d",i+1);
            exit(0);
        }
    }
    printf("Element not found");
}