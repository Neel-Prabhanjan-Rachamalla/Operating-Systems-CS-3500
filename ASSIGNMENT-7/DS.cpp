#include <bits/stdc++.h>
#include <sys/time.h>
using namespace std;

long long int N=4999;

vector <long long int> order;
long long int total=0;
double avg=0;

void FCFS(long long int init , vector <long long int> req)
{
    long long int n=req.size();
    long long int i,j,k;

    order=req;

    for(i=0 ; i<n ; i++)
    {
        if(i==0) total+=abs(req[i]-init);
        else total+=abs(req[i]-req[i-1]);
    }

    avg=(double)total/n;

    return;
}

void SSTF(long long int init , vector <long long int> req)
{
    long long int n=req.size();
    long long int i,j,k;

    while(req.size()>0)
    {
        int mini=0;

        for(j=0 ; j<req.size() ; j++)
        {
            if(abs(req[mini]-init)>abs(req[j]-init)) mini=j;
        }

        total+=(abs(req[mini]-init));
        init=req[mini];

        order.push_back(init);

        req.erase(req.begin()+mini);
    }

    avg=(double)total/n;

    return;
}

void SCAN(long long int init , vector <long long int> req , int dir)
{
    long long int n=req.size();
    long long int i,j,k;

    vector <long long int> left;
    vector <long long int> right;

    for(i=0 ; i<n ; i++)
    {
        if(req[i]<init) left.push_back(req[i]);
        else if(req[i]>init) right.push_back(req[i]);
    }

    sort(left.rbegin(),left.rend());
    sort(right.begin(),right.end());

    if(dir==1)
    {
        for(i=0 ; i<right.size() ; i++)
        {
            order.push_back(right[i]);
        }
        for(i=0 ; i<left.size() ; i++)
        {
            order.push_back(left[i]);
        }

        int l=N;
        if(left.size()!=0) l=left[left.size()-1];

        total+=(N-init)+(N-l);
    }
    else
    {
        for(i=0 ; i<right.size() ; i++)
        {
            order.push_back(left[i]);
        }
        for(i=0 ; i<left.size() ; i++)
        {
            order.push_back(right[i]);
        }

        int r=0;
        if(right.size()!=0) r=right[right.size()-1];

        total+=(init)+(r);
    }

    avg=(double)total/n;
}

void C_SCAN(long long int init , vector <long long int> req)
{
    long long int n=req.size();
    long long int i,j,k;

    vector <long long int> left;
    vector <long long int> right;

    for(i=0 ; i<n ; i++)
    {
        if(req[i]<init) left.push_back(req[i]);
        else if(req[i]>init) right.push_back(req[i]);
    }

    sort(left.begin(),left.end());
    sort(right.begin(),right.end());

    for(i=0 ; i<right.size() ; i++)
    {
        order.push_back(right[i]);
    }
    for(i=0 ; i<left.size() ; i++)
    {
        order.push_back(left[i]);
    }

    long long int l=0;
    if(left.size()!=0) l=N+left[left.size()-1];

    total+=(N-init)+l;

    avg=(double)total/n;
}

void LOOK(long long int init , vector <long long int> req , int dir)
{
    long long int n=req.size();
    long long int i,j,k;

    vector <long long int> left;
    vector <long long int> right;

    for(i=0 ; i<n ; i++)
    {
        if(req[i]<init) left.push_back(req[i]);
        else if(req[i]>init) right.push_back(req[i]);
    }

    sort(left.rbegin(),left.rend());
    sort(right.begin(),right.end());

    if(dir==1)
    {
        for(i=0 ; i<right.size() ; i++)
        {
            order.push_back(right[i]);
        }
        for(i=0 ; i<left.size() ; i++)
        {
            order.push_back(left[i]);
        }

        long long int r=init;
        if(right.size()!=0) r=right[right.size()-1];

        long long int l=r;
        if(left.size()!=0) l=left[left.size()-1];

        total+=(r-init)+(r-l);
    }
    else
    {
        for(i=0 ; i<right.size() ; i++)
        {
            order.push_back(left[i]);
        }
        for(i=0 ; i<left.size() ; i++)
        {
            order.push_back(right[i]);
        }

        long long int l=init;
        if(left.size()!=0) l=left[left.size()-1];

        long long int r=l;
        if(right.size()!=0) r=right[right.size()-1];

        total+=(init-l)+(r-l);
    }

    avg=(double)total/n;
}

void C_LOOK(long long int init , vector <long long int> req)
{
    long long int n=req.size();
    long long int i,j,k;

    vector <long long int> left;
    vector <long long int> right;

    for(i=0 ; i<n ; i++)
    {
        if(req[i]<init) left.push_back(req[i]);
        else if(req[i]>init) right.push_back(req[i]);
    }

    sort(left.begin(),left.end());
    sort(right.begin(),right.end());

    for(i=0 ; i<right.size() ; i++)
    {
        order.push_back(right[i]);
    }
    for(i=0 ; i<left.size() ; i++)
    {
        order.push_back(left[i]);
    }

    long long int r=init;
    if(right.size()!=0) r=right[right.size()-1];

    long long int l1=r;
    if(left.size()!=0) l1=left[0];

    long long int l2=l1;
    if(left.size()!=0) l2=left[left.size()-1];

    total+=(r-init)+(r-l1)+(l2-l1);

    avg=(double)total/n;
}

int main()
{
    cout << "\n                ****** DISK SCHEDULING ALGORITHMS ******" << endl;
    long long int n=1000;

    /*cout << "\nEnter the number of requests : ";
    cin >> n;*/

    vector <long long int> req(n);
    long long int i,j,k;

    //cout << "\nEnter the requests' sequence : ";
  
    struct timeval start;
    gettimeofday(&start, NULL);

    srand((unsigned) start.tv_usec);

    for (i=0 ; i<n ; i++)
    {
        req[i]=rand()%5000;
    }

    long long int ds;

    cout << "\n1 : FCFS\n2 : SSTF\n3 : SCAN\n4 : C-SCAN\n5 : LOOK\n6 : C-LOOK" << endl;
    cout << "Enter the disk scheduling algorithm : ";

    cin >> ds;

    long long int init;

    cout << "\nEnter the initial position of the head : ";

    cin >> init;

    switch(ds)
    {
        case 1 :
        {
            FCFS(init,req);

            break;
        }
        case 2 :
        {
            SSTF(init,req);

            break;
        }
        case 3 :
        {
            long long int dir;

            cout << "-1 : LEFT\n1 : RIGHT" << endl;
            cout << "Enter the direction : ";

            cin >> dir;

            SCAN(init,req,dir);

            break;
        }
        case 4 :
        {
            C_SCAN(init,req);

            break;
        }
        case 5 :
        {
            long long int dir;

            cout << "-1 : LEFT\n1 : RIGHT" << endl;
            cout << "Enter the direction : ";

            cin >> dir;

            LOOK(init,req,dir);

            break;
        }
        case 6 :
        {
            C_LOOK(init,req);

            break;
        }
    }

    cout << "\nSERVICE ORDER : ";

    for(i=0 ; i<n ; i++)
    {
        cout << order[i] << " ";
    }
    cout << endl;

    cout << "\nTOTAL SEEK OPERATIONS : " << total << endl;
    cout << "\nAVERAGE SEEK OPERATIONS PER REQUEST : " << avg << endl;
    cout << endl;

    return 0;
}