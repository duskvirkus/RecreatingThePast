# 25 Carrés

A series originally created by Vera Molnár. Recreated in openFrameworks by Violet Graham.

![Image shows a work by Vera Molnár on the left. With the recreation on the right.](./assets/comparison-01.png)

![Image shows a work by Vera Molnár on the left. With the recreation on the right.](./assets/comparison-02.png)

![Screenshot from application running with controls showing.](./assets/recreation/recreation-03.png)

Required addons:

- ofxGui (included in openFrameworks)
- [ofxMidi](https://github.com/danomatika/ofxMidi)
- [ofxLaunchControllers](https://github.com/violetcraze/ofxLaunchControllers) (my fork is working)

Launch controller not required to run program. The gui has full functionality and can be brought up with any key press.

## About

Started with [ofLinuxVSCodeTemplate](https://github.com/violetcraze/ofLinuxVSCodeTemplate)

Project is designed to be used on Linux with vscode. Use the openFrameworks project generator to update for other systems.

### Setup

0. Install clang-format (if not installed already)
1. Open in vscode
2. Click button `Open Workspace`
3. Run command `Extensions: Configure Recommended Extensions (Workspace Folder)` (you can bring up command pallet by using `ctrl + shift + p` and type it in)
4. Start using!

### Tasks

- build (builds project using make)
- run (runs compiled project)
- kill (will kill program if it's running)

`ctrl + shift + b` will run kill, build, and run (this happens by default on save)

Read more about tasks on [vscode website](https://code.visualstudio.com/docs/editor/tasks).
