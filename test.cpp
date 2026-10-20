#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <sstream>
#include <windows.h>
using namespace std;
void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void resetColor() {
    setColor(7);
}

void sleepFor(int milliseconds) {
    Sleep(milliseconds);
}

void beepSound() {
    Beep(750, 300);
}

void pressAnyKeyToContinue() {
    cout << endl;
    setColor(14);
    cout << "Press Enter to continue...";
    resetColor();
    cin.get();
}

int stringToInt(string str) {
    int result = 0;
    for (int i = 0; i < (int)str.length(); i++) {
        result = result * 10 + (str[i] - '0');
    }
    return result;
}

string intToString(int num) {
    if (num == 0) return "0";
    string result = "";
    while (num > 0) {
        result = (char)('0' + num % 10) + result;
        num = num / 10;
    }
    return result;
}

class Student {
private:
    string name;
    string id;
    string password;
    int semester;
    int year;
    string registeredUnits[20];
    string registeredGroups[20];
    int registrationCount;
    int groupSlots[4][4];
    string groupNames[4];
    string unitNames[4];
    bool hasRegistered;
    bool individualUnitChosen[4][4];
    bool loggedIn;
    bool unitRegistered[4];
    bool hasFullGroupRegistration;
    int fullGroupIndex;

public:
    Student() {
        registrationCount = 0;
        hasRegistered = false;
        loggedIn = false;
        semester = 0;
        year = 0;
        name = "";
        id = "";
        password = "";
        hasFullGroupRegistration = false;
        fullGroupIndex = -1;
        groupNames[0] = "1E1";
        groupNames[1] = "1E2";
        groupNames[2] = "1E3";
        groupNames[3] = "1E4";
        unitNames[0] = "Programming";
        unitNames[1] = "Physics 1";
        unitNames[2] = "Mathematics 2";
        unitNames[3] = "Writing and Research Skills";
        for (int i = 0; i < 4; i++) {
            unitRegistered[i] = false;
            for (int j = 0; j < 4; j++) {
                groupSlots[i][j] = 15;
                individualUnitChosen[i][j] = false;
            }
        }
    }

    void setName(string n) {
        name = n;
    }

    string getName() {
        return name;
    }

    void setId(string i) {
        id = i;
    }

    string getId() {
        return id;
    }

    void setPassword(string p) {
        password = p;
    }

    string getPassword() {
        return password;
    }

    void setSemester(int s) {
        semester = s;
    }

    int getSemester() {
        return semester;
    }

    void setYear(int y) {
        year = y;
    }

    int getYear() {
        return year;
    }

    bool getHasRegistered() {
        return hasRegistered;
    }

    bool isLoggedIn() {
        return loggedIn;
    }

    void setLoggedIn(bool status) {
        loggedIn = status;
    }

    bool isAccountCreated() {
        if (id != "" && password != "") {
            return true;
        }
        return false;
    }

    int getRegistrationCount() {
        return registrationCount;
    }

    string getRegisteredUnit(int index) {
        return registeredUnits[index];
    }

    string getRegisteredGroup(int index) {
        return registeredGroups[index];
    }

    string getGroupName(int index) {
        return groupNames[index];
    }

    string getUnitName(int index) {
        return unitNames[index];
    }

    int getGroupSlot(int groupIndex, int unitIndex) {
        return groupSlots[groupIndex][unitIndex];
    }

    void setGroupSlot(int groupIndex, int unitIndex, int value) {
        groupSlots[groupIndex][unitIndex] = value;
    }

    bool hasFullGroup() {
        return hasFullGroupRegistration;
    }

    int getFullGroupIndex() {
        return fullGroupIndex;
    }

    bool isUnitRegistered(int unitIndex) {
        return unitRegistered[unitIndex];
    }

    bool hasAllUnitsRegistered() {
        for (int i = 0; i < 4; i++) {
            if (!unitRegistered[i]) {
                return false;
            }
        }
        return true;
    }

    int countUnregisteredUnits() {
        int count = 0;
        for (int i = 0; i < 4; i++) {
            if (!unitRegistered[i]) {
                count++;
            }
        }
        return count;
    }

    bool isAlreadyRegistered(int groupIndex, int unitIndex) {
        string group = groupNames[groupIndex];
        string unit = unitNames[unitIndex];
        for (int i = 0; i < registrationCount; i++) {
            if (registeredGroups[i] == group && registeredUnits[i] == unit) {
                return true;
            }
        }
        return false;
    }

