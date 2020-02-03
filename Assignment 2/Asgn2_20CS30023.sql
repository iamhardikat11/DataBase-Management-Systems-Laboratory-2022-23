/*
    Name:- Hardik Pravin Soni
    Roll No:- 20CS30023
    Subject:- Database Management System Labortary 2023 (CS39202)
    Assignment 3
*/
CREATE DATABASE IF NOT EXISTS 20CS30023;
CREATE TABLE IF NOT EXISTS 20CS30023.Physician (
    EmployeeID INTEGER PRIMARY KEY NOT NULL,
    `Name` TEXT NOT NULL,
    Position TEXT NOT NULL,
    SSN INTEGER NOT NULL
);
CREATE TABLE IF NOT EXISTS 20CS30023.Department(
    DepartmentID INTEGER PRIMARY KEY NOT NULL,
    `Name` TEXT NOT NULL,
    Head INTEGER NOT NULL
);
CREATE TABLE IF NOT EXISTS 20CS30023.Affiliated_With (
  PrimaryAffiliation BOOLEAN NOT NULL DEFAULT false,
  Physician INTEGER NOT NULL,
  Department INTEGER NOT NULL,
  PRIMARY KEY (Department, Physician),
  FOREIGN KEY (Department) REFERENCES 20CS30023.Department(DepartmentID),
  FOREIGN KEY (Physician) REFERENCES 20CS30023.Physician(EmployeeID)
);
CREATE TABLE IF NOT EXISTS 20CS30023.Procedure(
    Code INTEGER PRIMARY KEY NOT NULL,
    `Name` TEXT NOT NULL,
    Cost INTEGER NOT NULL
);
CREATE TABLE IF NOT EXISTS 20CS30023.Trained_In(
    Physician INTEGER NOT NULL,
    Treatment INTEGER NOT NULL,
    CertificationDate DATETIME NOT NULL,
    CertificationExpires DATETIME NOT NULL,
    PRIMARY KEY(Physician, Treatment),
    FOREIGN KEY (Physician) REFERENCES 20CS30023.Physician(EmployeeID),
    FOREIGN KEY (Treatment) REFERENCES 20CS30023.Procedure(Code)
);

CREATE TABLE IF NOT EXISTS 20CS30023.Patient(
    SSN INTEGER PRIMARY KEY NOT NULL,
    `Name` TEXT NOT NULL,
    `Address` TEXT NOT NULL,
    Phone TEXT NOT NULL,
    InsuranceID INTEGER NOT NULL,
    PCP INTEGER NOT NULL,
    FOREIGN KEY (PCP) REFERENCES 20CS30023.Physician(EmployeeID)
);

