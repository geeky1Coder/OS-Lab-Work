//Shortest Job First (Non Preemptive)
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
        return ((a.arrival <= b.arrival));
    });

    vector<pair<int, int>> completion;
    std::map<int, bool> completed;

    int clock = 0;
    int i = 0;
    int n = jobs.size();
    for (int j = 1; j <= n; ++j)
    {
        completed.insert({(j), false});
    }
    while (i < n)
    {
        int j = 0;
        pair<int, int> minBurst = make_pair(INT_MAX, -1);
        while (j < n && (jobs[j].arrival <= clock))
        {
            if ((!completed[jobs[j].index]) && minBurst.first > jobs[j].burst)
            {
                minBurst.first = jobs[j].burst;
                minBurst.second = jobs[j].index;
            }
            j++;
        }
        if (minBurst.second == -1)
        {
            if (j < n)
            {
                clock += jobs[j].burst + (jobs[j].arrival);
                completed[jobs[j].index] = true;
                completion.push_back({clock, jobs[j].index});
            }
        }
        else
        {
            clock += (minBurst.first);
            completed[minBurst.second] = true;
            completion.push_back({clock, minBurst.second});
        }
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
    vector<pair<int, int>> completionTime = completion(jobs);
    cout << "Completion Time : ";
    for (auto el : completionTime)
    {
        cout << "Job " << el.second << "--" << el.first << endl;
    }
    sort(completionTime.begin(), completionTime.end(), [](pair<int, int> a, pair<int, int> b) {
        return (a.second < b.second);
    });
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
