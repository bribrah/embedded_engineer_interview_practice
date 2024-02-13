### Exercise: Gene Sequencing and Protein Translation Program

**Objective:** Write a program in C or C++ that reads a file containing a long sequence of nucleotides (A, T, C, G) mixed with spaces, new lines, and other irrelevant characters or numbers. The program should detect genes by finding start and stop codons, translate the genes into proteins according to a given translation table, and output the protein sequences along with their corresponding gene sequences and occurrence counts.

#### Requirements:

1. **File Input**: The program should accept a file path as input. The file will contain a sequence of nucleotides (A, T, C, G) and possibly other non-relevant characters.

2. **Gene Detection**:
    - **Start Codon**: ATG
    - **Stop Codons**: TAA, TAG, TGA

3. **Translation Table**: Use a simplified version of the real translation table for this exercise. For example:
    - ATG -> Methionine (M)
    - GGT -> Glycine (G)
    - TTT -> Phenylalanine (F)
    - (Include at least 10-20 mappings for the sake of the exercise; the full table is available online.)

4. **Processing**:
    - Read through the file, cleaning irrelevant characters and identifying sequences starting with the ATG codon and ending with any of the stop codons.
    - Translate the identified gene sequences into proteins based on the translation table.

5. **Output**:
    - For each unique protein sequence, output the protein, the original gene sequences (including start and stop codons) that translate to this protein, and the count of how many times this protein appears.
    - If multiple gene sequences translate to the same protein, list all these gene sequences.

#### Example:

**Input File Content:**
```
XXATGGGTGTTTAAAXXXATGGGTGGGTTGTAGXX
```

**Output:**
```
Protein: MGFF
Gene Sequence 1: ATGGGTGTTTAA
Gene Sequence 2: ATGGGTGGGTTGTA
Occurrences: 2
```

#### Guidelines:

- **File Reading**: Open and read the file content character by character, filtering out non-ATCG characters.
- **State Machine**: Consider using a state machine approach to detect valid gene sequences from the start codon to the stop codon.
- **Data Structures**: Use appropriate data structures to store the translation table, detected genes, and proteins.
- **Translation Logic**: Implement logic to read three nucleotides at a time (codon) and translate them into an amino acid, concatenating these to form the protein sequence.
- **Output Formatting**: Ensure the output is clear and matches the requirements, listing all gene sequences for each unique protein and their occurrences.

#### Tips:

- Start by implementing the basic file reading and sequence filtering logic.
- Develop the translation functionality with a hardcoded small part of the translation table for initial testing.
- Expand your solution step by step, adding detection of start/stop codons, full translation capability, and then the output formatting.

This exercise will test your ability to work with file I/O, strings, state machines, and data structures in C or C++. It's a comprehensive challenge that mirrors real-world problems in bioinformatics, making it an excellent test of your programming and problem-solving skills.

## Test Cases


### 1. Basic Functionality Test
- **Input**: `ATGGGTGTTTAATAG`
- **Expected Output**:
  - Protein: MGV (Methionine, Glycine, Valine)
  - Gene Sequence: ATGGGTGTTTAA
  - Occurrences: 1

### 2. Multiple Genes, Same Protein
- **Input**: `ATGGGTGTTTAAXXXATGGGTGTTTAATAG`
- **Expected Output**: 
  - Protein: MGV
  - Gene Sequences:
    - ATGGGTGTTTAA
    - ATGGGTGTTTAA
  - Occurrences: 2

### 3. Gene With Irrelevant Characters
- **Input**: `XXATGGGTGTTTAAYYY`
- **Expected Output**: 
  - Protein: MGV
  - Gene Sequence: ATGGGTGTTTAA
  - Occurrences: 1

### 4. Multiple Different Proteins
- **Input**: `ATGGGTGTTTAAXXXATGTTTGGGTAA`
- **Expected Output**: 
  - Protein 1: MGV
    - Gene Sequence: ATGGGTGTTTAA
    - Occurrences: 1
  - Protein 2: MF (Methionine, Phenylalanine)
    - Gene Sequence: ATGTTTGGGTAA
    - Occurrences: 1

### 5. No Start Codon
- **Input**: `XXXGGTGTTTAA`
- **Expected Output**: No valid genes found.

### 6. No Stop Codon After Start
- **Input**: `ATGGGTGTTT`
- **Expected Output**: No valid genes found.

### 7. Start Codon Within Gene
- **Input**: `ATGATGGGTGTTTAATAG` (assuming ATG within a gene sequence is considered part of the gene)
- **Expected Output**: 
  - Protein: MMGV
  - Gene Sequence: ATGATGGGTGTTTAA
  - Occurrences: 1

### 8. Overlapping Genes (Not applicable as genes do not overlap in reality, but for the sake of testing parser robustness)
- **Input**: `ATGGGTATGTTTAATAG` (Note: In practice, genes don't overlap like this with shared start/stop codons)
- **Expected Output**: Assuming the first valid gene is processed:
  - Protein: MG (Methionine, Glycine)
  - Gene Sequence: ATGGGTATGTTTAA
  - Occurrences: 1

### 9. Nested Genes (Biologically improbable in this context, included for completeness)
- **Input**: `ATGGGTATGTAGGTTTAATAG` (Genes don't nest with separate start/stop codons in reality)
- **Expected Output**: 
  - Protein: MGI
  - Gene Sequence: ATGGGTATGTAG
  - Occurrences: 1

### 10. Long Sequence With Multiple Genes and Proteins
- **Input**: A long, complex string simulating a real nucleotide sequence with multiple start and stop codons, irrelevant characters, and possible gene sequences.
- **Expected Output**: Varies. The aim is to validate the parser's capability to handle realistic and complex data accurately.

### 11. Edge Cases
- **Input**: An empty file or a file with only irrelevant characters.
- **Expected Output**: No valid genes found.

I have carefully revised these test cases to ensure they accurately reflect standard codon-to-amino acid mappings and the logic expected from the gene sequencing and protein translation exercise. This set should provide comprehensive coverage for testing the functionality of your gene sequencer program, from basic operations to handling more complex scenarios.