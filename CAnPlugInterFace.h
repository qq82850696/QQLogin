//
STDMETHOD(TileWindow)( BSTR Title, BSTR class_name, long wHow, long * retLong );

//把窗口坐标转换为屏幕坐标(指定的窗口句柄,返回X坐标,返回Y坐标)[整形数]0 失败, 1 成功
STDMETHOD(ClientToScreen)( long hWnd, long * X, long * y, long * retLong );

//根据指定进程名,枚举系统中符合条件的进程PID(进程名,[方式])[字符串]进程PID
STDMETHOD(EnumProcess)( BSTR ProcessName, short n, BSTR * retstring );

//枚举符合条件的窗口(指定的父窗口句柄,标题,类名,取值)[字符串]返回所有匹配的指定的窗口句柄字符串,格式 hwnd1,hwnd2,hwnd3
STDMETHOD(EnumWindow)( long Parent, BSTR Title, BSTR class_name, long Filte, BSTR * retstring );

//根据指定进程以及其它条件,枚举系统中符合条件的窗口(进程映像名,窗口标题,窗口类名,取值)[字符串]
STDMETHOD(EnumWindowByProcess)( BSTR exeName, BSTR Title, BSTR class_name, short filter, BSTR * retstring );

//根据指定进程pid以及其它条件,枚举系统中符合条件的窗口(进程PID,窗口标题,窗口类名,取值)[字符串]
STDMETHOD(EnumWindowByProcessId)( long nPID, BSTR Title, BSTR class_name, short filter, BSTR * retstring );

//在指定窗口的属性表中增加一个新项，或者修改一个现有项(指定的窗口句柄,项名,数据的句柄)[整形数]0 失败,1 成功
STDMETHOD(SetWindowProp)( long hWnd, BSTR lpString, BSTR hstring, long * retLong );

//获取指定窗口属性表的项值(指定的窗口句柄,项名)[整形数]0 失败,非 0 成功
STDMETHOD(GetWindowProp)( long hWnd, BSTR lpString, BSTR * retstring );

//清除指定窗口属性表的项值(指定的窗口句柄,项名)[整形数]0 失败, 1 成功
STDMETHOD(RemoveWindowProp)( long hWnd, BSTR lpString, long * retLong );

//查找窗口句柄(类名,标题)[整形数]窗口句柄
STDMETHOD(FindWindow)( BSTR class_name, BSTR Title, long * retLong );

//根据指定的进程名字,来查找可见窗口(进程名,窗口类名,窗口标题)[整形数]整形数表示的窗口句柄，没找到返回0
STDMETHOD(FindWindowByProcess)( BSTR Process, BSTR class_name, BSTR Title, long * retLong );

//根据指定的进程ID,来查找可见窗口(PID,窗口类名,窗口标题)[整形数]整形数表示的窗口句柄，没找到返回0
STDMETHOD(FindWindowByProcessId)( long process_id, BSTR class_name, BSTR Title, long * retLong );

//查找子窗口(父窗口,类名,标题)[整形数]窗口句柄
STDMETHOD(FindWindowEx)( long Parent, BSTR class_name, BSTR Title, long * retLong );

//获取浏览器的网页句柄(顶层窗口句柄,[窗口类名])[整形数]整形数表示的窗口句柄，没找到返回0
STDMETHOD(FindIEWindow)( long hWnd, BSTR Class, long * retLong );

//获取线程句柄(窗口句柄)[整形数]线程句柄
STDMETHOD(GetThreadHwnd)( long hWnd, long * retLong );

//窗口句柄取线程ID(窗口句柄)[整形数]线程ID
STDMETHOD(GetThreadID)( long hWnd, long * retLong );

//获取自身进程PID()[整形数]进程PID
STDMETHOD(GetMyPID)( long * retLong );

//获取自身句柄([窗口类名],[窗口标题])[整形数]整形数表示的窗口句柄，没找到返回0
STDMETHOD(GetMyHwnd)( BSTR class_name, BSTR Title, long * retLong );

//获取指定窗口客户区的大小(窗口句柄,x1,y1,x2,y2)[整形数]0 失败, 1 成功
STDMETHOD(GetClientRect)( long hWnd, VARIANT * x1, VARIANT * y1, VARIANT * x2, VARIANT * y2, long * retLong );

//获取窗口客户区域的宽度和高度(窗口句柄,宽度,高度)[整形数]0 失败, 1 成功
STDMETHOD(GetClientSize)( long hWnd, VARIANT * W, VARIANT * h, long * retLong );

//获取当前拥有输入焦点的窗口()[整形数]整形数表示的窗口句柄，没找到返回0
STDMETHOD(GetForegroundFocus)( long * retLong );

//获取顶层活动窗口()[整形数]整形数表示的窗口句柄，没找到返回0
STDMETHOD(GetForegroundWindow)( long * retLong );

//获取鼠标指向的窗口句柄()[整形数]整形数表示的窗口句柄，没找到返回0
STDMETHOD(GetMousePointWindow)( long * retLong );

//获取给定坐标的窗口句柄(x,y)[整形数]整形数表示的窗口句柄，没找到返回0
STDMETHOD(GetPointWindow)( long X, long y, long * retLong );

//获取特殊窗口(取值:0.桌面窗口 1.任务栏句柄)[整形数]整形数表示的窗口句柄，没找到返回0
STDMETHOD(GetSpecialWindow)( short flag, long * retLong );

//获取相关窗口(窗口句柄,取值)[整形数]整形数表示的窗口句柄，没找到返回0
STDMETHOD(GetWindow)( long hWnd, short flag, long * retLong );

//获取兄弟窗口(窗口句柄,位置)[整形数]整形数表示的窗口句柄，没找到返回0
STDMETHOD(GetBrotherWindow)( long hWnd, short p, long * retLong );

//查找窗口类名(窗口句柄)[字符串]窗口类名
STDMETHOD(GetWindowClass)( long hWnd, BSTR * retstring );

//获取进程ID(窗口句柄)[整形数]进程PID
STDMETHOD(GetWindowProcessId)( long hWnd, long * retLong );

//得到窗口程序路径(窗口句柄)[字符串]窗口句柄所在的进程全路径
STDMETHOD(GetWindowProcessPath)( long hWnd, BSTR * retstring );

//获取窗口在屏幕上的位置(窗口句柄,x1,y1,x2,y2)[整形数]0 失败,1 成功
STDMETHOD(GetWindowRect)( long hWnd, VARIANT * x1, VARIANT * y1, VARIANT * x2, VARIANT * y2, long * retLong );

//获取窗口高度和宽度(窗口句柄,宽度,高度)[整形数]0 失败,1 成功
STDMETHOD(GetWindowSize)( long hWnd, long * nWidth, long * nHeight, long * retLong );

//获取指定窗口的一些属性(指定的窗口句柄,取值)[整形数]0: 不满足条件,1:满足条件
STDMETHOD(GetWindowState)( long hWnd, short flag, long * retLong );

//查找窗口标题(窗口句柄,[方式])[字符串]窗口标题
STDMETHOD(GetWindowTitle)( long hWnd, short n, BSTR * retstring );

//移动窗口(窗口句柄,x坐标,y坐标)[整形数]0 失败, 1 成功
STDMETHOD(MoveWindow)( long hWnd, VARIANT X, VARIANT y, long * retLong );

//把屏幕坐标转换为窗口坐标(窗口句柄,返回X坐标,返回Y坐标)[整形数]0 失败, 1 成功
STDMETHOD(ScreenToClient)( long hWnd, long * X, long * y, long * retLong );

//向指定窗口发送文本数据(指定的窗口句柄,发送的文本数据,[发送方式])[整形数]0失败,1成功
STDMETHOD(SendString)( long hWnd, BSTR SetStr, short IsClear, long * retLong );

//向指定窗口发送文本数据(指定的窗口句柄,发送的文本数据,[发送方式])[整形数]0失败,1成功
STDMETHOD(SendString2)( long hWnd, BSTR SetStr, short IsClear, long * retLong );

//设置窗口客户区域的宽度和高度(指定的窗口句柄,宽度,高度)[整形数]0失败,1成功
STDMETHOD(SetClientSize)( long hWnd, VARIANT X, VARIANT y, long * retLong );

//设置窗口的状态(指定的窗口句柄,取值)
STDMETHOD(SetWindowState)( long hWnd, short flag, long * retLong );

//设置窗口的标题文字(窗口句柄,标题)[0失败,1成功]
STDMETHOD(SetWindowText)( long hWnd, BSTR Title, long * retLong );

//设置窗口的大小(窗口句柄,宽度,高度)[整形数]0 失败,1 成功
STDMETHOD(SetWindowSize)( VARIANT Hwnds, VARIANT W, VARIANT h, long * retLong );

//设置窗口透明度(窗口句柄,透明度:整形数:0-255)[整形数]0 失败,1 成功
STDMETHOD(SetWindowTransparent)( long hWnd, short trans, long * retLong );

//设置窗口鼠标穿透(窗口句柄)[整形数]0 失败,1 成功
STDMETHOD(SetMouseThrough)( long hWnd, long * retLong );

//取消窗口设置(窗口句柄,模式：0 一般窗体~1 UpdateLayeredWindow画窗体)[整形数]0 失败,1 成功
STDMETHOD(ClearSetWindow)( long hWnd, short flag, long * retLong );

//禁止窗口关闭按钮(指定的窗口句柄,[允许或禁止],[是否MDI窗口])[整形数]0 失败, 1 成功
STDMETHOD(EnableClose)( long hWnd, VARIANT_BOOL IsClose, VARIANT_BOOL MDIChild, long * retLong );

//进程名获取进程全路径(进程名)[字符串]进程路径
STDMETHOD(GetProcessPath)( BSTR ProcessName, BSTR * retstring );

//PID获取进程全路径(PID)[字符串]进程路径
STDMETHOD(GetProcessPathByPID)( long PID, BSTR * retstring );

//获取进程数量(进程名)[整形数]进程数量
STDMETHOD(GetProcessNum)( BSTR ProcessName, long * retLong );

//结束进程(映像名称)
STDMETHOD(EndByProcessOf)( BSTR ProcessName, long * retLong );

//结束自身的进程()[整形数] 0 失败,1 成功
STDMETHOD(EndMyProcess)( long * retLong );

//判断进程是否存在(进程名)[整形数]0 不存在,1 存在
STDMETHOD(IsProcessExist)( BSTR ProcessName, long * retLong );

//获取指定进程的创建时间(进程PID或进程名)[字符串]进程的创建时间
STDMETHOD(GetProcessCreateTime)( long PID, BSTR * retstring );

//通过PID取进程名(PID)[字符串]
STDMETHOD(GetProcessNameByPID)( long PID, BSTR * retstring );

//通过进程名取父进程PID(进程名)[整形数]PID
STDMETHOD(GetParentPIDByName)( BSTR szProcessName, long * retLong );

//通过PID取父进程PID(PID)[整形数]PID
STDMETHOD(GetParentPIDByPID)( long nProcessID, long * retLong );

//设置枚举窗口的超时时间,默认10s(延时 单位:毫秒)
STDMETHOD(SetEnumWindowDelay)( long dy );

