CREATE TABLE ΠΙΣΤΩΤΙΚΗ_ΚΑΡΤΑ (
  ID INTEGER  NOT NULL  ,
  PIN CHAR(4)    ,
  ΗμερομηνίαΛήξης DATE      ,
PRIMARY KEY(ID));



CREATE TABLE ΠΕΛΑΤΗΣ (
  ID INTEGER  NOT NULL  ,
  Όνομα INTEGER    ,
  Επώνυμο VARCHAR(30)    ,
  ΌνομαΠατρός VARCHAR(50)    ,
  Πόλη VARCHAR(30)    ,
  Οδός VARCHAR(100)    ,
  Αριθμός VARCHAR(100)    ,
  ΤΚ VARCHAR(10)    ,
  ΑΦΜ VARCHAR(20)    ,
  ΑΤ VARCHAR(10)      ,
PRIMARY KEY(ID));



CREATE TABLE YΠΑΛΛΗΛΟΣ (
  ID INTEGER  NOT NULL  ,
  Όνομα VARCHAR(50)    ,
  Επώνυμο VARCHAR(50)    ,
  Διεύθυνση VARCHAR(100)    ,
  Τηλέφωνο VARCHAR(20)      ,
PRIMARY KEY(ID));



CREATE TABLE ΤΗΛΕΦΩΝΑ_ΠΕΛΑΤΩΝ (
  Τηλέφωνο INTEGER  NOT NULL  ,
  IDπελάτη INTEGER  NOT NULL    ,
PRIMARY KEY(Τηλέφωνο, IDπελάτη)  ,
  FOREIGN KEY(IDπελάτη)
    REFERENCES ΠΕΛΑΤΗΣ(ID)
      ON DELETE NO ACTION
      ON UPDATE NO ACTION);


CREATE INDEX ΤΗΛΕΦΩΝΑ_ΠΕΛΑΤΩΝ_FKIndex1 ON ΤΗΛΕΦΩΝΑ_ΠΕΛΑΤΩΝ (IDπελάτη);



CREATE TABLE ΛΟΓΑΡΙΑΣ0ΜΟΣ (
  ID INTEGER  NOT NULL  ,
  IDπελάτη INTEGER  NOT NULL  ,
  ΕίδοςΛογαριασμού VARCHAR(20)    ,
  Υπόλοιπο DECIMAL(30,2)      ,
PRIMARY KEY(ID)  ,
  FOREIGN KEY(IDπελάτη)
    REFERENCES ΠΕΛΑΤΗΣ(ID)
      ON DELETE NO ACTION
      ON UPDATE NO ACTION);


CREATE INDEX ΛΟΓΑΡΙΑΣ0ΜΟΣ_FKIndex1 ON ΛΟΓΑΡΙΑΣ0ΜΟΣ (IDπελάτη);



CREATE TABLE E_BANKING (
  ID INTEGER  NOT NULL  ,
  IDπελάτη INTEGER  NOT NULL  ,
  Username VARCHAR(50)    ,
  Password_2 VARCHAR(50)    ,
  Email VARCHAR(50)      ,
PRIMARY KEY(ID)  ,
  FOREIGN KEY(IDπελάτη)
    REFERENCES ΠΕΛΑΤΗΣ(ID)
      ON DELETE NO ACTION
      ON UPDATE NO ACTION);


CREATE INDEX E_BANKING_FKIndex1 ON E_BANKING (IDπελάτη);



CREATE TABLE ΚΙΝΗΣΗ (
  ID INTEGER  NOT NULL  ,
  IDλογαριασμού INTEGER  NOT NULL  ,
  ΕίδοςΚίνησης VARCHAR(20)    ,
  Ημερομηνία DATE    ,
  Ποσό DECIMAL(30,2)      ,
PRIMARY KEY(ID)  ,
  FOREIGN KEY(IDλογαριασμού)
    REFERENCES ΛΟΓΑΡΙΑΣ0ΜΟΣ(ID)
      ON DELETE NO ACTION
      ON UPDATE NO ACTION);


CREATE INDEX ΚΙΝΗΣΗ_FKIndex1 ON ΚΙΝΗΣΗ (IDλογαριασμού);



CREATE TABLE ΣΥΝΔΕΣΕΙΣ_ΚΑΡΤΩΝ (
  IDπιστωτικής INTEGER  NOT NULL  ,
  IDλογαριασμού INTEGER  NOT NULL    ,
PRIMARY KEY(IDπιστωτικής, IDλογαριασμού)    ,
  FOREIGN KEY(IDλογαριασμού)
    REFERENCES ΛΟΓΑΡΙΑΣ0ΜΟΣ(ID)
      ON DELETE NO ACTION
      ON UPDATE NO ACTION,
  FOREIGN KEY(IDπιστωτικής)
    REFERENCES ΠΙΣΤΩΤΙΚΗ_ΚΑΡΤΑ(ID)
      ON DELETE NO ACTION
      ON UPDATE NO ACTION);


CREATE INDEX ΣΥΝΔΕΣΕΙΣ_ΚΑΡΤΩΝ_FKIndex1 ON ΣΥΝΔΕΣΕΙΣ_ΚΑΡΤΩΝ (IDλογαριασμού);
CREATE INDEX ΣΥΝΔΕΣΕΙΣ_ΚΑΡΤΩΝ_FKIndex2 ON ΣΥΝΔΕΣΕΙΣ_ΚΑΡΤΩΝ (IDπιστωτικής);



CREATE TABLE ΕΞΥΠΗΡΕΤΗΣΕΙΣ (
  IDπελάτη INTEGER  NOT NULL  ,
  IDυπαλλήλου INTEGER  NOT NULL  ,
  Ημερομηνία DATE  NOT NULL  ,
  Ώρα TIME  NOT NULL    ,
PRIMARY KEY(IDπελάτη, IDυπαλλήλου, Ημερομηνία, Ώρα)    ,
  FOREIGN KEY(IDπελάτη)
    REFERENCES ΠΕΛΑΤΗΣ(ID)
      ON DELETE NO ACTION
      ON UPDATE NO ACTION,
  FOREIGN KEY(IDυπαλλήλου)
    REFERENCES YΠΑΛΛΗΛΟΣ(ID)
      ON DELETE NO ACTION
      ON UPDATE NO ACTION);


CREATE INDEX ΠΕΛΑΤΗΣ_has_YΠΑΛΛΗΛΟΣ_FKIndex1 ON ΕΞΥΠΗΡΕΤΗΣΕΙΣ (IDπελάτη);
CREATE INDEX ΠΕΛΑΤΗΣ_has_YΠΑΛΛΗΛΟΣ_FKIndex2 ON ΕΞΥΠΗΡΕΤΗΣΕΙΣ (IDυπαλλήλου);




