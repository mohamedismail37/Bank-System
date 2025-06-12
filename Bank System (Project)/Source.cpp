#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

const string ClientsFileName = "ClientsData.txt";
const string UsersFileName = "Users.txt";

enum enUserInput {
	OpenLoginScreen = 0,ShowClientList = 1, AddNewClient = 2, DeleteClient = 3,
	UpdateClient = 4, FindClient = 5, Transactions = 6, ManageUsers = 7, Logout = 8
};

enum enTransactionType
{
	Deposit = 1, WithDraw = 2, TotalBalances = 3, MainMenu = 4
};

struct stClientData
{
	string AccountNumber;
	string PINCode;
	string ClientName;
	string Phone;
	double Balance;
	bool MarkToDelete = false;
};

struct stUserData
{
	string UserName;
	short Password;
	short Permession = 0;
	bool MarkToDelete = false;
};

enum enUserMenu
{ListUsers = 1, AddNewUser = 2, DeleteUser =3, UpdateUser = 4, FindUser =5, MainMenuSc = 6};

enum enUserPermission 
{ ShowClientsList = 1, AddNewClients = 2, DeleteClients = 4, UpdateClients = 8, FindClients = 16, ShowTrasactions = 32, CanManageUsers = 64 };

enUserInput MainMenuScreen()
{
	system("cls");
	short UserChoose = 0;

	cout << "====================================\n";
	printf("           Main Menu Screen\n");
	cout << "====================================\n";
	printf("        [1] Show Client List.\n");
	printf("        [2] Add New Client.\n");
	printf("        [3] Delete Client.\n");
	printf("        [4] Update Client Info.\n");
	printf("        [5] Find Client.\n");
	printf("        [6] Transactions.\n");
	printf("        [7] Manage Users.\n");
	printf("        [8] Logout.\n");
	cout << "====================================\n";

	do
	{
		cout << "Choose what do you want to do? [1 to 8]? ";
		cin >> UserChoose;
	} while (UserChoose < 1 || UserChoose > 8);

	return enUserInput(UserChoose);
}

vector <string> Splitter(string Line, string Separator = "#//#")
{
	short Position = 0;
	vector <string> vWords;
	string Word;

	while ((Position = Line.find(Separator)) != std::string::npos)
	{
		Word = Line.substr(0, Position);
		Line.erase(0, Position + Separator.length());
		vWords.push_back(Word);
	}
	if (Line != "")
	{
		vWords.push_back(Line);
	}

	return vWords;
}

stClientData FromVectorOfStringTostClientData(vector <string> vWords)
{
	stClientData ClientData;

	ClientData.AccountNumber = vWords[0];
	ClientData.PINCode = (vWords[1]);
	ClientData.ClientName = vWords[2];
	ClientData.Phone = vWords[3];
	ClientData.Balance = stod(vWords[4]);

	return ClientData;
}

void FromFileToVectorOfstClientsData(vector <stClientData>& vOfstClientsData,string FileName)
{
	fstream MyFile;
	MyFile.open(FileName, ios::in);

	if (MyFile.is_open())
	{
		string Line;

		while (getline(MyFile, Line))
		{
			vOfstClientsData.push_back(FromVectorOfStringTostClientData(Splitter(Line)));
		}
		MyFile.close();
	}

}

void GoBackToTransactionMenu()
{
	cout << "Press any key to go back to Transaction Menu...";
	system("pause>0");
}

void GoBackToMainMenu()
{
	cout << "Press any key to go back to Main Menu...";
	system("pause>0");
}

void GoBackToManageUsersMenu()
{
	cout << "\n\nPress any key to go back to Users Menu...\n";
	system("pause>0");
}

void ShowAllClientsList(vector <stClientData> vOfstClientsData)
{
	cout << right << setw(57) << "Client List (" << vOfstClientsData.size() << ") Client(s).\n";
	cout << "-----------------------------------------------------------------------------------------------------------\n";
	cout << "| Account Number   | PIN Code   | Client Name\t\t\t\t| Phone\t\t| Balance  \n";
	cout << "-----------------------------------------------------------------------------------------------------------\n";
	if (vOfstClientsData.size() == 0)
	{
		cout << "\t\t\t\tNo Clients Available In the System!";
	}
	else
	{
		for (short i = 0; i < vOfstClientsData.size(); i++)
		{
			if (vOfstClientsData[i].MarkToDelete != true)
			{
				cout << "| " << left << setw(17) << vOfstClientsData[i].AccountNumber;
				cout << "| " << setw(11) << vOfstClientsData[i].PINCode;
				cout << "| " << setw(38) << vOfstClientsData[i].ClientName;
				cout << "| " << setw(14) << vOfstClientsData[i].Phone;
				cout << "| " << vOfstClientsData[i].Balance;
				cout << endl;
			}
		}
	}
	cout << "\n-----------------------------------------------------------------------------------------------------------\n";

}

