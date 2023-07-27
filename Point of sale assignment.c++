#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

class Shopping
{
private:
    int price;
    int discount;
    int productcode;
    string product;

public:
    void menu();
    void administrator();
    void buyer();
    void add();
    void edit();
    void rem();
    void list();
    void reciept();
    void viewProducts();
    void showProducts(); // function to show products before editing or removing
};

void Shopping::menu()
{
    m:
    int choice;
    string email;
    string password;

    cout << "\t\t\t\t______________________________________________________\n";
    cout << "\t\t\t\t                                                      \n";
    cout << "\t\t\t\t                  SHOPPING MENU                       \n";
    cout << "\t\t\t\t                                                      \n";
    cout << "\t\t\t\t______________________________________________________\n";
    cout << "\t\t\t\t          1.Administrator                             \n";
    cout << "\t\t\t\t                                                      \n";
    cout << "\t\t\t\t          2.Buyer                                     \n";
    cout << "\t\t\t\t                                                      \n";
    cout << "\t\t\t\t          3.Exit                                      \n";
    cout << "\n\t\t\t Please select: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        cout << "Please login:\n";
        cout << "Enter email: ";
        cin >> email;
        cout << "Enter password: ";
        cin >> password;

        if (email == "omondiondiek@gmail.com" && password == "omondi@2023")
        {
            administrator();
        }
        else
        {
            cout << "Invalid password or email. Try again.\n";
        }
        break;

    case 2:
        buyer();
        break;

    case 3:
        exit(0);
        break;

    default:
    {
        cout << "Please select from the given option.\n";
    }
    }

    goto m;
}

void Shopping::administrator()
{
    m:
    int choice;

    cout << "\n\t\t\t\t__________________________________________\n";
    cout << "\t\t\t\t\t     Administrator Menu                   \n";
    cout << "\t\t\t\t\t__________________________________________\n";
    cout << "\t\t\t\t\t      1.Add Product\n";
    cout << "\t\t\t\t\t                                          \n";
    cout << "\t\t\t\t\t      2.Edit Product\n";
    cout << "\t\t\t\t\t                                          \n";
    cout << "\t\t\t\t\t      3.Remove Product\n";
    cout << "\t\t\t\t\t                                          \n";
    cout << "\t\t\t\t\t      4.View Products\n"; // Added option to view products
    cout << "\t\t\t\t\t                                          \n";
    cout << "\t\t\t\t\t      5.Back to Main menu\n"; // Changed option number to 5
    cout << "\t\t\t\t\t                                          \n";
    cout << "Please enter your choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        add();
        break;

    case 2:
        showProducts(); // Display the products before editing
        edit();
        break;

    case 3:
        showProducts(); // Display the products before removing
        rem();
        break;

    case 4:
        viewProducts(); // Call the viewProducts() function
        break;

    case 5:
        menu();
        break;

    default:
        cout << "Invalid choice, try again.\n";
    }

    if (choice != 5)
        goto m;
}

void Shopping::buyer()
{
    m:
    int choice;
    int decision;
    cout << "\t\t\t\t_____________________________________________\n";
    cout << "\t\t\t\t               Buyer Menu                    \n";
    cout << "\t\t\t\t_____________________________________________\n";
    cout << "\t\t\t\t         1.Buy Product                       \n";
    cout << "\t\t\t\t         2.View Products                     \n"; // Option to view products
    cout << "\t\t\t\t         3.Go Back                           \n";
    cout << "\t\t\t\t                                             \n";
    cout << "\t\t\t\t        Enter choice:";
    cin >> choice;

    switch (choice)
    {
    case 1:
        reciept();
        break;

    case 2:
        viewProducts(); // Call the viewProducts() function to display available products
        cout << "\nDo you wish to proceed with your purchase? If yes, press 1; Press 2  to go back: ";
        cin >> decision;
        if (decision == 1)
        {
            reciept();
        }
        else
        {
            goto m; // Go back to the Buyer Menu
        }
        break;

    case 3:
        menu();
        break;

    default:
        cout << "Invalid choice, try again.\n";
        goto m; // Go back to the Buyer Menu for an invalid choice
    }
}