//检测当前进程的父进程是否是EXPLORE的父进程()[整形数] 0 否,1 是
STDMETHOD(IsExplorer)( long * retLong );

//检测运行环境是否在调试器内()[整形数] 0 否,1 是
STDMETHOD(IsDebug)( long * retLong );

//检测csrss调试器有没有在运行()[整形数] 0 否,1 是
STDMETHOD(IsCsrss)( long * retLong );

//返回当前插件版本号()[字符串]
STDMETHOD(Ver)( BSTR * retstring );

//设置全局路径(路径)[整形数]0 失败, 1 成功
STDMETHOD(SetPath)( BSTR dPath, long * retLong );

//获取注册在系统中的Aniu.dll的路径()[字符串]返回Aniu.dll所在路径
STDMETHOD(GetBasePath)( BSTR * retstring );

//返回当前进程已经创建的Aniu对象个数()[整形数]
STDMETHOD(GetAnCount)( long * retLong );

//获取全局路径()[字符串]
STDMETHOD(GetPath)( BSTR * retstring );

//获取插件命令的最后错误()[整形数]
STDMETHOD(GetLastError)( long * retLong );

//获取插件命令的的错误信息([错误代码])[整形数]
STDMETHOD(GetLastText)( long dwErrCode, BSTR * retstring );

//设置是否弹出错误信息(显示)[整形数] 0 失败,1 成功
STDMETHOD(SetShowErrorMsg)( long EM, long * retLong );

//设置函数的使用方式(方式)
STDMETHOD(SetFuncIndex)( BSTR strMode, long * retLong );

//绑定窗口(指定的窗口句柄,[屏幕颜色获取方式],[鼠标模式],[键盘模式])[整形数] 0 失败,1 成功
STDMETHOD(BindWindow)( long Hwnds, VARIANT dis, VARIANT MouseMode, VARIANT KeyMode, long * retLong );

//解除窗口绑定()[整形数] 0 失败,1 成功
STDMETHOD(UnBindWindow)( long * retLong );

//释放当前进程物理内存到虚拟内存{慎用}([指定的窗口句柄])[整形数] 0 失败 1 成功
STDMETHOD(FreeMemory)( long hWnd, long * retLong );

//注册卸载DLL和OCX(DLL路径,[注册=True.卸载=False])[布尔值]成功 True,失败 False
STDMETHOD(RegServer)( BSTR sDllPath, VARIANT_BOOL * bRegister, VARIANT_BOOL * _arg3 );

//禁止程序重复运行(标识文本)[布尔值] false 标识已存在,true 创建标识成功
STDMETHOD(DisableMultiOpen)( BSTR lpName, VARIANT_BOOL * _arg2 );

//禁止程序重复运行(标识文本)[整形数]0 失败,>0 成功
STDMETHOD(AppNoRepeatRun)( BSTR strIDText, long * retLong );

//设置文本框只读(窗口句柄)[整形数]0 失败,1 成功
STDMETHOD(SetTextBox)( long THwnd, long * retLong );

//通过桌面快捷方式获取程序路径(快捷方式名称)[字符串]成功返回exe路径,失败返回空
STDMETHOD(GetDeskToplnkPath)( BSTR lnkName, BSTR * retstring );

//
STDMETHOD(CheckPoint2)( SAFEARRAY * * PointsX, SAFEARRAY * * PointsY, VARIANT DestX, VARIANT DestY, VARIANT_BOOL * _arg5 );

//
STDMETHOD(CheckPoint)( double DestX, double DestY, VARIANT_BOOL * _arg3 );

//根据指定的PID，强制结束进程([PID])[整形数]0 失败,1 成功
STDMETHOD(TerminateProcess)( long PID, long * retLong );

//根据指定pid打开进程，并返回进程句柄([PID])[整形数]进程句柄,失败返回 0
STDMETHOD(OpenProcess)( long PID, long * retLong );

//获取内存信息(取值:0-12)[变体型]返回整形数或字符串
STDMETHOD(GetMemoryInfo)( long flag, VARIANT * _arg2 );

//异常处理程序,收集崩溃信息()[整形数]
STDMETHOD(ExceptionHandle)( long * retLong );

//获取指定窗口所在进程的启动命令行(窗口句柄)[字符串]
STDMETHOD(GetCommandLine)( long hWnd, BSTR * retstring );

//读取快捷方式指向的路径(快捷方式)[字符串] 文件路径
STDMETHOD(ReadShortcutPath)( BSTR lnkFile, BSTR * retstring );

//创建快捷方式(快捷方式,指定路径)
STDMETHOD(CreateShortCut)( BSTR position, BSTR SourePath );

//修改靠谱.BS分辨率([宽度],[高度])
STDMETHOD(ModiResolution)( long an_Width, long an_Height );

//创建互斥体对象(互斥体名称)[整形数]互斥体句柄
STDMETHOD(CreateMutex)( BSTR sMutex, long * retLong );

//打开互斥体对象(互斥体名称)[整形数]互斥体句柄
STDMETHOD(OpenMutex)( BSTR sMutex, long * retLong );

//锁定互斥体对象(互斥体句柄,锁定时间.单位毫秒)[整形数]0 核心对象已被激活;258 等待超时;-1 出现错误，可通过GetLastError得到错误代码
STDMETHOD(WaitForObject)( long hHandle, long dwMilliseconds, long * retLong );

//解锁互斥体对象(互斥体句柄)[整形数]0 失败, 1 成功
STDMETHOD(DeleteMutex)( long hHandle, long * retLong );

//关闭一个内核对象,其中包括文件、文件映射、进程、线程、安全和同步对象等(句柄)[整形数]
STDMETHOD(ClosedObject)( long hHandle, long * retLong );

//创建一个进入线程许可证，用作进入程序中的指定许可代码区，以避免多线程冲突()[整形数] 0 失败 非0 成功
STDMETHOD(CreatePermit)( long * retLong );

//根据已经创建的许可证进入指定许可代码区，在此线程未退出之前，其它线程如要通过同一个进入许可证进入该许可代码区则必须先等待此线程退出许可代码区，从而保证了指定许可代码区在任何时候都只能有一条线程进入并执行()[整形数]
STDMETHOD(LockPermit)( long * retLong );

//指示当前线程将退出许可代码区，并允许其它使用同一进入许可证的线程进入此许可代码区()[整形数]
STDMETHOD(UnlockPermit)( long * retLong );

//删除由“CreatePermit”命令所创建的进入许可证()[整形数]0 失败 1 成功
STDMETHOD(DeletePermit)( long * retLong );

//创建或打开一个命名的或无名的事件对象([对象名称])[整形数]成功返回事件对象句柄,失败返回 0
STDMETHOD(CreateAffair)( BSTR lpName, long * retLong );

//打开一个已经存在的命名事件对象([对象句柄])[整形数]成功返回事件对象句柄,失败返回 0
STDMETHOD(OpenAffair)( BSTR lpName, long * retLong );

//设置事件的状态为有信号(事件句柄)[整数数]0,失败 1,成功
STDMETHOD(SetAffair)( long hEvent, long * retLong );

//设置事件的状态为有信号(事件句柄)[整数数]0,失败 1,成功
STDMETHOD(PulseAffair)( long hEvent, long * retLong );

//把指定的事件对象设置为无信号状态(事件句柄)[整数数]0,失败 1,成功
STDMETHOD(ResetAffair)( long hEvent, long * retLong );

//获取当前输入法()[字符串]
STDMETHOD(GetInput)( BSTR * retstring );

//获取所有输入法()[字符串]
STDMETHOD(GetAllInput)( BSTR * retstring );

//创建新的信号量(信号名,[空闲使用数量])[整形数]信号量对象的句柄
STDMETHOD(CreateSemap)( BSTR lpName, long lMaximumCount, long * retLong );

//打开信号量(信号量句柄)[整形数]信号量对象的句柄
STDMETHOD(OpenSemap)( BSTR lpName, long * retLong );

//对指定的信号量增加指定的值(信号量句柄,[需要增加的值])[整形数]信号量对象的句柄
STDMETHOD(ReleaseSemap)( long hSemaphore, long lReleaseCount, long * retLong );

//指针到字符串(字符串地址,字符串长度,[模式])[字符串]
STDMETHOD(Point2Str)( long Pointer, long nLength, short n, BSTR * retstring );

//指针到长整数(指针地址,指针长度)[整形数]
STDMETHOD(Point2Long)( long Pointer, long Length, long * retLong );

//创建共享内存([共享对象的名字])[整形数]对象句柄
STDMETHOD(CreateShareMem)( BSTR lpName, long * retLong );

//写入共享内存(对象句柄,[写入内容])[整形数]
STDMETHOD(WriteShareMem)( long lpString, BSTR lpString2 );

//读取共享内存([对象句柄])[字符串]成功返回字符串,失败返回空
STDMETHOD(ReadShareMem)( long lpString2, BSTR * retstring );

//关闭共享内存()[整形数]0,失败 1,成功
STDMETHOD(ClosedShareMem)( long * retLong );

//判断指定点(x,y)是否在区域内(一系列点,X坐标,Y坐标)[整型数]0,不在范围内 1,在范围内
STDMETHOD(IsInRect)( BSTR strCoor, long X, long y, long * retLong );

//广度优先遍历(起点,终点,二维地图数组)[字符串]成功返回路线,失败返回空
STDMETHOD(Topology)( BSTR Starting, BSTR Endting, VARIANT * MapArr, BSTR * retstring );

//程序重启([重启延时])
STDMETHOD(ProgramRestart)( long seconds );

//创建文件(文件名,[布尔值]创建方式)[长整型]创建成功的文件句柄
STDMETHOD(CreateFile)( BSTR FilePath, VARIANT_BOOL CreateIfNotExists, long * retLong );

//打开一个文件(文件名,[打开方式])[长整型]文件句柄,失败返回 -1
STDMETHOD(OpenFile)( BSTR FilePath, long FileType, long * retLong );

//关闭文件(文件句柄)[整形数] 0失败,1成功
STDMETHOD(CloseFile)( long FileHandl, long * retLong );

//移动文件(目标文件,存放路径)[整形数] 0失败,1成功
STDMETHOD(MoveFile)( VARIANT Source, VARIANT Destination, long * retLong );

//复制文件(目标文件,存放路径)[整形数] 0失败,1成功
STDMETHOD(CopyFile)( BSTR Source, BSTR Destination, long * retLong );

//删除文件(目标文件)[整形数] 0失败,1成功
STDMETHOD(DeleteFile)( SAFEARRAY * * FilePath, long * retLong );

//判断文件是否存在(目标源文件)[整形数] 存在为1 不存在为0
STDMETHOD(IsFileExist)( BSTR FilePath, long * retLong );

//判断文件夹是否存在(目标源文件)[整形数] 存在为1 不存在为0
STDMETHOD(IsFolderExist)( BSTR FilePath, long * retLong );

//检测文件或者目录(目标路径,[方式])[整形数] 根据'方式'不同返回值不同
STDMETHOD(IsPathExist)( BSTR lpPathName, VARIANT TestType, long * retLong );

