#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stack>
#include <string>
#include <ctime>
#include <windows.h>
#include <sstream>
#define MAX 100
using namespace std;

stack <string> action;
stack <string> date;
stack <string> status;
stack <string> remarks;

string Daytime[MAX];
string med[MAX];

//LOGS
void showLogs(stack <string> action,stack <string> date, stack <string> status, stack <string> remarks){
    if(!action.empty()==false)
    {
        cout << "\nThe log is empty\n\n";
    }
    while (!action.empty())
    {
        cout << '\n'<<"Date/Time: "<<date.top()
        <<"Action: "<< action.top()<<"\n"
        <<"Status: "<<status.top()<<"\n"
        <<"Remarks: "<<remarks.top()<<"\n"
        <<"----------------------------------";
        status.pop();
        action.pop();
        date.pop();
        remarks.pop();
    }
    cout << '\n';
    Sleep(3000);
}

//STATUS
string BPUpdate(string BP){//DONE
    cout << "Current Status \n \n";
    //Blood Pressure
    int result1=0;
    int result2=0;
    srand((unsigned) time(0));
    cout << "Blood Pressure: ";

    while (result1 <= 90)
    {
        result1 = rand() % 180;
    }
    if (result1 <120){
        while (result2<=70){
            result2 = result1-20;
        }
        BP = to_string(result1)+"/"+ to_string(result2)+"\nResults: Normal";
    }
    else if (result1 >=120 && result1<=129){
        while (result2<=70){
            result2 = result1-20;
        }
        BP = to_string(result1)+"/"+ to_string(result2)+"\nResults: Elevated";
    }
    else if (result1>=130 && result1 <=139){
        while (result2<80){
            result2 = result1-20;
        }
        BP = to_string(result1)+"/"+ to_string(result2)+"\nResults: High BP Stage 1";
    }
    else if (result1>=140 && result1<=179){
        while (result2<90){
            result2 = result1-20;
        }
        BP = to_string(result1)+"/"+ to_string(result2)+"\nResults: High BP Stage 2";
    }
    else{
        while (result2<120){
            result2 = result1-20;
        }
        BP = to_string(result1)+"/"+ to_string(result2)+"\nResults: Hypertensive Crisis";
    }
    BP += "\n\n";
    cout << BP;
    return BP;
}
string BSUpdate (string BSR){//DONE
    int BS=0;
    //Blood Sugar
    srand((unsigned) time(0));
    printf("Blood Sugar: ");
    while (BS < 70)
    {
        BS = rand() % 200;
    }

    if (BS >= 140&&BS<200)
    {
        BSR = to_string(BS) +"\nResults: You have high blood sugar.\n\n";
    }
    else if (BS <140)
    {
        BSR = to_string(BS) +"\nResults: Your blood sugar is normal\n\n";
    }
    else
    {
        BSR = to_string(BS) +"\nResults: Go see your doctor\n\n";
    }
    cout << BSR;
return BSR;
}

//PUSH FUNCTIONS
void DatePush(){//DONE
    time_t curr_time;
    time(&curr_time);
        curr_time = time(NULL);
    char *tm = ctime(&curr_time);
    string redate;
    redate += tm;
    date.push(redate);
}
void RemarksPush(int b){//DONE
string note;
if (b == 1){
    string a;
    string note;
    cout <<"Do you wish to leave a note? \n"
    <<"[1] Yes \n"
    <<"[2] No \n \n"
    <<"Input: ";
    cin >>a;
    if (a == "1")
    {
        cout <<"Note: ";
        cin.ignore();
        getline(cin, note);
        remarks.push(note);
        cout <<"\nRecord Complete!\n\n";
    }
    else if (a == "2")
    {
        note = "N/A";
        remarks.push(note);
        cout <<"\nRecord Complete!\n\n";
    }
    else
    {
        cout <<"Invalid Input \n\n";
        RemarksPush(1);
    }
}
else
    {
        cout <<"\nEnter your note: ";
        cin >> note;
        remarks.push(note);
        cout <<"\nRecord Complete!\n\n";
    }
}

//INTRO
string intro(){//DONE
    string input;
    cout << "Choose Option"
    <<"\n [1] Add/Delete Medication"
    <<"\n [2] Record your Current Status"
    <<"\n [3] Record your hours of sleep"
    <<"\n [4] Record your Medication"
    <<"\n [5] Extra Notes"
    <<"\n [6] Show Logs "
    <<"\n [7] Delete Previous Record"
    <<"\n [8] Exit\n\n"
    <<"Input: ";
    cin >> input;
    return input;
}

