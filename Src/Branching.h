#pragma once

#include "All.h"


class Branching
{
public:
    string currentBranch;
    Branching() : currentBranch("C : \\Users\\HP\\Desktop\\Data Structures Project\\.git\\branches\\Initial Branch\\") {}

	string getCurrentBranch(){	return currentBranch;}

	void createBranch()
	{
		string branchName;
		cout << "Enter the name of the new Branch: ";
		cin.ignore();
		getline(cin, branchName);

		string currentFolderPath = "C:\\Users\\HP\\Desktop\\Data Structures Project\\.git\\branches";
		string branchFolder = currentFolderPath + "\\" + branchName + "\\Node Files\\";

		if (fs::exists(branchFolder))
		{
			cout << "Error: Branch folder already exists!" << endl;
			return;
		}

		fs::create_directories(branchFolder);

		for (const auto& entry : fs::directory_iterator("C:\\Users\\HP\\Desktop\\Data Structures Project\\.git\\branches\\Initial Branch\\Node Files\\"))
		{
			const string sourceFile = entry.path().string();
			string destinationFile = branchFolder + entry.path().filename().string();

			if (fs::is_regular_file(entry))
				fs::copy(sourceFile, destinationFile, fs::copy_options::overwrite_existing);
		}

		cout << "Branch '" << branchName << "' created successfully." << endl;
		currentBranch = branchFolder;
	}


    void switchBranch()
    {
        string parentDirectory = "C:\\Users\\HP\\Desktop\\Data Structures Project\\.git\\branches\\";
        vector<string> branchesNames;

        for (const auto& entry : fs::directory_iterator(parentDirectory))
        {
            if (fs::is_directory(entry)) 
                branchesNames.push_back(entry.path().filename().string());
        }

		cout << "Available Branches: " << endl;

		for (int i = 0; i < branchesNames.size(); i++)
			cout << i + 1 << ". " << branchesNames[i] << endl;

		cout << "Enter the number of the branch you want to switch to: ";
		int branchNumber;
		cin >> branchNumber;
		if (branchNumber < 1 || branchNumber > branchesNames.size())
		{
			cout << "Error: Invalid branch number!" << endl;
			return;
		}
		string branchFolder = parentDirectory + branchesNames[branchNumber - 1];
		currentBranch = branchFolder;
		cout << "Switched to branch '" << branchesNames[branchNumber - 1] << "'." << endl;
    }

	void deleteBranch()
	{
		string parentDirectory = "C:\\Users\\HP\\Desktop\\Data Structures Project\\.git\\branches\\";
		vector<string> branchesNames;
		for (const auto& entry : fs::directory_iterator(parentDirectory))
		{
			if (fs::is_directory(entry))
				branchesNames.push_back(entry.path().filename().string());
		}
		cout << "Available Branches: " << endl;
		for (int i = 0; i < branchesNames.size(); i++)
			cout << i + 1 << ". " << branchesNames[i] << endl;
		cout << "Enter the number of the branch you want to delete: ";
		int branchNumber;
		cin >> branchNumber;
		if (branchNumber < 1 || branchNumber > branchesNames.size())
		{
			cout << "Error: Invalid branch number!" << endl;
			return;
		}
		string branchFolder = parentDirectory + branchesNames[branchNumber - 1];
		fs::remove_all(branchFolder);
		cout << "Branch '" << branchesNames[branchNumber - 1] << "' deleted successfully." << endl;
	}

	void mergeBranch()
	{
		string parentDirectory = "C:\\Users\\HP\\Desktop\\Data Structures Project\\.git\\branches\\";
		vector<string> branchesNames;

		for (const auto& entry : fs::directory_iterator(parentDirectory))
		{
			if (fs::is_directory(entry))
				branchesNames.push_back(entry.path().filename().string());
		}

		cout << "Available Branches: " << endl;
		for (int i = 0; i < branchesNames.size(); i++)
			cout << i + 1 << ". " << branchesNames[i] << endl;

		cout << "Your current branch is: " << currentBranch << endl;
		cout << "Enter the number of the branch you want to merge with the current branch: ";
		int branchNumber;
		cin >> branchNumber;
		if (branchNumber < 1 || branchNumber > branchesNames.size())
		{
			cout << "Error: Invalid branch number!" << endl;
			return;
		}
		string branchFolder = parentDirectory + branchesNames[branchNumber - 1];
		for (const auto& entry : fs::directory_iterator(branchFolder))
		{
			const string& sourceFile = entry.path().string();
			string destinationFile = currentBranch + "\\" + entry.path().filename().string();

			if (fs::is_regular_file(entry))
				fs::copy(sourceFile, destinationFile);
		}
		cout << "Branch '" << branchesNames[branchNumber - 1] << "' merged successfully." << endl;
	}

	void menu()
	{
		int choice;
		cout << "1. Create a new branch" << endl;
		cout << "2. Switch to a branch" << endl;
		cout << "3. Delete a branch" << endl;
		cout << "4. Merge a branch" << endl;
		cout << "5. Display all branches" << endl;
		cout << "Enter your choice: ";
		cin >> choice;
		switch (choice)
		{
		case 1:
			createBranch();
			break;
		case 2:
			switchBranch();
			break;
		case 3:
			deleteBranch();
			break;
		case 4:
			mergeBranch();
			break;
		case 5:
			displayAllBranches();
			break;
		default:
			cout << "Invalid choice!" << endl;
		}
	}

	void displayAllBranches()
	{
		string parentDirectory = "C:\\Users\\HP\\Desktop\\Data Structures Project\\.git\\branches\\";
		vector<string> branchesNames;

		for (const auto& entry : fs::directory_iterator(parentDirectory))
		{
			if (fs::is_directory(entry))
				branchesNames.push_back(entry.path().filename().string());
		}

		cout << "Available Branches: " << endl;

		for (int i = 0; i < branchesNames.size(); i++)
			cout << i + 1 << ". " << branchesNames[i] << endl;
	}
};
