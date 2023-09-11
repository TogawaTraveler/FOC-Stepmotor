# FOC-Stepmotor
步进电机foc+弱磁驱动方案
包括立创EDA原理图PCB，keil固件，Qt上位机工程
忘提交串口指令了，在这里补充下：

P(+/-)(XXXXXXX)E 	(位置帧头)(增/减)(7位 16384为一圈)(帧尾)   例：P+016384E

L(XXXXX)E	 	      (定位帧头)(0-16384 就近定位到指定角度)(帧尾)  例：L05800E

RESET		  	      (重置  清除转动过的累计角度)

V(+/-)(XXXX)E	  	(速度帧头)(增/减)(4位 每毫秒走过编码器角度)(帧尾) 例：V+1000E

P(+/-)(XXXXXXX)T(XXXX)E  	(位置帧头)(增/减)(7位 16384为一圈)(限制)(最大速度) P+0016384T5000E
                          (角度在数量上必须大于时间，即最小速度3.6rpm)
                          
S(+/-)(xx)E	  	  (低速模式速度设置)速度为高速模式的1/25

INERTIA(XXX)E 	  设置转动惯量 例：INERTIA005E  转动惯量为5即校准完成的默认值

UPDATA	 	  	    更新零点和转动惯量(先完成设置再更新参数)


还未完成的部分：
  拨码开关的模式选择 我也不知道该有什么模式
  自动配置参数  没找到啥理论
