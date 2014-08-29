package com.oulrich.eventreceiver;

import java.lang.ref.WeakReference;
import java.sql.Time;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.Date;
import java.util.Locale;

import android.app.NotificationManager;
import android.support.v7.app.ActionBarActivity;
import android.support.v7.app.ActionBar;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentTransaction;
import android.support.v4.app.FragmentPagerAdapter;

import android.app.Notification;
import android.app.NotificationManager;

import android.app.PendingIntent;
import android.content.Intent;
import android.os.Bundle;

import android.support.v4.view.ViewPager;
import android.text.format.DateFormat;
import android.view.Gravity;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ListView;
import android.widget.TextView;

import android.app.Activity;
import android.os.AsyncTask;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

import org.apache.http.HttpEntity;
import org.apache.http.HttpResponse;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.params.BasicHttpParams;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;

public class MainActivity extends ActionBarActivity {

    // JSON RESTful API test
    static String recipePuppyURL = "http://www.recipepuppy.com/api/?i=onions,garlic,egg,basil&q=omelet&p=3";
    static String TAG = "***RECIPE COMPOSER***: ";

    static String recipeTitle = "";
    static String recipeURL = "";
    static String recipeIngredients = "";

    /**
     * The {@link android.support.v4.view.PagerAdapter} that will provide
     * fragments for each of the sections. We use a
     * {@link FragmentPagerAdapter} derivative, which will keep every
     * loaded fragment in memory. If this becomes too memory intensive, it
     * may be best to switch to a
     * {@link android.support.v4.app.FragmentStatePagerAdapter}.
     */
    SectionsPagerAdapter mSectionsPagerAdapter;

    /**
     * The {@link ViewPager} that will host the section contents.
     */
    ViewPager mViewPager;



    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Create the adapter that will return a fragment for each of the three
        // primary sections of the activity.
        mSectionsPagerAdapter = new SectionsPagerAdapter(getSupportFragmentManager());