void Shopping::add()
{
    m:
    fstream data;
    int c;
    int token = 0;
    float d;
    float p;
    string n;

    cout << "\n\n\t\tAdd Product";
    cout << "\n\n\t\t Product code: ";
    cin >> c; // Renamed variable from 'productcode' to 'c'
    cout << "\n\n\t\t Name of Product: ";
    cin.ignore(); // Add this line to clear the input buffer before reading the name
    getline(cin, n); // Use getline to read the product name with spaces
    cout << "\n\n\t\tPrice of Product: ";
    cin >> p;
    cout << "Discount on Product: ";
    cin >> d;

    data.open("databank.txt", ios::app | ios::in);

    if (!data)
    {
        data.open("databank.txt", ios::app | ios::out);
        data << c << " " << n << " " << p << " " << d << "\n"; // Used 'c' instead of 'productcode'
        data.close();
    }
    else
    {
        data >> productcode >> product >> price >> discount;

        while (!data.eof())
        {
            if (c == productcode)
            {
                token++;
            }
            data >> productcode >> product >> price >> discount;
        }

        data.close();
    }

    if (token == 1)
        goto m;
    else
    {
        data.open("databank.txt", ios::app | ios::out);
        data << c << " " << n << " " << p << " " << d << "\n"; // Used 'c' instead of 'productcode'
        data.close();
    }

    cout << "\n\n\t\t~>Product inserted<~";
    cout << "\nProduct has been successfully added.\n";

    // Ask the administrator whether they want to continue adding products or go back to the administrator menu
    cout << "Do you want to continue adding products? (y/n): ";
    char continueAdding;
    cin >> continueAdding;

    if (continueAdding == 'y' || continueAdding == 'Y')
    {
        goto m; // Go back to adding another product
    }
    else
    {
        // Take the user back to the administrator menu
        administrator();
    }
}

void Shopping::edit()
{
    int productkey;
    cout << "\n\t\t\tModify Databank";
    cout << "\n\t\t\tProduct code: ";
    cin >> productkey;

    fstream data("databank.txt", ios::in);
    fstream tempData("temp_databank.txt", ios::out | ios::app);

    if (!data)
    {
        cout << "\n\nFile doesn't exist.\n";
    }
    else
    {
        data >> productcode >> product >> price >> discount;
        bool productFound = false;

        do
        {
            if (productkey == productcode)
            {
                cout << "\n\t\t\tProduct's new code: ";
                cin >> productcode;
                cout << "\n\t\t\tName of Product: ";
                cin.ignore();
                getline(cin, product);
                cout << "\n\t\t\tPrice: ";
                cin >> price;
                cout << "Discount on Product: ";
                cin >> discount;
                productFound = true;
            }

            tempData << productcode << " " << product << " " << price << " " << discount << "\n";
            data >> productcode >> product >> price >> discount;

        } while (!data.eof());

        data.close();
        tempData.close();

        remove("databank.txt");
        rename("temp_databank.txt", "databank.txt");

        if (productFound)
        {
            cout << "\n\t\t\t\t~Databank Edited~\n";
        }
        else
        {
            cout << "\n\t\t\t~Record not found~\n";
        }
    }

    // Close the file streams and display the updated list of products after editing
    viewProducts();
}

void Shopping::rem()
{

    fstream data, data1;
    int productkey;
    int token = 0;

    cout << "\n\t\t\tDelete Product";
    cout << "\n\t\t\t Product code: ";
    cin >> productkey;

    data.open("databank.txt", ios::in);
    if (!data)
    {
        cout << "\n\t\tFile doesn't exist";
    }
    else
    {
        data1.open("databank1.txt", ios::app | ios::out);
        data >> productcode >> product >> price >> discount;
        while (!data.eof())
        {
            if (productcode == productkey)
            {
                cout << "\n\t\t\t~Product successfully deleted~";
                token++;
            }
            else
            {
                data1 << productcode << " " << product << " " << price << " " << discount << "\n";
            }
            data >> productcode >> product >> price >> discount;
        }
        data.close();
        data1.close();
        remove("databank.txt");
        rename("databank1.txt", "databank.txt");

        if (token == 0)
        {
            cout << "\n\t\t\t~Record not Found~";
        }
    }
}