//替换指定文件内容(欲查找的内容,替换的内容,文本路径)[整形数]0 失败,1 成功
STDMETHOD(ReplaceTxt)( BSTR find, BSTR Replac, BSTR * FilePath, long * retLong );

//替换指定行(指定行,欲替换的内容,文件路径)[整形数]0 失败 ,1 成功
STDMETHOD(ReplaceLine)( VARIANT Line, BSTR Replace, BSTR FilePath, long * retLong );

//小精灵重启(程序路径)[整形数]0 失败,1 成功
STDMETHOD(RestartMe)( BSTR FilePath, long * retLong );

//删除指定行(指定行,文件路径)[整形数]0 失败 ,1 成功
STDMETHOD(DeleteLine)( VARIANT Line, BSTR FilePath, long * retLong );

//读取指定行(指定行,文件路径)[字符串]
STDMETHOD(ReadSLine)( VARIANT Line, BSTR FilePath, BSTR * retstring );

//删除重复行(源文件,[新文件],[方式])[整形数]0 失败 ,1 成功
STDMETHOD(RemoveRepLine)( BSTR OldFile, BSTR NewFile, VARIANT_BOOL n, long * retLong );

//读文本(目标文件路径,返回格式: 0 数组 1 字符串 以 | 隔开 2 字符串 以Chr（0）隔开)
STDMETHOD(ReadFile)( BSTR FilePath, long n, VARIANT * _arg3 );

//读指定编码文本(目标文件路径,[文件编码格式])[字符串]
STDMETHOD(ReadFileEx)( BSTR Filename, VARIANT fmt, BSTR * retstring );

//Vista路径转Win32路径(Vista路径)[字符串]
STDMETHOD(Vista2Win32Path)( BSTR DrivePath, BSTR * retstring );

//写文本内容(目标源文件,写入的内容,[方式])[整形数] 0 失败 ,1 成功
STDMETHOD(WriteFile)( BSTR FilePath, VARIANT Text, long n, long * retLong );

//写到文件(目标源文件,写入的内容,[是否添加方式],[文件编码格式])[整形数] 0 失败 ,1 成功
STDMETHOD(WriteFileEx)( BSTR Filename, BSTR * sText, VARIANT_BOOL IsAppend, long * fmt, long * retLong );

//二进制写到文件(目标源文件,写入的内容,[写入位置])[整形数] 0 失败 ,1 成功
STDMETHOD(WriteFileByBin)( VARIANT FilePath, VARIANT Text, long fSeek, long * retLong );

//二进制读取文件(目标源文件,读取位置)[整形数] 0 失败 ,1 成功
STDMETHOD(ReadFileByBin)( VARIANT FilePath, VARIANT fSeek, BSTR * retstring );

//打开文件并定位(文件名)[文件存在返回 True,否则返回 False]
STDMETHOD(OpenFileLocate)( BSTR FilePath, long * retLong );

//定期删除文件(路径,扩展名,时间类型,时间间隔)
STDMETHOD(DelFilesTiming)( BSTR FilePath, BSTR suffix, BSTR interval, short Num, long * retLong );

//批量修改文件名(文件夹路径,旧文件名,新文件名)[整形数]0 失败,1 成功
STDMETHOD(ChangeFileName)( BSTR FilePath, BSTR OldFile, BSTR NewFile, long * retLong );

//建立文件夹(创建的文件夹路径)[整形数]0 失败 ,1 成功
STDMETHOD(CreateFolder)( BSTR FilePath, long * retLong );

//复制文件夹(目标文件夹路径,存放文件夹路径)[整形数] 0 失败 1 成功
STDMETHOD(CopyFolder)( BSTR Source, BSTR Destination, long * retLong );

//移动文件夹(目标文件夹路径,存放文件夹路径)[整形数] 0 失败 1 成功
STDMETHOD(MoveFolder)( BSTR Source, BSTR Destination, long * retLong );

//删除文件夹(文件夹路径)[整形数]0 失败 ,1 成功
STDMETHOD(DeleteFolder)( BSTR FilePath, long * retLong );

//全面获取文件夹属性(文件路径,取值,[操作对象])[字符串]
STDMETHOD(GetFileMsg)( VARIANT FilePath, short n, VARIANT_BOOL Directory, BSTR * retstring );

//获取指定文件的时间信息(文件路径,[类型 0:创建时间.1:修改时间.2:写入时间])[字符串]
STDMETHOD(GetFileTime)( BSTR FilePath, short n, BSTR * retstring );

//获取文件属性(文件路径)[整形数]
STDMETHOD(GetFileState)( BSTR FilePath, long * retLong );

//获取文件属性中详细信息里的各项目(文件路径)[字符串]
STDMETHOD(GetFileInfo)( BSTR Filename, BSTR * retstring );

//获取指定文件的短路径名(文件名)[字符串]短文件名
STDMETHOD(GetShortFileName)( BSTR strFileName, BSTR * retstring );

//获取指定文件的长路径名(文件名)[字符串]长文件名
STDMETHOD(GetLongFileName)( BSTR strFileName, BSTR * retstring );

//获取指定路径的最后成分(指定文件的路径)[字符串]
STDMETHOD(GetFileName)( BSTR FilePath, BSTR * retstring );

//获取包含路径中最后成分扩展名的字符串(指定文件的路径)[字符串]
STDMETHOD(GetExtension)( BSTR FilePath, BSTR * retstring );

//获取指定路径的父路径(指定文件的路径)[字符串]
STDMETHOD(GetFilePath)( BSTR FilePath, BSTR * retstring );

//获取文件的行数(文件路径)[整形数]
STDMETHOD(GetFileLine)( BSTR FilePath, long * retLong );

//设置文件的创建、访问及上次修改时间(文件路径,[创建时间],[上一次访问的时间],[最近一次修改的时间])[整形数] 0 失败 ,1 成功
STDMETHOD(SetFileTime)( BSTR FilePath, DATE lpCreationTime, DATE lpLastAccessTime, DATE lpLastWriteTime, long * retLong );

//设置文件属性(文件路径,取值)[整形数] 0 失败 ,1 成功
STDMETHOD(SetFileState)( BSTR FilePath, VARIANT n, long * retLong );

//枚举指定目录下的所有文件([文件名:支持通配符],[文件夹路径])[字符串]
STDMETHOD(EnumFile)( BSTR Filename, BSTR FilePath, BSTR * retstring );

//枚举指定目录下的所有文件夹(文件夹路径,过滤文件名)[字符串]
STDMETHOD(EnumFloder)( BSTR FilePath, VARIANT FlodeName, BSTR * retstring );

//Bat遍历目录下指定文件扩展名(文件扩展名,目录名,写入的txt文件名)[字符串]
STDMETHOD(EnumExtension_bat)( BSTR Extension, BSTR FilePath, BSTR ByPath, BSTR * retstring );

//根据通配符获取文件集合(文件名])[字符串]
STDMETHOD(MatchFileName)( BSTR pic_name, BSTR * retstring );

//遍历磁盘查找程序路径(程序名,[第n个盘开始],[方式])[字符串]
STDMETHOD(FindExePath)( BSTR FilePath, short Disk, short n, BSTR * retstring );

//文件比较(源文件1,源文件2,输出文件)[整形数] 0 无重复, 1 有重复
STDMETHOD(FileComp)( BSTR inFile1, BSTR inFile2, BSTR OutFile, long * retLong );

//文件去除重复行(源文件,输出文件)
STDMETHOD(FileToRepeat)( BSTR InFile, BSTR OutFile );

//文件或文件夹操作(源文件,[目标文件],[操作方式 0 移动.1 复制.2 重命名.3 删除])[整形数]0 失败,1 成功
STDMETHOD(FileOperation)( VARIANT Source, BSTR Destination, long n, long * retLong );

//文件重定向(布尔值: True 禁止重定向; False 恢复重定向)[整形数]0 失败,1 成功
STDMETHOD(FileRedirect)( VARIANT_BOOL Wow64FsEnableRedirection, long * retLong );

//弹出选择文件夹对话框([标题])[字符串]文件路径
STDMETHOD(SelectDirectory)( BSTR Title, BSTR * retstring );

//弹出选择文件对话框([过滤器的索引],[0 选择 1 保存],[初始目录])[字符串]文件路径
STDMETHOD(SelectFileEx)( short Index, short n, BSTR szInitalDir, BSTR * retstring );

//写配置文件(小节名,键名,键值,文件路径)[整形数] 0 失败 ,1 成功
STDMETHOD(WriteInI)( BSTR SectionName, VARIANT KeyWord, VARIANT ValInt, BSTR Filename, long * retLong );

//向指定的Ini写入信息.支持加密文件(小节名,键名,键值,ini文件路径,密码)[整形数]0 失败,1 成功
STDMETHOD(WriteInIPwd)( BSTR SectionName, VARIANT KeyWord, VARIANT ValInt, BSTR Filename, BSTR pwd, long * retLong );

//读配置文件(小节名,键名,文件路径)[字符串]
STDMETHOD(ReadInI)( BSTR SectionName, VARIANT KeyWord, BSTR Filename, BSTR * retstring );

//从Ini中读取指定信息.可支持加密文件(小节名,键名,ini文件路径,密码)[字符串]
STDMETHOD(ReadInIPwd)( BSTR SectionName, VARIANT KeyWord, BSTR Filename, BSTR pwd, BSTR * retstring );

//遍历小节名(配置文件路径)[字符串]
STDMETHOD(EnumIniSection)( BSTR FilePath, BSTR * retstring );

//遍历指定小节名下的键名(小节名,ini路径)[字符串]键名
STDMETHOD(EnumIniKey)( BSTR JieName, BSTR FilePath, BSTR * retstring );

//删除指定的ini小节(小节名,文件路径)[整形数] 0 失败 ,1 成功
STDMETHOD(DeleteIni)( BSTR SectionName, BSTR FilePath, long * retLong );

//删除配置项(小节名,键名,文件路径)[整形数] 0 失败 ,1 成功
STDMETHOD(DelIniItem)( BSTR SectionName, BSTR KeyName, BSTR FilePath, long * retLong );

//删除自身()
STDMETHOD(KillMe)( short n );

//设置EnumFile EnumFloder的匹配模式(0:模糊 1:精确)
STDMETHOD(SetMatchPattren)( long n );

//正则删除文本中的空行(要操作的文本)[字符串]成功返回删除空行后的文本,失败返回空
STDMETHOD(Reg_DelBlankLine)( BSTR szText, BSTR * retstring );

//正则遍历ini小节名(ini文件路径)[字符串]
STDMETHOD(Reg_EnumIniSection)( BSTR SetStr, BSTR * retstring );

//正则遍历ini键名(小节名,ini文件路径)[字符串]
STDMETHOD(Reg_EnumIniKey)( BSTR SetStr, BSTR IniPath, BSTR * retstring );

//正则删除指定的ini小节(小节名,键名,ini文件路径)[整形数]0 失败, 1 成功
STDMETHOD(Reg_DeleteIni)( BSTR Section, BSTR Key, BSTR IniPath, long * retLong );

//正则删除文本中的空行(文件路径)[整形数]0 失败, 1 成功
STDMETHOD(Reg_DeleteBlankLine)( BSTR FilePath, long * retLong );

