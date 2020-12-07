# 王泽宇\_181250148\_操作系统实验2



### 文件目录结构

| 目录/文件名          | 说明                           |
| -------------------- | ------------------------------ |
| bin                  | 可执行程序及其运行环境所在目录 |
| Elevator             | 电梯程序工程目录               |
| ElevatorControlPanel | 电梯控制面板工程目录           |
| StoreyControlPanel   | 楼层控制面板工程目录           |
| linux-release        | Linux可执行文件的构建目录      |
| windows-release      | Windows可执行文件的构建目录    |
| demo.mp4             | 系统运行效果演示视频           |
| readme.md            | 实验报告（本文件）             |



### 实验名称

电梯模拟



### 实验目的

编写程序，实现对3层楼房中电梯运行逻辑的模拟。系统中包含：

1. 电梯进程，实现对电梯本身运行逻辑的模拟；
2. 电梯控制面板进程，实现电梯内控制面板的模拟，包含电梯所在楼层、运行方向等信息的显示，以及楼层、开关门按钮的响应；
3. 楼层控制面板进程，实现楼层控制面板的模拟，包含电梯所在楼层、运行方向等信息的显示，以及上下行按钮的响应。

其中电梯控制面板和楼层控制面板进程都应包含2个线程，分别负责信息显示和按钮响应。



### 实验环境

本次实验采用C++语言与Qt图形界面框架，使用Qt Creator绘制界面并编写代码，通过Qt的不同构建套件可构建Windows和Linux平台下的可执行程序。



### 实验过程

#### 系统总体设计

系统共包含5个进程，其中3个进程分别为1、2、3层的楼层电梯控制面板进程。因此定义以下3个互相独立的子程序：

| 程序名               | 说明                                                       |
| -------------------- | ---------------------------------------------------------- |
| Elevator             | 电梯程序，实现电梯运行逻辑，发送电梯状态信息，响应控制请求 |
| ElevatorControlPanel | 电梯控制面板程序，显示电梯运行状态信息，发送控制请求       |
| StoreyControlPanel   | 楼层控制面板程序，显示电梯运行状态信息，发送控制请求       |

进程之间采用Shared Memory形式通信。定义以下进程间共享的变量：

| 变量名               | 写者                                               | 读者                                     | 说明                   |
| -------------------- | -------------------------------------------------- | ---------------------------------------- | ---------------------- |
| sharedFloor          | Elevator                                           | ElevatorControlPanel, StoreyControlPanel | 电梯当前所在楼层       |
| sharedStatus         | Elevator                                           | ElevatorControlPanel, StoreyControlPanel | 电梯当前运行状态       |
| sharedDirection      | Elevator                                           | ElevatorControlPanel, StoreyControlPanel | 电梯当前运行方向       |
| sharedRequestTo[3]   | ElevatorControlPanel                               | Elevator                                 | 到达某一楼层的控制请求 |
| sharedRequestUp[3]   | StoreyControlPanel                                 | Elevator                                 | 在某一层上行的控制请求 |
| sharedRequestDown[3] | StoreyControlPanel                                 | Elevator                                 | 在某一层下行的控制请求 |
| sharedOpen           | ElevatorControlPanel, StoreyControlPanel, Elevator | Elevator                                 | 开门的控制请求         |
| sharedClose          | ElevatorControlPanel, Elevator                     | Elevator                                 | 关门的控制请求         |

以上共享变量均由Elevator进程创建，并由其他进程连接。

将电梯视为状态机，其状态由floor、status和direction共3个变量定义。其中floor取值为1至3，表示电梯当前所在楼层。status取值范围及其说明如下：

| 取值 | 宏定义标识符   | 说明                           |
| ---- | -------------- | ------------------------------ |
| 0    | ELEVATOR_STOP  | 电梯停止在某层                 |
| 1    | ELEVATOR_RUN   | 电梯在某两层之间运行           |
| 2    | ELEVATOR_OPEN  | 电梯门正在打开                 |
| 3    | ELEVATOR_CLOSE | 电梯门正在关闭                 |
| 4    | ELEVATOR_WAIT  | 电梯门已打开，正在等待乘员进出 |

direction取值范围及其说明如下：

