# ARM_Repo - Embedded Systems Drivers for ARM Cortex-M

![ARM Cortex-M](https://img.shields.io/badge/ARM-Cortex--M-blue) 
![STM32](https://img.shields.io/badge/STM32F401CC-MCU-green)
![PlatformIO](https://img.shields.io/badge/PlatformIO-Compatible-orange)

A collection of embedded system drivers for ARM Cortex-M microcontrollers, specifically targeting STM32F401CC.

## 📁 Repository Structure
ARM_Repo/

├── COTS/ # Commercial Off-The-Shelf components

│ ├── HAL/ # Hardware Abstraction Layer drivers

│ ├── LIB/ # Library files

│ └── MCAL/ # Microcontroller Abstraction Layer drivers

└── Workspace/ # Working copies of the drivers


## 🚀 Key Features

- **Modular driver design** (each with include/src/test)
- **PlatformIO support** for all projects
- **Standardized types** (STD_TYPES.h)
- **Configuration headers** for each driver
- **Ready for testing** with dedicated test directories

## 💻 Supported Drivers

### MCAL Layer
- GPIO Driver
- NVIC Driver (Interrupt Controller)
- RCC Driver (Clock Control)
- SysTick Driver
- UART Driver
- Scheduler

### HAL Layer
- LED Driver
- Switch Driver
- LCD Driver
- UART with Interrupts

