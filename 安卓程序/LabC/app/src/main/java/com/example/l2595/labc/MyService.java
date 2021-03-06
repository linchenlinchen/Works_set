package com.example.l2595.labc;

import android.app.Service;
import android.content.Intent;
import android.os.Binder;
import android.os.IBinder;
import android.util.Log;

public class MyService extends Service {
    private MyBinder myBinder = new MyBinder();
    Thread thread;
    class MyBinder extends Binder{
        public void startWork(){
            thread = new Thread(new Runnable() {
                @Override
                public void run() {
                    Log.d("MyService","Create a subThread,doing something");
                }
            });
            thread.start();
            Log.d("MyService","startWork executed");
        }
        public int getProgress(){
            Log.d("MyService","The subThreadID is " + thread.getId());
            Log.d("MyService","getProgress executed");
            return 0;
        }
    }

    public MyService() {
    }

    @Override
    public IBinder onBind(Intent intent) {
        // TODO: Return the communication channel to the service.
//        throw new UnsupportedOperationException("Not yet implemented");
        return myBinder;

    }
    @Override
    public void onCreate(){
        super.onCreate();
        Log.d("MyService","onCreate executed");
    }

    @Override
    public int onStartCommand(Intent intent,int flags,int startId){
        Log.d("MyService","onStartCommand executed");
        return super.onStartCommand(intent,flags,startId);
    }

    @Override
    public void onDestroy(){
        super.onDestroy();
        Log.d("MyService","onDestroy executed");
    }
}
