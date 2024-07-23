#include <iostream>
#include <vector>
#include <iomanip>
#include <random>
#include <cstdlib>
#include <climits>
#include <fstream>

// ANSI color escape sequences
const std::string ANSI_RESET = "\033[0m";
const std::string ANSI_BOLD = "\033[1m";
const std::string ANSI_CYAN = "\033[36m";
const std::string ANSI_YELLOW = "\033[33m";
const std::string ANSI_GREEN = "\033[32m";
const std::string ANSI_RED = "\033[31m";
const std::string ANSI_FONT_SIZE_BIG = "\033[2m";

class ToDoItem {
    public:
    std::string description;
    bool completed;
};

std::vector<ToDoItem> toDoList;
std::vector<std::string> notes;
std::vector<std::string> motivationalQuotes;
std::vector<std::string> jokes;

std::vector<size_t> searchItems(const std::string& searchTerm, const std::vector<ToDoItem>& items) {
    std::vector<size_t> matchingIndices;
    for (size_t i = 0; i < items.size(); ++i) {
        if (items[i].description.find(searchTerm) != std::string::npos) {
            matchingIndices.push_back(i);
        }
    }
    return matchingIndices;
}

std::vector<size_t> searchItems(const std::string& searchTerm, const std::vector<std::string>& items) {
    std::vector<size_t> matchingIndices;
    for (size_t i = 0; i < items.size(); ++i) {
        if (items[i].find(searchTerm) != std::string::npos) {
            matchingIndices.push_back(i);
        }
    }
    return matchingIndices;
}

void addTodoItem() {
    std::cout << "Enter the description: ";
    std::string description;
    std::cin.ignore();
    std::getline(std::cin, description);
    ToDoItem newItem;
    newItem.description = description;
    newItem.completed = false;
    toDoList.push_back(newItem);
    std::cout << ANSI_GREEN << "Item added to the to-do list." << ANSI_RESET << "\n";

    newItem.description += "\n";
    std::ofstream active("todos.txt", std::ios::app);
    active<<newItem.description;
    active.close();
}

void viewTodoList() {
    std::cout << "╔════════════════════════════════════════╗\n";
    std::cout << "║ " << ANSI_BOLD << "To-Do List" << ANSI_RESET << "                             ║\n";
   std::cout <<  "╠════════════════════════════════════════╣\n";

    if (toDoList.empty()) {
        std::cout << "║" << ANSI_YELLOW << " No items in the to-do list " << ANSI_RESET << "            ║\n";
    } 
    else {
        for (size_t i = 0; i < toDoList.size(); ++i) {
            std::cout << "║ " << std::setw(1) <<i + 1 << ". "; 
            std::cout << (toDoList[i].completed ? ANSI_GREEN + "[X] " : ANSI_RED + "[ ] ");
            std::cout << std::left << std::setw(18) << toDoList[i].description << ANSI_RESET << "              ║\n";
        }
    }
    std::cout << "╚════════════════════════════════════════╝\n";
}

void editTodoItem(size_t index) {
    if (index < toDoList.size()) {
        std::cout << "Enter new description: ";
        std::string newDescription;
        std::cin.ignore();
        std::getline(std::cin, newDescription);
        toDoList[index].description = newDescription;
        std::cout << ANSI_GREEN << "Item updated." << ANSI_RESET << "\n";
    } 
    else {
        std::cout << ANSI_RED << "Invalid item index." << ANSI_RESET << "\n";
    }
}

void markTodoItemAsCompleted(size_t index) {
    if (index < toDoList.size()) {
        toDoList[index].completed = true;
        std::cout << ANSI_GREEN << "Item marked as completed." << ANSI_RESET << "\n";
    } 
    else {
        std::cout << ANSI_RED << "Invalid item index." << ANSI_RESET << "\n";
    }
}

void markTodoItemIncomplete(size_t index) {
    if (index < toDoList.size()) {
        toDoList[index].completed = false;
        std::cout << ANSI_GREEN << "Item marked as incomplete." << ANSI_RESET << "\n";
    } 
    else {
        std::cout << ANSI_RED << "Invalid index." << ANSI_RESET << "\n";
    }
}

void deleteTodoItem(size_t index) {
    if (index < toDoList.size()) {
        toDoList.erase(toDoList.begin() + index);
        std::cout << ANSI_GREEN << "Item deleted." << ANSI_RESET << "\n";
    } 
    else {
        std::cout << ANSI_RED << "Invalid item index." << ANSI_RESET << "\n";
    }
}

void addNote() {
    std::cout << "Enter your note: ";
    std::string note;
    std::cin.ignore();
    std::getline(std::cin, note);
    notes.push_back(note);
    std::cout << ANSI_GREEN << "Note added." << ANSI_RESET << "\n";

    note += "\n";
    std::ofstream active("notes.txt", std::ios::app);
    active<<note;
    active.close();
}

