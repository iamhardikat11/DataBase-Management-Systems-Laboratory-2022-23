/*
 @ Steps to Run the Code
   sudo -u postgres psql
   gcc Asgn3_20CS30023.c -lpq
*/
#include <stdio.h>
#include "/usr/include/postgresql/libpq-fe.h"
#include <string.h>
#include <stdlib.h>
void printDB(PGresult *data, char *columns[], int column_count) {
    int i, j;
    if (PQntuples(data) == 0 || data == NULL) {
        printf("No data Found \n");
        return;
    }
    int col_widths[column_count];
    for (i = 0; i < column_count; i++) {
        col_widths[i] = 0;
        for (j = 0; j < PQntuples(data); j++) {
            int length = strlen(PQgetvalue(data, j, i));
            if (length > col_widths[i]) {
                col_widths[i] = length;
            }
        }
    }
    char header[1024] = "";
    strcat(header, columns[0]);
    for (i = 1; i < column_count; i++) {
        int width = col_widths[i];
        strcat(header, " | ");
        strcat(header, columns[i]);
    }
    int header_length = strlen(header);
    for (i = 0; i < header_length; i++) {
        printf("-");
    }
    printf("\n");
    printf("%s\n", header);
    for (i = 0; i < header_length; i++) {
        printf("-");
    }
    printf("\n");
    for (i = 0; i < PQntuples(data); i++) {
        char row[1024] = "";
        strcat(row, PQgetvalue(data, i, 0));
        for (j = 1; j < column_count; j++) {
            int width = col_widths[j];
            strcat(row, " | ");
            strcat(row, PQgetvalue(data, i, j));
        }
        printf("%s\n", row);
    }
    for (i = 0; i < header_length; i++) {
        printf("-");
    }
    printf("\n");
    printf("\n");
}
int main()
{
    PGconn *conn = PQconnectdb("host=localhost user=postgres password=1234 dbname=postgres");
    if (PQstatus(conn) == CONNECTION_OK)
    {
        printf("Connection to database successful\n");
        PQexec(conn, "SET client_min_messages = WARNING;");
        PQexec(conn, "CREATE TABLE IF NOT EXISTS Physician ( EmployeeID INTEGER PRIMARY KEY NOT NULL, Name TEXT NOT NULL, Position TEXT NOT NULL, SSN INTEGER NOT NULL);");
        PQexec(conn, "CREATE TABLE IF NOT EXISTS Department (DepartmentID INTEGER PRIMARY KEY NOT NULL, Name TEXT NOT NULL, Head INTEGER NOT NULL);");
        PQexec(conn, "CREATE TABLE IF NOT EXISTS Affiliated_With (PrimaryAffiliation BOOLEAN NOT NULL DEFAULT false, Physician INTEGER NOT NULL, Department INTEGER NOT NULL, PRIMARY KEY (Department, Physician), FOREIGN KEY (Physician) REFERENCES Physician (EmployeeID), FOREIGN KEY (Department) REFERENCES Department (DepartmentID) );");
        PQexec(conn, "CREATE TABLE IF NOT EXISTS Procedure ( Code INTEGER PRIMARY KEY NOT NULL, Name TEXT NOT NULL, Cost INTEGER NOT NULL);");
        PQexec(conn, "CREATE TABLE IF NOT EXISTS Trained_In ( Physician INTEGER NOT NULL, Treatment INTEGER NOT NULL, CertificationDate DATE NOT NULL, CertificationExpires DATE NOT NULL, PRIMARY KEY ( Physician, Treatment), FOREIGN KEY (Physician) REFERENCES Physician(EmployeeID), FOREIGN KEY (Treatment) REFERENCES Procedure (Code) );");
        PQexec(conn, "CREATE TABLE IF NOT EXISTS Patient (SSN INTEGER PRIMARY KEY NOT NULL, Name TEXT NOT NULL, Address TEXT NOT NULL, Phone TEXT NOT NULL, InsuranceID INTEGER NOT NULL, PCP INTEGER NOT NULL, FOREIGN KEY (PCP) REFERENCES Physician(EmployeeID) );");
        PQexec(conn, "CREATE TABLE IF NOT EXISTS Nurse(EmployeeID INTEGER PRIMARY KEY NOT NULL, Name TEXT NOT NULL, Position TEXT NOT NULL, Registered BOOLEAN NOT NULL DEFAULT FALSE, SSN INTEGER NOT NULL );");
        PQexec(conn, "CREATE TABLE IF NOT EXISTS Appointment (AppointmentID INTEGER PRIMARY KEY NOT NULL, Patient INTEGER NOT NULL, PrepNurse INTEGER, Physician INTEGER NOT NULL, StartDate DATE NOT NULL, EndDate DATE NOT NULL, ExaminationRoom TEXT NOT NULL, FOREIGN KEY (Physician) REFERENCES Physician(EmployeeID), FOREIGN KEY (PrepNurse) REFERENCES Nurse(EmployeeID), FOREIGN KEY (Patient) REFERENCES Patient(SSN));");
        PQexec(conn, "CREATE TABLE IF NOT EXISTS Medication ( Code INTEGER PRIMARY KEY NOT NULL, Name TEXT NOT NULL, Brand TEXT NOT NULL, Description TEXT NOT NULL);");
        PQexec(conn, "CREATE TABLE IF NOT EXISTS Prescribes ( Physician INTEGER NOT NULL, Patient INTEGER NOT NULL, Medication INTEGER NOT NULL, Date DATE NOT NULL, Appointment INTEGER, Dose TEXT NOT NULL, PRIMARY KEY (Physician, Patient, Medication, Date), FOREIGN KEY (Physician) REFERENCES Physician(EmployeeID), FOREIGN KEY (Patient) REFERENCES Patient(SSN), FOREIGN KEY (Medication) REFERENCES Medication(Code), FOREIGN KEY (Appointment) REFERENCES Appointment(AppointmentID) );");
        PQexec(conn, "CREATE TABLE IF NOT EXISTS Block (Floor INTEGER NOT NULL, Code INTEGER NOT NULL, PRIMARY KEY (Floor, Code) );");
        PQexec(conn, "CREATE TABLE IF NOT EXISTS Room (Number INTEGER PRIMARY KEY NOT NULL, Type TEXT NOT NULL, BlockFloor INTEGER NOT NULL, BlockCode INTEGER NOT NULL, Unavailable BOOLEAN NOT NULL DEFAULT FALSE, FOREIGN KEY (BlockFloor, BlockCode) REFERENCES Block(Floor, Code));");
        PQexec(conn, "CREATE TABLE IF NOT EXISTS On_Call(Nurse INTEGER NOT NULL, BlockFloor INTEGER NOT NULL, BlockCode INTEGER NOT NULL, StartDate DATE NOT NULL, EndDate DATE NOT NULL, PRIMARY KEY (Nurse, BlockFloor, BlockCode, StartDate, EndDate), FOREIGN KEY (BlockFloor, BlockCode) REFERENCES Block(Floor, Code), FOREIGN KEY (Nurse) REFERENCES Nurse(EmployeeID));");
        PQexec(conn, "CREATE TABLE IF NOT EXISTS Stay(StayID INTEGER PRIMARY KEY NOT NULL, Patient INTEGER NOT NULL, Room INTEGER NOT NULL, StartDate DATE NOT NULL, EndDate DATE NOT NULL, FOREIGN KEY (Patient) REFERENCES Patient(SSN), FOREIGN KEY (Room) REFERENCES Room(Number));");
        PQexec(conn, "CREATE TABLE IF NOT EXISTS Undergoes(Patient INTEGER NOT NULL, Procedure1 INTEGER NOT NULL, Stay INTEGER NOT NULL, Date1 DATE NOT NULL, Physician INTEGER NOT NULL, AssistingNurse INTEGER NOT NULL, PRIMARY KEY (Patient, Procedure1, Stay, Date1), FOREIGN KEY (Physician) REFERENCES Physician(EmployeeID), FOREIGN KEY (Patient) REFERENCES Patient(SSN), FOREIGN KEY (AssistingNurse) REFERENCES Nurse(EmployeeID), FOREIGN KEY (Stay) REFERENCES Stay(StayID), FOREIGN KEY (Procedure1) REFERENCES Procedure(Code) );");
        // Deleting all Data Tuples from every table Table
        PQexec(conn, "DELETE FROM Undergoes;");
        PQexec(conn, "DELETE FROM Stay;");
        PQexec(conn, "DELETE FROM On_Call;");
        PQexec(conn, "DELETE FROM Room;");
        PQexec(conn, "DELETE FROM Block;");
        PQexec(conn, "DELETE FROM Prescribes;");
        PQexec(conn, "DELETE FROM Medication;");
        PQexec(conn, "DELETE FROM Appointment;");
        PQexec(conn, "DELETE FROM Trained_In;");
        PQexec(conn, "DELETE FROM Affiliated_With;");
        PQexec(conn, "DELETE FROM Patient;");
        PQexec(conn, "DELETE FROM Physician;");
        PQexec(conn, "DELETE FROM Procedure;");
        PQexec(conn, "DELETE FROM Department;");
        PQexec(conn, "DELETE FROM Nurse;");
        // Inserting into Physician table
        PQexec(conn, "INSERT INTO Physician VALUES(1,'John Dorian','Staff Internist',111111111);");
        PQexec(conn, "INSERT INTO Physician VALUES(2,'Elliot Reid','Attending Physician',222222222);");
        PQexec(conn, "INSERT INTO Physician VALUES(3,'Christopher Turk','Surgical Attending Physician',333333333);");
        PQexec(conn, "INSERT INTO Physician VALUES(4,'Percival Cox','Senior Attending Physician',444444444);");
        PQexec(conn, "INSERT INTO Physician VALUES(5,'Bob Kelso','Head Chief of Medicine',555555555);");
        PQexec(conn, "INSERT INTO Physician VALUES(6,'Todd Quinlan','Surgical Attending Physician',666666666);");
        PQexec(conn, "INSERT INTO Physician VALUES(7,'John Wen','Surgical Attending Physician',777777777);");
        PQexec(conn, "INSERT INTO Physician VALUES(8,'Keith Dudemeister','MD Resident',888888888);");
        PQexec(conn, "INSERT INTO Physician VALUES(9,'Molly Clock','Attending Psychiatrist',999999999);");
        // Inserting into Department table
        PQexec(conn, "INSERT INTO Department VALUES(1,'General Medicine',4);");
        PQexec(conn, "INSERT INTO Department VALUES(2,'Surgery',7);");
        PQexec(conn, "INSERT INTO Department VALUES(3,'Psychiatry',9);");
        PQexec(conn, "INSERT INTO Department VALUES(4,'Cardiology',3);");
        // Inserting into Affliated With Table
        PQexec(conn, "INSERT INTO Affiliated_With VALUES(true,1,1);");
        PQexec(conn, "INSERT INTO Affiliated_With VALUES(true,4,4);");
        PQexec(conn, "INSERT INTO Affiliated_With VALUES(false,5,3);");
        PQexec(conn, "INSERT INTO Affiliated_With VALUES(true,7,4);");
        PQexec(conn, "INSERT INTO Affiliated_With VALUES(true,2,2);");
        PQexec(conn, "INSERT INTO Affiliated_With VALUES(false,9,3);");
        PQexec(conn, "INSERT INTO Affiliated_With VALUES(true,6,1);");
        PQexec(conn, "INSERT INTO Affiliated_With VALUES(true,3,3);");
        PQexec(conn, "INSERT INTO Affiliated_With VALUES(true,8,1);");
        // Inserting into Procedure Table
        PQexec(conn, "INSERT INTO Procedure VALUES(1, 'Reverse Rhinopodoplasty',1500.0);");
        PQexec(conn, "INSERT INTO Procedure VALUES(2, 'Obtuse Pyloric Recombustion',8750.0);");
        PQexec(conn, "INSERT INTO Procedure VALUES(3, 'Folded Demiopthalmectomy',4500.0);");
        PQexec(conn, "INSERT INTO Procedure VALUES(4, 'Complete Wallectomy', 5500.0);");
        PQexec(conn, "INSERT INTO Procedure VALUES(5, 'bypass surgery', 5899.0);");
        PQexec(conn, "INSERT INTO Procedure VALUES(6, 'Reversible PancreaomyPlasty', 1322.40);");
        // Inserting into Patient Table
        PQexec(conn, "INSERT INTO Patient (SSN, Name, Address, Phone, InsuranceID, PCP) VALUES(100000001,'Jonhny Smithsonian','42 Foobar Lane','+91 983-555-0256',68476213,1);");
        PQexec(conn, "INSERT INTO Patient (SSN, Name, Address, Phone, InsuranceID, PCP) VALUES(100000002,'Grace Ritchie','37 Snafu Drive','+91 785-551-0512',36546321,6);");
        PQexec(conn, "INSERT INTO Patient (SSN, Name, Address, Phone, InsuranceID, PCP) VALUES(100000003,'Random J. Patient','101 Omgbbq Street','+91 985-552-1204',65465421,5);");
        PQexec(conn, "INSERT INTO Patient (SSN, Name, Address, Phone, InsuranceID, PCP) VALUES(100000004,'Dennis Doe','1100 Foobaz Avenue','+91 895-552-2048',68421879,3);");
        // Inserting into Trained In Table
        PQexec(conn, "INSERT INTO Trained_In (Treatment, Physician, CertificationDate, CertificationExpires) VALUES(1,1,'2008-01-01 12:00:00','2008-12-31 12:00:00');");
        PQexec(conn, "INSERT INTO Trained_In (Treatment, Physician, CertificationDate, CertificationExpires) VALUES(2,3,'2008-01-01 12:00:00','2008-12-31 12:00:00');");
        PQexec(conn, "INSERT INTO Trained_In (Treatment, Physician, CertificationDate, CertificationExpires) VALUES(3,3,'2008-01-01 12:00:00','2008-12-31 12:00:00');");
        PQexec(conn, "INSERT INTO Trained_In (Treatment, Physician, CertificationDate, CertificationExpires) VALUES(6,3,'2008-01-01 12:00:00','2008-12-31 12:00:00');");
        PQexec(conn, "INSERT INTO Trained_In (Treatment, Physician, CertificationDate, CertificationExpires) VALUES(4,4,'2008-01-01 12:00:00','2008-12-31 12:00:00');");
        PQexec(conn, "INSERT INTO Trained_In (Treatment, Physician, CertificationDate, CertificationExpires) VALUES(2,2,'2008-01-01 12:00:00','2008-12-31 12:00:00');");
        PQexec(conn, "INSERT INTO Trained_In (Treatment, Physician, CertificationDate, CertificationExpires) VALUES(5,6,'2007-01-01 12:00:00','2007-12-31 12:00:00');");
        PQexec(conn, "INSERT INTO Trained_In (Treatment, Physician, CertificationDate, CertificationExpires) VALUES(6,4,'2008-01-01 12:00:00','2008-12-31 12:00:00');");
        PQexec(conn, "INSERT INTO Trained_In (Treatment, Physician, CertificationDate, CertificationExpires) VALUES(5,7,'2008-01-01 12:00:00','2008-12-31 12:00:00');");
        PQexec(conn, "INSERT INTO Trained_In (Treatment, Physician, CertificationDate, CertificationExpires) VALUES(2,8,'2008-01-01 12:00:00','2008-12-31 12:00:00');");
        PQexec(conn, "INSERT INTO Trained_In (Treatment, Physician, CertificationDate, CertificationExpires) VALUES(3,9,'2008-01-01 12:00:00','2008-12-31 12:00:00');");
        PQexec(conn, "INSERT INTO Trained_In (Treatment, Physician, CertificationDate, CertificationExpires) VALUES(4,5,'2008-01-01 12:00:00','2008-12-31 12:00:00');");
        PQexec(conn, "INSERT INTO Trained_In (Treatment, Physician, CertificationDate, CertificationExpires) VALUES(5,4,'2008-01-01 12:00:00','2008-12-31 12:00:00');");
        PQexec(conn, "INSERT INTO Trained_In (Treatment, Physician, CertificationDate, CertificationExpires) VALUES(6,6,'2008-01-01 12:00:00','2008-12-31 12:00:00');");
        PQexec(conn, "INSERT INTO Trained_In (Treatment, Physician, CertificationDate, CertificationExpires) VALUES(3,4,'2008-01-01 12:00:00','2008-12-31 12:00:00');");
        // Inserting into Nurse Table
        PQexec(conn, "INSERT INTO Nurse VALUES(101,'Carla Espinosa','Head Nurse',true,111111110);");
        PQexec(conn, "INSERT INTO Nurse VALUES(102,'Laverne Roberts','Nurse',true,222222220);");
        PQexec(conn, "INSERT INTO Nurse VALUES(103,'Paul Flowers','Nurse',false,333333330);");
        // Inserting into Appointment Table
        PQexec(conn, "INSERT INTO Appointment VALUES(13216584,100000001,101,4,'2008-04-24 10:00','2008-04-24 11:00','A');");
        PQexec(conn, "INSERT INTO Appointment VALUES(26548913,100000002,101,2,'2008-04-24 10:00','2008-04-24 11:00','B');");
        PQexec(conn, "INSERT INTO Appointment VALUES(36549879,100000001,102,4,'2008-04-25 10:00','2008-04-25 11:00','A');");
        PQexec(conn, "INSERT INTO Appointment VALUES(46846589,100000004,103,4,'2008-04-25 10:00','2008-04-25 11:00','B');");
        PQexec(conn, "INSERT INTO Appointment VALUES(59871321,100000004,NULL,4,'2008-04-26 10:00','2008-04-26 11:00','C');");
        PQexec(conn, "INSERT INTO Appointment VALUES(69879231,100000003,103,2,'2008-04-26 11:00','2008-04-26 12:00','C');");
        PQexec(conn, "INSERT INTO Appointment VALUES(76983231,100000001,NULL,3,'2008-04-26 12:00','2008-04-26 13:00','C');");
        PQexec(conn, "INSERT INTO Appointment VALUES(86213939,100000004,102,9,'2008-04-27 10:00','2008-04-21 11:00','A');");
        PQexec(conn, "INSERT INTO Appointment VALUES(93216548,100000002,101,2,'2008-04-27 10:00','2008-04-27 11:00','B');");
        // Inserting into Medication table
        PQexec(conn, "INSERT INTO Medication VALUES(1,'Procrastin-X','X','N/A');");
        PQexec(conn, "INSERT INTO Medication VALUES(2,'Remdesivir','Foo Labs','N/A');");
        PQexec(conn, "INSERT INTO Medication VALUES(3,'Awakin','Bar Laboratories','N/A');");
        PQexec(conn, "INSERT INTO Medication VALUES(4,'Crescavitin','Baz Industries','N/A');");
        PQexec(conn, "INSERT INTO Medication VALUES(5,'Melioraurin','Snafu Pharmaceuticals','N/A');");
        // Inserting into Prescribe table
        PQexec(conn, "INSERT INTO Prescribes VALUES(1,100000001,1,'2008-04-24 10:47',13216584,'5');");
        PQexec(conn, "INSERT INTO Prescribes VALUES(8,100000001,2,'2008-04-27 10:53',86213939,'10');");
        PQexec(conn, "INSERT INTO Prescribes VALUES(9,100000002,3,'2008-04-30 16:53',NULL,'5');");
        PQexec(conn, "INSERT INTO Prescribes VALUES(2,100000003,2,'2008-04-27 10:53',86213939,'10');");
        PQexec(conn, "INSERT INTO Prescribes VALUES(3,100000004,2,'2008-04-27 10:53',86213939,'10');");
        PQexec(conn, "INSERT INTO Prescribes VALUES(4,100000001,2,'2008-04-27 10:53',86213939,'10');");
        // Inserting into Block Table
        PQexec(conn, "INSERT INTO Block VALUES(1,1);");
        PQexec(conn, "INSERT INTO Block VALUES(1,2);");
        PQexec(conn, "INSERT INTO Block VALUES(1,3);");
        PQexec(conn, "INSERT INTO Block VALUES(2,1);");
        PQexec(conn, "INSERT INTO Block VALUES(2,2);");
        PQexec(conn, "INSERT INTO Block VALUES(2,3);");
        PQexec(conn, "INSERT INTO Block VALUES(3,1);");
        PQexec(conn, "INSERT INTO Block VALUES(3,2);");
        PQexec(conn, "INSERT INTO Block VALUES(3,3);");
        PQexec(conn, "INSERT INTO Block VALUES(4,1);");
        PQexec(conn, "INSERT INTO Block VALUES(4,2);");
        PQexec(conn, "INSERT INTO Block VALUES(4,3);");
        // Inserting into Room Table
        PQexec(conn, "INSERT INTO Room VALUES(101,'Single',1,1,false);");
        PQexec(conn, "INSERT INTO Room VALUES(102,'Single',1,1,false);");
        PQexec(conn, "INSERT INTO Room VALUES(103,'icu',1,1,false);");
        PQexec(conn, "INSERT INTO Room VALUES(111,'icu',1,2,false);");
        PQexec(conn, "INSERT INTO Room VALUES(112,'Single',1,2,true);");
        PQexec(conn, "INSERT INTO Room VALUES(113,'Single',1,2,false);");
        PQexec(conn, "INSERT INTO Room VALUES(121,'Single',1,3,false);");
        PQexec(conn, "INSERT INTO Room VALUES(122,'icu',1,3,false);");
        PQexec(conn, "INSERT INTO Room VALUES(123,'Single',1,3,false);");
        PQexec(conn, "INSERT INTO Room VALUES(201,'Single',2,1,true);");
        PQexec(conn, "INSERT INTO Room VALUES(202,'icu',2,1,false);");
        PQexec(conn, "INSERT INTO Room VALUES(203,'Single',2,1,false);");
        PQexec(conn, "INSERT INTO Room VALUES(211,'Single',2,2,false);");
        PQexec(conn, "INSERT INTO Room VALUES(212,'Single',2,2,false);");
        PQexec(conn, "INSERT INTO Room VALUES(213,'Single',2,2,true);");
        PQexec(conn, "INSERT INTO Room VALUES(221,'Single',2,3,false);");
        PQexec(conn, "INSERT INTO Room VALUES(222,'Single',2,3,false);");
        PQexec(conn, "INSERT INTO Room VALUES(223,'Single',2,3,false);");
        PQexec(conn, "INSERT INTO Room VALUES(301,'Single',3,1,false);");
        PQexec(conn, "INSERT INTO Room VALUES(302,'Single',3,1,true);");
        PQexec(conn, "INSERT INTO Room VALUES(303,'Single',3,1,false);");
        PQexec(conn, "INSERT INTO Room VALUES(311,'icu',3,2,false);");
        PQexec(conn, "INSERT INTO Room VALUES(312,'Single',3,2,false);");
        PQexec(conn, "INSERT INTO Room VALUES(313,'Single',3,2,false);");
        PQexec(conn, "INSERT INTO Room VALUES(321,'Single',3,3,true);");
        PQexec(conn, "INSERT INTO Room VALUES(322,'Single',3,3,false);");
        PQexec(conn, "INSERT INTO Room VALUES(323,'Single',3,3,false);");
        PQexec(conn, "INSERT INTO Room VALUES(401,'icu',4,1,false);");
        PQexec(conn, "INSERT INTO Room VALUES(402,'Single',4,1,true);");
        PQexec(conn, "INSERT INTO Room VALUES(403,'Single',4,1,false);");
        PQexec(conn, "INSERT INTO Room VALUES(411,'icu',4,2,false);");
        PQexec(conn, "INSERT INTO Room VALUES(412,'Single',4,2,false);");
        PQexec(conn, "INSERT INTO Room VALUES(413,'Single',4,2,false);");
        PQexec(conn, "INSERT INTO Room VALUES(421,'Single',4,3,true);");
        PQexec(conn, "INSERT INTO Room VALUES(422,'Single',4,3,false);");
        PQexec(conn, "INSERT INTO Room VALUES(423,'Single',4,3,false);");
        // Inserting into On_Call Table
        PQexec(conn, "INSERT INTO On_Call VALUES(101,1,1,'2008-11-04 11:00','2008-11-04 19:00');");
        PQexec(conn, "INSERT INTO On_Call VALUES(101,1,2,'2008-11-04 11:00','2008-11-04 19:00');");
        PQexec(conn, "INSERT INTO On_Call VALUES(102,1,3,'2008-11-04 11:00','2008-11-04 19:00');");
        PQexec(conn, "INSERT INTO On_Call VALUES(103,1,1,'2008-11-04 19:00','2008-11-05 03:00');");
        PQexec(conn, "INSERT INTO On_Call VALUES(103,1,2,'2008-11-04 19:00','2008-11-05 03:00');");
        PQexec(conn, "INSERT INTO On_Call VALUES(103,1,3,'2008-11-04 19:00','2008-11-05 03:00');");
        // Inserting into Stay Table
        PQexec(conn, "INSERT INTO Stay VALUES(3215,100000001,111,'2008-05-01','2008-07-04');");
        PQexec(conn, "INSERT INTO Stay VALUES(3216,100000003,123,'2008-05-03','2008-05-14');");
        PQexec(conn, "INSERT INTO Stay VALUES(3217,100000004,112,'2008-05-02','2008-05-03');");
        // Inserting into Undergoes Table
        PQexec(conn, "INSERT INTO Undergoes VALUES(100000001,6,3215,'2008-05-02',3,101);");
        PQexec(conn, "INSERT INTO Undergoes VALUES(100000001,2,3215,'2008-05-03',7,101);");
        PQexec(conn, "INSERT INTO Undergoes VALUES(100000004,1,3217,'2008-05-07',3,102);");
        PQexec(conn, "INSERT INTO Undergoes VALUES(100000004,5,3217,'2008-05-09',6,102);");
        PQexec(conn, "INSERT INTO Undergoes VALUES(100000001,3,3217,'2008-05-10',7,101);");
        PQexec(conn, "INSERT INTO Undergoes VALUES(100000004,4,3217,'2008-05-13',3,103);");
        while (1)
        {
            int n;
            printf("[?] Enter Query:-:Number (1-13) or Zero to Exit: ");
            scanf("%d", &n);
            if (n == 0)
            {
                printf("Exiting...\n");
                break;
            }
            else if (n == 1)
            {
                /*
                Questions
                    Queries: Obtain the following -
                    1. Names of all physicians who are trained in procedure name “bypass surgery”
                */
                printf("\n[*] Answer to Query 1:-\n");
                PGresult *res = PQexec(conn, "SELECT P.Name AS Physician_Name FROM Physician AS P JOIN Trained_In AS T ON P.EmployeeID = T.Physician JOIN Procedure AS Pr ON T.Treatment = Pr.Code WHERE Pr.name = 'bypass surgery' ;");
                char* arr[] = {"Physician_Name"};
                printDB(res, arr, 1);
                PQclear(res);
            }
            else if (n == 2)
            {
                /*
                2. Names of all physicians affiliated with the department name “cardiology” and trained in "bypass surgery"
                */
                printf("\n[*] Answer to Query 2:-\n");
                PGresult *res = PQexec(conn, "SELECT P.Name FROM Physician AS P JOIN Affiliated_With AS AW ON P.EmployeeID = AW.Physician JOIN Department AS D ON AW.Department = D.DepartmentID JOIN Trained_In AS T ON P.EmployeeID = T.Physician JOIN Procedure AS Pr ON T.Treatment = Pr.Code WHERE D.Name = 'Cardiology' AND Pr.Name = 'bypass surgery';");
                char* arr[] = {"Physician_Name"};
                printDB(res, arr, 1);
                PQclear(res);
            }
            else if (n == 3)
            {
                /*
                    3. Names of all the nurses who have ever been on call for room 123
                */
                printf("\n[*] Answer to Query 3:-\n");
                PGresult *res = PQexec(conn, "SELECT Name FROM Nurse WHERE EmployeeID IN ( SELECT Nurse FROM On_Call WHERE BlockFloor IN ( SELECT BlockFloor FROM Room WHERE Number=123 ) AND BlockCode IN( SELECT BlockCode FROM Room WHERE Number=123 ));");
                char* arr[] = {"Nurse_Name"};
                printDB(res, arr, 1);
                PQclear(res);
            }
            else if (n == 4)
            {
                /*
                    4. Names and addresses of all patients who were prescribed the medication named “remdesivir”
                */
                printf("\n[*] Answer to Query 4:-\n");
                PGresult *res = PQexec(conn, "SELECT Name, Address FROM Patient WHERE SSN IN ( SELECT Patient FROM Prescribes WHERE Medication IN ( SELECT Code FROM Medication WHERE Name='Remdesivir' ));");
                char* arr[] = {"Name_Patient", "Address_Patient"};
                printDB(res, arr, 2);
                PQclear(res);
            }
            else if (n == 5)
            {
                /*
                    5. Name and insurance id of all patients who stayed in the “icu” room type for more than 15 days
                */
                printf("\n[*] Answer to Query 5:-\n");
                PGresult *res = PQexec(conn, "SELECT P.Name AS Patient_Name, P.InsuranceID AS Patient_InsuranceID FROM Patient P JOIN Stay S ON P.SSN = S.Patient JOIN Room R ON S.Room = R.Number WHERE S.EndDate-S.StartDate > 15 AND R.Type='icu';");
                char* arr[] = {"Patient_Name", "Patient_Insurance_ID"};
                printDB(res, arr, 2);
                PQclear(res);
            }
            else if (n == 6)
            {
                /*
                    6. Names of all nurses who assisted in the procedure name “bypass surgery”
                */
                printf("\n[*] Answer to Query 6:-\n");
                PGresult *res = PQexec(conn, "SELECT N.Name AS Nurse_Name FROM Undergoes U JOIN Procedure P ON U.Procedure1 = P.Code JOIN Nurse N ON U.AssistingNurse = N.EmployeeID WHERE P.Name = 'bypass surgery';");
                char* arr[] = {"Nurse_Name"};
                printDB(res, arr, 1);
                PQclear(res);
            }
            else if (n == 7)
            {
                /*
                    7. Name and position of all nurses who assisted in the procedure name “bypass surgery” along with the names of and the accompanying physicians
                */

                printf("\n[*] Answer to Query 7:-\n");
                PGresult *res = PQexec(conn, "SELECT P.Name AS Physician_Name, N.Name AS Nurse_Name, N.Position AS Nurse_Position FROM Undergoes U JOIN Physician P ON U.Physician = P.EmployeeID JOIN Nurse N ON U.AssistingNurse = N.EmployeeID JOIN Procedure Pr ON U.Procedure1 = Pr.Code WHERE Pr.Name = 'bypass surgery';");
                char* arr[] = {" Physician_Name", "Nurse_Name", "Nurse_Position"};
                printDB(res, arr, 3);
                PQclear(res);
            }
            else if (n == 8)
            {
                /*
                    8. Obtain the names of all physicians who have performed a medical procedure they have never been trained to perform
                */
                printf("\n[*] Answer to Query 8:-\n");
                PGresult *res = PQexec(conn, "SELECT DISTINCT Physician.Name FROM Undergoes LEFT JOIN Trained_In ON Undergoes.Physician = Trained_In.Physician AND Undergoes.Procedure1 = Trained_In.Treatment JOIN Physician ON Undergoes.Physician = Physician.EmployeeID WHERE Trained_In.Treatment IS NULL;");
                char* arr[] = {" Physician_Name"};
                printDB(res, arr, 1);
                PQclear(res);
            }
            else if (n == 9)
            {
                /*
                    9. Names of all physicians who have performed a medical procedure that they are trained to perform, but such that the procedure was done at a date (Undergoes.Date) after the physician's certification expired (Trained_In.CertificationExpires)
                */
                printf("\n[*] Answer to Query 9:-\n");
                PGresult *res = PQexec(conn, "SELECT Name FROM Physician WHERE EmployeeID IN ( SELECT U.Physician FROM Undergoes U JOIN Trained_In T ON T.Physician = U.Physician WHERE U.Date1 > T.CertificationExpires);");
                char* arr[] = {" Physician_Name"};
                printDB(res, arr, 1);
                PQclear(res);
            }
            else if (n == 10)
            {
                /*
                    10. Same as the previous query, but include the following information in the results: Physician name, name of procedure, date when the procedure was carried out, name of the patient the procedure was carried out on
                */
                printf("\n[*] Answer to Query 10:-\n");
                PGresult *res = PQexec(conn, "SELECT P.Name AS Physician_Name, Pr.Name AS Procedure_Name, U.Date1 AS Procedure_Date, Pa.Name AS Patient_Name FROM Undergoes U JOIN Trained_In T ON T.Physician = U.Physician JOIN Patient Pa  ON U.Patient = Pa.SSN JOIN Physician P  ON T.Physician = P.EmployeeID JOIN Procedure Pr ON U.Procedure1 = Pr.Code WHERE U.Date1 > T.CertificationExpires;");
                char* arr[] = {" Physician_Name","Procedure_Name", "Procedure_Date", "Patient_Name"};
                printDB(res, arr, 4);
                PQclear(res);
            }
            else if (n == 11)
            {
                /*
                    11. Names of all patients (also include, for each patient, the name of the patient's physician), such that all the following are true:
                            • The patient has been prescribed some medication by his/her physician
                            • The patient has undergone a procedure with a cost larger that 5000
                            • The patient has had at least two appointment where the physician was affiliated with the cardiology department
                            • The patient's physician is not the head of any department
                */

                printf("\n[*] Answer to Query 11:-\n");
                PGresult *res = PQexec(conn, "WITH count_appointments AS (SELECT Physician, Patient, COUNT(*) AS count FROM Appointment GROUP BY Physician, Patient) SELECT Pa.Name AS Patient_Name, P.Name AS Physician_Name FROM Patient Pa JOIN Undergoes U ON Pa.SSN = U.Patient JOIN Department D ON D.Name = 'Cardiology' JOIN Physician P ON P.EmployeeID != D.Head JOIN Affiliated_With AW ON AW.Department = D.DepartmentID JOIN Procedure Pr ON U.Procedure1 = Pr.Code JOIN Prescribes Pre ON P.EmployeeID = Pre.Physician JOIN count_appointments AP ON P.EmployeeID = AP.Physician AND Pa.SSN = AP.Patient WHERE Pr.Cost > 5000 AND P.EmployeeID = AW.Physician AND Pa.SSN = Pre.Patient AND AP.count >= 2;");
                char* arr[] = {"Patient_Name"," Physician_Name"};
                printDB(res, arr, 2);
                PQclear(res);
            }
            else if (n == 12)
            {
                /*
                    12. Name and brand of the medication which has been prescribed to the highest number of patients
                */
                printf("\n[*] Answer to Query 12:-\n");
                PGresult *res = PQexec(conn, "WITH count_prescriptions AS (SELECT Medication, COUNT(*) AS count FROM Prescribes GROUP BY Medication) SELECT Name, Brand FROM Medication WHERE Code IN ( SELECT Medication FROM count_prescriptions WHERE count IN ( SELECT MAX(count) FROM count_prescriptions WHERE Medication IS NOT NULL));");
                char* arr[] = {"Name","Brand"};
                printDB(res, arr, 2);
                PQclear(res);
            }
            else if (n == 13)
            {
                /*
                    13. Names of all physicians who are trained in procedure name as custom name
                */
                
                size_t pr_name_size = 100;
                char *pr_name = (char *)malloc(pr_name_size * sizeof(char));
                memset(pr_name, '\0', pr_name_size);
                printf("\n\n[?] Enter the procedure name[Size less than 100]:- ");
                int k = getline(&pr_name, &pr_name_size, stdin);
                k = getline(&pr_name, &pr_name_size, stdin);
                if (k == -1) {
                    printf("Error reading input\n");
                    continue;
                } 
                printf("\n[*] Answer to Query 13:-\n");
                char* buf = (char *)malloc(500*sizeof(char));
                strcpy(buf,"SELECT P.Name AS Physician_Name FROM Physician AS P JOIN Trained_In AS T ON P.EmployeeID = T.Physician JOIN Procedure AS Pr ON T.Treatment = Pr.Code WHERE Pr.name = \'");
                int i, j;
                for (i = 0; buf[i] != '\0'; i++);
                for (j = 0; pr_name[j] != '\0'; j++) {
                        buf[i + j] = pr_name[j];
                }
                strcpy(buf+i+j-1, "\';"); 
                buf[strlen(buf)] = '\0';
                PGresult *res = PQexec(conn,buf);
                char* arr[] = {"Physician_Name"};
                printDB(res, arr, 1);
                PQclear(res);
            }
            else
                printf("INVALID CHOICE!!");
        }
    }
    else
        printf("Connection to database failed\n");
    PQfinish(conn);
    return 0;
}