    bool hasChosenIndividualUnit(int groupIndex) {
        for (int j = 0; j < 4; j++) {
            if (individualUnitChosen[groupIndex][j]) {
                return true;
            }
        }
        return false;
    }

    void registerUnit(int groupIndex, int unitIndex) {
        registeredUnits[registrationCount] = unitNames[unitIndex];
        registeredGroups[registrationCount] = groupNames[groupIndex];
        registrationCount++;
        groupSlots[groupIndex][unitIndex]--;
        individualUnitChosen[groupIndex][unitIndex] = true;
        unitRegistered[unitIndex] = true;
        hasRegistered = true;
    }

    void registerAllUnits(int groupIndex) {
        int unitsRegistered = 0;
        for (int j = 0; j < 4; j++) {
            if (!isAlreadyRegistered(groupIndex, j) && groupSlots[groupIndex][j] > 0) {
                registeredUnits[registrationCount] = unitNames[j];
                registeredGroups[registrationCount] = groupNames[groupIndex];
                registrationCount++;
                groupSlots[groupIndex][j]--;
                individualUnitChosen[groupIndex][j] = true;
                unitRegistered[j] = true;
                unitsRegistered++;
            }
        }
        if (unitsRegistered == 4) {
            hasFullGroupRegistration = true;
            fullGroupIndex = groupIndex;
        }
        hasRegistered = true;
    }

    void registerRemainingUnits(int groupIndex) {
        int unitsRegistered = 0;
        for (int j = 0; j < 4; j++) {
            if (!unitRegistered[j] && groupSlots[groupIndex][j] > 0) {
                registeredUnits[registrationCount] = unitNames[j];
                registeredGroups[registrationCount] = groupNames[groupIndex];
                registrationCount++;
                groupSlots[groupIndex][j]--;
                individualUnitChosen[groupIndex][j] = true;
                unitRegistered[j] = true;
                unitsRegistered++;
            }
        }
        
        if (hasAllUnitsRegistered()) {
            hasFullGroupRegistration = true;
            fullGroupIndex = groupIndex;
        }
        hasRegistered = true;
    }

    string getTrimesterString() {
        return intToString(semester) + "F-" + intToString(year);
    }

    void saveToFile() {
        ofstream outFile("Record.txt");
        outFile << "Trimester: " << getTrimesterString() << endl;
        outFile << "Student Name: " << name << endl;
        outFile << "Student ID: " << id << endl;
        outFile << left << setw(30) << "Unit" << "Grouping" << endl;
        outFile << "===========================" << endl;
        for (int i = 0; i < registrationCount; i++) {
            outFile << left << setw(30) << registeredUnits[i] << registeredGroups[i] << endl;
        }
        outFile << "===========================" << endl;
        outFile.close();
    }