void viewNotes() {
    std::cout << "╔══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗\n";
    std::cout << "║ " << ANSI_BOLD << "Notes" << ANSI_RESET << "                                                                                                                                                        ║\n";
    std::cout << "╠══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╣\n";

    if (notes.empty()) {
    std::cout << "║ " << ANSI_YELLOW << "No notes available" << ANSI_RESET << "                                                                                                                                           ║\n";
    } 
    else {
        for (size_t i = 0; i < notes.size(); ++i) {
        std::cout << "║ " << std::setw(1) <<i + 1 << ". ";
        std::cout << std::left << std::setw(18) << notes[i] << "                                                                                                                                        ║\n";
        }
    }
    std::cout << "╚══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝\n";
}

void fetchMotivation(){
    std::string line;
    srand(time(0));
    std::ifstream file("motivation.txt");
    int no_of_lines = 0;
    while(getline(file, line)){
        no_of_lines++;
        if(int random_number = rand() % no_of_lines){ 
            motivationalQuotes.push_back(line);
        }
    }
}

void fetchJokes(){
    std::string line;
    srand(time(0));
    std::ifstream file("jokes.txt");
    int no_of_lines = 0;
    while(getline(file, line)){
        no_of_lines++;
        if(int random_number = rand() % no_of_lines){
            jokes.push_back(line);
        }
    }
}

void displayMotivationalQuote() {
    fetchMotivation();
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<size_t> distribution(0, motivationalQuotes.size() - 1);
    size_t index = distribution(rng);
    std::cout << ANSI_BOLD << "Motivational Quote: " << ANSI_RESET << "\n";
    std::cout << ANSI_YELLOW << motivationalQuotes[index] << ANSI_RESET << "\n";
}

void tellJoke() {
    fetchJokes();
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<size_t> distribution(0, jokes.size() - 1);
    size_t index = distribution(rng);
    std::cout << ANSI_BOLD << "Joke of the Day: " << ANSI_RESET << "\n";
    std::cout << ANSI_YELLOW << jokes[index] << ANSI_RESET << "\n";
}

void searchInToDoList() {
    std::cout << "Enter the search term: ";
    std::string searchTerm;
    std::cin.ignore();
    std::getline(std::cin, searchTerm);

    std::vector<size_t> matchingIndices = searchItems(searchTerm, toDoList);

    if (matchingIndices.empty()) {
        std::cout << "No matching items found in the to-do list.\n";
    } else {
        std::cout << "Matching items in the to-do list:\n";
        for (size_t index : matchingIndices) {
            std::cout << "- " << toDoList[index].description << "\n";
        }
    }
}

void searchInNotes() {
    std::cout << "Enter the search term: ";
    std::string searchTerm;
    std::cin.ignore();
    std::getline(std::cin, searchTerm);

    std::vector<size_t> matchingIndices = searchItems(searchTerm, notes);

    if (matchingIndices.empty()) {
        std::cout << "No matching notes found.\n";
    } else {
        std::cout << "Matching notes:\n";
        for (size_t index : matchingIndices) {
            std::cout << "- " << notes[index] << "\n";
        }
    }
}

size_t returnIndex(){
    std::cout << "Enter the index of the item to delete: ";
    size_t index;
    std::cin >> index;
    return index;
}

void deleteFileContent(std::string fileName) {
    std::ofstream file(fileName, std::ios::out | std::ios::trunc);
    file.close();
}

void exitProgram(){
    std::cout << "Exiting the program...Goodbye!\n";
    deleteFileContent("todos.txt");
    deleteFileContent("notes.txt");
}