//OPTIONS
int pickDay(int counter){//DONE
    string picker;
    cout << "\nTime it needs to be drank \n"
    <<"\n[1] Morning"
    <<"\n[2] Afternoon"
    <<"\n[3] Evening\n\n"
    <<"Input: ";
    cin >> picker;
    if (picker == "1")
        Daytime[counter]="Morning";
    else if (picker == "2")
        Daytime[counter] ="Afternoon";
    else if (picker =="3")
        Daytime[counter] ="Evening";
    else
        pickDay(counter);
    counter++;
    return counter;
}
int AddMed(int counter){
    cin.ignore();
    getline(cin, med[counter]);
    counter=pickDay(counter);
    cout << "Successfully added.\n\n";
    return counter;
}
int DelMed(int counter){
    string a;
    int flag=0;
    cout << "\nWhat medicine would you like to delete?\n";
    for(int i=0;i<counter;i++)
    {
        cout <<"["<<i+1<<"] "<<med[i]<<"\n";
    }
    cout << "\nInput: ";
    cin >> a;
    stringstream pick(a);
    int picker2=0;
    pick >> picker2;
    if (picker2>0)
    {
    for (int i=0;i<counter;i++)
    {
        if (picker2 == i+1)
            {
                for (int j=picker2-1;j<counter;j++){
                    med[j]=med[j+1];
                }
                flag = 1;
            }
    }
    if(flag==1)
    {
        cout << "Successfully deleted.\n\n";
        counter--;
    }
    else
        cout <<"Invalid Input.\n\n";
    }
    else
    {
        cout << "\nInvalid Input. Try again.\n\n";
    }
    return counter;
}
int MedOp(int counter){//DONE, ADDED DELETE MEDICINE
    //cout << "\nName of Medicine: ";
    string a;
    cout << "\nWhat would you like to do?\n[1] Add Medicine\n[2] Delete Listed Medicine\n\nInput: ";
    cin >> a;
    if (a == "1")
        {
        cout << "Name of Medicine: ";
        counter=AddMed(counter);
        }
    else if (a == "2")
    {
        if (counter==0)
        {
            cout << "\nYou need to create a list first.\n\n";
        }
        else
        {
        counter=DelMed(counter);
        }
    }
    else
    {
        cout << "\nInvalid Option. Try Again.\n\n";
    }
    return counter;
}
void recordCurrentStatus(string BP, string BSR){//WIP
    cout << "\nHealth Status Recorded!\n\n";
    string RCS = "\nBlood Pressure: "+ BP+ "Blood Sugar: "+BSR;
    status.push(RCS);
    DatePush();
    action.push("Health Status\n");
    RemarksPush(1); //Put status of BP and BSR HERE
}
void sleepHours(){//DONE, IT IS ASSUMED THAT THE USER IS A TEENAGE-ADULT/ADULT
    string hours;
    int flag = 0;
    cout << "\nHow many hours did you sleep today? \n"
    <<"Input: ";
    cin >> hours;
    stringstream x(hours);
    int hours2 = 0;
    x >> hours2;
    if(hours2 <=24 && hours2 >=1){
        flag++;
        status.push(hours);
        action.push("Sleep Hours");
        DatePush();
        if(hours2>=1 && hours2<=4){
            remarks.push("You don't have enough sleep! Make sure to sleep more during the day.");
        }
        else if(hours2>4 && hours2<=6){
            remarks.push("Your sleep is enough to keep you for the day, but be sure to rest more!");
        }
        else if (hours2==7){
            remarks.push("You sleep enough for today.");
        }
        else{
            remarks.push("You slept too much, be sure to be productive during the day.");
        }
    }
    else
    {
        cout << "Invalid Input\n\n";
        sleepHours();
    }
    if (flag == 1)
        cout <<"Recorded Successfully.\n\n";
}
void recordMedication(int counter){//DONE
    if (counter>0){
    int flag = 0;
    string picker;
    cout << "\nWhat medication did you take?\n\n";
    for (int i=0; i<counter;i++)
    {
        cout <<"["<<i+1<<"] "<<med[i]
        <<" :In the "<<Daytime[i]<<"\n";
    }
    cout <<"Input: ";
    cin >> picker;
    stringstream pick(picker);
    int picker2=0;
    pick >> picker2;
    if (picker2>=1)
    {
    for (int i=1; i<counter+1;i++)
    {
        if(picker2==i){
            status.push(med[picker2-1]+" :In the "+Daytime[picker2-1]);
            action.push("Took Medication");
            DatePush();
            RemarksPush(1);
            flag++;
        }
    }
    if (flag == 0)
        cout << "Invalid Input\n\n";
    else
        cout << "Successfully Recorded\n\n";
    }
    else{
        cout << "Invalid Input\n\n";
    }
    }
    else{
        cout << "No Medication Listed\n\n";
    }
}
void ExtraNotes(){//DONE
    DatePush();
    status.push("-");
    RemarksPush(2);
    action.push("Extra Notes");
}

//MAIN
int main() {//DONE
    string input;
    string BSR;
    string BP;
    int counter=0;

    //FIRST PART WEARABLE DEVICE
    while (true)
    {
        Sleep(1000);
        BP=BPUpdate(BP);
        BSR=BSUpdate(BSR);
        input=intro();
        if (input == "1")
            counter = MedOp(counter);
        else if (input == "2")
            recordCurrentStatus(BP, BSR);
        else if (input == "3")
            sleepHours();
        else if (input == "4")
            recordMedication(counter);
        else if (input == "5")
            ExtraNotes();
        else if (input == "6")
            showLogs(action,date,status,remarks);
        else if (input == "8")
            return 0;
        else if (input == "7")
        {
            if (action.empty()==true)
            {
                cout << "The log is empty\n\n";
            }
            else{
            status.pop();
            action.pop();
            date.pop();
            remarks.pop();
            cout << "The previously recorded action was deleted.\n\n";
        }
        }
        else
        {
            cout << "Invalid Input\n\n";
        }
    }
}