    void saveStudentData(ofstream &outFile) {
        outFile << name << "|" << id << "|" << password << "|" << semester << "|" << year << "|";
        outFile << registrationCount << "|" << hasRegistered << "|" << hasFullGroupRegistration << "|" << fullGroupIndex << "|";
        for (int i = 0; i < 4; i++) {
            outFile << unitRegistered[i];
            if (i < 3) outFile << ",";
        }
        outFile << "|";
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                outFile << groupSlots[i][j];
                if (j < 3) outFile << ",";
            }
            if (i < 3) outFile << ";";
        }
        outFile << "|";
        for (int i = 0; i < registrationCount; i++) {
            outFile << registeredUnits[i];
            if (i < registrationCount - 1) outFile << ",";
        }
        outFile << "|";
        for (int i = 0; i < registrationCount; i++) {
            outFile << registeredGroups[i];
            if (i < registrationCount - 1) outFile << ",";
        }
        outFile << endl;
    }

    void loadStudentData(string line) {
        int fieldCount = 0;
        string field = "";
        
        for (int i = 0; i <= (int)line.length(); i++) {
            if (i == (int)line.length() || line[i] == '|') {
                if (fieldCount == 0) name = field;
                else if (fieldCount == 1) id = field;
                else if (fieldCount == 2) password = field;
                else if (fieldCount == 3) semester = stringToInt(field);
                else if (fieldCount == 4) year = stringToInt(field);
                else if (fieldCount == 5) registrationCount = stringToInt(field);
                else if (fieldCount == 6) hasRegistered = (field == "1");
                else if (fieldCount == 7) hasFullGroupRegistration = (field == "1");
                else if (fieldCount == 8) fullGroupIndex = stringToInt(field);
                else if (fieldCount == 9) {
                    int idx = 0;
                    string token = "";
                    for (int j = 0; j <= (int)field.length(); j++) {
                        if (j == (int)field.length() || field[j] == ',') {
                            unitRegistered[idx++] = (token == "1");
                            token = "";
                        } else {
                            token += field[j];
                        }
                    }
                }
                else if (fieldCount == 10) {
                    int groupIdx = 0;
                    int unitIdx = 0;
                    string token = "";
                    for (int j = 0; j <= (int)field.length(); j++) {
                        if (j == (int)field.length() || field[j] == ';' || field[j] == ',') {
                            groupSlots[groupIdx][unitIdx] = stringToInt(token);
                            token = "";
                            unitIdx++;
                            if (field[j] == ';') {
                                groupIdx++;
                                unitIdx = 0;
                            }
                        } else {
                            token += field[j];
                        }
                    }
                }
                else if (fieldCount == 11) {
                    int idx = 0;
                    string token = "";
                    for (int j = 0; j <= (int)field.length(); j++) {
                        if (j == (int)field.length() || field[j] == ',') {
                            if (token != "") {
                                registeredUnits[idx++] = token;
                                token = "";
                            }
                        } else {
                            token += field[j];
                        }
                    }
                }
                else if (fieldCount == 12) {
                    int idx = 0;
                    string token = "";
                    for (int j = 0; j <= (int)field.length(); j++) {
                        if (j == (int)field.length() || field[j] == ',') {
                            if (token != "") {
                                registeredGroups[idx++] = token;
                                token = "";
                            }
                        } else {
                            token += field[j];
                        }
                    }
                }
                
                field = "";
                fieldCount++;
            } else {
                field += line[i];
            }
        }
    }
};

class UserDatabase {
private:
    Student users[30];
    int userCount;
    int currentUserIndex;
    string databaseFile;

public:
    UserDatabase() {
        userCount = 0;
        currentUserIndex = -1;
        databaseFile = "userdata.txt";
        loadFromFile();
    }

    ~UserDatabase() {
        saveToFile();
    }

    int getUserCount() {
        return userCount;
    }

    int getCurrentUserIndex() {
        return currentUserIndex;
    }

    Student& getCurrentUser() {
        return users[currentUserIndex];
    }

    int findUserById(string id) {
        for (int i = 0; i < userCount; i++) {
            if (users[i].getId() == id) {
                return i;
            }
        }
        return -1;
    }

    bool isDatabaseFull() {
        if (userCount >= 30) {
            return true;
        }
        return false;
    }

    bool registerNewUser(string name, string id, string password) {
        if (isDatabaseFull()) {
            return false;
        }
        if (findUserById(id) != -1) {
            return false;
        }
        users[userCount].setName(name);
        users[userCount].setId(id);
        users[userCount].setPassword(password);
        users[userCount].setLoggedIn(true);
        currentUserIndex = userCount;
        userCount++;
        saveToFile();
        return true;
    }

    bool loginUser(string id, string password) {
        int index = findUserById(id);
        if (index == -1) {
            return false;
        }
        if (users[index].getPassword() != password) {
            return false;
        }
        users[index].setLoggedIn(true);
        currentUserIndex = index;
        return true;
    }

    void logoutCurrentUser() {
        if (currentUserIndex != -1) {
            saveToFile();
            users[currentUserIndex].setLoggedIn(false);
            currentUserIndex = -1;
        }
    }

    void saveToFile() {
        ofstream outFile(databaseFile.c_str());
        if (!outFile) {
            return;
        }
        outFile << userCount << endl;
        for (int i = 0; i < userCount; i++) {
            users[i].saveStudentData(outFile);
        }
        outFile.close();
    }

    void loadFromFile() {
        ifstream inFile(databaseFile.c_str());
        if (!inFile) {
            return;
        }
        string line;
        getline(inFile, line);
        if (line.empty()) {
            inFile.close();
            return;
        }
        userCount = stringToInt(line);
        for (int i = 0; i < userCount; i++) {
            getline(inFile, line);
            if (!line.empty()) {
                users[i].loadStudentData(line);
            }
        }
        inFile.close();
    }

    void updateGroupSlots(int groupIndex, int unitIndex) {
        for (int i = 0; i < userCount; i++) {
            users[i].setGroupSlot(groupIndex, unitIndex, users[currentUserIndex].getGroupSlot(groupIndex, unitIndex));
        }
        saveToFile();
    }
};

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void loadingMessage(string message) {
    cout << endl;
    cout << message;
    for (int i = 0; i < 3; i++) {
        cout << " .";
    }
    cout << endl;
}

