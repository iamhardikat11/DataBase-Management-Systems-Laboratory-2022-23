CREATE DATABASE IF NOT EXISTS db_name;
CREATE TABLE IF NOT EXISTS db_name.Physician (
    EmployeeID INTEGER PRIMARY KEY NOT NULL,
    Name TEXT NOT NULL,
    Position TEXT NOT NULL,
    SSN INTEGER NOT NULL
);
CREATE TABLE IF NOT EXISTS db_name.Department(
    DepartmentID INTEGER PRIMARY KEY NOT NULL,
    Name TEXT NOT NULL,
    Head INTEGER NOT NULL
);
CREATE TABLE IF NOT EXISTS db_name.Affiliated_With (
  PrimaryAffiliation BOOLEAN NOT NULL DEFAULT false,
  Physician INTEGER NOT NULL,
  Department INTEGER NOT NULL,
  PRIMARY KEY (Department, Physician),
  FOREIGN KEY (Department) REFERENCES db_name.Department(DepartmentID),
  FOREIGN KEY (Physician) REFERENCES db_name.Physician(EmployeeID)
);
CREATE TABLE IF NOT EXISTS db_name.Procedure(
    Code INTEGER PRIMARY KEY NOT NULL,
    Name TEXT NOT NULL,
    Cost INTEGER NOT NULL
);
CREATE TABLE IF NOT EXISTS db_name.Trained_In(
    Physician INTEGER NOT NULL,
    Treatment INTEGER NOT NULL,
    CertificationDate DATETIME NOT NULL,
    CertificationExpires DATETIME NOT NULL,
    PRIMARY KEY(Physician, Treatment),
    FOREIGN KEY (Physician) REFERENCES db_name.Physician(EmployeeID),
    FOREIGN KEY (Treatment) REFERENCES db_name.Procedure(Code)
);

CREATE TABLE IF NOT EXISTS db_name.Patient(
    SSN INTEGER PRIMARY KEY NOT NULL,
    Name TEXT NOT NULL,
    Address TEXT NOT NULL,
    Phone TEXT NOT NULL,
    InsuranceID INTEGER NOT NULL,
    PCP INTEGER NOT NULL,
    FOREIGN KEY (PCP) REFERENCES db_name.Physician(EmployeeID)
);

CREATE TABLE IF NOT EXISTS db_name.Nurse(
    EmployeeID INTEGER PRIMARY KEY NOT NULL,
    Name TEXT NOT NULL,
    Position TEXT NOT NULL,
    Registered BOOLEAN NOT NULL DEFAULT FALSE,
    SSN INTEGER NOT NULL
);

CREATE TABLE IF NOT EXISTS db_name.Appointment(
    AppointmentID INTEGER PRIMARY KEY NOT NULL,
    Patient INTEGER NOT NULL,
    PrepNurse INTEGER,
    Physician INTEGER NOT NULL,
    Start DATETIME NOT NULL,
    End DATETIME NOT NULL,
    ExaminationRoom TEXT NOT NULL,
    FOREIGN KEY (Patient) REFERENCES db_name.Patient(SSN),
    FOREIGN KEY (PrepNurse) REFERENCES db_name.Nurse(EmployeeID),
    FOREIGN KEY (Physician) REFERENCES db_name.Physician(EmployeeID)
);

CREATE TABLE IF NOT EXISTS db_name.Medication(
    Code INTEGER PRIMARY KEY NOT NULL,
    Name TEXT NOT NULL,
    Brand TEXT NOT NULL,
    Description TEXT NOT NULL
);

CREATE TABLE IF NOT EXISTS db_name.Prescribes(
    Physician INTEGER NOT NULL,
    Patient INTEGER NOT NULL,
    Medication INTEGER NOT NULL,
    Date DATETIME NOT NULL,
    Appointment INTEGER, 
    Dose TEXT NOT NULL,
    PRIMARY KEY (Physician, Patient, Medication, Date),
    FOREIGN KEY (Physician) REFERENCES db_name.Physician(EmployeeID),
    FOREIGN KEY (Patient) REFERENCES db_name.Patient(SSN),
    FOREIGN KEY (Medication) REFERENCES db_name.Medication(Code),
    FOREIGN KEY (Appointment) REFERENCES db_name.Appointment(AppointmentID)
);

CREATE TABLE IF NOT EXISTS db_name.Block(
    Floor INTEGER NOT NULL,
    Code INTEGER NOT NULL,
    PRIMARY KEY (Code, Floor)
);

ALTER TABLE db_name.Block ADD INDEX (Floor, Code);

CREATE TABLE IF NOT EXISTS db_name.Room(
    Number INTEGER PRIMARY KEY NOT NULL,
    Type TEXT NOT NULL,
    BlockFloor INTEGER NOT NULL,
    BlockCode INTEGER NOT NULL,
    Unavailable BOOLEAN NOT NULL DEFAULT FALSE,
    FOREIGN KEY (BlockFloor) REFERENCES db_name.Block(Floor),
    FOREIGN KEY (BlockCode) REFERENCES db_name.Block(Code)
);


