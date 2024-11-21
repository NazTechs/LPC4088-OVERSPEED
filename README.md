LPC4088-OVERSPEED: Turbine Overspeed Protection System
======================================================

Overview
--------

The LPC4088-OVERSPEED project provides a microcontroller-based solution to safeguard turbines from overspeed conditions. Utilizing the NXP LPC4088 microcontroller, this system monitors turbine speed and initiates protective measures when necessary.

![image](https://github.com/user-attachments/assets/ac8ee334-62c8-4adf-a148-c013a9c6bae5)

Features
--------

-   **Real-Time Speed Monitoring**: Continuously tracks turbine rotational speed to detect overspeed scenarios promptly.
-   **Configurable Parameters**: Allows customization of overspeed thresholds and response actions to suit specific turbine requirements.
-   **User Interface**: Includes an LCD display and keypad for user interaction, enabling parameter adjustments and status monitoring.
-   **Data Logging**: Records events and system statuses for analysis and maintenance purposes.
-   **Communication Interfaces**: Supports UART and Modbus protocols for integration with external systems and remote monitoring.
-   
![image](https://github.com/user-attachments/assets/41ed2497-850b-4c1a-b5d2-8552e88502c9)

Repository Structure
--------------------

-   `config_analog_output/`: Configuration files for analog output settings.
-   `config_modbus/`: Configuration files for Modbus communication.
-   `config_speed_input/`: Settings related to speed input parameters.
-   `monitor_system_status/`: Modules for monitoring overall system health.
-   `FLASHMNG.c` and `FLASHMNG.h`: Flash memory management routines.
-   `FPGA.c` and `FPGA.h`: Interfaces for FPGA communication.
-   `LCD.c` and `LCD.h`: Drivers for LCD display operations.
-   `MAIN.c`: Main program entry point.
-   `MODBUSMNG.c` and `MODBUSMNG.h`: Modbus protocol management.
-   `OSPMNG.c` and `OSPMNG.h`: Overspeed protection management logic.
-   `README.md`: Project documentation.
-   `RTC.c` and `RTC.h`: Real-Time Clock functionalities.
-   `SSD1963.c` and `SSD1963.h`: Drivers for the SSD1963 LCD controller.
-   `UART_LPC4088.h`: UART communication definitions.
-   `timer.c` and `timer.h`: Timer functionalities for scheduling and delays.

Getting Started
---------------

1.  **Prerequisites**:

    -   NXP LPC4088 microcontroller development board.
    -   Keil MDK or a compatible ARM development environment.
2.  **Cloning the Repository**:
3.  
    `git clone https://github.com/NazTechs/LPC4088-OVERSPEED.git`

4.  **Building the Project**:

    -   Open the project in your development environment.
    -   Compile the source code to generate the firmware binary.
5.  **Programming the Microcontroller**:

    -   Use a suitable programmer to upload the firmware to the LPC4088 microcontroller.

Usage
-----

-   **System Initialization**: Upon powering up, the system initializes peripherals and enters monitoring mode.
-   **Parameter Configuration**: Use the keypad and LCD interface to set overspeed thresholds and other parameters.
-   **Monitoring**: The system continuously monitors turbine speed and triggers protective actions if overspeed is detected.
-   **Data Logging**: Events and statuses are logged for future analysis.

Contributing
------------

Contributions are welcome! Please submit issues or pull requests to enhance the functionality or documentation of this project.

License
-------

This project is licensed under the MIT License. See the LICENSE file for details.

Acknowledgments
---------------

Special thanks to the open-source community for providing valuable resources and support in the development of this project.