string ReadAccountNumber()
{
	string AccoutNumber;
	cout << "Please enter Account Number? ";
	cin >> AccoutNumber;

	return AccoutNumber;
}

bool IsClientFound(vector <stClientData> vOfstClientsData, string AccountNumber)
{
	for (stClientData& C : vOfstClientsData)
	{
		if (C.AccountNumber == AccountNumber)
		{
			return true;
		}
	}

	return false;
}

void AddNewClientScreen(vector <stClientData>& vOfstClientsData)
{
	char AddAgain = 'y';
	do
	{
		cout << "---------------------------------------\n";
		cout << setw(15) << "Add New Clients Screen\n";
		cout << "---------------------------------------\n";
		cout << "Adding New Client:\n\n";

		stClientData NewClient;

		string AccountNumber = ReadAccountNumber();

		while (IsClientFound(vOfstClientsData, AccountNumber))
		{
			cout << "\nClient with [" << AccountNumber << "] already exists, Enter another Account Number? ";
			cin >> AccountNumber;
		}

		// Hadhoud Putted this in a separated function
		// AddNewClient();\

		NewClient.AccountNumber = AccountNumber;
		cout << "Enter PIN Code? ";
		cin >> NewClient.PINCode;
		cout << "Client Name? ";
		getline(cin >> ws, NewClient.ClientName);
		cout << "Enter Phone? ";
		getline(cin, NewClient.Phone);
		cout << "Enter Account Balance? ";
		cin >> NewClient.Balance;

		vOfstClientsData.push_back(NewClient);

		cout << "\nClient Added Successfully, do you want to add more clients? [Y/N]? ";
		cin >> AddAgain;

	} while (AddAgain == 'y' || AddAgain == 'Y');

}

string Joinner(stClientData OneClient, string Separator = "#//#")
{
	string Line = "";
	Line += OneClient.AccountNumber + Separator;
	Line += (OneClient.PINCode) + Separator;
	Line += OneClient.ClientName + Separator;
	Line += OneClient.Phone + Separator;
	Line += to_string(OneClient.Balance);

	return Line;
}

string Joinner2(stUserData OneUser, string Separator = "#//#")
{
	string Line = "";
	Line += OneUser.UserName + Separator;
	Line += to_string(OneUser.Password) + Separator;
	Line += to_string(OneUser.Permession);

	return Line;
}

void PrintvOfstClientsInFile(vector <stClientData>& vOfstClientsData)
{
	fstream MyFile;
	MyFile.open(ClientsFileName, ios::out);

	if (MyFile.is_open())
	{
		for (stClientData& C : vOfstClientsData)
		{
			if (C.MarkToDelete == false)
			{
				MyFile << Joinner(C) << endl;
			}
		}
		MyFile.close();
	}
}

void PrintvOfstUsersInFile(vector <stUserData>& vOfstUsersData)
{
	fstream MyFile;
	MyFile.open(UsersFileName, ios::out);

	if (MyFile.is_open())
	{
		for (stUserData& C : vOfstUsersData)
		{
			if (C.MarkToDelete == false)
			{
				MyFile << Joinner2(C) << endl;
			}

		}
		MyFile.close();
	}
}

void ShowClientCard(vector <stClientData> vOfstClientsData, string AccountNumber)
{
	for (stClientData& C : vOfstClientsData)
	{
		if (C.AccountNumber == AccountNumber)
		{
			cout << "\nThe following are the client details:\n";
			cout << "---------------------------------------\n";
			cout << "Account Number  : " << C.AccountNumber;
			cout << "\nPIN Code        : " << C.PINCode;
			cout << "\nName            : " << C.ClientName;
			cout << "\nPhone           : " << C.Phone;
			cout << "\nAccount Balance : " << C.Balance << endl;
			cout << "---------------------------------------\n";
			break;
		}
	}
}

void MarkStructToDelete(vector <stClientData>& vOfstClientsData, string AccountNumber)
{
	for (stClientData& C : vOfstClientsData)
	{
		if (C.AccountNumber == AccountNumber)
		{
			C.MarkToDelete = true;
			break;
		}
	}
}

