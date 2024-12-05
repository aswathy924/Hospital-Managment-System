#include<stdlib.h>
#include<iostream>
#include<string.h>
#include<fstream>
#include<windows.h>
#include<unistd.h>
using namespace std;

class Patient
{
private:
    char pat_name[50],pat_blood_grp[20],pat_gender[20],pat_address[100],pat_email[50],pat_allg[50];
    struct dob
    {   int day;
        int month;
        int year;
    }d;
    int pat_age;
    long long int pat_mobile;

public:
    void add_p()
    {
        cout<<"Name:";
        cin>>ws;
        cin.getline(pat_name,50);
        cout<<"Age:";
        cin>>pat_age;
        int x = 0;
        do{
            cout<<"Date of birth(DD MM YYYY): ";
            cin>>d.day>>d.month>>d.year;
            if(d.day<=31 && d.month<13)
            {
                x = 1;
            }
            else
            {
                cout<<"/nINVALID INPUT/n"<<endl;
                x = 0;
            }
        }while(x==0);
        cin>>pat_age;
        cout<<"DOB:";
        cin>>d.day>>d.month>>d.year;
        cout<<"Gender:";
        cin>>pat_gender;
        cout<<"Blood group:";
        cin>>pat_blood_grp;
        cout<<"Mobile number:";
        cin>>pat_mobile;
        cout<<"Address:";
        cin>>ws;
        cin.getline(pat_address,100);
        cout<<"Email:";
        cin>>pat_email;
        cout<<"Any allergies known(if not, NIL):";
        cin>>ws;
        cin.getline(pat_allg,50);
    }

    void pat_display()
    {
        cout<<"NAME:"<<pat_name<<endl;
        cout<<"AGE:"<<pat_age<<endl;
        cout<<"GENDER:"<<pat_gender<<endl;
        cout<<"Date of Birth:"<<d.day<<"/"<<d.month<<"/"<<d.year<<endl;
        cout<<"BLOOD GROUP:"<<pat_blood_grp<<endl;
        cout<<"MOBILE NUMBER:"<<pat_mobile<<endl;
        cout<<"ADDRESS:"<<pat_address<<endl;
        cout<<"EMAIL:"<<pat_email<<endl;
        cout<<"ALLERGIES:"<<pat_allg<<endl;
    }

    string add_p_file();
    string pat_search();

};

class Doctor
{
protected:
    char doc_name[50],spec[50],day[50],intime[20],outtime[20];

public:
    void doc_display()
    {
        system("cls");
        cout<<"\nDOCTOR NAME:\t\t"<<doc_name;
        cout<<"\nSPECILIZATION:\t\t"<<spec;
        cout<<"\nDAYS AVAILABLE:\t\t"<<day;
        cout<<"\nIN TIME:\t\t"<<intime;
        cout<<"\nOUT TIME:\t\t"<<outtime<<endl;
    }

    void add_doc_file();
    string doc_search(int n2);
};

class Spl_Doctor:public Doctor
{
protected:
    char pcase[50];

public:
    void spl_add_doc_file();
    string spl_doc_search(char ch[]);
};

class Medicine
{
protected:
    char med_name[50];
    float med_price;

public:
    void med_display()
    {
        cout<<"\nMEDICINE:\t\t"<<med_name;
        cout<<"\nPRICE:\t\t"<<med_price;
    }

    void add_med_file();
    float med_search(char ch[]);
};

string Patient::add_p_file()
{
    fstream out;
    out.open("Patient.dat",ios::binary|ios::app);

    if(!out.is_open())
    {
        cout<<"\nERROR OCCURED : UNABLE TO OPEN FILE";
        return NULL;
    }
    Patient p;
    p.add_p();

    out.write((char*)&p,sizeof(p));
    out.close();
    string s;
    s=(string)p.pat_name;
    return s;
}

