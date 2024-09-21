package com.example.mapass;

import androidx.annotation.RequiresApi;
import androidx.appcompat.app.AppCompatActivity;
import androidx.room.Room;

import android.content.Intent;
import android.os.Build;
import android.os.Bundle;
import android.view.MenuItem;
import android.view.View;
import android.widget.Toast;

import com.example.mapass.databinding.ActivityUpdateBinding;

public class UpdateActivity extends AppCompatActivity {

    ActivityUpdateBinding binding;
    MyDatabase myDb;
    MyInterface myInt;

    @RequiresApi(api = Build.VERSION_CODES.O)
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        binding = ActivityUpdateBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        myDb = Room.databaseBuilder(this, MyDatabase.class, "accounts").allowMainThreadQueries().build();
        myInt = myDb.myInterface();

        String name = getIntent().getStringExtra("name");
        String email = getIntent().getStringExtra("email");
        String password = getIntent().getStringExtra("password");
        int id = getIntent().getIntExtra("id", -1);

        binding.socialMediaName.setText(name);
        binding.email.setText(email);

        // Decrypt the password
        String decryptedPassword = EncryptionUtils.decrypt(password);
        if (decryptedPassword != null) {
            binding.password.setText(decryptedPassword);
        } else {
            Toast.makeText(this, "Error decrypting the password", Toast.LENGTH_SHORT).show();
        }

        binding.updateAcc.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String name = binding.socialMediaName.getText().toString();
                String email = binding.email.getText().toString();
                String pass = binding.password.getText().toString();

                if (name.isEmpty() || email.isEmpty() || pass.isEmpty()) {
                    Toast.makeText(getApplicationContext(), "Name, email, and password are required", Toast.LENGTH_SHORT).show();
                } else {
                    // Encrypt the password
                    String encryptedPassword = EncryptionUtils.encrypt(pass);

                    Accounts accounts = new Accounts(id, name, email, encryptedPassword);
                    myInt.update(accounts);
                    Toast.makeText(getApplicationContext(), "Account updated successfully", Toast.LENGTH_SHORT).show();
                    navigateToFetchDataActivity();
                }
            }
        });

        binding.delAcc.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                myInt.deleteAcc(id);
                Toast.makeText(getApplicationContext(), "Account deleted successfully", Toast.LENGTH_SHORT).show();
                navigateToFetchDataActivity();
            }
        });
    }

    @Override
    public void onBackPressed() {
        navigateToFetchDataActivity();
    }

    private void navigateToFetchDataActivity() {
        Intent intent = new Intent(getApplicationContext(), FetchDataActivity.class);
        intent.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP | Intent.FLAG_ACTIVITY_NEW_TASK);
        startActivity(intent);
        finish();
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        if (item.getItemId() == android.R.id.home) {
            navigateToFetchDataActivity();
            return true;
        }
        return super.onOptionsItemSelected(item);
    }
}
