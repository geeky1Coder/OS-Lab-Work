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

vector<pair<int, int>> completionTime(vector<Job> jobs)
{
    vector<pair<int, int>> completion;
    sort(jobs.begin(), jobs.end(), [](Job a, Job b) {
        return (a.arrival < b.arrival);
    });
    int n = jobs.size();
    int i = 1;
    int end = jobs[0].arrival + jobs[0].burst;
    completion.push_back({end, jobs[0].index});
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
        completion.push_back({end, jobs[i].index});
        i++;
    }
    return completion;
}

vector<int> turnAroundTime(vector<Job> jobs, vector<pair<int, int>> completionTime)
{
    int n = jobs.size();
    vector<int> tat;
    for (int i = 0; i < n; ++i)
    {
        tat.push_back(completionTime[i].first - jobs[i].arrival);
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

    vector<pair<int, int>> completion = completionTime(jobs);
    cout << "Completion Time :";
    for (auto el : completion)
    {
        cout << "Job " << el.second << "--" << el.first << endl;
    }
    cout << endl;

    sort(completion.begin(), completion.end(), [](pair<int, int> a, pair<int, int> b) {
        return (a.second < b.second);
    });
    cout << "Turn Around Time :";
    vector<int> tat = turnAroundTime(jobs, completion);
    for (int i = 0; i < tat.size(); ++i)
    {
        cout << "Job " << (i + 1) << "--" << tat[i] << endl;
    }
    cout << endl;

    cout << "Waiting Time : ";
    vector<int> wt = waitingTime(jobs, tat);

    for (int i = 0; i < wt.size(); ++i)
    {
        cout << "Job " << (i + 1) << "--" << wt[i] << endl;
    }
    cout << endl;
    return 0;
}