| 取值 | 宏定义标识符   | 说明       |
| ---- | -------------- | ---------- |
| 0    | DIRECTION_NONE | 无运行方向 |
| 1    | DIRECTION_UP   | 电梯上行   |
| 2    | DIRECTION_DOWN | 电梯下行   |

具体的状态转移逻辑稍后说明。



#### 共享变量相关函数编写

定义readSharedInt()、writeSharedInt()和createSharedInt()共3个全局函数，用于读写和创建进程间共享变量。在读写时需要对共享变量加锁。

```C++
void readSharedInt(QSharedMemory *src, int& dst){
    if (!src->isAttached() && !src->attach()){
        qDebug() << tr("Attach Error: ") << src->errorString();
        dst = -1;
        return;
    }
    QBuffer buffer;
    QDataStream bufferStream(&buffer);
    src->lock();
    buffer.setData(static_cast<const char *>(src->constData()), src->size());
    buffer.open(QBuffer::ReadWrite);
    bufferStream >> dst;
    src->unlock();
}

void writeSharedInt(int& src, QSharedMemory* dst){
    if (!dst->isAttached() && !dst->attach()){
        qDebug() << tr("Attach Error: ") << dst->errorString();
        return;
    }
    QBuffer buffer;
    QDataStream bufferStream(&buffer);
    buffer.open(QBuffer::ReadWrite);
    bufferStream << src;
    int size = buffer.size();
    dst->lock();
    char *to = static_cast<char *>(dst->data());
    const char *from=buffer.data().constData();
    memcpy(to,from,size);
    dst->unlock();
}

void createSharedInt(int& src, QSharedMemory* dst){
    if (dst->attach()) dst->detach();
    if (!dst->create(sizeof(int))) qDebug() << tr("Create Error: ") << dst->errorString();
    writeSharedInt(src,dst);
}
```

以上函数在Elevator、ElevatorControlPanel和StoreyControlPanel程序中都有调用。



#### Elevator程序编写

Elevator程序逻辑在MainWindow类中实现，其数据成员包括图形界面中相关控件的指针、上述所有共享变量的指针，以及这些变量的本地版本。

```C++
private:
    Ui::MainWindow *ui;
    QSharedMemory *sharedFloor;
    QSharedMemory *sharedStatus;
    QSharedMemory *sharedDirection;
    QSharedMemory *sharedRequestUp[3];
    QSharedMemory *sharedRequestDown[3];
    QSharedMemory *sharedRequestTo[3];
    QSharedMemory *sharedOpen;
    QSharedMemory *sharedClose;

    QLabel *labelFloor[3];
    QLabel *labelRequestTo[3];
    QLabel *labelRequestUp[3];
    QLabel *labelRequestDown[3];

    int floor;
    int status;
    int direction;
    int requestUp[3];
    int requestDown[3];
    int requestTo[3];
    int open;
    int close;
```

同时，定义数据成员nextTime，用于实现电梯状态循环，其功能稍后说明。

```C++
    int nextTime;
```

在MainWindow类的默认构造函数中，首先对各数据成员赋初值，并初始化各共享变量的指针，而后通过createSharedInt()创建各共享变量。

```C++
    createSharedInt(floor,sharedFloor);
    createSharedInt(status,sharedStatus);
    createSharedInt(direction,sharedDirection);
    for (int i = 0;i < 3;i++) {
        int val = 0;
        createSharedInt(val,sharedRequestUp[i]);
        createSharedInt(val,sharedRequestDown[i]);
        createSharedInt(val,sharedRequestTo[i]);
    }
    createSharedInt(open,sharedOpen);
    createSharedInt(close,sharedClose);
```

而后通过一个QTimer对象定时生成timeout信号，将timeout信号与成员函数repeatExec()相连，即实现了对repeatExec()的定时循环调用。将QTimer对象生成timeout信号的时间间隔设为50ms，即每秒调用20次repeatExec()。

```C++
    QTimer *timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,&MainWindow::repeatExec);
    timer->start(50);
```

