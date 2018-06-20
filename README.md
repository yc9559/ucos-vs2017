# μC/OS-II for Visual Studio 2017

修改自Micrium官网适配给VS2017源码，加入卢有亮的《嵌入式实时操作系统μC/OS原理与实践》移植代码中的实验例子。

## 包含的 MICRIUM 产品版本

- uC/OS-II  v2.92.13 
- uC/OS-III v3.06.02
- uC/CPU    v1.31.01
- uC/LIB    v1.38.02
 
## IDE 环境要求

- Visual Studio v2017
 
## VS解决方案文件路径

- Microsoft/Windows/Kernel/OS2/VS/OS2.sln
- Microsoft/Windows/Kernel/OS3/VS/OS3.sln
 
## 使用说明

1. 在 Visual Studio 打开上面路径的文件
2. 在项目上点右键，清理已编译的文件
3. 修改`Windows SDK Version`为可用的版本，比如`10.0.17134.0`
4. 编译并运行

![vs2017 sdk](./media/vs2017_sdk.png)

## 原始链接

<https://www.micrium.com/download/micrium_win32_kernel/>
