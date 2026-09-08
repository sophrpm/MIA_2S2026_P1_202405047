#include "simulation/SimulState.hpp"

#include <algorithm>
#include <cctype>
using namespace std;

SimulState::SimulState(const string& carnet)
    : studentId(carnet){}

    //existe el disco?
bool SimulState::diskExists(const string& path) const{
    for (const SimulDisk& disk : disks){
        if (disk.path == path){
            return true;
        }
    }
    return false;
}

//elimina un disco
bool SimulState::removeDisk(const string& path){
    for (size_t diskIndex = 0; diskIndex < disks.size(); diskIndex++){
        if (disks[diskIndex].path == path){
            disks.erase(disks.begin() + static_cast<long>(diskIndex));

            //elimina part y mount asociadas
            partitions.erase(
                remove_if(
                    partitions.begin(),
                    partitions.end(),
                    [&path](const SimulPartition& partition){
                        return partition.diskPath == path;
                    }
                ),
                partitions.end()
            );
            mounts.erase(
                remove_if(
                    mounts.begin(),
                    mounts.end(),
                    [&path](const SimulMount& mountedPartition){
                        return mountedPartition.diskPath == path;
                    }
                ),
                mounts.end()
            );

            return true;
        }
    }
    return false;
}

//existe la particion?
bool SimulState::partitionExists(
    const string& diskPath,
    const string& name
) 
const{
    for (const SimulPartition& partition : partitions){
        if (partition.diskPath == diskPath && partition.name == name){
            return true;
        }
    }
    return false;
}

//particion extendida?
bool SimulState::extendedPartitionExists(const std::string& diskPath) const
{
    for (const SimulPartition& partition : partitions){
        if (partition.diskPath == diskPath && partition.type == "E"){
            return true;
        }
    }
    return false;
}

//existe el mount?
bool SimulState::mountExists(
    const std::string& diskPath,
    const std::string& name
) const{
    for (const SimulMount& mountedPartition : mounts){
        if (mountedPartition.diskPath == diskPath &&mountedPartition.partitionName == name){
            return true;
        }
    }
    return false;
}

//crea id mount
string SimulState::createMountId() const{
    string digits;
    for (char character : studentId){
        if (isdigit(static_cast<unsigned char>(character))){
            digits += character;
        }
    }

    if (digits.size() > 2){
        digits = digits.substr(digits.size() - 2);
    }

    if (digits.empty()){
        digits = "00";
    }

    return digits + to_string(mounts.size() + 1) + "A";
}

//busca mount por id
SimulMount* SimulState::findMount(const string& id)
{
    for (SimulMount& mountedPartition : mounts){
        if (mountedPartition.id == id){
            return &mountedPartition;
        }
    }
    return nullptr;
}

//existe el usuario?
bool SimulState::userExists(const std::string& username) const{
    for (const SimulUser& user : users){
        if (user.username == username && user.active){
            return true;
        }
    }
    return false;
}

bool SimulState::removeUser(const std::string& username){
    for (SimulUser& user : users){
        if (user.username == username && user.active){
            user.active = false;
            return true;
        }
    }
    return false;
}

//existe el archivo?
bool SimulState::fileExists(const std::string& path) const{
    for (const SimulFile& file : files){
        if (file.path == path){
            return true;
        }
    }
    return false;
}