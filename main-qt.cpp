#include <QApplication>
#include <QtWidgets>
#include <iostream>
#include <fstream>
#include "lib/json.hpp"
namespace nl = nlohmann;
/* open file (i def need to do a hpp for that*/
class fileDialog{
public:
    std::string openfile(){
        QString fileName = QFileDialog::getOpenFileName(Q_NULLPTR,
               "Open json file", "",
               "JSON file (*.json);;All Files (*)");
        std::string str = fileName.toStdString();
        return str;
    }
};
std::string username(nl::json file);
int main(int argc, char *argv[]){

    QApplication app(argc, argv);
    QLabel *text = new QLabel;
    std::string output;
    /*QLineEdit file;
    file.setText("Path to file");
    QPushButton confirm;
    confirm.setText("Open");*/
    /*std::string filename;                       //
    std::cout << "File?" << std::endl;          //
    std::cin >> filename;                       //Open file
    std::ifstream openfile(filename);           *///
    fileDialog openthefile;
    std::ifstream file(openthefile.openfile());
    nl::json jfile = nl::json::parse(file); //

    output += "Hello " + username(jfile);
    output += std::string("\nYou are in ") +  std::to_string(jfile["settings"]["guild_positions"].size()) + std::string(" servers.\n");//get server number
    int servinfolders = 0;
    int folders = 0;
    for(int i = 0; i < jfile["settings"]["guild_folders"].size(); i++){ //get number of folders
        /* for some reason, the servers outside of folders are set as a folder for each of them, with the id = null */
        if(i < jfile["settings"]["guild_folders"][i]["id"] != NULL){
            servinfolders+=jfile["settings"]["guild_folders"][i]["guild_ids"].size(); //get number of server in the folder i
            folders++;
        }
    }
    output += std::to_string(servinfolders) + std::string(" of them are in folders. (there is ") + std::to_string(folders) + std::string(" folders)\n");
    std::string theme = jfile["settings"]["theme"];
    output += "You prefer " + theme + " theme.\n";

    output += "You have the following accounts: \n";
    for(int j = 0; j < jfile["connections"].size();j++){
        std::string type = jfile["connections"][j]["type"];
        std::string name = jfile["connections"][j]["name"];
        output += type + " : " + name + "\n";
    }

    /*std::string End;
    std::cin >> End;*/
    text->setText(QString::fromStdString(output));
    text->show();
    return app.exec();
}



/*Get username and tag*/
std::string username(nl::json file){
    std::string name = file["username"];
    int disc = file["discriminator"];
    std::string fulln = name + "#" + std::to_string(disc);
    return fulln;
}
