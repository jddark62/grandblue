#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <omp.h>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <set>

#define DEBUG 1

using namespace std;

void sleep(int id) {
    srand(time(0) * id);
    int duration = rand();
    Sleep(duration);
    #ifdef DEBUG
        cout<<id<<" has arrived after "<<duration<< " milliseconds. ";
    #endif
}

int main() {
    int n, days;
    cout<<"Enter the total number of days to simulate: ";
    cin>>days;
    cout<<"Enter the number of runners in the group: ";
    cin>>n;
    cout<<"\n";

    omp_set_num_threads(n);

    vector<int> loneLeader(n);
    fill(loneLeader.begin(), loneLeader.end(), 0);
    vector<int> lateCount(n);
    fill(lateCount.begin(), lateCount.end(), 0);
    set<int> leftGroup;

    for(int iter = 0; iter < days; iter++) {
        cout<<"\n\n=========================================\n";
        cout<<"DAY "<<iter + 1<<"\n\n";
        int leader = -1;
        bool started = false;
        vector<int> runners;

        #pragma omp parallel shared(leader, started, runners, lateCount, loneLeader, leftGroup)
        {
            int id = omp_get_thread_num();

            // Check if runner has left the running group
            if(lateCount[id] >= 5 || loneLeader[id] >= 10) {
                #ifdef DEBUG
                    cout<<id<<" has left the running group\n";
                #endif
                leftGroup.insert(id);
            }
            else {
                if(leader == -1) {
                    leader = id;
                    cout<<"The leader for this session is: "<<leader<<"\n";
                    runners.push_back(leader);
                    #ifdef DEBUG
                        cout<<"The leader has arrived and is waiting...\n\n";
                    #endif
                    Sleep(5000);
                    started = true;
                    #ifdef DEBUG
                        cout<<"\nThe leader has started running\n";
                    #endif
                }
                else {
                    sleep(id);
                    if(started) {
                        #ifdef DEBUG
                            cout<<id<<" is late and has missed the run today.\n";
                        #endif
                        lateCount[id]++;
                    } else {
                        #ifdef DEBUG
                            cout<<id<<" has arrived in time.\n";
                        #endif
                        runners.push_back(id);
                    }
                }
            }
            #pragma omp barrier
        }

        cout<<"\n";
        for(int i = 0; i < runners.size(); i++) {
            #ifdef DEBUG
                cout<<runners[i]<<" was in the running group today\n";
            #endif
        }
        cout<<"\nTotal number of runners today: "<<runners.size()<<"\n";
        if(runners.size() == 1) {
            loneLeader[runners[0]]++;
        }
        cout<<"=========================================\n";

        if((n - leftGroup.size()) < 2) {
            cout<<"Not enough runners in the group. The running group is over :(\n";
            break;
        }
    }

    for(int i = 0; i < n; i++) {
        cout<<i<<" missed the run "<<lateCount[i]<<" times\n";
        cout<<i<<" ran alone "<<loneLeader[i]<<" times\n";
    }
}