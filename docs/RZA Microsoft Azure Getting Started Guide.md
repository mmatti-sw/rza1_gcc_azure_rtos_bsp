# RZA Microsoft Azure Getting Started Guide

## NetxDuo Demos

These demo projects demonstrate the network connectivity of NetXDuo library and the Azure IoT Cloud connectivity. These demos depend on the NetXDuo, ThreadX, FileX and Renesas RZ BSP libraries.To run the demos do the following.

1.  Set the target processor and target board in the mcu_board_select.h file. The demos support RZA1LU Stream-it Kit and RZA1H Display-it Kit.

2. Open the NetxDuo  RZ driver file: azure/ports/cortex_a9/gnu/inc/nx_driver_renesas_rz.h. Set the MAC address to match the board. Current demo configuration is shown below.
    ```
    #define ETHERNET_MAC_H              0x00000011
    #define ETHERNET_MAC_L              0x22334455
    ```

3. Build the rz_bsp.

4. Set the demo build configuration to the same target processor set in step 1. The supported build configuration RZA1H Debug and RZA1LU Debug.

5. Build the demo.

## GUIX Demos

These demo projects demonstrate the GUI on the RZA1H Display it kit and RZA1LU Stream-it kit. The LCD panel resolutions for the board are the following. These demos depend on the GUIX, ThreadX, and Reness RZ BSP libraries.

| Renesas Target Board | Resolution | Supported Color Depth |
| -------------------- | ---------- | --------------------- |
| RZA1H Display-it Kit | 800 x 480  | 16BPP, 24BPP, 32BPP   |
| RZA1LU Stream-it Kit | 480 x 272  | 16BPP                 |

*These setting reflect the hardware restrictions of the board*

1. Set the target processor and target board in the mcu_board_select.h file. The demos support RZA1LU Stream-it Kit and RZA1H Display-it Kit. This will select the appropriate touch driver and LCD configurations.

2. In addition the mcu_board_select.h includes selection of the GUIX Driver. Use one of the following settings. These settings reflect the design of the GUIX demo. 

   | Target Board          | TARGET_GUI_RGB565 | TARGET_GUI_RGB888 | TARGET_GUI_RGB8888 |
   | :-------------------- | :---------------: | :---------------: | :----------------: |
   | RZA1H Display-it Kit  |        no         |        yes        |         no         |
   | RZA1LU Display-it Kit |        yes        |        no         |         no         |

   

3. Build the rz_bsp.

4. There are two demos each is designed specifically for a target board. The Stream-it GUI demo project is the rza1lu_sample_guix_home_automation. The Display-it GUI project is the rza1h_sample_guix_home_automation. 



## USBX Demos

These demonstrated the USB MSC host and device class. These demos depend on the USBX, ThreadX, FileX, and Reness RZ BSP libraries. To run the demos do the following:

1. Set the target processor and target board in the mcu_board_select.h file. The demos support RZA1LU Stream-it Kit and RZA1H Display-it Kit.
2. Build the rz_bsp
3. Full Build of the USBX. The USBx RZ driver is located in the USB library changes in the target MCU or target board requires the USB to be compiled.
4. Set the demo build configuration to the same target processor set in step 1. The supported build configuration RZA1H Debug and RZA1LU Debug.
5. Build the demo.
