package com.lurunfa.test;

import android.Manifest;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.support.v4.app.ActivityCompat;
import android.support.v4.content.ContextCompat;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        if (ContextCompat.checkSelfPermission(this, Manifest.permission.CAMERA)== PackageManager.PERMISSION_GRANTED){
            Log.i("TAG","1");
            setContentView(new OpenCVHelper(this));
        }else{
            ActivityCompat.requestPermissions(this,new String[]{Manifest.permission.CAMERA},1);
            setContentView(new OpenCVHelper(this));
        }

//        ImageView imageView = (ImageView) findViewById(R.id.img);
//        Bitmap bitmap = ((BitmapDrawable) getResources().getDrawable(
//                R.mipmap.ic_launcher)).getBitmap();
//        int w = bitmap.getWidth(), h = bitmap.getHeight();
//        int[] pix = new int[w * h];
//        bitmap.getPixels(pix, 0, w, 0, 0, w, h);
//        int [] resultPixes=OpenCVHelper.gray(pix,w,h);
//        Bitmap result = Bitmap.createBitmap(w,h, Bitmap.Config.RGB_565);
//        result.setPixels(resultPixes, 0, w, 0, 0,w, h);
//        imageView.setImageBitmap(result);

    }
}
