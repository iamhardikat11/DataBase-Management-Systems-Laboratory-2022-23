"""
    Name:- Hardik Pravin Soni
    Roll No:- 20CS30023
    Subject:- Database Management System Labortary 2023 (CS39202)
    Assignment 3 
    File in Python
"""
import psycopg2
conn = psycopg2.connect("dbname=postgres user=hardiksoni")
# Open a cursor to perform database operations
cur = conn.cursor()
# Creation of Table Done
cur.execute("CREATE TABLE IF NOT EXISTS Physician ( EmployeeID INTEGER PRIMARY KEY NOT NULL, Name TEXT NOT NULL, Position TEXT NOT NULL, SSN INTEGER NOT NULL);")
cur.execute("CREATE TABLE IF NOT EXISTS Department (DepartmentID INTEGER PRIMARY KEY NOT NULL, Name TEXT NOT NULL, Head INTEGER NOT NULL);")
cur.execute("CREATE TABLE IF NOT EXISTS Affiliated_With (PrimaryAffiliation BOOLEAN NOT NULL DEFAULT false, Physician INTEGER NOT NULL, Department INTEGER NOT NULL, PRIMARY KEY (Department, Physician), FOREIGN KEY (Physician) REFERENCES Physician (EmployeeID), FOREIGN KEY (Department) REFERENCES Department (DepartmentID) );")
cur.execute("CREATE TABLE IF NOT EXISTS Procedure ( Code INTEGER PRIMARY KEY NOT NULL, Name TEXT NOT NULL, Cost INTEGER NOT NULL);")
cur.execute("CREATE TABLE IF NOT EXISTS Trained_In ( Physician INTEGER NOT NULL, Treatment INTEGER NOT NULL, CertificationDate DATE NOT NULL, CertificationExpires DATE NOT NULL, PRIMARY KEY ( Physician, Treatment), FOREIGN KEY (Physician) REFERENCES Physician(EmployeeID), FOREIGN KEY (Treatment) REFERENCES Procedure (Code) );")
cur.execute("CREATE TABLE IF NOT EXISTS Patient (SSN INTEGER PRIMARY KEY NOT NULL, Name TEXT NOT NULL, Address TEXT NOT NULL, Phone TEXT NOT NULL, InsauranceID INTEGER NOT NULL, PCP INTEGER NOT NULL, FOREIGN KEY (PCP) REFERENCES Physician(EmployeeID) );")
cur.execute("CREATE TABLE IF NOT EXISTS Nurse(EmployeeID INTEGER PRIMARY KEY NOT NULL, Name TEXT NOT NULL, Position TEXT NOT NULL, Registered BOOLEAN NOT NULL DEFAULT FALSE, SSN INTEGER NOT NULL );")
cur.execute("CREATE TABLE IF NOT EXISTS Appointment (AppointmentID INTEGER PRIMARY KEY NOT NULL, Patient INTEGER NOT NULL, PrepNurse INTEGER, Physician INTEGER NOT NULL, StartDate DATE NOT NULL, EndDate DATE NOT NULL, ExaminationRoom TEXT NOT NULL, FOREIGN KEY (Physician) REFERENCES Physician(EmployeeID), FOREIGN KEY (PrepNurse) REFERENCES Nurse(EmployeeID), FOREIGN KEY (Patient) REFERENCES Patient(SSN));")
cur.execute("CREATE TABLE IF NOT EXISTS Medication ( Code INTEGER PRIMARY KEY NOT NULL, Name TEXT NOT NULL, Brand TEXT NOT NULL, Description TEXT NOT NULL);")
cur.execute("CREATE TABLE IF NOT EXISTS Prescribes ( Physician INTEGER NOT NULL, Patient INTEGER NOT NULL, Medication INTEGER NOT NULL, Date DATE NOT NULL, Appointment INTEGER, Dose TEXT NOT NULL, PRIMARY KEY (Physician, Patient, Medication, Date), FOREIGN KEY (Physician) REFERENCES Physician(EmployeeID), FOREIGN KEY (Patient) REFERENCES Patient(SSN), FOREIGN KEY (Medication) REFERENCES Medication(Code), FOREIGN KEY (Appointment) REFERENCES Appointment(AppointmentID) );")
cur.execute("CREATE TABLE IF NOT EXISTS Block (Floor INTEGER NOT NULL, Code INTEGER NOT NULL, PRIMARY KEY (Floor, Code) );")
cur.execute("CREATE TABLE IF NOT EXISTS Room (Number INTEGER PRIMARY KEY NOT NULL, Type TEXT NOT NULL, BlockFloor INTEGER NOT NULL, BlockCode INTEGER NOT NULL, Unavailable BOOLEAN NOT NULL DEFAULT FALSE, FOREIGN KEY (BlockFloor, BlockCode) REFERENCES Block(Floor, Code));")
cur.execute("CREATE TABLE IF NOT EXISTS On_Call(Nurse INTEGER NOT NULL, BlockFloor INTEGER NOT NULL, BlockCode INTEGER NOT NULL, StartDate DATE NOT NULL, EndDate DATE NOT NULL, PRIMARY KEY (Nurse, BlockFloor, BlockCode, StartDate, EndDate), FOREIGN KEY (BlockFloor, BlockCode) REFERENCES Block(Floor, Code), FOREIGN KEY (Nurse) REFERENCES Nurse(EmployeeID));")
cur.execute("CREATE TABLE IF NOT EXISTS Stay(StayID INTEGER PRIMARY KEY NOT NULL, Patient INTEGER NOT NULL, Room INTEGER NOT NULL, StartDate DATE NOT NULL, EndDate DATE NOT NULL, FOREIGN KEY (Patient) REFERENCES Patient(SSN), FOREIGN KEY (Room) REFERENCES Room(Number));")
cur.execute("CREATE TABLE IF NOT EXISTS Undergoes(Patient INTEGER NOT NULL, Procedure1 INTEGER NOT NULL, Stay INTEGER NOT NULL, Date1 DATE NOT NULL, Physician INTEGER NOT NULL, AssistingNurse INTEGER NOT NULL, PRIMARY KEY (Patient, Procedure1, Stay, Date1), FOREIGN KEY (Physician) REFERENCES Physician(EmployeeID), FOREIGN KEY (Patient) REFERENCES Patient(SSN), FOREIGN KEY (AssistingNurse) REFERENCES Nurse(EmployeeID), FOREIGN KEY (Stay) REFERENCES Stay(StayID), FOREIGN KEY (Procedure1) REFERENCES Procedure(Code) );")
# Deleting all Data Tuples from every table Table
cur.execute("DELETE FROM Undergoes;");
cur.execute("DELETE FROM Stay;");
cur.execute("DELETE FROM On_Call;");
cur.execute("DELETE FROM Room;");
cur.execute("DELETE FROM Block;");
cur.execute("DELETE FROM Prescribes;");
cur.execute("DELETE FROM Medication;");
cur.execute("DELETE FROM Appointment;");
cur.execute("DELETE FROM Trained_In;");
cur.execute("DELETE FROM Affiliated_With;");
cur.execute("DELETE FROM Patient;");
cur.execute("DELETE FROM Physician;");
cur.execute("DELETE FROM Procedure;");
cur.execute("DELETE FROM Department;");
cur.execute("DELETE FROM Nurse;");
#Inserting into Physician table
cur.execute("INSERT INTO Physician VALUES(1,'John Dorian','Staff Internist',111111111);");
cur.execute("INSERT INTO Physician VALUES(2,'Elliot Reid','Attending Physician',222222222);");
cur.execute("INSERT INTO Physician VALUES(3,'Christopher Turk','Surgical Attending Physician',333333333);");
cur.execute("INSERT INTO Physician VALUES(4,'Percival Cox','Senior Attending Physician',444444444);");
cur.execute("INSERT INTO Physician VALUES(5,'Bob Kelso','Head Chief of Medicine',555555555);");
cur.execute("INSERT INTO Physician VALUES(6,'Todd Quinlan','Surgical Attending Physician',666666666);");
cur.execute("INSERT INTO Physician VALUES(7,'John Wen','Surgical Attending Physician',777777777);");
cur.execute("INSERT INTO Physician VALUES(8,'Keith Dudemeister','MD Resident',888888888);");
cur.execute("INSERT INTO Physician VALUES(9,'Molly Clock','Attending Psychiatrist',999999999);");
#Inserting into Department table
cur.execute("INSERT INTO Department VALUES(1,'General Medicine',4);");
cur.execute("INSERT INTO Department VALUES(2,'Surgery',7);");
cur.execute("INSERT INTO Department VALUES(3,'Psychiatry',9);");
cur.execute("INSERT INTO Department VALUES(4,'Cardiology',3);");
#Inserting into Affliated With Table
cur.execute("INSERT INTO Affiliated_With VALUES(true,1,1);");
cur.execute("INSERT INTO Affiliated_With VALUES(true,4,4);");
cur.execute("INSERT INTO Affiliated_With VALUES(false,5,3);");
cur.execute("INSERT INTO Affiliated_With VALUES(true,7,4);");
cur.execute("INSERT INTO Affiliated_With VALUES(true,2,2);");
cur.execute("INSERT INTO Affiliated_With VALUES(false,9,3);");
cur.execute("INSERT INTO Affiliated_With VALUES(true,6,1);");
cur.execute("INSERT INTO Affiliated_With VALUES(true,3,3);");
cur.execute("INSERT INTO Affiliated_With VALUES(true,8,1);");
#Inserting into Procedure Table
cur.execute("INSERT INTO Procedure VALUES(1, 'Reverse Rhinopodoplasty',1500.0);");
cur.execute("INSERT INTO Procedure VALUES(2, 'Obtuse Pyloric Recombustion',8750.0);");
cur.execute("INSERT INTO Procedure VALUES(3, 'Folded Demiopthalmectomy',4500.0);");
cur.execute("INSERT INTO Procedure VALUES(4, 'Complete Wallectomy', 5500.0);");
cur.execute("INSERT INTO Procedure VALUES(5, 'ByPass Surgery', 5899.0);");
cur.execute("INSERT INTO Procedure VALUES(6, 'Reversible PancreaomyPlasty', 1322.40);");
#Inserting into Patient Table
cur.execute("INSERT INTO Patient VALUES(100000001,'Jonhny Smithsonian','42 Foobar Lane','+91 983-555-0256',68476213,1);");
cur.execute("INSERT INTO Patient VALUES(100000002,'Grace Ritchie','37 Snafu Drive','+91 785-551-0512',36546321,6);");
cur.execute("INSERT INTO Patient VALUES(100000003,'Random J. Patient','101 Omgbbq Street','+91 985-552-1204',65465421,5);");
cur.execute("INSERT INTO Patient VALUES(100000004,'Dennis Doe','1100 Foobaz Avenue','+91 895-552-2048',68421879,3);");
#Inserting into Trained In Table
cur.execute("INSERT INTO Trained_In (Treatment, Physician, CertificationDate, CertificationExpires) VALUES(1,1,'2008-01-01 12:00:00','2008-12-31 12:00:00');");
cur.execute("INSERT INTO Trained_In (Treatment, Physician, CertificationDate, CertificationExpires) VALUES(2,3,'2008-01-01 12:00:00','2008-12-31 12:00:00');");
cur.execute("INSERT INTO Trained_In (Treatment, Physician, CertificationDate, CertificationExpires) VALUES(3,3,'2008-01-01 12:00:00','2008-12-31 12:00:00');");
cur.execute("INSERT INTO Trained_In (Treatment, Physician, CertificationDate, CertificationExpires) VALUES(6,3,'2008-01-01 12:00:00','2008-12-31 12:00:00');");
cur.execute("INSERT INTO Trained_In (Treatment, Physician, CertificationDate, CertificationExpires) VALUES(4,4,'2008-01-01 12:00:00','2008-12-31 12:00:00');");
cur.execute("INSERT INTO Trained_In (Treatment, Physician, CertificationDate, CertificationExpires) VALUES(2,2,'2008-01-01 12:00:00','2008-12-31 12:00:00');");
cur.execute("INSERT INTO Trained_In (Treatment, Physician, CertificationDate, CertificationExpires) VALUES(5,6,'2007-01-01 12:00:00','2007-12-31 12:00:00');");
cur.execute("INSERT INTO Trained_In (Treatment, Physician, CertificationDate, CertificationExpires) VALUES(6,4,'2008-01-01 12:00:00','2008-12-31 12:00:00');");
cur.execute("INSERT INTO Trained_In (Treatment, Physician, CertificationDate, CertificationExpires) VALUES(5,7,'2008-01-01 12:00:00','2008-12-31 12:00:00');");
cur.execute("INSERT INTO Trained_In (Treatment, Physician, CertificationDate, CertificationExpires) VALUES(2,8,'2008-01-01 12:00:00','2008-12-31 12:00:00');");
cur.execute("INSERT INTO Trained_In (Treatment, Physician, CertificationDate, CertificationExpires) VALUES(3,9,'2008-01-01 12:00:00','2008-12-31 12:00:00');");
cur.execute("INSERT INTO Trained_In (Treatment, Physician, CertificationDate, CertificationExpires) VALUES(4,5,'2008-01-01 12:00:00','2008-12-31 12:00:00');");
cur.execute("INSERT INTO Trained_In (Treatment, Physician, CertificationDate, CertificationExpires) VALUES(5,4,'2008-01-01 12:00:00','2008-12-31 12:00:00');");
cur.execute("INSERT INTO Trained_In (Treatment, Physician, CertificationDate, CertificationExpires) VALUES(6,6,'2008-01-01 12:00:00','2008-12-31 12:00:00');");
cur.execute("INSERT INTO Trained_In (Treatment, Physician, CertificationDate, CertificationExpires) VALUES(3,4,'2008-01-01 12:00:00','2008-12-31 12:00:00');");
#Inserting into Nurse Table
cur.execute("INSERT INTO Nurse VALUES(101,'Carla Espinosa','Head Nurse',true,111111110);");
cur.execute("INSERT INTO Nurse VALUES(102,'Laverne Roberts','Nurse',true,222222220);");
cur.execute("INSERT INTO Nurse VALUES(103,'Paul Flowers','Nurse',false,333333330);");
#Inserting into Appointment Table
cur.execute("INSERT INTO Appointment VALUES(13216584,100000001,101,4,'2008-04-24 10:00','2008-04-24 11:00','A');");
cur.execute("INSERT INTO Appointment VALUES(26548913,100000002,101,2,'2008-04-24 10:00','2008-04-24 11:00','B');");
cur.execute("INSERT INTO Appointment VALUES(36549879,100000001,102,4,'2008-04-25 10:00','2008-04-25 11:00','A');");
cur.execute("INSERT INTO Appointment VALUES(46846589,100000004,103,4,'2008-04-25 10:00','2008-04-25 11:00','B');");
cur.execute("INSERT INTO Appointment VALUES(59871321,100000004,NULL,4,'2008-04-26 10:00','2008-04-26 11:00','C');");
cur.execute("INSERT INTO Appointment VALUES(69879231,100000003,103,2,'2008-04-26 11:00','2008-04-26 12:00','C');");
cur.execute("INSERT INTO Appointment VALUES(76983231,100000001,NULL,3,'2008-04-26 12:00','2008-04-26 13:00','C');");
cur.execute("INSERT INTO Appointment VALUES(86213939,100000004,102,9,'2008-04-27 10:00','2008-04-21 11:00','A');");
cur.execute("INSERT INTO Appointment VALUES(93216548,100000002,101,2,'2008-04-27 10:00','2008-04-27 11:00','B');");
#Inserting into Medication table
cur.execute("INSERT INTO Medication VALUES(1,'Procrastin-X','X','N/A');");
cur.execute("INSERT INTO Medication VALUES(2,'Remdesivir','Foo Labs','N/A');");
cur.execute("INSERT INTO Medication VALUES(3,'Awakin','Bar Laboratories','N/A');");
cur.execute("INSERT INTO Medication VALUES(4,'Crescavitin','Baz Industries','N/A');");
cur.execute("INSERT INTO Medication VALUES(5,'Melioraurin','Snafu Pharmaceuticals','N/A');");
#Inserting into Prescribe table
cur.execute("INSERT INTO Prescribes VALUES(1,100000001,1,'2008-04-24 10:47',13216584,'5');");
cur.execute("INSERT INTO Prescribes VALUES(8,100000001,2,'2008-04-27 10:53',86213939,'10');");
cur.execute("INSERT INTO Prescribes VALUES(9,100000002,3,'2008-04-30 16:53',NULL,'5');");
cur.execute("INSERT INTO Prescribes VALUES(2,100000003,2,'2008-04-27 10:53',86213939,'10');");
cur.execute("INSERT INTO Prescribes VALUES(3,100000004,2,'2008-04-27 10:53',86213939,'10');");
cur.execute("INSERT INTO Prescribes VALUES(4,100000001,2,'2008-04-27 10:53',86213939,'10');");
#Inserting into Block Table
cur.execute("INSERT INTO Block VALUES(1,1);");
cur.execute("INSERT INTO Block VALUES(1,2);");
cur.execute("INSERT INTO Block VALUES(1,3);");
cur.execute("INSERT INTO Block VALUES(2,1);");
cur.execute("INSERT INTO Block VALUES(2,2);");
cur.execute("INSERT INTO Block VALUES(2,3);");
cur.execute("INSERT INTO Block VALUES(3,1);");
cur.execute("INSERT INTO Block VALUES(3,2);");
cur.execute("INSERT INTO Block VALUES(3,3);");
cur.execute("INSERT INTO Block VALUES(4,1);");
cur.execute("INSERT INTO Block VALUES(4,2);");
cur.execute("INSERT INTO Block VALUES(4,3);");
#Inserting into Room Table
cur.execute("INSERT INTO Room VALUES(101,'Single',1,1,false);");
cur.execute("INSERT INTO Room VALUES(102,'Single',1,1,false);");
cur.execute("INSERT INTO Room VALUES(103,'icu',1,1,false);");
cur.execute("INSERT INTO Room VALUES(111,'Single',1,2,false);");
cur.execute("INSERT INTO Room VALUES(112,'Single',1,2,true);");
cur.execute("INSERT INTO Room VALUES(113,'Single',1,2,false);");
cur.execute("INSERT INTO Room VALUES(121,'Single',1,3,false);");
cur.execute("INSERT INTO Room VALUES(122,'icu',1,3,false);");
cur.execute("INSERT INTO Room VALUES(123,'Single',1,3,false);");
cur.execute("INSERT INTO Room VALUES(201,'Single',2,1,true);");
cur.execute("INSERT INTO Room VALUES(202,'icu',2,1,false);");
cur.execute("INSERT INTO Room VALUES(203,'Single',2,1,false);");
cur.execute("INSERT INTO Room VALUES(211,'Single',2,2,false);");
cur.execute("INSERT INTO Room VALUES(212,'Single',2,2,false);");
cur.execute("INSERT INTO Room VALUES(213,'Single',2,2,true);");
cur.execute("INSERT INTO Room VALUES(221,'Single',2,3,false);");
cur.execute("INSERT INTO Room VALUES(222,'Single',2,3,false);");
cur.execute("INSERT INTO Room VALUES(223,'Single',2,3,false);");
cur.execute("INSERT INTO Room VALUES(301,'Single',3,1,false);");
cur.execute("INSERT INTO Room VALUES(302,'Single',3,1,true);");
cur.execute("INSERT INTO Room VALUES(303,'Single',3,1,false);");
cur.execute("INSERT INTO Room VALUES(311,'icu',3,2,false);");
cur.execute("INSERT INTO Room VALUES(312,'Single',3,2,false);");
cur.execute("INSERT INTO Room VALUES(313,'Single',3,2,false);");
cur.execute("INSERT INTO Room VALUES(321,'Single',3,3,true);");
cur.execute("INSERT INTO Room VALUES(322,'Single',3,3,false);");
cur.execute("INSERT INTO Room VALUES(323,'Single',3,3,false);");
cur.execute("INSERT INTO Room VALUES(401,'icu',4,1,false);");
cur.execute("INSERT INTO Room VALUES(402,'Single',4,1,true);");
cur.execute("INSERT INTO Room VALUES(403,'Single',4,1,false);");
cur.execute("INSERT INTO Room VALUES(411,'icu',4,2,false);");
cur.execute("INSERT INTO Room VALUES(412,'Single',4,2,false);");
cur.execute("INSERT INTO Room VALUES(413,'Single',4,2,false);");
cur.execute("INSERT INTO Room VALUES(421,'Single',4,3,true);");
cur.execute("INSERT INTO Room VALUES(422,'Single',4,3,false);");
cur.execute("INSERT INTO Room VALUES(423,'Single',4,3,false);");
#Inserting into On_Call Table
cur.execute("INSERT INTO On_Call VALUES(101,1,1,'2008-11-04 11:00','2008-11-04 19:00');");
cur.execute("INSERT INTO On_Call VALUES(101,1,2,'2008-11-04 11:00','2008-11-04 19:00');");
cur.execute("INSERT INTO On_Call VALUES(102,1,3,'2008-11-04 11:00','2008-11-04 19:00');");
cur.execute("INSERT INTO On_Call VALUES(103,1,1,'2008-11-04 19:00','2008-11-05 03:00');");
cur.execute("INSERT INTO On_Call VALUES(103,1,2,'2008-11-04 19:00','2008-11-05 03:00');");
cur.execute("INSERT INTO On_Call VALUES(103,1,3,'2008-11-04 19:00','2008-11-05 03:00');");
#Inserting into Stay Table
cur.execute("INSERT INTO Stay VALUES(3215,100000001,111,'2008-05-01','2008-05-04');");
cur.execute("INSERT INTO Stay VALUES(3216,100000003,123,'2008-05-03','2008-05-14');");
cur.execute("INSERT INTO Stay VALUES(3217,100000004,112,'2008-05-02','2008-05-03');");
#Inserting into Undergoes Table
cur.execute("INSERT INTO Undergoes VALUES(100000001,6,3215,'2008-05-02',3,101);");
cur.execute("INSERT INTO Undergoes VALUES(100000001,2,3215,'2008-05-03',7,101);");
cur.execute("INSERT INTO Undergoes VALUES(100000004,1,3217,'2008-05-07',3,102);");
cur.execute("INSERT INTO Undergoes VALUES(100000004,5,3217,'2008-05-09',6,102);");
cur.execute("INSERT INTO Undergoes VALUES(100000001,3,3217,'2008-05-10',7,101);");
cur.execute("INSERT INTO Undergoes VALUES(100000004,4,3217,'2008-05-13',3,103);");

conn.commit()
cur.close()
conn.close()