/*
CREATE TABLE On_Call
CREATE TABLE Stay
CREATE TABLE Undergoes
DELETE FROM db_name.Medication;
*/

DELETE FROM db_name.Room;
DELETE FROM db_name.Block;
DELETE FROM db_name.Prescribes;
DELETE FROM db_name.Medication;
DELETE FROM db_name.Appointment;
DELETE FROM db_name.Trained_In;
DELETE FROM db_name.Affiliated_With;
DELETE FROM db_name.Patient;
DELETE FROM db_name.Physician;
DELETE FROM db_name.Procedure;
DELETE FROM db_name.Department;
DELETE FROM db_name.Nurse;

INSERT INTO db_name.Physician VALUES(1,'John Dorian','Staff Internist',111111111);
INSERT INTO db_name.Physician VALUES(2,'Elliot Reid','Attending Physician',222222222);
INSERT INTO db_name.Physician VALUES(3,'Christopher Turk','Surgical Attending Physician',333333333);
INSERT INTO db_name.Physician VALUES(4,'Percival Cox','Senior Attending Physician',444444444);
INSERT INTO db_name.Physician VALUES(5,'Bob Kelso','Head Chief of Medicine',555555555);
INSERT INTO db_name.Physician VALUES(6,'Todd Quinlan','Surgical Attending Physician',666666666);
INSERT INTO db_name.Physician VALUES(7,'John Wen','Surgical Attending Physician',777777777);
INSERT INTO db_name.Physician VALUES(8,'Keith Dudemeister','MD Resident',888888888);
INSERT INTO db_name.Physician VALUES(9,'Molly Clock','Attending Psychiatrist',999999999);

INSERT INTO db_name.Department VALUES(1,'General Medicine',4);
INSERT INTO db_name.Department VALUES(2,'Surgery',7);
INSERT INTO db_name.Department VALUES(3,'Psychiatry',9);

INSERT INTO db_name.Affiliated_With VALUES(1,1,1);
INSERT INTO db_name.Affiliated_With VALUES(1,4,2);
INSERT INTO db_name.Affiliated_With VALUES(0,5,3);
INSERT INTO db_name.Affiliated_With VALUES(1,7,1);
INSERT INTO db_name.Affiliated_With VALUES(1,2,2);
INSERT INTO db_name.Affiliated_With VALUES(0,9,3);
INSERT INTO db_name.Affiliated_With VALUES(1,6,1);
INSERT INTO db_name.Affiliated_With VALUES(1,3,3);
INSERT INTO db_name.Affiliated_With VALUES(1,8,1);

INSERT INTO db_name.Procedure VALUES(1, 'Reverse Rhinopodoplasty',1500.0);
INSERT INTO db_name.Procedure VALUES(2, 'Obtuse Pyloric Recombustion',3750.0);
INSERT INTO db_name.Procedure VALUES(3, 'Folded Demiopthalmectomy',4500.0);
INSERT INTO db_name.Procedure VALUES(4, 'Complete Wallectomy', 4500.0);
INSERT INTO db_name.Procedure VALUES(5, 'Obfuscated Dermogastrotomy', 4899.0);
INSERT INTO db_name.Procedure VALUES(6, 'Reversible PancreaomyPlasty', 1322.40);

INSERT INTO db_name.Patient (SSN, Name, Address, Phone, InsuranceID, PCP) VALUES(100000001,'Jonhny Smithsonian','42 Foobar Lane','+91 983-555-0256',68476213,1);
INSERT INTO db_name.Patient (SSN, Name, Address, Phone, InsuranceID, PCP) VALUES(100000002,'Grace Ritchie','37 Snafu Drive','+91 785-551-0512',36546321,6);
INSERT INTO db_name.Patient (SSN, Name, Address, Phone, InsuranceID, PCP) VALUES(100000003,'Random J. Patient','101 Omgbbq Street','+91 985-552-1204',65465421,5);
INSERT INTO db_name.Patient (SSN, Name, Address, Phone, InsuranceID, PCP) VALUES(100000004,'Dennis Doe','1100 Foobaz Avenue','+91 895-552-2048',68421879,3);

