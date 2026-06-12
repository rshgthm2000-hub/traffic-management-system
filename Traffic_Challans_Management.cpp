#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <vector>
#include <sstream>
using namespace std;
class Challan
{
private:
    string reason;
    string date;
    int amount;

public:
    Challan() {}
    Challan(string r, string d, int a)
    {
        reason = r;
        date = d;
        amount = a;
    }
    string get_reason() const
    {
        return reason;
    }
    string get_date() const
    {
        return date;
    }
    int get_amount() const
    {
        return amount;
    }
    bool operator<(const Challan &c) const
    {
        if (reason != c.reason)
            return reason < c.reason;
        if (date != c.date)
            return date < c.date;
        return amount < c.amount;
    }
};
class Vehicle
{
private:
    string vehicle_reg_no;
    string owner_name;
    multiset<Challan> challans;
    int total_challan_amount = 0;

public:
    Vehicle() {}
    Vehicle(string reg, string name)
    {
        vehicle_reg_no = reg;
        owner_name = name;
    }
    string get_vehicle_reg_no()
    {
        return vehicle_reg_no;
    }
    string get_owner_name()
    {
        return owner_name;
    }
    bool set_params(fstream &fio)
    {
        return bool(fio >> vehicle_reg_no >> owner_name);
    }
    void write_params(fstream &fio)
    {
        fio << vehicle_reg_no << " " << owner_name << endl;
    }
    void add_challan(string reason, string date, int amount)
    {
        Challan c(reason, date, amount);
        challans.insert(c);
        total_challan_amount += amount;
    }
    bool delete_challan(string reason, string date, int amount)
    {
        auto it = challans.find(Challan(reason, date, amount));
        if (it != challans.end())
        {
            challans.erase(it);
            total_challan_amount -= amount;
            return true;
        }
        return false;
    }
    void print_challans()
    {
        cout << "Challans for vehicle " << vehicle_reg_no << ":" << endl;
        if(total_challan_amount == 0)
        {
            cout << "No challans found" << endl;
            cout<<endl;
            return;
        }
        for (auto it = challans.begin(); it != challans.end(); it++)
        {
            cout << "Reason: " << it->get_reason() << " " << "Date: " << it->get_date() << " " << "Amount: " << it->get_amount() << endl;
        }
        cout<<endl;
    }
};
class Traffic_Management_System
{
private:
    map<string, Vehicle> reg_vehicles;
    multimap<string, Vehicle *> owner_vehicles;

public:
    void load_vehicles_from_file()
    {
        fstream fio;
        fio.open("vehicles.txt", ios::in);
        Vehicle v;
        while (v.set_params(fio))
        {
            reg_vehicles[v.get_vehicle_reg_no()] = v;
            owner_vehicles.insert({v.get_owner_name(), &reg_vehicles[v.get_vehicle_reg_no()]});
        }
        fio.close();
        fio.open("challans.txt", ios::in);
        string reg_no, reason, date;
        int amount;
        while (fio >> reg_no >> reason >> date >> amount)
        {
            auto it = reg_vehicles.find(reg_no);
            it->second.add_challan(reason, date, amount);
        }
    }
    void welcome()
    {
        system("cls");
        cout << "            WELCOME TO TRAFFIC MANAGEMENT SYSTEM" << endl;
        cout << "press 1 to add a new vehicle" << endl;
        cout << "press 2 to search for a vehicle" << endl;
        cout << "press 3 to add a new challan" << endl;
        cout << "press 4 to delete a challan" << endl;
        cout << "press 5 to search for a challan" << endl;
        int choice;
        cin >> choice;
        if (choice == 1)
        {
            addVehicle();
        }
        else if (choice == 2)
        {
            searchVehicle();
        }
        else if (choice == 3)
        {
            addChallan();
        }
        else if (choice == 4)
        {
            deleteChallan();
        }
        else if (choice == 5)
        {
            searchChallan();
        }
        else
        {
            cout << "Invalid choice, please try again" << endl;
            welcome();
        }
    }
    void addVehicle()
    {
        system("cls");
        fstream fio;
        string reg_no, owner_name;
        cout << "Enter vehicle registration number" << endl;
        cin >> reg_no;
        Vehicle v;
        if (reg_vehicles.find(reg_no) != reg_vehicles.end())
        {
            cout << "Registration number already exists" << endl;
            cout<<endl;
            cout << "Press 0 to go back to the home screen" << endl;
            cout << "Press 1 to enter the vehicle registration number again" << endl;
        }
        else
        {
            cout << "Enter owner's name" << endl;
            cin >> owner_name;
            Vehicle new_vehicle(reg_no, owner_name);
            reg_vehicles[reg_no] = new_vehicle;
            owner_vehicles.insert({owner_name, &reg_vehicles[reg_no]});
            fio.open("vehicles.txt", ios::app);
            fio << new_vehicle.get_vehicle_reg_no() << " " << new_vehicle.get_owner_name() << endl;
            fio.close();
            cout << "Vehicle added successfully" << endl;
            cout<<endl;
            cout << "Press 0 to go back to the home screen" << endl;
            cout << "Press 1 to add another vehicle" << endl;
        }
        int choice;
        cin >> choice;
        while (choice != 0 && choice != 1)
        {
            cout << "Invalid choice, please try again" << endl;
            cin >> choice;
        }
        if (choice == 0)
        {
            welcome();
        }
        else if (choice == 1)
        {
            addVehicle();
        }
    }
    void searchVehicle()
    {
        system("cls");
        cout << "press 1 to search by vehicle registration number" << endl;
        cout << "press 2 to search by owner's name" << endl;
        cout << "press 0 to go back to the home screen" << endl;
        int choice;
        cin >> choice;
        while (choice != 0 && choice != 1 && choice != 2)
        {
            cout << "Invalid choice, please try again" << endl;
            cin >> choice;
        }
        if (choice == 0)
        {
            welcome();
        }
        else if (choice == 1)
        {
            searchVehicleByRegNo();
        }
        else if (choice == 2)
        {
            searchVehicleByOwnerName();
        }
    }
    void searchVehicleByRegNo()
    {
        system("cls");
        cout << "Enter vehicle registration number" << endl;
        string reg_no;
        cin >> reg_no;
        Vehicle v;
        if (reg_vehicles.find(reg_no) == reg_vehicles.end())
        {
            cout << "Registration number not found" << endl;
            cout<<endl;
            cout << "Press 0 to go back to the home screen" << endl;
            cout << "Press 1 to enter the vehicle registration number again" << endl;
            int choice;
            cin >> choice;
            while (choice != 0 && choice != 1)
            {
                cout << "Invalid choice, please try again" << endl;
                cin >> choice;
            }
            if (choice == 0)
            {
                welcome();
            }
            else if (choice == 1)
            {
                searchVehicleByRegNo();
            }
        }
        else
        {
            v = reg_vehicles[reg_no];
            cout << "Vehicle registration number: " << v.get_vehicle_reg_no() << endl;
            cout << "Owner's name: " << v.get_owner_name() << endl;
            cout<<endl;
            cout << "Press 0 to go back to the home screen" << endl;
            cout << "Press 1 to search for another vehicle" << endl;
            int choice;
            cin >> choice;
            while (choice != 0 && choice != 1)
            {
                cout << "Invalid choice, please try again" << endl;
                cin >> choice;
            }
            if (choice == 0)
            {
                welcome();
            }
            else if (choice == 1)
            {
                searchVehicle();
            }
        }
    }
    void searchVehicleByOwnerName()
    {
        system("cls");
        cout << "Enter owner's name" << endl;
        string owner_name;
        cin >> owner_name;
        Vehicle v;
        if (owner_vehicles.find(owner_name) != owner_vehicles.end())
        {
            cout << "Vehicles owned by " << owner_name << ":" << endl;
            auto range = owner_vehicles.equal_range(owner_name);
            for (auto it = range.first; it != range.second; ++it)
            {
                cout << "Vehicle registration number: " << it->second->get_vehicle_reg_no() << endl;
            }
            cout<<endl;
            cout << "Press 0 to go back to the home screen" << endl;
            cout << "Press 1 to search for another vehicle" << endl;
            int choice;
            cin >> choice;
            while (choice != 0 && choice != 1)
            {
                cout << "Invalid choice, please try again" << endl;
                cin >> choice;
            }
            if (choice == 0)
            {
                welcome();
            }
            else if (choice == 1)
            {
                searchVehicle();
            }
        }
        else
        {
            cout << "No vehicles found for owner " << owner_name << endl;
            cout<<endl;
            cout << "Press 0 to go back to the home screen" << endl;
            cout << "Press 1 to enter the owner's name again" << endl;
            int choice;
            cin >> choice;
            while (choice != 0 && choice != 1)
            {
                cout << "Invalid choice, please try again" << endl;
                cin >> choice;
            }
            if (choice == 0)
            {
                welcome();
            }
            else if (choice == 1)
            {
                searchVehicleByOwnerName();
            }
        }
    }
    void addChallan()
    {
        system("cls");
        string reg_no, reason, date;
        int amount;
        cout << "Enter vehicle registration number" << endl;
        cin >> reg_no;
        auto it = reg_vehicles.find(reg_no);
        if (it == reg_vehicles.end())
        {
            cout << "Registrstion number not found" << endl;
            cout<<endl;
            cout << "Press 0 to go back to the home screen" << endl;
            cout << "Press 1 to enter the vehicle registration number again" << endl;
        }
        else
        {
            cout << "Enter the reason for challan" << endl;
            cin >> reason;
            cout << "Enter the date of challan" << endl;
            cin >> date;
            cout << "Enter the amount of challan" << endl;
            cin >> amount;
            it->second.add_challan(reason, date, amount);
            fstream fio;
            fio.open("challans.txt", ios::app);
            fio << reg_no << " " << reason << " " << date << " " << amount << endl;
            fio.close();
            cout << "Challan added successfully" << endl;
            cout<<endl;
            cout << "Press 0 to go back to the home screen" << endl;
            cout << "Press 1 to add another challan" << endl;
        }
        int choice;
        cin >> choice;
        while (choice != 0 && choice != 1)
        {
            cout << "Invalid choice, please try again" << endl;
            cin >> choice;
        }
        if (choice == 0)
        {
            welcome();
        }
        else if (choice == 1)
        {
            addChallan();
        }
    }
    void deleteChallan()
    {
        system("cls");
        string reg_no, reason, date;
        int amount;
        cout << "Enter vehicle registration number" << endl;
        cin >> reg_no;
        auto it = reg_vehicles.find(reg_no);
        if (it == reg_vehicles.end())
        {
            cout << "Registrstion number not found" << endl;
            cout<<endl;
            cout << "Press 0 to go back to the home screen" << endl;
            cout << "Press 1 to enter the vehicle registration number again" << endl;
        }
        else
        {
            cout << "Enter the reason for challan" << endl;
            cin >> reason;
            cout << "Enter the date of challan" << endl;
            cin >> date;
            cout << "Enter the amount of challan" << endl;
            cin >> amount;
            if (it->second.delete_challan(reason, date, amount))
            {
                fstream fio;
                fio.open("challans.txt", ios::in);
                fstream temp;
                temp.open("temp.txt", ios::out);
                string line;
                bool found = false;
                while (getline(fio, line))
                {
                    stringstream ss(line);
                    string reg_no_temp, reason_temp, date_temp;
                    int amount_temp;
                    ss >> reg_no_temp >> reason_temp >> date_temp >> amount_temp;
                    if (reg_no_temp == reg_no && reason_temp == reason && date_temp == date && amount_temp == amount && !found)
                    {
                        found = true;
                        continue;
                    }
                    temp << reg_no_temp << " " << reason_temp << " " << date_temp << " " << amount_temp << endl;
                }
                fio.close();
                temp.close();
                remove("challans.txt");
                rename("temp.txt", "challans.txt");
                cout << "Challan deleted successfully" << endl;
            }
            else
            {
                cout << "challan not found" << endl;
            }
            cout<<endl;
            cout << "Press 0 to go back to the home screen" << endl;
            cout << "Press 1 to delete another challan" << endl;
        }
        int choice;
        cin >> choice;
        while (choice != 0 && choice != 1)
        {
            cout << "Invalid choice, please try again" << endl;
            cin >> choice;
        }
        if (choice == 0)
        {
            welcome();
        }
        else if (choice == 1)
        {
            deleteChallan();
        }
    }
    void searchChallan()
    {
        system("cls");
        cout << "press 1 to search by vehicle registration number" << endl;
        cout << "press 2 to search by owner's name" << endl;
        cout << "press 0 to go back to the home screen" << endl;
        int choice;
        cin >> choice;
        while (choice != 0 && choice != 1 && choice != 2)
        {
            cout << "Invalid choice, please try again" << endl;
            cin >> choice;
        }
        if (choice == 0)
        {
            welcome();
        }
        else if (choice == 1)
        {
            searchChallanByRegNo();
        }
        else if (choice == 2)
        {
            searchChallanByOwnerName();
        }
    }
    void searchChallanByRegNo()
    {
        system("cls");
        string reg_no;
        cout << "Enter vehicle registration number" << endl;
        cin >> reg_no;
        auto it = reg_vehicles.find(reg_no);
        if (it == reg_vehicles.end())
        {
            cout << "Registration number not found" << endl;
            cout<<endl;
            cout << "Press 0 to go back to the home screen" << endl;
            cout << "Press 1 to enter the vehicle registration number again" << endl;
            int choice;
            cin >> choice;
            while (choice != 0 && choice != 1)
            {
                cout << "Invalid choice, please try again" << endl;
                cin >> choice;
            }
            if (choice == 0)
            {
                welcome();
            }
            else if (choice == 1)
            {
                searchChallanByRegNo();
            }
        }
        else
        {
            it->second.print_challans();
            cout<<endl;
            cout << "Press 0 to go back to the home screen" << endl;
            cout << "Press 1 to search for another vehicle" << endl;
            int choice;
            cin >> choice;
            while (choice != 0 && choice != 1)
            {
                cout << "Invalid choice, please try again" << endl;
                cin >> choice;
            }
            if (choice == 0)
            {
                welcome();
            }
            else if (choice == 1)
            {
                searchChallan();
            }
        }
    }
    void searchChallanByOwnerName()
    {
        system("cls");
        string owner_name;
        cout << "Enter owner's name" << endl;
        cin >> owner_name;
        if (owner_vehicles.find(owner_name) == owner_vehicles.end())
        {
            cout << "Owner's name not found" << endl;
            cout<<endl;
            cout << "Press 0 to go back to the home screen" << endl;
            cout << "Press 1 to enter the owner's name again" << endl;
            int choice;
            cin >> choice;
            while (choice != 0 && choice != 1)
            {
                cout << "Invalid choice, please try again" << endl;
                cin >> choice;
            }
            if (choice == 0)
            {
                welcome();
            }
            else if (choice == 1)
            {
                searchChallanByOwnerName();
            }
        }
        else
        {
            auto range = owner_vehicles.equal_range(owner_name);
            cout << "     Challans for owner " << owner_name << ":" << endl;
            for (auto it = range.first; it != range.second; it++)
            {
                it->second->print_challans();
            }
            cout << "Press 0 to go back to the home screen" << endl;
            cout << "Press 1 to search for another challan" << endl;
            int choice;
            cin >> choice;
            while (choice != 0 && choice != 1)
            {
                cout << "Invalid choice, please try again" << endl;
                cin >> choice;
            }
            if (choice == 0)
            {
                welcome();
            }
            else if (choice == 1)
            {
                searchChallan();
            }
        }
    }
};
int main()
{
    Traffic_Management_System tms;
    tms.load_vehicles_from_file();
    tms.welcome();
}