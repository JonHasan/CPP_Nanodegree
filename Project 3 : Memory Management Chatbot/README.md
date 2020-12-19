# CPPND: Memory Management Chatbot

This project was definitely the most difficult one for me. I knew before the program that memory management was the most valuable aspect of C++. The rule of five, resource sharing policies, move semantics and smart pointers had me doing more research on the knowledge forum and outside internet resources. 

Smart pointers are used when we don't want to worry about allocation and deallocation taks of memory management. When the smart pointer gets out of scope. It will automatically release the memory that was in use. However, it still requires more resources to use a smart pointer than it is to manually allocate and deallocate memory. One needs to be careful about memory leaks though with the latter. 

## Code Explanation

I will now begin the explanation of each of the tasks. 

### Task 1: Exclusive Ownership

The first thing that needed to be done was to change the ownership of the chatLogic variable. It needs to be an exclusive resource of the class ChatBotPanelDialog. It started off as a regular pointer but was transformed to a std::unique_ptr. Since the unique pointer takes care of resource destruction, the destructor in chatgui.cpp is basically useless. I commented out the destructor code. 

### Task 2 : Apply the Rule of Five

This task was a difficult one. I had a shaky appreciation for the rule of five which says you need to implement a copy constructor, an assigment operator, a destructor, a move constructor and move assignment operator. These changes need to be made in chatbot.h and chatbot.cpp. 

#### Copy Constructor
For the copy constructor, I needed to do a deep copy of all the data. So from this source node reference I needed to place all of the attributes into new variables and then place a new image variable with all of the deep copied data. A suggestion was given to me on this where I was supposed to do a check to see if the image attribute was not NULL. The image would then be make with a new wxBitmap with a dereferenced parameter of source.image. 

#### Copy Assignment constructor 

For the copy assignment constructor, I needed to assign the source attributes to new variables and then set the image equal to a new wxBitmap(); 

I then needed to deepcopy with the image attribute from source. 

#### Move Constructor

For the move constructor, I needed to do the same thing as above for the first half by taking a R-value reference to the source parameter. Then setting new image, chatlogic, rootNode and currentNode variables equal to the respective attributes in the source parameter. Then the source needs to be removed by setting all source attributes to null pointer. 

#### Move Assignment Operator 

For the Move Assignment operator, needed to check if the current instance is equal to the current source, return the current instance. 

copy the attributes from source to new variables. Then set all attributes to null. 

#### Destructor 

Destructor is already possible with the ~ character in front of a method name. 

### Task 3 : Exclusive Ownership 2 

In the chatlogic.h/chatlogic.cpp, I needed to change the vector called nodes so that any instance of GraphNodes that are referred to by the vector are owned by class ChatLogic. I had to go to the ChatLogic::LoadAnswerGraphFromFile and change the edge pointer to a unique_ptr and then make each graph edge unique. Then I needed to set the attributes for each edge. Then the reference needs to be stored. 

### Task 4 : Moving smart pointers

### Task 5 : Moving the Chatbot

This is the project for the third course in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213): Memory Management.

<img src="images/chatbot_demo.gif"/>

The ChatBot code creates a dialogue where users can ask questions about some aspects of memory management in C++. After the knowledge base of the chatbot has been loaded from a text file, a knowledge graph representation is created in computer memory, where chatbot answers represent the graph nodes and user queries represent the graph edges. After a user query has been sent to the chatbot, the Levenshtein distance is used to identify the most probable answer. The code is fully functional as-is and uses raw pointers to represent the knowledge graph and interconnections between objects throughout the project.

In this project you will analyze and modify the program. Although the program can be executed and works as intended, no advanced concepts as discussed in this course have been used; there are currently no smart pointers, no move semantics and not much thought has been given to ownership or memory allocation.

Your goal is to use the course knowledge to optimize the ChatBot program from a memory management perspective. There are a total of five specific tasks to be completed, which are detailed below.

## Dependencies for Running Locally
* cmake >= 3.11
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* wxWidgets >= 3.0
  * Linux: `sudo apt-get install libwxgtk3.0-dev libwxgtk3.0-0v5-dbg`
  * Mac: There is a [homebrew installation available](https://formulae.brew.sh/formula/wxmac).
  * Installation instructions can be found [here](https://wiki.wxwidgets.org/Install). Some version numbers may need to be changed in instructions to install v3.0 or greater.

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./membot`.

## Project Task Details

Currently, the program crashes when you close the window. There is a small bug hidden somewhere, which has something to do with improper memory management. So your first warm-up task will be to find this bug and remove it. This should familiarize you with the code and set you up for the rest of the upcoming tasks. Have fun debugging!

Aside from the bug mentioned above, there are five additional major student tasks in the Memory Management chatbot project, which are:

### Task 1 : Exclusive Ownership 1
In file `chatgui.h` / `chatgui.cpp`, make `_chatLogic` an exclusive resource to class `ChatbotPanelDialog` using an appropriate smart pointer. Where required, make changes to the code such that data structures and function parameters reflect the new structure. 

### Task 2 : The Rule Of Five
In file `chatbot.h` / `chatbot.cpp`, make changes to the class `ChatBot` such that it complies with the Rule of Five. Make sure to properly allocate / deallocate memory resources on the heap and also copy member data where it makes sense to you.  In each of the methods (e.g. the copy constructor), print a string of the type "ChatBot Copy Constructor" to the console so that you can see which method is called in later examples. 

### Task 3 : Exclusive Ownership 2
In file `chatlogic.h` / `chatlogic.cpp`, adapt the vector `_nodes` in a way that the instances of `GraphNodes` to which the vector elements refer are exclusively owned by the class `ChatLogic`. Use an appropriate type of smart pointer to achieve this. Where required, make changes to the code such that data structures and function parameters reflect the changes. When passing the `GraphNode` instances to functions, make sure to not transfer ownership and try to contain the changes to class `ChatLogic` where possible. 

### Task 4 : Moving Smart Pointers

In files `chatlogic.h` / `chatlogic.cpp` and `graphnodes.h` / `graphnodes.cpp` change the ownership of all instances of `GraphEdge` in a way such that each instance of `GraphNode` exclusively owns the outgoing `GraphEdges` and holds non-owning references to incoming `GraphEdges`. Use appropriate smart pointers and where required, make changes to the code such that data structures and function parameters reflect the changes. When transferring ownership from class `ChatLogic`, where all instances of `GraphEdge` are created, into instances of `GraphNode`, make sure to use move semantics. 

### Task 5 : Moving the ChatBot

In file `chatlogic.cpp`, create a local `ChatBot` instance on the stack at the bottom of function `LoadAnswerGraphFromFile`. Then, use move semantics to pass the `ChatBot` instance into the root node. Make sure that `ChatLogic` has no ownership relation to the `ChatBot` instance and thus is no longer responsible for memory allocation and deallocation. Note that the member `_chatBot` remains so it can be used as a communication handle between GUI and `ChatBot` instance. Make all required changes in files `chatlogic.h` / `chatlogic.cpp` and `graphnode.h` / `graphnode.cpp`. When the program is executed, messages on which part of the Rule of Five components of `ChatBot` is called should be printed to the console. When sending a query to the `ChatBot`, the output should look like the following: 

```
ChatBot Constructor
ChatBot Move Constructor
ChatBot Move Assignment Operator
ChatBot Destructor
ChatBot Destructor 
```