//正则取汉字(文本)[字符串]
STDMETHOD(Reg_GetWord)( BSTR SetStr, BSTR * retstring );

//正则取字母(文本)[字符串]
STDMETHOD(Reg_GetLetter)( BSTR SetStr, BSTR * retstring );

//正则取数字(文本)[字符串]
STDMETHOD(Reg_GetNum)( BSTR SetStr, BSTR * retstring );

//正则搜索(正则文本,欲搜索的文本,[子匹配索引],[区分大小写],[多行匹配],[全局匹配])[字符串]以Vbcrlf隔开
STDMETHOD(Reg_Search)( VARIANT RegPattern, VARIANT SeraCh, VARIANT SubCount, VARIANT_BOOL IsCase, VARIANT_BOOL IsMultiline, VARIANT_BOOL IsGlobal, BSTR * retstring );

//正则表达式创建(正则文本,欲搜索的文本,[区分大小写],[多行匹配],[全局匹配])[整形数]0失败,1成功
STDMETHOD(Reg_Craete)( VARIANT Source, VARIANT Destination, VARIANT_BOOL IsCase, VARIANT_BOOL IsMultiline, VARIANT_BOOL IsGlobal, VARIANT_BOOL * _arg6 );

//正则表达式卸载()[整形数]0失败,1成功
STDMETHOD(Reg_Terminate)( long * retLong );

//正则表达式取匹配数量()[整形数]
STDMETHOD(Reg_GetMatchCount)( long * retLong );

//正则表达式取子匹配数量()[整形数]
STDMETHOD(Reg_GetSubMatchCount)( long * retLong );

//正则表达式取匹配文本(匹配索引)[字符串]
STDMETHOD(Reg_GetMatchText)( short Index, BSTR * retstring );

//正则表达式取子匹配文本(匹配索引,子匹配索引)[整形数]
STDMETHOD(Reg_GetSubMatchText)( short Index, short SubIndex, BSTR * retstring );

//正则表达式替换(表达式,欲替换的文本)[整形数]0失败,1成功
STDMETHOD(Reg_Replace)( BSTR find, BSTR Expression, BSTR * retstring );

//正则表达式替换(正则表达式,欲搜索的字符串,[欲替换的值])[字符串]
STDMETHOD(Reg_ReplaceEx)( VARIANT sPattern, VARIANT sSearch, BSTR Expression, BSTR * retstring );

//正则设置对象序号(序号)
STDMETHOD(Reg_SetRegSN)( short n );

//设置开机启动([应用程序路径])[整形数]0 失败,1 成功
STDMETHOD(HKEY_SetStartup)( BSTR progarmPath, long * retLong );

//创建注册表项双(主键,项名称)[长整型]0,失败 1,创建成功 2,打开现有的项
STDMETHOD(HKEY_CreateKey)( BSTR sRootkey, BSTR sKeyName, long * retLong );

//删除注册表项(主键,项名称,[欲删除的项],[是否包括子项])[整形数]0 失败,1 成功
STDMETHOD(HKEY_DeleteSubKey)( BSTR sRootkey, BSTR sKeyName, BSTR sDelKeyName, VARIANT_BOOL Delete, long * retLong );

//删除注册表项的值(主键,项名称,值名称)[整形数]0 失败,1 成功
STDMETHOD(HKEY_DeleteValue)( BSTR sRootkey, BSTR sKeyName, BSTR SValueName, long * retLong );

//注册表定位(主键,[项名称])[整形数]0失败,1成功
STDMETHOD(HKEY_LocateRegistry)( BSTR RegKey, BSTR ValueStr, long * retLong );

//枚举注册表项下的包含指定内容的子项(主键,项名称,欲搜索的内容.多个内容以'|'隔开)[字符串]一维数组
STDMETHOD(HKEY_EnumKey)( BSTR sRootkey, BSTR sSubKey, VARIANT conditions, SAFEARRAY * * _arg4 );

//查找注册表项下的包含指定键名的子项(主键,项名称,欲搜索的内容.多个内容以'|'隔开)[字符串]一维数组
STDMETHOD(HKEY_FindKey)( BSTR sRootkey, BSTR sSubKey, VARIANT conditions, SAFEARRAY * * _arg4 );

//查找注册表项下的包含指定键值的子项(主键,项名称,欲搜索的内容.多个内容以'|'隔开)[字符串]一维数组
STDMETHOD(HKEY_FindValue)( BSTR sRootkey, BSTR sSubKey, VARIANT conditions, SAFEARRAY * * _arg4 );

//枚举注册表项下的所有子项(主键,项名称,返回子项数组)[长整型]子项数量
STDMETHOD(HKEY_EnumSubKeys)( BSTR sRootkey, BSTR sKeyName, SAFEARRAY * * sSubKey, long * retLong );

//枚举注册表项下的所有子项(主键,项名称,返回子项数组)[整形数]子项数量
STDMETHOD(HKEY_EnumSubKeyEx)( BSTR sRootkey, BSTR sKeyName, SAFEARRAY * * subKeys, long * retLong );

//枚举注册表子项的值(主键,项名称,用于返回的值名称数组)[整形数]项数量
STDMETHOD(HKEY_EnumValue)( BSTR sRootkey, BSTR sKeyName, SAFEARRAY * * subKeys, BSTR findKey, long * retLong );

//枚举注册表子项的值(主键,项名称,用于返回的值名称数组,用于返回的值数据数组,[欲枚举的值类型])[长整型]项数量
STDMETHOD(HKEY_EnumValues)( BSTR sRootkey, BSTR sKeyName, SAFEARRAY * * SValueName, SAFEARRAY * * SValueValue, VARIANT OnlyType, long * retLong );

//注册表项查找程序路径(程序名称,[主键],[项名称])[字符串]
STDMETHOD(HKEY_GetExePath)( BSTR exeName, BSTR sRootkey, BSTR sKeyName, BSTR * retstring );

//注册表项值查找程序路径(程序名称,[主键],[项名称])[字符串]
STDMETHOD(HKEY_GetExePath2)( BSTR exeName, BSTR sRootkey, BSTR sKeyName, BSTR * retstring );

//获取注册表项字符串值(主键,项名称,值名称,[值类型],[布尔值 是否单一])[字符串]
STDMETHOD(HKEY_GetString)( BSTR sRootkey, VARIANT sKeyName, BSTR SValueName, long sz_Type, VARIANT_BOOL blnForceSingleString, BSTR * retstring );

//获取注册表项二进制值(主键,项名称,值名称,[布尔值 是否取长整型数据],[布尔值 是否取二进制数据])[整形数]0 失败,1 成功
STDMETHOD(HKEY_GetBinary)( BSTR sRootkey, VARIANT sKeyName, BSTR SValueName, VARIANT_BOOL blnGetAsLong, VARIANT_BOOL blnGetAsString, VARIANT * _arg6 );

//获取注册表项默认值(主键,项名称,[值类型])[字符串]
STDMETHOD(HKEY_GetDefault)( BSTR sRootkey, VARIANT sKeyName, VARIANT lValueType, BSTR * retstring );

//获取注册表项双字节值(主键,项名称,值名称)[长整型]十进制数据
STDMETHOD(HKEY_GetDword)( BSTR sRootkey, BSTR sKeyName, BSTR SValueName, long * retLong );

//向注册表项写入二进制值(主键,项名称,值名称,二进制数据)[整形数]0 失败,1 成功
STDMETHOD(HKEY_SetBinary)( BSTR sRootkey, BSTR sKeyName, BSTR SValueName, VARIANT lValueValue, long * retLong );

//向注册表项写入双字节值(主键,项名称,值名称,十进制数据)[整形数]0 失败,1 成功
STDMETHOD(HKEY_SetDword)( BSTR sRootkey, BSTR sKeyName, BSTR SValueName, long lValueValue, long * retLong );

//向注册表项写入字符串(主键,项名称,值名称,值数据,[值类型])[整形数]0 失败,1 成功
STDMETHOD(HKEY_SetString)( BSTR sRootkey, BSTR sKeyName, BSTR SValueName, VARIANT SValueValue, long lValueType, long * retLong );

//判断注册表项是否存在(主键,项名称)[整形数]0 不存在,1 存在
STDMETHOD(HKEY_IsKeyExists)( BSTR sRootkey, BSTR * sKeyName, long * retLong );

//判断注册表项下是否存在子项(主键,项名称)[整形数]0 不存在,1 存在
STDMETHOD(HKEY_IsSubKeyExists)( BSTR sRootkey, BSTR * sKeyName, long * retLong );

//判断注册表项的值是否存在(主键,项名称,值名称)[整形数]0 不存在,1 存在
STDMETHOD(HKEY_IsValueExists)( BSTR sRootkey, BSTR sKeyName, BSTR SValueName, long * retLong );

//导出注册表项(主键,项名称,保存的文件路径,[布尔值 是否包括版本号],[布尔值 是否包括子项],[输出状态文本框的内容])[整形数] 0 失败,1 成功
STDMETHOD(HKEY_ExportFormReg)( BSTR sRootkey, BSTR * sKeyName, VARIANT sRegFile, VARIANT_BOOL RegVersion4, VARIANT_BOOL IncludeSubkeys, long * retLong );

//导入注册表文件(.Reg 注册表文件路径)[整形数] 0 失败,1 成功
STDMETHOD(HKEY_ImportToReg)( VARIANT sRegFile, long * retLong );

//注册表主键的值转字符串值(主键)[字符串]
STDMETHOD(HKEY_RootKeyToStr)( long lRootkey, BSTR * retstring );

//注册表主键字符串转整数值(主键)[整形数]
STDMETHOD(HKEY_StrToRootKey)( BSTR sRootkey, long * retLong );

//注册表主键路径转主键值和项名称(主键全路径,用于返回的项名称)[整形数]主键值
STDMETHOD(HKEY_StrToRootKeyAbb)( BSTR StrPath, VARIANT * sKeyName, long * retLong );

//注册表字符串解密(注册表字符串)[字符串]明文
STDMETHOD(HKEY_StrDecryption)( BSTR strCiphertext, BSTR * retstring );

//VBS读取注册表(注册表项)[字符串]注册表项
STDMETHOD(ReadHKEY)( VARIANT HKEYValue, VARIANT * _arg2 );

//VBS写入注册表(注册表项,新项名,[数据类型])
STDMETHOD(WriteHKEY)( VARIANT MainHKEY, VARIANT HKEYValue, VARIANT HKEYName = vtMissing );

//VBS删除注册表(注册表项)
STDMETHOD(DelHKEY)( VARIANT ItemDeleted );

//文本批量替换(原文本,起始位置,进行的次数,是否匹分大小写,可变参数:欲被替换的文本n.用作替换的文本n+1)[字符串]替换后文本
STDMETHOD(Text_Replace)( BSTR szText, long nStart, long nCount, long nCompare, SAFEARRAY * * sonText, BSTR * retstring );

//从文本的左边按欲寻找的文本开始寻找(被查找的文本,欲寻找的文本,寻找起始位置,是否区分大小写.默认不区分)[字符串]成功返回取到的文本,失败返回空
STDMETHOD(Text_GetLeft)( BSTR szText, BSTR findText, long nStart, long nCompare, BSTR * retstring );

