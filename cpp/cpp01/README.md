# 📖 C++ - Module 01
**Memory allocation, pointers to members, references and switch statements**

## 📝 Introduction
This project lays the foundation for **memory management**, one of the most crucial concepts in C++. Beyond simply creating objects, you will learn to decide where in memory (Stack vs. Heap) to allocate them, and you will study **references**, an advanced form of pointers, and **pointers to member functions**.

## 🛠️ General Rules
These are strict rules that must be followed while completing the assignments. If you break these rules, not only will your skills not improve, but your score will be disastrous!

### 1. Compilation
* **Compiler**: `c++`
* **Flags**: `-Wall -Wextra -Werror`
* **Standard**: Must compile perfectly even with the `-std=c++98` flag.

### 2. Naming Conventions
* **Directories**: `ex00`, `ex01`, ..., `exn`
* **Class Names**: Must follow the **UpperCamelCase** format.
* **Files**: Header and source file names must match the class name (e.g., `Zombie.hpp`, `Zombie.cpp`).

### 3. Forbidden & Allowed
* **C functions are forbidden**: Using `*printf()`, `*alloc()`, `free()` will result in a score of **0**.
* **Keywords**: You cannot use `using namespace <ns_name>` or the `friend` keyword without explicit permission. (Violation: **-42 points**)
* **STL Restriction**: Until Module 08, the use of containers (vector, list, map, etc.) and algorithm headers is forbidden. (Violation: **-42 points**)
* **Memory Management**: Memory allocated with `new` must be deallocated with `delete` to prevent **Memory Leaks**.

---

## 🧟 Exercise 00: BraiiiiiiinnnzzzZ
This exercise is about developing the ability to decide on a memory allocation method (Stack vs. Heap) based on an object's life cycle (Scope).

### Objectives
* Implement a `Zombie` class and create appropriate zombie creation functions for different situations.
* Verify that the destructor is called correctly when an object is destroyed.

### Key Functions
* **`Zombie* newZombie(std::string name)`**: Allocates a zombie on the heap and returns it. Use this when the zombie needs to persist after the function ends.
* **`void randomChump(std::string name)`**: Allocates a zombie on the stack. This is efficient when you want to use the zombie only temporarily within the function and have it be destroyed automatically.

### 🚀 Usage & Testing

1.  **Compilation**
	Navigate to the `ex00` directory in your terminal and enter the `make` command.
	```bash
	$ make
	```
	If successful, an executable file named `braiiiiiiinnnzzzZ` will be created.

2.  **Execution**
	Run the created program to check the creation/destruction order of stack and heap zombies.
	```bash
	$ ./braiiiiiiinnnzzzZ
	```

3.  **Memory Leak Check**
	This is the most important step in the 42 assignments. Check if the destructor of the heap-allocated zombie was called via `delete` and if there are any memory leaks.
	*   **Linux:** `valgrind --leak-check=full ./braiiiiiiinnnzzzZ`

### 💡 Deep Dive

#### **Q1. When should I use heap allocation?**
*   **Answer**: Use it when an object needs to survive after the function that created it has finished, or when dealing with large data whose size isn't known at compile time. It uses the `new` keyword, and you must manually deallocate the memory with `delete`.

#### **Q2. What are the advantages of stack allocation?**
*   **Answer**: It's very easy and fast to manage. The system automatically reclaims the memory and calls the destructor as soon as the scope (defined by `{ }`) is exited. Because there's no risk of memory leaks, it's best to prioritize stack allocation whenever possible.

#### **Q3. Why make the destructor print the name?**
*   **Answer**: It's to visually confirm whether the programmer has deallocated memory at the appropriate time. If you don't `delete` a heap-allocated zombie, the message won't be printed until the program terminates, which signifies a memory leak.

#### **Q4. Is `Zombie z(name);` the same as `Zombie z = Zombie(name);`?**
*   **Answer**: The result might look the same, but there's a subtle difference. The first is **Direct Initialization**, which creates the object immediately. The second is **Copy Initialization**, which may involve creating a temporary object and then copying it. In the C++98 standard, the first method is recommended for performance and clarity.