CREATE TABLE IF NOT EXISTS 20CS30023.Nurse(
    EmployeeID INTEGER PRIMARY KEY NOT NULL,
    `Name` TEXT NOT NULL,
    Position TEXT NOT NULL,
    Registered BOOLEAN NOT NULL DEFAULT FALSE,
    SSN INTEGER NOT NULL
);
CREATE TABLE IF NOT EXISTS 20CS30023.Appointment(
    AppointmentID INTEGER PRIMARY KEY NOT NULL,
    Patient INTEGER NOT NULL,
    PrepNurse INTEGER,
    Physician INTEGER NOT NULL,
    `Start` DATETIME NOT NULL,
    `End` DATETIME NOT NULL,
    ExaminationRoom TEXT NOT NULL,
    FOREIGN KEY (Patient) REFERENCES 20CS30023.Patient(SSN),
    FOREIGN KEY (PrepNurse) REFERENCES 20CS30023.Nurse(EmployeeID),
    FOREIGN KEY (Physician) REFERENCES 20CS30023.Physician(EmployeeID)
);
CREATE TABLE IF NOT EXISTS 20CS30023.Medication(
    Code INTEGER PRIMARY KEY NOT NULL,
    `Name` TEXT NOT NULL,
    Brand TEXT NOT NULL,
    `Description` TEXT NOT NULL
);
CREATE TABLE IF NOT EXISTS 20CS30023.Prescribes(
    Physician INTEGER NOT NULL,
    Patient INTEGER NOT NULL,
    Medication INTEGER NOT NULL,
    `Date` DATETIME NOT NULL,
    Appointment INTEGER, 
    Dose TEXT NOT NULL,
    PRIMARY KEY (Physician, Patient, Medication, Date),
    FOREIGN KEY (Physician) REFERENCES 20CS30023.Physician(EmployeeID),
    FOREIGN KEY (Patient) REFERENCES 20CS30023.Patient(SSN),
    FOREIGN KEY (Medication) REFERENCES 20CS30023.Medication(Code),
    FOREIGN KEY (Appointment) REFERENCES 20CS30023.Appointment(AppointmentID)
);
CREATE TABLE IF NOT EXISTS 20CS30023.Block(
    Floor INTEGER NOT NULL,
    Code INTEGER NOT NULL,
    PRIMARY KEY (Code, Floor)
);  
ALTER TABLE 20CS30023.Block ADD INDEX (Floor, Code);
CREATE TABLE IF NOT EXISTS 20CS30023.Room(
    `Number` INTEGER PRIMARY KEY NOT NULL,
    `Type` TEXT NOT NULL,
    BlockFloor INTEGER NOT NULL,
    BlockCode INTEGER NOT NULL,
    Unavailable BOOLEAN NOT NULL DEFAULT FALSE,
    FOREIGN KEY (BlockFloor) REFERENCES 20CS30023.Block(Floor),
    FOREIGN KEY (BlockCode) REFERENCES 20CS30023.Block(Code)
);
CREATE TABLE IF NOT EXISTS 20CS30023.On_Call(
    Nurse INTEGER NOT NULL,
    BlockFloor INTEGER NOT NULL,
    BlockCode INTEGER NOT NULL,
    `Start` DATETIME NOT NULL,
    `End` DATETIME NOT NULL,
    PRIMARY KEY (Nurse, BlockCode, BlockFloor, Start, End),
    FOREIGN KEY (BlockFloor) REFERENCES 20CS30023.Block(Floor),
    FOREIGN KEY (BlockCode) REFERENCES 20CS30023.Block(Code),
    FOREIGN KEY (Nurse) REFERENCES 20CS30023.Nurse(EmployeeID)
);
CREATE TABLE IF NOT EXISTS 20CS30023.Stay(
    StayID INTEGER PRIMARY KEY NOT NULL,
    Patient INTEGER NOT NULL,
    Room INTEGER NOT NULL,
    `Start` DATETIME NOT NULL,
    `End` DATETIME NOT NULL,
    FOREIGN KEY (Patient) REFERENCES 20CS30023.Patient(SSN),
    FOREIGN KEY (Room) REFERENCES 20CS30023.Room(Number)
);
CREATE TABLE IF NOT EXISTS 20CS30023.Undergoes(
    Patient INTEGER NOT NULL,
    `Procedure` INTEGER NOT NULL,
    Stay INTEGER NOT NULL,
    `Date` DATETIME NOT NULL,
    Physician INTEGER NOT NULL,
    AssistingNurse INTEGER,
    PRIMARY KEY (Patient, `Procedure`, Stay, `Date`),
    FOREIGN KEY (Patient) REFERENCES 20CS30023.Patient(SSN),
    FOREIGN KEY (`Procedure`) REFERENCES 20CS30023.Procedure(Code),
    FOREIGN KEY (Stay) REFERENCES 20CS30023.Stay(StayID),
    FOREIGN KEY (Physician) REFERENCES 20CS30023.Physician(EmployeeID),
    FOREIGN KEY (AssistingNurse) REFERENCES 20CS30023.Nurse(EmployeeID)
);

