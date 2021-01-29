#include <iostream>
#include <fstream>
#include "lib/json.hpp"
namespace nl = nlohmann;

std::string username(nl::json file);
inline bool fileexists (const std::string& name);

int main(int argc, char* argv[]){

    if (argv[1] && fileexists(std::string(argv[1]))){
        std::ifstream openfile(argv[1]);            //Open file stuff
	    nl::json jfile = nl::json::parse(openfile); //
        std::cout << "\nHello "<< username(jfile) << std::endl;
        std::cout << "You are in " <<  jfile["settings"]["guild_positions"].size() << " servers. ";//get server number
        int servinfolders = 0;
        int folders = 0;
        for(int i = 0; i < jfile["settings"]["guild_folders"].size(); i++){ //get number of folders
            /* for some reason, the servers outside of folders are set as a folder for each of them, with the id = null */
            if(i < jfile["settings"]["guild_folders"][i]["id"] != NULL){
                servinfolders+=jfile["settings"]["guild_folders"][i]["guild_ids"].size(); //get number of server in the folder i
                folders++;
            }
        }
        std::cout << servinfolders << " of them are in folders. (there is " << folders << " folders)" << std::endl;
        std::string theme = jfile["settings"]["theme"];
        std::cout << "You prefer " << theme << " theme." << std::endl;

        std::cout << "You have the following accounts: " << std::endl;
        for(int j = 0; j < jfile["connections"].size();j++){
            std::string type = jfile["connections"][j]["type"];
            std::string name = jfile["connections"][j]["name"];
            std::cout << type << " : " << name << std::endl;
        }

	    std::string End;
	    std::cin >> End;
    } else {
        std::cout << "Something went wrong. Make sure the file you specified exists." << std::endl;
    }
    return 0;
}

/*if file exists*/
inline bool fileexists (const std::string& name) {
    std::ifstream f(name.c_str());
    return f.good();
}

/*Get username and tag*/
std::string username(nl::json file){
	std::string name = file["username"];
	int disc = file["discriminator"];
	std::string fulln = name + "#" + std::to_string(disc);
	return fulln;
}