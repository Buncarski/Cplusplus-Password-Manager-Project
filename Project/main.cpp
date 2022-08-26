#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>

using namespace std;


void encode(string& a);
void addEncodedPass(string& a, string& b, string& c);
void readPasswords();
void changeDirectory();
void inputPasswordsToFile(string& newFile);
void changeFile();

int select;
bool exitBoolean = false;
string fileName;
string savingFileName;

class MasterCheck{
    string masterUserName = "big boy";
    string masterPassword = "Bigg";
    string uNameCheck;
    string pCheck;
    public:
        void check(){
            cout << "Provide Master Username: ";
            getline(cin, uNameCheck);
            cout << "Provide Master Pass: ";
            getline(cin, pCheck);
            if(uNameCheck != masterUserName || pCheck != masterPassword){
                cout << uNameCheck << " " << pCheck << endl;
                cout << "bad man" << endl;
                exit(0);
            }
            else{
                cout << "Good man" << endl;
            };
        }
};

class Pass{
public:
    string username;
    string password;
    string appName;
    void addData(){
        string *uname = &username;
        string *pass = &password;
        string *app = &appName;
        string tmp;

        cout << "1. Enter username" << endl;
        cin.ignore();
        getline(cin, tmp);
        *uname = tmp;

        cout << "2. Enter password" << endl;
        getline(cin, tmp);
        *pass = tmp;

        cout << "3. Enter appName" << endl;
        getline(cin, tmp);
        *app = tmp;

        encode(*uname);
        encode(*pass);
        encode(*app);
    }
};
int main()
{
    MasterCheck uGotThePass;
    uGotThePass.check();

    ifstream savingFile;
    savingFile.open("currentSavingFile.txt");

    while (getline (savingFile, savingFileName)) {
        fileName = savingFileName;
    }
    savingFile.close();

    cout << "Greetings chief, what you wanna do?" << endl;
    while(exitBoolean == false){
        cout << fileName << endl;
        cout << "1. New pass" << endl;
        cout << "2. Show all passwords" << endl;
        cout << "3. Change file it will be saved too" << endl;
        cout << "4. Exit" << endl;
        cin >> select;
        switch(select){
            case 1:{
                Pass newPass;
                newPass.addData();
                string *uname = &newPass.username;
                string *pass = &newPass.password;
                string *app = &newPass.appName;
                cout << *uname << " " << *pass << " " << *app << endl;

                addEncodedPass(*uname, *pass, *app);
                break;
            }
            case 2:{
                readPasswords();
                break;
            }
            case 3:{
                changeDirectory();
                changeFile();
                break;
            }
            case 4:{
                exitBoolean = true;
                break;
            }
        }
    }
    return 0;
}

void encode(string& a){
    string* tmp = &a;
    int length = a.length();
    char array[length+1];
    string changed = "";
    strcpy(array, a.c_str());
    for (int i = 0; i < length; i++){
        array[i] = array[i]+10;
        changed += array[i];
    }
    *tmp = changed;
}

void addEncodedPass(string& a, string& b, string& c){
    string* encA = &a;
    string* encB = &b;
    string* encC = &c;
    std::fstream file(fileName, std::ios::out | std::ios::app);
    file << *encA << " " << *encB << " " << *encC << endl;
    file.close();
};

void readPasswords(){
    string myText;

    ifstream file(fileName);

    while (getline (file, myText)) {
        cout << myText << endl;
    }

    file.close();
};

void changeDirectory(){
    string nameOfFile;
    cout << "Change file" << endl;
    cin.ignore();
    getline(cin, nameOfFile);
    string* newFile = &nameOfFile;
    *newFile += ".txt";
    inputPasswordsToFile(*newFile);
    fileName = *newFile;
    delete newFile;
};

void inputPasswordsToFile(string& newFileName){
    string myText;
    int length = fileName.length();
    char array[length+1];
    strcpy(array, fileName.c_str());

    std::ifstream file(fileName);
    std::fstream newFile(newFileName, std::ios::out | std::ios::app);
    while (getline (file, myText)) {
        newFile << myText << endl;
    }
    file.close();
    if (remove(array) != 0)
		perror("File deletion failed");
	else
		cout << "File deleted successfully";
    newFile.close();
};

void changeFile(){
    ofstream newSavingFile;
    newSavingFile.open("currentSavingFile.txt");

    newSavingFile << fileName << endl;
    newSavingFile.close();
};