void DeleteClientScreen(vector <stClientData>& vOfstClientsData)
{
	cout << "----------------------------------------------\n";
	cout << "\t\tDelete Client Info Screen\n";
	cout << "----------------------------------------------\n";

	string AccountNumber = ReadAccountNumber();
	if (IsClientFound(vOfstClientsData, AccountNumber))
	{
		ShowClientCard(vOfstClientsData, AccountNumber);
		char Delete;
		cout << "\n\nAre you sure you want to delete this client? {Y/N}? ";
		cin >> Delete;
		if (Delete == 'y' || Delete == 'Y')
		{
			MarkStructToDelete(vOfstClientsData, AccountNumber);
			cout << "\nClient Deleted Successfully.\n";
		}
	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!\n";
	}
}

void UpdateInfo(vector <stClientData>& vOfstClientsData, string AccountNumber)
{
	for (stClientData& C : vOfstClientsData)
	{
		if (C.AccountNumber == AccountNumber)
		{
			cout << "\nEnter PIN Code: ";
			cin >> C.PINCode;
			cout << "Enter Name: ";
			getline(cin >> ws, C.ClientName);
			cout << "Enter Phone: ";
			getline(cin, C.Phone);
			cout << "Account Balance: ";
			cin >> C.Balance;
			break;
		}
	}
}

void UpdateClientInfoScreen(vector <stClientData>& vOfstClientsData)
{

	cout << "----------------------------------------------\n";
	cout << "\t\tUpdate Client Info Screen\n";
	cout << "----------------------------------------------\n";

	string AccountNumber = ReadAccountNumber();
	if (IsClientFound(vOfstClientsData, AccountNumber))
	{
		ShowClientCard(vOfstClientsData, AccountNumber);
		char Update;
		cout << "\n\nAre you sure you want to Update this client? {Y/N}? ";
		cin >> Update;
		if (Update == 'y' || Update == 'Y')
		{
			UpdateInfo(vOfstClientsData, AccountNumber);
			cout << "\nClient Update Successfully.\n";
		}
	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!\n";
	}
}

void FindClientScreen(vector <stClientData> vOfstClientsData)
{

	cout << "----------------------------------------------\n";
	cout << "\t\tFind Client Screen\n";
	cout << "----------------------------------------------\n";

	string AccountNumber = ReadAccountNumber();
	if (IsClientFound(vOfstClientsData, AccountNumber))
	{
		ShowClientCard(vOfstClientsData, AccountNumber);
	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!\n";
	}
}

void ExitScreen()
{
	cout << "----------------------------------------------\n";
	cout << "\t\tProgram Ends :-)\n";
	cout << "----------------------------------------------\n";
}

enTransactionType TransactionMenuScreen()
{
	system("cls");
	short UserChoose = 0;

	cout << "====================================\n";
	printf("           Transaction Menu Screen\n");
	cout << "====================================\n";
	printf("        [1] Deposite.\n");
	printf("        [2] Withdraw.\n");
	printf("        [3] Total Balances.\n");
	printf("        [4] Main Menu.\n");
	cout << "====================================\n";

	do
	{
		cout << "Choose what do you want to do? [1 to 4]? ";
		cin >> UserChoose;
	} while (UserChoose < 1 || UserChoose > 4);

	return enTransactionType(UserChoose);
}

float DepositFunction(vector <stClientData>& vOfstClientsData, string AccountNumber, float Deposite)
{
	for (stClientData& C : vOfstClientsData)
	{
		if (C.AccountNumber == AccountNumber)
		{
			C.Balance += Deposite;
			return C.Balance;
		}
	}
}

void DepositScreen(vector <stClientData>& vOfstClientsData)
{
	cout << "----------------------------------------------\n";
	cout << "\t\tDeposit Screen\n";
	cout << "----------------------------------------------\n";

	float Deposit = 0;
	char Do;
	string AccountNumber = ReadAccountNumber();
	bool Found = IsClientFound(vOfstClientsData, AccountNumber);

	if (Found)
	{
		ShowClientCard(vOfstClientsData, AccountNumber);
		cout << "\nPlease enter deposit amount? ";
		cin >> Deposit;
		cout << "\n\nAre you sure you want perform this transaction? [Y/N]? ";
		cin >> Do;
		if (Do == 'y' || Do == 'Y')
		{
			cout << "Done Successfuly\nNew Balance = " << DepositFunction(vOfstClientsData, AccountNumber, Deposit) << endl;
		}
	}

	else
	{
		cout << "\nClient with Account Number [" << AccountNumber << "] is now exist\n";
		DepositScreen(vOfstClientsData);
	}
}

