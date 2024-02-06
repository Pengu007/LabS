#include <stdio.h>
#include<stdlib.h>
#include<string.h>
int main(){
	int ar[5]={4,3,7,6,5};
	int *pf = malloc(10*sizeof(int));
	int *sf = malloc(10*sizeof(int));
	int n=5-1;//length of the arrai
	
	pf[0]=ar[0]; sf[n]=ar[n];
	for(int i=1;i<5;i++){
		pf[i]=pf[i-1]+ar[i];
	}
	for(int i=n;i>0;i--){
	    sf[i-1]=sf[i]+ar[i-1];
	}
	int count =n;
	for(int x=0;x<=n;x++){
	    printf("Iteration %d\n",x+1);
    	for(int i=x;i<=n;i++){
    	    //int ved=0;
    	    int ved=ar[x];
    	    for(int j=x;j<=count;j++){
    	        printf("%d\t",ar[j]);
    	    }
    	    printf("\n");
    	    for(int j=x;j<=count;j++){
    	        printf("%d\t",ved);
    	        ved = ved+ar[j+1];
    	    }
    	    //printf("=");
    	    //printf("%d",ved);
    	    count--;
    	    printf("\n");
    	}
    	count=n;
    	printf("\n");
	}
	/*
	for(int i=0;i<5;i++){
	    printf("%d\t",pf[i]);
	}
	printf("\n");
	for(int i=0;i<5;i++){
	    printf("%d\t",sf[i]);
	}*/
}
