package com.free.diary.ui.view;

import android.content.Context;
import android.content.res.TypedArray;
import android.util.AttributeSet;
import android.widget.TextView;

import com.free.diary.R;


public class DynamicTextView extends TextView {

    private double mHeightRatio = 1.0;

    public DynamicTextView(Context context) {
        this(context, null);
    }

    public DynamicTextView(Context context, AttributeSet attrs) {
        this(context, attrs, 0);
    }

    public DynamicTextView(Context context, AttributeSet attrs, int defStyle) {
        super(context, attrs, defStyle);

        TypedArray a = context.getTheme().obtainStyledAttributes(attrs, R.styleable.DynamicSpecImage, defStyle, 0);
        int n = a.getIndexCount();
        for (int i = 0; i < n; i++) {
            int attr = a.getIndex(i);
            switch (attr) {
                case R.styleable.DynamicSpecImage_ratio:
                    mHeightRatio = a.getFloat(attr, (float) 0.0);
                    break;

                default:
                    break;
            }
        }
        a.recycle();
    }

    public void setHeightRatio(double ratio) {
        mHeightRatio = ratio;
        requestLayout();
    }

    @Override
    protected void onMeasure(int widthMeasureSpec, int heightMeasureSpec) {
        if (mHeightRatio > 0.0) {
            // set the image views size
            int width = MeasureSpec.getSize(widthMeasureSpec);
            int height = (int) (width * mHeightRatio);
            setMeasuredDimension(width, height);
        } else {
            super.onMeasure(widthMeasureSpec, heightMeasureSpec);
        }
    }
}