void ShowTotalBalances(vector <stClientData> vOfstClientsData)
{
	double TotalBalances = 0;

	cout << right << setw(57) << "Client List (" << vOfstClientsData.size() << ") Client(s).\n";
	cout << "-----------------------------------------------------------------------------------------------------------\n";
	cout << "| Account Number      | Client Name\t\t\t\t| Balance  \n";
	cout << "-----------------------------------------------------------------------------------------------------------\n";
	if (vOfstClientsData.size() == 0)
	{
		cout << "\t\t\t\tNo Clients Available In the System!";
	}
	else
	{
		for (short i = 0; i < vOfstClientsData.size(); i++)
		{
			if (vOfstClientsData[i].MarkToDelete != true)
			{
				cout << "| " << left << setw(17) << vOfstClientsData[i].AccountNumber;
				cout << "| " << setw(38) << vOfstClientsData[i].ClientName;
				cout << "| " << vOfstClientsData[i].Balance;
				cout << endl;
				TotalBalances += vOfstClientsData[i].Balance;
			}
		}
	}
	cout << "\n-----------------------------------------------------------------------------------------------------------\n";
	cout << "\t\t\t\tTotal Balances = " << TotalBalances << endl << endl;
}

double BalanceAmount(vector <stClientData> vOfstClientsData, string AccountNumber)
{
	for (stClientData& C : vOfstClientsData)
	{
		if (C.AccountNumber == AccountNumber)
		{
			return C.Balance;
		}
	}
}

void WithDrawScreen(vector <stClientData>& vOfstClientsData)
{
	cout << "----------------------------------------------\n";
	cout << "\tWithdraw Screen\n";
	cout << "----------------------------------------------\n";

	float WithdrawAmount = 0;
	char Do;
	string AccountNumber = ReadAccountNumber();
	double Balance = BalanceAmount(vOfstClientsData, AccountNumber);
	if (IsClientFound(vOfstClientsData, AccountNumber))
	{
		ShowClientCard(vOfstClientsData, AccountNumber);

		cout << "\nPlease enter Withdraw amount? ";
		cin >> WithdrawAmount;

		while (WithdrawAmount > Balance)
		{
			cout << "Amount Exceed the balance, you can withdraw up to : " << Balance << endl;
			cout << "Please enter another amount? ";
			cin >> WithdrawAmount;
		}


		cout << "\n\nAre you sure you want perform this transaction? [Y/N]? ";
		cin >> Do;
		if (Do == 'y' || Do == 'Y')
		{
			cout << "Done Successfuly\nNew Balance = " << DepositFunction(vOfstClientsData, AccountNumber, WithdrawAmount * -1) << endl;
		}
	}
	else
	{
		cout << "\nClient with Account Number [" << AccountNumber << "] is Not Found!\n";
	}
}

void UserChooseForward(enUserInput UserChoose, vector <stClientData>& vOfstClientsData, stUserData UserData);

void TransactionChooseForward(enTransactionType UserChoice, vector <stClientData>& vOfstClientsData, stUserData &UserData)
{
	switch (UserChoice)
	{
	case Deposit:
		system("cls");
		DepositScreen(vOfstClientsData);
		PrintvOfstClientsInFile(vOfstClientsData);
		GoBackToTransactionMenu();
		TransactionChooseForward(TransactionMenuScreen(), vOfstClientsData, UserData);
		break;
	case WithDraw:
		system("cls");
		WithDrawScreen(vOfstClientsData);
		PrintvOfstClientsInFile(vOfstClientsData);
		GoBackToTransactionMenu();
		TransactionChooseForward(TransactionMenuScreen(), vOfstClientsData, UserData);
		break;
	case TotalBalances:
		system("cls");
		ShowTotalBalances(vOfstClientsData);
		GoBackToTransactionMenu();
		TransactionChooseForward(TransactionMenuScreen(), vOfstClientsData, UserData);
		break;
	case MainMenu:
		system("cls");
		UserChooseForward(MainMenuScreen(), vOfstClientsData, UserData);
		break;
	}
}

stUserData ReadUserData()
{
	stUserData UserData;
	cout << "Enter Username? ";
	cin >> UserData.UserName;
	cout << "Enter Password? ";
	cin >> UserData.Password;

	return UserData;
}