INSERT INTO db_name.Trained_In (Treatment, Physician, CertificationDate, CertificationExpires)  VALUES(1,3,'2008-01-01 12:00:00','2008-12-31 12:00:00');
INSERT INTO db_name.Trained_In (Treatment, Physician, CertificationDate, CertificationExpires)  VALUES(2,3,'2008-01-01 12:00:00','2008-12-31 12:00:00');
INSERT INTO db_name.Trained_In (Treatment, Physician, CertificationDate, CertificationExpires)  VALUES(5,3,'2008-01-01 12:00:00','2008-12-31 12:00:00');
INSERT INTO db_name.Trained_In (Treatment, Physician, CertificationDate, CertificationExpires)  VALUES(6,3,'2008-01-01 12:00:00','2008-12-31 12:00:00');
INSERT INTO db_name.Trained_In (Treatment, Physician, CertificationDate, CertificationExpires)  VALUES(4,3,'2008-01-01 12:00:00','2008-12-31 12:00:00');
INSERT INTO db_name.Trained_In (Treatment, Physician, CertificationDate, CertificationExpires)  VALUES(2,6,'2008-01-01 12:00:00','2008-12-31 12:00:00');
INSERT INTO db_name.Trained_In (Treatment, Physician, CertificationDate, CertificationExpires)  VALUES(5,6,'2007-01-01 12:00:00','2007-12-31 12:00:00');
INSERT INTO db_name.Trained_In (Treatment, Physician, CertificationDate, CertificationExpires)  VALUES(6,6,'2008-01-01 12:00:00','2008-12-31 12:00:00');
INSERT INTO db_name.Trained_In (Treatment, Physician, CertificationDate, CertificationExpires)  VALUES(1,7,'2008-01-01 12:00:00','2008-12-31 12:00:00');
INSERT INTO db_name.Trained_In (Treatment, Physician, CertificationDate, CertificationExpires)  VALUES(2,8,'2008-01-01 12:00:00','2008-12-31 12:00:00');
INSERT INTO db_name.Trained_In (Treatment, Physician, CertificationDate, CertificationExpires)  VALUES(3,9,'2008-01-01 12:00:00','2008-12-31 12:00:00');
INSERT INTO db_name.Trained_In (Treatment, Physician, CertificationDate, CertificationExpires)  VALUES(4,5,'2008-01-01 12:00:00','2008-12-31 12:00:00');
INSERT INTO db_name.Trained_In (Treatment, Physician, CertificationDate, CertificationExpires)  VALUES(5,4,'2008-01-01 12:00:00','2008-12-31 12:00:00');
INSERT INTO db_name.Trained_In (Treatment, Physician, CertificationDate, CertificationExpires)  VALUES(6,1,'2008-01-01 12:00:00','2008-12-31 12:00:00');
INSERT INTO db_name.Trained_In (Treatment, Physician, CertificationDate, CertificationExpires)  VALUES(3,4,'2008-01-01 12:00:00','2008-12-31 12:00:00');

INSERT INTO db_name.Nurse VALUES(101,'Carla Espinosa','Head Nurse',1,111111110);
INSERT INTO db_name.Nurse VALUES(102,'Laverne Roberts','Nurse',1,222222220);
INSERT INTO db_name.Nurse VALUES(103,'Paul Flowers','Nurse',0,333333330);

INSERT INTO db_name.Appointment VALUES(13216584,100000001,101,1,'2008-04-24 10:00','2008-04-24 11:00','A');
INSERT INTO db_name.Appointment VALUES(26548913,100000002,101,2,'2008-04-24 10:00','2008-04-24 11:00','B');
INSERT INTO db_name.Appointment VALUES(36549879,100000001,102,1,'2008-04-25 10:00','2008-04-25 11:00','A');
INSERT INTO db_name.Appointment VALUES(46846589,100000004,103,4,'2008-04-25 10:00','2008-04-25 11:00','B');
INSERT INTO db_name.Appointment VALUES(59871321,100000004,NULL,4,'2008-04-26 10:00','2008-04-26 11:00','C');
INSERT INTO db_name.Appointment VALUES(69879231,100000003,103,2,'2008-04-26 11:00','2008-04-26 12:00','C');
INSERT INTO db_name.Appointment VALUES(76983231,100000001,NULL,3,'2008-04-26 12:00','2008-04-26 13:00','C');
INSERT INTO db_name.Appointment VALUES(86213939,100000004,102,9,'2008-04-27 10:00','2008-04-21 11:00','A');
INSERT INTO db_name.Appointment VALUES(93216548,100000002,101,2,'2008-04-27 10:00','2008-04-27 11:00','B');

INSERT INTO db_name.Medication VALUES(1,'Procrastin-X','X','N/A');
INSERT INTO db_name.Medication VALUES(2,'Thesisin','Foo Labs','N/A');
INSERT INTO db_name.Medication VALUES(3,'Awakin','Bar Laboratories','N/A');
INSERT INTO db_name.Medication VALUES(4,'Crescavitin','Baz Industries','N/A');
INSERT INTO db_name.Medication VALUES(5,'Melioraurin','Snafu Pharmaceuticals','N/A');

INSERT INTO db_name.Prescribes VALUES(1,100000001,1,'2008-04-24 10:47',13216584,'5');
INSERT INTO db_name.Prescribes VALUES(8,100000004,2,'2008-04-27 10:53',86213939,'10');
INSERT INTO db_name.Prescribes VALUES(9,100000004,3,'2008-04-30 16:53',NULL,'5');


INSERT INTO db_name.Block VALUES(1,1);
INSERT INTO db_name.Block VALUES(1,2);
INSERT INTO db_name.Block VALUES(1,3);
INSERT INTO db_name.Block VALUES(2,1);
INSERT INTO db_name.Block VALUES(2,2);
INSERT INTO db_name.Block VALUES(2,3);
INSERT INTO db_name.Block VALUES(3,1);
INSERT INTO db_name.Block VALUES(3,2);
INSERT INTO db_name.Block VALUES(3,3);
INSERT INTO db_name.Block VALUES(4,1);
INSERT INTO db_name.Block VALUES(4,2);
INSERT INTO db_name.Block VALUES(4,3);
