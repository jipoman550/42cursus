# C++ - Module 00
**Namespaces, classes, member functions, stdio streams, initialization lists, static, const, and more.**

## 📝 Introduction
This project is the starting point of the C++ journey to learn the basic concepts of **Object-Oriented Programming (OOP)**. Moving beyond the familiar C language, you will learn new concepts step by step while adhering to the C++98 standard.

## 🛠️ General Rules
Strict rules that must be followed while completing the assignments.

### 1. Compilation
* **Compiler**: `c++`
* **Flags**: `-Wall -Wextra -Werror`
* **Standard**: Adding the `-std=c++98` flag must not cause compilation issues.

### 2. Naming Conventions
* **Directories**: `ex00`, `ex01`, ..., `exn`
* **Class Names**: Must follow the **UpperCamelCase** format.
* **Files**: Header and source file names must exactly match the class name. (e.g., `ClassName.hpp`, `ClassName.cpp`)

### 3. Forbidden & Allowed
* **Forbidden Functions**: The use of `*printf()`, `*alloc()`, and `free()` is strictly forbidden. (0 points if violated)
* **Forbidden Keywords**: The `using namespace <ns_name>` and `friend` keywords cannot be used without explicit permission. (**-42 points** if violated)
* **STL Restricted**: The use of containers (vector, list, map, etc.) and algorithm headers is forbidden until Module 08. (**-42 points** if violated)
* **Header Files**: Placing non-template function implementations in headers is forbidden, and **Include Guards** must be included.

---

## 🔊 Exercise 00: Megaphone
A step to practice standard input/output streams (`iostream`) and string manipulation.

### Objectives
* Converts all input string arguments to uppercase and prints them.
* If there are no input arguments, prints a specific predefined noise message.

### Key Concepts
* **`std::cout` & `std::endl`**: C++ style I/O replacing C's `printf`.
* **`std::toupper`**: Understanding how to convert characters to uppercase.
* **Namespace `std`**: The habit of explicitly using the `std::` prefix without `using namespace`.

### Usage
```bash
$ make
$ ./megaphone "shhhhh... I think the students are asleep..."
SHHHHH... I THINK THE STUDENTS ARE ASLEEP...
$ ./megaphone Damnit " ! " "Sorry students, I thought this thing was off."
DAMNIT ! SORRY STUDENTS, I THOUGHT THIS THING WAS OFF.
$ ./megaphone
* LOUD AND UNBEARABLE FEEDBACK NOISE *
```

### 💡 Deep Dive: Megaphone Core Q&A

#### **Q1. Why use `std::cout` instead of `printf`?**
* **Answer**: C++'s standard output stream `std::cout` guarantees **Type-safety**. Unlike `printf`, it prevents runtime errors caused by incorrect format specifiers (`%d`, `%s`, etc.), and through the `<<` operator overloading, it can flexibly print various data types.

#### **Q2. What is a Namespace, and why attach `std::`?**
* **Answer**: A namespace is a logical space to **prevent name collisions** of identifiers (functions, classes, etc.). `std` is the namespace containing all the features of the C++ Standard Library. Explicitly stating `std::` clarifies that the identifier belongs to the standard library, solving naming conflicts with other libraries.

#### **Q3. What is the difference between `std::endl` and `\n`?**
* **Answer**: While `\n` simply prints a newline character, `std::endl` performs a newline and simultaneously **forces a flush** of the output buffer. Therefore, `std::endl` is advantageous when you need to check the output in real-time, but when outputting large amounts of data, using `\n` might be more efficient for performance.

### 🔍 C++ Basic Syntax

#### **For Loop Structure**
`for (initialization; condition; increment)`
1. **initialization**: Executed once at the start of the loop (variable initialization).
2. **condition**: Evaluated before each loop starts (executes only if true).
3. **increment**: Executed after the body (updates variable values).