DELETE FROM 20CS30023.Undergoes;
DELETE FROM 20CS30023.Stay;
DELETE FROM 20CS30023.On_Call;
DELETE FROM 20CS30023.Room;
DELETE FROM 20CS30023.Block;
DELETE FROM 20CS30023.Prescribes;
DELETE FROM 20CS30023.Medication;
DELETE FROM 20CS30023.Appointment;
DELETE FROM 20CS30023.Trained_In;
DELETE FROM 20CS30023.Affiliated_With;
DELETE FROM 20CS30023.Patient;
DELETE FROM 20CS30023.Physician;
DELETE FROM 20CS30023.Procedure;
DELETE FROM 20CS30023.Department;
DELETE FROM 20CS30023.Nurse;

INSERT INTO 20CS30023.Physician VALUES(1,'John Dorian','Staff Internist',111111111);
INSERT INTO 20CS30023.Physician VALUES(2,'Elliot Reid','Attending Physician',222222222);
INSERT INTO 20CS30023.Physician VALUES(3,'Christopher Turk','Surgical Attending Physician',333333333);
INSERT INTO 20CS30023.Physician VALUES(4,'Percival Cox','Senior Attending Physician',444444444);
INSERT INTO 20CS30023.Physician VALUES(5,'Bob Kelso','Head Chief of Medicine',555555555);
INSERT INTO 20CS30023.Physician VALUES(6,'Todd Quinlan','Surgical Attending Physician',666666666);
INSERT INTO 20CS30023.Physician VALUES(7,'John Wen','Surgical Attending Physician',777777777);
INSERT INTO 20CS30023.Physician VALUES(8,'Keith Dudemeister','MD Resident',888888888);
INSERT INTO 20CS30023.Physician VALUES(9,'Molly Clock','Attending Psychiatrist',999999999);

INSERT INTO 20CS30023.Department VALUES(1,'General Medicine',4);
INSERT INTO 20CS30023.Department VALUES(2,'Surgery',7);
INSERT INTO 20CS30023.Department VALUES(3,'Psychiatry',9);
INSERT INTO 20CS30023.Department VALUES(4,'Cardiology',3);

INSERT INTO 20CS30023.Affiliated_With VALUES(1,1,1);
INSERT INTO 20CS30023.Affiliated_With VALUES(1,4,4);
INSERT INTO 20CS30023.Affiliated_With VALUES(0,5,3);
INSERT INTO 20CS30023.Affiliated_With VALUES(1,7,4);
INSERT INTO 20CS30023.Affiliated_With VALUES(1,2,2);
INSERT INTO 20CS30023.Affiliated_With VALUES(0,9,3);
INSERT INTO 20CS30023.Affiliated_With VALUES(1,6,1);
INSERT INTO 20CS30023.Affiliated_With VALUES(1,3,3);
INSERT INTO 20CS30023.Affiliated_With VALUES(1,8,1);

INSERT INTO 20CS30023.Procedure VALUES(1, 'Reverse Rhinopodoplasty',1500.0);
INSERT INTO 20CS30023.Procedure VALUES(2, 'Obtuse Pyloric Recombustion',8750.0);
INSERT INTO 20CS30023.Procedure VALUES(3, 'Folded Demiopthalmectomy',4500.0);
INSERT INTO 20CS30023.Procedure VALUES(4, 'Complete Wallectomy', 5500.0);
INSERT INTO 20CS30023.Procedure VALUES(5, 'ByPass Surgery', 5899.0);
INSERT INTO 20CS30023.Procedure VALUES(6, 'Reversible PancreaomyPlasty', 1322.40);

INSERT INTO 20CS30023.Patient (SSN, Name, Address, Phone, InsuranceID, PCP) VALUES(100000001,'Jonhny Smithsonian','42 Foobar Lane','+91 983-555-0256',68476213,1);
INSERT INTO 20CS30023.Patient (SSN, Name, Address, Phone, InsuranceID, PCP) VALUES(100000002,'Grace Ritchie','37 Snafu Drive','+91 785-551-0512',36546321,6);
INSERT INTO 20CS30023.Patient (SSN, Name, Address, Phone, InsuranceID, PCP) VALUES(100000003,'Random J. Patient','101 Omgbbq Street','+91 985-552-1204',65465421,5);
INSERT INTO 20CS30023.Patient (SSN, Name, Address, Phone, InsuranceID, PCP) VALUES(100000004,'Dennis Doe','1100 Foobaz Avenue','+91 895-552-2048',68421879,3);

