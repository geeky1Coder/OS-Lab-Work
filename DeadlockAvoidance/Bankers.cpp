//Bankers Algo
//Author -- Yuvraj Mann
#include <bits/stdc++.h>
using namespace std;

class Process
{
public:
    int index;
    vector<int> allocation;
    vector<int> maxNeed;
    vector<int> remaingNeed;
    Process(int index, vector<int> allocation, vector<int> maxNeed)
    {
        this->index = index;
        this->allocation = allocation;
        this->maxNeed = maxNeed;
        int n = allocation.size();
        for (int i = 0; i < n; ++i)
        {
            remaingNeed.push_back((maxNeed[i] - allocation[i]));
        }
    }
};

vector<int> resTotal = {10, 5, 7};
int resources = 3;
vector<int> availableNow(vector<Process> processes)
{
    int n = processes.size();
    int resources = processes[0].allocation.size();
    vector<int> curUsed(resources, 0);
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < resources; ++j)
        {
            int t = processes[i].allocation[j];
            curUsed[j] += t;
        }
    }

    vector<int> iniAllocation(resources, 0);

    for (int j = 0; j < resources; ++j)
    {
        iniAllocation[j] = (resTotal[j] - curUsed[j]);
    }
    return iniAllocation;
}
vector<int> applyBankers(vector<Process> processes, vector<int> available)
{
    vector<int> order;
    map<int, bool> completed;
    int completedCount = 0;
    int processCount = processes.size();
    bool isDeadlocked = false;

    for (int i = 0; i < processCount; ++i)
    {
        completed.insert(make_pair(i, false));
    }
    while (completedCount != processCount)
    {
        bool f1 = false;
        for (int i = 0; i < processCount; ++i)
        {
            bool f = true;
            if (completed[i] == false)
            {
                for (int j = 0; j < resources; ++j)
                {
                    if (available[j] < processes[i].remaingNeed[j])
                    {
                        f = false;
                        break;
                    }
                }
                if (f)
                {
                    //we can process this process
                    completed[i]=true;
                    f1 = true;
                    order.push_back(i);
                    completedCount++;
                    for(int j=0;j<resources;++j){
                        available[j]+=(processes[i].allocation[j]);
                    }
                }
            }
        }

        if (!f1)
        {
            isDeadlocked = true;
            break;
        }
    }

    if(isDeadlocked){
        //System is Deadlocaked
        vector<int> nullAns;
        return nullAns;
    }
    else{
        return order;
    }
}
int main()
{

    vector<Process> processes;
    vector<int> a1 = {0, 1, 0};
    vector<int> m1 = {7, 5, 3};
    Process p1(0, a1, m1);
    vector<int> a2 = {2, 0, 0};
    vector<int> m2 = {3, 2, 2};
    Process p2(1, a2, m2);
    vector<int> a3 = {3, 0, 2};
    vector<int> m3 = {9, 0, 2};
    Process p3(2, a3, m3);
    vector<int> a4 = {2, 1, 1};
    vector<int> m4 = {4, 2, 2};
    Process p4(3, a4, m4);
    vector<int> a5 = {0, 0, 2};
    vector<int> m5 = {5, 3, 3};
    Process p5(4, a5, m5);

    processes.push_back(p1);
    processes.push_back(p2);
    processes.push_back(p3);
    processes.push_back(p4);
    processes.push_back(p5);

    vector<int> iniAvailable = availableNow(processes);
    

    vector<int> order=applyBankers(processes,iniAvailable);
    if(order.size()==0){
        cout<<"System is Deadlocked !";
    }
    else{
        cout<<"Safe Order :";
        for(auto el:order){
                cout<<"p"<<(el+1)<<" ";
        }
    }
    cout<<endl;
    return 0;
}