#### **Standard Library (std::)**
- **`std::cout`**: Standard output stream object (Type-safe output).
- **`std::endl`**: Newline + output buffer flush.
- **`std::toupper`**: Function that converts a character to uppercase.

#### **Safe Truncation & Casting**
- **`(unsigned char)`**: `std::toupper` can cause undefined behavior with negative inputs. To prepare for cases where `char` is signed, it is safely cast to a positive range (`unsigned char`) before being passed.
- **`(char)`**: The return type of `std::toupper` (`int`) is cast back to a character format for output.

#### **Operator Overloading**
- **Definition**: Redefining existing operators (`+`, `-`, `<<`, etc.) for specific classes or types.
- **std::cout and <<**: Redefined the bitwise shift operator `<<` as the 'output stream insertion operator'.
- **Advantages**:
  1. **Automatic Type Recognition**: The compiler determines the data type and calls the appropriate overloaded function.
  2. **Readability**: Enables intuitive code writing without format specifiers.

---

## 📖 Exercise 01: My Awesome PhoneBook
A step to implement an 80s-style, clunky but awesome phonebook software. Deeply covers class design, object lifecycle (constructors and destructors), and standard I/O control.

### Objectives
* **Save up to 8 contacts**: Can save a maximum of 8 contacts. From the 9th contact onwards, the oldest contact is overwritten with new information (Circular Buffer structure).
* **No dynamic allocation**: Implemented using static arrays without dynamic memory allocation such as `new` or `delete`.
* **Command processing**: The program receives and executes three commands: `ADD`, `SEARCH`, and `EXIT`.

### Class Structure
* **`Contact` Class**: The unit that holds individual contact information.
	* Stores first name, last name, nickname, phone number, and darkest secret.
	* For data protection, attributes are designed as `private` and functions as `public`.
* **`PhoneBook` Class**: Manages the array of `Contact` objects and controls the entire system.

### Key Features
* **`ADD`**: The user inputs information field by field. If left blank, it prompts for input again to maintain data integrity.
* **`SEARCH`**: Prints the saved list in the order of index, first name, last name, and nickname in a 10-character wide table format.
	* Strings longer than 10 characters are truncated to 9 characters and appended with a dot (`.`) to maintain the format.
	* After outputting the list, selecting a specific index displays all detailed information of that contact.
* **`EXIT`**: Terminates the program, and all saved contact information is permanently lost.

### Key Concepts (Lessons Learned)
* **Constructors & Destructors**: Learned the concept of special member functions that initialize variables when an object is created and perform cleanup when it is destroyed.
* **`const` Member Functions**: Improved code safety and reliability by adding `const` to functions that only read and do not modify the object's internal data.
* **`std::setw` & `std::right`**: Learned formatting techniques using the `<iomanip>` header for text alignment and fixed column widths.
* **Objects and Instances**: Understood the relationships between actual entities created in memory based on the blueprint called a class.

### Usage
```bash
$ make
$ ./phonebook
Welcome to My Awesome PhoneBook!
Enter command (ADD, SEARCH, EXIT): ADD
Enter First Name: Bjarne
Enter Last Name: Stroustrup
...
Successfully added!
Enter command (ADD, SEARCH, EXIT): SEARCH
|     index|first name| last name|  nickname|
|         0|    Bjarne|Stroustrup|    cpp_god|
Enter index to display details: 0
First Name     : Bjarne
Last Name      : Stroustrup
...
Enter command (ADD, SEARCH, EXIT): EXIT
The program quits and the contacts are lost forever!
```

### 📚 Study Notes & Core Concepts

#### 1. OOP Design

* **Reason for separating classes (`Contact` vs `PhoneBook`)**:
	* **Separation of Concerns**: `Contact` has the responsibility of storing and printing individual information (business card), while `PhoneBook` manages the contact array and controls the circular logic (business card holder).
	* **Encapsulation and Data Protection**: By hiding information in `private`, data is prevented from being mixed up or arbitrarily modified from the outside. Stability is increased by communicating only through allowed methods (`public` functions).
