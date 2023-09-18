#include "Comicazz.hpp"





int main(int argc, char* argv[]){

    if (argc != 2) {
        std::cerr << "Oh forgive me, you initiated me but I didn't show up. My name is Comicazz, you're probably wondering 'What the fuck is this stuff?'. The answer is very simple, a bounty hunter. A big problem afflicts our society, the commits done like a dog. Relaunch me by specifying an svn path, I will find the bad boys for you.\n Write in my folder command prompt 'Comicazz.exe svn_url_path'" <<  std::endl;
        return 1; // Return an error code
    }
    std::string svn_url(argv[1]);
   
    std::string svnbase = "svn log -v --search \"report\" " + svn_url ;
    const char* svnCommand = svnbase.c_str();

    std::cout << svnbase << std::endl;

    // Open a pipe to capture the command's output
    FILE* pipe = popen(svnCommand, "r");
    
    if (!pipe) {
        std::cerr << "Error: Unable to execute the command." << std::endl;
        return 1; // Return an error code
    }
    
    char buffer[1024*2]; // Buffer for reading lines
    std::string line;
    std::vector<CommitData> commitDataVector;
    std::string commitMessage;
    
    while (fgets(buffer, sizeof(buffer), pipe)) {
        line = buffer;
        if (line[0] == 'r' && line[1] != 'e') {
            // Create a CommitData object and populate it
            CommitData commitData(line, "");
            std::string commitMessage;
            while (fgets(buffer, sizeof(buffer), pipe)) {
                line = buffer;
                if (line[0] == '-'){
                    break;
                }
                if (line[0] != '-'){
                    commitMessage = line;    
                }
                
               
                commitData.commit = commitMessage;
                commitData.size = commitData.commit.size();
                
            }
            commitDataVector.push_back(commitData);
        }

    }

    pclose(pipe);

    std::vector<CommitData> filteredCommitDataVector;
    
    CommitData::filterDataframe(commitDataVector,filteredCommitDataVector);

    for (const auto& data : filteredCommitDataVector){
        std::cout << "Tester: " << data.tester << ",Commit: " << data.commit << ", Size: " << data.size << std::endl;
    }

    std::vector<std::string> countTester;

    countTester = CommitData::Return_filtered_testers(filteredCommitDataVector);

    std::map<std::string, int> stringCounts = countStringOccurrences(countTester);

    std::cout << "######################## RESULTS ########################" << std::endl;
    for (std::map<std::string, int>::iterator it = stringCounts.begin(); it != stringCounts.end(); ++it) {
        std::cout << "Tester: " << it->first << ", Bad Commits: " << it->second << std::endl;
    }


    return 0;

    
}
