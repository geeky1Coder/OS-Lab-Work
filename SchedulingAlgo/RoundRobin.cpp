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

vector<pair<int, int>> completion(vector<Job> jobs, int timeQuantum)
{
    sort(jobs.begin(), jobs.end(), [](Job a, Job b) {
        return ((a.arrival <= b.arrival));
    });
    //running queue
    queue<Job> ready;
    int clock = 0;
    ready.push(jobs[0]); //placing very first JOB

    int n = jobs.size();
    int completedCount = 0;
    //checking if job is completed
    std::map<int, bool> completed;
    //checking bojs in ready queue
    std::map<int, bool> in_ready;
    for (int j = 1; j <= n; ++j)
    {
        completed.insert({(j), false});
        in_ready.insert({(j), false});
    }

    vector<pair<int, int>> complete;
    while (completedCount != n)
    {
        Job front_Job = (ready.front()); //job ready execute
        if (front_Job.burst <= (timeQuantum))
        {
            //Job can be completed within this time quantum
            clock += front_Job.burst;
            front_Job.burst = 0;
            completed[front_Job.index] = true;
            completedCount++;
            complete.push_back({clock, front_Job.index});
        }
        else
        {
            //Job can't be completed within this time quantum
            front_Job.burst -= timeQuantum;
            clock += timeQuantum;
        }
        ready.pop();
        in_ready[front_Job.index] = false;
        //Pushing jobs to queue;
        for (auto el : jobs)
        {
            if (el.arrival <= clock && (!in_ready[el.index]) && (el.index != front_Job.index) && (!completed[el.index]))
            {
                ready.push(el);
                in_ready[el.index] = true;
            }
        }

        //push executed againg in ready queue if not completed
        if (front_Job.burst > 0)
        {
            ready.push(front_Job);
            in_ready[front_Job.index] = true;
        }
    }
    return complete;
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
    Job j1(0, 5, 1);
    Job j2(1, 4, 2);
    Job j3(2, 2, 3);
    Job j4(4, 1, 4);

    vector<Job> jobs;
    int timeQuantum = 2;
    jobs.push_back(j1);
    jobs.push_back(j2);
    jobs.push_back(j3);
    jobs.push_back(j4);

    vector<pair<int, int>> completionTime = completion(jobs, timeQuantum);
    cout << "Completion Time : " << endl;
    for (auto el : completionTime)
    {
        cout << "Job " << el.second << "--" << el.first << endl;
    }
    sort(completionTime.begin(), completionTime.end(), [](pair<int, int> a, pair<int, int> b) {
        return (a.second < b.second);
    });
    cout << "Turn Around Time : " << endl;
    vector<int> tat = turnAroundTime(jobs, completionTime);
    for (int i = 0; i < tat.size(); ++i)
    {
        cout << "Job " << (i + 1) << "--" << tat[i] << endl;
    }
    cout << "Waiting Time : " << endl;
    vector<int> wt = waitingTime(jobs, tat);
    for (int i = 0; i < wt.size(); ++i)
    {
        cout << "Job " << (i + 1) << "--" << wt[i] << endl;
    }
    cout << endl;

    return 0;
}