//从文本的右边按欲寻找的文本开始寻找(被查找的文本,欲寻找的文本,寻找起始位置,是否区分大小写.默认不区分)[字符串]成功返回取到的文本,失败返回空
STDMETHOD(Text_GetLeftRev)( BSTR szText, BSTR findText, long nStart, long nCompare, BSTR * retstring );

//从文本的右边按欲寻找的文本开始寻找(被查找的文本,欲寻找的文本,寻找起始位置,是否区分大小写.默认不区分)[字符串]成功返回取到的文本,失败返回空
STDMETHOD(Text_GetRight)( BSTR szText, BSTR findText, long nStart, long nCompare, BSTR * retstring );

//从文本的左边按欲寻找的文本开始寻找(被查找的文本,欲寻找的文本,寻找起始位置,是否区分大小写.默认不区分)[字符串]成功返回取到的文本,失败返回空
STDMETHOD(Text_GetRightRev)( BSTR szText, BSTR findText, long nStart, long nCompare, BSTR * retstring );

//按键码转按键名(键码)[字符串]按键名
STDMETHOD(AscToChr)( long X, BSTR * retstring );

//字符串繁体转简体(字符串)[字符串]
STDMETHOD(BIG5ToGB)( BSTR SetStr, BSTR * retstring );

//字符串简体转繁体(字符串)[字符串]
STDMETHOD(GBToBIG5)( BSTR SetStr, BSTR * retstring );

//按键码转按键名字(键名)[字符串]按键名
STDMETHOD(ChrToAsc)( BSTR X, long * retLong );

//中文数字转西文数字(欲转换的字符串)[整形数]转换后的数字
STDMETHOD(ChinaToNum)( BSTR Chinese, double * _arg2 );

//阿拉伯数字转中文数字(欲转换的数字,是否返回人民币大写,是否带十百千等单位,小数点个数)[字符串]转换后的数字
STDMETHOD(NumberToChinese)( VARIANT otherNum, VARIANT_BOOL isRMB, VARIANT_BOOL numOption, short dotNum, BSTR * retstring );

//取文本中的数字(文本)[字符串]
STDMETHOD(GetStrNum)( VARIANT Text, BSTR * retstring );

//取中间字符串(源文本,左边的字符,右边的字符,[方式])[字符串]
STDMETHOD(GetMidStr)( VARIANT Text, VARIANT LeftStr, VARIANT RightStr, long nType, BSTR * retstring );

//批量取中间字符串(字符串,左边的字符,右边的字符)[字符串]
STDMETHOD(GetMidStrEx)( VARIANT Text, VARIANT LeftStr, VARIANT RightStr, BSTR * retstring );

//查找一个字符串在另一个字符串中出现的次数(接受搜索的字符串,要搜索的字符串)[整形数]
STDMETHOD(GetNumOfStr)( VARIANT str1, VARIANT str2, long * retLong );

//获取全球唯一标识符()[字符串]
STDMETHOD(GetUUID)( BSTR * retstring );

//在大型文件里查找字符串(文件路径,欲查找的字符串)[整形数]返回字节位置
STDMETHOD(InStrBEx)( BSTR FilePath, BSTR strText, long * retLong );

//InStr或运算(欲查找的字符串,大于或者等于,判断的字符串.可变参数1..n)[整形数]0 没有找到,1 找到
STDMETHOD(InStrOr)( BSTR string1, VARIANT_BOOL compare, BSTR Strs, long * retLong );

//InStr与运算(欲查找的字符串,大于或者等于,判断的字符串.可变参数1..n)[整形数]0 没有找到,1 找到
STDMETHOD(InStrAnd)( BSTR string1, VARIANT_BOOL compare, BSTR Strs, long * retLong );

//按键码转字符串,同ChrToAsc(键名)[字符串]按键]
STDMETHOD(KeyCodeToStr)( long Key, BSTR * retstring );

//西文数字转中文数字(欲转换的数字)[字符串]转换后的字符
STDMETHOD(NumToChina)( long Num, BSTR * retstring );

//批量替换文本(原字符串,搜索字符串,替换字符串)[字符串]
STDMETHOD(ReplaceEx)( VARIANT Sion, VARIANT findstr, VARIANT rewith, BSTR * retstring );

//字符串批量替换(源文本,用来替换的子字符串,[可变参数]要搜索的字符串1....n)[字符串]替换后的文本
STDMETHOD(ReplaceBatCh)( VARIANT Expression, VARIANT Replacewith, SAFEARRAY * * rwith, VARIANT * _arg4 );

//随机帐号(字母个数,数字个数,是否重复．布尔值　默认:不重复 False)[字符串]
STDMETHOD(RndAccount)( long zimu, long Num, VARIANT_BOOL wei, BSTR * retstring );

//利用GUID生气随机帐号(账号个数)[字符串]
STDMETHOD(RndAccount2)( long zimu, BSTR * retstring );

//不重复的随机数(最大数,最小数,位数)[字符串]
STDMETHOD(RndNotRep)( long MAX, long Min, long wei, BSTR * retstring );

//随机生成汉字(个数)[字符串]
STDMETHOD(RndWord)( long Num, BSTR * retstring );

//随机字母(位数)[字符串]
STDMETHOD(RndStr)( long wei, BSTR * retstring );

//随机数字(位数)[字符串]
STDMETHOD(RndNum)( long wei, BSTR * retstring );

//随机姓名()[字符串]
STDMETHOD(RndName)( BSTR * retstring );

//打乱字符串顺序(字符串)
STDMETHOD(ShuffleDeck)( VARIANT Text, BSTR * retstring );

//字符串去重复(字符串)
STDMETHOD(StringToRepeat)( VARIANT Text, BSTR * retstring );

//汉字转拼音(中文汉字)[字符串]
STDMETHOD(WordtoPinyin)( VARIANT Word, BSTR * retstring );

//获取全球唯一标识符GUID()[字符串]
STDMETHOD(CreateGuid)( BSTR * retstring );

//冒泡排序(数组,[排序方式.默认:1])
STDMETHOD(Arr_BubbleSort)( VARIANT * SetArr, short fs, SAFEARRAY * * _arg3 );

//选择排序(数组,[排序方式.默认:1])
STDMETHOD(Arr_SelectSort)( VARIANT * SetArr, short fs, VARIANT * _arg3 );

//插入排序(数组,[排序方式.默认:1])
STDMETHOD(Arr_InsertSort)( VARIANT * SetArr, short fs, VARIANT * _arg3 );

//交换排序(数组,[排序方式.默认:1])
STDMETHOD(Arr_ChangeSort)( VARIANT * SetArr, short fs, VARIANT * _arg3 );

//快速排序算法(数组,[最小下标],[最大下标])
STDMETHOD(Arr_QuickSort)( VARIANT * SetArr, double l, double r, SAFEARRAY * * _arg4 );

//桶排序(数组,[排序方式.默认:1])
STDMETHOD(Arr_Bucket)( VARIANT * SetArr, short fs, VARIANT * _arg3 );

//希尔排序算法(数组,[排序方式.默认:1])
STDMETHOD(Arr_ShellSort)( VARIANT * SetArr, short fs, VARIANT * _arg3 );

//堆排序算法(数组)
STDMETHOD(Arr_Heap)( VARIANT * SetArr, VARIANT * _arg2 );

//数组去重复(数组,方式)[数组]
STDMETHOD(Arr_ToRepeat)( VARIANT * SetArr, short fs, VARIANT * _arg3 );

//计算两个坐标间的距离(X1坐标,Y1坐标,X2坐标,Y2坐标)
STDMETHOD(Calculation)( VARIANT x1, VARIANT y1, VARIANT x2, VARIANT y2, long * retLong );

//10进制转16进制(欲转换的数字)[字符串]
STDMETHOD(DecToHex)( CURRENCY Dec, BSTR * retstring );

//十六进制转十进制(字符串)
STDMETHOD(HexToDec)( BSTR Dec, short ms, double * _arg3 );

//坐标排序(坐标数组,X坐标,Y坐标)[数组]
STDMETHOD(CoorSort)( VARIANT * SetArr, long X, long y, VARIANT * _arg4 );

//带序号的坐标去重复(坐标串,[误差x],[误差y])[字符串]
STDMETHOD(dmToRepeat)( BSTR dm, short px, short py, BSTR * retstring );

//不带序号坐标去重复(坐标串,[误差x],[误差y])[字符串]
STDMETHOD(dmToRepeatNoIndex)( BSTR dm, short px, short py, BSTR * retstring );

//不带坐标的序号去重复(坐标串)[字符串]
STDMETHOD(dmToRepeatNoCoor)( BSTR dm, BSTR * retstring );

//带序号的坐标排序(坐标串)[字符串]
STDMETHOD(dmCoorSort)( BSTR dm, BSTR * retstring );

//
STDMETHOD(Repeatdm)( VARIANT dmStr, VARIANT X, VARIANT y, long lIndex, BSTR * retstring );

//
STDMETHOD(RepeatInRect)( VARIANT dmStr, VARIANT X, VARIANT y, long lIndex, BSTR * retstring );

//
STDMETHOD(SetRect)( VARIANT strRect );

//随机延时(最小值,最大值)[整形数]随机数
STDMETHOD(Random)( long Min, long MAX, long * retLong );

//获取随机坐标(左上角X,左上角Y,右下角X,右下角Y)[二维数组]
STDMETHOD(RandCoordinates)( VARIANT x1, VARIANT y1, VARIANT x2, VARIANT y2, VARIANT * _arg5 );

//取平均数(数组)
STDMETHOD(Mean)( VARIANT * SetArr, double * _arg2 );

//求小数(除数,被除数,小数部分保留位数)
STDMETHOD(ODecimal)( VARIANT divisor, VARIANT Dividend, long Figures, double * _arg4 );

//替代按键自代的延迟(延时间隔.单位:毫秒)
STDMETHOD(Delay)( double Dt );

//延时指定范围内随机毫秒,过程中不阻塞UI操作. 一般高级语言使用.按键用不到(最小毫秒数,最大毫秒数)[整形数]返回延时的毫秒数
STDMETHOD(Delays)( double mis_min, double mis_max, double * _arg3 );

//超级随机延时(最小毫秒数,最大毫秒数,[延时单位 0.毫秒 1.微秒 2.秒 3.分 4.小时 5.天])[整形数]0 失败,1 成功
STDMETHOD(DelayExs)( double mis_min, double mis_max, long dCompany, long * retLong );

//超级延时(延时间隔,[延时单位 0.毫秒 1.微秒 2.秒 3.分 4.小时 5.天])[整形数]0 失败,1 成功
STDMETHOD(DelayEx)( double Dt, long dCompany, long * retLong );

//时间限制(单位:毫秒,天数)
STDMETHOD(DelaySEx)( double Dt, short tian, long * retLong );

//从网络获取当前北京时间()[字符串:时间格式]
STDMETHOD(GetNetTime)( DATE * _arg1 );

//两个日期相加(日期1,[日期2])[时间日期型]
STDMETHOD(DateAddEx)( DATE Date1, DATE Date2, DATE * _arg3 );