成员函数repeatExec()即电梯状态循环函数，实现了电梯运行逻辑。其中数据成员nextTime表示距离下一次状态转移还有多少时间间隔，其处理方式类似IPv4 Packet中的TTL，在每一轮循环中对其自减，若其值为0则进行下一次状态转移。通过nextTime实现了电梯各状态之间的定时转移。



在函数repeatExec()中，当nextTime == 0，即需要进行状态转移时，首先通过readSharedInt()从各共享变量读取控制请求。

```C++
        for (int i = 0;i < 3;i++){
            readSharedInt(sharedRequestTo[i],requestTo[i]);
            readSharedInt(sharedRequestUp[i],requestUp[i]);
            readSharedInt(sharedRequestDown[i],requestDown[i]);
        }
```

而后对当前状态分类处理。当状态为ELEVATOR_STOP时，若存在开门请求，则转移至状态ELEVATOR_OPEN。否则扫描所有到达楼层和上下行请求，若存在请求，则若请求楼层与电梯所在楼层相同，则转移至状态ELEVATOR_OPEN，否则转移至状态ELEVATOR_RUN，并对direction赋值。若不存在到达楼层和上下行请求，则保持ELEVATOR_STOP状态，无需转移。

```C++
        case ELEVATOR_STOP:
            readSharedInt(sharedOpen,open);
            if (open == 1){
                status = ELEVATOR_OPEN;
                nextTime = 10;
                int val = 0;
                writeSharedInt(val, sharedOpen);
                break;
            }
            for (int i = 0;i < 3;i++){
                if (requestTo[i] == 1 || requestUp[i] == 1 || requestDown[i] == 1){
                    if (i + 1 == floor){
                        status = ELEVATOR_OPEN;
                        nextTime = 10;
                        break;
                    }
                    status = ELEVATOR_RUN;
                    nextTime = 20;
                    direction = i + 1 > floor?DIRECTION_UP:DIRECTION_DOWN;
                    break;
                }
            }
            break;
```

当状态为ELEVATOR_RUN时，先更新floor的值。若floor为1或3，即电梯在底楼或顶楼，则对direction赋值。若当前楼层存在到达、上下行请求，则转移至状态ELEVATOR_OPEN。否则扫描当前运行方向上后续楼层的到达和上下行请求，若存在请求，则保持状态ELEVETOR_RUN，且重设nextTime，否则转移到状态ELEVATOR_STOP，将direction设为DIRECTION_NONE。

```C++
        case ELEVATOR_RUN:
            floor += direction == DIRECTION_UP?1:-1;
            if (floor == 1) direction = DIRECTION_UP;
            if (floor == 3) direction = DIRECTION_DOWN;
            if (requestTo[floor - 1] == 1 || (direction == DIRECTION_UP && requestUp[floor - 1] == 1) || (direction == DIRECTION_DOWN && requestDown[floor - 1] == 1)){
                status = ELEVATOR_OPEN;
                nextTime = 10;
                break;
            }
            if (direction == DIRECTION_UP){
                bool next = 0;
                for (int i = floor;i < 3;i++) if (requestTo[i] == 1 || requestUp[i] == 1  || requestDown[i] == 1) {
                    next = 1;
                    break;
                }
                if (next == 0){
                    status = ELEVATOR_STOP;
                    direction = DIRECTION_NONE;
                    break;
                }
                status = ELEVATOR_RUN;
                nextTime = 20;
            }
            else {
                bool next = 0;
                for (int i = floor - 2;i > -1;i--) if (requestTo[i] == 1 || requestUp[i] == 1 || requestDown[i] == 1) {
                    next = 1;
                    break;
                }
                if (next == 0){
                    status = ELEVATOR_STOP;
                    direction = DIRECTION_NONE;
                    break;
                }
                status = ELEVATOR_RUN;
                nextTime = 20;
            }
            break;
```

当状态为ELEVATOR_OPEN时，转移到状态ELEVATOR_WAIT。同时将开关门请求的共享变量设为0，即重置开关门状态，开始接收开关门请求。

```C++
        case ELEVATOR_OPEN:
            status = ELEVATOR_WAIT;
            int val = 0;
            writeSharedInt(val, sharedOpen);
            writeSharedInt(val, sharedClose);
            nextTime = 20;
            break;
```

