//
// Created by tanknee on 2021/2/1.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct info
{
    unsigned short id;   //(备注：)采用unsigned short 是因为满足大于40000的要求
    unsigned short Ge;   //如果采用int, info arr[40000] 会造成内存溢出
    float Gsum;
};

bool cmp(info a, info b)
{
    if (a.Gsum == b.Gsum)
        return a.Ge > b.Ge;
    else
        return a.Gsum > b.Gsum;
}

int main()
{
    int N, M, K, Ge, Gi, vol;
    cin>>N>>M>>K;
    info arr[40000];                     //学生集合;
    vector<int> voluntary[40000];        //学生志愿
    vector<int> admitSchool[100];        //大学集合-招到学生的编号
    int numOfStu[101];                   //大学招生人数
    int curNum[101] = {0};               //当前大学招生的人数
    for (int i=0; i<M; i++)
    {
        cin>>numOfStu[i];
    }
    for (int i=0; i<N; i++)
    {
        cin>>Ge>>Gi;
        arr[i].id = i;
        arr[i].Ge = Ge;
        arr[i].Gsum = float(Ge+Gi)/2.0;
        for (int j=0; j<K; j++)
        {
            cin>>vol;
            voluntary[i].push_back(vol);
        }
    }
    sort(arr, arr+N, cmp);                //完成学生的排名，从高到低
    for (int i=0; i<N; i++)
    {
        for (int j=0; j<K; j++)
        {
            int choose = voluntary[arr[i].id][j];          //当前志愿
            if (numOfStu[choose] > curNum[choose])         //人未招满，直接进入vector
            {
                admitSchool[choose].push_back(arr[i].id);
                curNum[choose]++;
                break;
            }
            else           //招满情况，比较报考学校最后一名学生的成绩和当前学生的成绩
            {
                int lastId = admitSchool[choose].back(), callID;
                for (int k=0; k<i; k++)
                {
                    if (arr[k].id == lastId)
                    {
                        callID = k;
                        break;
                    }
                }
                if (arr[callID].Ge==arr[i].Ge && arr[callID].Gsum==arr[i].Gsum)
                {
                    admitSchool[choose].push_back(arr[i].id);
                    curNum[choose]++;
                    break;
                }
            }
        }
    }

    for (int i=0; i<M; i++)
    {
        sort(admitSchool[i].begin(), admitSchool[i].end());
        bool flag = false;
        for (int j=0; j<curNum[i]; j++)
        {
            if (!flag)
            {
                cout<<admitSchool[i][j];
                flag = true;
            }
            else
                cout<<" "<<admitSchool[i][j];
        }
        cout<<endl;
    }

    return 0;
}



/**
 *
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct application {
    int id, ge, gi, rank;

    bool operator>(const application &a) const {
        if (ge + gi != a.ge + a.gi) {
            return ge + gi > a.ge + a.gi;
        } else if (ge != a.ge) {
            return ge > a.ge;
        }
        return false;
    }
};


int main() {
    int application_num, school_num, choice_num;
    cin >> application_num >> school_num >> choice_num;
    int quotas[school_num];
    vector<application> applications(application_num, application{});
    vector<vector<int>> admissions(school_num, vector<int>());
    vector<vector<int>> choices(application_num, vector<int>());
    bool visit[application_num];
    fill(visit, visit + application_num, false);
    for (int i = 0; i < school_num; ++i) {
        cin >> quotas[i];
    }
    for (int i = 0; i < application_num; ++i) {
        applications[i].id = i;
        cin >> applications[i].ge >> applications[i].gi;
        for (int j = 0; j < choice_num; ++j) {
            int tmp;
            cin >> tmp;
            choices[i].push_back(tmp);
//            applications[i].choices.push_back(tmp);
        }
    }
    sort(applications.begin(), applications.end(), greater<>());
    for (int i = 1, rank = 1; i < application_num; ++i) {
        if (applications[i - 1] > applications[i]) {
            applications[i].rank = rank++;
        } else {
            applications[i].rank = applications[i - 1].rank;
        }
    }
    for (int i = 0; i < application_num; ++i) {
        int school;
        if (visit[i]) continue;
        for (int j = 0; j < choices[applications[i].id].size(); ++j) {
            int choice = choices[applications[i].id][j];
            if (quotas[choice] > 0) {
                quotas[choice]--;
                admissions[choice].push_back(applications[i].id);
                school = choice;
                visit[i] = true;
                break;
            }
        }
        for (int j = i + 1; j < applications.size(); ++j) {
            if (applications[j].rank == applications[i].rank) {
                for (int k = 0; k < choices[applications[j].id].size(); ++k) {
                    int choice = choices[applications[j].id][k];
                    if (quotas[choice] > 0 && choice != school) break;
                    if (choice == school) {
                        quotas[choice]--;
                        admissions[choice].push_back(applications[j].id);
                        visit[j] = true;
                        break;
                    }
                }
            } else {
                break;
            }
        }
    }
    for (int i = 0; i < admissions.size(); ++i) {
        if (admissions[i].empty()) {
            cout << endl;
            continue;
        }
        sort(admissions[i].begin(), admissions[i].end());
        for (int j = 0; j < admissions[i].size(); ++j) {
            cout << admissions[i][j];
            if (j != admissions[i].size() - 1) cout << " ";
        }
        cout << endl;
    }
    return 0;
}
**/