bool isNumeric(string str) {
    if (str.empty()) return false;
    for (int i = 0; i < (int)str.length(); i++) {
        if (!isdigit(str[i])) {
            return false;
        }
    }
    return true;
}

bool isValidId(string id) {
    if (id.empty()) {
        cout << endl;
        cout << "ERROR: Your ID value cannot be blank/empty!" << endl;
        return false;
    }
    if (id.length() != 9) {
        cout << endl;
        cout << "ERROR: Your ID value must be 9-digit long!" << endl;
        return false;
    }
    if (!isNumeric(id)) {
        cout << endl;
        cout << "ERROR: Your ID value must be numeric value only" << endl;
        return false;
    }
    if (id.substr(0, 4) != "7000") {
        cout << endl;
        cout << "ERROR: Your ID value must be in 7000XXXXX format!" << endl;
        return false;
    }
    return true;
}

bool isValidPassword(string password) {
    if (password.empty()) {
        cout << "ERROR: Password cannot be blank/empty!" << endl;
        return false;
    }
    if (password.length() < 6) {
        cout << "ERROR: Password must be at least 6 characters long!" << endl;
        return false;
    }
    return true;
}

void displayLoginMenu() {
    cout << "========================================" << endl;
    cout << "   Grouping Registration App" << endl;
    cout << "========================================" << endl;
    cout << endl;
    cout << "1 - Register (New User)" << endl;
    cout << "2 - Login (Existing User)" << endl;
    cout << "0 - Exit" << endl;
    cout << endl;
}

bool registerUser(UserDatabase &database) {
    clearScreen();
    string name;
    string id;
    string password;
    string confirmPassword;

    cout << "========================================" << endl;
    cout << "         New User Registration" << endl;
    cout << "========================================" << endl;
    cout << endl;

    do {
        cout << "Enter your name: ";
        getline(cin, name);
        if (name.empty()) {
            cout << endl;
            cout << "ERROR: Your name value cannot be blank/empty!" << endl;
            cout << endl;
        }
    } while (name.empty());

    do {
        cout << endl;
        cout << "Enter your ID: ";
        getline(cin, id);
    } while (!isValidId(id));

    if (database.findUserById(id) != -1) {
        cout << endl;
        cout << "ERROR: An account with this ID already exists!" << endl;
        cout << "Please use Login instead." << endl;
        cout << endl;
        cout << "Press Enter to return to the login page...";
        getline(cin, name);
        return false;
    }

    if (database.isDatabaseFull()) {
        cout << endl;
        cout << "ERROR: Maximum number of users (30) has been reached!" << endl;
        cout << "Cannot register new users at this time." << endl;
        cout << endl;
        cout << "Press Enter to return to the login page...";
        getline(cin, name);
        return false;
    }

    do {
        cout << endl;
        cout << "Create a password (min 6 characters): ";
        getline(cin, password);
    } while (!isValidPassword(password));

    do {
        cout << "Confirm your password: ";
        getline(cin, confirmPassword);
        if (confirmPassword != password) {
            cout << "ERROR: Passwords do not match! Please try again." << endl;
            cout << endl;
        }
    } while (confirmPassword != password);

    database.registerNewUser(name, id, password);

    cout << endl;
    cout << "Registration successful!" << endl;
    cout << "Welcome to our Grouping Registration App, " << name << " (ID: " << id << ")!" << endl;
    loadingMessage("Loading Main Page");

    return true;
}

