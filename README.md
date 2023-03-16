# FruitNinja
基于Cocos2d-x2.2.3游戏引擎开发


游戏效果:
实现两个场景并实现场景的切换（游戏的菜单界面和开始游戏界面）
实现触屏事件，并显示水果刀效果。
实现间断性的创建多种水果，并实现水果的上抛下落
实现水果被切后的落体运动
实现计分机制，通过计分机制判断是否结束游戏


模块设计:
本次游戏设计主要分为两个模块：场景绘制模块和游戏控制模块。各个模块之间作用如下：
场景绘制模块：主要负责游戏中两个静态场景的绘制，加载场景中的各个节点和节点动作
游戏控制模块：主要负责游戏进行状态的控制，负责游戏中各种动画的创建，动画播放，动画事件，和动画销毁等。

关键类介绍:
1)PrepareScene类——继承CCLayer
主要功能：负责菜单界面的创建和绘制，实现菜单界面的触控和菜单项选择
2)GameStart类——继承CCLayer
主要功能：实现游戏场景的创建和绘制，实现触控
3)FruitManager类——继承CCNode
主要功能：控制水果的循环上抛下落和旋转动作、水果被切后的落体、果汁效果、刀光效果

开发环境 vs2010

压缩包下载之后将class和resource文件夹替换到自己的项目中即可


部分截图



![image](https://user-images.githubusercontent.com/126632187/225497304-e584ab71-5b88-4fb0-92c8-ad1a42d2592d.png)
![image](https://user-images.githubusercontent.com/126632187/225496569-d050aef0-91c1-44c1-b362-9cfcc6cfa199.png)
![image](https://user-images.githubusercontent.com/126632187/225496646-7ba7da51-86e1-4298-a9fe-a47665e5251d.png)
![image](https://user-images.githubusercontent.com/126632187/225497239-ae065e2b-d1a7-45b9-8c70-9daadf31e50d.png)



