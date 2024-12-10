#include <bits/stdc++.h>
using namespace std;

typedef tuple<string, int, int> Process;

const int MAX_PROCESSES = 100;
const int MAX_TIME = 30;

vector<Process> processes;      
int process_count;             
int last_instant = MAX_TIME;     
char timeline[MAX_TIME][MAX_PROCESSES]; 
int finishTime[MAX_PROCESSES];   
int turnAroundTime[MAX_PROCESSES]; 
double normTurn[MAX_PROCESSES];  

int getArrivalTime(const Process &p) { return get<1>(p); }
int getServiceTime(const Process &p) { return get<2>(p); }
string getProcessName(const Process &p) { return get<0>(p); }

bool sortByArrivalTime(const Process &a, const Process &b) {
    return get<1>(a) < get<1>(b);
}

void firstComeFirstServe() {
    int time = getArrivalTime(processes[0]); 

    for (int i = 0; i < process_count; i++) {
        int arrivalTime = getArrivalTime(processes[i]);
        int serviceTime = getServiceTime(processes[i]);

        finishTime[i] = max(time, arrivalTime) + serviceTime;
        turnAroundTime[i] = finishTime[i] - arrivalTime;
        normTurn[i] = (double)turnAroundTime[i] / serviceTime;

        last_instant = max(last_instant, finishTime[i]);

        for (int j = time; j < finishTime[i] && j < MAX_TIME; j++) {
            timeline[j][i] = '*';
        }
        
        for (int j = arrivalTime; j < time && j < MAX_TIME; j++) {
            timeline[j][i] = '.';
        }

        time = finishTime[i]; 
    }
}


void printProcesses() {
    cout << "Process    ";
    for (int i = 0; i < process_count; i++) {
        cout << "|  " << getProcessName(processes[i]) << "  ";
    }
    cout << "|\n";
}

void printArrivalTime() {
    cout << "Arrival    ";
    for (int i = 0; i < process_count; i++) {
        printf("|%3d  ", getArrivalTime(processes[i]));
    }
    cout << "|\n";
}

void printServiceTime() {
    cout << "Service    ";
    for (int i = 0; i < process_count; i++) {
        printf("|%3d  ", getServiceTime(processes[i]));
    }
    cout << "|\n";
}

void printFinishTime() {
    cout << "Finish     ";
    for (int i = 0; i < process_count; i++) {
        printf("|%3d  ", finishTime[i]);
    }
    cout << "|\n";
}

void printTurnAroundTime() {
    cout << "Turnaround ";
    for (int i = 0; i < process_count; i++) {
        printf("|%3d  ", turnAroundTime[i]);
    }
    cout << "|\n";
}

void printNormTurn() {
    cout << "NormTurn   ";
    for (int i = 0; i < process_count; i++) {
        printf("|%4.2f ", normTurn[i]);
    }
    cout << "|\n";
}

void printTimeline() {
    for (int i = 0; i <= last_instant; i++) 
        cout << i % 10 << " ";
    cout << "\n";
    cout << "------------------------------------------------\n";
    for (int i = 0; i < process_count; i++) {
        cout << getProcessName(processes[i]) << "     |";
        for (int j = 0; j <= last_instant; j++) {
            cout << timeline[j][i] << "|";
        }
        cout << " \n";
    }
    cout << "------------------------------------------------\n";
}


int main() {
   
    memset(timeline, ' ', sizeof(timeline));

    int count;
    cin>>count;

    cout << "Enter the number of processes: ";
    cin >> process_count;

    cout << "Enter process details (Name ArrivalTime ServiceTime):\n";
    for (int i = 0; i < process_count; i++) {
        string name;
        int arrival, service;
        cin >> name >> arrival >> service;
        processes.emplace_back(name, arrival, service);
    }

    sort(processes.begin(), processes.end(), sortByArrivalTime);

    firstComeFirstServe();

    printProcesses();
    printArrivalTime();
    printServiceTime();
    printFinishTime();
    printTurnAroundTime();
    printNormTurn();
    if(count==1) cout<<"FCFS   ";
    printTimeline();

    return 0;
}
