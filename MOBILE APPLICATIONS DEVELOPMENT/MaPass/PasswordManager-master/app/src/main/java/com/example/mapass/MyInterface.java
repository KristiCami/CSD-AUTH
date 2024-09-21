package com.example.mapass;

import androidx.room.Dao;
import androidx.room.Insert;
import androidx.room.Query;
import androidx.room.Update;

import java.util.List;

@Dao
public interface MyInterface {
    @Insert
    void insert(Accounts entityClass);
    @Update
    void update(Accounts entityClass);
    @Query("DELETE from accounts where id=:id")
    void deleteAcc(int id);
    @Query("SELECT * From accounts")
    List<Accounts> getAllAccounts();
}
