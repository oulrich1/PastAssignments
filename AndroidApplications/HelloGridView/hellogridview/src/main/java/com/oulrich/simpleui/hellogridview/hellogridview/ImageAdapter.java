package com.oulrich.simpleui.hellogridview.hellogridview;

import android.content.Context;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.GridView;
import android.widget.ImageView;

import java.util.ArrayList;


public class ImageAdapter extends BaseAdapter {
    private Context mContext;

    public ImageAdapter(Context c) {
        mContext = c;
    }

    @Override
    public int getCount() {
        return mThumbIds.length;
    }

    /* should return the actual object.. */
    public Object getItem(int position){
        return null;
    }

    /* should return the row id of the item.. */
    public long getItemId(int position) {
        return 0;
    }

    @Override
    public View getView(int position, View convertView, ViewGroup parent) {
        ImageView imageView;
        if (convertView == null) {  // if it's not recycled, initialize some attributes
            imageView = new ImageView(mContext);
            imageView.setLayoutParams(new GridView.LayoutParams(85, 85));
            imageView.setScaleType(ImageView.ScaleType.CENTER_CROP);
            imageView.setPadding(8, 8, 8, 8);
        } else {
            imageView = (ImageView) convertView;
        }

        imageView.setImageResource(mThumbIds[position]);
        return imageView;
    }


    private Integer[] mThumbIds = {
            R.drawable.g0018,
            R.drawable.g0019,
            R.drawable.g0020,
            R.drawable.g0021,
            R.drawable.g0022,
            R.drawable.g0023,
            R.drawable.g0024,
            R.drawable.g0025,
            R.drawable.g0026,
            R.drawable.g0027
    };
}
