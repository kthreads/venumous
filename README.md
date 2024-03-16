
# 🕷 Venumous
A Minecraft JNI Cheat Library (WIP).



## 📝 Examples
```cpp
CheatInteractor ct = { 0 };
ct.initJVMs(); // find jvms
ct.attachThread(); // attach to thread

ct.initMouse(); // init mouse class
ct.initKeyboard(); // init keyboard class
ct.initRobot(); // init robot class

printf("[*] Java VM -> 0x%p\n", ct.vm);

int keyCount = ct.keyCount(); // get key count
printf("you have %d Keys.\n", keyCount);

std::this_thread::sleep_for(std::chrono::milliseconds(5000));
ct.keyPress((jint)69); // press the 'e' key
```
