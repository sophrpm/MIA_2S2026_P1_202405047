#ifndef SIMUL_STATE_HPP
#define SIMUL_STATE_HPP

#include <string>
#include <vector>
using namespace std;

struct SimulDisk{string path; int size; string unit; string fit;};

struct SimulPartition{string diskPath; string name; int size; string unit; string type; string fit;};

struct SimulMount{string id; string diskPath; string partitionName; bool formatted;};

struct SimulUser{string username; string password; string group; bool active;};

struct SimulFile{string path; int size; bool recursive; string content;};

class SimulState{
private: string studentId;

public:
    vector<SimulDisk> disks;
    vector<SimulPartition> partitions;
    vector<SimulMount> mounts;
    vector<SimulUser> users;
    vector<SimulFile> files;

    explicit SimulState(const string& carnet = "202405047");

    bool diskExists(const string& path) const;
    bool removeDisk(const string& path);

    bool partitionExists(const string& diskPath, const string& name) const;
    bool extendedPartitionExists(const string& diskPath) const;

    bool mountExists(const string& diskPath, const string& name) const;
    string createMountId() const;
    SimulMount* findMount(const string& id);

    bool userExists(const string& username) const;
    bool removeUser(const string& username);

    bool fileExists(const string& path) const;
};

#endif
