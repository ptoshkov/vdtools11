# VD Tools 11

Lightweight extension for Windows 11 virtual desktops with three core features:
- Start on leftmost virtual desktop
- Jump to arbitrary virtual desktop using keyboard shortcut
- Move window to adjacent desktop using keyboard shortcut


# Tutorial
1. Create four virtual desktops:
2. Make sure VD Tools 11 is running and the keyboard shortcuts are enabled:
3. Press CTRL + ALT + WIN + 4.

Virtual desktop 4 was brought in focus and a window from virtual desktop 4 is set as the active window.

4. Press SHIFT + CTRL + ALT + WIN + 1.

Virtual desktop 1 was brought in focus and the active window was moved to virtual desktop 1.

5. Press CTRL + ALT + WIN + →.

Virtual desktop 2 was brought in focus and the active window was moved to virtual desktop 2.


# FAQ
Q: Why does the option to start on the leftmost virtual desktop exist?\
A: Windows 11, unlike Windows 10, boots on the virtual desktop which was last in use. If you enable the option to start on the leftmost virtual desktop and you enabled VD Tools 11 autostart, you will get the same behavior as Windows 10.

Q: If a window is part of a snap group and I move it to another virtual desktop, will the whole group move with it?\
A: Yes, the whole group will move to the new virtual desktop, preserving the window layout.