当状态为ELEVATOR_WAIT时，转移到状态ELEVATOR_CLOSE。

```C++
        case ELEVATOR_WAIT:
            status = ELEVATOR_CLOSE;
            nextTime = 10;
            break;
```

当状态为ELEVATOR_CLOSE时，状态转移逻辑与ELEVATOR_RUN类似，但无需判断当前楼层是否存在请求。同时还需注意，在ELEVATOR_CLOSE状态下，direction可能为DIRECTION_NONE，此时转移为状态ELEVATOR_STOP，使其重新扫描所有到达楼层和上下行请求。

```C++
        case ELEVATOR_CLOSE:
            if (direction == DIRECTION_UP){
                bool next = 0;
                for (int i = floor;i < 3;i++) if (requestTo[i] == 1 || requestUp[i] == 1 || requestDown[i] == 1) {
                    next = 1;
                    break;
                }
                if (next == 0){
                    status = ELEVATOR_STOP;
                    direction = DIRECTION_NONE;
                    break;
                }
                status = ELEVATOR_RUN;
                nextTime = 20;
            }
            else if (direction == DIRECTION_DOWN){
                bool next = 0;
                for (int i = floor - 2;i > -1;i--) if (requestTo[i] == 1 || requestUp[i] == 1 || requestDown[i] == 1) {
                    next = 1;
                    break;
                }
                if (next == 0){
                    status = ELEVATOR_STOP;
                    direction = DIRECTION_NONE;
                    break;
                }
                status = ELEVATOR_RUN;
                nextTime = 20;
            }
            else {
                status = ELEVATOR_STOP;
                direction = DIRECTION_NONE;
                break;
            }
            break;
```

以上所有状态转移时都需要重设nextTime，nextTime值与状态转移目标的关系如下：

| 状态转移目标   | nextTime设定 | 说明                           |
| -------------- | ------------ | ------------------------------ |
| ELEVATOR_STOP  | 0            | 持续扫描控制请求，直到出现请求 |
| ELEVATOR_RUN   | 20           | 电梯在两层之间的运行时长为1秒  |
| ELEVATOR_OPEN  | 10           | 电梯开门所用时长为0.5秒        |
| ELEVATOR_CLOSE | 10           | 电梯关门所用时长为0.5秒        |
| ELEVATOR_WAIT  | 20           | 电梯等待时间默认为1秒          |

对状态分类处理完成后，将更新后的状态信息写入共享变量。

```C++
        writeSharedInt(floor,sharedFloor);
        writeSharedInt(status, sharedStatus);
        writeSharedInt(direction, sharedDirection);
```



当nextTime != 0，即不需要进行状态转移时，将nextTime自减。同时还需要考虑一种特殊情况，若当前状态为ELEVATOR_WAIT，则读取共享变量并扫描开关门请求。若存在开门请求，则将nextTime重设为20，即重置电梯等待时间，并将共享变量都写为0。若存在关门请求，则将nextTime设为0，即使电梯等待时间立即结束，并将共享变量写为0。当开关门请求同时存在时，开门请求优先处理。

```C++
        nextTime--;
        if (status == ELEVATOR_WAIT){
            readSharedInt(sharedOpen,open);
            readSharedInt(sharedClose,close);
            if (open == 1){
                nextTime = 20;
                int val = 0;
                writeSharedInt(val, sharedOpen);
                writeSharedInt(val, sharedClose);
            }
            else if (close == 1){
                nextTime = 0;
                int val = 0;
                writeSharedInt(val, sharedOpen);
                writeSharedInt(val, sharedClose);
            }
        }
```



Elevator程序即编写完成。



#### ElevatorControlPanel程序编写

Elevator程序使用两个线程实现，主线程读取电梯状态共享变量并显示在图形界面，子线程响应按钮并写入控制请求共享变量，两者逻辑分别在MainWindow类和ThreadOperation类实现。

MainWindow类的数据成员包括图形界面中相关控件的指针、电梯状态共享变量的指针，以及这些变量的本地版本。

```C++
private:
    Ui::MainWindow *ui;
    QSharedMemory *sharedFloor;
    QSharedMemory *sharedStatus;
    QSharedMemory *sharedDirection;

    QPushButton *pushButtonTo[3];

    int floor;
    int status;
    int direction;
```

