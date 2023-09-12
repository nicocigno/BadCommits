#include <fstream>
#include <iostream>
#include <map>


class CommitData{
    public:
    std::string name;
    std::string commit;
    std::string tester;
    size_t size;

    CommitData(const std::string& name, const std::string& commit)
    : name(name), commit(commit){
        tester = Tester_ID(name);
    }

    std::string Tester_ID(const std::string& inputString) {
    size_t firstPipePos = inputString.find('|');
    size_t secondPipePos = inputString.find('|', firstPipePos + 1);
    return inputString.substr(firstPipePos + 2, secondPipePos - firstPipePos - 2);
    }
    
    static void filterDataframe(std::vector<CommitData>& commitDataVector, std::vector<CommitData>& filteredCommitDataVector){
        for (const CommitData& data : commitDataVector) {
            if (data.size < 20) {
                filteredCommitDataVector.push_back(data);
            }
        }
    }

    static std::vector<std::string> Return_filtered_testers(std::vector<CommitData> filteredCommitDataVector ){
        
        std::vector<std::string> tes;
        for (const CommitData& data: filteredCommitDataVector){
            tes.push_back(data.tester);
        }
        return tes;
    }

};