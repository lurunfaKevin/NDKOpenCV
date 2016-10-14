package com.lurunfa.test;

import android.content.Context;
import android.graphics.Bitmap;
import android.util.Log;

/**
 * Created by lurunfa on 2016/9/28.
 */

public class OpenCVHelper extends SampleViewBase{

    static {
        System.loadLibrary("OpenCV");
    }

    public OpenCVHelper(Context context) {
        super(context);
    }

    public native int FindFeatures(int width, int height, byte yuv[], int[] rgba);

    @Override
    protected Bitmap processFrame(byte[] data) {
        int frameSize = getFrameWidth() * getFrameHeight();
        int[] rgba = new int[frameSize];
        Log.i("TAG","1111");

        int nc=  FindFeatures(getFrameWidth(), getFrameHeight(), data, rgba);
        Log.i("TAG",nc+"------------");

        Bitmap bmp = Bitmap.createBitmap(getFrameWidth(), getFrameHeight(), Bitmap.Config.ARGB_8888);
        bmp.setPixels(rgba, 0/* offset */, getFrameWidth() /* stride */, 0, 0, getFrameWidth(), getFrameHeight());
        return bmp;
    }
}