同时，定义数据成员buttonToDown[3]，记录3个楼层按钮是否已被按下。

```C++
    bool buttonToDown[3];
```

在MainWindow类的默认构造函数中，首先对各数据成员赋初值，并初始化各共享变量的指针，而后创建threadOperation线程，在该线程中运行objectOperation，并连接相关信号和函数。而后通过QTimer对象每秒调用20次repeatExec()。

```C++
    QThread* threadOperation;
    ThreadOperation* objectOperation;
    threadOperation = new QThread();
    objectOperation = new ThreadOperation();
    objectOperation->moveToThread(threadOperation);
    connect(threadOperation,&QThread::finished,threadOperation,&QObject::deleteLater);
    connect(ui->pushButtonFloor1,&QPushButton::clicked,this,[&](){this->buttonToClicked(1);});
    connect(ui->pushButtonFloor2,&QPushButton::clicked,this,[&](){this->buttonToClicked(2);});
    connect(ui->pushButtonFloor3,&QPushButton::clicked,this,[&](){this->buttonToClicked(3);});
    connect(this,&MainWindow::to,objectOperation,&ThreadOperation::to);
    connect(this,&MainWindow::toCancel,objectOperation,&ThreadOperation::toCancel);
    connect(ui->pushButtonOpen,&QPushButton::clicked,this,&MainWindow::buttonOpenClicked);
    connect(this,&MainWindow::open,objectOperation,&ThreadOperation::open);
    connect(ui->pushButtonClose,&QPushButton::clicked,this,&MainWindow::buttonCloseClicked);
    connect(this,&MainWindow::close,objectOperation,&ThreadOperation::close);
    threadOperation->start();

    QTimer *timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,&MainWindow::repeatExec);
    timer->start(50);
```

当楼层按钮被按下时，执行函数MainWindow::buttonToClicked()，判断楼层按钮是否已被按下，若无则将对应的buttonToDown设为1，并发送to信号。

```C++
void MainWindow::buttonToClicked(int floor){
    pushButtonTo[floor - 1]->setChecked(1);
    if (!buttonToDown[floor - 1]){
        buttonToDown[floor - 1] = 1;
        emit to(floor);
    }
}
```

子线程threadOperation收到to信号后会调用函数ThreadOperation::to()，将对应共享变量设为1。

```C++
void ThreadOperation::to(int floor){
    int val = 1;
    writeSharedInt(val, sharedRequestTo[floor - 1]);
    qDebug()<< "TO " + QString::number(floor);
}
```

子线程中的其他函数与上述函数类似，之后不再赘述。

当开关门按钮被按下时，首先判断当前电梯是否在可以开关门的状态，而后发出open或close信号调用子线程将对应共享变量设为1。

```C++
void MainWindow::buttonOpenClicked(){
    if (status == ELEVATOR_WAIT || status == ELEVATOR_STOP) emit open();
}

void MainWindow::buttonCloseClicked(){
    if (status == ELEVATOR_WAIT) emit close();
}
```

在函数repeatExec()中，首先读取电梯状态共享变量并在图形界面显示，而后若电梯处于等待状态，且电梯所在楼层所对应的按钮被按下，即电梯到达了请求的楼层，则将该按钮弹起，并发出toCancel信号调用子线程将对应共享变量设为0。

```C++
void MainWindow::repeatExec(){
    readSharedInt(sharedFloor,floor);
    readSharedInt(sharedStatus,status);
    readSharedInt(sharedDirection,direction);
    refreshDisplay();
    if (floor == -1 || status == -1 || direction == -1) {
        qDebug()<<"ELEVATOR NOT FOUND";
        return;
    }
    if (status == ELEVATOR_WAIT){
        if (buttonToDown[floor - 1]) emit toCancel(floor);
        buttonToDown[floor - 1] = 0;
        pushButtonTo[floor - 1]->setChecked(0);
    }
}
```

ElevatorControlPanel程序即编写完成。



#### StoreyControlPanel程序编写

StoreyControlPanel程序的实现方式与ElevatorControlPanel程序基本相同，此处不再赘述，但有3处主要的不同。



