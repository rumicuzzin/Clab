# Clab MTRX2700 C Lab for STM32F3 Discovery Board

## Project Overview

---

## Team Members
- **Will Rumi** - Exercise 3: Timers  
- **Audrey** - Exercise 2: Serial  
- **James Blisset** - Exercise 2: Serial  
- **Marcus** - Exercise 1: Digital I/O

---

## Table of Contents
- [Project Overview](#project-overview)
- [Team Members](#team-members)
- [Exercise 1: Digital I/O](#exercise-1-digital-io)
  - [Part a) Basic Functionality](#part-a-basic-functionality)
  - [Part b)](#part-b)
  - [Part c)](#part-c)
  - [Part d) Advanced Functionality](#part-d-advanced-functionality)
  - [Discussion Points](#discussion-points)
- [Exercise 2: Serial Interface](#exercise-2-serial-interface)
  - [Part a) Basic Functionality](#part-a-basic-functionality-1)
  - [Part b)](#part-b-1)
  - [Part c)](#part-c-1)
  - [Part d) Advanced Functionality](#part-d-advanced-functionality-1)
  - [Discussion Points](#discussion-points-1)
- [Exercise 3: Timer Interface](#exercise-3-timer-interface)
  - [Part a) Basic Functionality](#part-a-basic-functionality-2)
  - [Part b)](#part-b-2)
  - [Part c) Advanced Functionality](#part-c-advanced-functionality)
  - [Discussion Points](#discussion-points-2)
- [Exercise 4: Integration Task](#exercise-4-integration-task)
  - [Discussion Points](#discussion-points-3)
- [Installation](#installation)
- [Usage](#usage)
- [Contributing](#contributing)

---

## Exercise 1: Digital I/O

### Part a) Basic Functionality

### Part b)

### Part c)

### Part d) Advanced Functionality

### Discussion Points

---

## Exercise 2: Serial Interface

### Part a) Basic Functionality

### Part b)

### Part c)

### Part d) Advanced Functionality
Features: 
- **Serial Communication**: 115200 baud UART with interrupt-driven RX
- **LED Control**: GPIO interface for 8 LEDs (Port E)
- **Command Framework**: Buffered input system with `processBuffer` callback
- **Dual-buffer receive system**: With interrupt handling and buffer switching

Functions: 
- `SerialInitialise()`:  
  Initializes **USART1**, sets the baud rate, configures GPIO pins for alternate functions, and enables interrupts. Also assigns a user-defined terminator character and a callback function to process received data.

- `USART1_EXTI25_IRQHandler()`:  
  Interrupt handler that gets triggered on receiving data over USART1.  
  It:
  - Reads incoming characters into the active buffer.
  - Checks for the termination character.
  - Swaps to the alternate buffer.
  - Calls the user-defined callback (`processBuffer`) to process the full buffer.

- `SerialOutputString()`:  
  Sends a **null-terminated string** over USART1, one character at a time, using polling (waits for transmit buffer to be ready).

- 'processBuffer()': User-defined RX callback — processes the inactive buffer once full or terminated

### Discussion Points

---

## Exercise 3: Timer Interface

### Part a) Basic Functionality
Overview:
This module demonstrates how to implement a **software timer system** on the STM32F3 Discovery board using **Timer 2** to generate periodic interrupts that invoke a user-defined **callback function**.

The core functionality involves using a timer interrupt to trigger a function (such as toggling LEDs) at a configurable time interval. It showcases function pointers, NVIC interrupt configuration, and low-level peripheral access on STM32.

Functions:
`enable_clocks()`
`initialise_board()`
`timer_init(uint32_t time_period_ms, callback_t cb)`

### Part b)

### Part c) Advanced Functionality

### Discussion Points

---

## Exercise 4: Integration Task

### Discussion Points

---

## Installation
Instructions for setting up the project locally.

---

## Usage
How to use the project after installation.

---

## Contributing
How to contribute to the project.

