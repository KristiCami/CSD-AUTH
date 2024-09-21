package com.example.mapass;

import androidx.annotation.RequiresApi;
import androidx.appcompat.app.AppCompatActivity;
import androidx.room.Room;

import android.annotation.SuppressLint;
import android.app.Dialog;
import android.content.Intent;
import android.graphics.Color;
import android.graphics.drawable.ColorDrawable;
import android.os.Build;
import android.os.Bundle;
import android.view.View;
import android.view.ViewGroup;
import android.view.Window;
import android.widget.EditText;
import android.widget.Toast;
import android.widget.ImageView;
import android.widget.TextView;

import com.example.mapass.databinding.ActivityMainBinding;
public class MainActivity extends AppCompatActivity {
    ActivityMainBinding binding;
    MyDatabase myDb;
    MyInterface myInt;

    @SuppressLint("SetTextI18n")
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        Dialog dialog = new Dialog(this);
        dialog.requestWindowFeature(Window.FEATURE_NO_TITLE);
        dialog.setContentView(R.layout.dialog_image);
        dialog.getWindow().setBackgroundDrawable(new ColorDrawable(Color.TRANSPARENT));
        dialog.getWindow().setLayout(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT);

        // Set the image resource for the ImageView in the dialog
        ImageView dialogImage = dialog.findViewById(R.id.dialogImage);
        dialogImage.setImageResource(R.drawable.applogo);

        // Set the welcome message below the image
        TextView welcomeMessage = dialog.findViewById(R.id.welcomeMessage);
        welcomeMessage.setText("Welcome to the Password Manager App");
        dialog.show();

        myDb= Room.databaseBuilder(this,MyDatabase.class,"accounts").allowMainThreadQueries().fallbackToDestructiveMigration().build();
        myInt=myDb.myInterface();

        EditText objName = findViewById(R.id.socialMediaName);
        EditText objEmail = findViewById(R.id.Email);
        EditText objPassword = findViewById(R.id.password);

        if (savedInstanceState != null) {
            // Retrieve data from the Bundle (other methods include getInt(), getBoolean(), etc)
            CharSequence userText = savedInstanceState.getCharSequence("savedUserText");
            CharSequence displayText = savedInstanceState.getCharSequence("savedDisplayText");

            // Restore the dynamic state of the UI
            objName.setText(userText);
            objEmail.setText(displayText);
        } else {
            // Initialize the UI
            objName.setText("");
            objName.setHint("Name");
            objEmail.setText("");
            objEmail.setHint("Email");
            objPassword.setText("");
            objPassword.setHint("Password");
        }

        binding.addAcc.setOnClickListener(new View.OnClickListener() {
            @RequiresApi(api = Build.VERSION_CODES.O)
            @Override
            public void onClick(View view) {
                String name = binding.socialMediaName.getText().toString();
                String email = binding.Email.getText().toString();
                String password = binding.password.getText().toString();

                if (name.isEmpty() || email.isEmpty() || password.isEmpty()) {
                    Toast.makeText(getApplicationContext(), "Name, email, and password are required", Toast.LENGTH_SHORT).show();
                } else {
                    String encryptedPassword = EncryptionUtils.encrypt(password);
                    if (encryptedPassword != null) {
                        Accounts accounts = new Accounts(0, name, email, encryptedPassword);
                        myInt.insert(accounts);
                        Toast.makeText(getApplicationContext(), "Account added successfully", Toast.LENGTH_SHORT).show();
                        binding.socialMediaName.setText("");
                        binding.Email.setText("");
                        binding.password.setText("");

                    } else {
                        Toast.makeText(getApplicationContext(), "Error encrypting the password", Toast.LENGTH_SHORT).show();
                    }
                }
            }
        });

        binding.showAccBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                startActivity(new Intent(MainActivity.this, FetchDataActivity.class));
            }
        });

    }
}