#include "gene_sequencing.h"

int main(int argc, char *argv[])
{
    std::string filename;
    if (argc < 2)
    {
        std::cout << "need to enter a filename...";
        // return -1;
    }
    filename = std::string(argv[1]);
    std::cout << "using filename: " << filename << std::endl;

    std::ifstream file(filename);

    std::string myText;
    std::getline(file, myText);
    getProteins(myText);
    return 0;
}