#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <pthread.h>
using namespace std;

//Globalizing all the required variables.
long long int n,N,element;
vector <long long int> arr;
long long int s=0,q,r,counter=0;
int flag=0;

//Mergesort function.
void* mergesort(void* tid)
{
    if(flag==0) sort(arr.begin(),arr.begin()+((n/2)));
    else sort(arr.begin()+((n/2)),arr.end());

    flag=1;
}

//Merge function.
void* merge(void* tid1)
{
    long long int l=0,r=n-1,m=(n/2)-1;
    vector <long long int> merged(r-l+1);

    long long int i=l,j=m+1,k=0;

    while(i<=m && j<=r)
    {
        if(arr[i]<arr[j])
        {
            merged[k++]=arr[i++];
        }
        else
        {
            merged[k++]=arr[j++];
        }
    }
    while(i<=m) merged[k++]=arr[i++];
    while(j<=r) merged[k++]=arr[j++];

    long long int t=l;

    for(i=0 ; i<r-l+1 ; i++)
    {
        arr[i]=merged[i];
    }
}

//Search function.
void* search(void* tid)
{
    int t=q;
    if(r>0) t+=1;

    for(long long int i=s ; i<s+t ; i++)
    {
        if(arr[i]%element==0) counter++;
    }

    s+=t;
    r--;
}

int main()
{
    cout << "Enter the size of the array : ";
    cin >> n;

    long long int i,j,k;

    for(i=0 ; i<n ; i++)
    {
        long long int a;
        cin >> a;

        arr.push_back(a);
    }

    cout << "Enter a number N : ";
    cin >> N;
    cout << "Enter the search element : ";
    cin >> element;

    q=n/N;
    r=n%N;

    pthread_t sortingthreads[2];
    pthread_t mergingthread;
    pthread_t searchingthreads[N];
    pthread_t* psortingthreads[2];
    pthread_t* pmergingthread;
    pthread_t* psearchingthreads[N];

    for(i=0 ; i<2 ; i++)
    {
        psortingthreads[i]=&sortingthreads[i];
    }
    pmergingthread=&mergingthread;
    for(i=0 ; i<N ; i++)
    {
        psearchingthreads[i]=&searchingthreads[i];
    }

    //Creating a thread for mergsorting 1st half and waiting for it to complete.
    pthread_create(psortingthreads[0],NULL,mergesort,NULL);
    pthread_join(sortingthreads[0],NULL);

    //Creating a thread for mergsorting 2nd half and waiting for it to complete.
    pthread_create(psortingthreads[1],NULL,mergesort,NULL);
    pthread_join(sortingthreads[1],NULL);

    //Creating a thread for merging sorted halves and waiting for it to complete.
    pthread_create(pmergingthread,NULL,merge,NULL);
    pthread_join(mergingthread,NULL);

    //Creating threads for N parts of the array to search for the element.
    for(i=0 ; i<N ; i++)
    {
        pthread_create(psearchingthreads[i],NULL,search,NULL);
        pthread_join(searchingthreads[i],NULL);
    }
    
    //Printing the sorted array.
    cout << "\nSorted Array : ";
    for(i=0 ; i<n ; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;

    //Printing the total number of multiples of given element.
    cout << "Total Number of multiples of " << element << " : " << counter << "\n" << endl;

    //Exiting thread.
    pthread_exit(NULL);

    return 0;
}