stUserData FromVectorOfStringTostUserData(vector <string> vWords)
{
	stUserData UserData;

	UserData.UserName = vWords[0];
	UserData.Password = stoi(vWords[1]);
	UserData.Permession = stoi(vWords[2]);

	return UserData;
}

void FromFileToVectorOfstUserData(vector <stUserData>& vOfstUsersData, string FileName)
{
	fstream MyFile;
	MyFile.open(FileName, ios::in);

	if (MyFile.is_open())
	{
		string Line;

		while (getline(MyFile, Line))
		{
			vOfstUsersData.push_back(FromVectorOfStringTostUserData(Splitter(Line)));
		}
		MyFile.close();
	}

}

bool IsUserDataCorrect(stUserData UserData)
{
	vector <stUserData> vOfstUsersData;
	FromFileToVectorOfstUserData(vOfstUsersData, UsersFileName);

	for (stUserData& C : vOfstUsersData)
	{
		if (C.UserName == UserData.UserName && C.Password == UserData.Password)
		{
			return true;
		}
	}

	return false;
}

bool IsNameExists(string UserName)
{
	vector <stUserData> vOfstUsersData;
	FromFileToVectorOfstUserData(vOfstUsersData, UsersFileName);

	for (stUserData& C : vOfstUsersData)
	{
		if (C.UserName == UserName)
		{
			return true;
		}
	}

	return false;
}

stUserData FollowTheAssinging(string UserName)
{
	vector <stUserData> vOfstUsersData;
	FromFileToVectorOfstUserData(vOfstUsersData, UsersFileName);

	for (stUserData& C : vOfstUsersData)
	{
		if (C.UserName == UserName)
		{
			return C;
		}
	}
}

void LoginScreenText()
{
	system("cls");
	printf("------------------------------\n");
	printf("           Login Screen\n");
	printf("------------------------------\n");
}

stUserData LoginScreen()
{
	LoginScreenText();
	stUserData UserData = ReadUserData();

	while (!IsUserDataCorrect(UserData)) 
	{
		LoginScreenText();
		cout << "Invalid Username/Password!\n";
		UserData = ReadUserData();
	}
	return UserData;

}

void AssingTheInputUserToHimInFile(stUserData &UserData,vector <stUserData> vOfstUserData)
{
	UserData = FollowTheAssinging(UserData.UserName);
}

void Login()
{	
	vector <stClientData> vOfstClientsData;
	vector <stUserData> vOfstUserData;

	FromFileToVectorOfstClientsData(vOfstClientsData,ClientsFileName);
	FromFileToVectorOfstUserData(vOfstUserData, UsersFileName);

	stUserData UserData = LoginScreen();
	AssingTheInputUserToHimInFile(UserData, vOfstUserData);

	UserChooseForward(enUserInput::OpenLoginScreen, vOfstClientsData, UserData);

}

enUserMenu ManageUsersMenuScreen()
{
	system("cls");
	short UserChoice = 0;
	cout << "====================================\n";
	printf("           Manage Users Menu Screen\n");
	cout << "====================================\n";
	printf("        [1] List Users.\n");
	printf("        [2] Add New User.\n");
	printf("        [3] Delete User.\n");
	printf("        [4] Update User.\n");
	printf("        [5] Find User.\n");
	printf("        [6] Main Menu.\n");
	cout << "====================================\n";

	do
	{
		cout << "Choose what do you want to do? [1 to 6]? ";
		cin >> UserChoice;
	} while (UserChoice < 1 || UserChoice >6);

	return enUserMenu(UserChoice);
}

void UsersList(vector <stUserData> vOfstUsersData)
{
	system("cls");

	cout << right << setw(57) << "Users List (" << vOfstUsersData.size() << ") User(s).\n";
	cout << "-----------------------------------------------------------------------------------------------------------\n";
	cout << "| User Name   | Password   | Permission  \n";
	cout << "-----------------------------------------------------------------------------------------------------------\n";

	for (short i = 0; i < vOfstUsersData.size(); i++)
	{

		cout << "| " << left << setw(12) << vOfstUsersData[i].UserName;
		cout << "| " << setw(11) << vOfstUsersData[i].Password;
		cout << "| " << setw(38) << vOfstUsersData[i].Permession;
		cout << endl;

	}
	cout << "\n-----------------------------------------------------------------------------------------------------------\n";

	GoBackToManageUsersMenu();
}

bool GiveFullAccess()
{
	char FullAccess;
	cout << "\nDo you want to give full access? (Y/N)? ";
	cin >> FullAccess;
	if (FullAccess == 'y' || FullAccess == 'Y')
		return true;
	else
		return false;
}