#### **Q5. Why use `new` in C++ when C has `malloc`?**
*   **Answer**: `malloc` just allocates a block of memory, but `new` is an operator that **automatically calls the object's constructor**. This means it allocates memory and prepares the object for use (initialization) at the same time, which is essential to C++'s object-oriented philosophy. Conversely, `delete` calls the **destructor** before deallocating memory to help with cleanup.

#### **Q6. What happens if I don't `delete` after a function ends?**
*   **Answer**: Memory allocated on the heap is an area you, the programmer, have promised to manage directly. Therefore, if you don't call `delete`, the object's **destructor will not be called** even when the program ends, leading to a memory leak. If you don't see the "Destroyed" message, this is what's happening.

#### **Q7. Why is the function named `randomChump`?**
*   **Answer**: "Chump" is slang for an extra or an easy target. This function creates a zombie on the **stack**, so it disappears as soon as the function ends. The name wittily reflects the allocation method's nature: this isn't a main character zombie that sticks around, but a "disposable" one that appears briefly and then vanishes.

#### **Q8. Why use an initializer list (`: name(name)`) instead of the constructor body (`{}`)**?
*   **Answer**: In C++, object creation is a two-step process: 'initialization' and 'assignment'.
*   **Efficiency (Initialization vs. Assignment)**: Using an initializer list (`: name(name)`) sets the value as the object is being created in memory. In contrast, assigning in the body (`{ name = name; }`) first creates the object with a default value and then overwrites it, which is less efficient.
*   **Required Situations**: Using an initializer list is **mandatory**, not optional, in the following cases:
	1.  **`const` member variables**: Constants must be assigned a value upon creation; they cannot be modified (assigned to) in the constructor body.
	2.  **Reference (`&`) member variables**: References must point to something upon declaration, so they must be defined in the initializer list.
	3.  **Class members without a default constructor**: If a member variable is an object of another class that doesn't have a no-argument constructor, you must specify how to initialize it in the list.
*   **Readability**: It separates the data setup that forms the basis of the object from the logic that runs in the `{}` body, making the code's intent clearer.
```cpp
/* Zombie.cpp */

Zombie::Zombie(std::string name) : name(name) // Initializer list: name is given at birth
{
	// Constructor body: for logic to be executed after initialization
}
```

#### **Q9. In `Zombie::Zombie(std::string name) : name(name)`, why use the same name twice?**

*   **Answer**: This is the cleanest way to solve the 'Name Shadowing' problem that occurs in C++ when a **member variable** and a **parameter** have the same name.
*   **Division of Roles**:
	*   **The first `name` (after the colon)**: Refers to the **member variable** declared inside the class (usually `private`). The compiler is designed to always recognize names in this position as member variables.
	*   **The second `(name)` (in parentheses)**: Refers to the **parameter** passed to the constructor.
*   **Advantages**:
	*   It directly injects the argument's value into the member variable at the moment of object creation, without an extra assignment operation like `this->name = name;`.
	*   You don't need to force different names like `newName` or `pName`, which helps maintain the clear meaning of the variable (setting the name).

```cpp
/* Zombie.cpp */

// (std::string name) <- 'parameter' passed from outside
Zombie::Zombie(std::string name)
	: name(name) // First name: class's member variable / Second (name): received parameter
{
	// Since I put 'what you gave me' (parameter) into 'my pocket' (member variable)
	// at birth via the initializer list, this body can be left empty.
}
```

#### **Q10. Is there a special reason to prefix member variables with an underscore (`_`)?**