INSERT INTO 20CS30023.Trained_In (Treatment, Physician, CertificationDate, CertificationExpires)  VALUES(1,1,'2022-01-01 12:00:00','2022-12-31 12:00:00');
INSERT INTO 20CS30023.Trained_In (Treatment, Physician, CertificationDate, CertificationExpires)  VALUES(2,3,'2022-01-01 12:00:00','2022-12-31 12:00:00');
INSERT INTO 20CS30023.Trained_In (Treatment, Physician, CertificationDate, CertificationExpires)  VALUES(3,3,'2022-01-01 12:00:00','2022-12-31 12:00:00');
INSERT INTO 20CS30023.Trained_In (Treatment, Physician, CertificationDate, CertificationExpires)  VALUES(6,3,'2022-01-01 12:00:00','2022-12-31 12:00:00');
INSERT INTO 20CS30023.Trained_In (Treatment, Physician, CertificationDate, CertificationExpires)  VALUES(4,4,'2022-01-01 12:00:00','2022-12-31 12:00:00');
INSERT INTO 20CS30023.Trained_In (Treatment, Physician, CertificationDate, CertificationExpires)  VALUES(2,2,'2022-01-01 12:00:00','2022-12-31 12:00:00');
INSERT INTO 20CS30023.Trained_In (Treatment, Physician, CertificationDate, CertificationExpires)  VALUES(5,6,'2023-01-01 12:00:00','2023-12-31 12:00:00');
INSERT INTO 20CS30023.Trained_In (Treatment, Physician, CertificationDate, CertificationExpires)  VALUES(6,4,'2022-01-01 12:00:00','2022-12-31 12:00:00');
INSERT INTO 20CS30023.Trained_In (Treatment, Physician, CertificationDate, CertificationExpires)  VALUES(5,7,'2022-01-01 12:00:00','2022-12-31 12:00:00');
INSERT INTO 20CS30023.Trained_In (Treatment, Physician, CertificationDate, CertificationExpires)  VALUES(2,8,'2022-01-01 12:00:00','2022-12-31 12:00:00');
INSERT INTO 20CS30023.Trained_In (Treatment, Physician, CertificationDate, CertificationExpires)  VALUES(3,9,'2022-01-01 12:00:00','2022-12-31 12:00:00');
INSERT INTO 20CS30023.Trained_In (Treatment, Physician, CertificationDate, CertificationExpires)  VALUES(4,5,'2022-01-01 12:00:00','2022-12-31 12:00:00');
INSERT INTO 20CS30023.Trained_In (Treatment, Physician, CertificationDate, CertificationExpires)  VALUES(5,4,'2022-01-01 12:00:00','2022-12-31 12:00:00');
INSERT INTO 20CS30023.Trained_In (Treatment, Physician, CertificationDate, CertificationExpires)  VALUES(6,6,'2022-01-01 12:00:00','2022-12-31 12:00:00');
INSERT INTO 20CS30023.Trained_In (Treatment, Physician, CertificationDate, CertificationExpires)  VALUES(3,4,'2022-01-01 12:00:00','2022-12-31 12:00:00');

INSERT INTO 20CS30023.Nurse VALUES(101,'Carla Espinosa','Head Nurse',1,111111110);
INSERT INTO 20CS30023.Nurse VALUES(102,'Laverne Roberts','Nurse',1,222222220);
INSERT INTO 20CS30023.Nurse VALUES(103,'Paul Flowers','Nurse',0,333333330);