bool loginUser(UserDatabase &database) {
    clearScreen();
    string id;
    string password;
    int attempts = 0;
    int maxAttempts = 3;

    cout << "========================================" << endl;
    cout << "            User Login" << endl;
    cout << "========================================" << endl;
    cout << endl;

    do {
        cout << "Enter your ID: ";
        getline(cin, id);

        if (!isValidId(id)) {
            attempts++;
            if (attempts >= maxAttempts) {
                cout << endl;
                cout << "Maximum login attempts reached!" << endl;
                cout << "Press Enter to return to the login page...";
                getline(cin, id);
                return false;
            }
            cout << endl;
            continue;
        }

        if (database.findUserById(id) == -1) {
            cout << endl;
            cout << "ERROR: No account found with this ID!" << endl;
            cout << "Please register first." << endl;
            attempts++;
            if (attempts >= maxAttempts) {
                cout << endl;
                cout << "Maximum login attempts reached!" << endl;
                cout << "Press Enter to return to the login page...";
                getline(cin, id);
                return false;
            }
            cout << endl;
            continue;
        }

        break;
    } while (true);

    attempts = 0;
    do {
        cout << endl;
        cout << "Enter your password: ";
        getline(cin, password);

        if (database.loginUser(id, password)) {
            cout << endl;
            cout << "Login successful!" << endl;
            cout << "Welcome back, " << database.getCurrentUser().getName()
                 << " (ID: " << database.getCurrentUser().getId() << ")!" << endl;
            loadingMessage("Loading Main Page");
            return true;
        }

        cout << "ERROR: Incorrect password!" << endl;
        attempts++;
        if (attempts >= maxAttempts) {
            cout << endl;
            cout << "Maximum password attempts reached!" << endl;
            cout << "Press Enter to return to the login page...";
            getline(cin, password);
            return false;
        }
    } while (true);
}

void semesterModule(Student &student) {
    if (student.getSemester() != 0 && student.getYear() != 0) {
        return;
    }

    string semInput;
    int semester;
    string yearInput;
    int year;

    do {
        cout << "Enter Semester (e.g., 1, 2 or 3): ";
        getline(cin, semInput);
        if (semInput.length() == 1 && isNumeric(semInput)) {
            semester = stringToInt(semInput);
            if (semester >= 1 && semester <= 3) {
                break;
            }
        }
        cout << "ERROR: Please enter a valid semester (1, 2, or 3)!" << endl;
        cout << endl;
    } while (true);

    student.setSemester(semester);
    cout << endl;

    do {
        cout << "Enter Year (e.g. 2024): ";
        getline(cin, yearInput);
        if (isNumeric(yearInput) && !yearInput.empty()) {
            year = stringToInt(yearInput);
            if (year > 2000 && year < 2050) {
                break;
            } else {
                setColor(12);
                cout << "ERROR: Year must be between 2001 and 2049!" << endl;
                resetColor();
                cout << endl;
            }
        } else {
            cout << "ERROR: Please enter a valid numeric year!" << endl;
            cout << endl;
        }
    } while (true);

    student.setYear(year);
    cout << endl;
    cout << "Thank you for your input. You are registering for Trimester " << student.getTrimesterString() << "!" << endl;
    cout << endl;
}

