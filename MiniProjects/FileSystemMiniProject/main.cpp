#include <iostream>
#include <string>
#include <vector>

// Representing files and directories with the help of classes
class File {
    public:
    std::string name, content;
};

class Directory {
    public:
    std::string name;
    std::vector<File*> files;
    std::vector<Directory*> subDirs;
    Directory* parent;
};

// Creating the base of the file system, the root
Directory* createRootDirectory() {
    Directory* root = new Directory;
    root->name = "root";
    root->parent = nullptr;
    return root;
}

// Clears everything inside the directory inputed as the parameter
void clearDirectory(Directory* dir) {
    // Delete all files in the root
    for (auto* file : dir->files) {
        delete file;
    }
    dir->files.clear();

    // Delete all subdirectories in the root
    for (auto* subDir : dir->subDirs) {
        clearDirectory(subDir);
        delete subDir;
    }
    dir->subDirs.clear();
}

// Functionality 1: Creating a new file and saving it into the directory user is in
void createNewFile(Directory* dir, const std::string& fileName, const std::string& fileContents)
{
    File* newFile = new File{fileName, fileContents};
    dir->files.push_back(newFile);
    std::cout << "File, " << fileName << " has been created in directory, " << dir->name << ".\n";
}

// Functionality 2: Creating a new directory and saving it into the directory user is in
void createNewDirectory(Directory* parentDir, const std::string& dirName)
{
    Directory* newDirectory = new Directory;
    newDirectory->name = dirName;
    newDirectory->parent = parentDir;
    parentDir->subDirs.push_back(newDirectory);
    std::cout << "Directory, " << dirName << " has been created inside " << parentDir->name << ".\n";
}

// Functionality 3: Deleting a file by inputing its name
void deleteFile(Directory* dir, const std::string& fileName)
{
    for (auto targetedFile = dir->files.begin(); targetedFile != dir->files.end(); targetedFile++) {
        if ((*targetedFile)->name == fileName) {
            delete *targetedFile;
            dir->files.erase(targetedFile);
            std::cout << fileName << " has been successfully deleted!\n";
            return;
        }
    }
    std::cout << "File, " << fileName << " not found. Returning...\n";
}

// Functionality 4: Deleting a directory by inputing its name
void deleteDirectory(Directory* dir, const std::string& dirName)
{
    for (auto targetedDir = dir->subDirs.begin(); targetedDir != dir->subDirs.end(); targetedDir++) {
        if ((*targetedDir)->name == dirName) {
            clearDirectory(*targetedDir);
            delete *targetedDir;
            dir->subDirs.erase(targetedDir);
            std::cout << dirName << " has been successfuly deleted!\n";
            return;
        }
    }
    std::cout << "Directory, " << dirName << " not found. Returning...\n";
}

// Functionality 5: Lists all the contents in the directory user is in
void listAllContents(Directory* dir) 
{
    std::cout << "List of every content in directory, " << dir->name << ":\n";
    for (const auto& file : dir->files) {
        std::cout << "File name: " << file->name << "\n";
    }
    for (const auto& subDir : dir->subDirs) {
        std::cout << "Directory name: " << subDir->name << "\n";
    }
}

// Functionality 6: Moves the user from one directory to the directory which name is inputed
Directory* changeDirectory(Directory* currentDir, const std::string& dirName)
{
    if (dirName == "..")
    {
        if (currentDir->parent) {
            return currentDir->parent;
        } else {
            std::cout << "Already at the root directory.\n";
            return currentDir;
        }
    }

    for (auto* subDir : currentDir->subDirs) {
        if (subDir->name == dirName){
            return subDir;
        }
    }
    std::cout << "Directory not found.\n";
    return currentDir;
}

int main()
{
    // Creates the base and places user into it
    Directory* root = createRootDirectory();
    Directory* currentDir = root;

    int option;
    std::string name, content;

    std::cout << "Welcome to my simple file system!\n";

    do {
        std::cout << "Current directory: " << currentDir->name << "\n";
        std::cout << "These are the features available: \n1. Create File\n2. Create Directory\n3. Delete File\n4. Delete Directory\n5. List Contents\n6. Change Directory\n7. Exit\n";
        std::cout << "Enter your choice ( 1, 2, 3, 4, 5, 6 or 7): "; std::cin >> option;
        std::cin.ignore();

        // Utilizes switch to ensure correct code block is executed after user's input
        switch (option) {
            case 1:
            std::cout << "Enter new file name: ";
            std::getline(std::cin, name);
            std::cout << "Enter the file contents: ";
            std::getline(std::cin, content);
            createNewFile(currentDir, name, content);
            break;

            case 2:
            std::cout << "Enter new directory name: ";
            std::getline(std::cin, name);
            createNewDirectory(currentDir, name);
            break;

            case 3:
            std::cout << "Enter the name of the file to delete: ";
            std::getline(std::cin, name);
            deleteFile(currentDir,name);
            break;

            case 4:
            std::cout << "Enter the name of the directory to delete: ";
            std::getline(std::cin, name);
            deleteDirectory(currentDir, name);
            break;

            case 5:
            listAllContents(currentDir);
            break;

            case 6:
            std::cout << "Enter the name of the directory to change to (Enter .. to change to parent): ";
            std::getline(std::cin, name);
            currentDir = changeDirectory(currentDir, name);
            break;

            case 7:
            std::cout << "Exiting the system...\n";
            break;

            default:
            std::cout << "Invalid input";
        }
    } while (option != 7);

    // Clears everything inside the root, then deletes the root
    clearDirectory(root);
    delete root;
    root = nullptr;
    return 0;
}
