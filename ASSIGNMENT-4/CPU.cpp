#include <bits/stdc++.h>
using namespace std;

vector <int> schedule;
priority_queue <vector <int> , vector <vector <int>> , greater <vector <int>>> pq[5];
int tim=0;

class process
{
    public :

    int pid;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
    int type;
    int priority;

    process(vector <int> p)
    {
        int i,j,k;

        pid=p[0];
        at=p[1];
        bt=p[2];
        ct=-1;
        tat=-1;
        wt=-1;
        type=p[3];
        priority=p[4];
    }
};

bool comp(process* a,process* b)
{
    return a->pid>b->pid;
}


void priorityscheduling(int x)
{
    schedule.push_back((pq[x].top())[3]);

    int a=(pq[x].top())[0];
    int b=(pq[x].top())[1];
    int c=(pq[x].top())[2];
    int d=(pq[x].top())[3];

    pq[x].pop();

    if(c!=1) pq[x].push(vector <int> {a,b,c-1,d});

    return;
}

void fcfsscheduling(int x)
{
    schedule.push_back(pq[x].top()[3]);

    int a=(pq[x].top())[0];
    int b=(pq[x].top())[1];
    int c=(pq[x].top())[2];
    int d=(pq[x].top())[3];

    pq[x].pop();

    if(c!=1) pq[x].push(vector <int> {a,b,c-1,d});
 
    return;
}

void sjfscheduling(int x)
{
    schedule.push_back(pq[x].top()[2]);

    int a=(pq[x].top())[0];
    int b=(pq[x].top())[1];
    int c=(pq[x].top())[2];

    pq[x].pop();

    if(a!=1) pq[x].push(vector <int> {a-1,b,c});

    return;
}

