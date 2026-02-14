#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include <vector>
#include <fstream>

using namespace std;

class clsBankClient : public clsPerson
{
private:

    enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
    enMode _Mode;
    string _AccountNumber;
    string _PinCode;
    float _AccountBalance;
    bool _MarkedForDelete = false;

    static clsBankClient _ConvertLinetoClientObject(string Line, string Seperator = "#//#")
    {
        vector<string> vClientData;
        vClientData = clsString::Split(Line, Seperator);

        return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2],
            vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));

    }

    static string _ConverClientObjectToLine(clsBankClient Client, string Seperator = "#//#")
    {

        string stClientRecord = "";
        stClientRecord += Client.FirstName + Seperator;
        stClientRecord += Client.LastName + Seperator;
        stClientRecord += Client.Email + Seperator;
        stClientRecord += Client.Phone + Seperator;
        stClientRecord += Client.AccountNumber() + Seperator;
        stClientRecord += Client.PinCode + Seperator;
        stClientRecord += to_string(Client.AccountBalance);

        return stClientRecord;

    }

    static vector <clsBankClient> _LoadClientDateFtomFile() {
        vector <clsBankClient> _vClient;
        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);

        if (MyFile.is_open()) {
            string Line;

            while (getline(MyFile, Line)) {
                clsBankClient Client = _ConvertLinetoClientObject(Line);
                _vClient.push_back(Client);
            }
            MyFile.close();
        }
        return _vClient;
    }

    static void _SaveClientsDataToFile(vector<clsBankClient> vClients) {

        fstream MyFile;

        MyFile.open("Clients.txt", ios::out);
        string DataLine;

        if (MyFile.is_open()) {

            for (clsBankClient C : vClients) {
                if (C.MarkedForDelete() == false) {
                    DataLine = _ConverClientObjectToLine(C);
                    MyFile << DataLine << endl;
                }

            }
            MyFile.close();
        }
    }

    void _Update() {
        vector <clsBankClient> _vClient;

        _vClient = _LoadClientDateFtomFile();

        
        for (clsBankClient& C : _vClient) 
        {
            if (C.AccountNumber() == AccountNumber()) {
                C = *this;
                break;
            }
        }

        _SaveClientsDataToFile(_vClient);

    }

    void _AddDataLineToFile(string stDataLine) {
        fstream MyFile;
        MyFile.open("Clients.txt", ios::out | ios::app);

        if (MyFile.is_open()) {

            MyFile << stDataLine << endl;

            MyFile.close();
        }
    }

    static clsBankClient _GetEmptyClientObject()
    {
        return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }

    void _AddNew() {
        _AddDataLineToFile(_ConverClientObjectToLine(*this));
    }


public:


    clsBankClient(enMode Mode, string FirstName, string LastName,
        string Email, string Phone, string AccountNumber, string PinCode,
        float AccountBalance) :
        clsPerson(FirstName, LastName, Email, Phone)

    {
        _Mode = Mode;
        _AccountNumber = AccountNumber;
        _PinCode = PinCode;
        _AccountBalance = AccountBalance;

    }

    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }

    string AccountNumber()
    {
        return _AccountNumber;
    }

    void SetPinCode(string PinCode)
    {
        _PinCode = PinCode;
    }
    string GetPinCode()
    {
        return _PinCode;
    }
    __declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

    void SetAccountBalance(float AccountBalance)
    {
        _AccountBalance = AccountBalance;
    }
    float GetAccountBalance()
    {
        return _AccountBalance;
    }
    __declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;

    bool MarkedForDelete() {
        return _MarkedForDelete;
    }

    /*
      No UI Related code iside object.
    void Print()
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << FirstName;
        cout << "\nLastName    : " << LastName;
        cout << "\nFull Name   : " << FullName();
        cout << "\nEmail       : " << Email;
        cout << "\nPhone       : " << Phone;
        cout << "\nAcc. Number : " << _AccountNumber;
        cout << "\nPassword    : " << _PinCode;
        cout << "\nBalance     : " << _AccountBalance;
        cout << "\n___________________\n";

    }*/


    static clsBankClient Find(string AccountNumber)
    {
        vector <clsBankClient> vClient;

        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsBankClient Client = _ConvertLinetoClientObject(Line);
                if (Client.AccountNumber() == AccountNumber)
                {
                    MyFile.close();
                    return Client;
                }

            }

            MyFile.close();

        }

        return _GetEmptyClientObject();
    }

    static clsBankClient Find(string AccountNumber, string PinCode)
    {

        vector <clsBankClient> vClient;

        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsBankClient Client = _ConvertLinetoClientObject(Line);
                if (Client.AccountNumber() == AccountNumber && Client.PinCode == PinCode)
                {
                    MyFile.close();
                    return Client;
                }

            }

            MyFile.close();

        }
        return _GetEmptyClientObject();
    }

    enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildAccountNumberExists =2 };

    enSaveResults Save() {
        switch (_Mode) {
        case enMode::EmptyMode:
            if (IsEmpty())
            return enSaveResults::svFaildEmptyObject;
        case enMode::UpdateMode:
            _Update();
            return enSaveResults::svSucceeded;
        case enMode::AddNewMode:
            if (clsBankClient::IsClientExist(_AccountNumber))
                return clsBankClient::enSaveResults::svFaildAccountNumberExists;
            else
                _AddNew();
            _Mode = enMode::UpdateMode;
            return enSaveResults::svSucceeded;

        }
    }

    static bool IsClientExist(string AccountNumber)
    {

        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        return (!Client1.IsEmpty());
    }

    static clsBankClient GetAddNewClientObject(string AccountNumber) {
        return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
    }

    bool Delete() {
        vector <clsBankClient> _vClient;
        _vClient = _LoadClientDateFtomFile();

        for (clsBankClient& C : _vClient) {
            if (C.AccountNumber() == _AccountNumber) {
                C._MarkedForDelete = true;
                break;
            }
        }
        _SaveClientsDataToFile(_vClient);

        *this = _GetEmptyClientObject();

        return true;

    }

    static vector <clsBankClient> GetClientsList() {
        return _LoadClientDateFtomFile();
    }

    static double GetTotalBalances(vector <clsBankClient> vClients) {
        double Sum = 0;
        for (clsBankClient& Client : vClients) {
            Sum += Client.AccountBalance;
        }
        return Sum;
    }

    static double GetTotalBalances()
    {
        vector <clsBankClient> vClients = clsBankClient::GetClientsList();

        double TotalBalances = 0;

        for (clsBankClient Client : vClients)
        {

            TotalBalances += Client.AccountBalance;
        }

        return TotalBalances;
    }

    void Deposit(double Amount)
    {
        _AccountBalance += Amount;
        Save();
    }

    bool Withdraw(double Amount)
    {
        if (Amount > _AccountBalance)
            return false;
        else {
            _AccountBalance -= Amount;
            Save();
            return true;
        }
    }

};