void groupRegistrationModule(Student &student, UserDatabase &database) {
    clearScreen();
    string groupInput;
    int groupChoice;
    int groupIndex;

    cout << "Welcome to Group Registration Module, " << student.getName() << "!" << endl;
    cout << endl;

    if (student.hasAllUnitsRegistered()) {
        setColor(10);
        cout << "Congratulations! You have already chosen all subjects!" << endl;
        resetColor();
        cout << "You cannot register for any more units." << endl;
        beepSound();
        sleepFor(1000);
        pressAnyKeyToContinue();
        return;
    }

    if (student.hasFullGroup()) {
        cout << "You have already registered for all 4 units in group " << student.getGroupName(student.getFullGroupIndex()) << "!" << endl;
        cout << "You cannot register for any more units." << endl;
        cout << endl;
        cout << "Returning to Main Page..." << endl;
        return;
    }

    cout << "Choose ONE of the following groupings:" << endl;
    cout << "1 - 1E1" << endl;
    cout << "2 - 1E2" << endl;
    cout << "3 - 1E3" << endl;
    cout << "4 - 1E4" << endl;
    cout << "0 - Exit to Main Page" << endl;
    cout << endl;

    do {
        cout << "Group selection: ";
        getline(cin, groupInput);
        if (groupInput.length() == 1 && isNumeric(groupInput)) {
            groupChoice = stringToInt(groupInput);
            if (groupChoice >= 0 && groupChoice <= 4) {
                break;
            }
        }
        cout << "Sorry, please select option 0 to 4 only!" << endl;
        cout << endl;
    } while (true);

    if (groupChoice == 0) {
        cout << "Returning to Main Page..." << endl;
        return;
    }

    groupIndex = groupChoice - 1;
    cout << "You have chosen Group " << student.getGroupName(groupIndex) << endl;
    cout << endl;
    cout << "Please select the following units for group " << student.getGroupName(groupIndex) << endl;
    cout << endl;

    string unitInput;
    int unitChoice;

    for (int i = 0; i < 4; i++) {
        cout << i + 1 << " - " << student.getUnitName(i);
        if (student.isUnitRegistered(i)) {
            setColor(12);
            cout << " (Already registered)";
            resetColor();
        } else {
            setColor(11);
            cout << " (" << intToString(student.getGroupSlot(groupIndex, i)) << " slots available)";
            resetColor();
        }
        cout << endl;
    }
    
    int unregisteredCount = student.countUnregisteredUnits();
    if (unregisteredCount > 0) {
        setColor(14);
        cout << "5 - Select ALL remaining units (" << unregisteredCount << " unit";
        if (unregisteredCount > 1) cout << "s";
        cout << " remaining)" << endl;
        resetColor();
    } else {
        cout << "5 - Select ALL the units above (only if you have not chosen individual unit)" << endl;
    }
    
    cout << "0 - Exit to Main Page" << endl;
    cout << endl;

    do {
        cout << "Choice: ";
        getline(cin, unitInput);
        if (unitInput.length() == 1 && isNumeric(unitInput)) {
            unitChoice = stringToInt(unitInput);
            if (unitChoice >= 0 && unitChoice <= 5) {
                break;
            }
        }
        cout << "Sorry, please select option 0 to 5 only!" << endl;
        cout << endl;
    } while (true);

    if (unitChoice == 0) {
        cout << "Returning to Main Page..." << endl;
        return;
    }

    if (unitChoice == 5) {
        int unregisteredUnits = student.countUnregisteredUnits();
        
        if (unregisteredUnits == 0) {
            setColor(12);
            cout << "You have already registered for all units!" << endl;
            resetColor();
            beepSound();
            sleepFor(1000);
            pressAnyKeyToContinue();
            loadingMessage("Loading grouping registration module");
            return;
        }
        
        bool allRemainingAvailable = true;
        for (int i = 0; i < 4; i++) {
            if (!student.isUnitRegistered(i) && student.getGroupSlot(groupIndex, i) <= 0) {
                allRemainingAvailable = false;
                break;
            }
        }

        if (!allRemainingAvailable) {
            setColor(12);
            cout << "Sorry, not all remaining units have available slots in this group!" << endl;
            resetColor();
            beepSound();
            sleepFor(1000);
            pressAnyKeyToContinue();
            loadingMessage("Loading grouping registration module");
            return;
        } else {
            student.registerRemainingUnits(groupIndex);
            for (int i = 0; i < 4; i++) {
                if (!student.isUnitRegistered(i)) {
                    database.updateGroupSlots(groupIndex, i);
                }
            }
            setColor(10);
            cout << "You have successfully registered into " << student.getGroupName(groupIndex) << " for " << unregisteredUnits << " remaining unit";
            if (unregisteredUnits > 1) cout << "s";
            cout << "!" << endl;
            resetColor();
            beepSound();
            sleepFor(1000);
        }
        pressAnyKeyToContinue();
        loadingMessage("Loading grouping registration module");
        return;
    }

    int unitIndex = unitChoice - 1;

    if (student.isUnitRegistered(unitIndex)) {
        setColor(12);
        cout << "Sorry, you have already registered for " << student.getUnitName(unitIndex) << " in another group!" << endl;
        resetColor();
        beepSound();
        sleepFor(1000);
        pressAnyKeyToContinue();
        loadingMessage("Loading grouping registration module");
        return;
    }

    if (student.getGroupSlot(groupIndex, unitIndex) <= 0) {
        setColor(12);
        cout << "Sorry, no available slot for group " << student.getGroupName(groupIndex) << " for " << student.getUnitName(unitIndex) << endl;
        resetColor();
        beepSound();
        sleepFor(1000);
        pressAnyKeyToContinue();
        loadingMessage("Loading grouping registration module");
        return;
    }

    if (student.isAlreadyRegistered(groupIndex, unitIndex)) {
        setColor(12);
        cout << "Sorry, you have previously registered into " << student.getGroupName(groupIndex) << " for " << student.getUnitName(unitIndex) << "!" << endl;
        resetColor();
        beepSound();
        sleepFor(1000);
        pressAnyKeyToContinue();
        loadingMessage("Loading grouping registration module");
        return;
    }

    student.registerUnit(groupIndex, unitIndex);
    database.updateGroupSlots(groupIndex, unitIndex);
    setColor(10);
    cout << "You have successfully registered into " << student.getGroupName(groupIndex) << " for " << student.getUnitName(unitIndex) << "!" << endl;
    resetColor();
    beepSound();
    sleepFor(1000);
    pressAnyKeyToContinue();
    loadingMessage("Loading grouping registration module");
}

