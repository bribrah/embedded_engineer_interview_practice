## Challenge: Implement a Lightweight Command Parser To Expand Software UART

The task is to design and implement a lightweight command parser for an embedded system that can interpret and act upon a set of predefined commands.

### Requirements:

1. **Command Definitions**: Define a small set of commands that the system can recognize. Each command should have a unique identifier or name. Example commands could be `START`, `STOP`, `SET <parameter> <value>`, and `STATUS`.

2. **Parsing Logic**: Implement the logic to parse incoming strings and identify them as one of the predefined commands. The parser should be able to handle variations in case sensitivity and ignore leading/trailing whitespace.

3. **Command Execution**: For each recognized command, implement a stub function that simulates the execution of the command. For instance, printing a message to indicate what action would be taken.

4. **Error Handling**: If an unrecognized command is received, the parser should provide a meaningful error response.

5. **Use Google Test and Cmake for Test Suite**

### Bonus Points:

- **Parameter Extraction**: For commands that include parameters (like `SET <parameter> <value>`), extract and print the parameter name and value as part of the command execution.
- **Dynamic Command Registration**: Create a mechanism that allows for commands to be dynamically registered or unregistered with the parser during runtime.
- **Resource Efficiency**: Optimize the parser for low memory usage and minimal processing overhead, considering the constraints of typical embedded systems.

## Test Cases

### 1. Test Valid Commands
- **Purpose**: Ensure the parser correctly identifies and executes valid commands without parameters.
- **Test Cases**:
    - `START`
    - `STOP`
- **Expected Behavior**: The parser should execute the corresponding action for each command, such as printing "Starting system" for `START` and "Stopping system" for `STOP`.

### 2. Test Commands with Parameters
- **Purpose**: Verify that the parser correctly handles commands with parameters, extracting and utilizing the parameters as intended.
- **Test Cases**:
    - `SET time 12:00`
    - `SET date 2024-02-07`
- **Expected Behavior**: The parser should recognize the `SET` command and print the parameter and value, e.g., "Setting time to 12:00" for the first test case.

### 3. Test Case Sensitivity
- **Purpose**: Determine whether the parser correctly handles commands in various cases (upper, lower, mixed).
- **Test Cases**:
    - `start`
    - `sTop`
    - `SeT time 14:00`
- **Expected Behavior**: Depending on your design decision (case-sensitive vs. case-insensitive), the parser should either execute the commands as if they were in the correct case or return an error for unrecognized commands.

### 4. Test Leading/Trailing Whitespace
- **Purpose**: Check if the parser correctly trims leading and trailing whitespace around commands and parameters.
- **Test Cases**:
    - `  START `
    - `SET  date   2024-02-07  `
- **Expected Behavior**: The parser should ignore extra whitespace and execute the commands as if they were entered without it.

### 5. Test Invalid or Unrecognized Commands
- **Purpose**: Ensure the parser appropriately handles commands that are not recognized or are invalid.
- **Test Cases**:
    - `JUMP`
    - `SET time` (missing parameter)
- **Expected Behavior**: The parser should print an error message indicating the command is unrecognized or incorrect usage for commands missing parameters.

### 6. Test Empty and Garbage Input
- **Purpose**: Assess how the parser deals with empty inputs or nonsensical input strings.
- **Test Cases**:
    - ``
    - `asdfghjkl`
- **Expected Behavior**: The parser should either ignore empty input without effect or report an error for garbage inputs indicating an unrecognized command.

### 7. Test Dynamic Command Registration and Unregistration
- **Purpose**: If your parser supports dynamic command registration/unregistration, test this functionality.
- **Test Cases**:
    - Register a new command `ECHO` dynamically and then call it.
    - Unregister a previously registered command and then attempt to call it.
- **Expected Behavior**: For dynamic registration, the new command should be recognized and executed. For unregistration, the parser should treat the command as unrecognized after it's removed.

### Implementing Test Cases
In a real development environment, you'd implement these test cases either as unit tests using a testing framework (like Google Test for C++) or as part of an integrated test suite that runs on the embedded device itself, printing results to a serial console or similar interface.

This suite of test cases ensures comprehensive coverage of the command parser's functionality, helping to identify and correct issues related to command parsing, execution, and error handling.

