package com.example.mapass;

import androidx.room.ColumnInfo;
import androidx.room.Entity;
import androidx.room.PrimaryKey;
@Entity(tableName = "accounts")
public class Accounts {
    @PrimaryKey(autoGenerate = true)
    private int id;
    @ColumnInfo(name = "name")
    public String sName;
    @ColumnInfo(name = "email")
    private String email;
    @ColumnInfo(name = "password")
    private String password;
    public Accounts(int id, String sName, String email, String password) {
        this.id = id;
        this.sName = sName;
        this.email = email;
        this.password = password;
    }

    public int getId() {
        return id;
    }
    public String getsName() {
        return sName;
    }
    public String getEmail() {
        return email;
    }
    public String getPassword() {
        return password;
    }
    public void setId(int id) {
        this.id = id;
    }
    public void setsName(String sName) {
        this.sName = sName;
    }
    public void setEmail(String email) {
        this.email = email;
    }
    public void setPassword(String password) {
        this.password = password;
    }
}
