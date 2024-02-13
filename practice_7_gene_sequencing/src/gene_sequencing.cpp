#include "gene_sequencing.h"

std::unordered_map<std::string, char> codon_to_amino_acid = {
    {"GCT", 'A'}, // Alanine
    {"CGT", 'R'}, // Arginine
    {"AAT", 'N'}, // Asparagine
    {"GAT", 'D'}, // Aspartic acid
    {"TGT", 'C'}, // Cysteine
    {"GAA", 'E'}, // Glutamic acid
    {"CAA", 'Q'}, // Glutamine
    {"GGT", 'G'}, // Glycine
    {"CAT", 'H'}, // Histidine
    {"ATT", 'I'}, // Isoleucine
    {"CTT", 'L'}, // Leucine
    {"AAA", 'K'}, // Lysine
    {"ATG", 'M'}, // Methionine
    {"TTT", 'F'}, // Phenylalanine
    {"CCT", 'P'}, // Proline
    {"TCT", 'S'}, // Serine
    {"ACT", 'T'}, // Threonine
    {"TGG", 'W'}, // Tryptophan
    {"TAT", 'Y'}, // Tyrosine
    {"GTT", 'V'}, // Valine
    {"TAA", '>'}, // Stop
    {"TAG", '>'}, // Stop
    {"TGA", '>'}, // Stop

};
std::string startCodon = "ATG";
char VALID_AA[4] = {'A', 'T', 'C', 'G'};

bool checkValidAA(char c)
{
    for (int i = 0; i < 4; i++)
    {
        if (c == VALID_AA[i])
        {
            return true;
        }
    }
    return false;
}

void getProteins(std::string fullSeq)
{
    bool inProtein = false;
    std::string currentSeq = "";
    std::string currentGene = "";
    std::string currentProtein = "";
    std::map<std::string, int> proteinOccurences;
    std::vector<std::string> sequences;
    for (char c : fullSeq)
    {
        if (checkValidAA(c))
        {
            // look for start
            if (!inProtein)
            {
                if (currentSeq.length() == 2)
                {
                    currentSeq += c;
                    if (currentSeq == startCodon)
                    {
                        inProtein = true;
                        currentGene += currentSeq;
                        currentSeq = "";
                        currentProtein += "M";
                    }
                    else
                    {
                        currentSeq = std::string(1, currentSeq[1]) + currentSeq[2];
                    }
                }
                else
                {
                    currentSeq += c;
                }
            }
            else
            {
                currentSeq += c;
                if (currentSeq.length() == 3)
                {
                    char AA = codon_to_amino_acid[currentSeq];
                    if (AA == '>')
                    {
                        inProtein = false;
                        if (proteinOccurences.find(currentProtein) != proteinOccurences.end())
                        {
                            proteinOccurences[currentProtein]++;
                        }
                        else
                        {
                            proteinOccurences[currentProtein] = 1;
                        }
                        sequences.push_back(currentSeq);
                        currentGene = "";
                        currentProtein = "";
                        currentSeq = "";
                    }
                    else
                    {

                        currentGene += currentSeq;
                        currentProtein += AA;
                        currentSeq = "";
                    }
                }
            }
        }
    }
    if (proteinOccurences.empty())
    {
        std::cout << NO_GENES_FOUND;
        return;
    }
    for (auto it = proteinOccurences.begin(); it != proteinOccurences.end(); it++)
    {
        std::cout << it->first << " : " << it->second << std::endl;
    }
}