void groupingRecordModule(Student &student) {
    clearScreen();
    cout << "Welcome to Grouping Record Module, " << student.getName() << "!" << endl;
    cout << endl;
    cout << "Here are your registered groupings:" << endl;
    cout << endl;
    cout << "Trimester: " << student.getTrimesterString() << endl;
    cout << "Student Name: " << student.getName() << endl;
    cout << "Student ID: " << student.getId() << endl;
    cout << endl;
    cout << left << setw(30) << "Unit" << "Grouping" << endl;
    cout << "===========================" << endl;
    for (int i = 0; i < student.getRegistrationCount(); i++) {
        cout << left << setw(30) << student.getRegisteredUnit(i) << student.getRegisteredGroup(i) << endl;
    }
    cout << "===========================" << endl;
    cout << endl;

    string printChoice;
    do {
        cout << "Would you like to print your grouping record (Y/N)? ";
        getline(cin, printChoice);
        if (printChoice == "Y" || printChoice == "y" || printChoice == "N" || printChoice == "n") {
            break;
        }
        cout << "Sorry, please enter Y or N only!" << endl;
        cout << endl;
    } while (true);

    if (printChoice == "Y" || printChoice == "y") {
        cout << "Printing your grouping record..." << endl;
        student.saveToFile();
#ifdef _WIN32
        system("notepad Record.txt");
#else
        system("xdg-open Record.txt");
#endif
    }

    cout << endl;
    cout << "Returning to Main Page..." << endl;
}

void displayColorfulEnding() {
    clearScreen();
    
    setColor(14);
    displayWelcomeBanner();
    setColor(11);
    displayThankYouArt();
    resetColor();
    
    cout << endl;
    setColor(13);
    cout << "Group 1E1-A:" << endl;
    resetColor();
    
    setColor(10);
    cout << "1. Bou Socheat (p20250046)" << endl;
    setColor(11);
    cout << "2. Oum Phymean (p20250200)" << endl;
    setColor(14);
    cout << "3. Seng Sarak (p20250178)" << endl;
    setColor(9);
    cout << "4. Techsamnang Monyrak (p20250194)" << endl;
    resetColor();
    cout << endl;

    setColor(12);
    cout << "Team Member Task/Job Description" << endl;
    setColor(8);
    cout << "================================================================" << endl;
    resetColor();
    
    setColor(10);
    cout << left << setw(25) << "Bou Socheat";
    setColor(7);
    cout << "Design flowchart and Main Page" << endl;
    
    setColor(11);
    cout << left << setw(25) << "Oum Phymean";
    setColor(7);
    cout << "Design and Develop Grouping Selection Module" << endl;
    
    setColor(14);
    cout << left << setw(25) << "Seng Sarak";
    setColor(7);
    cout << "Integration of Main Page and other Modules" << endl;
    
    setColor(9);
    cout << left << setw(25) << "Techsamnang Monyrak";
    setColor(7);
    cout << "Debugging of Errors in all parts and program exit" << endl;
    resetColor();
    cout << endl;

#ifdef _WIN32
    system("start kvmrBosba.jpg");
#else
    system("xdg-open kvmrBosba.jpg");
#endif

    cout << endl;
    setColor(10);
    cout << "=====================================================" << endl;
    setColor(14);
    cout << "     Thank you for using our program!     " << endl;
    setColor(10);
    cout << "=====================================================" << endl;
    resetColor();
    cout << endl;
    
    beepSound();
    sleepFor(500);
    beepSound();
}

void exitModule(Student &student, UserDatabase &database) {
    clearScreen();
    string exitChoice;

    cout << "You are attempting to Exit the program." << endl;
    cout << endl;
    cout << "Are you sure you want to exit the program, " << student.getName() << " (ID " << student.getId() << ") Y/N?" << endl;
    cout << endl;

    do {
        cout << "Your choice: ";
        getline(cin, exitChoice);
        if (exitChoice == "Y" || exitChoice == "y" || exitChoice == "N" || exitChoice == "n") {
            break;
        }
        cout << "Sorry, please enter Y or N only!" << endl;
        cout << endl;
    } while (true);

    if (exitChoice == "N" || exitChoice == "n") {
        cout << endl;
        cout << "Returning to Main Page..." << endl;
        return;
    }

    displayColorfulEnding();
    database.logoutCurrentUser();
    exit(0);
}

