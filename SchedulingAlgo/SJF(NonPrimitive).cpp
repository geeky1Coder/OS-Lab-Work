//Shortest Job First (Non primitive)
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

vector<pair<int, int>> completion(vector<Job> jobs)
{
    sort(jobs.begin(), jobs.end(), [](Job a, Job b) {
        return ((a.burst <= b.burst) && ((a.arrival <= b.arrival)));
    });

    vector<pair<int, int>> completion;
    int n = jobs.size();
    int i = 0;
    int end = jobs[i].arrival + jobs[i].burst;
    completion.push_back({end, jobs[i].index});
    i++;
    while (i < n)
    {
        if (end > jobs[i].arrival)
        {
            end += (jobs[i].burst);
        }
        else
        {
            end = (jobs[i].arrival + jobs[i].burst);
        }
        completion.push_back({end, jobs[i].index});
        i++;
    }

    sort(completion.begin(), completion.end(), [](pair<int, int> a, pair<int, int> b) {
        return (a.second < b.second);
    });
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
    int n = jobs.size();
    vector<int> waiting_time;
    for (int i = 0; i < n; ++i)
    {
        waiting_time.push_back(tat[i] - jobs[i].burst);
    }
    return waiting_time;
}
int main()
{
    //stores arrival burst and
    vector<Job> jobs;
    Job job1(1, 3, 1);
    Job job2(2, 4, 2);
    Job job3(1, 2, 3);
    Job job4(4, 4, 4);

    jobs.push_back(job1);
    jobs.push_back(job2);
    jobs.push_back(job3);
    jobs.push_back(job4);
    vector<pair<int, int>> completionTime = completion(jobs);
    cout << "Completion Time : ";
    for (auto el : completionTime)
    {
        cout << "Job " << el.second << "--" << el.first << endl;
    }

    cout << "Turn Around Time : ";
    vector<int> tat = turnAroundTime(jobs, completionTime);
    for (int i = 0; i < tat.size(); ++i)
    {
        cout << "Job " << (i + 1) << "--" << tat[i] << endl;
    }

    cout << "Waiting Time : ";
    vector<int> wt = waitingTime(jobs, tat);
    for (int i = 0; i < wt.size(); ++i)
    {
        cout << "Job " << (i + 1) << "--" << wt[i] << endl;
    }
    cout << endl;
}