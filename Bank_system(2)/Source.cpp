#include<iostream>
#include<fstream>
#include<iomanip>
#include<vector>
#include<cctype>
#include<string>
using namespace std;
const string FileName = "file.txt";
void MainMenueScreen();
void TransactionsScreen();
struct sClient {
	string AccountNumber = "";
	string PINcode = "";
	string Name = "";
	string Phone = "";
	double AccountBalance = 0;


};
enum enOptionScreen {
	ClientList = 1,
	AddNewClientS = 2,
	DeleteClientS = 3,
	UpdateClientS = 4,
	FindeClientS = 5,
	Transactions = 6,
	Exit = 7

};
enum enOptionTransactionsScreen {
	Deposit = 1,
	Withdraw = 2,
	TotalBalances = 3,
	MainMenue = 4,
};
void printClient(sClient Client) {
	cout << "\nthe following are the client details :\n\n";
	cout << "----------------------------------\n";
	cout << "Account Number : " << Client.AccountNumber << endl;
	cout << "Pin code : " << Client.PINcode << endl;
	cout << "Name : " << Client.Name << endl;
	cout << "Phone : " << Client.Phone << endl;
	cout << "Account Balance : " << Client.AccountBalance << endl;
	cout << "----------------------------------\n";
}
vector<string> split(string Line, string separator = "#//#") {
	int pos = 0;
	string word = "";
	vector<string> vClient;
	while ((pos = Line.find(separator)) != std::string::npos) {
		word = Line.substr(0, pos);
		if (word != "")
		{
			vClient.push_back(word);
		}
		Line.erase(0, pos + separator.length());

	}
	if (Line != "")
	{
		vClient.push_back(Line);
	}
	return vClient;
}
string ReadAccountNumber() {
	string number;
	cout << "\nplease enter Account Number?";
	getline(cin >> ws, number);
	return number;
}
sClient LineToRecord(string Line) {
	sClient Client;
	vector<string> vClient = split(Line);
	Client.AccountNumber = vClient[0];
	Client.PINcode = vClient[1];
	Client.Name = vClient[2];
	Client.Phone = vClient[3];
	Client.AccountBalance = stod(vClient[4]);

	return Client;
}
void AddNewClientToFile(string Line) {
	fstream file;
	file.open(FileName, ios::out | ios::app);
	while (file.is_open()) {

		file << Line << endl;
		file.close();
	}


}
string RecordToLine(sClient Client, string separator = "#//#") {
	string Line = "";
	Line += Client.AccountNumber + separator;
	Line += Client.PINcode + separator;
	Line += Client.Name + separator;
	Line += Client.Phone + separator;
	Line += to_string(Client.AccountBalance);
	return Line;
}
vector<sClient> LoadClientFromFile() {
	vector<sClient> vClients;
	sClient Client;
	fstream file;
	string Line;
	file.open(FileName, ios::in);
	while (file.is_open()) {
		while (getline(file, Line))
		{

			Client = LineToRecord(Line);
			vClients.push_back(Client);

		}
		file.close();
	}
	return vClients;
}
bool SearchByAccountNumber(string AccountNumber, sClient& C) {
	vector<sClient> vClients = LoadClientFromFile();

	for (sClient& Client : vClients)
	{
		if (Client.AccountNumber == AccountNumber) {
			C = Client;
			return false;
		}

	}
	return true;

}
double ReadDeposit() {
	double num;
	cout << "Please Enter deposit amount ?";
	cin >> num;
	while (num < 0)
	{
		cout << "Amount is Negtive = " << num << endl;
		cout << "Please Enter another amount (postive) ?";
		cin >> num;
	}
	return num;

}
double ReadWithdraw(sClient& c) {
	double num;
	cout << "Please Enter Withdraw amount ?";
	cin >> num;
	while (num < 0)
	{
		cout << "Amount is Negtive = " << num << endl;
		cout << "Please Enter another amount (postive) ?";
		cin >> num;
	}
	while (num > c.AccountBalance)
	{
		cout << "Amount exceeds the Balnce, you can withdraw up to :" << c.AccountBalance << endl;
		cout << "Please Enter another amount ?";
		cin >> num;
	}


	return num;

}
double DepositToAccount(double DepositAmount, string AccountNumber) {
	vector<sClient> vClients = LoadClientFromFile();
	fstream file;
	double AfterDeposit = 0;
	file.open(FileName, ios::out);
	while (file.is_open()) {
		for (sClient& client : vClients)
		{
			if (client.AccountNumber == AccountNumber)
			{
				client.AccountBalance += DepositAmount;
				file << RecordToLine(client) << endl;
				AfterDeposit = client.AccountBalance;
			}
			else
			{
				file << RecordToLine(client) << endl;
			}
		}

		file.close();
	}
	return 	AfterDeposit;
}
double WithdrawToAccount(double DepositAmount, string AccountNumber) {
	vector<sClient> vClients = LoadClientFromFile();
	fstream file;
	double AfterWithdraw = 0;
	file.open(FileName, ios::out);
	while (file.is_open()) {
		for (sClient& client : vClients)
		{
			if (client.AccountNumber == AccountNumber)
			{
				client.AccountBalance -= DepositAmount;
				file << RecordToLine(client) << endl;
				AfterWithdraw = client.AccountBalance;
			}
			else
			{
				file << RecordToLine(client) << endl;
			}
		}

		file.close();
	}
	return AfterWithdraw;
}
sClient ReadClientFromuser(string AccountNumber) {
	sClient Client;

	Client.AccountNumber = AccountNumber;
	cout << "Enter Pin code ?";
	getline(cin >> ws, Client.PINcode);
	cout << "Enter Name ?";
	getline(cin, Client.Name);
	cout << "Enter Phone ?";
	getline(cin, Client.Phone);
	cout << "Enter AccountBalance ?";
	cin >> Client.AccountBalance;
	cin.ignore();

	return Client;

}
void DeleteClientFromfile(string AccountNumber) {
	vector<sClient> vClients = LoadClientFromFile();
	fstream file;
	file.open(FileName, ios::out);
	while (file.is_open()) {
		for (sClient& Client : vClients)
		{
			if (Client.AccountNumber != AccountNumber)
			{
				file << RecordToLine(Client) << endl;
			}
		}
		file.close();
	}
}
void UpdateClientFromfile(string AccountNumber, sClient C)
{
	vector<sClient> vClients = LoadClientFromFile();
	fstream file;
	file.open(FileName, ios::out);
	while (file.is_open()) {
		for (sClient& Client : vClients)
		{
			if (Client.AccountNumber == AccountNumber)
			{
				file << RecordToLine(C) << endl;
			}
			else
			{
				file << RecordToLine(Client) << endl;
			}
		}
		file.close();
	}
}
void DepositScreen() {
	sClient Client;
	system("cls");
	cout << "----------------------------------\n";
	cout << "\t Deposit Screen\n";
	cout << "----------------------------------\n";
	string AccountNumber = ReadAccountNumber();
	while (SearchByAccountNumber(AccountNumber, Client))
	{
		cout << "\nClient with[" << AccountNumber << "] does not exist.\n";
		AccountNumber = ReadAccountNumber();
	}
	printClient(Client);
	double DepositAmount = ReadDeposit();
	cout << "\nAre you sure you want  perform this transcations? Y/N?";
	char ans;
	cin >> ans;
	if (toupper(ans) == 'Y')
	{
		double NewBalance = DepositToAccount(DepositAmount, AccountNumber);
		cout << "\nDone Successfully. New balance is : " << NewBalance << endl;;
	}
}
void WithdrawScreen() {
	sClient Client;
	system("cls");
	cout << "----------------------------------\n";
	cout << "\t Withdraw Screen\n";
	cout << "----------------------------------\n";
	string AccountNumber = ReadAccountNumber();
	while (SearchByAccountNumber(AccountNumber, Client))
	{
		cout << "\nClient with[" << AccountNumber << "] does not exist.\n";
		AccountNumber = ReadAccountNumber();
	}
	printClient(Client);


	double WithdrawAmount = ReadWithdraw(Client);

	cout << "\nAre you sure you want  perform this transcations? Y/N?";
	char ans;
	cin >> ans;
	if (toupper(ans) == 'Y')
	{
		double NewBalance = WithdrawToAccount(WithdrawAmount, AccountNumber);
		cout << "\nDone Successfully. New balance is : " << NewBalance << endl;
	}
}
void TotalBalanceScreen() {
	system("cls");
	vector<sClient> vClients = LoadClientFromFile();
	double SumBalanceOfAllAccount = 0;
	cout << "\t\t\t\tClient List (" << vClients.size() << ") Client(s).\n";
	cout << "__________________________________________________________________________________________________________\n\n";
	cout << "| " << left << setw(18) << "Account Number";
	cout << "| " << left << setw(35) << " Client Name";
	cout << "| " << left << setw(12) << "Balance";
	cout << "\n__________________________________________________________________________________________________________\n\n";
	if (vClients.size() == 0)
	{
		cout << "\n \t\t\t NO Client Avaliable In The System.\n\n";
	}
	else
	{
		for (sClient Client : vClients)
		{

			cout << "| " << left << setw(18) << Client.AccountNumber;
			cout << "| " << left << setw(35) << Client.Name;
			cout << "| " << left << setw(12) << Client.AccountBalance << endl;
			SumBalanceOfAllAccount += Client.AccountBalance;
		}
		cout << "\n__________________________________________________________________________________________________________\n";
		cout << "\n \t\t\t\t Total Balance = " << SumBalanceOfAllAccount << endl << endl;
	}
}
void BackToTranscationsScreen() {

	cout << "press any key to go back to Transcations Screen...\n";
	system("pause>0");
	TransactionsScreen();
}
void BackToMainMenueScreen() {

	cout << "press any key to go back to Main Menue...\n";
	system("pause>0");
	MainMenueScreen();
}
void ClientListScreen() {
	system("cls");
	vector<sClient> vClients = LoadClientFromFile();
	cout << "\t\t\t\tClient List (" << vClients.size() << ") Client(s).\n";
	cout << "__________________________________________________________________________________________________________\n\n";
	cout << "| " << left << setw(18) << "Account Number";
	cout << "| " << left << setw(11) << "Pin code";
	cout << "| " << left << setw(35) << " Client Name";
	cout << "| " << left << setw(15) << "Phone";
	cout << "| " << left << setw(12) << "Balance";
	cout << "\n__________________________________________________________________________________________________________\n\n";
	for (sClient Client : vClients)
	{
		cout << "| " << left << setw(18) << Client.AccountNumber;
		cout << "| " << left << setw(11) << Client.PINcode;
		cout << "| " << left << setw(35) << Client.Name;
		cout << "| " << left << setw(15) << Client.Phone;
		cout << "| " << left << setw(12) << Client.AccountBalance << endl;
	}
	cout << "\n__________________________________________________________________________________________________________\n";

}
void AddNewClientScreen() {
	char AddmMoreClient;
	string Line;
	string AccountNumber;
	sClient C;
	do {
		system("cls");
		cout << "----------------------------------\n";
		cout << "\t Add New Client Screen\n";
		cout << "----------------------------------\n";
		cout << "Adding New Client :\n\n";
		cout << "Enter Account Number ?";
		getline(cin >> ws, AccountNumber);
		while (!SearchByAccountNumber(AccountNumber, C))
		{
			cout << "Client  with[" << AccountNumber << "] Already exist, Enter anoter Account Number ?";
			getline(cin, AccountNumber);
		}
		sClient c = ReadClientFromuser(AccountNumber);
		Line = RecordToLine(c);
		AddNewClientToFile(Line);
		cout << "Client Add successfully, do you want to add more clients? Y/N?";
		cin >> AddmMoreClient;
	} while (toupper(AddmMoreClient) == 'Y');

}
void deleteClientScreen() {
	sClient Client;
	system("cls");
	cout << "----------------------------------\n";
	cout << "\t Delete Client Screen\n";
	cout << "----------------------------------\n";
	string AccountNumber = ReadAccountNumber();
	if (!SearchByAccountNumber(AccountNumber, Client))
	{
		printClient(Client);
		cout << "\n\nAre you sure you want delete this Client? Y/N?";
		char Ans;
		cin >> Ans;
		if (toupper(Ans) == 'Y') {

			DeleteClientFromfile(AccountNumber);

			cout << "\n Client delete successufully.\n";
		}
	}
	else
	{
		cout << "Client with Account Number [" << AccountNumber << "] is Not Found! " << endl;
	}

}
void UpdateClientScreen() {
	sClient Client;
	system("cls");
	cout << "----------------------------------\n";
	cout << "\t Update Client  Info Screen\n";
	cout << "----------------------------------\n";
	string AccountNumber = ReadAccountNumber();
	if (!SearchByAccountNumber(AccountNumber, Client))
	{
		printClient(Client);
		cout << "\n\nAre you sure you want Update this Client? Y/N?";
		char Ans;
		cin >> Ans;
		if (toupper(Ans) == 'Y') {

			Client = ReadClientFromuser(AccountNumber);
			UpdateClientFromfile(AccountNumber, Client);

			cout << "\n Client Update successufully.\n";
		}
	}
	else
	{
		cout << "Client with Account Number [" << AccountNumber << "] is Not Found! " << endl;
	}

}
void FindClientScreen() {
	sClient Client;
	system("cls");
	cout << "----------------------------------\n";
	cout << "\t Find Client Screen\n";
	cout << "----------------------------------\n";
	string AccountNumber = ReadAccountNumber();
	if (!SearchByAccountNumber(AccountNumber, Client))
	{
		printClient(Client);
	}
	else
	{
		cout << "Client with Account Number [" << AccountNumber << "] is Not Found! " << endl;
	}

}
void TransactionsScreen() {
	system("cls");
	cout << "================================================\n";
	cout << "\t\t Transactions Screen\n";
	cout << "================================================\n";
	cout << "\t[1] Deposit.\n";
	cout << "\t[2] withdraw.\n";
	cout << "\t[3] Total Balance\n";
	cout << "\t[4] Main Menue.\n";
	cout << "================================================\n";
	short NumberYouWant;
	do {
		cout << "Choose what do you want to do? [1 to 4] ? ";
		cin >> NumberYouWant;
	} while (NumberYouWant < 1 || NumberYouWant > 4);
	switch (enOptionTransactionsScreen(NumberYouWant)) {
	case   enOptionTransactionsScreen::Deposit:
	{
		DepositScreen();
		BackToTranscationsScreen();
		break;
	}
	case   enOptionTransactionsScreen::Withdraw:
	{
		WithdrawScreen();
		BackToTranscationsScreen();
		break;
	}
	case   enOptionTransactionsScreen::TotalBalances:
	{
		TotalBalanceScreen();
		BackToTranscationsScreen();
		break;
	}
	case   enOptionTransactionsScreen::MainMenue:
	{
		MainMenueScreen();
		break;
	}

	}
}
void ProgramEndScreen() {
	sClient Client;
	system("cls");
	cout << "----------------------------------\n";
	cout << "\t Program Ends :-) \n";
	cout << "----------------------------------\n";
}
void MainMenueScreen() {
	system("cls");
	cout << "================================================\n";
	cout << "\t\t Main Menue Screen\n";
	cout << "================================================\n";
	cout << "\t[1] Show Client List.\n";
	cout << "\t[2] Add New Client.\n";
	cout << "\t[3] Delete Client\n";
	cout << "\t[4] Update Client.\n";
	cout << "\t[5] Find Client.\n";
	cout << "\t[6] Transactions.\n";
	cout << "\t[7] Exit.\n";
	cout << "================================================\n";
	short NumberYouWant;
	do {
		cout << "Choose what do you want to do? [1 to 7] ? ";
		cin >> NumberYouWant;
	} while (NumberYouWant < 1 || NumberYouWant > 7);
	switch (enOptionScreen(NumberYouWant)) {
	case   enOptionScreen::ClientList:
	{
		ClientListScreen();
		BackToMainMenueScreen();
		break;
	}
	case  enOptionScreen::AddNewClientS:
	{
		AddNewClientScreen();
		BackToMainMenueScreen();
		break;
	}
	case  enOptionScreen::DeleteClientS:
	{
		deleteClientScreen();
		BackToMainMenueScreen();
		break;
	}
	case  enOptionScreen::UpdateClientS:
	{
		UpdateClientScreen();
		BackToMainMenueScreen();
		break;
	}
	case  enOptionScreen::FindeClientS:
	{
		FindClientScreen();
		BackToMainMenueScreen();
		break;
	}
	case  enOptionScreen::Transactions:
	{
		TransactionsScreen();
		break;
	}
	case  enOptionScreen::Exit:
	{
		ProgramEndScreen();
		system("pause>0");
		break;
	}
	}
}
int main() {
	MainMenueScreen();

	return 0;

}


