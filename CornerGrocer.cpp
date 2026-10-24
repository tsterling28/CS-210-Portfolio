
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <limits>
using namespace std;

// GroceryTracker manages grocery purchase frequencies.
class GroceryTracker {
private:
    map<string, int> itemFrequency;

public:
    // Read grocery purchases from the input file.
    bool LoadData(const string& filename) {
        ifstream inputFile(filename);

        if (!inputFile.is_open()) {
            cout << "Error: Could not open " << filename << endl;
            return false;
        }

        string item;

        while (inputFile >> item) {
            itemFrequency[item]++;
        }

        inputFile.close();

        cout << "Grocery data loaded successfully!" << endl;
        return true;
    }

    // Menu Option 1: Search for an item's frequency.
    void SearchItem() const {
        string item;

        cout << "\nEnter the item you want to search for: ";
        cin >> item;

        auto found = itemFrequency.find(item);

        if (found != itemFrequency.end()) {
            cout << item << " was purchased "
                << found->second << " times." << endl;
        }
        else {
            cout << item << " was not found." << endl;
        }
    }

    // Menu Option 2: Display all item frequencies.
    void DisplayAllItems() const {
        cout << "\nGROCERY ITEM FREQUENCIES" << endl;
        cout << "------------------------" << endl;

        for (const auto& item : itemFrequency) {
            cout << item.first << " "
                << item.second << endl;
        }
    }

    // Menu Option 3: Display a histogram.
    void DisplayHistogram() const {
        cout << "\nGROCERY FREQUENCY HISTOGRAM" << endl;
        cout << "---------------------------" << endl;

        for (const auto& item : itemFrequency) {
            cout << item.first << " ";

            for (int i = 0; i < item.second; i++) {
                cout << "*";
            }

            cout << endl;
        }
    }

    // Create the required backup file automatically.
    bool SaveBackup(const string& filename) const {
        ofstream outputFile(filename);

        if (!outputFile.is_open()) {
            cout << "Error: Could not create "
                << filename << endl;
            return false;
        }

        for (const auto& item : itemFrequency) {
            outputFile << item.first << " "
                << item.second << endl;
        }

        outputFile.close();

        cout << "Backup file " << filename
            << " created successfully!" << endl;

        return true;
    }

    // Display the main menu.
    void DisplayMenu() const {
        cout << "\n========== CORNER GROCER ==========" << endl;
        cout << "1. Search for an item" << endl;
        cout << "2. Display all item frequencies" << endl;
        cout << "3. Display frequency histogram" << endl;
        cout << "4. Exit program" << endl;
        cout << "===================================" << endl;
        cout << "Enter your choice (1-4): ";
    }
};

int main() {
    GroceryTracker tracker;

    // Load the grocery purchase data.
    if (!tracker.LoadData(
        "CS210_Project_Three_Input_File.txt.txt")) {
        return 1;
    }

    // Create the backup file when the program starts.
    if (!tracker.SaveBackup("frequency.dat")) {
        return 1;
    }

    int choice = 0;

    // Continue displaying the menu until the user exits.
    do {
        tracker.DisplayMenu();

        if (!(cin >> choice)) {
            cout << "\nInvalid input. Enter a number from 1 to 4."
                << endl;

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
        case 1:
            tracker.SearchItem();
            break;

        case 2:
            tracker.DisplayAllItems();
            break;

        case 3:
            tracker.DisplayHistogram();
            break;

        case 4:
            cout << "\nThank you for using Corner Grocer!"
                << endl;
            break;

        default:
            cout << "\nInvalid choice. Please enter 1-4."
                << endl;
            break;
        }

    } while (choice != 4);

    return 0;
}