string Patient::pat_search()
{
    int f=0;
    char ch[50];
    cout<<"Enter your name:";
    cin>>ws;
    cin.getline(ch,50);

    fstream in;
    in.open("Patient.dat",ios::binary|ios::in);

    if(!in.is_open())
    {
        cout<<"\nERROR OCCURED : UNABLE TO OPEN FILE";
        return NULL;
    }

    Patient p;

    while(in.read(reinterpret_cast<char*>(&p),sizeof(p)))
    {
        if(strcmp(p.pat_name,ch)==0)
        {
            f++;
            p.pat_display();
            break;
        }
    }
    if (f==0)
    {
        cout<<"\nPATIENT NOT FOUND"<<endl<<"TRY AGAIN"<<endl;
        return "NULL";
    }
    sleep(3);
    in.close();
    string s;
    s=(string)p.pat_name;
    return s;
}

void Doctor::add_doc_file()
{
    Doctor doc[5];

    strcpy(doc[0].doc_name,"Dr. Kavitha nadar");
    strcpy(doc[0].spec,"General Medicine");
    strcpy(doc[0].day,"Everyday");
    strcpy(doc[0].intime,"8.00am");
    strcpy(doc[0].outtime,"5.00pm");

    strcpy(doc[1].doc_name,"Dr. Jacob George");
    strcpy(doc[1].spec,"ENT");
    strcpy(doc[1].day,"Monday,Wednesday,Friday");
    strcpy(doc[1].intime,"10.00am");
    strcpy(doc[1].outtime,"4.30pm");

    strcpy(doc[2].doc_name,"Dr. Ashwin Kumar");
    strcpy(doc[2].spec,"Paediatrition");
    strcpy(doc[2].day,"Everyday");
    strcpy(doc[2].intime,"9.00am");
    strcpy(doc[2].outtime,"5.00pm");

    strcpy(doc[3].doc_name,"Dr. Rekha Sharma");
    strcpy(doc[3].spec,"Psychiatrist");
    strcpy(doc[3].day,"Tuesday,Friday");
    strcpy(doc[3].intime,"10.00am");
    strcpy(doc[3].outtime,"4.00pm");

    strcpy(doc[4].doc_name,"Dr. Lawrence Stilton");
    strcpy(doc[4].spec,"General Surgeon");
    strcpy(doc[4].day,"Monday,Thursday,Saturday");
    strcpy(doc[4].intime,"11.00am");
    strcpy(doc[4].outtime,"3.30pm");

    ofstream out;
    out.open("Doctor.dat",ios::binary|ios::out);

    if(!out.is_open())
    {
        cout<<"\nERROR OCCURED : UNABLE TO OPEN FILE";
//        return 0;
    }

    for(int i=0;i<5;i++)
    {
        out.write((char*)&doc[i],sizeof(doc[i]));

    }
    out.close();
}

