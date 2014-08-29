package com.oulrich.simpleui.simpleui;

import java.util.ArrayList;
import java.util.Locale;

import android.support.v7.app.ActionBarActivity;
import android.support.v7.app.ActionBar;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentTransaction;
import android.support.v4.app.FragmentPagerAdapter;
import android.os.Bundle;
import android.support.v4.view.ViewPager;
import android.util.Log;
import android.view.Gravity;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;


public class MainActivity extends ActionBarActivity {

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
            return 3;
        }

        @Override
        public CharSequence getPageTitle(int position) {
            Locale l = Locale.getDefault();
            switch (position) {
                case 0:
                    return getString(R.string.title_section1).toUpperCase(l);
                case 1:
                    return getString(R.string.title_section2).toUpperCase(l);
                case 2:
                    return getString(R.string.title_section3).toUpperCase(l);
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
        private static final String ARG_SECTION_NUMBER = "section_number";

        ArrayList<String> ingredient_titles; // used as a stack
        int ingredient_titles_top_index = 0;
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

        @Override
        public View onCreateView(LayoutInflater inflater, ViewGroup container,
                Bundle savedInstanceState) {
            View rootView = inflater.inflate(R.layout.fragment_main, container, false);
            //TextView textView = (TextView) rootView.findViewById(R.id.section_label);
            //textView.setText(Integer.toString(getArguments().getInt(ARG_SECTION_NUMBER)));

            Log.d(" About to:  ", "onCreateView");

            final Button pushIngredientButton;
            final Button popIngredientButton;
            final EditText ingredientEditText;
            final TextView ingredientTopTextView;

            ingredient_titles = new ArrayList<String>();
            ingredient_titles.clear();

            try {
                pushIngredientButton  = (Button)   rootView.findViewById(R.id.pushIngredient);
                popIngredientButton   = (Button)   rootView.findViewById(R.id.popIngredient);
                ingredientEditText    = (EditText) rootView.findViewById(R.id.ingredientEditText);
                ingredientTopTextView = (TextView) rootView.findViewById(R.id.ingredientTopTextView);

                pushIngredientButton.setOnClickListener(new View.OnClickListener() {
                    @Override
                    public void onClick(View v) {
                        Log.d(" >> >> >>", "push ingredient button clicked!");
                        String ingredient_title = ingredientEditText.getText().toString();
                        if (ingredient_titles.contains(ingredient_title) == false){
                            ingredient_titles.add(ingredient_title);
                            ingredient_titles_top_index = ingredient_titles.size()-1;
                            ingredientTopTextView.setText(ingredient_titles.get(ingredient_titles_top_index));
                        } else {
                            Toast.makeText(     getActivity(),
                                                "Ingredient '" + ingredient_title + "', Already Exists..",
                                                Toast.LENGTH_LONG).show();
                        }


                    }
                });

                popIngredientButton.setOnClickListener(new View.OnClickListener() {
                    @Override
                    public void onClick(View v) {
                        Log.d(" >> >> >>", "pop ingredient button clicked!");
                        if (ingredient_titles != null && ingredient_titles.size() > 0) {
                            ingredient_titles.remove(ingredient_titles_top_index);
                            if (!ingredient_titles.isEmpty()) {
                                ingredient_titles_top_index = ingredient_titles.size() - 1;
                                ingredientTopTextView.setText(ingredient_titles.get(ingredient_titles_top_index));
                            } else {
                                ingredient_titles_top_index = 0;
                                ingredientTopTextView.setText("");
                            }
                        } else {
                            ingredient_titles_top_index = 0;
                            Toast.makeText(getActivity(), "The Stack is Empty", Toast.LENGTH_SHORT).show();
                        }
                    }
                });
            } catch (NullPointerException e) {
                Log.d("EXCEPTION ", "onCreateView: " + e.toString());
            }

            return rootView;
        }
    }

}