INSERT INTO 20CS30023.Appointment VALUES(13216584,100000001,101,4,'2022-04-24 10:00','2022-04-24 11:00','A');
INSERT INTO 20CS30023.Appointment VALUES(26548913,100000002,101,2,'2022-04-24 10:00','2022-04-24 11:00','B');
INSERT INTO 20CS30023.Appointment VALUES(36549879,100000001,102,4,'2022-04-25 10:00','2022-04-25 11:00','A');
INSERT INTO 20CS30023.Appointment VALUES(46846589,100000004,103,4,'2022-04-25 10:00','2022-04-25 11:00','B');
INSERT INTO 20CS30023.Appointment VALUES(59871321,100000004,NULL,4,'2022-04-26 10:00','2022-04-26 11:00','C');
INSERT INTO 20CS30023.Appointment VALUES(69879231,100000003,103,2,'2022-04-26 11:00','2022-04-26 12:00','C');
INSERT INTO 20CS30023.Appointment VALUES(76983231,100000001,NULL,3,'2022-04-26 12:00','2022-04-26 13:00','C');
INSERT INTO 20CS30023.Appointment VALUES(86213939,100000004,102,9,'2022-04-27 10:00','2022-04-21 11:00','A');
INSERT INTO 20CS30023.Appointment VALUES(93216548,100000002,101,2,'2022-04-27 10:00','2022-04-27 11:00','B');

INSERT INTO 20CS30023.Medication VALUES(1,'Procrastin-X','X','N/A');
INSERT INTO 20CS30023.Medication VALUES(2,'Remdesivir','Foo Labs','N/A');
INSERT INTO 20CS30023.Medication VALUES(3,'Awakin','Bar Laboratories','N/A');
INSERT INTO 20CS30023.Medication VALUES(4,'Crescavitin','Baz Industries','N/A');
INSERT INTO 20CS30023.Medication VALUES(5,'Melioraurin','Snafu Pharmaceuticals','N/A');

INSERT INTO 20CS30023.Prescribes VALUES(1,100000001,1,'2022-04-24 10:47',13216584,'5');
INSERT INTO 20CS30023.Prescribes VALUES(8,100000001,2,'2022-04-27 10:53',86213939,'10');
INSERT INTO 20CS30023.Prescribes VALUES(9,100000002,3,'2022-04-30 16:53',NULL,'5');
INSERT INTO 20CS30023.Prescribes VALUES(2,100000003,2,'2022-04-27 10:53',86213939,'10');
INSERT INTO 20CS30023.Prescribes VALUES(3,100000004,2,'2022-04-27 10:53',86213939,'10');
INSERT INTO 20CS30023.Prescribes VALUES(4,100000001,2,'2022-04-27 10:53',86213939,'10');

INSERT INTO 20CS30023.Block VALUES(1,1);
INSERT INTO 20CS30023.Block VALUES(1,2);
INSERT INTO 20CS30023.Block VALUES(1,3);
INSERT INTO 20CS30023.Block VALUES(2,1);
INSERT INTO 20CS30023.Block VALUES(2,2);
INSERT INTO 20CS30023.Block VALUES(2,3);
INSERT INTO 20CS30023.Block VALUES(3,1);
INSERT INTO 20CS30023.Block VALUES(3,2);
INSERT INTO 20CS30023.Block VALUES(3,3);
INSERT INTO 20CS30023.Block VALUES(4,1);
INSERT INTO 20CS30023.Block VALUES(4,2);
INSERT INTO 20CS30023.Block VALUES(4,3);