//与网络时间同步()[网络时间]
STDMETHOD(TimeSynchronous)( DATE * _arg1 );

//时间限制([起始时间],[结束时间])[整形数]0 时间到,1 时间未到
STDMETHOD(Timelimit)( DATE StartTime, DATE EndTime, long * retLong );

//时间限制2(结束时间,[文件路径],[获取数量])[整形数]0 时间到,1 时间未到
STDMETHOD(TimelimitEx)( DATE SetTime, BSTR SetFile, short SetNum, long * retLong );

//时间_取现行时间戳([是否取十位时间])[字符串]
STDMETHOD(GetNowStamp)( VARIANT_BOOL IsTen, BSTR * retstring );

//时间_取随机时间戳()[字符串]
STDMETHOD(GetRndStamp)( BSTR * retstring );

//生成随机日期(最小日期,最大日期)[时间日期型]
STDMETHOD(GetRndDate)( VARIANT MinDate, VARIANT MaxDate, DATE * _arg3 );

//弹出现窗口显示内容(提示内容,[显示样式],[提示标题],[等待时间],[方式])[整形数]
STDMETHOD(MsgBoxEx)( VARIANT Prompt, long Buttons, BSTR Title, long Wait, long n, enum VbMsgBoxResult * _arg6 );

//时间_时间戳转文本(欲转换的时间戳)[字符串]转换后的文本
STDMETHOD(TimeStampToStr)( BSTR Stamp, BSTR * retstring );

//北京时间转格林尼治时间(欲转换的时间)[字符串]
STDMETHOD(TimeToGMT)( VARIANT Times, BSTR * retstring );

//北京时间转格林尼治时间(欲转换的时间)[字符串]
STDMETHOD(TimeToGMT1)( BSTR Times, BSTR * retstring );

//北京时间转格林尼治时间(欲转换的时间)[字符串]
STDMETHOD(TimeToGMT2)( BSTR Times, BSTR * retstring );

//两个时间差转字符串(时间1,时间2)[字符串]
STDMETHOD(TimeDiffToStr)( VARIANT T1, VARIANT T2, BSTR * retstring );

//格林尼治时间转北京时间(欲转换的时间)[时间日期型]
STDMETHOD(GMTtoTime)( BSTR GMT, DATE * _arg2 );

//格林尼治时间转北京时间(欲转换的时间)[时间日期型]
STDMETHOD(GMTtoTime1)( BSTR GMT, DATE * _arg2 );

//获取自windows启动以来经历的时间长度()[整形数]毫秒数
STDMETHOD(GetTime)( long * retLong );

//设置当前系统时间(欲设置的时间)[整形数] 0 失败 1 成功
STDMETHOD(SetSystemTime)( DATE Times, long * retLong );

//获取当前系统时间([返回的毫秒])[时间日期]
STDMETHOD(GetSystemTime)( long * Milliseconds, DATE * _arg2 );

//获取当前系统时间([返回的毫秒],[使用格式])[时间日期型]
STDMETHOD(GetSystemTimeEx)( long * Milliseconds, short n, DATE * _arg3 );

//注册插件(Registration)[整形数]0 失败,1 成功
STDMETHOD(RegAniu)( BSTR Reg, long * retLong );

//设置限制时间,单位:天(天数)
STDMETHOD(SetNumber)( long number );

//获取设置的限制天数()[整形数]
STDMETHOD(GetNumber)( long * retLong );

//绑定电脑(Registration)[整形数]0 失败,1 成功
STDMETHOD(BusinessDecry)( BSTR regCode, long * retLong );

//
STDMETHOD(MachineCodeEncry)( DATE DueTime, BSTR rCode, BSTR * retstring );

//加密指定的文件(文件路径,密码,加密方式)[整形数]0 失败,1 成功
STDMETHOD(EncodeFile)( BSTR FilePath, BSTR Key, short ED, long * retLong );

//解密指定的文件(文件路径,密码,解密方式)[整形数]0 失败,1 成功
STDMETHOD(DecodeFile)( BSTR FilePath, BSTR Key, short ED, long * retLong );

//加密字符串(字符串,密码,加密方式)[字符串]
STDMETHOD(EncodeString)( BSTR strSource, BSTR Key, short ED, BSTR * retstring );

//解密字符串(加密过的字符串,密码,解密方式)[字符串]
STDMETHOD(DecodeString)( BSTR Source, BSTR Key, short ED, BSTR * retstring );

//将CRC写入文件(文件路径,模式)[CRC校验码]
STDMETHOD(GetCRC32)( BSTR Lujing, short ms, BSTR * retstring );

//获取哈希值(欲加密的字符串,加密方式)[哈希值]
STDMETHOD(GetHash)( BSTR Source, short Way, BSTR * retstring );

//替代按键RunApp运行程序(可执行应用程序路径,[显示方式])[整形数]0 失败,1 成功
STDMETHOD(RunApp)( BSTR Application, long n, long lType, long * retLong );

//启动带命令行的应用程序(可执行应用程序路径,[显示方式],[是否等待])[整形数]0 失败,1 进程PID
STDMETHOD(RunApp2)( BSTR commandLine, long ShowModel, VARIANT_BOOL WaitForIt, long * retLong );

//获取屏幕的色深()[整形数]
STDMETHOD(GetScreenDepth)( long * retLong );

//获取屏幕的高度()[整形数]
STDMETHOD(GetScreenHeight)( long * retLong );

//获取屏幕的宽度()[整形数]
STDMETHOD(GetScreenWidth)( long * retLong );

//得到操作系统的类型()[整形数]
STDMETHOD(GetOsType)( float * _arg1 );

//得到操作系统的类型()[字符串]
STDMETHOD(GetOsType2)( BSTR * retstring );

//判断当前系统是否是64位操作系统()[整形数]0 否,1 是
STDMETHOD(Is64Bit)( short * _arg1 );

//判断当前系统是否是多少位操作系统()[字符串]
STDMETHOD(Is64Bit2)( BSTR * retstring );

//检测当前系统是否有开启屏幕字体平滑()[整形数]0 没开,1 已开
STDMETHOD(CheckFontSmooth)( long * retLong );

//关闭当前系统屏幕字体平滑.同时关闭系统的ClearType功能()[整形数]0 失败,1 成功
STDMETHOD(DisableFontSmooth)( long * retLong );

//检测当前系统是否有开启UAC()[整形数]0 没开,1 已开
STDMETHOD(CheckUAC)( long * retLong );

//设置当前系统的UAC(取值如下:0 关闭. 1 开启)[整形数]0 没开,1 已开
STDMETHOD(SetUAC)( long enable, long * retLong );

//设置剪贴板的内容(欲设置的内容)[整形数]0 失败,1 成功
STDMETHOD(SetClipboard)( VARIANT Text, long * retLong );

//获取剪贴板的内容()[字符串]
STDMETHOD(GetClipboard)( VARIANT * _arg1 );

//获取硬盘类型(盘符)[字符串]
STDMETHOD(GetDriveType)( BSTR Drive, BSTR * retstring );

//获取硬盘容量(盘符,0:总容量.1:剩余容量.2:已用容量,获取类型)[字符串]容量
STDMETHOD(GetDiskSpace)( BSTR DrivePath, VARIANT n, VARIANT M, BSTR * retstring );

//获取硬盘信息(取值)
STDMETHOD(GetDriveInfo)( VARIANT n, BSTR * retstring );

//获取所有磁盘盘符()[字符串]盘符,以'|'隔开
STDMETHOD(GetAllDiskName)( BSTR * retstring );

//获取局域网计算机的MAC地址(局域网IP)[字符串]Mac地址
STDMETHOD(GetLANMac)( BSTR sRemoteIP, BSTR * retstring );

//获取机器码([取值])[字符串]
STDMETHOD(GetMachineCode)( long n, BSTR * retstring );

//获取系统目录(类型)[字符串]返回路径
STDMETHOD(GetDir)( long types, BSTR * retstring );

//退出系统([0 注销 1关机 2 重启 3 快整关机],[是否强制 默认 False])[整形数]0 失败,1 成功
STDMETHOD(ExitOs)( short z, VARIANT_BOOL sd, long * retLong );

//播放音乐(路径,取值 0 播放 1 暂停 2 停止 3 关闭)[整形数]0 失败, 1 成功
STDMETHOD(Play)( BSTR Musci, short Mods, long * retLong );

//获取本机计算机名()[字符串]计算机名
STDMETHOD(GetRegEdit)( BSTR * retstring );

//获取当前用户名()[字符串]用户名
STDMETHOD(GetUserName)( BSTR * retstring );

//修改计算机名(名字)
STDMETHOD(ModCompName)( BSTR Name );

//获取博客网络验证限制的时间()[字符串]失败返回空
STDMETHOD(GetMicroTime)( BSTR * retstring );

//获取博客网络验证限制的地址()[字符串]失败返回空
STDMETHOD(GetMicroRegion)( BSTR * retstring );

//获取博客网络验证绑定的机器码()[字符串]失败返回空
STDMETHOD(GetMicroMachine)( BSTR * retstring );

//
STDMETHOD(SetValidateHtml)( BSTR strHtml );

//
STDMETHOD(Reg)( BSTR regCode, long * retLong );

//博客网络验证(博客地址,[访问方式],[提交数据])[布尔值]True 正常使用,False 禁止使用
STDMETHOD(BlogValidation)( BSTR Url, VARIANT_BOOL types, BSTR PostData, VARIANT_BOOL * _arg4 );

//博客网络验证_增强(博客地址)[布尔值]True 正常使用,False 禁止使用
STDMETHOD(BlogValidationEx)( SAFEARRAY * * UrlArr, VARIANT_BOOL * _arg2 );

//删除IE的Cookie([COOKie文件名],[Cookie路径])[整形数] 0 失败 1 成功
STDMETHOD(ClearCookie)( BSTR TheKeyWord, BSTR CookiePath, long * retLong );

//删除IE临时文件([文件路径])[整形数] 0 失败 1 成功
STDMETHOD(ClearTemp)( BSTR TempPath, long * retLong );

//删除IE历史记录()[整形数] 0 失败 1 成功
STDMETHOD(ClearHistory)( long * retLong );

//从网络上下载文件(下载地址,保存路径)[整形数] 0 失败 1 成功
STDMETHOD(DownLoadFile)( BSTR Url, BSTR SavePath, long * retLong );

//获取网页源文件(网址,编码方式: GB2312 或者 UTF-8)[字符串]成功返回网页源码,失败返回空
STDMETHOD(GetHtml)( BSTR Url, BSTR Code, BSTR * retstring );

//获取重定向后的网址(网址)[字符串]成功返回网址,失败返回空
STDMETHOD(GetRedirectUrl)( BSTR SetUrl, BSTR * retstring );

//获取博客验证得到的网页源码()[字符串]成功返回网页源代码,失败返回空
STDMETHOD(GetWebHtml)( BSTR * retstring );

//获取网页访问后的Cookie()[字符串]成功返回网页Cookie,失败返回空
STDMETHOD(GetCookie)( BSTR * retstring );

