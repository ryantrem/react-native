#include <jni.h>
#include <jsi/jsi.h>
#include <android/log.h>
#include <sstream>

using namespace facebook;

namespace
{
    void log(const char *str)
    {
      __android_log_print(ANDROID_LOG_VERBOSE, "JSITest", "%s", str);
    }
}

extern "C" JNIEXPORT void JNICALL Java_com_facebook_react_uiapp_JSITestModule_initialize(JNIEnv* env, jclass clazz, jlong jsiPtr)
{
  auto& jsiRuntime = *reinterpret_cast<facebook::jsi::Runtime*>(jsiPtr);

  auto testFunction = jsi::Function::createFromHostFunction(jsiRuntime, jsi::PropNameID::forAscii(jsiRuntime, "testArrayBuffer"), 1, [](jsi::Runtime& runtime, const jsi::Value& thisValue, const jsi::Value* arguments, size_t count) -> jsi::Value
  {
      auto arrayBufferArg = arguments[0].asObject(runtime);
      bool isArrayBuffer = arrayBufferArg.isArrayBuffer(runtime);
      if (isArrayBuffer)
      {
        jsi::ArrayBuffer arrayBuffer = arrayBufferArg.getArrayBuffer(runtime);
        uint8_t* arrayBufferData = arrayBuffer.data(runtime);
        size_t arrayBufferSize = arrayBuffer.size(runtime);

        for (int i = 0; i < arrayBufferSize; i++)
        {
          uint8_t element = arrayBufferData[i];
          std::ostringstream message;
          message << "Element at index " << i << ": " << std::to_string(element);
          log(message.str().c_str());
          arrayBufferData[i] = element * 2;
        }
      }

      return nullptr;
  });
  jsiRuntime.global().setProperty(jsiRuntime, "testArrayBuffer", std::move(testFunction));
}