void displayMenu() {
    std::cout << "\n";
    std::cout << ANSI_GREEN << ANSI_FONT_SIZE_BIG << "██████╗░██████╗░░█████╗░░█████╗░██████╗░░█████╗░░██████╗████████╗██╗███╗░░██╗░█████╗░████████╗███████╗" << ANSI_RESET << "\n";
    std::cout << ANSI_GREEN << ANSI_FONT_SIZE_BIG << "██╔══██╗██╔══██╗██╔══██╗██╔══██╗██╔══██╗██╔══██╗██╔════╝╚══██╔══╝██║████╗░██║██╔══██╗╚══██╔══╝██╔════╝" << ANSI_RESET << "\n";
    std::cout << ANSI_GREEN << ANSI_FONT_SIZE_BIG << "██████╔╝██████╔╝██║░░██║██║░░╚═╝██████╔╝███████║╚█████╗░░░░██║░░░██║██╔██╗██║██║░░██║░░░██║░░░█████╗░░" << ANSI_RESET << "\n";
    std::cout << ANSI_GREEN << ANSI_FONT_SIZE_BIG << "██╔═══╝░██╔══██╗██║░░██║██║░░██╗██╔══██╗██╔══██║░╚═══██╗░░░██║░░░██║██║╚████║██║░░██║░░░██║░░░██╔══╝░░" << ANSI_RESET << "\n";
    std::cout << ANSI_GREEN << ANSI_FONT_SIZE_BIG << "██║░░░░░██║░░██║╚█████╔╝╚█████╔╝██║░░██║██║░░██║██████╔╝░░░██║░░░██║██║░╚███║╚█████╔╝░░░██║░░░███████╗" << ANSI_RESET << "\n";
    std::cout << ANSI_GREEN << ANSI_FONT_SIZE_BIG << "╚═╝░░░░░╚═╝░░╚═╝░╚════╝░░╚════╝░╚═╝░░╚═╝╚═╝░░╚═╝╚═════╝░░░░╚═╝░░░╚═╝╚═╝░░╚══╝░╚════╝░░░░╚═╝░░░╚══════╝" << ANSI_RESET << "\n";                                                                                                                                                                                                                                                       

    std::cout << "╔═══════════════════════════════════════╗\n";
    std::cout << "║   " << ANSI_BOLD << ANSI_YELLOW << ANSI_FONT_SIZE_BIG << "      Procrastinote-To-Do" << ANSI_RESET << "           ║\n";
    std::cout << "╠═══════════════════════════════════════╣\n";
    std::cout << "║ " << ANSI_CYAN << "1. Add item to to-do list" << ANSI_RESET << "             ║\n";
    std::cout << "║ " << ANSI_CYAN << "2. View to-do list" << ANSI_RESET << "                    ║\n";
    std::cout << "║ " << ANSI_CYAN << "3. Edit a to-do item" << ANSI_RESET << "                  ║\n";                       
    std::cout << "║ " << ANSI_CYAN << "4. Mark a to-do item as completed"<< ANSI_RESET << "     ║\n";         
    std::cout << "║ " << ANSI_CYAN << "5. Mark a to-do item as incomplete" << ANSI_RESET << "    ║\n";
    std::cout << "║ " << ANSI_CYAN << "6. Delete a to-do item" << ANSI_RESET << "                ║\n";
    std::cout << "║ " << ANSI_CYAN << "7. Add note" << ANSI_RESET << "                           ║\n";
    std::cout << "║ " << ANSI_CYAN << "8. View notes" << ANSI_RESET << "                         ║\n";
    std::cout << "║ " << ANSI_CYAN << "9. Get motivated!" << ANSI_RESET << "                     ║\n";
    std::cout << "║ " << ANSI_CYAN << "10. Cheer me up!" << ANSI_RESET << "                      ║\n";
    std::cout << "║ " << ANSI_CYAN << "11. Search in to-do list" << ANSI_RESET << "              ║\n";
    std::cout << "║ " << ANSI_CYAN << "12. Search in notes" << ANSI_RESET << "                   ║\n";
    std::cout << "║ " << ANSI_CYAN << "13. Exit" << ANSI_RESET << "                              ║\n";
    std::cout << "╚═══════════════════════════════════════╝\n";
    std::cout << "Enter your choice (1-13): ";
}

int main() {
    
    while (true) {
        displayMenu();

        int choice;
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
        }

        switch (choice) {
            case 1: {
                addTodoItem();
                break;
            }
            case 2: {
                viewTodoList();
                break;
            }
            case 3: {
                editTodoItem(returnIndex()-1);
                break;
            }
            case 4: {
                markTodoItemAsCompleted(returnIndex()-1);
                break;
            }
            case 5: {
                markTodoItemIncomplete(returnIndex()-1);
                break;
            }

            case 6: {
                deleteTodoItem(returnIndex()-1);
                break;
            }
            case 7: {
                addNote();
                break;
            }
            case 8: {
                viewNotes();
                break;
            }
            case 9: {
                displayMotivationalQuote();
                break;
            }
            case 10: {
                tellJoke();
                break;
            }
            case 11: {
                searchInToDoList();
                break;
            }
            case 12: {
                searchInNotes();
                break;
            }
            case 13: {
                exitProgram();
                return 0;
            }
            default: {
                std::cout << "Invalid choice. Please try again.\n";
                break;
            }
            std::cout << "\n";
        }
    }
    return 0;
}

                                                                                                                                                                                                                                                                                 
                                                                                                                                                                                                                                                                           

 



                                                                                                                                                                                                                                                                                
                                                                                                                                                                                                                                                                                
                                                                                                                                                                                                                                                                                
                                                                                                                                                                                                                                                                                

                                                                                                                                                                                                                                                                                
                                                                                                                                                                                                                                                                                
                                                                                                                                                                                                                                                                                
                                                                                                                                                                                                                                                                                
                                                                                                                                                                                                                                                                                
 
                                                                                               