void Shopping::list()
{

    fstream data, data1;

    data.open("databank.txt", ios::in);
    cout << "\n\t______________________________________________";
    cout << "\n\tProduct No.\tProduct\tPrice";
    cout << "\n\t______________________________________________";
    data >> productcode >> product >> price >> discount;
    while (!data.eof())
    {
        cout << "\n" << productcode << "\t\t" << product << "\t\t" << price;
        data >> productcode >> product >> price >> discount;
    }
    data.close();
}

void Shopping::reciept()
{
    m:
    fstream data;
    int arrc[100];
    int arrq[100];
    int choice;
    int c = 0;
    float amount = 0;
    float discount = 0;
    float total = 0;

    cout << "\n\t\t\t\t~~RECEIPT~~";
    data.open("databank.txt", ios::in);
    if (!data)
    {
        cout << "\n\tEmpty databank";
    }
    else
    {
        data.close();

        list();
        cout << "\n____________________________________________";
        cout << "\n                                            ";
        cout << "\n      Please place your Order               ";
        cout << "\n____________________________________________";
        do
        {
            cout << "\n\tEnter Product code: ";
            cin >> arrc[c];
            cout << "\n\tEnter Product Quantity: ";
            cin >> arrq[c];
            for (int i = 0; i < c; i++)
            {
                if (arrc[c] == arrc[i])
                {
                    cout << "Duplicate Product code, Please Try Again";
                    goto m;
                }
            }
            c++;
            cout << "Do you wish to continue with the purchase? If yes, press 1; Press 2 key to finish: ";
            cin >> choice;
        } while (choice == 1);

        cout << "\n\t\t__________________________RECEIPT____________________________________";
        cout << "\nProd No.\tProduct\t\tProd Quant\tPrice\tAmount\tAmount with Discount";

        for (int i = 0; i < c; i++)
        {

            data.open("databank.txt", ios::in);
            data >> productcode >> product >> price >> discount;
            while (!data.eof())
            {
                if (productcode == arrc[i])
                {
                    amount = price * arrq[i];
                    discount = amount - (amount * discount / 100);
                    total = total + discount;
                    cout << "\n" << productcode << "\t\t" << product << "\t\t" << arrq[i] << "\t\t" << price << "\t\t" << amount << "\t\t" << "\t\t" << discount;
                }
                data >> productcode >> product >> price >> discount;
            }
            data.close();

            cout << "\n________________________________________________";
            cout << "\nTotal Amount: " << total;
            cout << "\n                                                ";
            cout << "\n________________________________________________";
            cout << "\n   You were served by Omondi                    ";
            cout << "\n                                                ";
            cout << "\n________________________________________________";
        }
    }
}

void Shopping::viewProducts()
{
    fstream data;
    int productcode;

    data.open("databank.txt", ios::in);
    if (!data)
    {
        cout << "No products in the databank." << endl;
    }
    else
    {
        cout << "\n\t\t\t\t_________ PRODUCTS AVAILABLE _________\n";
        cout << "\n\tProduct No.\tProduct\t\tPrice\tDiscount\n";
        cout << "\t________________________________________________\n";
        data >> productcode >> product >> price >> discount;
        while (!data.eof())
        {
            cout << "\t" << productcode << "\t\t" << product << "\t\t" << price << "\t" << discount << "%\n";
            data >> productcode >> product >> price >> discount;
        }
        data.close();
    }
}

void Shopping::showProducts()
{
    fstream data;
    int productcode;

    data.open("databank.txt", ios::in);
    if (!data)
    {
        cout << "No products in the databank." << endl;
    }
    else
    {
        cout << "\n\t\t\t\t_________ PRODUCTS AVAILABLE _________\n";
        cout << "\n\tProduct No.\tProduct\t\tPrice\tDiscount\n";
        cout << "\t________________________________________________\n";
        data >> productcode >> product >> price >> discount;
        while (!data.eof())
        {
            cout << "\t" << productcode << "\t\t" << product << "\t\t" << price << "\t" << discount << "%\n";
            data >> productcode >> product >> price >> discount;
        }
        data.close();
    }
}

int main()
{
    Shopping supermarket;
    supermarket.menu();

    return 0;
}