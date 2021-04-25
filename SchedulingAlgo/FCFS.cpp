#include <bits/stdc++.h>
using namespace std;

vector<int> completionTime(vector<int> arrival, vector<int> burst)
{
    vector<int> completion(4, 0);
    int n = arrival.size();
    int i = 1;
    int end = arrival[0] + burst[i];
    completion[0] = end;
    while (i < n)
    {
        if (end > (arrival[i]))
        {
            end += burst[i];
        }
        else
        {
            end = arrival[i] + burst[i];
        }
        completion[i] = end;
        i++;
    }
    return completion;
}

vector<int> turnAroundTime(vector<int> arrival, vector<int> completion)
{
    vector<int> tat;
    int n = arrival.size();
    for (int i = 0; i < n; ++i)
    {
        tat.push_back(completion[i] - arrival[i]);
    }
    return tat;
}

vector<int> waitingTime(vector<int> burst, vector<int> tat)
{
    vector<int> waiting;
    int n = burst.size();
    for (int i = 0; i < n; ++i)
    {
        waiting.push_back(tat[i] - burst[i]);
    }
    return waiting;
}
int main()
{
    vector<int> processes = {0, 1, 5, 6}; //arrival time
    vector<int> burstTime = {2, 2, 3, 4};

    vector<int> completion = completionTime(processes, burstTime);
    cout << "Completion Time :";
    for (auto el : completion)
    {
        cout << el << " ";
    }
    cout << endl;

    cout << "Turn Around Time :";
    vector<int> tat = turnAroundTime(processes, completion);
    for (auto el : tat)
    {
        cout << el << " ";
    }
    cout << endl;

    cout << "Waiting Time : ";
    vector<int> waiting = waitingTime(burstTime, tat);

    for (auto el : waiting)
    {
        cout << el << " ";
    }
    cout << endl;
    return 0;
}