INSERT INTO 20CS30023.Room VALUES(101,'Single',1,1,0);
INSERT INTO 20CS30023.Room VALUES(102,'Single',1,1,0);
INSERT INTO 20CS30023.Room VALUES(103,'icu',1,1,0);
INSERT INTO 20CS30023.Room VALUES(111,'Single',1,2,0);
INSERT INTO 20CS30023.Room VALUES(112,'icu',1,2,1);
INSERT INTO 20CS30023.Room VALUES(113,'Single',1,2,0);
INSERT INTO 20CS30023.Room VALUES(121,'Single',1,3,0);
INSERT INTO 20CS30023.Room VALUES(122,'icu',1,3,0);
INSERT INTO 20CS30023.Room VALUES(123,'Single',1,3,0);
INSERT INTO 20CS30023.Room VALUES(201,'Single',2,1,1);
INSERT INTO 20CS30023.Room VALUES(202,'icu',2,1,0);
INSERT INTO 20CS30023.Room VALUES(203,'Single',2,1,0);
INSERT INTO 20CS30023.Room VALUES(211,'Single',2,2,0);
INSERT INTO 20CS30023.Room VALUES(212,'Single',2,2,0);
INSERT INTO 20CS30023.Room VALUES(213,'Single',2,2,1);
INSERT INTO 20CS30023.Room VALUES(221,'Single',2,3,0);
INSERT INTO 20CS30023.Room VALUES(222,'Single',2,3,0);
INSERT INTO 20CS30023.Room VALUES(223,'Single',2,3,0);
INSERT INTO 20CS30023.Room VALUES(301,'Single',3,1,0);
INSERT INTO 20CS30023.Room VALUES(302,'Single',3,1,1);
INSERT INTO 20CS30023.Room VALUES(303,'Single',3,1,0);
INSERT INTO 20CS30023.Room VALUES(311,'icu',3,2,0);
INSERT INTO 20CS30023.Room VALUES(312,'Single',3,2,0);
INSERT INTO 20CS30023.Room VALUES(313,'Single',3,2,0);
INSERT INTO 20CS30023.Room VALUES(321,'Single',3,3,1);
INSERT INTO 20CS30023.Room VALUES(322,'Single',3,3,0);
INSERT INTO 20CS30023.Room VALUES(323,'Single',3,3,0);
INSERT INTO 20CS30023.Room VALUES(401,'icu',4,1,0);
INSERT INTO 20CS30023.Room VALUES(402,'Single',4,1,1);
INSERT INTO 20CS30023.Room VALUES(403,'Single',4,1,0);
INSERT INTO 20CS30023.Room VALUES(411,'icu',4,2,0);
INSERT INTO 20CS30023.Room VALUES(412,'Single',4,2,0);
INSERT INTO 20CS30023.Room VALUES(413,'Single',4,2,0);
INSERT INTO 20CS30023.Room VALUES(421,'Single',4,3,1);
INSERT INTO 20CS30023.Room VALUES(422,'Single',4,3,0);
INSERT INTO 20CS30023.Room VALUES(423,'Single',4,3,0);

INSERT INTO 20CS30023.On_Call VALUES(101,1,1,'2022-11-04 11:00','2022-11-04 19:00');
INSERT INTO 20CS30023.On_Call VALUES(101,1,2,'2022-11-04 11:00','2022-11-04 19:00');
INSERT INTO 20CS30023.On_Call VALUES(102,1,3,'2022-11-04 11:00','2022-11-04 19:00');
INSERT INTO 20CS30023.On_Call VALUES(103,1,1,'2022-11-04 19:00','2022-11-05 03:00');
INSERT INTO 20CS30023.On_Call VALUES(103,1,2,'2022-11-04 19:00','2022-11-05 03:00');
INSERT INTO 20CS30023.On_Call VALUES(103,1,3,'2022-11-04 19:00','2022-11-05 03:00');

INSERT INTO 20CS30023.Stay VALUES(3215,100000001,111,'2022-05-01','2022-05-24');
INSERT INTO 20CS30023.Stay VALUES(3216,100000003,123,'2022-05-03','2022-05-14');
INSERT INTO 20CS30023.Stay VALUES(3217,100000004,112,'2022-05-02','2022-07-03');