*   **Answer**: Yes, this is a **Naming Convention** used to improve code readability and prevent mistakes.
*   **Key Benefits**:
	1.  **Visual Distinction**: Anywhere you see `_name` in the code, you immediately recognize, "This is a class member variable, not a local variable in a function."
	2.  **Avoid `this->` pointer**: If the member variable and parameter names are different (`_name` vs `name`), you can assign them without confusion (`_name = name;`) instead of writing the longer `this->_name = name;`.
	3.  **Clarity in Initializer Lists**: Writing `_name(name)` makes it much more intuitive which one belongs to the class and which is the value received from outside.
*   **⚠️ Caution (System Reserved Words)**:
	*   In the C++ standard, identifiers starting with an **underscore + uppercase letter (`_Name`)** or a **double underscore (`__name`)** are reserved for the compiler or standard library.
	*   Therefore, to avoid conflicts, it's safer to use the **underscore + lowercase letter (`_name`)** format or append an underscore (`name_`).

```cpp
/* Zombie.hpp */

class Zombie {
private:
	std::string _name; // Member variable starts with _ (Readability UP!)

public:
	Zombie(std::string name) : _name(name) {} // Initializer list becomes much clearer
};
```

### 🧠 Memory Structure Revisited (Memory Segments)

Understanding where objects are stored is the first step in C++ design.

*   **Stack**: Local variables, parameters. Automatically destroyed when `{}` scope is exited. (`randomChump`)
*   **Heap**: Dynamic memory allocated with `new`. Persists until `delete` is called. (`newZombie`)
*   **Data/BSS**: Where global and static variables are stored. Persists until the program terminates.

---

## 🧠 Exercise 01: Moar brainz!
This exercise is about learning to create an array of objects with a single allocation (`new[]`) and managing a large number of objects through a loop.

### Objectives
* Create a zombie horde with a single memory allocation.
* Name and initialize all allocated zombie objects.
* Safely deallocate the entire horde using `delete[]` and prevent memory leaks.

### Key Function
* **`Zombie* zombieHorde(int N, std::string name)`**:
	* Allocates `N` zombie objects at once with `new Zombie[N]`.
	* Calls a `setName()` function to set the name of all zombies to `name`.
	* Returns a pointer to the first zombie in the created horde.

### 🚀 Usage & Testing

1.  **Compilation**
	```bash
	$ cd ex01
	$ make
	```
	If successful, an executable file named `moar_braiiinz` will be created.

2.  **Execution**
	```bash
	$ ./moar_braiiinz
	```
	Check that all zombies announce their names and that the entire horde is destroyed ("Destroyed") when the program exits.

3.  **Memory Leak Check**
	Memory allocated with `new[]` must be deallocated with `delete[]`.
	*   **Linux:** `valgrind --leak-check=full ./moar_braiiinz`

### 💡 Deep Dive

#### **Q1. Why use Getters and Setters, and why is `setName` needed in ex01?**
*   **Answer**: They are used to protect (encapsulate) an object's internal data (`_name`) from being modified directly from the outside. The `new[]` operator can only call the **default constructor** (one with no arguments), so a **Setter (`setName`)** function is essential to assign names to the objects right after they are created.

#### **Q2. Between Getters and Setters, which should be avoided more, and why?**
*   **Answer**: **Setters** should be avoided more. Overusing setters allows the object's state to be changed freely from the outside, which breaks encapsulation and undermines the object's autonomy. It's better to establish the initial state through the constructor whenever possible.

#### **Q3. Do Getters and Setters always have to be created in pairs?**
*   **Answer**: No. For 'read-only' properties, you only create a getter. For 'set-only' properties not exposed to the outside, you only create a setter. They are used independently based on the design intent. However, it's a good habit to declare getters with **`const`** at the end of the function signature (Const Correctness) to indicate they don't modify the object.

#### **Q4. What's the difference between Getters/Setters and Shallow/Deep Copy?**
*   **Answer**: Getters/Setters are about **access control (Encapsulation)** to data, while Shallow/Deep Copy is about **memory management** when cloning an object. If a getter returns an internal pointer directly, it can lead to side effects similar to a 'shallow copy' by unintentionally giving away control, so caution is needed.

