

#ifndef CAL_PROJETCT_FASTERSERVICES_SOLVER_H
#define CAL_PROJETCT_FASTERSERVICES_SOLVER_H

#include <exception>
#include <string>
#include <utility>

#include "Graph.h"
#include "GraphImporter.h"

#define DEAD_EDGE pair<unsigned, unsigned>
#define ASSIGNED_BUSES_TYPE vector<vector<unsigned>>

typedef struct {
    double dist;
    vector<unsigned> path;
} meetingPath;

class Solver {
private:
    Graph<unsigned> *g;
    vector<Vertex<unsigned> *> workers;
    vector<Vertex<unsigned> *> meeting_points;
    vector<DEAD_EDGE> dead_edges;

    double d_max = 0;
    Vertex<unsigned> *V0 ;
    Vertex<unsigned> *Cn ;

    vector<Vertex<unsigned> *> used_vertexes;
    //vector<MeetingPoint> meeting_points;
    vector<Vertex<unsigned> *> bus_stops;
    vector<vector<meetingPath>> meeting_path;
    vector<unsigned> bus_capacities;



    void ResetUsedVertexes(void);


    void MakeMeetPath(meetingPath &mp, unsigned const s, unsigned const t) const;

    void parseConfig(const string &config_file);

public:
    Solver(Graph<unsigned > *g);



    void findMeetingPoints();

    void MakeMeetingDists();

    /**
     * @brief Normalize the Graph g coordinates based on graphImporter reported
     *        maximum and minimum values.
     */
    void normalize(void);
    /**
     * @brief Get a random configuration.
     */
    void genRandConf(const size_t num_bus_stops, const size_t num_workers,
                     const double d_max);
    /**
     * @brief Import bus stops from a file.
     */
    void importBusStops(const string &bus_file);
    /**
     * @brief Import company information from a file.
     */
    void importCompany(const string &worker_file);

    /**
     * @brief Performs many operations to get the imported Graph g ready for use
     *        in the ProblemSolver. Clears empty Vertex (see Graph.h), the
     * strongly connected component, etc..
     */
    void fixGraph(void);

    Graph<unsigned> *getGraph(void) { return this->g; }
    /*unsigned getV0(void) { return this->V0; }
    unsigned getCn(void) { return this->Cn; }
    void setV0(unsigned V0) { this->V0 = V0; }
    void setCn(unsigned Cn) { this->Cn = Cn; }*/

    /**
     * @brief Converts a given path of Vertex represented by their info into a
     *        list of all the Vertexes that must be passed on the shortest path
     *        (vertexes between them).
     */
    vector<unsigned> reconstructPath(const vector<unsigned> &path);



    void assignMeetingPoints();

    ;

    int tspInit(vector<bool> &visited);

    vector<unsigned> tsp();

    vector<vector<unsigned>> assignBuses(const vector<unsigned> &main_path);

    vector<unsigned> genBusPath(unsigned start, unsigned end,
                                const vector<unsigned> &p);


    void clearSolution();



};

#endif //CAL_PROJETCT_FASTERSERVICES_SOLVER_H