void Spl_Doctor::spl_add_doc_file()
{
    Spl_Doctor sdoc[6];

    strcpy(sdoc[0].doc_name,"Dr. Sean da Silva");
    strcpy(sdoc[0].spec,"Cardiologist");
    strcpy(sdoc[0].day,"Everyday");
    strcpy(sdoc[0].intime,"9.00am");
    strcpy(sdoc[0].outtime,"4.00pm");
    strcpy(sdoc[0].pcase,"Heart attack");

    strcpy(sdoc[1].doc_name,"Dr. Imran Akhtar");
    strcpy(sdoc[1].spec,"Surgeon");
    strcpy(sdoc[1].day,"Monday,Wednesday,Friday");
    strcpy(sdoc[1].intime,"10.30am");
    strcpy(sdoc[1].outtime,"3.30pm");
    strcpy(sdoc[1].pcase,"Severe bleeding");

    strcpy(sdoc[2].doc_name,"Dr. Aarushi Suresh");
    strcpy(sdoc[2].spec,"Neurologist");
    strcpy(sdoc[2].day,"Monday,Wednesday,Saturday");
    strcpy(sdoc[2].intime,"11.00am");
    strcpy(sdoc[2].outtime,"5.00pm");
    strcpy(sdoc[2].pcase,"Stroke");

    strcpy(sdoc[3].doc_name,"Dr. Gokul Sundar");
    strcpy(sdoc[3].spec,"Toxicologist");
    strcpy(sdoc[3].day,"Everyday");
    strcpy(sdoc[3].intime,"9.00am");
    strcpy(sdoc[3].outtime,"4.00pm");
    strcpy(sdoc[3].pcase,"Poisoning");

    strcpy(sdoc[4].doc_name,"Ananya Deepak");
    strcpy(sdoc[4].spec,"Orthopedist");
    strcpy(sdoc[4].day,"Everday");
    strcpy(sdoc[4].intime,"11.00am");
    strcpy(sdoc[4].outtime,"4.30pm");
    strcpy(sdoc[4].pcase,"Injury");

    strcpy(sdoc[5].doc_name,"Micheal Walker");
    strcpy(sdoc[5].spec,"Gynaecologist");
    strcpy(sdoc[5].day,"Tuesday,Thursday,Friday");
    strcpy(sdoc[5].intime,"10.00am");
    strcpy(sdoc[5].outtime,"4.00pm");
    strcpy(sdoc[5].pcase,"Obstetric");

    ofstream out;
    out.open("Spl_Doctor.dat",ios::binary|ios::out);

    if(!out.is_open())
    {
        cout<<"\nERROR OCCURED : UNABLE TO OPEN FILE";
        //return;
    }

    for(int i=0;i<6;i++)
    {
        out.write((char*)&sdoc[i],sizeof(sdoc[i]));

    }
    out.close();
}


string Doctor::doc_search(int n2)
{
    char ch3[50];

    if (n2==1)
        strcpy(ch3,"General Medicine");
    else if (n2==2)
        strcpy(ch3,"ENT");
    else if (n2==3)
        strcpy(ch3,"Pediatrician");
    else if (n2==4)
        strcpy(ch3,"Psychiatrist");
    else if (n2==5)
        strcpy(ch3,"General Surgeon");
    else
     {
        cout<<"WRONG INPUT";
        return "F";
     }

    fstream in;
    in.open("Doctor.dat",ios::binary|ios::in);

    if(!in.is_open())
    {
        cout<<"\nERROR OCCURED : UNABLE TO OPEN FILE";
        return NULL;
    }

    Doctor d;

    for(;;)
    {
        in.read(reinterpret_cast<char*>(&d),sizeof(d));
        if(strcmp(d.spec,ch3)==0)
        {
            d.doc_display();
            break;
        }
    }
    in.close();
    sleep(3);
    string s;
    s=(string)d.doc_name;
    return s;
}

int booking(string doc,string time)
{
    int c=0;

    fstream file;
    file.open(doc+".txt");

    if(file)
    {
        file.close();
        file.open(doc+".txt",ios::in);
        string s;
        while(getline(file,s))
        {
            if(time==s)
            {
                c++;
                break;
            }
        }
        file.close();
        if(c==0)
        {
            file.open(doc+".txt",ios::app);
            file<<time<<"\n";
            file.close();
            return 1;
        }
        else
        {
            cout<<"\nSORRY!!DOCTOR NOT AVAILABLE "<<endl;
            return 0;
        }
    }
    else
    {
        file.open(doc+".txt",ios::app);
        file<<time<<"\n";
        file.close();
        return 1;
    }
}

string Spl_Doctor::spl_doc_search(char ch[])
{
    fstream in;
    in.open("Spl_Doctor.dat",ios::binary|ios::in);

    if(!in.is_open())
    {
        cout<<"\nERROR OCCURED : UNABLE TO OPEN FILE";
        return NULL;
    }

    Spl_Doctor sd;

    for(;;)
    {
        in.read(reinterpret_cast<char*>(&sd),sizeof(sd));
        if(strcmp(sd.pcase,ch)==0)
        {
              sd.doc_display();
              break;
        }
    }
    sleep(3);
    in.close();
}