int main()
{
    int n;
    cin >> n;

    int tslice;
    cin >> tslice;

    vector <process*> processes;
    vector <int> visited(n,0);

    int i,j,k;
    int tmax=0,maxat=0;

    for(i=0 ; i<n ; i++)
    {
        vector <int> p(5);
        for(j=0 ; j<5 ; j++)
        {
            cin >> p[j];
        }

        process* ptr=new process(p);

        tmax+=(ptr->bt);
        maxat=max(maxat,ptr->at);

        processes.push_back(ptr);
    }
    tmax+=maxat;

    vector <int> f(5,-1);
    f[0]++;

    while(tim<=tmax)
    {
        int size=schedule.size();
        int flag1=0,flag2=0;

        for(i=0 ; i<n ; i++)
        {
            if(visited[i]==0 && tim==processes[i]->at)
            {
                if(processes[i]->type==0) pq[0].push(vector <int> {processes[i]->priority,processes[i]->pid,processes[i]->bt,i});
                else if (processes[i]->type==1 || processes[i]->type==2) pq[processes[i]->type].push(vector <int> {processes[i]->at,processes[i]->pid,processes[i]->bt,i});
                else pq[processes[i]->type].push(vector <int> {processes[i]->bt,processes[i]->pid,i});

                visited[i]=1;
            }
        }

        if(pq[0].empty() && pq[1].empty() && pq[2].empty() && pq[3].empty() && pq[4].empty())
        {
            schedule.push_back(-1);
            tim++;
            f[0]=0;f[1]=-1;f[2]=-1;f[3]=-1;f[4]=-1;
            continue;
        }

        if(f[0]!=-1)
        {
            if(!pq[0].empty())
            {
                priorityscheduling(0);
                f[0]++;
                if(f[0]==tslice)
                {
                    f[0]=-1;
                    f[1]++;
                    tim++;
                    continue;
                }
            }
            else
            {
                f[0]=-1;
                f[1]++;
            }
        }
        if(f[1]!=-1)
        {
            if(!pq[1].empty())
            {
                fcfsscheduling(1);
                f[1]++;
                if(f[1]==tslice)
                {
                    f[1]=-1;
                    f[2]++;
                    tim++;
                    continue;
                }
            }
            else
            {
                f[1]=-1;
                f[2]++;
            }
        }
        if(f[2]!=-1)
        {
            if(!pq[2].empty())
            {
                fcfsscheduling(2);
                f[2]++;
                if(f[2]==tslice)
                {
                    f[2]=-1;
                    f[3]++;
                    tim++;
                    continue;
                }
            }
            else
            {
                f[2]=-1;
                f[3]++;
            }
        }
        if(f[3]!=-1)
        {
            if(!pq[3].empty())
            {
                sjfscheduling(3);
                f[3]++;
                if(f[3]==tslice)
                {
                    f[3]=-1;
                    f[4]++;
                    tim++;
                    continue;
                }
            }
            else
            {
                f[3]=-1;
                f[4]++;
            }
        }
        if(f[4]!=-1)
        {
            if(!pq[4].empty())
            {
                sjfscheduling(4);
                f[4]++;
                if(f[4]==tslice)
                {
                    f[4]=-1;
                    f[0]++;
                    tim++;
                    continue;
                }
            }
            else
            {
                f[4]=-1;
                f[0]++;
            }
        }

        if(schedule.size()!=size) tim++;
    }

    int count=0;
    for(i=schedule.size()-1 ; i>=0 ; i--)
    {
        if(schedule[i]<0) count++;
        else break; 
    }

    for(i=schedule.size()-count-1 ; i>=0 ; i--)
    {
        if(schedule[i]>=0)
        {
            if(processes[schedule[i]]->ct==-1)
            {
                processes[schedule[i]]->ct=i+1;
                processes[schedule[i]]->tat=i+1-processes[schedule[i]]->at;
                processes[schedule[i]]->wt=i+1-processes[schedule[i]]->at-processes[schedule[i]]->bt;
            }
        }
    }

    cout << "\n****************************************************" << endl;
    cout << "*******     MULTI-LEVEL QUEUE SCHEDULING     *******" << endl;
    cout << "****************************************************\n" << endl;
    cout << "               *****GANT CHART*****               " << endl;
    cout << "                    ==========                   " << endl;
    for(i=0 ; i<schedule.size()-count ; i++)
    {
        if(schedule[i]<0) cout << "**********  IDLE  **********" << setw(10) << "SLOT :" << setw(3) << i << setw(5) << "to" << setw(5) << i+1 << endl;
        else
        {
            string s;
            if(processes[schedule[i]]->type==0) s="SYS";
            if(processes[schedule[i]]->type==1) s="IPS";
            if(processes[schedule[i]]->type==2) s="IEP";
            if(processes[schedule[i]]->type==3) s="BPS";
            if(processes[schedule[i]]->type==4) s="SPS";
            cout << "Process ID :" << setw(3) << processes[schedule[i]]->pid << setw(10) << "Type : " << s << setw(10) << "SLOT :" << setw(3) << i << setw(5) << "to" << setw(5) << i+1 << endl;
        }
    }

    vector <int> pro;
    vector <int> vis(n,0);

    for(i=0 ; i<schedule.size()-count ; i++)
    {
        if(schedule[i]>=0 && vis[schedule[i]]==0) 
        {
            vis[schedule[i]]=1;
            pro.push_back(schedule[i]);   
        }
    }

    sort(pro.begin(),pro.end());

    cout << "\n               *****STATITICS*****               " << endl;
    cout << "                    =========                    " << endl;

    int act=0,atat=0,awt=0;

    for(i=0 ; i<n ; i++)
    {
        act+=processes[pro[i]]->ct;
        atat+=processes[pro[i]]->tat;
        awt+=processes[pro[i]]->wt;

        cout << "Process ID :" << setw(3) << processes[pro[i]]->pid << setw(7) << "CT :" << setw(3) << processes[pro[i]]->ct << setw(8) << "TAT :" << setw(3) << processes[pro[i]]->tat << setw(8) << "WT :" << setw(3) << processes[pro[i]]->wt << endl;
    }

    cout << "\nAverage Completion Time  :  " << (double)act/n << endl;
    cout << "Average Turn Around Time :  " << (double)atat/n << endl;
    cout << "Average Waiting Time     :  " << (double)awt/n << "\n" << endl;

    return 0;
}