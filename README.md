### crazyflie2.0_perching

#### 1.下载及编译

```bash
mkdir -p ~/crazyflie2.0_ws/src
cd ~/crazyflie2.0_ws/src
git clone https://github.com/JJGing/crazyflie2.0_perching.git
cd ..
rosdep install --from-path src --ignore-src
catkin_make
echo "source ~/crazyflie2.0_ws/devel/setup.bash" >> ~/.bashrc 
source ~/.bashrc
```

#### 2.配置
```bash
sudo groupadd plugdev 
```
##### 在/etc/udev/rules.d创建一个99-crazyradio.rules文件,并打开权限
```bash
sudo gedit /etc/udev/rules.d/99-crazyradiio.rules
```
##### 创建99-crazyradiio.rules文件，并写入以下代码
```
SUBSYSTEM=="usb",ATTRS{idVendor}=="1915", ATTRS{idProduct}=="7777",

MODE="0664",GROUP="plugdev" 
```

#### 3.测试
```bash
roscore
```
新开终端
```
rosrun crazyflie_tools scan
roslaunch crazyflie_demo teleop_ps3.launch uri:=radio://0/80/2M
```