//发送邮件(用户名,密码,接收邮箱地址,信件标题,信件内容,[附件地址],[方式])[整形数]
STDMETHOD(SendEmail)( BSTR User, BSTR Pass, BSTR SendAddres, VARIANT MailCaption, VARIANT MailText, BSTR SFilename, VARIANT n, long * retLong );

//设置博客验证读取网页的编码(网页编码)[整形数]0 失败, 1 成功
STDMETHOD(SetWebCode)( BSTR Code, long * retLong );

//设置博客验证发送的邮箱(用户名,密码,接收邮箱地址,信件标题,信件内容,[附件地址])[整形数]0 失败, 1 成功
STDMETHOD(SetEMail)( SAFEARRAY * * Mail, long * retLong );

//保存图片(保存路径,[图片二进制数据])[整形数]0 失败,1 成功
STDMETHOD(SaveBitMap)( BSTR ImgPath, VARIANT ImgData, long * retLong );

//按指定类型转换(字符串,[定转换的类型])
STDMETHOD(Strconversion)( VARIANT Expsion, short conversion, VARIANT * _arg3 );

//运行脚本(脚本,脚本类型)[字符串]失败返回空,成功返回执行结果
STDMETHOD(RunScript)( BSTR ScriptCode, VARIANT_BOOL ScriptType, BSTR * retstring );

//运行脚本函数(函数源码,函数名,脚本类型VBS或JS,参数个数0-12,参数列表)[字符串]失败返回空,成功返回执行结果
STDMETHOD(RunScriptEx)( BSTR ScriptCode, BSTR FunName, VARIANT_BOOL ScriptType, short nParam, SAFEARRAY * * Param, BSTR * retstring );

//编码转换,Utf-8转Ansi(待转换的文本)
STDMETHOD(Utf8ToAnsi)( BSTR Unicode, BSTR * retstring );

//编码转换,Utf-8转GB2312(待转换的文本)
STDMETHOD(Utf8ToGB2312)( BSTR Unicode, BSTR * retstring );

//编码转换,GB2312转Utf-8(待转换的文本)
STDMETHOD(GB2312ToUtf8)( BSTR Unicode, BSTR * retstring );

//编码转换,Usc2转Ansi(待转换的文本)
STDMETHOD(Usc2ToAnsi)( BSTR Unicode, BSTR * retstring );

//网页_置Cookie(网址,[Cookie名称],[Cookie内容],[有效期])[整形数]0 失败,1 成功
STDMETHOD(Url_SetCookie)( BSTR Url, BSTR CookieN, BSTR Cookies, DATE validity, long * retLong );

//网页_取Cookie(域名,[Cookie名称])[字符串]
STDMETHOD(Url_GetCookie)( BSTR ServerName, BSTR CookieN, BSTR * retstring );

//网页_清除Cookie(域名)[整形数]0 失败,1 成功
STDMETHOD(Url_DeleteCookie)( BSTR ServerName, long * retLong );

//Url编码(待编码的文本,编码方式)[字符串]
STDMETHOD(URLEncode)( BSTR Url, short Way, BSTR * retstring );

//Url解码(待解码的文本,解码方式)[字符串]
STDMETHOD(URLDecode)( BSTR Url, short Way, BSTR * retstring );

//网页_访问_对象(网址,[访问方式],[提交信息],[提交Cookie],[返回Cookie],[附加协议头],[返回协议头],[返回状态代码],[禁止重定向],[代理地址],[超时],[用户名],[密码],[代理标识],[对象继承])[字符串]网页源码
STDMETHOD(ObjWebAccess)( BSTR Url, VARIANT_BOOL AccessType, BSTR SubmitMsg, BSTR SubCookie, BSTR * ReCookie, BSTR Addhead, BSTR * ReHead, long * Restatus, VARIANT_BOOL IsRedirect, BSTR AgentUrl, long timeOut, BSTR strUserName, BSTR strPass, short intAgentIdentity, IDispatch * intObj, BSTR * retstring6 );

//网页_访问(网址,[访问方式],[提交信息],[提交Cookie],[返回Cookie],[附加协议头],[返回协议头],[禁止重定向],[代理地址])[字符串]网页源码
STDMETHOD(WebPost)( BSTR Url, short AccessType, BSTR SubmitMsg, BSTR SubmitCookie, BSTR * ReturnCookie, BSTR Addhead, BSTR * ReturnHead, VARIANT_BOOL IsRedirect, BSTR Process, BSTR * retstring0 );

//网页_访问_事件(网址,[访问方式],[提交信息],[提交Cookie],[返回Cookie],[附加协议头],[返回协议头],[返回状态代码],[禁止重定向],[对象继承])[字符串]网页源码
STDMETHOD(EventWebAcces)( BSTR Url, VARIANT_BOOL AccessType, BSTR SubmitMsg, BSTR SubCookie, BSTR * ReCookie, BSTR Addhead, BSTR * ReHead, long * Restus, VARIANT_BOOL IsRedrect, IDispatch * ObjWin, BSTR * retstring1 );

//从网络上下载图片(网址,保存路径)[整形数]0 失败,1 成功
STDMETHOD(DownLoadPic)( BSTR ImgSrc, BSTR ImgPath, long * retLong );

//转换图片格式为24位BMP格式(要转换的图片名,要保存的BMP图片名)[整形数]0 失败,1 成功
STDMETHOD(ImageToBmp)( BSTR pic_name, BSTR bmp_name, long * retLong );

//图片互相转换(要转换的图片名,要保存的图片名,[转换格式 1 BMP;2 JPG;3 PNG;4 GIF],[JPG比率])[整形数]0 失败,1 成功
STDMETHOD(PictureSwap)( BSTR pic_name, BSTR bmp_name, long FileFormat, long JpgQuality, long * retLong );

//窗口打字(左上角x坐标,左上角y坐标,文本,颜色,[窗口句柄],[字体名称],[字体大小])[整形数]0 失败,1 成功
STDMETHOD(ShowText)( VARIANT X, VARIANT y, BSTR SetText, BSTR SetColor, long hWnd, BSTR fontName, long fontSize, long * retLong );

//窗口打字2(左上角x坐标,左上角y坐标,右下角x坐标,右下角y坐标,文本,颜色,[窗口句柄])[整形数]0 失败,成功返回的是正文的高度（逻辑单位）
STDMETHOD(ShowTextEx)( VARIANT x1, VARIANT y1, VARIANT x2, VARIANT y2, BSTR SetText, BSTR SetColor, long hWnd, long * retLong );

//获取是前台鼠标特征()[字符串]
STDMETHOD(GetCursorShape)( BSTR * retstring );

//获取鼠标位置(x,y)[整形数]0 失败, 1 成功
STDMETHOD(GetCursorPos)( VARIANT * X, VARIANT * y, long * retLong );

//按下指定的虚拟键码(虚拟按键码,[指定的窗口句柄])[整形数] 0 失败 1 成功
STDMETHOD(KeyPress)( long KeyCode, long SetHwnd, long * retLong );

//按下指定的虚拟键码(字符串描述的键码.大小写无所谓,[指定的窗口句柄])[整形数] 0 失败 1 成功
STDMETHOD(KeyPressChar)( BSTR StrKey, long SetHwnd, long * retLong );

//根据指定的字符串序列，依次按顺序按下其中的字符(字符串序列,延时,[指定的窗口句柄])[整形数] 0 失败 1 成功
STDMETHOD(KeyPressStr)( BSTR StrKey, long Delays, long SetHwnd, long * retLong );

//按住指定的虚拟键码(虚拟按键码,[指定的窗口句柄])[整形数] 0 失败 1 成功
STDMETHOD(KeyDown)( long KeyCode, long SetHwnd, long * retLong );

//按住指定的虚拟键码(字符串描述的键码.大小写无所谓,[指定的窗口句柄])[整形数] 0 失败 1 成功
STDMETHOD(KeyDownChar)( BSTR StrKey, long SetHwnd, long * retLong );

//弹起来指定的虚拟键码(虚拟按键码,[指定的窗口句柄])[整形数] 0 失败 1 成功
STDMETHOD(KeyUp)( long KeyCode, long SetHwnd, long * retLong );

//弹起来指定的虚拟键码(字符串描述的键码.大小写无所谓,[指定的窗口句柄])[整形数] 0失败 1成功
STDMETHOD(KeyUpChar)( BSTR StrKey, long SetHwnd, long * retLong );

//鼠标点击(模式,x坐标,y坐标,[指定的窗口句柄])[整形数] 0失败 1成功
STDMETHOD(MoveClick)( short Mos, long X, long y, long SetHwnd, long * retLong );

//把鼠标移动到目的点(x,y,[指定的窗口句柄])[整形数]0失败,1成功
STDMETHOD(MoveTo)( long X, long y, long SetHwnd, long * retLong );

//鼠标相对于上次的位置移动(rx,ry)[整形数]0失败,1成功
STDMETHOD(MoveR)( long X, long y, long * retLong );

//按下鼠标左键([指定的窗口句柄])[整形数]0失败,1成功
STDMETHOD(LeftClick)( long SetHwnd, long * retLong );

//双击鼠标左键([指定的窗口句柄])[整形数]0失败,1成功
STDMETHOD(LeftDoubleClick)( long SetHwnd, long * retLong );

//按住鼠标左键([指定的窗口句柄])[整形数]0失败,1成功
STDMETHOD(LeftDown)( long SetHwnd, long * retLong );

//弹起鼠标左键([指定的窗口句柄])[整形数]0失败,1成功
STDMETHOD(LeftUp)( long SetHwnd, long * retLong );

//按下鼠标右键([指定的窗口句柄])[整形数]0失败,1成功
STDMETHOD(RightClick)( long SetHwnd, long * retLong );

//双击鼠标右键([指定的窗口句柄])[整形数]0失败,1成功
STDMETHOD(RightDoubleClick)( long SetHwnd, long * retLong );

//按住鼠标右键([指定的窗口句柄])[整形数]0失败,1成功
STDMETHOD(RightDown)( long SetHwnd, long * retLong );

//弹起鼠标右键([指定的窗口句柄])[整形数]0失败,1成功
STDMETHOD(RightUp)( long SetHwnd, long * retLong );

//按下鼠标中键([指定的窗口句柄])[整形数]0失败,1成功
STDMETHOD(MiddleClick)( long SetHwnd, long * retLong );

//滚轮向下滚([滚动次数])[整形数]0失败,1成功
STDMETHOD(WheelDown)( long nMove, long * retLong );

//滚轮向上滚([滚动次数])[整形数]0失败,1成功
STDMETHOD(WheelUp)( long nMove, long * retLong );

//获取指定的按键状态.'前台信息,不是后台'(按键码)[整形数]0 弹起 ,1 按下
STDMETHOD(GetKeyState)( long Key, long * retLong );

//禁止外部输入到指定窗口([取值])[整形数]0失败,1成功
STDMETHOD(LockInput)( short locks, long * retLong );

//设置前台鼠标在屏幕上的活动范围(左上X坐标, 左上Y坐标,右下X坐标,右下Y坐标)[整形数]0失败,1成功
STDMETHOD(LockMouseRect)( long x1, long y1, long x2, long y2, long * retLong );

//设置鼠标延时(延时)
STDMETHOD(SetMouseDelay)( long Dt );

