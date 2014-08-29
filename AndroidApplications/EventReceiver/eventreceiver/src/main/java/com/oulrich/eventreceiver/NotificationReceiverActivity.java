package com.oulrich.eventreceiver;

import android.app.Activity;
import android.os.Bundle;
import android.widget.TextView;

public class NotificationReceiverActivity extends Activity {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.result);

        String title = "Receive the title of the recipe and display it here...";
        TextView textview = (TextView) findViewById(R.id.titleTextView);
        textview.setText(title);
    }
}