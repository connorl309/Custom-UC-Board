This demo is an example which introduces user how to use flash driver and auto swap mode.

Operation procedure:

1)Open IAR EWARM IDE, connect J-Link with PC and TOSHIBA M46B Evaluation Board, then click menu: file->open->workspace, choose 

  "Flash_Swp_A.eww" to open demo project.

2)Click menu: Project->Options->Debugger->Download, and then check "Override default .board file" option, click the path button to 

  choose file "Flash_Swp_A\IAR\res\Flash_Swp_A_for_M46B.board(Flash_Swp_A_for_M46B.board)", then press OK to close Options window.

3)Click menu: Project->Download->Download file, then choose file "Flash_Swp_A\IAR\res\Flash_Swp_A.out", click "open", then the 

  IAR embedded flashloader will download Flash_Swp_A to specified block.

4)Repeat 2) and 3), choose .board file "Flash_Swp_A\IAR\res\Flash_Swp_B_for_M46B.board(Flash_Swp_B_for_M46B.board)", and file "Flash_Swp_A\IAR\res\Flash_Swp_B.out" to 

  download Flash_Swp_B to specified block.

5)Click "reset" button on board. You will watch LED0 blinks.

6)Hold the SW4 turned on, then click "reset" button on board, you will watch LED2 light.(It indicates the swap is done)

7)Release SW4, You will watch LED1 blinks.

8)Hold the SW4 turned on, then click "reset" button on board, you will watch LED2 light.(It indicates the swap is release)

9)Release SW4, You will watch LED0 blinks.


Note:
<1> You can repeat step 6) to step 9) to display the demo again.
<2> You can create new Flash_Swp_A.out and Flash_Swp_B.out in Release mode of each project.(Due to the file size limited, the file can only be created in Release mode)


