package com.example.mapass;

import androidx.annotation.NonNull;
import androidx.annotation.RequiresApi;
import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.room.Room;

import android.annotation.SuppressLint;
import android.os.Build;
import android.os.Bundle;
import android.widget.Toast;
import com.example.mapass.databinding.ActivityFetchDataActivityBinding;
import java.util.List;


public class FetchDataActivity extends AppCompatActivity {
    ActivityFetchDataActivityBinding binding;
    MyDatabase myDb;
    MyInterface myInt;
    List<Accounts> accountsList;
    MyAdapter myAdapter;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        binding = ActivityFetchDataActivityBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        myDb = Room.databaseBuilder(this, MyDatabase.class, "accounts").allowMainThreadQueries().build();
        myInt = myDb.myInterface();

        accountsList = myInt.getAllAccounts();
        Toast.makeText(this, "You have " + accountsList.size() + " accounts", Toast.LENGTH_SHORT).show();

        myAdapter = new MyAdapter(this, accountsList) {
            @RequiresApi(api = Build.VERSION_CODES.O)
            @SuppressLint("SetTextI18n")
            @Override

            public void onBindViewHolder(@NonNull MyAdapter.MyViewHolder holder, int position) {
                super.onBindViewHolder(holder, position);

                Accounts account = accountsList.get(position);
                String decryptedPassword = EncryptionUtils.decrypt(account.getPassword());
                if (decryptedPassword != null) {
                    holder.password.setText(decryptedPassword);
                } else {
                    holder.password.setText("Error decrypting the password");
                }
            }
        };

        binding.dataRecycler.setLayoutManager(new LinearLayoutManager(this));
        binding.dataRecycler.setAdapter(myAdapter);
    }
}