#### **Q5. Why put a `*` after a class name, like `Zombie*`?**
*   **Answer**: It signifies that the variable is a pointer that stores the **memory address** of the object. `new[]` returns the starting address of the allocated memory block, so a pointer is needed to store it. This allows you to access elements like an array, e.g., `horde[i]`.

#### **Q6. Why keep the constructor with an argument (`Zombie(std::string name)`) in ex01?**
*   **Answer**: Although it's not used in the current `zombieHorde` implementation, it's kept for the class's **versatility**. When creating a single zombie object, it's more efficient and cleaner to assign the name at the time of creation rather than calling `setName` separately.

---

## 🧠 Exercise 02: HI THIS IS BRAIN
This exercise is about understanding the syntactic differences between pointers and references and clearly grasping the relationship between memory addresses and values.

### Objectives
* Declare a pointer and a reference to a single string variable.
* Print the **memory address** and **actual value** of the variable in three ways (original, pointer, reference) for comparison.

### Key Concepts
*   **Pointer (`std::string*`)**: A variable that has its own memory space to store the address of another variable.
*   **Reference (`std::string&`)**: An **alias** for an existing variable. It does not occupy new memory space and refers directly to the original variable.

### 🚀 Usage & Testing

1.  **Compilation**
	```bash
	$ cd ex02
	$ make
	```
	If successful, an executable named `brainz` will be created.

2.  **Execution**
	```bash
	$ ./brainz
	```
	Check if the addresses of all three outputs match, and if their values are all "HI THIS IS BRAIN".

---

### 💡 Deep Dive

#### **Q1. Why are the addresses of the original variable, the pointer's target, and the reference all the same?**
*   **Answer**: Because the pointer variable (`stringPTR`) holds the original's **address** as its value, and the reference (`stringREF`) is just **another name** for the original variable itself. Therefore, `&stringREF` prints the address of the original variable `str`.

#### **Q2. What is the biggest difference between pointers and references?**
*   **Answer**:
	*   **Pointer**: An independent variable that stores an address, so it can be `NULL` and can be changed to point to a different address later.
	*   **Reference**: Must be **initialized at declaration** and, once initialized, it refers to that same variable for its entire life (cannot be reassigned). There's no concept of a `NULL` reference, making it safer.

#### **Q3. What are the advantages of using references?**
*   **Answer**: They handle addresses like pointers but can be used with the syntax of regular variables, which improves readability. You don't need to use the dereference operator (`*`) repeatedly, and you can prevent mistakes from pointer arithmetic or `NULL` access errors.

#### **Q4. What is the difference between printing `&stringREF` and `stringPTR`?**
*   **Answer**: `stringPTR` prints the **value it holds (the address of the original)**, whereas `&stringREF` directly prints the **address of the original object** it refers to. The result is the same, but it semantically shows that the reference is 'identified' with the original.
- "If you look at the code, there's a commented-out part that prints the address of `stringPTR` itself. If you uncomment it, you'll see that the pointer variable `stringPTR` also has its own place in memory. The biggest difference is that a reference doesn't have its own separate address!"

---

## 🧠 Exercise 03: Unnecessary violence
This exercise is about developing the design skill to decide whether to use a **pointer** or a **reference** for a member variable when designing a class.

### Objectives
* Implement three classes: `Weapon`, `HumanA`, and `HumanB`.
* Design `HumanA` and `HumanB` to own a `Weapon` object in different ways.
* Verify that changes to the weapon's state from the outside are reflected in real-time by the objects that own it.

### Key Concepts
*   **HumanA (using a Reference)**: Must be given a weapon at the time of creation and uses only that weapon for its entire life. Since a reference cannot be `NULL`, it doesn't allow for an unarmed state.
*   **HumanB (using a Pointer)**: Can be created without a weapon (`NULL`) and can later be equipped with or change weapons.
*   **Const Reference Return**: The `getType()` function returns a reference to the original string to optimize performance but adds `const` to prevent external modification.

### 🚀 Usage & Testing

