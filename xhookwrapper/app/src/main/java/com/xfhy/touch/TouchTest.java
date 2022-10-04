package com.xfhy.touch;

/**
 * Created by caikelun on 18/01/2018.
 */

public class TouchTest {
    private static final TouchTest ourInstance = new TouchTest();

    public static TouchTest getInstance() {
        return ourInstance;
    }

    private TouchTest() {
    }

    public synchronized void init() {
        System.loadLibrary("touch");
    }

    public native void start();
}
