# DualECU_SPI_UART_Communication

## Abstract
This project focuses on the design and implementation of an advanced automotive embedded system. It features communication between two Electronic Control Units (ECUs) using SPI (Serial Peripheral Interface) and UART (Universal Asynchronous Receiver-Transmitter) protocols. The implementation is carried out on Tiva C microcontrollers, demonstrating efficient data handling and control processes crucial in automotive technologies.

## Team Members
- [Mohamed Khaled]: SPI Driver + task_readState
- [Mohamed Ahmed Badr]: SPI Driver + task_readSwitches
- [Mazen Ahmed]: OS + Integration of all tasks
- [Amal Amr]: UART Driver + task_uartMessage
- [Ahmed Khaled]: GPIO + Timer2 + task_switchStates + task_readSwitches

## System Architecture
The system's architecture consists of two ECUs implemented on Tiva C microcontrollers, each programmed to communicate over SPI and UART protocols. These ECUs perform specific control tasks, exchanging data in a synchronized manner. Detailed information on the hardware and software design, including Tiva C microcontroller specifics, schematics, and flowcharts, is provided in this section.

## Installation and Setup
Instructions for setting up and running the project, including:
- Hardware requirements (specifics about the Tiva C microcontroller setup)
- Software dependencies
- Steps to compile and deploy the code on Tiva C microcontrollers

## Usage
Detailed instructions on operating the system or executing the code, including necessary commands and procedures specific to the Tiva C microcontroller environment.

## Code Structure
An overview of the repository, emphasizing key components such as the UART and SPI drivers designed for the Tiva C microcontroller, along with other important modules or scripts.

## Acknowledgments
Acknowledgments to individuals, institutions, or resources that have contributed to the development of this project, with special mention to any support specific to the Tiva C microcontroller.