void logoutModule(Student &student, UserDatabase &database) {
    clearScreen();
    string logoutChoice;

    cout << "You are attempting to Logout, " << student.getName() << " (ID " << student.getId() << ")." << endl;
    cout << endl;
    cout << "Are you sure you want to logout? (Y/N)" << endl;
    cout << endl;

    do {
        cout << "Your choice: ";
        getline(cin, logoutChoice);
        if (logoutChoice == "Y" || logoutChoice == "y" || logoutChoice == "N" || logoutChoice == "n") {
            break;
        }
        cout << "Sorry, please enter Y or N only!" << endl;
        cout << endl;
    } while (true);

    if (logoutChoice == "N" || logoutChoice == "n") {
        cout << endl;
        cout << "Returning to Main Page..." << endl;
        return;
    }

    cout << endl;
    cout << "You have been logged out successfully!" << endl;
    cout << "Returning to Login Page..." << endl;
    database.logoutCurrentUser();
}

void mainPage(Student &student, UserDatabase &database) {
    string choice;
    int menuChoice;

    do {
        clearScreen();
        cout << "Group Registration Main Page" << endl;
        cout << "Welcome, " << student.getName() << " (ID: " << student.getId() << ")" << endl;
        cout << "Trimester: " << student.getTrimesterString() << endl;
        cout << "========================================" << endl;
        cout << "1 - Register for grouping" << endl;
        cout << "2 - View/Print grouping record" << endl;
        cout << "3 - Logout" << endl;
        cout << "0 - Exit program" << endl;
        cout << endl;

        do {
            cout << "Your choice: ";
            getline(cin, choice);
            if (choice.length() == 1 && isNumeric(choice)) {
                menuChoice = stringToInt(choice);
                if (menuChoice >= 0 && menuChoice <= 3) {
                    break;
                }
            }
            cout << "Sorry, please select option 0 to 3 only!" << endl;
            cout << endl;
        } while (true);

        cout << "You have chosen option " << menuChoice << endl;

        switch (menuChoice) {
            case 1:
                loadingMessage("Loading grouping registration module");
                groupRegistrationModule(student, database);
                break;
            case 2:
                if (!student.getHasRegistered()) {
                    cout << "You have not registered using menu 1 above" << endl;
                    cout << endl;
                    cout << "Returning to Main Page..." << endl;
                } else {
                    loadingMessage("Loading Grouping Record module");
                    groupingRecordModule(student);
                }
                break;
            case 3:
                logoutModule(student, database);
                if (!student.isLoggedIn()) {
                    return;
                }
                break;
            case 0:
                loadingMessage("Loading Exit Program module");
                exitModule(student, database);
                break;
        }

    } while (true);
}

void loginPage(UserDatabase &database) {
    string choice;
    int menuChoice;

    while (true) {
        clearScreen();
        displayLoginMenu();

        do {
            cout << "Your choice: ";
            getline(cin, choice);
            if (choice.length() == 1 && isNumeric(choice)) {
                menuChoice = stringToInt(choice);
                if (menuChoice >= 0 && menuChoice <= 2) {
                    break;
                }
            }
            cout << "Sorry, please select option 0 to 2 only!" << endl;
            cout << endl;
        } while (true);

        switch (menuChoice) {
            case 1: {
                if (registerUser(database)) {
                    clearScreen();
                    semesterModule(database.getCurrentUser());
                    mainPage(database.getCurrentUser(), database);
                }
                break;
            }
            case 2: {
                if (loginUser(database)) {
                    Student &currentUser = database.getCurrentUser();
                    if (currentUser.getSemester() == 0 || currentUser.getYear() == 0) {
                        clearScreen();
                        semesterModule(currentUser);
                    }
                    mainPage(currentUser, database);
                }
                break;
            }
            case 0: {
                clearScreen();
                cout << "========================================" << endl;
                cout << "   Are you sure you want to exit?" << endl;
                cout << "========================================" << endl;
                cout << endl;
                string exitChoice;
                do {
                    cout << "Your choice (Y/N): ";
                    getline(cin, exitChoice);
                    if (exitChoice == "Y" || exitChoice == "y" || exitChoice == "N" || exitChoice == "n") {
                        break;
                    }
                    cout << "Sorry, please enter Y or N only!" << endl;
                    cout << endl;
                } while (true);

                if (exitChoice == "Y" || exitChoice == "y") {
                    displayColorfulEnding();
                    exit(0);
                }
                break;
            }
        }
    }
}

int main() {
    UserDatabase database;
    loginPage(database);
    return 0;
}