void Permissions(stUserData& UserData)
{
	char YesOrNo;

	cout << "\nShow Client List? y/n? ";
	cin >> YesOrNo;
	if (YesOrNo == 'y' || YesOrNo == 'Y')
	{
		UserData.Permession += enUserPermission::ShowClientsList;
	}
	cout << "\nAdd New Client? y/n? ";
	cin >> YesOrNo;
	if (YesOrNo == 'y' || YesOrNo == 'Y')
	{
		UserData.Permession += enUserPermission::AddNewClients;
	}

	cout << "\nDelete Client? y/n? ";
	cin >> YesOrNo;
	if (YesOrNo == 'y' || YesOrNo == 'Y')
	{
		UserData.Permession += enUserPermission::DeleteClients;
	}
	cout << "\nUpdate Client? y/n? ";
	cin >> YesOrNo;
	if (YesOrNo == 'y' || YesOrNo == 'Y')
	{
		UserData.Permession += enUserPermission::UpdateClients;
	}
	cout << "\nFind Client? y/n? ";
	cin >> YesOrNo;
	if (YesOrNo == 'y' || YesOrNo == 'Y')
	{
		UserData.Permession += enUserPermission::FindClients;
	}
	cout << "\nTransactions? y/n? ";
	cin >> YesOrNo;
	if (YesOrNo == 'y' || YesOrNo == 'Y')
	{
		UserData.Permession += enUserPermission::ShowTrasactions;
	}

	cout << "\nManage Users? y/n? ";
	cin >> YesOrNo;

	if (YesOrNo == 'y' || YesOrNo == 'Y')
	{
		UserData.Permession += enUserPermission::CanManageUsers;
	}

}

void AddNewUserScreen(vector <stUserData>& vOfstUsersData)
{
	system("cls");
	cout << "---------------------------------------\n";
	printf ("        Add New User Screen\n");
	cout << "---------------------------------------\n";

	char AddAgain = 'y';
	do
	{
		cout << "Adding New User:\n\n";

		stUserData NewUser;
		cout << "Enter Username? ";
		cin >> NewUser.UserName;

		while (IsNameExists(NewUser.UserName))
		{
			cout << "\nUser with [" << NewUser.UserName << "] already exists, Enter another UserName? ";
			cin >> NewUser.UserName;
		}
		cout << "Enter Password? ";
		cin >> NewUser.Password;

		if (GiveFullAccess())
		{
			NewUser.Permession = -1;
		}
		else
		{
			Permissions(NewUser);
		}

		vOfstUsersData.push_back(NewUser);
		PrintvOfstUsersInFile(vOfstUsersData);

		cout << "\nUser Added Successfully, do you want to add more clients? [Y/N]? ";
		cin >> AddAgain;

	} while (AddAgain == 'y' || AddAgain == 'Y');

	GoBackToManageUsersMenu();

}

void ShowUserCard(vector <stUserData> vOfstUserssData, string Username)
{
	for (stUserData& C : vOfstUserssData)
	{
		if (C.UserName == Username)
		{
			cout << "\nThe following are the User details:\n";
			cout << "---------------------------------------\n";
			cout << "Username        : " << C.UserName;
			cout << "\nPassword        : " << C.Password;
			cout << "\nPermissions     : " << C.Permession;
			cout << "\n---------------------------------------\n";
			break;
		}
	}
}

void MarkUserToDelete(vector <stUserData>& vOfstUsersData, string UserName)
{
	for (stUserData& C : vOfstUsersData)
	{
		if (C.UserName == UserName)
		{
			C.MarkToDelete = true;
			break;
		}
	}
}

void DeleteUsersScreen(vector <stUserData>& vOfstUsersData)
{
	system("cls");
	cout << "---------------------------------------\n";
	printf("        Delete Users Screen\n");
	cout << "---------------------------------------\n";

	char ConfirmDelete;

	stUserData DeleteUser;
	cout << "Please enter Username? ";
	cin >> DeleteUser.UserName;

	if (!IsNameExists(DeleteUser.UserName))
	{
		cout << "\nUser with Username [" << DeleteUser.UserName << "] is Not Found!\n";
	}
	else if (DeleteUser.UserName == "Admin")
	{
		cout << "\n\nYou cannot Delete This User.\n";
	}
	else
	{
		ShowUserCard(vOfstUsersData, DeleteUser.UserName);
		cout << "\nAre you sure you want to delete this User? [Y/N]? ";
		cin >> ConfirmDelete;

		if (ConfirmDelete == 'y' || ConfirmDelete == 'Y')
		{
			MarkUserToDelete(vOfstUsersData, DeleteUser.UserName);
			PrintvOfstUsersInFile(vOfstUsersData);
			cout << "\nUser Deleted Successfully.\n";
		}
	}

	GoBackToManageUsersMenu();

}

