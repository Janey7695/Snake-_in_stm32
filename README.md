# Snake-_in_stm32
A SnakeGame in stm32f103
# About The Project 简介
一个运行在stm32f103c8t6上的贪吃蛇游戏，实现了最基本最简单的贪吃蛇逻辑流程。
# Getting Started 开始
## Prerequisites 开始前的准备
本例程运行在stm32f103c8t6上，通过一块0.96'的oled屏（SPI）显示。</br>
### Materials 物料准备
* keil5_ARM开发环境  
* STM32F103最小系统板 *1  
* 0.96'oled(128*64)drive by SSD1306 （SPI）
* 按键开关*4  
* EC11旋钮编码器*1
* AT24C32(也可是其它容量的E2PROM)*1  
### Line connection 线路连接
#### 按键连接
GND<----UP    Button---->PA1  
GND<----DOWN  Button---->PA2  
GND<----RIGHT Button---->PA3  
GND<----LEFT  Button---->PA0  
EC11_A---->PB5  
EC11_B---->GND  
EC11_C---->PB8  
EC11_1---->PB9  
EC11_2---->GND 
#### oled屏连接(SPI协议)
GND---->GND  
VCC---->VCC  
D0---->PA5  
D1---->PA7  
RST---->PB0  
DC---->PB1  
CS---->PA4

## Installation 下载
1. 获取源码  
`git clone https://github.com/Janey7695/Snake-_in_stm32.git`
2. 进入`USER`目录，打开keil工程`Template.uvprojx`并编译
3. 通过`ST-LINK`或其它仿真器下载程序到stm32f103上
## Usage 使用
### 控制
* EC11按下是确定  
* EC11左右旋转  
->在菜单：切换选项  
->在游戏中：改变游戏难度
* 4个按键分别控制上下左右
### 已实现功能
* 正常的“移动、吃点、加分增长、碰撞死亡检测”
* 保存最高分，并且可以查询最高分
* 10级难度可调

## TODO 计划功能
* 保存游戏进度，断电重启后可复原
* 增加更多模式
* 可联机模式