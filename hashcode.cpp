#include<bits/stdc++.h>
using namespace std;

class contributor{
public:
    string name;
    vector < pair <string, int> > skillset;
    contributor(string name, vector <pair <string, int> > &skillset){
        this->name = name;
        this->skillset = skillset;
    }
};

class project{
public:
    string name;
    int score;
    int reqDays;
    int bestBefore;
    vector < pair <string, int> > skillset;
    project(string name, int reqDays, int score, int Bestbefore, vector <pair <string, int> > &skillset){
        this->name = name;
        this->reqDays = reqDays;
        this->score = score;
        this->bestBefore = bestBefore;
        this->skillset = skillset;
    }
};

bool operator < (project & p1, project & p2){
    return p1.reqDays * p2.score < p2.reqDays * p1.score;
}

int find(vector <contributor> & list, bool * visited, pair<string, int> & j){
    int pos = 0;
    for(auto x:list){
        if (visited[pos] == true) {
            pos ++;
            continue;
        }
        for(auto &y : x.skillset){
            if(y.first != j.first) continue;    
            if (y.second >= j.second) {
                if (y.second == j.second) y.second++;
                visited[pos] = true;
                return pos;
            }
        }
        pos ++;    
    }
    return -1;
}

int main(){

#ifndef ONLINE_JUDGE
  freopen("d_dense_schedule.in.txt", "r", stdin);
  freopen("outputd.txt", "w", stdout);
#endif

    //input
    int contributorCnt;
    int projCnt;

    cin >> contributorCnt;
    cin >> projCnt;

    vector <contributor> contList;
    vector <project> projList;

    for (int i = 0; i < contributorCnt; i++){
        string name;
        int skillCount;
        vector <pair <string , int> > temp;
        cin >> name;
        cin >> skillCount;
        for(int j = 0; j < skillCount; j++){
            string skillName;
            int skillLevel;
            cin >> skillName;
            cin >> skillLevel;
            temp.push_back(pair <string, int>(skillName, skillLevel));
        }
        contList.push_back(contributor(name, temp));
    }


    for(int i = 0; i < projCnt; i++){
        string name;
        cin >> name;
        int reqDays;
        cin >> reqDays;
        int score;
        cin >> score;
        int bestBefore;
        cin >> bestBefore;
        int skillCount;
        cin >> skillCount;
        vector <pair <string, int> > temp;
        for(int j = 0; j<skillCount; j++){
            string skillName;
            int skillLevel;
            cin >> skillName;
            cin >> skillLevel;
            temp.push_back(pair <string, int>(skillName, skillLevel));
        }
        projList.push_back(project(name, reqDays, score, bestBefore, temp));
    }

    sort(projList.begin(), projList.end());
    //input end

    //vector before showing output
    //res: stores list of Project outputs
    //restemp: stores string list (starts with proj name and followed by contr names) 
    vector <vector <string> > res;

    bool visited[contributorCnt] = {false};
    vector <string> resTemp;
    bool flag = false;
    for(int i = 0; i<projCnt; i++){
        resTemp.clear();
        resTemp.push_back(projList[i].name);
        for(auto j : projList[i].skillset){
            int pos = find(contList, visited, j);
            if (pos == -1) {
                flag = true;
                vector <string> clear;
                resTemp= clear;
                break;
            }
            else resTemp.push_back(contList[pos].name);
        }
        if (flag == true){
            flag = false;
        } else {
            res.push_back(resTemp);
        }
        for(int i = 0; i<contributorCnt; i++){
            visited[i] = false;
        }
    }

    cout << res.size() << endl;
    for (auto x:res){
        bool flag = true;
        for(auto y:x){
            cout << y;
            if (flag == true){
                cout << endl;
            } else cout << " ";
            flag = false;
        }
        cout << endl;
    }
}