//设置按键延时(延时)
STDMETHOD(SetKeypadDelay)( long Dt );

//抓取指定区域的图像保存为bmp格式的位图(左上X坐标,左上Y坐标,右下X坐标,右下Y坐标,保存的文件名)[整形数] 0 失败,1 成功
STDMETHOD(Capture)( long x1, long y1, long x2, long y2, BSTR PathFile, long * retLong );

//抓取指定区域的图像保存格式为Gif(左上X坐标,左上Y坐标,右下X坐标,右下Y坐标,保存的文件名)[整形数] 0 失败,1 成功
STDMETHOD(CaptureGif)( long x1, long y1, long x2, long y2, BSTR PathFile, long * retLong );

//抓取指定区域的图像保存为JPG压缩格式(左上X坐标,左上Y坐标,右下X坐标,右下Y坐标,保存的文件名,[jpg压缩比率])[整形数] 0 失败,1 成功
STDMETHOD(CaptureJpg)( long x1, long y1, long x2, long y2, BSTR PathFile, long JpgQuality, long * retLong );

//抓取指定区域的图像保存格式为Png(左上X坐标,左上Y坐标,右下X坐标,右下Y坐标,保存的文件名)[整形数] 0 失败,1 成功
STDMETHOD(CapturePng)( long x1, long y1, long x2, long y2, BSTR PathFile, long * retLong );

//比较指定坐标点(x,y)的颜色(x,y,颜色串,相似度)[整形数] 0 匹配 1 不匹配
STDMETHOD(CmpColor)( long X, long y, BSTR Color, double Sim, long * retLong );

//获取指定点的颜色(X坐标,Y坐标)[字符串]RGB格式
STDMETHOD(GetColor)( long X, long y, BSTR * retstring );

//把16进制颜色值转换分解到10进制R,G,B分量中(16进制颜色值 ,R<10进制> ,G<10进制>,B<10进制>)[整形数]0 失败,1 成功
STDMETHOD(ColorToRGB)( VARIANT Color, VARIANT * r, VARIANT * G, VARIANT * B, VARIANT flags, long * retLong );

//获取指定图片的尺寸(文件名,[方式])[字符串]
STDMETHOD(GetPicSize)( BSTR PathFile, short n, BSTR * retstring );

//获取指定区域的图像,用二进制数据的方式返回(左上X坐标,左上Y坐标,右下X坐标,右下Y坐标)[字节集]
STDMETHOD(GetScreenData)( long x1, long y1, long x2, long y2, SAFEARRAY * * _arg5 );

//把BGR的颜色格式转换为RGB(BGR格式的颜色字符串)[字符串]
STDMETHOD(BGR2RGB)( BSTR Color, BSTR * retstring );

//把RGB的颜色格式转换为BGR(RGB格式的颜色字符串)[字符串]
STDMETHOD(RGB2BGR)( BSTR Color, BSTR * retstring );

//把10进制R,G,B分量合并到16进制颜色值中(R,G,B)[字符串] 16进制颜色值
STDMETHOD(GetRGB)( short r, short G, short B, BSTR * retstring );

//打开网页(网页地址)[整形数]
STDMETHOD(OpenUrls)( BSTR WebAddress, long * retLong );

//打开QQ聊天对话框(QQ号码)[整形数]
STDMETHOD(OpenChat)( BSTR QQNumber, long * retLong );

//获取外网IP()[字符串]
STDMETHOD(GetNetworkIP)( BSTR * retstring );

//获取本机所有IP()[字符串]失败返回空,成功返回所有IP
STDMETHOD(GetMachineIP)( BSTR * retstring );

//获取所有连接名()[字符串]
STDMETHOD(GetAllConnection)( BSTR * retstring );

//获取所有网络连接名()[字符串]
STDMETHOD(EnumConnectName)( BSTR * retstring );

//连接宽带(连接名,帐号,密码,[域名],[电话],[回调])
STDMETHOD(AddConnection)( BSTR strNewEntryName, BSTR strNewUsername, BSTR strNewPassword, BSTR strNewDomain, BSTR strNewPhoneNumber, BSTR strNewCallbackNumber, long * retLong );

//列出所有活动RAS连接()[整形数]连接句柄
STDMETHOD(GetConnections)( long * retLong );

//断开宽带()
STDMETHOD(HangUpAll)( VARIANT_BOOL * _arg1 );

//判断是否连上的网络()[布尔型]连接:True 断开:False
STDMETHOD(IsConnected)( VARIANT_BOOL * _arg1 );

//创建数据库(数据库文件路径,[密码])[整形数]0 失败,1 成功
STDMETHOD(DB_Create)( VARIANT strDBPath, VARIANT Pass, short * _arg3 );

//创建数据表(欲创建的表名字,欲添加的字段名字和类型,[数据库文件路径],[密码])[整形数]0 失败,1 成功
STDMETHOD(DB_CreateTable)( BSTR strTableName, VARIANT strColumnName, VARIANT strDBPath, VARIANT Pass, short * _arg5 );

//添加字段(字段名字,字段类型,[数据表名])
STDMETHOD(DB_AddColumn)( BSTR strColumnName, BSTR strColumnType, BSTR strTableName );

//打开数据库(数据库文件路径,数据表名,[密码])[整形数]0 失败,1 成功
STDMETHOD(DB_Open)( VARIANT DBPath, VARIANT Table, VARIANT Pass, short * _arg4 );

//向数据表添加一条记录(字段名,字段值)
STDMETHOD(DB_Write)( VARIANT Field, VARIANT CValue, short * _arg3 );

//读取数据表一条记录(字段名字,取值)[得到的记录值]
STDMETHOD(DB_Read)( VARIANT Title, VARIANT n, VARIANT * _arg3 );

//模糊查询数据表(字段名字,关键字,欲得到的字段名字)[记录集,以'|'分开]
STDMETHOD(DB_Query)( VARIANT Field, VARIANT KeyWord, VARIANT Answer, BSTR * retstring );

//查询数据表内相同的记录数量(字段名,字段值)[整型数]数量
STDMETHOD(DB_GetRecord)( VARIANT Column, VARIANT Text, long * retLong );

//获取当前打开的表的所有字段名()[字符串]
STDMETHOD(DB_GetFields)( BSTR * retstring );

//执行SQL语句(sql)[整形数]0 失败,1 成功
STDMETHOD(DB_Execute)( VARIANT Sql, long * retLong );

//修改数据(原值,新值)
STDMETHOD(DB_Modify)( VARIANT CValue1, VARIANT Cvalue2 );

//插入数据(字段名,字段值)
STDMETHOD(DB_Insert)( VARIANT CValue1, VARIANT Cvalue2 );

//删除数据(删除条件)
STDMETHOD(DB_Delete)( VARIANT CValue );

//判断指定的值是否存在(字段名,字段值)[整形数]0 不存在,1 存在
STDMETHOD(DB_IsValue)( VARIANT Column, VARIANT CValue, long * retLong );

//关闭数据库()
STDMETHOD(DB_Close)( );

//DAO创建数据库(数据库路径)[整形数]0 成功,非0 失败并返回错误代码
STDMETHOD(DAO_CreateData)( VARIANT DataPath, long * retLong );

//DAO获取数据库所有表名(数据库路径,[密码])[字符串]
STDMETHOD(DAO_GetTables)( VARIANT DataPath, VARIANT pwd, BSTR * retstring );

//点击带有CheckBox的Treeview(指定的窗口句柄,节点名称,[True 精确匹配 False 模糊匹配])[整数型]0,失败 1,成功
STDMETHOD(Tree_ClickItem)( long AHandle, BSTR lpszPath, VARIANT_BOOL Isfuzzy, long * retLong );

//自动定位到指定节点(指定的窗口句柄,节点名称,[True 精确匹配 False 模糊匹配])[整数型]0,失败 1,成功
STDMETHOD(Tree_ExpandItem)( long AHandle, BSTR lpszPath, VARIANT_BOOL Isfuzzy, long * retLong );

//获取Treeview选中状态(指定的窗口句柄,节点名称,[True 精确匹配 False 模糊匹配])[整数型]0,没有选中 1,选中
STDMETHOD(Tree_GetItemCheck)( long AHandle, BSTR ItemName, VARIANT_BOOL Isfuzzy, long * retLong );

//
STDMETHOD(XML_CreateAttr)( BSTR strAttr, BSTR strValue, IDispatch * * _arg3 );

//
STDMETHOD(XML_Create)( BSTR XmlPath, BSTR strRootName, IDispatch * * _arg3 );

//
STDMETHOD(XML_CreateNode)( BSTR strNode, BSTR nodename, IDispatch * * _arg3 );

//
STDMETHOD(XML_CreateElement)( BSTR strElementName, IDispatch * * _arg2 );

//
STDMETHOD(XML_GetElementList)( BSTR strElement, IDispatch * * _arg2 );

//
STDMETHOD(XML_GetAttrValue)( BSTR NodePath, BSTR * retstring );

//导入XML文件(xml文件路径)[布尔型]False,失败 True,成功
STDMETHOD(XML_Load)( BSTR XmlPath, VARIANT_BOOL * _arg2 );

//
STDMETHOD(XML_LoadXML)( BSTR xmlSource, VARIANT_BOOL * _arg2 );

//获取节点对象(节点全路径)[对象]
STDMETHOD(XML_GetNodeObject)( BSTR szNodePath, IDispatch * * _arg2 );

//获取节点集(节点全路径)[对象]
STDMETHOD(XML_GetChildNodes)( BSTR szNodePath, IDispatch * * _arg2 );

//获取节点值(节点全路径)[字符串]成功返回值,失败返回空
STDMETHOD(XML_GetNodeValue)( BSTR szNodePath, long nIndex, BSTR * retstring );

//获取节点名称(节点全路径)[字符串]成功返回名称,失败返回空
STDMETHOD(XML_GetNodeName)( BSTR szNodePath, long nIndex, BSTR * retstring );

//枚举子节点名称(节点全路径)[字符串]成功返回所有名称.以'|'隔开,失败返回空
STDMETHOD(XML_EnumChildName)( BSTR szNodePath, BSTR * retstring );

//枚举子节点值(节点全路径)[字符串]成功返回所有节点值.以'|'隔开,失败返回空
STDMETHOD(XML_EnumChildValue)( BSTR szNodePath, BSTR * retstring );

//枚举子节点属性名称和值(节点全路径)[字符串]成功返回所有名称和值.以'|'隔开,失败返回空
STDMETHOD(XML_EnumAttributes)( BSTR szNodePath, BSTR * retstring );

//获取节点属性数量(节点全路径)[整形数]失败返回0,成功返回取到的数量
STDMETHOD(XML_GetAttrCount)( BSTR szNodePath, long * retLong );

//把所做的修改保存到xml文件([xml文件路径])[整形数]失败返回0,成功返回1
STDMETHOD(XML_Save)( BSTR szXmlPath, long * retLong );

//
STDMETHOD(Get_Plugin_Description)( BSTR * ItemName, BSTR * retstring );

//
STDMETHOD(Get_Plugin_Interpret_Template)( BSTR * ItemName, BSTR * retstring );