INSERT INTO 20CS30023.Undergoes VALUES(100000001,6,3215,'2023-05-02',3,101);
INSERT INTO 20CS30023.Undergoes VALUES(100000001,2,3215,'2022-05-03',7,101);
INSERT INTO 20CS30023.Undergoes VALUES(100000004,1,3217,'2022-05-07',3,102);
INSERT INTO 20CS30023.Undergoes VALUES(100000004,5,3217,'2022-05-09',6,102);
INSERT INTO 20CS30023.Undergoes VALUES(100000001,3,3217,'2022-05-10',7,101);
INSERT INTO 20CS30023.Undergoes VALUES(100000004,4,3217,'2022-05-13',3,103);

/*
Questions 
    Queries: Obtain the following -

/*    
    1. Names of all physicians who are trained in procedure name “bypass surgery”   
*/
    SELECT P.Name AS Physician_Name
    FROM 20CS30023.Physician AS P
    JOIN 20CS30023.Trained_In AS T
    ON P.EmployeeID = T.Physician
    JOIN 20CS30023.Procedure AS Pr
    ON T.Treatment = Pr.Code
    WHERE Pr.Name = "bypass surgery";
/*
    2. Names of all physicians affiliated with the department name “cardiology” and trained in “bypass surgery”
*/
    SELECT P.Name 
    FROM 20CS30023.Physician AS P
    JOIN 20CS30023.Affiliated_With AS AW
    ON P.EmployeeID = AW.Physician
    JOIN 20CS30023.Department AS D
    ON AW.Department = D.DepartmentID
    JOIN 20CS30023.Trained_In AS T
    ON P.EmployeeID = T.Physician
    JOIN 20CS30023.Procedure AS Pr
    ON T.Treatment = Pr.Code
    WHERE D.Name = "cardiology" AND Pr.Name = "bypass surgery";
/*
    3. Names of all the nurses who have ever been on call for room 123
*/
    SELECT Name FROM 20CS30023.Nurse WHERE EmployeeID IN (
     SELECT DISTINCT Nurse FROM 20CS30023.On_Call WHERE BlockFloor IN (
        SELECT BlockFloor FROM 20CS30023.Room WHERE Number=123
     )
     AND BlockCode IN(
        SELECT BlockCode FROM 20CS30023.Room WHERE Number=123
     )
    );
/*
    4. Names and addresses of all patients who were prescribed the medication named “remdesivir”
*/   
    SELECT Name, Address FROM 20CS30023.Patient WHERE SSN IN (
        SELECT DISTINCT Patient FROM 20CS30023.Prescribes WHERE Medication IN (
            SELECT Code FROM 20CS30023.Medication WHERE Name='Remdesivir'
        )
    );
/*   
    5. Name and insurance id of all patients who stayed in the “icu” room type for more than 15 days
*/  
    SELECT P.Name AS Patient_Name , P.InsuranceID AS Patient_InsuranceID
    FROM 20CS30023.Patient P
    JOIN 20CS30023.Stay S
    ON P.SSN = S.Patient
    JOIN 20CS30023.Room R
    ON S.Room = R.Number
    WHERE TIMESTAMPDIFF(hour, S.Start, S.End) > 360 AND R.Type='icu';  
/*  
    6. Names of all nurses who assisted in the procedure name “bypass surgery”
*/
    SELECT N.Name AS Nurse_Name
    FROM 20CS30023.Undergoes U
    JOIN 20CS30023.Procedure P
    ON U.Procedure = P.Code
    JOIN 20CS30023.Nurse N
    ON U.AssistingNurse = N.EmployeeID
    WHERE P.Name = 'bypass surgery';
/*
    7. Name and position of all nurses who assisted in the procedure name “bypass surgery” along with the names of and the accompanying physicians
*/
    SELECT P.Name AS Physician_Name, N.Name AS Nurse_Name, N.Position AS Nurse_Position
    FROM 20CS30023.Undergoes U 
    JOIN 20CS30023.Physician P
    ON U.Physician = P.EmployeeID
    JOIN 20CS30023.Nurse N
    ON U.AssistingNurse = N.EmployeeID
    JOIN 20CS30023.Procedure Pr
    ON U.Procedure = Pr.Code
    WHERE Pr.Name = 'bypass surgery';
