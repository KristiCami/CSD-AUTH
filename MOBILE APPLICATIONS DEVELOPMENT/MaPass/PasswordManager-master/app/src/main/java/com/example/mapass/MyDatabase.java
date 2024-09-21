package com.example.mapass;

import androidx.room.Database;
import androidx.room.RoomDatabase;
import com.example.mapass.MyInterface;

@Database(entities = {Accounts.class},version = 4)
public abstract class MyDatabase extends RoomDatabase {
    public abstract MyInterface myInterface();
}