        // Set up the ViewPager with the sections adapter.
        mViewPager = (ViewPager) findViewById(R.id.pager);
        mViewPager.setAdapter(mSectionsPagerAdapter);
    }


    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();
        if (id == R.id.action_settings) {
            return true;
        }
        return super.onOptionsItemSelected(item);
    }


    /**
     * A {@link FragmentPagerAdapter} that returns a fragment corresponding to
     * one of the sections/tabs/pages.
     */
    public class SectionsPagerAdapter extends FragmentPagerAdapter {

        public SectionsPagerAdapter(FragmentManager fm) {
            super(fm);
        }

        @Override
        public Fragment getItem(int position) {
            // getItem is called to instantiate the fragment for the given page.
            // Return a PlaceholderFragment (defined as a static inner class below).
            return PlaceholderFragment.newInstance(position + 1);
        }

        @Override
        public int getCount() {
            // Show 3 total pages.
            return 2;
        }

        @Override
        public CharSequence getPageTitle(int position) {
            Locale l = Locale.getDefault();
            switch (position) {
                case 0:
                    return getString(R.string.title_section1).toUpperCase(l);
                case 1:
                    return getString(R.string.title_section2).toUpperCase(l);
            }
            return null;
        }
    }

    /**
     * A placeholder fragment containing a simple view.
     */
    public static class PlaceholderFragment extends Fragment {
        /**
         * The fragment argument representing the section number for this
         * fragment.
         */

        private WeakReference<RecipeDownloader> asyncTaskWeakRef;

        private MainActivity mParentActivity;
        private static final String ARG_SECTION_NUMBER = "section_number";
        private LayoutInflater _inflater;
        private ViewGroup _container;
        private PlaceholderFragment frag;

        /**
         * Returns a new instance of this fragment for the given section
         * number.
         */
        public static PlaceholderFragment newInstance(int sectionNumber) {
            PlaceholderFragment fragment = new PlaceholderFragment();
            Bundle args = new Bundle();
            args.putInt(ARG_SECTION_NUMBER, sectionNumber);
            fragment.setArguments(args);
            return fragment;
        }

        public PlaceholderFragment() {
        }

        public void onAttach(Activity activity) {
            super.onAttach(activity);

            // This makes sure that the container activity has implemented
            // the callback interface. If not, it throws an exception
            try {
                mParentActivity = (MainActivity) activity;
            } catch (ClassCastException e) {
                throw new ClassCastException(activity.toString()
                        + " must implement mParentActivity");
            }
        }

        @Override
        public View onCreateView(LayoutInflater inflater, ViewGroup container,
                Bundle savedInstanceState) {
            View rootView = inflater.inflate(R.layout.fragment_main, container, false);
            TextView textView = (TextView) rootView.findViewById(R.id.section_label);
            textView.setText(Integer.toString(getArguments().getInt(ARG_SECTION_NUMBER)));

             _inflater = inflater;
             _container = container;
             frag = this;


            try{
                final Button btn = (Button) rootView.findViewById(R.id.submitRequest);
                btn.setOnClickListener(new View.OnClickListener() {
                    @Override
                    public void onClick(View v) {
                        Log.d("--> Fragment View Button Click Event: ", " Start");

                        RecipeDownloader rdAsyncTask = new RecipeDownloader(frag, _inflater, _container);
                        asyncTaskWeakRef = new WeakReference<RecipeDownloader >(rdAsyncTask);

                        // Make recipe request
                        rdAsyncTask.execute();

                        Log.d("--> Fragment View Button Click Event: ", " End");
                    }
                });
            } catch(Exception e){
                Log.d("--> EXCEPTION: ", e.getMessage());
            }


            return rootView;
        }

        public void sendNotification(String title){

            Date d = new Date();
            CharSequence date_string  = DateFormat.format("EEEE, MMMM d, yyyy ", d.getTime());

            // Prepare intent which is triggered if the
            // notification is selected
            Intent intent = new Intent(getActivity(), NotificationReceiverActivity.class);
            PendingIntent pIntent = PendingIntent.getActivity(getActivity(), 0, intent, 0);

            // Build notification
            // Actions are just fake
            Notification noti = new Notification.Builder(getActivity())
                    .setContentTitle(title)
                    .setContentText(date_string).setSmallIcon(R.drawable.ic_launcher)
                    .setContentIntent(pIntent).build();
            NotificationManager notificationManager = (NotificationManager) getActivity().getSystemService(NOTIFICATION_SERVICE);
            // hide the notification after its selected
            noti.flags |= Notification.FLAG_AUTO_CANCEL;

            notificationManager.notify(0, noti);
        }

        /*
       * Use AsyncTask if you need to perform background tasks, but also need
       * to change components on the GUI. Put the background operations in
       * doInBackground. Put the GUI manipulation code in onPostExecute
       * */
        private class RecipeDownloader extends AsyncTask<String, String, String> {

            private WeakReference<PlaceholderFragment> fragmentWeakRef;
            private PlaceholderFragment frag;
            private LayoutInflater inflater;
            private ViewGroup container;

            // create the temporary array for recipe list
            //String[] recipeList = new String[jsonArray.length()];
            ArrayList<String> recipeList = new ArrayList<String>();

            private RecipeDownloader(PlaceholderFragment fragment, LayoutInflater _inflater, ViewGroup _container){
                this.fragmentWeakRef = new WeakReference<PlaceholderFragment>(fragment);
                this.frag = fragment;
                this.inflater = _inflater;
                this.container = _container;
            }

            @Override
            protected String doInBackground(String... strings) {

                // HTTP Client that supports streaming uploads and downloads
                DefaultHttpClient defaultHttpClient = new DefaultHttpClient(new BasicHttpParams());

                // Define that I want to use the POST method to grab data from the provided URL
                HttpPost httpPost = new HttpPost(recipePuppyURL);

                // Web service used is defined
                httpPost.setHeader("Content-type", "application/json");

                // Used to read data from the URL
                InputStream inputStream = null;

                // Will hold all the data from the URL
                String queryResult = null;

                try {
                    // Get a response if any from the web service
                    HttpResponse httpResponse = defaultHttpClient.execute(httpPost);

                    // The content from the requested URL along with headers, etc.
                    HttpEntity httpEntity = httpResponse.getEntity();

                    // Get the main content from the URL
                    inputStream = httpEntity.getContent();

                    // JSON is UTF-8 by default
                    // BufferedReader reads data from the InputStream until the Buffer is full
                    BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(inputStream, "UTF-8"), 8);

                    // Will store the data
                    StringBuilder stringBuilder = new StringBuilder();

                    String line = "";

                    // Read in the data from the Buffer until nothing is left
                    while ((line = bufferedReader.readLine()) != null) {

                        // Add data from the Buffer until nothing is left
                        stringBuilder.append(line + '\n');
                    }

                    // Store the complete data in result
                    queryResult = stringBuilder.toString();

                } catch (Exception e) {
                    e.printStackTrace();
                }

                finally {
                    // Close the InputStream
                    try {
                        if (inputStream != null) {
                            inputStream.close();
                        }
                    } catch (Exception e) {
                        e.printStackTrace();
                    }
                }

                // Holds Key / Value pairs from a JSON source
                JSONObject jsonObject;

                try {
                    // Print out all the data read in
                    Log.v("JSONParser RESULT: ", queryResult);

                    // Get the root JSONObject
                    jsonObject = new JSONObject(queryResult);
                    Log.d(TAG, jsonObject.toString());

                    JSONArray jsonArray = jsonObject.getJSONArray("results");
                    Log.d(TAG, jsonArray.toString());

                    recipeList.clear();

                    for (int i = 0; i < jsonArray.length(); ++i)
                    {
                        try {
                            JSONObject recipe = jsonArray.getJSONObject(i);

                            // Pull items from the array
                            recipeTitle = recipe.getString("title");
                            recipeURL = recipe.getString("href");
                            recipeIngredients = recipe.getString("ingredients");

                            // append elements to the temporary string array:
                            recipeList.add(recipeTitle);

                            Log.d("Title: ", recipeTitle);
                            Log.d("URL: ", recipeURL);
                            Log.d("Ingredients List: ", recipeIngredients);

                        } catch (JSONException e) {
                            e.printStackTrace();
                        }
                    }

                } catch (JSONException je) {
                    je.printStackTrace();
                }

                return queryResult;
            }

            @Override
            protected void onPostExecute(String s) {
                super.onPostExecute(s);
                Log.d(TAG, "onPostExecute");

                if (this.fragmentWeakRef.get() != null) {
        //            TextView title = (TextView) findViewById(R.id.title);
        //            TextView url = (TextView) findViewById(R.id.href);
        //            TextView ingredients = (TextView) findViewById(R.id.ingredients);
        //
        //            title.setText("Title: " + recipeTitle);
        //            url.setText("URL: " + recipeURL);
        //            ingredients.setText("Ingredients: " + recipeIngredients);
                }

                // get the root view context
                View rootView = inflater.inflate(R.layout.fragment_main, container, false);
                ListView myListView = (ListView) rootView.findViewById(R.id.recipeList);

                if (myListView != null){
                    // append the string array to the List View:
                    // by posting the new view through an adapter?
                    ArrayAdapter<String> adapter;
                    adapter = new ArrayAdapter<String>(getActivity(), android.R.layout.simple_list_item_1, recipeList);
                    myListView.setAdapter(adapter);

                    Log.d("--> Notice: ", "Appended the list of recipes to the view..");

                    // notify that user the request was sent
                    try {
                        sendNotification(recipeTitle);
                    } catch (Exception e){
                        Log.d("--> Fragment View Notifications: ", " Error: " + e.getMessage());
                    }

                } else {
                    Log.d("--> Wanring: ", "recipeList ListView is NULL");
                }

            }
        }


    }


}
