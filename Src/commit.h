#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include "All.h"


class Commit
{
public:
	string folderPath;
	fstream commitlogFile;
	vector<int> commitNumbers;
	vector<string> commitPaths;

	Commit()
	{
		folderPath = "C:\\Users\\HP\\Desktop\\Data Structures Project\\.git\\branches\\Initial Branch\\commits\\";
		fs::create_directories(folderPath);
		commitPaths.push_back(folderPath);
		commitNumbers.push_back(0);

	}

	void commit(const string& currentBranch)
	{
		int index;
		bool found = 0;
		for (int i = 0; i < commitPaths.size(); i++)
		{
			if (commitPaths[i] == currentBranch)
			{
				index = i;
				found = 1;
				break;
			}
		}

		int commitNumber = 0;

		if(found)
			commitNumber = ++commitNumbers[index];
		else
		{
			commitPaths.push_back(currentBranch);
			commitNumbers.push_back(0);
		}
		
		fs::create_directories(currentBranch + "commits\\commit" + to_string(commitNumber));
		commitlogFile.open(currentBranch + "commitlog.txt", ios::app);

		commitlogFile << "Commit Number: " << commitNumber << endl;
		time_t currentTime = time(nullptr);
		tm localTime;
		localtime_s(&localTime, &currentTime); 
		commitlogFile << "Date and Time: "<< put_time(&localTime, "%Y-%m-%d %H:%M:%S")<< endl;

		commitlogFile << "Commit Message: " << endl;
		string message;
		cin.ignore();
		cout << "Enter your commit message: ";
		getline(cin, message);
		commitlogFile << message << endl;

		cout << "How many files do you want to commit? :  ";
		int fileCount;
		cin >> fileCount;

		vector<string> files;

		for (int i = 0; i < fileCount; i++)
		{
			string fileName;
			cout << "Enter the file name with extension : ";
			cin >> fileName;
			files.push_back(fileName);
		}

		for (int i = 0; i < fileCount; i++)
			fs::copy_file("C:\\Users\\HP\\Desktop\\Data Structures Project\\txt files\\" + files[i], currentBranch + "commit" + to_string(commitNumber) + "\\" + files[i], fs::copy_options::overwrite_existing);

		commitlogFile << "Files Committed: " << endl;
		for (int i = 0; i < fileCount; i++)
			commitlogFile << i+1 << ". " << files[i] << endl;
		commitlogFile << "----------------------------------------------------" << endl;
		commitlogFile << endl;
	}

	void displayCommitLog(const string& currentBranch)
	{
		commitlogFile.open(currentBranch + "commitlog.txt", ios::in);
		if (!commitlogFile.is_open())
		{
			cout << "Error: Could not open the commit log file!" << endl;
			return;
		}
		string line;
		while (getline(commitlogFile, line))
			cout << line << endl;
		commitlogFile.close();
	}

	void menu(string branchName)
	{
		cout << "1. Commit" << endl;
		cout << "2. Display Commit Log" << endl;
		cout << "Enter your choice: ";
		int choice;
		cin >> choice;
		switch (choice)
		{
		case 1:
			commit(branchName);
			break;
		case 2:
			displayCommitLog(branchName);
			break;
		default:
			cout << "Invalid choice!" << endl;
		}
	}
};