void UpdatedUserInfo(vector <stUserData>& vOfstUsersData, string UserName)
{
	for (stUserData &C : vOfstUsersData)
	{
		if (C.UserName == UserName)
		{
			cout << "\nEnter Password? ";
			cin >> C.Password;
			if (GiveFullAccess())
			{
				C.Permession = -1;
			} 
			else
			{
				C.Permession = 0;
				Permissions(C);
			}
		}
	}
}

void UpdateUserScreen(vector <stUserData>& vOfstUsersData)
{
	system("cls");
	cout << "---------------------------------------\n";
	printf("        Update Users Screen\n");
	cout << "---------------------------------------\n";

	char ConfirmUpdate;

	stUserData UpdateUser;
	cout << "Please enter Username? ";
	cin >> UpdateUser.UserName;

	if (!IsNameExists(UpdateUser.UserName))
	{
		cout << "\nUser with Username [" << UpdateUser.UserName << "] is Not Found!\n";
	}
	else
	{
		ShowUserCard(vOfstUsersData, UpdateUser.UserName);
		cout << "\nAre you sure you want to update this User? [Y/N]? ";
		cin >> ConfirmUpdate;
		if (ConfirmUpdate == 'y' || ConfirmUpdate == 'Y')
		{
			UpdatedUserInfo(vOfstUsersData, UpdateUser.UserName);
			PrintvOfstUsersInFile(vOfstUsersData);
			cout << "\n\nUser Updated Successfully.\n";
		}
	}

	GoBackToManageUsersMenu();

}

void ShowUserCardScreen(vector <stUserData> vOfstUsersData)
{
	system("cls");
	cout << "---------------------------------------\n";
	printf("        Find Users Screen\n");
	cout << "---------------------------------------\n";

	stUserData UpdateUser;
	cout << "Please enter Username? ";
	cin >> UpdateUser.UserName;

	if (!IsNameExists(UpdateUser.UserName))
	{
		cout << "\nUser with Username [" << UpdateUser.UserName << "] is Not Found!\n";
	}
	else
	{
		ShowUserCard(vOfstUsersData, UpdateUser.UserName);
	}

	GoBackToManageUsersMenu();
}

void UsersMenuChoiceForward(enUserMenu UserMenuChoice, vector <stClientData>& vOfstClientsData,stUserData &UserData)
{
	vector <stUserData> vOfstUsersData;
	FromFileToVectorOfstUserData(vOfstUsersData, UsersFileName);

	switch (UserMenuChoice)
	{
	case ListUsers:
		UsersList(vOfstUsersData);
		UsersMenuChoiceForward(ManageUsersMenuScreen(), vOfstClientsData,UserData);
		break;
	case AddNewUser:
		AddNewUserScreen(vOfstUsersData);
		UsersMenuChoiceForward(ManageUsersMenuScreen(), vOfstClientsData, UserData);
		break;
	case DeleteUser:
		DeleteUsersScreen(vOfstUsersData);
		UsersMenuChoiceForward(ManageUsersMenuScreen(), vOfstClientsData, UserData);
		break;
	case UpdateUser:
		UpdateUserScreen(vOfstUsersData);
		UsersMenuChoiceForward(ManageUsersMenuScreen(), vOfstClientsData, UserData);
		break;
	case FindUser:
		ShowUserCardScreen(vOfstUsersData);
		UsersMenuChoiceForward(ManageUsersMenuScreen(), vOfstClientsData, UserData);
		break;
	case MainMenuSc:
		system("cls");
		UserChooseForward(MainMenuScreen(), vOfstClientsData,UserData);
		break;
	}
}

bool IsAllowed(stUserData UserData,enUserPermission UserChoose)
{
	if (UserData.Permession == -1)
		return true;

	switch (UserChoose)
	{
	case ShowClientsList:
		return (UserData.Permession & ShowClientList) ? true : false;
		break;
	case AddNewClients:
		return (UserData.Permession & AddNewClients) ? true : false;
		break;
	case DeleteClients:
		return (UserData.Permession & DeleteClients) ? true : false;
		break;
	case UpdateClients:
		return (UserData.Permession & UpdateClients) ? true : false;
		break;
	case FindClients:
		return (UserData.Permession & FindClients) ? true : false;
		break;
	case ShowTrasactions:
		return (UserData.Permession & ShowTrasactions) ? true : false;
		break;
	case CanManageUsers:
		return (UserData.Permession & CanManageUsers) ? true : false;
		break;

	}
}

