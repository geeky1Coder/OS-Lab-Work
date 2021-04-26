//First Come first Serve
//Author -- Yuvraj Mann

#include <bits/stdc++.h>
using namespace std;

class Job
{
public:
    int arrival;
    int burst;
    int index;

    Job(int arrival, int burst, int index)
    {
        this->arrival = arrival;
        this->burst = burst;
        this->index = index;
    }
};

vector<int> completionTime(vector<Job> jobs)
{
    vector<int> completion;
    int n = jobs.size();
    int i = 1;
    int end = jobs[0].arrival + jobs[0].burst;
    completion.push_back(end);
    while (i < n)
    {
        if (end > (jobs[i].arrival))
        {
            end += jobs[i].burst;
        }
        else
        {
            end = jobs[i].arrival + jobs[i].burst;
        }
        completion.push_back(end);
        i++;
    }
    return completion;
}

vector<int> turnAroundTime(vector<Job> jobs, vector<int> completion)
{
    vector<int> tat;
    int n = jobs.size();
    for (int i = 0; i < n; ++i)
    {
        tat.push_back(completion[i] - jobs[i].arrival);
    }
    return tat;
}

vector<int> waitingTime(vector<Job> jobs, vector<int> tat)
{
    vector<int> waiting;
    int n = jobs.size();
    for (int i = 0; i < n; ++i)
    {
        waiting.push_back(tat[i] - jobs[i].burst);
    }
    return waiting;
}
int main()
{
    vector<Job> jobs;
    Job job1(2, 6, 1);
    Job job2(5, 2, 2);
    Job job3(1, 8, 3);
    Job job4(0, 3, 4);
    Job job5(4, 4, 5);

    jobs.push_back(job1);
    jobs.push_back(job2);
    jobs.push_back(job3);
    jobs.push_back(job4);
    jobs.push_back(job5);

    vector<int> completion = completionTime(jobs);
    cout << "Completion Time :";
    for (auto el : completion)
    {
        cout << el << " ";
    }
    cout << endl;

    cout << "Turn Around Time :";
    vector<int> tat = turnAroundTime(jobs, completion);
    for (auto el : tat)
    {
        cout << el << " ";
    }
    cout << endl;

    cout << "Waiting Time : ";
    vector<int> waiting = waitingTime(jobs, tat);

    for (auto el : waiting)
    {
        cout << el << " ";
    }
    cout << endl;
    return 0;
}