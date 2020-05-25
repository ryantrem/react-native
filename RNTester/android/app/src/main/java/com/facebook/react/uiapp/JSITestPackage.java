package com.facebook.react.uiapp;

import androidx.annotation.NonNull;

import com.facebook.react.ReactPackage;
import com.facebook.react.bridge.NativeModule;
import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReactContextBaseJavaModule;
import com.facebook.react.uimanager.ViewManager;

import java.util.Arrays;
import java.util.Collections;
import java.util.List;

class JSITestModule extends ReactContextBaseJavaModule {
  static {
    System.loadLibrary("JSITest");
  }

  private static native void initialize(long jsiPtr);

  public JSITestModule(ReactApplicationContext reactContext) {
    super(reactContext);
  }

  @NonNull
  @Override
  public String getName() {
    return "JSITestModule";
  }

  @Override
  public void initialize() {
    super.initialize();

    JSITestModule.initialize(this.getReactApplicationContext().getJavaScriptContextHolder().get());
  }
}

class JSITestPackage implements ReactPackage {
  @NonNull
  @Override
  public List<NativeModule> createNativeModules(@NonNull ReactApplicationContext reactContext) {
    return Arrays.<NativeModule>asList(new JSITestModule(reactContext));
  }

  @NonNull
  @Override
  public List<ViewManager> createViewManagers(@NonNull ReactApplicationContext reactContext) {
    return Collections.emptyList();
  }
}
