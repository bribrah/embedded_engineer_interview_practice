#include <gtest/gtest.h>
#include "gene_sequencing.h"
#include <algorithm>

std::string testSequence(std::string input)
{
    testing::internal::CaptureStdout();
    getProteins(input);
    std::string captured = testing::internal::GetCapturedStdout();
    captured.erase(std::remove(captured.begin(), captured.end(), '\0'), captured.end());
    return captured;
}

int countLines(std::string input)
{
    int count = 0;
    for (char c : input)
    {
        if (c == '\n')
        {
            count++;
        }
    }
    return count;
}

TEST(GeneSequencing, BasicFunctionality)
{
    std::string input = "ATGGGTGTTTAATAG";
    std::string captured = testSequence(input);

    EXPECT_TRUE(captured.find("MGV : 1") != std::string::npos);
    EXPECT_EQ(countLines(captured), 1);
}

TEST(GeneSequencing, MultipleGenesSameProtein)
{
    std::string input = "ATGGGTGTTTAAXXXATGGGTGTTTAATAG";

    std::string captured = testSequence(input);

    EXPECT_TRUE(captured.find("MGV : 2") != std::string::npos);
    EXPECT_EQ(countLines(captured), 1);
}

TEST(GeneSequencing, Genes_With_Irrelevant_Chars)
{
    std::string input = "XXATGGGTGTTTAAYYY";
    std::string captured = testSequence(input);

    EXPECT_TRUE(captured.find("MGV : 1") != std::string::npos);
    EXPECT_EQ(countLines(captured), 1);
}

TEST(GeneSequencing, MultipleProteins)
{
    std::string input = "ATGGGTGTTTAAXXXATGTTTGGGTAA";

    std::string captured = testSequence(input);

    EXPECT_TRUE(captured.find("MGV : 1") != std::string::npos);
    EXPECT_TRUE(captured.find("MF : 1") != std::string::npos);
    EXPECT_EQ(countLines(captured), 2);
}

TEST(GeneSequencing, NoStartCodon)
{
    std::string input = "XXXGGTGTTTAA";

    std::string captured = testSequence(input);

    EXPECT_TRUE(captured.find(NO_GENES_FOUND) != std::string::npos);
}

TEST(GeneSequencing, NoStopCodon)
{
    std::string input = "ATGGGTGTTT";

    std::string captured = testSequence(input);

    EXPECT_TRUE(captured.find(NO_GENES_FOUND) != std::string::npos);
}

TEST(GeneSequencing, StartCodonWithinGene)
{
    std::string input = "ATGATGGGTGTTTAATAG";

    std::string captured = testSequence(input);

    EXPECT_TRUE(captured.find("MMGV : 1") != std::string::npos);
    EXPECT_EQ(countLines(captured), 1);
}

TEST(GeneSequencing, EdgeCases)
{
    std::string input = "";

    std::string captured = testSequence(input);

    EXPECT_TRUE(captured.find(NO_GENES_FOUND) != std::string::npos);

    captured = testSequence("581361498075675672315[][]  71285725[';;89213487234]");

    EXPECT_TRUE(captured.find(NO_GENES_FOUND) != std::string::npos);
}
