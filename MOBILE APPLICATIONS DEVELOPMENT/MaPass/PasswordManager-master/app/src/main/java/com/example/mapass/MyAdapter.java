package com.example.mapass;

import android.content.Context;
import android.content.Intent;
import android.os.Build;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;
import androidx.annotation.NonNull;
import androidx.annotation.RequiresApi;
import androidx.recyclerview.widget.RecyclerView;
import java.util.List;

public class MyAdapter extends RecyclerView.Adapter<MyAdapter.MyViewHolder> {
    private Context context;
    private List<Accounts> accountsList;
    public MyAdapter(Context context, List<Accounts> accountsList) {
        this.accountsList = accountsList;
        this.context = context;
    }

    @NonNull
    @Override
    public MyViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        View view = LayoutInflater.from(parent.getContext()).inflate(R.layout.single_row,parent,false);
        return new MyViewHolder(view);
    }

    @RequiresApi(api = Build.VERSION_CODES.O)
    @Override
    public void onBindViewHolder(@NonNull MyViewHolder holder, int position) {

        Accounts accounts = accountsList.get(position);
        holder.name.setText(accounts.getsName());
        holder.email.setText(accounts.getEmail());
        String decryptedPassword = EncryptionUtils.decrypt(accounts.getPassword());
        holder.password.setText(decryptedPassword);


        holder.itemView.setOnClickListener(new View.OnClickListener() {
            @RequiresApi(api = Build.VERSION_CODES.O)
            @Override
            public void onClick(View v) {
                Intent intent=new Intent(context,UpdateActivity.class);
                intent.putExtra("name",accounts.getsName());
                intent.putExtra("id",accounts.getId());

                intent.putExtra("email",accounts.getEmail());
                intent.putExtra("password",EncryptionUtils.decrypt(accounts.getPassword()));
                context.startActivity(intent);
            }
        });
    }

    @Override
    public int getItemCount() {
        return accountsList.size();
    }

    public class MyViewHolder extends RecyclerView.ViewHolder{
        TextView name,email,password;
        public MyViewHolder(@NonNull View itemView) {
            super(itemView);
            name = itemView.findViewById(R.id.sName_one);
            email=itemView.findViewById(R.id.email_one);
            password = itemView.findViewById(R.id.pass_one);

        }
    }
}