void Medicine::add_med_file()
{
    Medicine m[15];

    strcpy(m[0].med_name,"Paracetamol");
    m[0].med_price=2.50;

    strcpy(m[1].med_name,"Ibuprofen");
    m[1].med_price=6.527;

    strcpy(m[2].med_name,"Ciprofloxacin");
    m[2].med_price=12.50;

    strcpy(m[3].med_name,"Amoxicillin");
    m[3].med_price=5.817;

    strcpy(m[4].med_name,"Omeprazole");
    m[4].med_price=9.87;

    strcpy(m[5].med_name,"Metformin");
    m[5].med_price=10.58;

    strcpy(m[6].med_name,"Aspirin");
    m[6].med_price=2.10;

    strcpy(m[7].med_name,"Ranitidine");
    m[7].med_price=8.19;

    strcpy(m[8].med_name,"Diclofenac");
    m[8].med_price=10.50;

    strcpy(m[9].med_name,"Atorvastatin");
    m[9].med_price=13.60;

    strcpy(m[10].med_name,"Cough Syrup");
    m[10].med_price=80.50;

    strcpy(m[11].med_name,"Multivitamin Syrup");
    m[11].med_price=90.89;

    strcpy(m[12].med_name,"Digestive Syrup");
    m[12].med_price=120.00;

    strcpy(m[13].med_name,"Anti-allergic Syrup");
    m[13].med_price=270.09;

    strcpy(m[14].med_name,"Antacid Syrup");
    m[14].med_price=163.00;

    fstream out;
    out.open("Medicine.dat",ios::binary|ios::out);

    if(!out.is_open())
    {
        cout<<"\nERROR OCCURED : UNABLE TO OPEN FILE";
        return;
    }

    for(int i=0;i<15;i++)
    {
        out.write((char*)&m[i],sizeof(m[i]));

    }
    out.close();
}

float Medicine::med_search(char ch[])
{
    float price;
    fstream in;
    in.open("Medicine.dat",ios::binary|ios::in);

    if(!in.is_open())
    {
        cout<<"\nERROR OCCURED : UNABLE TO OPEN FILE";
//        return;
    }

    Medicine m;
    for(;;)
    {
        in.read(reinterpret_cast<char*>(&m),sizeof(m));
        if(strcmp(m.med_name,ch)==0)
        {
            price=m.med_price;
            break;
        }
    }
    in.close();
    return price;
}