/*
    8. Obtain the names of all physicians who have performed a medical procedure they have never been trained to perform
*/

    SELECT DISTINCT Physician.`Name`
    FROM 20CS30023.Undergoes
    LEFT JOIN 20CS30023.Trained_In
    ON 20CS30023.Undergoes.Physician = 20CS30023.Trained_In.Physician
    AND 20CS30023.Undergoes.`Procedure` = 20CS30023.Trained_In.Treatment
    JOIN 20CS30023.Physician
    ON 20CS30023.Undergoes.Physician = 20CS30023.Physician.EmployeeID
    WHERE 20CS30023.Trained_In.Treatment IS NULL;

/*
    9. Names of all physicians who have performed a medical procedure that they are trained to perform, but such that the procedure was done at a date (Undergoes.Date) after the physician's certification expired (Trained_In.CertificationExpires)
*/
    SELECT Name FROM 20CS30023.Physician WHERE EmployeeID IN (
        SELECT U.Physician
        FROM 20CS30023.Undergoes U
        JOIN 20CS30023.Trained_In T
        ON T.Physician = U.Physician
        WHERE U.Date > T.CertificationExpires
    );
/*
    10. Same as the previous query, but include the following information in the results: Physician name, name of procedure, date when the procedure was carried out, name of the patient the procedure was carried out on
*/
    SELECT P.`Name` AS Physician_Name, Pr.`Name` AS Procedure_Name, U.`Date` AS Procedure_Date, Pa.`Name` AS Patient_Name
        FROM 20CS30023.Undergoes U
        JOIN 20CS30023.Trained_In T 
        ON T.Physician = U.Physician
        JOIN 20CS30023.Patient Pa 
        ON U.Patient = Pa.SSN
        JOIN 20CS30023.Physician P 
        ON T.Physician = P.EmployeeID
        JOIN 20CS30023.Procedure Pr 
        ON U.Procedure = Pr.Code
    WHERE U.Date > T.CertificationExpires;
/*
    11. Names of all patients (also include, for each patient, the name of the patient's physician), such that all the following are true:
            • The patient has been prescribed some medication by his/her physician
            • The patient has undergone a procedure with a cost larger that 5000
            • The patient has had at least two appointment where the physician was affiliated with the cardiology department
            • The patient's physician is not the head of any department
*/
    WITH count_appointments AS (
        SELECT Physician, Patient, COUNT(*) AS count
        FROM 20CS30023.Appointment
        GROUP BY Physician, Patient
    )
    SELECT Pa.Name AS Patient_Name, P.Name AS Physician_Name
        FROM 20CS30023.Patient Pa
        JOIN 20CS30023.Undergoes U
        ON Pa.SSN = U.Patient
        JOIN 20CS30023.Department D
        ON D.Name = 'Cardiology'
        JOIN 20CS30023.Physician P
        ON P.EmployeeID != D.Head
        JOIN 20CS30023.Affiliated_With AW
        ON AW.Department = D.DepartmentID
        JOIN 20CS30023.Procedure Pr
        ON U.Procedure = Pr.Code
        JOIN 20CS30023.Prescribes Pre
        ON P.EmployeeID = Pre.Physician
        JOIN count_appointments AP
        ON P.EmployeeID = AP.Physician AND Pa.SSN = AP.Patient
    WHERE Pr.Cost > 5000 AND P.EmployeeID = AW.Physician AND Pa.SSN = Pre.Patient AND AP.count >= 2;

-- /*
--     12. Name and brand of the medication which has been prescribed to the highest number of patients
-- */
    WITH count_prescriptions AS (
        SELECT Medication, COUNT(*) AS count
        FROM 20CS30023.Prescribes
        GROUP BY Medication
    )
    SELECT `Name`, Brand FROM 20CS30023.Medication WHERE Code IN (
        SELECT Medication FROM count_prescriptions WHERE count IN ( 
            SELECT MAX(count)
            FROM count_prescriptions
            WHERE Medication IS NOT NULL
        )
    );

