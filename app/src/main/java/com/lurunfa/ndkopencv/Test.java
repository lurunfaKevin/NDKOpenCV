package com.lurunfa.ndkopencv;

import android.app.Activity;
import android.os.Bundle;
import android.widget.TextView;

/**
 * Created by lurunfa on 2016/9/27.
 */

public class Test extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.test);
        TextView tv = (TextView) findViewById(R.id.text_view);
        tv.setText(Hello.stringFromJNI());
    }
    static {
        System.loadLibrary("hello-jni");
        System.loadLibrary("openCVLibrary310");
    }


}