int main()
{
    Patient P;
    Doctor D;
    Medicine M;
    Spl_Doctor S;
    int n1=0,n2,n3;
    string s1="NULL",s2="F";
    char ch1[50],ch2[50],ch3[50],ch4[50],ch5[50];
    int j1=0,j2=0,j3=0;
    float total=0;
    D.add_doc_file();
    M.add_med_file();
    S.spl_add_doc_file();

    system("cls");
    cout<<"\t\t\t\t1.APPOINTMENT\n\t\t\t\t2.EMERGENCY\n\t\t\t\t3.EXIT"<<endl;
    cin>>n1;
    system("cls");

    if (n1==1)
    {
        do{
            cout<<"\nIS THIS YOUR FIRST VISIT IN THE HOSPITAL?(YES/NO):";
            cin>>ch1;
            system("cls");
            if(strcmp(ch1,"YES")==0||strcmp(ch1,"yes")==0||strcmp(ch1,"Yes")==0)
            {
                s1=P.add_p_file();
                sleep(3);
                j1++;
             }
            else if(strcmp(ch1,"NO")==0||strcmp(ch1,"no")==0||strcmp(ch1,"No")==0)
            {
                while(s1=="NULL")
                {
                   s1=P.pat_search();
                }
                j1++;
            }
            else
            {
                cout<<"\nWRONG INPUT"<<endl;
            }
        }while(j1==0);

        do{
            system("cls");
            cout<<"What doctor you want to visit??\n1.General medicine\n2.ENT\n3.Paediatrition\n4.Psychiatrist\n5.General Surgeon"<<endl;
            cin>>n2;
            s2=D.doc_search(n2);

          }while(s2=="F");

            cout<<"Do you want to book an appointment for today?(Yes/No)";
            cin>>ch2;

            if(strcmp(ch2,"yes")==0||strcmp(ch2,"YES")==0||strcmp(ch2,"Yes")==0)
            {
                begin:
                string d;
                int t;
                cout<<"Enter the time for the appointment:";
                cin>>d;

                t=booking(s2,d);
                if(t!=0)
                {
                    cout<<"\nDOCTOR IS AVIALABLE\n"<<endl;
                }
                else
                {
                    cout<<"\nTRY AGIAN"<<endl;
                    goto begin;
                }
                int fee=500;
                cout<<"CONSULTATION FEE Rs500\n"<<endl;
                cout<<"APPOINTMNET HAS BEEN BOOKED"<<endl<<endl;
                sleep(2);
                cout<<"\nYOU MAY VISIT THE DOCTOR"<<endl;
                sleep(3);


                system("cls");
                cout<<"Is there medicine prescribed?(Yes/No)";
                cin>>ch3;
                if(strcmp(ch3,"yes")==0||strcmp(ch3,"YES")==0||strcmp(ch3,"Yes")==0)
                {
                    system("cls");
                    int no,n,num,c=0;
                    float price;
                    char ch[50];
                    cout<<"\n1.Paracetamol \t\t\t\t2.Ibuprofen \n3.Ciprofloxacin";
                    cout<<"\t\t\t\t4.Amoxicillin \n5.Omeprazole \t\t\t\t6.Metformin \n7.Aspirin";
                    cout<<"\t\t\t\t8.Ranitidine \n9.Diclofenac \t\t\t\t10.Atorvastatin";
                    cout<<"\n11.Cough Syrup \t\t\t\t12.Multivitamin Syrup";
                    cout<<"\n13.Digestive Syrup \t\t\t14.Anti-allergic Syrup";
                    cout<<"\n15.Antacid Syrup\n";

                    cout<<"\nEnter the number of medicines: ";
                    cin>>no;

                    fstream out;
                    out.open(s1 + ".txt",ios::out);

                    out<<"PATIENT NAME : "<<s1<<"\n"<<"DOCTOR NAME : "<<s2<<"\n\n";
                    out<<"CONSULTATION FEE : 500"<<"\n\n";
                    out<<"Medicine Name\tQuantity\tRate\tPrice\n";

                    while(c<no)
                    {
                        cout<<"\nEnter medicine number:";
                        cin>>n;
                        if(n==1)
                            strcpy(ch,"Paracetamol");
                        else if (n==2)
                            strcpy(ch,"Ibuprofen");
                        else if (n==3)
                            strcpy(ch,"Ciprofloxacin");
                        else if (n==4)
                            strcpy(ch,"Amoxicillin");
                        else if (n==5)
                            strcpy(ch,"Omeprazole");
                        else if (n==6)
                            strcpy(ch,"Metformin");
                        else if (n==7)
                            strcpy(ch,"Aspirin");
                        else if (n==8)
                            strcpy(ch,"Ranitidine");
                        else if (n==9)
                            strcpy(ch,"Diclofenac");
                        else if (n==10)
                            strcpy(ch,"Atorvastatin");
                        else if (n==11)
                            strcpy(ch,"Cough Syrup");
                        else if (n==12)
                            strcpy(ch,"Multivitamin Syrup");
                        else if (n==13)
                            strcpy(ch,"Digestive Syrup");
                        else if (n==14)
                            strcpy(ch,"Anti-allergic Syrup");
                        else if (n==15)
                            strcpy(ch,"Antacid Syrup");
                        else
                        {
                            cout<<"WRONG INPUT";
                            continue;
                        }
                        c++;
                        cout<<"Number of Tablets/Number of Bottles:";
                        cin>>num;
                        cout<<endl;
                        price=M.med_search(ch);
                        total=total+(price*num)+500;
                        out<<ch<<"\t"<<num<<"\t\t"<<price<<"\t\t"<<(price*num)<<"\n";
                    }
                    out<<"\t\t\tTOTAL : "<<total<<"\n\n";
                    out.close();
                    cout<<"\n\nTOTAL BILL:"<<total;
                    sleep(3);
                    j3++;

                    system("cls");
                    cout<<"Do you want to generate the bill?(Yes/No)";
                    cin>>ch4;
                    system("cls");

                    if(strcmp(ch4,"yes")==0||strcmp(ch4,"YES")==0||strcmp(ch4,"Yes")==0)
                    {
                        fstream in;
                        in.open(s1 + ".txt",ios::in);
                        string s;
                        cout<<"\t\t\tPHARMACY BILL"<<endl;
                        while(getline(in,s))
                        {
                            cout<<s<<"\n";
                        }
                        cout<<"PLEASE PAY THE AMOUNT"<<endl;
                        sleep(2);
                        cout<<"\nPAYMENT TRANSACTION SUCCESSFULL"<<endl;
                        sleep(2);
                        cout<<"\nTHANK YOU FOR VISITING:";
                        sleep(2);
                        j2++;
                    }
                    else if (strcmp(ch2,"NO")==0||strcmp(ch2,"no")==0||strcmp(ch2,"No")==0)
                    {
                        cout<<"\nTOTAL BILL : "<<total<<endl;
                        cout<<"\nPLEASE PAY THE AMOUNT"<<endl;
                        sleep(2);
                        cout<<"\nPAYMENT TRANSACTION SUCCESSFULL"<<endl;
                        sleep(2);
                        cout<<"\nTHANK YOU FOR VISITING";
                        sleep(2);
                        j2++;
                    }
                    else
                    {
                        cout<<"WRONG INPUT";
                    }
                }

                else if (strcmp(ch2,"NO")==0||strcmp(ch2,"no")==0||strcmp(ch2,"No")==0)
                {
                    cout<<"\nTHANK YOU FOR VISITING";
                    sleep(2);
                }
            }
            else if(strcmp(ch2,"NO")==0||strcmp(ch2,"no")==0||strcmp(ch2,"No")==0)
            {
                cout<<"\nTHANK YOU FOR VISITING";
                sleep(2);
            }
            j3++;
    }

    else if (n1==2)
    {
            do{
            cout<<"\nIS THIS PATIENT'S FIRST IN THE HOSPITAL?(YES/NO):";
            cin>>ch1;
            system("cls");
            if(strcmp(ch1,"YES")==0||strcmp(ch1,"yes")==0||strcmp(ch1,"Yes")==0)
            {
                s1=P.add_p_file();
                sleep(3);
                j1++;
             }
            else if(strcmp(ch1,"NO")==0||strcmp(ch1,"no")==0||strcmp(ch1,"No")==0)
            {
                s1=P.pat_search();
                j1++;
            }
            else
            {
                cout<<"\nWRONG INPUT";
            }
        }while(j1==0);

        system("cls");
        cout<<"\n1.HEART ATTACK\n2.SEVERE BLEEDING\n3.STROKE\n4.POISONING\n5.INJURY\n6.OBSTETRIC\n";
        cin>>n3;
        if(n3==1)
        {
            strcpy(ch5,"Heart attack");
            S.spl_doc_search(ch5);
        }
        else if (n3==2)
        {
            strcpy(ch5,"Severe bleeding");
            S.spl_doc_search(ch5);
        }
        else if (n3==3)
        {
            strcpy(ch5,"Stroke");
            S.spl_doc_search(ch5);
        }
        else if (n3==4)
        {
            strcpy(ch5,"Poisoning");
            S.spl_doc_search(ch5);
        }
        else if (n3==5)
        {
            strcpy(ch5,"Injury");
            S.spl_doc_search(ch5);
        }
        else if (n3==6)
        {
            strcpy(ch5,"Obstetric");
            S.spl_doc_search(ch5);
        }
    }
    else
    {
        cout<<"THANK YOU";
    }
}
