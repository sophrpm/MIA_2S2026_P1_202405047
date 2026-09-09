#ifndef REPORT_MANAGER_HPP
#define REPORT_MANAGER_HPP

#include <string>

#include "structures/DiskStructures.hpp"
#include "structures/Ext2Structures.hpp"

using namespace std;

struct AppState;


//Maneja la generacion de reportes
class ReportManager {
public:

    //Genera el reporte solicitado
    bool generateReport(const string& name, const string& path, const string& id, const string& pathFileLs, const AppState& appState, string& message) const;

private:

    //Reporte del MBR y particiones
    bool reportMBR(const string& outputPath, const string& id, const AppState& appState, string& message) const;

    //Reporte de distribucion del disco
    bool reportDisk(const string& outputPath, const string& id, const AppState& appState, string& message) const;

    //Reporte de inodos usados
    bool reportInode(const string& outputPath, const string& id, const AppState& appState, string& message) const;

    //Reporte de bloques usados
    bool reportBlock(const string& outputPath, const string& id, const AppState& appState, string& message) const;

    //Reporte del bitmap de inodos
    bool reportBitmapInode(const string& outputPath, const string& id, const AppState& appState, string& message) const;

    //Reporte del bitmap de bloques
    bool reportBitmapBlock(const string& outputPath, const string& id, const AppState& appState, string& message) const;

    //Reporte del arbol completo
    bool reportTree(const string& outputPath, const string& id, const AppState& appState, string& message) const;

    //Reporte del superbloque
    bool reportSuperBlock(const string& outputPath, const string& id, const AppState& appState, string& message) const;

    //Reporte del contenido de un archivo
    bool reportFile(const string& outputPath, const string& id, const string& internalPath, const AppState& appState, string& message) const;

    //Reporte de archivos y carpetas
    bool reportLs(const string& outputPath, const string& id, const string& internalPath, const AppState& appState, string& message) const;

    //Genera archivo dot y lo convierte al formato pedido
    bool generateGraphviz(const string& dotContent, const string& outputPath, string& message) const;

    //Guarda reportes de texto
    bool generateTextFile(const string& content, const string& outputPath, string& message) const;

    //Obtiene extension del archivo de salida
    string getExtension(const string& path) const;

    //Crea carpetas de la ruta de salida
    bool createOutputDirectories(const string& path) const;

    //Convierte fecha a texto
    string formatDate(time_t date) const;

    //Convierte char fijo a string
    string charArrayToString(const char* text, int size) const;

    //Agrega EBRs al reporte MBR
    bool addLogicalPartitionsMBR(const string& diskPath, const Partition& extendedPartition, string& dotContent) const;

    //Agrega particiones logicas al reporte DISK
    bool addLogicalPartitionsDisk(const string& diskPath, const Partition& extendedPartition, string& dotContent) const;

    //Agrega un inodo al reporte TREE
    bool addInodeTree(const string& diskPath, const SuperBlock& superBlock, int inodeIndex, string& dotContent) const;

    //Agrega bloque carpeta al TREE
    bool addFolderBlockTree(const string& diskPath, const SuperBlock& superBlock, int blockIndex, string& dotContent) const;

    //Agrega bloque archivo al TREE
    bool addFileBlockTree(const string& diskPath, const SuperBlock& superBlock, int blockIndex, string& dotContent) const;

    //Agrega bloque de apuntadores al TREE
    bool addPointerBlockTree(const string& diskPath, const SuperBlock& superBlock, int blockIndex, int level, string& dotContent) const;

    //Convierte permisos a formato rwx
    string permissionToText(const Inode& inode) const;
};


#endif