1.  **Compilation**
	```bash
	$ cd ex03
	$ make
	```
	If successful, an executable named `violence` will be created.

2.  **Execution**
	```bash
	$ ./violence
	```
	Check that `HumanA` attacks immediately, and that `HumanB`'s messages are different before and after being equipped with a weapon.

---

### 💡 Deep Dive

#### **Q1. Why does HumanA use a reference (`&`) as a member?**
*   **Answer**: As per the assignment requirements, `HumanA` must receive a weapon at creation and always be armed. Since a reference must be initialized upon declaration and cannot be `NULL`, it's the most suitable tool to enforce this "mandatory ownership" relationship.

#### **Q2. Why does HumanB use a pointer (`*`) as a member?**
*   **Answer**: `HumanB` can be created in an unarmed state. A pointer can have a `NULL` value, which can represent "no weapon," and it provides the flexibility to change the object it points to (its address) later via `setWeapon`.

#### **Q3. Why does `getType()` return `const std::string&`?**
*   **Answer**:
	1.  **Performance**: Returning a `std::string` object by value creates a new copy of the string, but returning a reference just passes an address, saving memory and time.
	2.  **Safety**: Adding `const` protects the original weapon's type from being modified by the code that reads the information.

#### **Q4. Why must HumanA's constructor use an initializer list?**
*   **Answer**: In C++, a **reference member variable** must be initialized at the moment the object is created. Assigning it a value inside the constructor body (`{}`) is a 'modification' of an already created variable, so references and `const` variables must be linked to their values at birth via an **initializer list**.

#### Tip
"In this assignment, you added an `if (_weapon)` check in `HumanB`'s `attack()` function, right? That's an excellent habit. A pointer always carries the risk of being `NULL`, so a check is always necessary. In contrast, the advantage of `HumanA`'s reference is that you can use it right away without that worry!"

---

## 📂 Exercise 04: Sed is for losers
This exercise is about implementing your own version of the `sed` tool using C++ **File Streams** and **string manipulation**, helping you understand the abstraction principles of the standard library.

### Objectives
* Design a string replacement logic without using the `std::string::replace` function.
* Learn C++-style file I/O using `ifstream` and `ofstream`.
* Practice defensive coding for various exceptional situations like file open failures, argument errors, and empty string handling.

### Key Concepts
*   **RAII (Resource Acquisition Is Initialization)**: Manages resources (like file handlers) automatically through the object's life cycle to prevent resource leaks.
*   **Manual String Replacement**: Implement a replacement algorithm using a combination of `find()`, `substr()`, and `append()`.
*   **Stream Buffering**: Use `rdbuf()` and `stringstream` to efficiently handle large amounts of data.

### 🚀 Usage & Testing

1.  **Compilation**
	```bash
	$ cd ex04
	$ make
	```
	If successful, an executable named `sed_is_for_losers` will be created.

2.  **Execution**
	```bash
	$ ./sed_is_for_losers <filename> <s1> <s2>
	```
	A file named `<filename>.replace` will be created with all occurrences of `s1` in `<filename>` replaced by `s2`.

---

### 💡 Deep Dive: C++ Standard Library and Its Principles

#### **Q1. Why is the assignment named "Sed is for losers"?**
*   **Answer**: It contains a challenging message: don't just rely on powerful pre-made tools (`sed`) or convenient functions (`std::string::replace`), but try to **design the logic from the ground up**, including string searching, memory reallocation, and stream control.

#### **Q2. How did you implement replacement without `std::string::replace`?**
*   **Answer**: I created a loop that uses `find()` to locate `s1` in the original string, `substr()` to cut out the content before the found position, and `append()` to concatenate the preceding content and `s2` into the result string. This process is repeated until `s1` is no longer found (`npos`).

#### **Q3. What are the advantages of C++ file handling compared to C?**
*   **Answer**: In C, if you don't manually close a `FILE*` pointer, a resource leak occurs. In C++, the `fstream` object's **destructor** automatically closes the file (RAII). Also, `std::string` manages its own memory size, making it safe from buffer overflow risks.

