This demo is an example which introduces how to use flash driver and user boot mode.

Operation procedure:

1)Open IAR EWARM IDE, connect J-Link with PC and TOSHIBA M46B Evaluation Board, then click menu: file->open->workspace, choose 

  "Flash_Userboot.eww" to open demo project.

2)Click menu: Project->Options->Debugger->Download, then check "Override default .board file" option, click the path button to 

  choose file "Flash_Userboot\IAR\res\DemoA_for_M46B.board(DemoA_for_M46B.board)", then press OK to close Options window.

3)Click menu: Project->Download->Download file, then choose file "Flash_Userboot\IAR\res\DemoA.out", click "open", then the 

  IAR embedded flashloader will download DemoA to specified block.

4)Repeat 2) and 3), choose .board file "Flash_Userboot\IAR\res\DemoB.board", and file "Flash_Userboot\IAR\res\DemoB.out" to 

  download DemoB to specified block.

5)Click menu: Project->Options->Debugger->Download, then uncheck "Override default .board file" option, and press OK to close 
  
  option window.

6)Click menu: Project->Download->Download active application to download application "Flash_Userboot" to board.

7)Press RESET button, DemoA will run first (LED0 blinks and LED2 Always show).

8)Press RESET button while SW4 is turned on, and release SW4.
  After a while, system will reset automatically to run DemoB (LED1 blinks and LED3 Always show).