* **Member Variable Naming Convention (`_`)**:
	* Added an underscore (`_`) in front of member variables to visually distinguish them from parameters or local variables instantly. (e.g., `_firstName = firstName`)
	* **Note**: Used the `_firstName` (underscore + lowercase) format instead of `_FirstName` (underscore + uppercase) to avoid collisions with system reserved words.

#### 2. C++ Core Syntax
* **Constructors and Destructors**:
	* **Constructor**: Automatically called when an object is created in memory to initialize variables.
	* **Destructor**: Called when the object's life ends. Since dynamic allocation is not used in this assignment, only the basic form is provided.
* **`const` Member Functions**:
	* By appending `const` after the function declaration, it guarantees that the function is 'read-only' and will never change the object's state (member variables).
	* This prevents unintended data modifications and allows the function to be called on constant objects.
* **Class vs Object vs Instance**:
	* **Class**: The mold (blueprint).
	* **Object**: The actual entity allocated in memory.
	* **Instance**: A term used to emphasize the 'relationship' of being born from a specific class.

#### 3. Implementation Details
* **Circular Buffer Logic**:
	* Utilized `% 8` (Modulo operation) without a separate deletion logic so that if the index exceeds 8, it automatically overwrites starting from index 0.
* **Text Formatting**:
	* Used `std::setw(10)` and `std::right` from `<iomanip>` to align to a 10-character wide right-aligned table format, and applied logic to print only 9 characters followed by a `.` if it exceeds 10 characters.

### 💬 Evaluation FAQ

**Q: Why use `std::getline` instead of `std::cin >>`?**
* **A**: `std::cin >>` stops reading when it encounters whitespace (space, tab), but `std::getline` reads the entire line until a newline character (`\n`) is met. Because names or nicknames in a phonebook can contain spaces, `std::getline` was used to prevent data omission.

**Q: How did you ensure index circularity?**
* **A**: The remainder of the total input count divided by the array size of 8 (`_totalCount % 8`) was used as the index, so when the 9th input arrives, it is designed to automatically point to index 0.

**Q: How did you handle `Ctrl+D` (EOF) during input?**
* **A**: `std::getline` returns `false` when it encounters EOF. By checking this with a conditional statement, defensive coding was applied so the program stops input or terminates safely without falling into an infinite loop.

**Q: Why didn't you use `using namespace std;`?**
* **A**: To prevent Naming Collisions in large-scale projects. I explicitly specified `std::` every time to build the habit of explicitly declaring where tools come from (the standard library, `std`) and to avoid polluting the namespace.

---

## 🏦 Exercise 02: The Job Of Your Dreams
This assignment is a **Reverse Engineering** step to restore the working logic based on the provided blueprint (`Account.hpp`) and test results (log file).

### Objectives
* **Restore `Account.cpp`**: Write the source code that generates the exact same output as the log file (`19920104_091532.log`) without modifying the provided `Account.hpp` and `tests.cpp`.
* **Implement Bank System Logic**: Real-time management of overall bank statistics (total balance, total number of deposits/withdrawals, etc.) in addition to individual account transactions.

### Key Features
* **Static Member Management**: Utilizes `static` variables and functions to handle bank-wide data shared by all objects.
* **Timestamp Output**: Prints the current time in `[YYYYMMDD_HHMMSS]` format at the beginning of every log line via the `_displayTimestamp` function.
* **Transaction Validation**: Includes exception handling logic that prints a `refused` message and rejects the transaction if the balance is insufficient during withdrawal.

### Key Concepts (Lessons Learned)
* **`static` Member Variables & Functions**: Learned how to define data and functionality belonging to the class itself rather than class instances, and how to initialize them in the `.cpp` file.
* **Member Initializer List**: Learned the syntax (`: variable(value)`) to efficiently initialize member variables before the constructor body executes.
* **Encapsulation and Getters**: Understood the role and importance of `get...()` and `check...()` functions (Getters) for safely reading `private` data.
* **`const` Correctness**: Developed the habit of explicitly adding `const` to functions that do not alter the object's state, ensuring code stability.