#### **Q4. What does the line `std::ifstream inputFile(filename.c_str());` mean?**
*   **Answer**: It's a statement that creates an **object** named `inputFile` of the `std::ifstream` class, and by passing the file path as an argument to its **constructor**, it commands the object to open the file at the moment of its creation.

#### **Q5. Why do you need to use `filename.c_str()`?**
*   **Answer**: The `ifstream` constructor in the C++98 standard cannot take a `std::string` directly as an argument; it can only accept a C-style string (`const char *`). Therefore, the `c_str()` member function is used as a translator to convert it.

#### **Q6. What's the difference between `std::string` and `std::stringstream`?**
*   **Answer**:
	*   **`string`**: Like a **water bottle** that holds data. Good for accessing values at specific locations.
	*   **`stringstream`**: Like a **pipe** through which data flows. It's optimized for combining various data types into one using the `<<` operator or for acting as a buffer to move entire file contents using `rdbuf()`.

#### **Q7. Why compare the result of `std::string::find()` with `std::string::npos`?**
*   **Answer**: `npos` is a special value that `find()` returns when it fails to find a matching string. If you use the result as an index without checking this value, you might access invalid memory. Therefore, you must always confirm success before proceeding with the next logic.

### 🛠️ Summary of Key Functions and Objects
*   **`std::cerr`**: An output stream specifically for error messages.
*   **`is_open()`**: Checks if a file was successfully opened.
*   **`rdbuf()`**: Provides direct access to a file's internal stream buffer for efficient data transfer.
*   **`str()`**: Extracts the data accumulated in a stream into a `std::string` format.
*   **`empty()`**: Intuitively checks if a string is empty.

---

## 🤬 Exercise 05: Harl 2.0
This exercise is about building an efficient and extensible function call system using **pointers to member functions** instead of numerous `if-else if-else` statements.

### Objectives
* Implement a `Harl` class to simulate four levels of complaint messages: DEBUG, INFO, WARNING, ERROR.
* Design a **'Dispatch Table'** using an array of pointers to member functions to call the appropriate member function based on the input string level.
* Adhere to object-oriented encapsulation principles by making the actual complaint logic `private` and the external calling interface `public`.

### Key Concepts
*   **Member Function Pointer**: A special type of pointer that stores the address (or more accurately, the offset within the class) of a function belonging to a class.
*   **Dispatch Table**: A design pattern where a table pre-links keys (strings) to actions to be performed (function pointers), allowing for immediate logic branching at runtime.

### 🚀 Usage & Testing

1.  **Compilation**
	```bash
	$ cd ex05
	$ make
	```
	If successful, an executable named `harl` will be created.

2.  **Execution**
	```bash
	$ ./harl
	```
	Check if the messages for each defined level are printed correctly and if a default message is printed for undefined level inputs.

---

### 💡 Deep Dive

#### **Q1. Why is the assignment named "Harl 2.0"?**
*   **Answer**: It originally used a meme named 'Karen', but was changed to the more neutral **Harl**. The **2.0** symbolizes the evolution from a simple conditional logic-based system to an 'advanced form' using pointers to member functions.

#### **Q2. What is the detailed meaning of the syntax `void (Harl::*funcs[])(void)`?**
*   **Answer**: It's the syntax for declaring an **array of pointers** that point to functions belonging to the `Harl` class, where the functions have a **return type of `void` and no parameters (`void`)**. Unlike regular function pointers, `Harl::*` must be used to specify that they are bound to a specific class scope.

#### **Q3. Why use complex syntax like `(this->*funcs[i])()` to call a member function pointer?**
*   **Answer**:
	1.  **Object Binding**: A member function cannot be executed with just an address; it needs the **address of the object (`this`)** on which to operate.
	2.  **Priority Protection**: The function call operator `()` has higher precedence than the member pointer operator `->*`. Therefore, you must use parentheses to first bind the object and the function pointer (`Binding`) before making the call.

