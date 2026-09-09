#ifndef APP_STATE_HPP
#define APP_STATE_HPP

#include <string>
#include <vector>

#include "state/MountedPartition.hpp"
#include "state/Session.hpp"

using namespace std;


//Guarda el estado general de la aplicacion
struct AppState {
    string carnet = "202405047";
    vector<MountedPartition> mountedPartitions;
    Session session;
};


#endif