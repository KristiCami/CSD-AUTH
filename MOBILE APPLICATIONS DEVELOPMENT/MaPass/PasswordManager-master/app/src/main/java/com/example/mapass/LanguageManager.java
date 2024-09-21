package com.example.mapass;
import android.content.Context;
import android.content.SharedPreferences;
import android.content.res.Configuration;
import android.content.res.Resources;
import android.os.Build;
import android.preference.PreferenceManager;
import java.util.Locale;



public class LanguageManager {
    // Retrieving the stored language preference
    private Context ct;

    public LanguageManager(Context context) {
        this.ct = context;
    }


    public void updateResource(String code)
    {
        Locale locale = new Locale(code);
        Locale.setDefault(locale);
        Resources resources = ct.getResources();
        Configuration configuration = resources.getConfiguration();
        configuration.setLocale(locale);

        ct = ct.createConfigurationContext(configuration);
        resources.updateConfiguration(configuration, resources.getDisplayMetrics());
    }
}




    /*SharedPreferences preferences = PreferenceManager.getDefaultSharedPreferences(context);
    String selectedLanguage = preferences.getString("language", "en"); // "en" is the default language

    // Setting the locale based on the selected language
    Locale locale;
if (selectedLanguage.equals("el")) {
        locale = new Locale("el"); // Greek language
    } else {
        locale = new Locale("en"); // Fallback to English
    }

Resources resources = context.getResources();
Configuration configuration = resources.getConfiguration();
configuration.setLocale(locale);
resources.updateConfiguration(configuration, resources.getDisplayMetrics());
}*/
