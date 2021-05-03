//Priority Interrupt
//Author -- Yuvraj Mann

#include <bits/stdc++.h>
using namespace std;

class Job
{
public:
    int arrival;
    int burst;
    int index;
    int priority;

    Job(int arrival, int burst, int index, int priority)
    {
        this->arrival = arrival;
        this->burst = burst;
        this->index = index;
        this->priority = priority;
    }
};
bool operator<(const Job &p1, const Job &p2)
{
    return p1.priority < p2.priority;
}
vector<pair<int, int>> completion(vector<Job> jobs)
{
    priority_queue<Job> q;

    int clock = 0;

    int completedCount = 0;
    int n = jobs.size();
    vector<pair<int, int>> complete;
    std::map<int, bool> in_ready;
    for (int j = 1; j <= n; ++j)
    {
        in_ready.insert({(j), false});
    }

    while (completedCount != n)
    {
        //intialing jobs with {clock} arrival time
        for (int i = 0; i < (jobs.size()); ++i)
        {
            if (jobs[i].arrival <= clock)
            {
                if (!in_ready[jobs[i].index])
                {
                    in_ready[jobs[i].index] = true;
                    q.push(jobs[i]);
                }
            }
            else
            {
                break;
            }
        }

        Job max_priority = q.top(); //getting job with max priority
        q.pop();
        max_priority.burst -= 1;
        if (max_priority.burst == 0)
        {
            //Job completed
            complete.push_back({(clock + 1), max_priority.index});
            completedCount++;
        }
        else
        {
            //Job not completed again push it into queue
            q.push(max_priority);
        }
        clock++;
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
    Job j1(0, 5, 1, 10);
    Job j2(1, 4, 2, 20);
    Job j3(2, 2, 3, 30);
    Job j4(4, 1, 4, 40);

    vector<Job> jobs;
    jobs.push_back(j1);
    jobs.push_back(j4);
    jobs.push_back(j2);
    jobs.push_back(j3);

    sort(jobs.begin(), jobs.end(), [](Job a, Job b) {
        return (a.arrival < b.arrival);
    });
    vector<pair<int, int>> completionTime = completion(jobs);
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
