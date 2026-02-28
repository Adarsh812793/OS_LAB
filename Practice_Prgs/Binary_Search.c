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
    int lb=0,hb=n;
    int mid=(lb+hb)/2;
    while(lb<=hb)
    {
        if(arr[mid]==key)
        {
            printf("Element found at position %d",mid+1);
            exit(0);
        }
        else if(key>arr[mid])
            lb=mid+1;
        else
            hb=mid-1;
        mid=(lb+hb)/2;
    }
    printf("Element not found");
}