void NotAllowedScreen()
{
	cout << "\n-----------------------------------------\n";
	cout << "Access Denied,\n";
	cout << "You don't Have Permission To Do this,\n";
	cout << "Please Contact Your Admin.\n";
	cout << "\n-----------------------------------------\n";
}

void UserChooseForward(enUserInput UserChoose, vector <stClientData>& vOfstClientsData, stUserData UserData)
{
	switch (UserChoose)
	{
	case OpenLoginScreen:
		system("cls");
		UserChooseForward(MainMenuScreen(), vOfstClientsData, UserData);
		break;
	case ShowClientList:
		system("cls");
		if (IsAllowed(UserData,enUserPermission::ShowClientsList))
		{
			ShowAllClientsList(vOfstClientsData);
			GoBackToMainMenu();
			UserChooseForward(MainMenuScreen(), vOfstClientsData, UserData);
		}
		else
		{
			NotAllowedScreen();
			GoBackToMainMenu();
			UserChooseForward(MainMenuScreen(), vOfstClientsData, UserData);
		}
		break;
	case AddNewClient:
		system("cls");
		if (IsAllowed(UserData, enUserPermission::AddNewClients))
		{
			AddNewClientScreen(vOfstClientsData);
			PrintvOfstClientsInFile(vOfstClientsData);
			GoBackToMainMenu();
			UserChooseForward(MainMenuScreen(), vOfstClientsData, UserData);
		}
		else
		{
			NotAllowedScreen();
			GoBackToMainMenu();
			UserChooseForward(MainMenuScreen(), vOfstClientsData, UserData);
		}
		break;
	case DeleteClient:
		system("cls");
		if (IsAllowed(UserData, enUserPermission::DeleteClients))
		{
			DeleteClientScreen(vOfstClientsData);
			PrintvOfstClientsInFile(vOfstClientsData);
			GoBackToMainMenu();
			UserChooseForward(MainMenuScreen(), vOfstClientsData, UserData);
		}
		else
		{
			NotAllowedScreen();
			GoBackToMainMenu();
			UserChooseForward(MainMenuScreen(), vOfstClientsData, UserData);
		}
		break;
	case UpdateClient:
		system("cls");
		if (IsAllowed(UserData, enUserPermission::UpdateClients))
		{
			UpdateClientInfoScreen(vOfstClientsData);
			PrintvOfstClientsInFile(vOfstClientsData);
			GoBackToMainMenu();
			UserChooseForward(MainMenuScreen(), vOfstClientsData, UserData);
		}
		else
		{
			NotAllowedScreen();
			GoBackToMainMenu();
			UserChooseForward(MainMenuScreen(), vOfstClientsData, UserData);
		}
		break;
	case FindClient:
		system("cls");
		if (IsAllowed(UserData, enUserPermission::FindClients))
		{
			FindClientScreen(vOfstClientsData);
			GoBackToMainMenu();
			UserChooseForward(MainMenuScreen(), vOfstClientsData, UserData);
		}
		else
		{
			NotAllowedScreen();
			GoBackToMainMenu();
			UserChooseForward(MainMenuScreen(), vOfstClientsData, UserData);
		}
		break;
	case Transactions:
		system("cls");
		if (IsAllowed(UserData, enUserPermission::ShowTrasactions))
		{
			TransactionChooseForward(TransactionMenuScreen(), vOfstClientsData, UserData);
		}
		else
		{
			NotAllowedScreen();
			GoBackToMainMenu();
			UserChooseForward(MainMenuScreen(), vOfstClientsData, UserData);
		}
		break;
	case ManageUsers:
		system("cls");
		if (IsAllowed(UserData, enUserPermission::CanManageUsers))
		{
			UsersMenuChoiceForward(ManageUsersMenuScreen(), vOfstClientsData, UserData);
		}
		else
		{
			NotAllowedScreen();
			GoBackToMainMenu();
			UserChooseForward(MainMenuScreen(), vOfstClientsData, UserData);
		}
		break;
	case Logout:
		Login();
	}
}

int main()
{	
	Login();

	return 0;
}
