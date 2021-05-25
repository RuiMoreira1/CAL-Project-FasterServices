
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>

#include "Solver.h"

using namespace std;

Solver::Solver(Graph<unsigned int> *g) {
    this->g = g;

    for(auto v : g->getVertexSet()){
        //cout << "V> "<< v->getInfo() << endl;
        if(v->getVertexType() == RESIDENCE){
          this->workers.push_back(v);

        }
        else if(v->getVertexType() == COMPANY){
            this->Cn = v;
        }
        else if(v->getVertexType() == GARAGE){
            this->V0 = v;
        }
    }
    //fixGraph();
    this-> meeting_points = this->workers;
    MakeMeetingDists();
}




void Solver::findMeetingPoints() {
    for(auto v1 : this->workers){

    }
}

void Solver::fixGraph() { //TODO
    auto dfsRes = g->DFS(this->V0->getInfo());
    auto invG = g->genInvertedGraph(g->getVertexSet());

    auto invDfsRes = invG->DFS(this->V0->getInfo());
    auto fortG = invG->genInvertedGraph(invDfsRes);

    //delete invG;
    this->g = invG;
    g->clearEmptyVert();
}

void Solver::MakeMeetPath(meetingPath &meetP, const unsigned int s, const unsigned int t) const {
    meetP.path = g->getPath(s, t, &meetP.dist);
    //cout <<  " MS> " <<meetP.dist <<endl;
    if (meetP.path.size() == 0 ||  meetP.path[0] != s)
        meetP.dist = -1;

}

void Solver::MakeMeetingDists() {


    size_t n = meeting_points.size();

    meeting_path.resize((n + 1) + 1);
    for (size_t i = 0; i < n + 2; ++i)
        meeting_path[i].resize((n + 1) + 1);

    unsigned int s, t;
    for (size_t i = 0; i < n; ++i) {
        s = meeting_points[i]->getInfo();
        //cout << ">>>" << s << endl;
        if (g->findVertex(s) != nullptr) {
            //cout << "FOUND";
        }
        //cout << "Debug1\n";
        for (size_t j = 0; j < n; ++j) {
            if (i == j)
                continue;
            //cout << "Debug2\n";
            t = meeting_points[j]->getInfo();
            if (!g->dijkstraBidirectional(s, t)) {
                cout << "oi 1";
                break;
            }
            //throw NoPathFound(s, t);
            MakeMeetPath(meeting_path[i][j], s, t);
        }

        if (!g->dijkstraBidirectional(s, V0->getInfo())) break;
            //cout << "oi 2";
        //throw NoPathFound(s, V0);
        MakeMeetPath(meeting_path[i][n], s, V0->getInfo());

        if (!g->dijkstraBidirectional(s, Cn->getInfo())) break;
            //cout << "oi 3";
        //throw NoPathFound(s, Cn);
        MakeMeetPath(meeting_path[i][n + 1], s, Cn->getInfo());
    }

    for (size_t i = 0; i < n; ++i) {
        t = meeting_points[i]->getInfo();
        if (!g->dijkstraBidirectional(V0->getInfo(), t)) {
            cout << "oi 4";
            break;
        }
        //throw NoPathFound(V0, t);
        MakeMeetPath(meeting_path[n][i], V0->getInfo(), t);
    }

    for (size_t i = 0; i < n; ++i) {
        t = meeting_points[i]->getInfo();
        if (!g->dijkstraBidirectional(Cn->getInfo(), t)) {
            cout << "oi 5";
            break;
        }
        //throw NoPathFound(Cn, t);
        MakeMeetPath(meeting_path[n + 1][i], Cn->getInfo(), t);
    }

    if (!g->dijkstraBidirectional(V0->getInfo(), Cn->getInfo())) {
        cout << "oi 6";
    }
    MakeMeetPath(meeting_path[n][n + 1], V0->getInfo(), Cn->getInfo());

    if (!g->dijkstraBidirectional(Cn->getInfo(), V0->getInfo())) {
        cout << "oi 7";
        //throw NoPathFound(Cn, V0);

    }
    MakeMeetPath(meeting_path[n + 1][n], Cn->getInfo(), V0->getInfo());
}


int Solver::tspInit(vector<bool> &visited) {

    int n = workers.size();

    visited = vector<bool>(n + 2, false);

    vector<meetingPath> end2start_vert;
    meetingPath unreachable_vert = {-1, vector<unsigned>()};

    for (int i = 0; i < n + 2; ++i) {
        end2start_vert.push_back(unreachable_vert);
        meeting_path[i].push_back(unreachable_vert);
    }
    end2start_vert.push_back(unreachable_vert); // end2start selfconnect forbidden
    meeting_path.push_back(end2start_vert);

    meeting_path[n + 2][n].dist = 0;     // -> V0
    meeting_path[n + 1][n + 2].dist = 0; // <- Cn


    return n;
}

vector<unsigned> Solver::tsp() {
    vector<bool> visited;

    size_t n = tspInit(visited);

    vector<unsigned> path;
    unsigned curr_vert = n + 1;       // start at Cn
    unsigned curr_target = curr_vert; // init for exception in case of failure
    visited[curr_vert] = true;

    for (size_t num_visited = 1; num_visited <= n + 2; ++num_visited) {
        double min = 999999;
        bool found_target = false;

        for (size_t i = 0; i <= n + 2; ++i) {
            double check_dist = meeting_path[curr_vert][i].dist;
            if (check_dist >= 0 && check_dist < min && !visited[i]) {
                found_target = true;
                min = check_dist;
                curr_target = i;
            }
        }

        if (!found_target)
            break;
            //cout << "not target";

        path.push_back(curr_target);

        curr_vert = curr_target;
        visited[curr_vert] = true;
    }

    path.erase(path.begin()); // Remove aux
    if (meeting_path[curr_vert][n + 1].dist < 0)
        cout << "not";
    path.push_back(n + 1);

    vector<unsigned> vertex_path;

    for(auto i : path){
        if (i == n){
            vertex_path.push_back(this->V0->getInfo());
        }
        else if (i == n+1){
            vertex_path.push_back(this->Cn->getInfo());
        }
        else if( i < meeting_points.size()) {
            vertex_path.push_back(meeting_points[i]->getInfo());
            //cout << endl << meeting_points[i]->getInfo() << " " << i<< endl;
        }
    }



    return vertex_path;
}