首先，在系统运行时，StoreyControlPanel程序会被实例化为3个线程，分别为1至3层的楼层控制面板，为了使楼层控制面板进程之间知道彼此的存在，并确定各自的所在楼层，定义以下StoreyControlPanel进程间共享的变量：

| 变量名            | 写者               | 读者               | 说明                                             |
| ----------------- | ------------------ | ------------------ | ------------------------------------------------ |
| sharedStoreyCount | StoreyControlPanel | StoreyControlPanel | 记录当前系统中已存在的StoreyControlPanel进程数量 |

同时定义函数incrementAndGetSharedInt()，用于对共享变量自增后读取之。

```C++
void MainWindow::incrementAndGetSharedInt(QSharedMemory *src, int& dst){
    if (!src->isAttached() && !src->attach()){
        qDebug() << tr("Attach Error in incrementAndGetSharedInt: ") << src->errorString();
        dst = -1;
        return;
    }
    QBuffer readBuffer;
    QDataStream readBufferStream(&readBuffer);
    QBuffer writeBuffer;
    QDataStream writeBufferStream(&writeBuffer);
    writeBuffer.open(QBuffer::ReadWrite);
    src->lock();
    readBuffer.setData(static_cast<const char *>(src->constData()), src->size());
    readBuffer.open(QBuffer::ReadWrite);
    readBufferStream >> dst;
    writeBufferStream << dst + 1;
    char *to = static_cast<char *>(src->data());
    const char *from=writeBuffer.data().constData();
    memcpy(to,from,writeBuffer.size());
    src->unlock();
    dst++;
}
```

在MainWindow类的默认构造函数中，首先判断共享变量sharedStoreyCount是否存在，若不存在则创建之并赋初值为0。而后通过incrementAndGetSharedInt()更新共享变量并得到控制面板的所在楼层。

```C++
    if (!sharedStoreyCount->attach()){
        if (!sharedStoreyCount->create(sizeof(int)) && !sharedStoreyCount->attach()) qDebug() << tr("Create Error: ") << sharedStoreyCount->errorString();
        else qDebug() << tr("Create Success");
        int val = 0;
        writeSharedInt(val, sharedStoreyCount);
    }
    incrementAndGetSharedInt(sharedStoreyCount,myFloor);
```



其次，当电梯在当前楼层等待时，上下行按钮不再用于发送上下行请求，而用于发送开门信号。如在函数buttonUpClicked()和buttonDownClicked()中应增加如下逻辑：

```C++
    if (status == ELEVATOR_WAIT && floor == myFloor){
        emit open();
        return;
    }
```



再次，在函数repeatExec()中，当电梯在当前楼层等待时，应当将电梯运行方向对应的上下行按钮弹起并发送cancel信号，若此时电梯运行方向为DIRECTION_NONE（即电梯停止在当前楼层时按下上下行按钮），则优先弹起上行按钮并处理上行请求。

```C++
    if (floor == myFloor && status == ELEVATOR_WAIT){
        if (direction == DIRECTION_UP){
            if (buttonUpDown) emit upCancel();
            buttonUpDown = 0;
            ui->pushButtonUp->setChecked(0);
        }
        else if (direction == DIRECTION_DOWN){
            if (buttonDownDown) emit downCancel();
            buttonDownDown = 0;
            ui->pushButtonDown->setChecked(0);
        }
        else {
            if (buttonUpDown){
                emit upCancel();
                buttonUpDown = 0;
                ui->pushButtonUp->setChecked(0);
            }
            else if (buttonDownDown){
                emit downCancel();
                buttonDownDown = 0;
                ui->pushButtonDown->setChecked(0);
            }
        }
    }
```



StoreyControlPanel程序即编写完成。



#### 图形界面绘制和编写

图形界面由Qt Creator绘制并编写相关交互代码，3个程序分别包含1个窗口，此处不再赘述。

[![rCTEnA.jpg](https://s3.ax1x.com/2020/12/09/rCTEnA.jpg)](https://imgchr.com/i/rCTEnA)



### 实验结果

系统运行效果参见demo.mp4，可见程序运行正常，电梯逻辑实现正确。