### Usage & Testing
```bash
# Compile and run
$ make
$ ./account > my_log.log

# Compare the logic results excluding the timestamp (Based on Linux/Mac)
$ diff <(sed 's/\[[^]]*\] //' my_log.log) <(sed 's/\[[^]]*\] //' 19920104_091532.log)

$ diff <(cut -d ' ' -f2- my_log.log) <(cut -d ' ' -f2- 19920104_091532.log)
# If nothing is printed out, the log match is successful!
```

### 📚 Study Notes & Core Concepts

#### 1. **Static Member Variables**
- **Sharing**: Belongs to the class itself rather than a specific object, and all instances share the same memory space.
- **Lifecycle**: Allocated when the program starts, destroyed when it ends (Data Segment area).
- **Initialization Location**: Must be performed in the `.cpp` file.
  - Reason: To prevent Duplicate Definition errors when initialized in a header file.
- **Encapsulation**: Has the same lifespan as global variables, but declared inside a class to prevent unrestricted access.

Cadets, following static member variables, I have organized **static member functions** and the **difference between `static` in C/C++** below so you can easily paste them into Obsidian or `README.md`.

This content provides perfect logical defenses, especially for the `ex02` evaluation when asked, "Why is this function `static`?".

#### 2. **Static Member Functions**

- **Object Independence**: A function belonging to the **class itself**, not a specific instance. It can be called like `Account::getNbAccounts()` without creating any objects.
- **Absence of `this` pointer**: Unlike regular member functions, the object's address (`this`) is not passed when called.
- **Access Restriction**: Because there is no `this`, it **cannot access regular member variables (instance variables)** whose object it doesn't know, and can only handle static member variables.
- **Reason for Use**:
	- Used to perform 'class-wide statistics' or 'utility functions' regardless of individual object states.
	- Optimizes memory and performance by calling functions without unnecessary object creation.

#### 3. **The Two Faces of the `static` Keyword: C vs C++**

C++ inherits the `static` properties of the C language while adding a new definition tailored to the concept of 'class'.

| Distinction | C Language (Internal Linkage) | C++ (Class Scope) |
| :--- | :--- | :--- |
| **Location** | Outside the class (Global scope) | Inside the class |
| **Meaning** | **File-level encapsulation** | **Object-level independence** |
| **Effect** | Inaccessible from outside the file (`.c`/`.cpp`) | Accessible by class name without object creation |
| **Main Purpose** | Prevent naming collisions with other files | Manage logic/data shared by all instances |

- **C-Style Static**: A declaration that "This function/variable will **only be used within this file**".
- **C++ Class Static**: A declaration that "This function/variable will be used as **belonging to the class, regardless of objects**".

#### 4. **Why use Static Member Functions?**

Even though they could simply be made global functions, the reasons for declaring `static` functions inside a class to be used "without an object" are as follows:

1. **Logical Validity**
	- **Solving questions awkward to ask objects**: In the bank system of `ex02`, "What is your balance?" should be asked to an individual account (object), but "How many total accounts are there currently?" is a question that must be asked to the **entire bank system (class)**, not a specific account.
	- If there were no `static` function, an illogical situation would arise where you would have to open an unnecessary account (create an object) just to find out the overall information.

2. **Resource Efficiency**
	- **Preventing unnecessary instantiation**: Allocating memory and calling a constructor to create an object just to use a single function is a waste. Using a `static` function allows you to call the function directly without object creation, optimizing memory and performance.

3. **Structural Management and Namespace Organization**
	- **Grouping related features**: If made as a global function, there is a high risk of name collision with other libraries later. However, placing it inside a class like `Account::displayTimestamp()` makes it clear which class this function relates to, maintaining **encapsulation** while also preventing naming collisions. (Using a class as a kind of 'name bag')

#### 5. **Role of Constructors and Destructors**

