# VD Tools 11

Lightweight extension for Windows 11 virtual desktops with three core features:
- Start on leftmost virtual desktop
- Jump to arbitrary virtual desktop using keyboard shortcut
- Move window to adjacent desktop using keyboard shortcut


# Tutorial
1. Create four virtual desktops:
<img width="1027" height="169" alt="a1b508cf-e2f3-48b8-af71-98280277126f" src="https://github.com/user-attachments/assets/7497d703-7f5b-4537-80d9-f3b3f824ab41" />

2. Make sure VD Tools 11 is running and the keyboard shortcuts are enabled:
<img width="290" height="147" alt="3b81b598-f81f-4878-bf6e-2f9b20521d7b" src="https://github.com/user-attachments/assets/e9fe323c-50c6-45ac-b768-60c8e531008d" />

3. Press CTRL + ALT + WIN + 4.
![bf4180c7-0dcb-445c-8624-6f9aa51d6d88](https://github.com/user-attachments/assets/4a7bf078-556c-4745-911e-c7e5aee48dfe)
Virtual desktop 4 was brought in focus and a window from virtual desktop 4 is set as the active window.

4. Press SHIFT + CTRL + ALT + WIN + 1.
![bfc711e7-5473-44a0-b94d-bd4d4d4f09ae](https://github.com/user-attachments/assets/55741c76-ba28-4e34-828e-d5c425ea5684)
Virtual desktop 1 was brought in focus and the active window was moved to virtual desktop 1.

5. Press CTRL + ALT + WIN + →.![a1b213d0-fa74-45bb-840c-43cec4e2408e](https://github.com/user-attachments/assets/1b13cb8b-dc01-46c0-af88-650bf44539a4)
Virtual desktop 2 was brought in focus and the active window was moved to virtual desktop 2.


# FAQ
Q: Why does the option to start on the leftmost virtual desktop exist?\
A: Windows 11, unlike Windows 10, boots on the virtual desktop which was last in use. If you enable the option to start on the leftmost virtual desktop and you enabled VD Tools 11 autostart, you will get the same behavior as Windows 10.

Q: If a window is part of a snap group and I move it to another virtual desktop, will the whole group move with it?\
A: Yes, the whole group will move to the new virtual desktop, preserving the window layout.

Q: If VD Tools 11 is written in C++, why doesn't it make use of more C++ features?\
A: VD Tools 11 is a Petzold-style application, i.e. it uses mostly plain C.
