package com.lurunfa.test;

import android.Manifest;
import android.annotation.TargetApi;
import android.app.Activity;
import android.content.Context;
import android.content.pm.PackageManager;
import android.hardware.camera2.CameraAccessException;
import android.hardware.camera2.CameraCharacteristics;
import android.hardware.camera2.CameraDevice;
import android.hardware.camera2.CameraManager;
import android.os.Build;
import android.os.Handler;
import android.os.HandlerThread;
import android.support.v4.app.ActivityCompat;
import android.util.Log;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

/**
 * Created by lurunfa on 2016/9/29.
 */

public class Test extends Activity {


    private class MySurface extends SurfaceView implements SurfaceHolder.Callback {
        private CameraManager mCameraManager;
        private Handler mHandler;
        private CameraDevice mCameraDevice;
        private String mCameraId;


        public MySurface(Context context) {

            super(context);
            initCamera();
        }

        @TargetApi(Build.VERSION_CODES.LOLLIPOP)
        private void initCamera() {
            Log.i("TAG", "initCamera");
            mCameraManager = (CameraManager) getSystemService(Context.CAMERA_SERVICE);
            HandlerThread handlerThread = new HandlerThread("Camera2");
            handlerThread.start();
            mHandler = new Handler(handlerThread.getLooper());
            try {
                mCameraId = "" + CameraCharacteristics.LENS_FACING_BACK;
                if (ActivityCompat.checkSelfPermission(Test.this, Manifest.permission.CAMERA) != PackageManager.PERMISSION_GRANTED) {
                    // TODO: Consider calling
                    //    ActivityCompat#requestPermissions
                    // here to request the missing permissions, and then overriding
                    //   public void onRequestPermissionsResult(int requestCode, String[] permissions,
                    //                                          int[] grantResults)
                    // to handle the case where the user grants the permission. See the documentation
                    // for ActivityCompat#requestPermissions for more details.
                    return;
                }
                mCameraManager.openCamera(mCameraId, new CameraDevice.StateCallback() {
                    @Override
                    public void onOpened(CameraDevice camera) {

                        mCameraDevice = camera;
                       // mCameraDevice.c

                    }

                    @Override
                    public void onDisconnected(CameraDevice camera) {

                    }

                    @Override
                    public void onError(CameraDevice camera, int error) {

                    }
                }, mHandler);
            }catch (CameraAccessException e){

            }
        }


        //View.calllback
        @Override
        public void surfaceCreated(SurfaceHolder holder) {


        }

        @Override
        public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {

        }

        @Override
        public void surfaceDestroyed(SurfaceHolder holder) {

        }
    }

}