The birth and death of objects affect not only the state changes of individual objects but also the shared data (Static) of the entire class.

1. **Constructor: Object Birth and System Registration**
	- **Individual Initialization**: Sets the unique index (`_accountIndex`) and initial balance (`_amount`) that each account (object) will have.
	- **Global Statistics Update**: Every time a new account is created, it increases the total number of accounts (`_nbAccounts`) and adds the initial deposit to the total deposits (`_totalAmount`).
	- **ID Assignment Logic**: Applied a design that grants sequential unique IDs starting from 0 by executing `_accountIndex(_nbAccounts)` first and then `_nbAccounts++`.

2. **Destructor: Object Demise and Cleanup**
	- **Log Recording**: Right before the object is released from memory, it outputs the last state (index, amount) of the account to record its closure (`closed`).
	- **Resource and Statistics Cleanup**: For the logical completeness of the program, processing such as reducing the total number of accounts (`_nbAccounts`) or deducting the remaining balance from the total amount is possible upon destruction. (In this assignment, they are sequentially destroyed when the program ends).

#### 6. **Member Initializer List**

When initializing member variables in a constructor, it is recommended to use the **initializer list** instead of assigning inside the constructor body (`{ }`).

- **Efficiency**: Rather than assigning a value after creating the variable, it **initializes at the same time as creation**, reducing unnecessary operations.
- **Necessity**: `const` member variables or reference (`&`) members must strictly be initialized in the initializer list.
- **Execution Order**: You must note that the initialization proceeds **in the order the member variables are declared in the class header (.hpp)**, not the order written in the initializer list. "If the initialization of one member variable is used for another, writing code relying only on the order in the initializer list can lead to unexpected garbage values if the declaration order changes."

#### 7. **const Member Functions**

- **Definition**: Appending the `const` keyword after a function declaration to specify that the function does not alter the object's state.
- **Guarantees**:
  - Forbids all acts of assigning values to member variables inside the function.
  - Forbids calling other non-const member functions.
- **Necessity**:
  - **Data Protection**: Prevents unintended value modifications in simple retrieval functions (Getters).
  - **Constant Object Support**: Objects declared as `const` can only call `const` member functions, making it an essential design convention.

| Distinction | Regular Member Function | `const` Member Function |
| :--- | :--- | :--- |
| **Modify Member Variables** | Possible | **Impossible (Compile Error)** |
| **this Pointer Type** | `Account* const` | `const Account* const` |
| **Called from Constant Object** | Impossible | **Possible** |

#### 8. **Static Utility Function: `_displayTimestamp`**

-   **Role**: Outputs the current system time in the `[YYYYMMDD_HHMMSS]` format according to the standard log format.
-   **Reason for static design**:
    1.  **Independence**: It is an independent logic that does not need to reference the state of an individual object (`this`).
    2.  **Compatibility**: It must be callable from other static member functions within the class (e.g., `displayAccountsInfos`), so it is declared as `static`.
    3.  **Encapsulation**: It could be made as a global function outside the class, but since it is a log format exclusive to the `Account` class, it is confined to `private static` inside the class for management.

#### 9. **Iterator**
- **Definition**: A pointer-like object that allows traversing and accessing elements within a container.
- **Advantages**: Allows handling data in a consistent manner regardless of the container's internal structure (arrays, lists, etc.) (**Consistent Interface**).
- **Key Functions**:
    - `container.begin()`: Returns the position of the first element.
    - `container.end()`: Returns a past-the-end (fictional) position after the last element.
- **Key Operations**:
    - `*` (Dereference): Accesses the value of the element being pointed to.
    - `++` (Increment): Moves to the next element.
    - `->` (Arrow): Accesses a member of the object being pointed to.

---

## 📁 Directory Structure Update
* `ex00/`: Megaphone program and Makefile.
* `ex01/`: My Awesome PhoneBook program.
* `ex02/`: The Job Of Your Dreams (Bank account management system restoration).