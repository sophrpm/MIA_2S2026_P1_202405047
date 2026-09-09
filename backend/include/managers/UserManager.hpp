#ifndef USER_MANAGER_HPP
#define USER_MANAGER_HPP

#include <string>

using namespace std;

struct AppState;


//Maneja usuarios, grupos y sesion activa
class UserManager {
public:

    //Inicia sesion con un usuario
    bool login(const string& user, const string& password, const string& id, AppState& appState, string& message) const;

    //Cierra la sesion actual
    bool logout(AppState& appState, string& message) const;

    //Crea un grupo nuevo
    bool createGroup(const string& name, AppState& appState, string& message) const;

    //Elimina un grupo
    bool removeGroup(const string& name, AppState& appState, string& message) const;

    //Crea un usuario nuevo
    bool createUser(const string& user, const string& password, const string& group, AppState& appState, string& message) const;

    //Elimina un usuario
    bool removeUser(const string& user, AppState& appState, string& message) const;

    //Cambia el grupo de un usuario
    bool changeUserGroup(const string& user, const string& group, AppState& appState, string& message) const;

private:

    //Lee todo el contenido de users.txt
    bool readUsersFile(const AppState& appState, string& content, string& message) const;

    //Escribe el nuevo contenido de users.txt
    bool writeUsersFile(AppState& appState, const string& content, string& message) const;

    //Verifica si hay una sesion activa
    bool hasActiveSession(const AppState& appState) const;

    //Verifica si el usuario actual es root
    bool isRoot(const AppState& appState) const;

    //Busca un grupo activo
    bool groupExists(const string& content, const string& group) const;

    //Busca un usuario activo
    bool userExists(const string& content, const string& user) const;

    //Busca las credenciales de un usuario
    bool validLogin(const string& content, const string& user, const string& password, int& uid, int& gid) const;

    //Obtiene el id de un grupo
    int getGroupId(const string& content, const string& group) const;

    //Obtiene el siguiente id para grupo
    int getNextGroupId(const string& content) const;

    //Obtiene el siguiente id para usuario
    int getNextUserId(const string& content) const;

    //Marca un grupo como eliminado
    bool markGroupDeleted(string& content, const string& group) const;

    //Marca un usuario como eliminado
    bool markUserDeleted(string& content, const string& user) const;

    //Cambia el grupo dentro del registro del usuario
    bool updateUserGroup(string& content, const string& user, const string& group) const;
};


#endif