#### **Q4. What are the practical benefits of using member function pointers over an `if-else` hell?**
*   **Answer**:
	1.  **Maintainability (OCP)**: If a new complaint level is added, you only need to add one line to the table (array) without modifying the existing `complain` function's logic.
	2.  **Readability**: The numerous conditional branches disappear, making the core logic of the code concise.
	3.  **Extensibility**: It is essential for implementing callbacks or state patterns where the function to be executed needs to be dynamically replaced.

#### Tip
"The technique of iterating through a string array (`levels[]`) and a function pointer array (`funcs[]`) with matching indices is a very common pattern in command processors for embedded systems or game engines. Getting familiar with this syntax means you're ready to handle C++'s powerful polymorphism!"

---

## 🔍 Exercise 06: Harl filter
This exercise is about building a filtering system that selectively prints logs of a certain level and above, using a `switch` statement and **intentional fall-through**.

### Objectives
* Reuse the `Harl` class implemented in **ex05** to extend its filtering capabilities.
* Determine the output range based on the level received as a command-line argument.
* Design a hierarchical execution logic based on conditions using a `switch-case` statement.

### Key Concepts
*   **Switch Statement**: A control statement that handles multi-way branching by comparing an integer or enum value. Since C++ strings cannot be compared directly, an indexing process is needed.
*   **Fall-through**: A technique where you omit the `break` at the end of a `case` statement to execute the subsequent `case` as well. This allows for efficient processing of hierarchically structured data.

### 🚀 Usage & Testing

1.  **Compilation**
	```bash
	$ cd ex06
	$ make
	```
	If successful, an executable named `harlFilter` will be created.

2.  **Execution**
	```bash
	$ ./harlFilter WARNING
	```
	Check if messages for the input level (`WARNING`) and all more severe levels (`ERROR`) are printed.

---

### 💡 Deep Dive

#### **Q1. Why use a `switch` statement instead of `if-else`?**
*   **Answer**: The purpose of this assignment is **'hierarchical filtering'**—printing all logs from a certain level upwards. The `switch` statement's characteristic of falling through to the next case when `break` is absent makes it possible to write much more concise and intention-clear code for this kind of sequential execution logic compared to `if-else`.

#### **Q2. What is the biggest logical difference compared to ex05?**
*   **Answer**:
	*   **ex05**: A '1:1 matching' approach where only **one single function** that exactly matches the input level is called.
	*   **ex06**: A 'hierarchical exposure' approach where **all higher-level functions** are executed sequentially, starting from the input level.

#### **Q3. What processing was done to put a string into a `switch` statement?**
*   **Answer**: A C++ `switch` statement can only take integer-family values as arguments. Therefore, I iterated through the `levels[]` array to find the index of the user-input string and then passed that **index number (int)** to the `switch` statement to handle the branching.

#### **Q4. What should be noted when using intentional fall-through?**
*   **Answer**: It must be clear whether a `break` was accidentally omitted or intentionally left out. It's conventional to leave a comment (e.g., `// fall-through`) for code readability and maintenance. Also, you must put a `break` in the last case (`ERROR`) to prevent unnecessary execution.

#### Tip
"In professional practice, it's common to set up logging systems to show all logs in `DEBUG` mode and only `ERROR`s in `PRODUCTION` mode. This `Harl filter` assignment is a great example of implementing the basic principles of such practical filtering logic using a `switch` statement!"

---

## 📁 Directory Structure
*   `ex00/`: Practice with zombie creation and memory allocation.
*   `ex01/`: Creating a zombie horde (`new[]`) and managing array memory.
*   `ex02/`: Understanding the concept of references.
*   `ex03/`: Class design using pointers vs. references.
*   `ex04/`: Implementing file streams and string replacement logic.
*   `ex05/`: Optimizing control flow with pointers to member functions.
*   `ex06/`: Log filtering using a `switch` statement.
