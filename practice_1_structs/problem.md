### Challenge: Struct Size Exploration

1. **Define Structs**: Define three struct types with varying data types and orderings. For example:

   - **Struct A**: Contains a `char`, an `int`, a `char`, and a `double`.
   - **Struct B**: Contains a `double`, a `char`, an `int`, and then another `char`.
   - **Struct C**: Contains an `int`, a `double`, and two `char` variables together.

2. **Predict Sizes**: Before writing any code, manually calculate and write down your predictions for the size of each struct. Consider the alignment requirements for each type on your platform (typically, a `char` requires 1 byte, an `int` requires 4 bytes, and a `double` requires 8 bytes, but alignment rules can increase the sizes).

3. **Write a Program**: Write a C++ program that defines the structs and prints out the size of each using the `sizeof` operator. For example:

   ```cpp
   #include <iostream>
   
   struct StructA {
       char a;
       int b;
       char c;
       double d;
   };
   
   // Define StructB and StructC similarly
   
   int main() {
       std::cout << "Size of StructA: " << sizeof(StructA) << " bytes\n";
       // Print sizes for StructB and StructC
       return 0;
   }
   ```

4. **Compare and Analyze**: Compare your predicted sizes with the actual sizes printed by the program. For any differences, analyze why the actual size differs from your prediction. Consider the padding added for alignment.

5. **Modify Structs** (Bonus): As a bonus challenge, try rearranging the members in one of the structs to reduce its size by minimizing padding. Predict the size of the modified struct, verify it with `sizeof`, and explain the difference.

6. **Reflection**: Reflect on how understanding the size and alignment of structs can impact memory usage in real-world applications, especially those with a large number of instances in memory at once.

### Submission Requirements:

- Include your predicted sizes and the rationale behind them.
- Provide the source code of your C++ program.
- Document the actual sizes reported by your program and any discrepancies from your predictions.
- If you attempted the bonus challenge, explain your approach and the results.
- Reflect on what you learned from this challenge regarding struct padding, alignment, and memory usage.

This challenge will test your understanding of struct memory layout in C++, including how different compilers and platforms might handle padding and alignment. It's a practical exercise that has implications for performance optimization and memory management in software development.