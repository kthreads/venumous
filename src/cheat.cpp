#include "cheat.h"
#include<Windows.h>
#include<iostream>
#include "../ext/Java.h"
#include<thread>
class GameClasses {
public:
    jclass Mouse;
    jclass Keyboard;
    jobject Robot;
};

class GameMethodIds {
public:
    jmethodID keyCount;
    jmethodID setCursorPosition;
    jmethodID keyPress;
};
class CheatInteractor {
public:
    JavaVM* vm;
    JNIEnv* env;
    GameClasses classes;
    GameMethodIds methodIds;
    void initJVMs();
    void attachThread();
    void initMouse();
    void initKeyboard();
    void initRobot();

    int keyCount();
    void setCursorPosition();
    void keyPress(jint code);
};


void CheatInteractor::initJVMs() {
    JNI_GetCreatedJavaVMs(&(this->vm), 1, nullptr);
}

void CheatInteractor::attachThread() {
    this->vm->AttachCurrentThread(reinterpret_cast<void**>(&(this->env)), nullptr);
}

void CheatInteractor::initMouse() {

    this->classes.Mouse = this->env->FindClass("org/lwjgl/input/Mouse");
    jmethodID cursorPos = this->env->GetStaticMethodID(this->classes.Mouse, "setCursorPosition", "(II)V");
    this->methodIds.setCursorPosition = cursorPos;
}

void CheatInteractor::initKeyboard() {
    this->classes.Keyboard = this->env->FindClass("org/lwjgl/input/Keyboard");
    jmethodID keyCountID = this->env->GetStaticMethodID(this->classes.Keyboard, "getKeyCount", "()I");
    this->methodIds.keyCount = keyCountID;
}
void CheatInteractor::initRobot() {
    auto robotPtr = this->env->FindClass("java/awt/Robot");
    auto constructor = this->env->GetMethodID(robotPtr, "<init>", "()V");
    this->classes.Robot = this->env->NewObject(robotPtr, constructor);
    jmethodID keyPress = this->env->GetMethodID(robotPtr, "keyPress", "(I)V");
    this->methodIds.keyPress = keyPress;
}
int CheatInteractor::keyCount() {
    if (!this->classes.Keyboard)
        return -1;
    if (!this->methodIds.keyCount)
        return -1;
    return (int)this->env->CallStaticIntMethod(this->classes.Keyboard, this->methodIds.keyCount);
}

void CheatInteractor::setCursorPosition() {
    // still learning about passing multiple args so implementation will be done in the future hopefully.
    if (!this->classes.Mouse)
        return;
    if (!this->methodIds.setCursorPosition)
        return;
}
void CheatInteractor::keyPress(jint code) {
    if (!this->classes.Robot)
        return;
    if (!this->methodIds.keyPress)
        return;
    
    this->env->CallVoidMethodA(this->classes.Robot, this->methodIds.keyPress, (jvalue*)&code);
}
void cheat::startCheat() {
    CheatInteractor ct = { 0 };
    ct.initJVMs();
    ct.attachThread();

    ct.initMouse();
    ct.initKeyboard();
    ct.initRobot();
    printf("[*] Java VM -> 0x%p\n", ct.vm);
    int keyCount = ct.keyCount();
    printf("you have %d Keys.\n", keyCount);
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    ct.keyPress((jint)69);
}

void cheat::makeConsole() {
    AllocConsole();
    freopen_s(&consoleFile, "CONOUT$", "w", stdout);
}

void cheat::startCheatThread() {
    CreateThread(NULL, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(startCheat), NULL, NULL, NULL);
}